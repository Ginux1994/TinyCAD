#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

// ����ģ�͵ĳ�����ӿ�
class IMoudle
{
public:
	virtual BOOL CreateModule(void* pParameter) = 0;
	virtual BOOL DeleteModule() = 0;
	// ID
	int m_nID;
	MESH_TYPE m_nType;
};
#endif