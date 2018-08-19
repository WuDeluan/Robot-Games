#include "Gobang_Base.h"
#include "Gobang_Rules.h"
#include "Gobang_Steps.h"

int main()
{
	Gobang_Steps Go = Gobang_Steps();
	Go.Gobang::Print_Checkerboard();
	Go.Opening();
	Go.ForthStep();
	Go.FifthStep();
}
