// GColorLayer.cpp: implementation of the GColorLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "GColorLayer.h"
#include "GameApp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GColorLayer::GColorLayer()
{
	pieces=null;
	amount_x=0;
	amount_y=0;
	pieceWidth=0;
	pieceHeight=0;
	followBitmaps=null;
	images=null;//
	followColor=0;
}

GColorLayer::~GColorLayer()
{
	if (pieces)
	{
		delete[] pieces;
	}
}

void GColorLayer::init(GTerrainPiece * p,int a_x,int a_y,int pwidth,int pheight)
{
	pieces=p;
	amount_x=a_x;
	amount_y=a_y;
	pieceWidth=pwidth;
	pieceHeight=pheight;
	GRenderer *render=GameApp::getInstance()->getRender();
	pieces=new GTerrainPiece[amount_x*amount_y];
	memcpy(pieces,p,amount_x*amount_y*sizeof(GTerrainPiece));
	images=new GFrame* [amount_x*amount_y];
	followBitmaps=new BitMapFile* [amount_x*amount_y];
//GTerrainPiece** pieceArray;
	int x0=0;//背景方块的x坐标
	int y0=pheight*(amount_y-1);//背景方块的y坐标
	for (int j=0;j<amount_y;j++)
	{
		for (int i=0;i<amount_x;i++)
		{
			GTerrainPiece* piece=&pieces[j*amount_x+i];
			BitMapFile *top=new BitMapFile();
			
			top->load(piece->topPath);
	
			images[j*amount_x+i]=render->createFrame(top,lowColor,heighColor);
			
			delete top;
			//生成地图片的精灵
			GSpirit* s= new GSpirit( );
			s->setFrame(images[j*amount_x+i]);
			s->setPosition(x0+i*amount_x,y0);
			addSpirit(s);
			x0+=amount_x;

			if (piece->bottomPath.length()!=0)
			{
				BitMapFile *bottom=new BitMapFile();
					
				bottom->load(piece->bottomPath.c_str());
				followBitmaps[j*amount_x+i]=bottom;
			}else{
				followBitmaps[j*amount_x+i]=null;
			}
			

		}
		x0=0;
		y0-=amount_y;
	}
	

	

	

}

void GColorLayer::follow(vector<GSpirit*> *spirits)
{
	 
}

void GColorLayer::followSpirit(GSpirit*spirit)
{
	 int color=getColor(&spirit->position);
	if (!spirit->isFollow)return;
	
//	G2DPointf position2=spirit->position+spirit->positionOffset;//获取物体移动后的位置
	if (spirit->positionOffset.x==0&&spirit->positionOffset.y==0)return;
	int type=spirit->rigid->type;
	
		switch(type)
		{
		case RIGID_SQUARE:
			{
				G2DRigidSquare  *r=(G2DRigidSquare*)spirit->rigid;
				G2DPointf rigidPosition=spirit->position+r->p0;//获取rigid原始位置
				G2DPointf rigidPosition2=rigidPosition+spirit->positionOffset ;//获取rigid终点位置
				int dy=spirit->positionOffset.y;
				int dx=spirit->positionOffset.x;
				
				int y_inc,x_inc,index;
				if (dy>0)
				{
					y_inc=1;
				}else{
					y_inc=-1;
					dy=-dy;
				}
				if (dx>0)
				{x_inc=1;
				}else{
					x_inc=-1;
					dx=-dx;
				}
				int de=0;
			 
				
				 
				G2DPoint temp_rigidPosition(spirit->position.x+r->p0.x,spirit->position.y+r->p0.y);
				G2DPoint v(0,0);
				if (dx>dy)
				{
					de=dy;
					v.x=x_inc;
					v.y=0;
					for (index=0;index<dx;index++)
					{
						if (de>=dx)
						{
							v.y=y_inc;
							de-=dx;
						}else v.y=0;
						if (getColor(temp_rigidPosition.x+v.x,temp_rigidPosition.y+v.y)==followColor)
						{
							break;

						}else
						{
							temp_rigidPosition.x+=v.x;
							temp_rigidPosition.y+=v.y;
							de+=dy;
						}
					}
				}else
				{
					de=dx;
					v.x=0;
					v.y=y_inc;
					for (index=0;index<dy;index++)
					{
						if (de>=dy)
						{
							v.x=x_inc;
							de-=dy;
						}else v.x=0;
						if ( getColor(temp_rigidPosition.x+v.x,temp_rigidPosition.y+v.y)==followColor)
						{
							 
							break;
						}else
						{
							temp_rigidPosition.x+=v.x;
							temp_rigidPosition.y+=v.y;
							de+=dx;
						}
					}
				}
				
				spirit->setPositionOffset(temp_rigidPosition.x-rigidPosition.x,temp_rigidPosition.y-rigidPosition.y);	
			}break;
		case RIGID_CIRCLE:
			{
				
			}break;
		}
}


bool GColorLayer::canMove(int x,int y)
{
	G2DPoint p(x,y);
	if (getColor(&p)==followColor)
	{
		return false;
	}
	return true;
}

int GColorLayer::getColor(G2DPointf* worldPosition)
{
	G2DPoint p(*worldPosition);
	return getColor(&p);
}
int GColorLayer::getColor(G2DPoint* worldPosition)
{
	int world_x=worldPosition->x;
	int world_y=worldPosition->y;
	return 	getColor(  world_x,  world_y);
}

int GColorLayer::getColor(int world_x,int world_y)
{
	int index_x=world_x/pieceWidth;
	int index_y=world_y/pieceHeight;
	//超出边界	
	if (index_x>=amount_x||index_y>=amount_y||index_x<0||index_y<0)
	{
		return -1;//
	}
	index_y=amount_y-1-index_y;
	BitMapFile* bitmap=followBitmaps[index_y*amount_y+index_x];
	if (!bitmap)
	{
		return -1;
	}
	int piece_x=world_x%pieceWidth;
	int piece_y=pieceHeight-1-world_y%pieceHeight;
	
	UCHAR * buffer=bitmap->buffer;
	
	buffer+=pieceWidth*3*piece_y+piece_x*3;
	UCHAR b=*buffer++;
	UCHAR g=*buffer++;
	UCHAR r=*buffer++;
	UCHAR color_char[4]={b,g,r,0};
	int color=*(int*)color_char;
	return color;
}

bool GColorLayer::isFollowed(GSpirit *s,G2DPoint *v)
{
	 return !canMove(s->position.x+v->x,s->position.y+v->y);
}
