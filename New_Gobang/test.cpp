#include "Gobang_Base.h"
#include "Gobang_Rules.h"
#include "Gobang_Steps.h"

int main()
{
	int tx, ty, x;
	char y;
	Gobang_Steps Go = Gobang_Steps();


	/*
	//minmaxSearch()测试

	MAN = WHITE;
	COM = BLACK;
	Go.Gobang::setBoard(7, H, BLACK);
	Go.Gobang::setBoard(5, H, BLACK);
	Go.Gobang::setBoard(5, G, BLACK);
	Go.Gobang::setBoard(6, E, WHITE);
	Go.Gobang::setBoard(6, F, WHITE);
	Go.Gobang::setBoard(6, G, WHITE);
	Go.Gobang::Print_Checkerboard();
	Go.minmaxSearch(3, tx, ty);  //大约半小时
	Go.Gobang::setBoard(tx, ty, COM);
	Go.Gobang::Print_Checkerboard();*/

	/*
	//PreJudge()测试

	COM = BLACK;
	Go.Gobang::setBoard(8, 3, WHITE);
	Go.Gobang::setBoard(9, E, BLACK);
	Go.Gobang::setBoard(10, F, BLACK);
	Go.Gobang::setBoard(11, G, BLACK);
	Go.Gobang::setBoard(12, H, BLACK);
	Go.Gobang::Print_Checkerboard();
	tx = 13; ty = I;
	cout << Go.PreJudge(tx, ty) << endl;
	Go.Gobang::setBoard(tx, ty, COM);
	Go.Gobang::Print_Checkerboard(); */

	/*
	//IsLegal()测试

	COM = BLACK;
	Go.Gobang::Print_Checkerboard();
	for (int i = 0; i < 7; i++)
	{
		cin >> x; cin >> y;
		Go.Gobang::setBoard(15 - x, y - 'A', BLACK);
		Go.Gobang::Print_Checkerboard();
	}
	if (Go.IsLegal(15 - x, y - 'A'))
		cout << "illegal" << endl;*/
	
	
	//各搜索算法测试
	MAN = WHITE;
	COM = BLACK;
	Go.Gobang::setBoard(7, H, BLACK);
	Go.Gobang::setBoard(5, H, BLACK);
	Go.Gobang::setBoard(5, G, BLACK);
	Go.Gobang::setBoard(6, E, WHITE);
	Go.Gobang::setBoard(6, F, WHITE);
	Go.Gobang::setBoard(6, G, WHITE); 
	//Go.Gobang::setBoard(0, 0, WHITE);
	//Go.Gobang::setBoard(6, H, BLACK);
	Go.Gobang::Print_Checkerboard();
	Go.NegaScoutSearch(tx, ty, 3, -INFINITY, +INFINITY, COM);//缩小搜索范围从1-11，耗时一个半
	Go.Gobang::setBoard(tx, ty, COM);
	Go.Gobang::Print_Checkerboard();

	Go.Gobang::Print_Checkerboard();
	Go.Opening();
	Go.ForthStep();
	Go.FifthStep();
	Go.Continue();
}

