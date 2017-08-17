#pragma once
class CMeshBuild_Sphere
{
public:
	CMeshBuild_Sphere();
	~CMeshBuild_Sphere();

	void CreateSphere(IDirect3DDevice9* pDevice);
private:
	int m_nRings;
	int m_nSegments;

	float m_fRadius;

};

