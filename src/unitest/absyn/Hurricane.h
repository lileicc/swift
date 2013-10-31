#ifndef HURRICANE_H_
#define HURRICANE_H_

#include "../../absyn/BlogProgram.h"
using namespace swift;

namespace unitest_absyn {

class Hurricane {
	Absyn* root;
	void build();
public:
	Hurricane();
	~Hurricane();
	void test(FILE *file);
};

}

#endif