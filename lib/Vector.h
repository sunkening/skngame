#pragma once
//œÚ¡øº∆À„
namespace skn
{
	struct Vector2D {
		union {
			struct {
				float x, y;
			};
			float v[2];
		};
		static const Vector2D ZERO;
	};
	struct Vector3D {
		union {
			struct {
				float x, y,z;
			};
			float v[3];
		};
		static const Vector3D ZERO;
	};


}