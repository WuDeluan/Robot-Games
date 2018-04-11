#include "Gobang_Base.h"
#include "Gobang_ManToMan.h"
#include "Gobang_ManToCom.h"

int main()
{
	ManToMan Gobang1 =  ManToMan();
	//Gobang1.Print_Menu1();
	ManToCom Gobang2 = ManToCom();
	Gobang2.Print_Menu2();
}
