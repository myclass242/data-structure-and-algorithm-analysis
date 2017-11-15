#pragma once
#ifndef TEST_H_
#define TEST_H_

#include "tree.h"
#include "infix2postfix.h"
#include "expressiontree.h"


//测试普通树，节点由子节点和兄弟节点链表组成
void TestTree(void);

//测试中缀表达式计算
void TestInfix2Postfix(void);

//测试表达式树
void TestExpressionTree(void);

#endif
