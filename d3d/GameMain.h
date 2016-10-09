#pragma once
namespace skn_d3d 
{
	class GameMain {
	public:
		GameMain();
		static int EnterMsgLoop(GameMain *game);
		
		void setD3DUtil(D3DUtil *d3dUtil) {
			this->d3dUtil = d3dUtil;
		}
		virtual bool setup();
		virtual void play(float timeDelta);
	protected:
		D3DUtil *d3dUtil;

	};


}
