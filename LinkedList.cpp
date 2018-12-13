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

LinkedList::~ LinkedList(void)
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
    m_Size = m_Index = NULL;
  }

  delete pItemToRemove;
  return true;
}


bool LinkedList::InsertHead(void* p_pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if (m_pFirst == NULL)
  {
    if ((m_pFirst = new LinkedListNode(p_pItemIns, NULL, NULL)) == NULL)
    {
      return false;
    }

    m_pLast = m_pActual = m_pFirst;
    m_Size = 1;
    m_Index = 0;
  }
  else
  {
    if ((pInserted = new LinkedListNode(p_pItemIns, NULL, m_pFirst)) == NULL)
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


bool LinkedList::InsertTail(void* p_pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if (m_pLast == NULL)
  {
    return InsertHead(p_pItemIns);
  }
  else
  {
    if ((pInserted = new LinkedListNode(p_pItemIns, m_pLast, NULL)) == NULL)
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


bool LinkedList::InsertBefore(void* p_pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if ((m_pActual == NULL) || (m_pActual == m_pFirst))
  {
    return InsertHead(p_pItemIns);
  }

  if ((pInserted = new LinkedListNode(p_pItemIns, m_pActual->m_pPrv, m_pActual)) == NULL)
  {
    return false;
  }

  m_pActual->m_pPrv->m_pNxt = pInserted;
  m_pActual->m_pPrv = pInserted;
  m_pActual = pInserted;

  m_Size++;
  return true;
}


bool LinkedList::InsertBehind(void* p_pItemIns)
{
  LinkedListNode* pInserted = NULL;

  if ((m_pActual == NULL) || (m_pActual == m_pLast))
  {
    return InsertTail(p_pItemIns);
  }

  if ((pInserted = new LinkedListNode(p_pItemIns, m_pActual, m_pActual->m_pNxt)) == NULL)
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


bool LinkedList::AddItemToList(void* p_pItemIns, int(*fcmp) (void* p_ItList, void* p_ItNew))
{
  if (GetFirst())        // Liste enthaelt schon Element(e)
  {
    do
    {
      if (fcmp(p_pItemIns, m_pActual->m_pData) > 0)
      {
        if (GetNext() == NULL)
        {
          return InsertTail(p_pItemIns);
        }
      }
      else
      {
        return InsertBefore(p_pItemIns);
      }
    }
    while (1);
  }
  else             // Liste enthaelt noch kein Element
  {
    return InsertHead(p_pItemIns);
  }
}


void* LinkedList::searchList(void* p_pItemSearch, int(fcmp) (void* pItList, void* pItNew))
{
  if (GetFirst() != NULL)
  {
    do
    {
      if (fcmp(p_pItemSearch, m_pActual->m_pData) == 0)
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

void* LinkedList::GetIndexed(size_t p_Id)
{
  if(m_Size == 0)
  {
    return NULL;
  }

  if(p_Id > (m_Size - 1))
  {
    return NULL;
  }

  int delta = p_Id - m_Index;
  if(delta < 0)
  {
    while(m_Index > p_Id)
    {
      GetPrev();
    }

    return m_pActual->m_pData;
  }
  else if(delta > 0)
  {
    while(m_Index < p_Id)
    {
      GetNext();
    }

    return m_pActual->m_pData;
  }
  else
  {
    return m_pActual->m_pData;
  }


//  size_t currIdx = 0;
//  void* pItem = GetFirst();
//  while (currIdx != p_Id)
//  {
//    currIdx++;
//    pItem = GetNext();
//    if(pItem == NULL)
//    {
//      return pItem;
//    }
//  }

//  return pItem;
}
