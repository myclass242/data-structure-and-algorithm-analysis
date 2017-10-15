#pragma once
#ifndef FORWARDLIST_H_
#define FORWARDLIST_H_
typedef struct node
{
    int item;
    struct node *next;
}Node;
typedef Node *Link;

void ForwardlistInit(Link *pLink);

void ForwardlistInsert(Link *pLink, int data);

int ForwardListTop(Link *pLink);

void ForwardlistPop(Link *pLink);

bool ForwardlistEmpty(Link *pLink);

void ForwardlistDestory(Link *pLink);

#endif
