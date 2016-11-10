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
//terrain
class GameTest6 :public skn_d3d::GameMain
{

public:
	skn_d3d::Terrain *terrain;
	 
	virtual bool setup() override;
	//IDirect3DVertexBuffer9 *vertexBuffer;
	//IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};

//terrain
class GameTest7 :public skn_d3d::GameMain
{

public:
	skn_d3d::Terrain *terrain;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	virtual bool setup() override;
	//IDirect3DVertexBuffer9 *vertexBuffer;
	//IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};