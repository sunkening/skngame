#pragma once
namespace skn_d3d 
{
	class GameMain {
	public:
		
		 void play(float timeDelta);
		void setD3DUtil(D3DUtil *d3dUtil) {
			this->d3dUtil = d3dUtil;
			this->d3dUtil->display = (void(  *)(float))play;
		}
	private:
		D3DUtil *d3dUtil;
	};


}
