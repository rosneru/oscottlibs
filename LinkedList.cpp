#include <stdlib.h>
#include "LinkedList.h"


LinkedList::LinkedList()
  : m_pFirst(NULL),
    m_pActual(NULL),
    m_pLast(NULL),
    m_Size(0),
    m_Index(0)
{

}

LinkedList::~LinkedList(void)
{
  while (RemoveItem() == true);
}

bool LinkedList::RemoveItem()
{
  LinkedListNode* pItemToRemove;
  pItemToRemove = m_pActual;

  if (pItemToRemove == NULL)
  {
    return false;
  }

  if(pItemToRemove->m_pPrv != NULL && pItemToRemove->m_pNxt != NULL)
  {
    // item has ancestor and successor
    m_pActual->m_pPrv->m_pNxt = m_pActual->m_pNxt;
    m_pActual->m_pNxt->m_pPrv = m_pActual->m_pPrv;
    m_pActual = m_pActual->m_pNxt;

    m_Size--;
  }
  else if(pItemToRemove->m_pPrv == NULL && pItemToRemove->m_pNxt != NULL)
  {
    // item has only successor; is first
    m_pFirst = m_pActual->m_pNxt;
    m_pFirst->m_pPrv = NULL;
    m_pActual = m_pFirst;

    m_Size--;
  }
  else if(pItemToRemove->m_pPrv != NULL && pItemToRemove->m_pNxt == NULL)
  {
    // item has only ancestor; is last
    m_pLast = m_pActual->m_pPrv;
    m_pLast->m_pNxt = NULL;
    m_pActual = m_pLast;

    m_Size--;
    m_Index--;
  }
  else
  {
    // item is last remaining item in list
    m_pFirst = m_pLast = m_pActual = NULL;
    m_Size = m_Index = 0;
  }

  freeListNode(pItemToRemove);
  return true;
}


void* LinkedList::GetFirst(void)
{
  if (m_pFirst == NULL)
  {
    return NULL;
  }

  m_Index = 0;
  m_pActual = m_pFirst;
  return m_pActual->m_pData;
}

void* LinkedList::GetLast(void)
{
  if (m_pLast == NULL)
  {
    return NULL;
  }

  m_Index = m_Size-1;
  m_pActual = m_pLast;
  return m_pActual->m_pData;
}

void* LinkedList::GetNext(void)
{
  if((m_pActual == NULL) || (m_pActual->m_pNxt == NULL))
  {
    return NULL;
  }

  m_Index++;
  m_pActual = m_pActual->m_pNxt;
  return m_pActual->m_pData;
}

void* LinkedList::GetPrev(void)
{
  if((m_pActual == NULL) || (m_pActual->m_pPrv == NULL))
  {
    return NULL;
  }

  m_Index--;
  m_pActual = m_pActual->m_pPrv;
  return m_pActual->m_pData;

  return NULL;
}

void* LinkedList::GetSelected(void)
{
  if (m_pActual == NULL)
  {
    return NULL;
  }

  return m_pActual->m_pData;
}

void* LinkedList::GetIndexed(size_t id)
{
  if(m_Size == 0)
  {
    return NULL;
  }

  if(id > (m_Size - 1))
  {
    return NULL;
  }

  int delta = id - m_Index;
  if(delta < 0)
  {
    while(m_Index > id)
    {
      GetPrev();
    }

    return m_pActual->m_pData;
  }
  else if(delta > 0)
  {
    while(m_Index < id)
    {
      GetNext();
    }

    return m_pActual->m_pData;
  }
  else
  {
    return m_pActual->m_pData;
  }
}



bool LinkedList::InsertHead(void* pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if (m_pFirst == NULL)
  {
    if ((m_pFirst = allocListNode(pItemIns, NULL, NULL)) == NULL)
    {
      return false;
    }

    m_pLast = m_pActual = m_pFirst;
    m_Size = 1;
    m_Index = 0;
  }
  else
  {
    if ((pInserted = allocListNode(pItemIns, NULL, m_pFirst)) == NULL)
    {
      return false;
    }

    m_pFirst->m_pPrv = pInserted;
    m_pFirst = m_pActual = pInserted;
    m_Size++;
    m_Index = 0;
  }

  return true;
}


bool LinkedList::InsertTail(void* pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if (m_pLast == NULL)
  {
    return InsertHead(pItemIns);
  }
  else
  {
    if ((pInserted = allocListNode(pItemIns, m_pLast, NULL)) == NULL)
    {
      return false;
    }

    m_pLast->m_pNxt = pInserted;
    m_pLast = m_pActual = pInserted;
    m_Size++;
    m_Index = m_Size-1;
  }

  return true;
}


bool LinkedList::InsertBefore(void* pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if ((m_pActual == NULL) || (m_pActual == m_pFirst))
  {
    return InsertHead(pItemIns);
  }

  if ((pInserted = allocListNode(pItemIns, m_pActual->m_pPrv, m_pActual)) == NULL)
  {
    return false;
  }

  m_pActual->m_pPrv->m_pNxt = pInserted;
  m_pActual->m_pPrv = pInserted;
  m_pActual = pInserted;

  m_Size++;
  return true;
}


bool LinkedList::InsertBehind(void* pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if ((m_pActual == NULL) || (m_pActual == m_pLast))
  {
    return InsertTail(pItemIns);
  }

  if ((pInserted = allocListNode(pItemIns, m_pActual, m_pActual->m_pNxt)) == NULL)
  {
    return false;
  }

  m_pActual->m_pNxt->m_pPrv = pInserted;
  m_pActual->m_pNxt = pInserted;
  m_pActual = pInserted;

  m_Size++;
  m_Index++;
  return true;
}


bool LinkedList::AddItemToList(void* pItemIns,
                               int(*pCompareFunc) (void* pItemList, void* pItemAdd))
{
  if (GetFirst())        // Liste enthaelt schon Element(e)
  {
    do
    {
      if (pCompareFunc(pItemIns, m_pActual->m_pData) > 0)
      {
        if (GetNext() == NULL)
        {
          return InsertTail(pItemIns);
        }
      }
      else
      {
        return InsertBefore(pItemIns);
      }
    }
    while (1);
  }
  else             // Liste enthaelt noch kein Element
  {
    return InsertHead(pItemIns);
  }
}


void* LinkedList::searchList(void* pItemSearch,
                             int(*pCompareFunc) (void* pItemList, void* pItemFind))
{
  if (GetFirst() != NULL)
  {
    do
    {
      if (pCompareFunc(pItemSearch, m_pActual->m_pData) == 0)
      {
        return m_pActual->m_pData;
      }
    }
    while (GetNext() != NULL);

    return NULL;
  }
  return NULL;
}

size_t LinkedList::Size() const
{
  return m_Size;
}

size_t LinkedList::Index() const
{
  return m_Index;
}


LinkedListNode* LinkedList::allocListNode(void* pItem,
                                          LinkedListNode* pPrev,
                                          LinkedListNode* pNext)
{
  LinkedListNode* pNode = new LinkedListNode(pItem, pPrev, pNext);
  return pNode;
}

void LinkedList::freeListNode(LinkedListNode* pNode)
{
  delete pNode;
}
