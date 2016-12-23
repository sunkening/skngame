#include <list>
#include<d3d9.h>
#include<d3dx9.h>
#include <iostream>
using namespace std;
#include "D3DUtil.h"
#include "Particle.h"
namespace skn_d3d {
	const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	PSystem::PSystem()
	{
		_device = 0;
		_vb = 0;
		_tex = 0;
	}

	PSystem::~PSystem()
	{
		D3DUtil::Release<IDirect3DVertexBuffer9*>(_vb);
		D3DUtil::Release<IDirect3DTexture9*>(_tex);
	}

	bool PSystem::init(IDirect3DDevice9 *device, TCHAR *   texFileName)
	{
		_device = device; // save a ptr to the device

		HRESULT hr = 0;
		// ��Ϊÿ֡�����Ӹ��£������ö�̬���棬
		hr = device->CreateVertexBuffer(
			_vbSize * sizeof(Particle),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			Particle::FVF,
			D3DPOOL_DEFAULT, // D3DPOOL_MANAGED can't be used with D3DUSAGE_DYNAMIC 
			&_vb,
			0);

		if (FAILED(hr))
		{
			::MessageBox(0, TEXT("CreateVertexBuffer() - FAILED"), TEXT("PSystem"), 0);
			return false;
		}

		hr = D3DXCreateTextureFromFile(
			device,
			texFileName,
			&_tex);

		if (FAILED(hr))
		{
			::MessageBox(0, TEXT("D3DXCreateTextureFromFile() - FAILED"), TEXT("PSystem"), 0);
			return false;
		}

		return true;
	}

