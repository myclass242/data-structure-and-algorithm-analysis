#pragma once
#ifndef GCD_H_
#define GCD_H_
/*
* �������¹�ʽ�����������
* gcd(a,b) = 2gcd(a/2,b/2)  a,b Ϊż��
* gcd(a,b) = gcd(a/2,b)  aΪż��
* gcd(a,b) = gcd(a,b/2) bΪż��
* gcd(a,b) = gcd((a+b)/2,(a-b)/2) a,bΪ������a>=b
*/

int Gcd(int a, int b);
#endif