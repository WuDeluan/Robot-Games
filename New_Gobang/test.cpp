#include "Gobang_Base.h"
#include "Gobang_Rules.h"

int main()
{
	Gobang_Rules Go = Gobang_Rules();
	Go.Opening();
	Go.Print_Checkerboard();
	
}
