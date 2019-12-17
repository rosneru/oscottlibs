#include "LinkedListNode.h"


LinkedListNode::LinkedListNode(void* pItemData, LinkedListNode* prevListItem, LinkedListNode* nextListItem)
  : m_pPrv(prevListItem),
    m_pNxt (nextListItem),
    m_pData(pItemData)
{

}

LinkedListNode::~ LinkedListNode()
{
//  delete m_pItem;
}
