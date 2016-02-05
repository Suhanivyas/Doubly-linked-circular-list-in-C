#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "cs402.h"
#include "my402list.h"

int My402ListLength(My402List* list1)
{
    return list1->num_members;
}
int My402ListEmpty(My402List *list1)
{
    if(list1->num_members==0)
    return 1;
    else
        return 0;
}

int My402ListAppend(My402List *list1, void *val)
{
    My402ListElem *node = (My402ListElem*)calloc(1, sizeof(My402ListElem));
    if (My402ListEmpty(list1)==1)
    {
        node->obj=val;
        list1->anchor.next=node;
        list1->anchor.prev=node;
        node->next=&(list1->anchor);
        node->prev=&(list1->anchor);
        list1->num_members++;
        return 1;
    }
    else
    {
        node->obj=val;
        list1->anchor.prev->next=node;
        node->prev=list1->anchor.prev;
        node->next=&(list1->anchor);
        list1->anchor.prev=node;
        list1->num_members++;
        return 1;
    }
}
int My402ListPrepend(My402List* list1, void* val)
{
    My402ListElem *node = (My402ListElem*)calloc(1, sizeof(My402ListElem));
    if (My402ListEmpty(list1)==1)
    {
        node->obj=val;
        list1->anchor.next=node;
        list1->anchor.prev=node;
        node->next=&(list1->anchor);
        node->prev=&(list1->anchor);
        list1->num_members++;
        return 1;
    }
    else
    {
        node->obj=val;
        list1->anchor.next->prev=node;
        node->prev=&(list1->anchor);
        node->next=(list1->anchor.next);
        list1->anchor.next=node;
        list1->num_members++;
        return 1;
    }
}
void My402ListUnlink(My402List* list1, My402ListElem* node)
{
    node->prev->next=node->next;
    node->next->prev=node->prev;
    list1->num_members--;
    free(node);
}

void My402ListUnlinkAll(My402List* list1)
{
    My402ListElem *node=NULL;
    My402ListElem *mode=NULL;
    for(node=My402ListFirst(list1); node!= NULL;node=mode)
    {
        mode=My402ListNext(list1, node);
        node->prev->next=node->next;
        node->next->prev=node->prev;
        node->prev=NULL;
        node->next=NULL;
        list1->num_members--;
        free(node);
    }
}

int  My402ListInsertAfter(My402List *list1, void* val, My402ListElem* node)
{
    if (node==My402ListLast(list1))
    {
        int a;
        a=My402ListAppend(list1,val);
        return a;
    }
    else
    {
        My402ListElem *newnode = (My402ListElem*)calloc(1, sizeof(My402ListElem));
        newnode->obj=val;
        node->next->prev=newnode;
        newnode->next=node->next;
        newnode->prev=node;
        node->next=newnode;
        list1->num_members++;
        return 1;
    }
}
int My402ListInsertBefore(My402List* list1, void* val, My402ListElem* node)
{
    if (node==My402ListFirst(list1))
    {
        int a;
        a=My402ListPrepend(list1,val);
        return a;
    }
    else
    {
        My402ListElem *newnode = (My402ListElem*)calloc(1, sizeof(My402ListElem));
        newnode->obj=val;
        node->prev->next=newnode;
        newnode->next=node;
        newnode->prev=node->prev;
        node->prev=newnode;
        list1->num_members++;
        return 1;
    }
}
My402ListElem *My402ListFirst(My402List* list1)
{
    if(My402ListEmpty(list1)==1)
    return NULL;
    else
    {
        return list1->anchor.next;
    }
}

My402ListElem *My402ListLast(My402List* list1)
{
    if(My402ListEmpty(list1)==1)
    return NULL;
    else
    {
        return list1->anchor.prev;
    }
}

My402ListElem *My402ListNext(My402List* list1, My402ListElem* node)
{
    if(node==My402ListLast(list1))
    return NULL;
    else
    {
        return node->next;
    }
}
My402ListElem *My402ListPrev(My402List* list1, My402ListElem* node)
{
    if(node==My402ListFirst(list1))
    return NULL;
    else
        return node->prev;
}

My402ListElem *My402ListFind(My402List* list1, void* val)
{
    My402ListElem *node= NULL;
    for (node=My402ListFirst(list1);node!=NULL;node=My402ListNext(list1,node))
    {
        if (node->obj==val)
        {
            return node;
        }
    }
    return 0;
}

int My402ListInit(My402List *list1)
{
    list1->num_members=0;
    list1->anchor.obj=NULL;
    list1->anchor.next=&(list1->anchor);
    list1->anchor.prev=&(list1->anchor);
    return 1;
}
