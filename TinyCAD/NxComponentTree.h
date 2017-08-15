#pragma once
#include "ModuleInterface.h"

typedef struct SNxComponentTree
{
	IMoudle* pData;
	SNxComponentTree* _pNext;
	SNxComponentTree* _pChild;

	SNxComponentTree(){ pData = NULL, _pNext = NULL, _pChild = NULL; }

}SNxCTree, SNxCTreeNode;

class CNxComponentTree
{
public:
	CNxComponentTree();
	~CNxComponentTree();
	// 添加一个兄弟节点
	void AddNextNode(SNxCTreeNode* pNext);
	// 添加一个子节点
	void AddChildNode(SNxCTreeNode* pChild);
	// 查找节点
	SNxCTreeNode* FindNode(int nID);
	SNxCTreeNode* GetRoot()
	{
		return m_pRoot;
	}
private:
	SNxCTreeNode* m_pRoot;
};

