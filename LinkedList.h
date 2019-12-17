/* LinkedList.h                                                      */
/*-------------------------------------------------------------------*/
/* Class of a linked template list                                   */
/*                                                                   */
/* Uwe Rosner                                                        */
/* Created 11/2004, Updated 09/2018                                  */
/*-------------------------------------------------------------------*/

#ifndef OSCOTTLIBS_LINKEDLIST
#define OSCOTTLIBS_LINKEDLIST

#include <stdlib.h>
#include "LinkedListNode.h"

class LinkedList
{
  LinkedListNode* m_pFirst;
  LinkedListNode* m_pActual;
  LinkedListNode* m_pLast;

public:
  LinkedList(void);
  ~LinkedList(void);

  bool InsertHead(void* pItemIns);
  bool InsertTail(void* pItemIns);
  bool InsertBefore(void* pItemIns);
  bool InsertBehind(void* pItemIns);
  bool AddItemToList(void* pItemIns,
                     int(*pCompareFunc) (void* pItemList, void* pItemAdd));

  bool RemoveItem(void);

  void* GetFirst(void);
  void* GetLast(void);
  void* GetNext(void);
  void* GetPrev(void);
  void* GetSelected(void);

  void* GetIndexed(size_t id);

  void* searchList(void* pItemSearch,
                   int(*pCompareFunc) (void* pItemList, void* pItemFind));

  size_t Size() const;
  size_t Index() const;

protected:
  virtual LinkedListNode* allocListNode(void* pItem,
                                        LinkedListNode* pPrev,
                                        LinkedListNode* pNext);

  virtual void freeListNode(LinkedListNode* pNode);

private:
  size_t m_Size;
  size_t m_Index;
};

#endif
