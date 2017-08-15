#ifndef DEFINES_H
#define DEFINES_H

#define UGPCOLOR_ARGB(a, r, g, b) ((unsigned long)((((a)&0xff)<<24)|\
									(((r)&0xff)<<16)|(((g)&0xff)<<8)|\
									((b)&0xff)))


#define STRAND_SAFE_RELEASE(p) if(p) p->Release(); p = NULL;

#undef ASSERT
#define ASSERT(x) if(!x) ::DebugBreak();

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
		x = y = z = 0;
		nx = ny = nz = 0;
		u = v = 0;
	}

	SNxVertex(float ix, float iy, float iz)
	{
		x = ix;
		y = iy;
		z = iz;

		u = v = 0;
		nx = ny = nz = 0;
	}

	// vertex结构中各个元素的顺序必须按照FVF各个代码定义的bit-order，即：
	// POSITION,NORMAL,PSIZE,DIFFUSE,SPECULAR,TEX0[,TEXn...]
	float x, y, z;
	float nx, ny, nz;
	float u, v;
};

struct STMeshBuild_Sphere
{
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