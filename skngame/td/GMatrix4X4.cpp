// GMatrix4X4.cpp: implementation of the GMatrix4X4 class.
//
//////////////////////////////////////////////////////////////////////

#include "GMatrix4X4.h"
#include "GVector4D.h"
#include <MATH.H>
#include <string.h>
#include "GMath.h"
#include "g3dlib.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GMatrix4X4::GMatrix4X4()
{
	memset(M,0,sizeof M);
}

GMatrix4X4::~GMatrix4X4()
{

}

void GMatrix4X4::diag(float n)
{
	memset(M,0,sizeof M);
	for (int i=0;i<4;i++)
	{
		M[i][i]=n;
	}
}

void GMatrix4X4::move(GVector4D* v)
{
	diag(1);
	M[3][0]+=v->x;
	M[3][1]+=v->y;
	M[3][2]+=v->z;
}

void GMatrix4X4::move(int x,int y,int z)
{
	diag(1);
	M[3][0]+=x;
	M[3][1]+=y;
	M[3][2]+=z;
}

void GMatrix4X4::rotate(float theta,int axis_select)
{
	diag(1);
	float cos_theta = GMath::fastCos(theta);  // no change since cos(-x) = cos(x)
	float sin_theta = GMath::fastSin(theta); 
	switch(axis_select)
	{
	case AXIS_X:
		{
			M[1][1]=cos_theta;
			M[2][2]=cos_theta;
			M[1][2]=sin_theta;
			M[2][1]=-sin_theta;
		}break;
	case AXIS_Y:
		{
			M[0][0]=cos_theta;
			M[2][2]=cos_theta;
			M[0][2]=-sin_theta;
			M[2][0]=sin_theta;
		}break;
	case AXIS_Z:
		{
			M[0][0]=cos_theta;
			M[1][1]=cos_theta;
			M[0][1]=sin_theta;
			M[1][0]=-sin_theta;
		}break;
	}
}

void GMatrix4X4::rotate(float theta_x, float theta_y, float theta_z )
{
	
GMatrix4X4 mx, my, mz;       // working matrices
float sin_theta=0, cos_theta=0;   // used to initialize matrices
int rot_seq = 0;                  // 1 for x, 2 for y, 4 for z

// step 1: based on zero and non-zero rotation angles, determine
// rotation sequence
if (fabs(theta_x) > EPSILON_E5) // x
   rot_seq = rot_seq | 1;

if (fabs(theta_y) > EPSILON_E5) // y
   rot_seq = rot_seq | 2;

if (fabs(theta_z) > EPSILON_E5) // z
   rot_seq = rot_seq | 4;

// now case on sequence
	switch(rot_seq)
	{
		case 0: // no rotation
		{
      // what a waste!
			return;
		} break;

		case 1: // x rotation
		{
			rotate(theta_x,AXIS_X);
			return;
		} break;
		case 2: // y rotation
		{
			rotate(theta_y,AXIS_Y);
			return;
		} break;
		case 3: // xy rotation
		{
			mx.rotate(theta_x,AXIS_X);
			my.rotate(theta_y,AXIS_Y);
			*this=mx*my;
			return;
		} break;
		case 4: // z rotation
		{
			rotate(theta_z,AXIS_Z);
			return;
		} break;

		case 5: // xz rotation
		{
			mx.rotate(theta_x,AXIS_X);
			mz.rotate(theta_z,AXIS_Z);
			*this=mx*mz;
			return;
		} break;

		case 6: // yz rotation
		{
			my.rotate(theta_y,AXIS_Y);
			mz.rotate(theta_z,AXIS_Z);
			*this=my*mz;
			return;
		} break;

		case 7: // xyz rotation
		{
			mx.rotate(theta_x,AXIS_X);
			my.rotate(theta_y,AXIS_Y);
			mz.rotate(theta_z,AXIS_Z);
			*this=mx*my*mz;
			return;
		} break;
		default: break;
      } // end switch
}

GMatrix4X4 GMatrix4X4::operator*(const GMatrix4X4& mt)const
{
	GMatrix4X4 mprod;
	for (int row=0; row<4; row++)
    {
		for (int col=0; col<4; col++)
        {
			
			float sum = 0; // used to hold result
			for (int index=0; index<4; index++)
			{
				// add in next product pair
				sum+=(M[row][index]*mt.M[index][col]);
			} // end for index
			// insert resulting row,col element
			mprod.M[row][col] = sum;
        } // end for col
    } // end for row
	return mprod;
}

GMatrix4X4 GMatrix4X4::operator*=(const GMatrix4X4& mt)
{
	*this= (*this) * mt;
	return *this;
}
