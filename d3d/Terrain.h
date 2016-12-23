#pragma once
namespace skn_d3d {
	struct TerrainVertex {
		TerrainVertex() {}
		TerrainVertex(float x, float y, float z, float u, float v)
		{
			_x = x;  _y = y;	_z = z;
			_u = u;
			_v = v;
		}

		float _x, _y, _z;
		float _u, _v;
		static const DWORD FVF;
	};

	class Terrain {
	public:
		Terrain(IDirect3DDevice9 *device, std::string heightmapFilename,
			int numVersPerRow, int numVersPerCol, int cellSpacing, float heightScale);
		std::vector<int> _heightMap;
		int _numVertices;
		int _numVersPreRow;
		int _numVersPerCol;
		int _cellSpacing;
		int _numCellsPerRow;
		int _numCellsPerCol;
		float _heithtScale;
		int _numTriangles;
		int _xlength;
		int _zlength;
		IDirect3DTexture9 * _tex;
		bool readRawFile(std::string fileName);
		int getHeightmapEntry(int row, int col);
		float getHeight(float x,float z);
		void setHeightmapEntry(int row, int col, int height);
		bool draw(float x,float y,float z,bool drawLine);
		float computeShade(int cellRow,int cellCol,D3DXVECTOR3* directionToLight);
		bool lightTerrain(D3DXVECTOR3 * directionToLight);
		bool loadTexture(TSTRING filename);
	private :
		bool buideVertex();
		bool buideIndex();
		IDirect3DDevice9* _device;
		IDirect3DVertexBuffer9 *_vertexBuffer;
		IDirect3DIndexBuffer9 * _indexBuffer;

	};
}