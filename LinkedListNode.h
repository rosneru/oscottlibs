/* LinkedListNode.h                                                            */
/*------------------------------------------------------------------------*/
/* Klasse eines Listenverbindungselementes fuer eine doppelt verk. Liste  */
/* Uwe Rosner, 17549, 03/041/02                                           */
/* 11/2004                                                                */
/*------------------------------------------------------------------------*/
#ifndef OSCOTTLIBS_LINKEDLISTNODE
#define OSCOTTLIBS_LINKEDLISTNODE


class LinkedListNode
{
  friend class LinkedList;

public:
  LinkedListNode(void* pItemData,
                 LinkedListNode* pPrevListItem,
                 LinkedListNode* pNextListItem);  // Konstruktor

  virtual ~LinkedListNode();

private:
  LinkedListNode* m_pPrv;     // Pointer auf vorheriges Verbindungselement
  LinkedListNode* m_pNxt;     // Pointer auf naechstes Verbindungselement
  void* m_pData;              // Pointer auf die Daten
};


#endif
