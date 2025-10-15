#ifndef LDACDS_LIST_H
#define LDACDS_LIST_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#include <ldaCds.h>

typedef struct __ldacds_listnode__
{
    void *nodedata;
    void *nodestate;
    struct __ldacds_listnode__ *prevnode;
    struct __ldacds_listnode__ *nextnode;
}ldaCds_ListNode;
typedef struct
{
    void *liststate;
    ldaCds_StatusCode liststatus;
    ldaCds_ListNode *firstelement;
    ldaCds_ListNode *lastelement;
}ldaCds_List;

ldaCds_List *ldaCds_CreateList(void *_liststate);
ldaCds_ListNode *ldaCds_CreateListNode(void *_nodedata, void *_nodestate);
bool ldaCds_ListHasState(ldaCds_List *_list);
bool ldaCds_ListNodeHasState(ldaCds_ListNode *_listnode);
bool ldaCds_ListIsEmpty(ldaCds_List *_list);

ldaCds_ListNode *ldaCds_ListPeekFirst(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListPeekLast(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListPeekIndex(ldaCds_List *_list, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListAddAtStart(ldaCds_List *_list, ldaCds_ListNode *_listnode, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListAddAtEnd(ldaCds_List *_list, ldaCds_ListNode *_listnode, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListAddAtIndex(ldaCds_List *_list, ldaCds_ListNode *_listnode, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListRemoveAtStart(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListRemoveAtEnd(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
ldaCds_ListNode *ldaCds_ListRemoveAtIndex(ldaCds_List *_list, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
bool ldaCds_ListRemoveDeleteAtStart(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
bool ldaCds_ListRemoveDeleteAtEnd(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
bool ldaCds_ListRemoveDeleteAtIndex(ldaCds_List *_list, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
bool ldaCds_ListClear(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));
bool ldaCds_ListDelete(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln));

#endif /* LDACDS_LIST_H */
