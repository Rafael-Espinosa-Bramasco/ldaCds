#include <ldaCds_List.h>

ldaCds_List *ldaCds_CreateList(void *_liststate)
{
    ldaCds_List *newlist = malloc(sizeof(ldaCds_List));
    if(newlist == NULL) return NULL;
    newlist->firstelement = NULL;
    newlist->lastelement = NULL;
    newlist->liststate = _liststate;
    newlist->liststatus = ldaCds_StatusNoErrorDetected;
    return newlist;
}
ldaCds_ListNode *ldaCds_CreateListNode(void *_nodedata, void *_nodestate)
{
    ldaCds_ListNode *newnode = malloc(sizeof(ldaCds_ListNode));
    if(newnode == NULL) return NULL;
    newnode->nextnode = NULL;
    newnode->nodedata = _nodedata;
    newnode->nodestate = _nodestate;
    newnode->prevnode = NULL;
    return newnode;
}
bool ldaCds_ListHasState(ldaCds_List *_list)
{
    if(_list == NULL) return false;
    return _list->liststate != NULL;
}
bool ldaCds_ListNodeHasState(ldaCds_ListNode *_listnode)
{
    if(_listnode == NULL) return false;
    return _listnode->nodestate != NULL;
}
bool ldaCds_ListIsEmpty(ldaCds_List *_list)
{
    if(_list == NULL) return false;
    return _list->firstelement == NULL && _list->lastelement == NULL;
}

