#pragma once

#include <string>
#include <iostream>

using namespace std;

class Bignum
{
public:
	bool flag;//0代表负数，1代表非负 
	string abs_num;
public:
	Bignum() :flag(1), abs_num("") {}
	void set_num(const string& data);
	void print()const;

};

extern Bignum operator +(Bignum& a, Bignum& b);
extern Bignum operator -(Bignum& a, Bignum& b);
extern Bignum operator *(Bignum& a, Bignum& b);
extern Bignum operator /(Bignum& a, Bignum& b);