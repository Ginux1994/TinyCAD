#ifndef DEFINES_H
#define DEFINES_H

#define UGPCOLOR_ARGB(a, r, g, b) ((unsigned long)((((a)&0xff)<<24)|\
									(((r)&0xff)<<16)|(((g)&0xff)<<8)|\
									((b)&0xff)))


#define STRAND_SAFE_RELEASE(p) if(p) p->Release(); p = NULL;

#undef ASSERT
#define ASSERT(x) if(!x) ::DebugBreak();

#define VERTEX_2D 0
#define VERTEX_3D 1

// 向量
struct SNxVEC3
{
	SNxVEC3(float x, float y, float z)
	{
		_x = x, _y = y, _z = z;
	}
	float _x;
	float _y;
	float _z;
};
struct SNxVertex
{
	SNxVertex()
	{
		_x = _y = _z = 0;
		_nx = _ny = _nz = 0;
		_u = _v = 0;
	}

	SNxVertex(float ix, float iy, float iz,
		float nx, float ny, float nz, 
		float iu, float iv)
	{
		_x = ix, _y = iy, _z = iz;

		_nx = nx, _ny = ny, _nz = nz;
		
		_u = iu, _v = iv;
	}

	// vertex结构中各个元素的顺序必须按照FVF各个代码定义的bit-order，即：
	// POSITION,NORMAL,PSIZE,DIFFUSE,SPECULAR,TEX0[,TEXn...]
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;
};
struct SNxVertex2D
{
	SNxVertex2D()
	{
		_x = 0.0f, _y = 0.0f, _z = 0.0f, _rhw = 0.0f;
		_color = 0;
		_u = 0.0f, _v = 0.0f;
	};
	SNxVertex2D(float x, float y, float z, 
		float rhw, UINT color, float u, float v)
	{
		_x = x, _y = y, _z = z;
		_rhw = rhw;
		_u = u, _v = v;
	}
	float _x, _y, _z, _rhw;
	unsigned long _color;
	float _u, _v;
};

struct STMeshBuild_Sphere
{
	STMeshBuild_Sphere(){};
	STMeshBuild_Sphere(float x, float y, float z, float Radius)
	{
		_x = x, _y = y, _z = z;
		_Radius = Radius;
	}
	float _x;
	float _y;
	float _z;
	float _Radius;
};

// Multi-sampling.
enum UGP_MS_TYPE
{
	UGP_MS_NONE,
	UGP_MS_SAMPLES_2,
	UGP_MS_SAMPLES_4,
	UGP_MS_SAMPLES_8,
	UGP_MS_SAMPLES_16
};
// Module type
enum MESH_TYPE
{
	MeshBuild_Sphere,
	MeshBuild_Cube,
	MeshBuild_Torus,
	MeshBuild_Cylinder
};

enum LIGHT_TYPE
{
	LIGHT_POINT,
	LIGHT_SPOT,
	LIGHT_DIRECTIONAL
};
#endif