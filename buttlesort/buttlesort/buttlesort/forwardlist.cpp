#include "forwardlist.h"
#include <assert.h>
#include <stdlib.h>

void ForwardlistInit(Link * pLink)
{
    *pLink = NULL;
}

void ForwardlistInsert(Link * pLink, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    assert(NULL != newNode);
    newNode->item = data;
    newNode->next = *pLink;
    *pLink = newNode;
}

int ForwardListTop(Link * pLink)
{
    assert(NULL != pLink);
    assert(NULL != *pLink);
    return (*pLink)->item;
}

void ForwardlistPop(Link * pLink)
{
    assert(NULL != pLink);
    assert(NULL != *pLink);
    Node *temp = *pLink;
    *pLink = (*pLink)->next;
    free(temp);
}

bool ForwardlistEmpty(Link * pLink)
{
    assert(NULL != pLink);
    return NULL == *pLink;
}

void ForwardlistDestory(Link * pLink)
{
    Node *temp = *pLink;
    while (*pLink)
    {
        temp = (*pLink)->next;
        free(*pLink);
        *pLink = temp;
    }
}
