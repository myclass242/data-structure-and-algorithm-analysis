#pragma once
#ifndef GCD_H_
#define GCD_H_
/*
* 利用如下公式计算最大公因数
* gcd(a,b) = 2gcd(a/2,b/2)  a,b 为偶数
* gcd(a,b) = gcd(a/2,b)  a为偶数
* gcd(a,b) = gcd(a,b/2) b为偶数
* gcd(a,b) = gcd((a+b)/2,(a-b)/2) a,b为奇数且a>=b
*/

int Gcd(int a, int b);
#endif