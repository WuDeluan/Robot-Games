#include "Gobang_Base.h"
#include "Gobang_Rules.h"
#include "Gobang_Steps.h"
#include <iostream>
using namespace std;

int main()
{
	int tx, ty, x;
	char y;
	Gobang_Steps Go = Gobang_Steps();

	//minmaxSearch()测试
	/*
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

	//PreJudge()测试
	/*
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

	//IsLegal()测试
	/*
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

	//zobrist测试
	/*
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
	Go.Gobang::setBoard(6, I, WHITE);
	Go.Gobang::setBoard(8, H, BLACK);
	int m = 0, i = 0;
	//int a[20][2] = { 9,G,9,I,7,G,8,J,10,H,8,I,8,G,7,H,9,J,6,I,10,I,8,K,8,L,5,F,4,E,7,I};
	int a[20][2] = { 9,H,8,F,9,G,9,F,8,I,11,F,10,F,8,G,6,I,7,I };
	while (m--)
	{
		x = a[i][0]; y = a[i][1]; i++;
		Go.Gobang::setBoard(15 - x, y, WHITE);
		x = a[i][0]; y = a[i][1]; i++;
		Go.Gobang::setBoard(15 - x, y, BLACK);
		
	}
	Go.Gobang::Print_Checkerboard();
	while (1)
	{
		while (true) {
			cout << "请白方落子：";
			cin >> x; cin >> y;
			if (Go.Gobang::_setBoard(15 - x, y - 'A', WHITE) == 0)
				if (Go.IsLegal(15 - x, y - 'A') == 0)
				{
					Go.Gobang::setBack();
					cout << "禁手" << endl;
				}
				else
					break;				
			else
				cout << "请选择正确的位置落子！" << endl;
		}
		Go.Gobang::Print_Checkerboard();
		tx = 15 - x; ty = y - 'A';
		if (Go.PreJudge(tx, ty) == 0)
		{
			Go.NegaScout_hash_history(4, -INFINITY, +INFINITY, COM);		
			Go.EmptyHashTable();
			//Go.Gobang::ResetHistoryTable();
		}
		Go.Gobang::_setBoard(best_move.x, best_move.y, BLACK);
		cout << "黑方落子： (" << 15 - best_move.x << " , " << char(best_move.y + 'A') << ")" << endl;
		Go.Gobang::Print_Checkerboard();
	}
	*/

	//各搜索算法测试
	/*
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
	Go.Search(4, -INFINITY, +INFINITY, COM);
 	//Go.PVS(4, -INFINITY, +INFINITY,  COM);//缩小搜索范围从1-11，耗时一个半
	Go.Gobang::setBoard(best_move.x, best_move.y, COM);
	Go.Gobang::Print_Checkerboard();
	*/

	Go.Gobang::Print_Checkerboard();
	Go.Opening();
	Go.ForthStep();
	Go.FifthStep();
	Go.Continue();
}

