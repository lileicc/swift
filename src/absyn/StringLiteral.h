/*
* StringLiteral.h
*
*  Created on: Oct 29, 2013
*      Author: yiwu
*/

#ifndef STRINGLITERAL_H_
#define STRINGLITERAL_H_

#include<string>
using std::string;

#include "Literal.h"

namespace swift {

class StringLiteral :
	public swift::Literal
{
	string value;
public:
	StringLiteral(int l, int c, string value);
	virtual ~StringLiteral();

	const string& getValue();
};

}

#endif