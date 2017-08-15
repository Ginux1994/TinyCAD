#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

// 定义模型的抽象类接口
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