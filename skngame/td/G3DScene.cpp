#include <windows.h>   // include important windows stuff

#include <ddraw.h> // include directdraw
#include "G3DScene.h"
#include "G3DRenderDDraw.h"
#include "PLGFile.h"
#include "ASCFile.h"
#include "GInput.h"
#include "GLightLib.h"
#include "GMath.h"
#include "System.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G3DScene::G3DScene()
{

}

G3DScene::~G3DScene()
{

}
void G3DScene::play()
{
	render->fillSurface(screen,RGB(0,0,0));
	tank_speed=2;
	int * buffer;
	int pitch;
	render->beginPaint(screen);

static GVector4D poly1_pos;

static GMatrix4X4 mrot; // general rotation matrix
static float ang_y =1;      // rotation angle
/*

if (GInput::isKeyPress(DIK_LEFT))
{
 mrot.rotate(1,AXIS_Y);
	obj.transform(&mrot, TRANSFORM_LOCAL_ONLY,0);
}
if (GInput::isKeyPress(DIK_RIGHT))
{
	mrot.rotate(-1,AXIS_Y);
	obj.transform(&mrot, TRANSFORM_LOCAL_ONLY,0);
}*/

poly1_pos.assign(0,0,100);

// clear the drawing surface 

//DDraw_Fill_Surface(lpddsback, 0);

// game logic here...

// initialize the renderlist
//只是把多边形数设为0
rend_list.reset();
obj.reset();
sph.reset();
// insert polygon into the renderlist
 
 

// generate rotation matrix around y axis
mrot.diag(1);
//mrot.move(1,0,0);
mrot.rotate(ang_y,AXIS_Y);

//Build_XYZ_Rotation_MATRIX4X4(0, ang_y, 0, &mrot);

// rotate polygon slowly
  if (++ang_y >= 360.0) ang_y = 0;
 mrot.rotate(ang_y,AXIS_Y);
// rotate the local coords of single polygon in renderlist
//rend_list.transform(&mrot, TRANSFORM_LOCAL_ONLY);
//obj.transform(&mrot, TRANSFORM_LOCAL_ONLY,0);


if (GInput::isKeyPress(DIK_LEFT))
{
	 cam.dir.y-=1;
}
if (GInput::isKeyPress(DIK_RIGHT))
{
	 cam.dir.y+=1;
}
 
if (GInput::isKeyPress(DIK_UP))
{
	cam.pos.x += tank_speed*GMath::fastSin(cam.dir.y);
	cam.pos.z += tank_speed*GMath::fastCos(cam.dir.y);
}
if (GInput::isKeyPress(DIK_DOWN))
{
	cam.pos.x -= tank_speed*GMath::fastSin(cam.dir.y);
   cam.pos.z -= tank_speed*GMath::fastCos(cam.dir.y);
}
if (GInput::isKeyPress(DIK_W))
{
	 if (wire)
	 {
		 wire=0;
	 }else wire=1;
	 GSystem::waitClock(200);
}
if (GInput::isKeyPress(DIK_B))
{
	if (back)
	{
		back=0;
	}else back=1;
 GSystem::waitClock(100);
}	
if (GInput::isKeyPress(DIK_S))
{
	if (sortp)
	{
		sortp=0;
	}else sortp=1;
	 GSystem::waitClock(100);
}


		
for (int x=0;x<2;x++)
	for (int z=0;z<1;z++)
	{
		tank.reset();
		tank.worldPosition.z=z*150+200;
		tank.worldPosition.y=-100;
		tank.worldPosition.x=x*150;
		
		cam.cullObject(&tank,CULL_OBJECT_XYZ_PLANES);
		tank.transform(&mrot,TRANSFORM_LOCAL_ONLY,1);
		tank.localToWorld();
		
	 //	rend_list.insertObjectIndex(&tank,0);

	}
	
	cam.buildMatrixEuler(CAM_ROT_SEQ_ZYX);

	 
	cam.cullObject(&obj,CULL_OBJECT_XYZ_PLANES);
	cam.cullObject(&sph,CULL_OBJECT_XYZ_PLANES);
	 
	GMatrix4X4 move;
	move.move(0,0,100);
	mrot*=move;
	sph.transform(&mrot, TRANSFORM_LOCAL_TO_TRANS,0);
	move.move(-50,0,0);
	mrot*=move;
	obj.transform(&mrot, TRANSFORM_LOCAL_TO_TRANS,0);
	if (back)
	{
		obj.removeBackFaces(&cam);
		sph.removeBackFaces(&cam);
	}
	 
	
 	rend_list.insertObjectIndex(&sph,0);
	rend_list.insertObjectIndex(&obj,0);
if (back)
{
	//rend_list.removeBackFaces(&cam);
}
 
 render3d->lightRenderListWorld(&rend_list,&cam,&lights);

// perform local/model to world transform
//rend_list.toWorld(&poly1_pos);

// generate camera matrix

//obj.removeBackFaces(&cam);
// apply world to camera transform
rend_list.worldToCamera(&cam);
//obj.worldToCamera(&cam);
if (sortp)
{
	rend_list.sort(SORT_POLYLIST_NEARZ);
	rend_list.sort(SORT_POLYLIST_AVGZ);
}

 
// apply camera to perspective transformation
rend_list.cameraToPerspective(&cam);
//obj.cameraToPerspective(&cam);

// apply screen transform
rend_list.perspectiveToScreen(&cam);
//obj.perspectiveToScreen(&cam);

// draw instructions
 

// lock the back buffer
//DDraw_Lock_Back_Surface();

// render the polygon list
if (wire)
{
	render3d->drawRenderListWire(&rend_list);
}else
{

render3d->drawRenderListSolid(&rend_list);
}


 //render3d->drawObjectIndexWire(&obj);

// unlock the back buffer
 

// flip the surfaces
 

// sync to 30ish fps
	render->endPaint();
	render->drawText("Press ESC to exit.", 5, 0, RGB(0,0,0), screen);
	render->drawText("Press W to turn on/off solid render.", 5, 22, RGB(0,0,0), screen);
	render->drawText("Press B to turn on/off Backfacecull.", 5, 44, RGB(0,0,0), screen);
	render->drawText("方向键控制摄像机", 5, 66, RGB(0,0,0), screen);
}

