#pragma once
class GameTest1 :public skn_d3d::GameMain
{

public:
	virtual bool setup() override;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};
//����
class GameTest2 :public skn_d3d::GameMain
{

public:
	virtual bool setup() override;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};
//������ں�
class GameTest3 :public skn_d3d::GameMain
{

public:
	virtual bool setup() override;
	IDirect3DVertexBuffer9 *vertexBuffer;
	IDirect3DIndexBuffer9* indexBuffer;
	virtual void play(float timeDelta) override;
};