ldaCds_ListNode *ldaCds_ListPeekFirst(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    ldaCds_ListNode *node = _list->firstelement;
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    return node;
}
ldaCds_ListNode *ldaCds_ListPeekLast(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    ldaCds_ListNode *node = _list->lastelement;
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    return node;
}
ldaCds_ListNode *ldaCds_ListPeekIndex(ldaCds_List *_list, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    ldaCds_ListNode *node = _list->firstelement;
    for(size_t i = 0; i < _index && node != NULL; i++)
    {
        if(node->nextnode == NULL)
        {
            _list->liststatus = ldaCds_StatusIndexOutOfRange;
            return NULL;
        }
        node = node->nextnode;
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    return node;
}
ldaCds_ListNode *ldaCds_ListAddAtStart(ldaCds_List *_list, ldaCds_ListNode *_listnode, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    if(_listnode == NULL)
    {
        _list->liststatus = ldaCds_StatusNodeParameterIsNUll;
        return NULL;
    }
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->lastelement = _listnode;
    }else
    {
        _listnode->nextnode = _list->firstelement;
    }
    _list->firstelement = _listnode;
    if(_callbackLN != NULL)
    {
        _callbackLN(_listnode);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return _listnode;
}
ldaCds_ListNode *ldaCds_ListAddAtEnd(ldaCds_List *_list, ldaCds_ListNode *_listnode, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    if(_listnode == NULL)
    {
        _list->liststatus = ldaCds_StatusNodeParameterIsNUll;
        return NULL;
    }
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->firstelement = _listnode;
    }else
    {
        _listnode->prevnode = _list->lastelement;
    }
    _list->lastelement = _listnode;
    if(_callbackLN != NULL)
    {
        _callbackLN(_listnode);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return _listnode;
}
ldaCds_ListNode *ldaCds_ListAddAtIndex(ldaCds_List *_list, ldaCds_ListNode *_listnode, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    ldaCds_ListNode *node = _list->firstelement;
    for(size_t i = 0; i < _index && node != NULL; i++)
    {
        if(node->nextnode == NULL)
        {
            _list->liststatus = ldaCds_StatusIndexOutOfRange;
            return NULL;
        }
        node = node->nextnode;
    }
    if(node == NULL)
    {
        _list->firstelement = _listnode;
        _list->lastelement = _listnode;
    }else
    {
        if(node->nextnode == NULL && node->prevnode == NULL)
        {
            _listnode->nextnode = _list->firstelement;
            _list->firstelement = _listnode;
        }else if(node->nextnode == NULL && node->prevnode != NULL)
        {
            _listnode->prevnode = _list->lastelement;
            _list->lastelement = _listnode;
        }else if(node->nextnode != NULL && node->prevnode == NULL)
        {
            _listnode->nextnode = _list->firstelement;
            _list->firstelement = _listnode;
        }else
        {
            ldaCds_ListNode *pnode = node->prevnode;
            pnode->nextnode = _listnode;
            _listnode->prevnode = pnode;
            node->prevnode = _listnode;
            _listnode->nextnode = node;
        }
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(_listnode);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return _listnode;
}
ldaCds_ListNode *ldaCds_ListRemoveAtStart(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    ldaCds_ListNode *node = _list->firstelement;
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->liststatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return NULL;
    }
    if(_list->firstelement == _list->lastelement)
    {
        _list->firstelement = NULL;
        _list->lastelement = NULL;
    }else
    {
        _list->firstelement = node->nextnode;
        node->nextnode = NULL;
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return node;
}
ldaCds_ListNode *ldaCds_ListRemoveAtEnd(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    ldaCds_ListNode *node = _list->lastelement;
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->liststatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return NULL;
    }
    if(_list->firstelement == _list->lastelement)
    {
        _list->firstelement = NULL;
        _list->lastelement = NULL;
    }else
    {
        _list->lastelement = node->prevnode;
        node->prevnode = NULL;
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return node;
}
ldaCds_ListNode *ldaCds_ListRemoveAtIndex(ldaCds_List *_list, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return NULL;
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->liststatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return NULL;
    }
    ldaCds_ListNode *node = _list->firstelement;
    for(size_t i = 0; i < _index && node != NULL; i++)
    {
        if(node->nextnode == NULL)
        {
            _list->liststatus = ldaCds_StatusIndexOutOfRange;
            return NULL;
        }
        node = node->nextnode;
    }
    if(node == NULL)
    {
        _list->firstelement = NULL;
        _list->lastelement = NULL;
    }else
    {
        if(node->nextnode == NULL && node->prevnode == NULL)
        {
            _list->firstelement = NULL;
            _list->lastelement = NULL;
        }else if(node->nextnode == NULL && node->prevnode != NULL)
        {
            _list->lastelement = node->prevnode;
            node->prevnode = NULL;
        }else if(node->nextnode != NULL && node->prevnode == NULL)
        {
            _list->firstelement = node->nextnode;
            node->nextnode = NULL;
        }else
        {
            ldaCds_ListNode *pnode = node->prevnode;
            ldaCds_ListNode *nnode = node->nextnode;
            pnode->nextnode = nnode;
            nnode->prevnode = pnode;
            node->nextnode = NULL;
            node->prevnode = NULL;
        }
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return node;
}
bool ldaCds_ListRemoveDeleteAtStart(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return false;
    ldaCds_ListNode *node = _list->firstelement;
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->liststatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return false;
    }
    if(_list->firstelement == _list->lastelement)
    {
        _list->firstelement = NULL;
        _list->lastelement = NULL;
    }else
    {
        _list->firstelement = node->nextnode;
        node->nextnode = NULL;
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    free(node);
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return false;
}
bool ldaCds_ListRemoveDeleteAtEnd(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return false;
    ldaCds_ListNode *node = _list->lastelement;
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->liststatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return false;
    }
    if(_list->firstelement == _list->lastelement)
    {
        _list->firstelement = NULL;
        _list->lastelement = NULL;
    }else
    {
        _list->lastelement = node->prevnode;
        node->prevnode = NULL;
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    free(node);
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return true;
}
bool ldaCds_ListRemoveDeleteAtIndex(ldaCds_List *_list, size_t _index, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return false;
    if(ldaCds_ListIsEmpty(_list))
    {
        _list->liststatus = ldaCds_StatusStructureIsAlreadyEmpty;
        return false;
    }
    ldaCds_ListNode *node = _list->firstelement;
    for(size_t i = 0; i < _index && node != NULL; i++)
    {
        if(node->nextnode == NULL)
        {
            _list->liststatus = ldaCds_StatusIndexOutOfRange;
            return false;
        }
        node = node->nextnode;
    }
    if(node == NULL)
    {
        _list->firstelement = NULL;
        _list->lastelement = NULL;
    }else
    {
        if(node->nextnode == NULL && node->prevnode == NULL)
        {
            _list->firstelement = NULL;
            _list->lastelement = NULL;
        }else if(node->nextnode == NULL && node->prevnode != NULL)
        {
            _list->lastelement = node->prevnode;
            node->prevnode = NULL;
        }else if(node->nextnode != NULL && node->prevnode == NULL)
        {
            _list->firstelement = node->nextnode;
            node->nextnode = NULL;
        }else
        {
            ldaCds_ListNode *pnode = node->prevnode;
            ldaCds_ListNode *nnode = node->nextnode;
            pnode->nextnode = nnode;
            nnode->prevnode = pnode;
            node->nextnode = NULL;
            node->prevnode = NULL;
        }
    }
    if(_callbackLN != NULL)
    {
        _callbackLN(node);
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    free(node);
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return true;
}
bool ldaCds_ListClear(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return false;
    while(ldaCds_ListRemoveDeleteAtStart(_list,NULL,_callbackLN));
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    _list->liststatus = ldaCds_StatusNoErrorDetected;
    return true;
}
bool ldaCds_ListDelete(ldaCds_List *_list, LDACDS_CBF(L,List,l), LDACDS_CBF(LN,ListNode,ln))
{
    if(_list == NULL) return false;
    if(!ldaCds_ListClear(_list,NULL,_callbackLN))
    {
        _list->liststatus = ldaCds_StatusStructureCantBeCleared;
        return false;
    }
    if(_callbackL != NULL)
    {
        _callbackL(_list);
    }
    free(_list);
    return true;
}