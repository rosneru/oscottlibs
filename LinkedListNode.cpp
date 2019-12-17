#include "LinkedListNode.h"


LinkedListNode::LinkedListNode(void* pItemData,
                               LinkedListNode* pPrevListItem,
                               LinkedListNode* pNextListItem)
  : m_pPrv(pPrevListItem),
    m_pNxt (pNextListItem),
    m_pData(pItemData)
{

}

LinkedListNode::~ LinkedListNode()
{

}
