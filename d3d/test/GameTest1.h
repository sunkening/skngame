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