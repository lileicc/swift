/*
* BlogProgram.h
*
*  Created on: Oct 30, 2013
*      Author: yiwu
*
*  Note :
*    This node appears only ONCE in the syntax tree
*
*/

#ifndef BLOGPROGRAM_H_
#define BLOGPROGRAM_H_

#include <vector>
using std::vector;

#include "ArrayExpr.h"
#include "BoolLiteral.h"
#include "DistinctDecl.h"
#include "DistrExpr.h"
#include "DoubleLiteral.h"
#include "FuncApp.h"
#include "FuncDecl.h"
#include "IfExpr.h"
#include "IntLiteral.h"
#include "MapExpr.h"
#include "NullLiteral.h"
#include "NumStDecl.h"
#include "NumStRef.h"
#include "ObsDecl.h"
#include "OpExpr.h"
#include "OriginDecl.h"
#include "QuantExpr.h"
#include "QueryDecl.h"
#include "SetExpr.h"
#include "StringLiteral.h"
#include "Symbol.h"
#include "TimeStampLiteral.h"
#include "TypDecl.h"
#include "VarDecl.h"
#include "VarRef.h"

namespace swift {

class BlogProgram :
	public swift::Absyn
{
	vector<Decl*> args;
public:
	BlogProgram(int l, int r);
	virtual ~BlogProgram();

	size_t size();
	void add(Decl* decl);
	Decl* get(int k);

	// For Debugging Use
	void print(FILE* file, int indent);
};

}

#endif