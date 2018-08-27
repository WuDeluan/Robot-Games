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
	Go.minmaxSearch(3);  //大约半小时
	Go.Gobang::setBoard(X, Y, COM);
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

	/*
	//zobrist测试
	Go.Gobang::Print_Checkerboard();cout << ZobristKey << endl;
	Go.Gobang::setBoard(7, H, BLACK);
	Go.Gobang::Print_Checkerboard(); cout << ZobristKey << endl;
	Go.Gobang::setBoard(6, F, WHITE);
	Go.Gobang::Print_Checkerboard(); cout << ZobristKey << endl;
	Go.Gobang::setEmpty(7, H);
	Go.Gobang::Print_Checkerboard(); cout << ZobristKey << endl;
	Go.Gobang::setBoard(7, H, BLACK);Go.Gobang::Print_Checkerboard(); 
	cout << ZobristKey << endl;
	Go.Gobang::setBoard(6, G, WHITE);
	Go.Gobang::Print_Checkerboard(); cout << ZobristKey << endl;*/

	/*
	COM = BLACK; MAN = WHITE;
	Go.Gobang::setBoard(7, H, BLACK);
	Go.Gobang::setBoard(6, H, WHITE);
	Go.Gobang::setBoard(9, G, BLACK);
	Go.Gobang::Print_Checkerboard();
	while (1)
	{
		while (true) {
			cout << "请白方落子：";
			cin >> x; cin >> y;
			if (Go.Gobang::setBoard(15 - x, y - 'A', WHITE) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Go.Gobang::Print_Checkerboard();
		if (Go.Gobang::IsWin(15 - x, y - 'A') == 0)
			cout << "白方获胜!" << endl;
		tx = 15 - x; ty = y - 'A';

		if (Go.PreJudge(tx, ty) != 0)
		{
			Go.Gobang::setBoard(tx, ty, BLACK);
			Go.Gobang::Print_Checkerboard();
		}

		Go.NegaScoutSearch(3, -INFINITY, +INFINITY, COM);
		Go.Gobang::setBoard(X, Y, BLACK);
		cout << "黑方落子： (" << 15 - X << " , " << char(Y + 'A') << ")" << endl;
		Go.Gobang::Print_Checkerboard();
		if (Go.Gobang::IsWin(15 - X, Y - 'A') == 0)
			cout << "黑方获胜!" << endl;
	}*/

	
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
	Go.NegaScoutSearch(4, -INFINITY, +INFINITY, COM);
	//Go.NegaScoutSearch(3, -INFINITY, +INFINITY, COM);//缩小搜索范围从1-11，耗时一个半
	Go.Gobang::setBoard(X, Y, COM);
	Go.Gobang::Print_Checkerboard();


	Go.Gobang::Print_Checkerboard();
	Go.Opening();
	Go.ForthStep();
	Go.FifthStep();
	Go.Continue();
}