int G3DScene::onLoad(GBandle *bandle)
{
	wire=1;
	back=1;
	sortp=1;
	int width=640;
	int height=480;
	
	layer=new GBackgroundLayer;
	layer->id=1;
	addLayer(layer);
	GSpirit*spirit= layer->addImage(this,null,0,0,width,height,-1);
	spirit->setPosition(0,0);

	spirit->z=1000;

	screen=spirit->frame;
	render=GameApp::getInstance()->getRender();

	//初始化3D渲染器
	render3d=new G3DRenderDDraw;
	render3d->render2d=render;

	//相机的位置和朝向
	GVector4D cam_pos;
	cam_pos.assign(0,0,-100);
	GVector4D cam_dir;
	cam_dir.assign(0,0,0);
	
	poly1.state=POLY4DV1_STATE_ACTIVE;
	poly1.attr=0;
	poly1.color=RGB(0,255,0);
	poly1.vlist[0].x = 0;
	poly1.vlist[0].y = 50;
	poly1.vlist[0].z = 0;
	poly1.vlist[0].w = 1;
	
	poly1.vlist[1].x = 50;
	poly1.vlist[1].y = -50;
	poly1.vlist[1].z = 0;
	poly1.vlist[1].w = 1;
	
	poly1.vlist[2].x = -50;
	poly1.vlist[2].y = -50;
	poly1.vlist[2].z = 0;
	poly1.vlist[2].w = 1;
	
	poly1.next = poly1.prev = NULL;
	cam.init(CAM_MODEL_EULER, // euler camera model
		&cam_pos,  // initial camera position
		&cam_dir,  // initial camera angles
		NULL,      // no initial target
		50.0,      // near and far clipping planes
		500.0,
		90.0,      // field of view in degrees
		width,   // size of final screen viewport
             height);
	PLGFile cube;
	GVector4D scale;
	scale.assign(5,5,5);
	GVector4D pos;
	pos.assign(0,0,0);
	GVector4D rot;
	rot.assign(0,0,0);
	cube.load(&obj,"res/plg/cube2.plg",&scale,&pos,&rot);
	obj.worldPosition.assign(-30,0,100);
 
	
	ASCFile asc;
	asc.load(&sph,"res/plg/sphere01.asc",&scale,&pos,&rot);
	sph.worldPosition.assign(10,0,100);
	GMatrix4X4 xrote;
	xrote.rotate(-90,AXIS_X);
	sph.transform(&xrote,TRANSFORM_LOCAL_ONLY,0);
//	rend_list.insertPoly(&poly1);
	
	scale.assign(0.75,0.75,0.75);
	pos.assign(0,-50,0);
	cube.load(&tank,"res/plg/tank2.plg",&scale,&pos,&rot);
	GLightInfinit* light1=new GLightInfinit;
	GLightAmbient *light2=new GLightAmbient;

	light1->dir.assign(-1,0,0);
	light1->c_diffuse.assign(150,150,50);
 
	light2->c_ambient.assign(60,40,30);
	lights.insert(light2);
	lights.insert(light1);

 
	 





	
	return 1;
}
