#pragma once
namespace skn_d3d {
	struct Particle
	{
		D3DXVECTOR3 _position;
		D3DCOLOR _color;
		//float _size;
		static const DWORD FVF;
	};
	struct ParticleAttribute 
	{
		D3DXVECTOR3 _position;
		D3DXVECTOR3 _velocity;
		D3DXVECTOR3 _acceleration;
		float _lifeTime;
		float _age;
		D3DCOLOR _color;
		D3DCOLOR _colorFade;
		bool _isAlive;
	};
	class PSystem {
	public:
		PSystem();
		virtual ~PSystem();
		virtual bool init(IDirect3DDevice9 *device, TCHAR* texFileName);
		virtual void reset();
		virtual void resetParticle(ParticleAttribute* attribute) = 0;
		virtual void addParticle();
		virtual void update(float timeDelta) = 0;
		virtual void preRender();
		virtual void render();
		virtual void postRender();

		bool isEmpty();
		bool isDead();
	protected:
		virtual void removeDeadParticles();
		IDirect3DDevice9* _device;
		D3DXVECTOR3 _origin;
		float _emitRate;
		float _size;
		IDirect3DTexture9 * _tex;
		IDirect3DVertexBuffer9 * _vb;
		std::list<ParticleAttribute> _particles;
		int _maxParticles;
		DWORD _vbSize;
		DWORD _vbOffset;
		DWORD _vbBatchSize;
	};
	class Snow : public PSystem
	{
	public:
		Snow( int numParticles);
		void resetParticle(ParticleAttribute* attribute);
		void update(float timeDelta);
	};
}