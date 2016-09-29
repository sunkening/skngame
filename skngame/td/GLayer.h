
#ifndef GLAYER_H
#define GLAYER_H

#include <list>
#include <map>
#include <VECTOR>
using namespace std;
#include "GObject.h"
#include "gl.h"
#include "GFrame.h"
#include "GSpirit.h"
#include "BitMapFile.h"
#include "GParticleEngine.h"
#include "GViewPort.h"
class GLayer :public GObject
{
public:
	static const int WORLD;
	static const int SCREEN;
	static const int VIEWPORT;
	GLayer();
	GLayer(int z);
	virtual ~GLayer();	
private:
	GScene* scene;
	
public:
	int z;
	int id;
	int renderPosition;
	bool needSort;
	bool needMoveSpirits;
	bool showGrid;
	vector<GSpirit*> spirits;//�����ͼ������о���
	vector<GParticleEngine*> particleEngines;//�����ͼ����������ӷ�����
	int lowColor,heighColor;//͸��ɫ��Χ������ǵ�һ��͸��ɫ��ֻ��Ҫ����lowColor

public:
	void deleteSpirit(GSpirit*);

	int getId(){return id;};
	void setId(int i){id=i;};
	void setTransparentColor(int l);
	void setTransparentColor(int l,int h);
	int getZ(){return z;}
	void setZ(int x){z=x;};
	GScene* getScene(){
		return scene;
	};
	virtual GFrame* getGrid(GViewPort* view){return null;};
	int getRenderPosition(){return renderPosition;}
	void addSpirit(GSpirit* s);
	
public :
	friend   class GScene;
};

#endif 