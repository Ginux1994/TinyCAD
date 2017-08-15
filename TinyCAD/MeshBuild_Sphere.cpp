#include "stdafx.h"
#include "MeshBuild_Sphere.h"
#include "MeshParam.h"

CMeshBuild_Sphere::CMeshBuild_Sphere()
{
	m_nID = -1;
	m_nType = MeshBuild_Sphere;
}


CMeshBuild_Sphere::~CMeshBuild_Sphere()
{
}

BOOL CMeshBuild_Sphere::CreateModule(void* pParameter)
{
	ASSERT(pParameter);
	m_pShpereParam = (STMeshBuild_Sphere*)pParameter;
	return TRUE;
}

BOOL CMeshBuild_Sphere::DeleteModule()
{
	return TRUE;
}