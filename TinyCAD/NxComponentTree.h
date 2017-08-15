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
	// ���һ���ֵܽڵ�
	void AddNextNode(SNxCTreeNode* pNext);
	// ���һ���ӽڵ�
	void AddChildNode(SNxCTreeNode* pChild);
	// ���ҽڵ�
	SNxCTreeNode* FindNode(int nID);
	SNxCTreeNode* GetRoot()
	{
		return m_pRoot;
	}
private:
	SNxCTreeNode* m_pRoot;
};

