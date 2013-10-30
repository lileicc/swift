/*
* Symbol.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include<string>
using std::string;

namespace swift {

class Symbol
{
	string value;
public:
	Symbol(string v="");
	virtual ~Symbol();

	const string& getValue();
};

}

#endif