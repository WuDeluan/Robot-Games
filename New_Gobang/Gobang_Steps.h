#ifndef GOBANG_STEPS_H
#define GOBANG_STEPS_H

#include "Gobang_Rules.h"

#define MAN 100
#define COM -100

class Gobang_Steps : public Gobang_Rules {
private:
	int MAN, COM;
public:
	void Opening();
};

Gobang_Steps::Opening()
{

}
#endif 