	void PSystem::reset()
	{
		std::list<ParticleAttribute>::iterator i;
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			resetParticle(&(*i));
		}
	}
	void PSystem::addParticle()
	{
		ParticleAttribute attribute;
		resetParticle(&attribute);
		_particles.push_back(attribute);
	}

	void PSystem::preRender()
	{
		_device->SetRenderState(D3DRS_LIGHTING, false);
		_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
		_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
		_device->SetRenderState(D3DRS_POINTSIZE, D3DUtil::FtoDw(_size));
		_device->SetRenderState(D3DRS_POINTSIZE_MIN, D3DUtil::FtoDw(0.0f));

		// control the size of the particle relative to distance
		_device->SetRenderState(D3DRS_POINTSCALE_A, D3DUtil::FtoDw(0.0f));
		_device->SetRenderState(D3DRS_POINTSCALE_B, D3DUtil::FtoDw(0.0f));
		_device->SetRenderState(D3DRS_POINTSCALE_C, D3DUtil::FtoDw(1.0f));

		// use alpha from texture
	 	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	void PSystem::render()
	{
		//
		// Remarks:  The render method works by filling a section of the vertex buffer with data,
		//           then we render that section.  While that section is rendering we lock a new
		//           section and begin to fill that section.  Once that sections filled we render it.
		//           This process continues until all the particles have been drawn.  The benifit
		//           of this method is that we keep the video card and the CPU busy.  

		if (!_particles.empty())
		{
			//
			// set render states
			//

			preRender();

			_device->SetTexture(0, _tex);
			_device->SetFVF(Particle::FVF);
			_device->SetStreamSource(0, _vb, 0, sizeof(Particle));

			//
			// render batches one by one
			//

			// start at beginning if we're at the end of the vb
			if (_vbOffset >= _vbSize)
				_vbOffset = 0;

			Particle* v = 0;

			_vb->Lock(
				_vbOffset * sizeof(Particle),
				_vbBatchSize * sizeof(Particle),
				(void**)&v,
				_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

			DWORD numParticlesInBatch = 0;

			//
			// Until all particles have been rendered.
			//
			std::list<ParticleAttribute>::iterator i;
			for (i = _particles.begin(); i != _particles.end(); i++)
			{
				if (i->_isAlive)
				{
					//
					// Copy a batch of the living particles to the
					// next vertex buffer segment
					//
					v->_position = i->_position;
					v->_color = (D3DCOLOR)i->_color;
					//v -> _size = 1.0f;
					v++; // next element;

					numParticlesInBatch++; //increase batch counter

										   // if this batch full?
					if (numParticlesInBatch == _vbBatchSize)
					{
						//
						// Draw the last batch of particles that was
						// copied to the vertex buffer. 
						//
						_vb->Unlock();

						_device->DrawPrimitive(
							D3DPT_POINTLIST,
							_vbOffset,
							_vbBatchSize);

						//
						// While that batch is drawing, start filling the
						// next batch with particles.
						//

						// move the offset to the start of the next batch
						_vbOffset += _vbBatchSize;

						// don't offset into memory thats outside the vb's range.
						// If we're at the end, start at the beginning.
						if (_vbOffset >= _vbSize)
							_vbOffset = 0;

						_vb->Lock(
							_vbOffset * sizeof(Particle),
							_vbBatchSize * sizeof(Particle),
							(void**)&v,
							_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

						numParticlesInBatch = 0; // reset for new batch
					}
				}
			}

			_vb->Unlock();

			// its possible that the LAST batch being filled never 
			// got rendered because the condition 
			// (numParticlesInBatch == _vbBatchSize) would not have
			// been satisfied.  We draw the last partially filled batch now.

			if (numParticlesInBatch)
			{
				_device->DrawPrimitive(
					D3DPT_POINTLIST,
					_vbOffset,
					numParticlesInBatch);
			}

			// next block
			_vbOffset += _vbBatchSize;

			//
			// reset render states
			//

			postRender();
		}
	}

	void PSystem::postRender()
	{
		_device->SetRenderState(D3DRS_LIGHTING, true);
		_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
		_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
		_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}

	bool PSystem::isEmpty()
	{
		return _particles.empty();
	}

	bool PSystem::isDead()
	{
		std::list<ParticleAttribute>::iterator i;
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			// is there at least one living particle?  If yes,
			// the system is not dead.
			if (i->_isAlive)
				return false;
		}
		// no living particles found, the system must be dead.
		return true;
	}

	void PSystem::removeDeadParticles()
	{
		std::list<ParticleAttribute>::iterator i;

		i = _particles.begin();

		while (i != _particles.end())
		{
			if (i->_isAlive == false)
			{
				// erase returns the next iterator, so no need to
				// incrememnt to the next one ourselves.
				i = _particles.erase(i);
			}
			else
			{
				i++; // next in list
			}
		}
	}

	//*****************************************************************************
	// Snow System
	//***************

	Snow::Snow(/*d3d::BoundingBox* boundingBox, */int numParticles)
	{
		//_boundingBox = *boundingBox;
		_size = 2.0f;
		_vbSize = 2048;
		_vbOffset = 0;
		_vbBatchSize = 512;

		for (int i = 0; i < numParticles; i++)
			addParticle();
	}

	void Snow::resetParticle(ParticleAttribute* attribute)
	{
		attribute->_isAlive = true;

		// get random x, z coordinate for the position of the snow flake.
		D3DXVECTOR3 minPosition(-100,50,-100);
		D3DXVECTOR3 maxPosition(100,100,100);
		D3DUtil::GetRandomVector(
			&attribute->_position,
			&minPosition,
			&maxPosition);

		// no randomness for height (y-coordinate).  Snow flake
		// always starts at the top of bounding box.
		attribute->_position.y = 150;

		// snow flakes fall downwards and slightly to the left
		attribute->_velocity.x = D3DUtil::GetRandomFloat(0.0f, 1.0f) * -3.0f;
		attribute->_velocity.y = D3DUtil::GetRandomFloat(0.0f, 1.0f) * -10.0f;
		attribute->_velocity.z = 0.0f;
		
		// white snow flake
		attribute->_color = D3DUtil::WHITE;
	}

	void Snow::update(float timeDelta)
	{
		std::list<ParticleAttribute>::iterator i;
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			i->_position += i->_velocity * timeDelta;

			// is the point outside bounds?
			if ( i->_position.y<0)
			{
				// nope so kill it, but we want to recycle dead 
				// particles, so respawn it instead.
				resetParticle(&(*i));
			}
		}
	}

}