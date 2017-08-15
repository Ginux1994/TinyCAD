#pragma once
#include "ModuleInterface.h"

class CMeshBuild_Sphere : public IMoudle
{
public:
	CMeshBuild_Sphere();
	~CMeshBuild_Sphere();

	virtual BOOL CreateModule(void* pParameter);
	virtual BOOL DeleteModule();

private:
	STMeshBuild_Sphere *m_pShpereParam;
};

