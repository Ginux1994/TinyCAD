#include "stdafx.h"
#include "NxComponentTree.h"


CNxComponentTree::CNxComponentTree()
{
	m_pRoot = new SNxCTreeNode;
}


CNxComponentTree::~CNxComponentTree()
{
}

void CNxComponentTree::AddNextNode(SNxCTreeNode* pNext)
{
	ASSERT(pNext);
	if (m_pRoot->pData == NULL)
	{
		// 将该节点作为根节点
		m_pRoot->pData = pNext->pData;
	}
	else
	{
		m_pRoot->_pNext = pNext;
	}
}

void CNxComponentTree::AddChildNode(SNxCTreeNode* pChild)
{
	ASSERT(pChild);
	if (m_pRoot->pData == NULL)
	{
		// 将该节点作为根节点
		m_pRoot->pData = pChild->pData;
	}
	else
	{
		m_pRoot->_pChild = pChild;
	}
}

SNxCTreeNode* CNxComponentTree::FindNode(int nID)
{
	return NULL;
}