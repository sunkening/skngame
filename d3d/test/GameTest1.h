#pragma once

class GameTest1 :public skn_d3d::GameMain
{

public:
	virtual bool setup() override;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};
//光照
class GameTest2 :public skn_d3d::GameMain
{

public:
	virtual bool setup() override;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};
//纹理和融合
class GameTest3 :public skn_d3d::GameMain
{

public:
	virtual bool setup() override;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};

//mesh
class GameTest4 :public skn_d3d::GameMain
{

public:
	ID3DXMesh* mesh;
	IDirect3DTexture9 *textures[2];
	static const int numSub;
	virtual bool setup() override;
	//IDirect3DVertexBuffer9 *vertexBuffer;
	//IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};
//x file
class GameTest5 :public skn_d3d::GameMain
{

public:
	ID3DXMesh* mesh;
	skn_d3d::Terrain *terrain;
	std::vector<D3DMATERIAL9> materials;
	std::vector<IDirect3DTexture9 *> textures;
	static const int numSub;
	virtual bool setup() override;
	//IDirect3DVertexBuffer9 *vertexBuffer;
	//IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};
//terrain  particle
class GameTest6 :public skn_d3d::GameMain
{

public:
	skn_d3d::Terrain *terrain;
	skn_d3d::Camera   TheCamera;
	skn_d3d::Snow *snow;
	virtual bool setup() override;
	//IDirect3DVertexBuffer9 *vertexBuffer;
	//IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};

//pick
class GameTest7 :public skn_d3d::GameMain
{

public:
	ID3DXMesh* Teapot = 0;
	ID3DXMesh* Sphere = 0;
	skn_d3d::BoundingSphere BSphere;
	virtual bool setup() override;
	//IDirect3DVertexBuffer9 *vertexBuffer;
	//IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};
//vertex shader
class GameTest8 :public skn_d3d::GameMain
{
public:
	IDirect3DDevice9* device;
	ID3DXMesh* Teapot = 0;
	IDirect3DVertexShader9* VertexShader = 0;
	ID3DXConstantTable* ConstantTable = 0;
	D3DXHANDLE TransformViewProjHandle = 0;
	virtual bool setup() override;
	virtual void play(float timeDelta) override;
	bool initBlueShader();
	void updateBlueShader();
	bool initDiffuseShader();
	void updateDiffuseShader();
	bool initToonShader();
	void updateToonShader();
};
//pixel shader
class GameTest9 :public skn_d3d::GameMain
{
public:
	IDirect3DVertexBuffer9* vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	IDirect3DDevice9* device;
	IDirect3DPixelShader9* PixelShader = 0;
	ID3DXConstantTable* ConstantTable = 0;
	D3DXHANDLE TransformViewProjHandle = 0;
	virtual bool setup() override;
	virtual void play(float timeDelta) override;
};