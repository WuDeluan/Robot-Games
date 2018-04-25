#ifndef GOBANG_MANTOCOM_H
#define GOBANG_MANTOCOM_H

#include "Gobang_ManToMan.h"
#include <stack>

#define random(a,b) (rand()%(b-a+1)+a)
#define INIFITY 100000

class ManToCom : public ManToMan
{
public:
	ManToCom();
	int MAN, COM;
	int Eval(int x, int y); //估值函数
	int Function(int len, string side1, string side2); //棋型判断
	int minmaxSearch(int depth, int &x, int &y); //极大极小值判断
	int MaxSearch(int depth, int x, int y);
	int MinSearch(int depth, int x, int y);
	void FirstStep(int who_first);
	void SecondStep(Step step[]);
	void ThirdStep(Step step[]);
	int WhetherChange(Step step[]);
	void ForthStep(Step step[]);
	void Print_Menu2(); //打印人机对弈界面
};

ManToCom::ManToCom()
{
	Init_Board();
}

int ManToCom::Eval(int x, int y)
{
	int i, j, tx, ty, len;
	int Side = getBoard(x, y);
	string side1, side2;
	int bestValue = -1;
	for (i = 0; i < 4; i++)
	{
		tx = x; ty = y;
		len = 0;
		side1.clear(); side2.clear();
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)
		{
			tx -= Direct[i][0];
			ty -= Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx -= Direct[i][0], ty -= Direct[i][1]) {
			if (getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side1 += '#';
			else if (getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
				side1 += '0';
			else
				side1 += '1';
		}
		tx += Direct[i][0] * 4;
		ty += Direct[i][1] * 4;
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)
		{
			len++;
			tx += Direct[i][0];
			ty += Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx += Direct[i][0], ty += Direct[i][1]) {
			if (getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side2 += '#';
			else if (getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
				side2 += '0';
			else
				side2 += '1';
		}
		int value = Function(len, side1, side2);
		if (value > bestValue)
			bestValue = value;
	}
	return bestValue;
}

int ManToCom::Function(int len, string side1, string side2)
{
	int Value = 0;
	if (len >= 5)
	{
		//cout << "五连" << endl; 
		Value += 100000;
	}
	else if (len == 4)
	{
		if (side1[0] == '#' && side2[0] == '#')
		{
			//cout << "活四" << endl;
			Value += 10000;
		}
		else if (side1[0] == '1' && side2[0] == '#' || side1[0] == '#' && side2[0] == '1')
		{
			//cout << "冲四" << endl;
			Value += 5000;
		}
		else if (side1[0] == '#' && side2.compare(0, 2, "#0") == 0 || side1.compare(0, 2, "#0") == 0 && side2[0] == '#')
		{
			//cout << "冲四" << endl; 
			Value += 5000;
		}
		else if (side1[0] == '1' && side2[0] == '1')
		{
			//cout << "死四" << endl;
			Value += 1000;
		}
	}
	else if (len == 3)
	{
		if (side1[0] == '1' && side2.compare(0, 2, "#0") == 0 || side1.compare(0, 2, "#0") == 0 && side2[0] == '1')
		{
			//cout << "冲四" << endl;
			Value += 5000;
		}
		else if (side1.compare(0, 2, "##") == 0 && side2.compare(0, 2, "##") == 0)
		{
			//cout << "连活三" << endl;
			Value += 1000;
		}
		else if (side1[0] == '1' && side2.compare(0, 2, "##") == 0 || side1.compare(0, 2, "##") == 0 && side2[0] == '1')
		{
			//cout << "眠三" << endl;
			Value += 500;
		}
		else if (side1.compare(0, 2, "#1") == 0 && side2.compare(0, 2, "#1") == 0)
		{
			//cout << "眠三" << endl; 
			Value += 500;
		}
		else if (side1[0] == '1' && side2[0] == '1')
		{
			//cout << "死三" << endl; 
			Value += 100;
		}
	}
	else if (len == 2)
	{
		if (side1 == "#00" || side2 == "#00")
		{
			//cout << "冲四" << endl;
			Value += 5000;
		}
		else if (side1[0] == '#' && side2 == "#0#" || side1 == "#0#" && side2[0] == '#')
		{
			//cout << "跳活三" << endl;
			Value += 1000;
		}
		else if (side1[0] == '1' && side2 == "#1#" || side1 == "#1#" && side2[0] == '1')
		{
			//cout << "眠三" << endl;
			Value += 500;
		}
		else if (side1[0] == '#' && side2 == "10#" || side1 == "10#" && side2[0] == '#')
		{
			//cout << "眠三" << endl;
			Value += 500;
		}
		else if (side1 == "##0" || side2 == "##0")
		{
			//cout << "眠三" << endl;
			Value += 500;
		}
		//其他情况待补充
		else
			Value += 100;
	}
	return Value;
}

/*int ManToCom::Neighbor(int x, int y, int(*neighbor)[5])
{
	int i, j;
	for (i = x - 2; i <= x + 2; i++)
		for (j = y - 2; j <= y + 2; j++)
			if (i >= 0 && i < 15 && j >= 0 && j < 15)
				neighbor[i - x + 2][j - y + 2] = getBoard(i, j);
			else
				neighbor[i - x + 2][j - y + 2] = OVERSIZE;

	return 0;
}
*/

int ManToCom::minmaxSearch(int depth, int &tx, int &ty)
{
	stack<int> bestMoveX, bestMoveY;
	int x, y;
	int bestValue = -INIFITY;
	if (depth == 0)
		return Eval(tx, ty);
	else
	{
		for (x = tx - 4; x <= tx + 4; x++)
		{
			for (y = ty - 4; y <= ty + 4; y++)
			{
				if (x >= 0 && x < 15 && y >= 0 && y < 15 && getBoard(x, y) == EMPTY)
				{
					setBoard(x, y, COM); //Print_Checkerboard();
					if (Eval(x, y) == +INIFITY)
					{
						bestMoveX.push(x);
						bestMoveY.push(y);
						setEmpty(x, y);// Print_Checkerboard();
						break;
					}
					int value = MinSearch(depth - 1, x, y);
					//cout << value << endl;
					if (value > bestValue)
					{
						bestValue = value;
						bestMoveX.push(x);
						bestMoveY.push(y);

					}
					else if (value == bestValue)
					{
						bestMoveX.push(x);
						bestMoveY.push(y);
					}
					setEmpty(x, y);// Print_Checkerboard();
				}
			}
		}
	}
	tx = bestMoveX.top();
	ty = bestMoveY.top();
}

int ManToCom::MaxSearch(int depth, int tx, int ty)
{
	int bestValue = -INIFITY, x, y;
	if (depth == 0)
		return Eval(tx, ty);
	else
	{
		int value;
		for (x = tx - 4; x <= tx + 4; x++)
		{
			for (y = ty - 4; y <= ty + 4; y++)
			{
				if (x >= 0 && x < 15 && y >= 0 && y < 15 && getBoard(x, y) == EMPTY)
				{
					setBoard(x, y, COM); //Print_Checkerboard();
					value = MinSearch(depth - 1, x, y);
					cout << value << endl;
					if (value > bestValue)
						bestValue = value;
					setEmpty(x, y); //Print_Checkerboard();
				}
			}
		}
	}
	//cout <<"MAX   "<< bestValue << endl;
	return bestValue;
}

int ManToCom::MinSearch(int depth, int tx, int ty)
{
	int bestValue = INFINITY, x, y;
	if (depth == 0)
		return Eval(tx, ty);
	else
	{
		int value;
		for (x = tx - 4; x <= tx + 4; x++)
		{
			for (y = ty - 4; y <= ty + 4; y++)
			{
				if (x >= 0 && x < 15 && y >= 0 && y < 15 && getBoard(x, y) == EMPTY)
				{
					setBoard(x, y, MAN); //Print_Checkerboard();
					value = MaxSearch(depth - 1, x, y);
					//cout << value << endl;
					if (value < bestValue)
						bestValue = value;
					setEmpty(x, y); //Print_Checkerboard();
				}
			}
		}
	}
	//cout << "MIN   " << bestValue << endl;
	return bestValue;
}

void ManToCom::FirstStep(int who_first)
{
	int x;
	char y;

	//人先手
	if (who_first == 1)
	{
		MAN = BLACK;
		COM = WHITE;
		while (true) {
			cout << "请落子：";
			cin >> x; x -= 1;
			cin >> y; y -= 'A';
			if (setBoard(x, y, MAN) == 0 && x == 7 && y == 7) //是否下在中心
				break;
			else
				cout << "请选择正确的位置落子！" << endl;
		}
		Print_Checkerboard();
	}
	//电脑先手
	else if (who_first == 2)
	{
		COM = BLACK;
		MAN = WHITE;
		setBoard(7, 7, COM); //下在中心
		Print_Checkerboard();
	}
}

void ManToCom::SecondStep(Step step[])
{
	int x;
	char y;

	//人先手
	if (MAN == WHITE)
	{
		while (true) {
			cout << "请落子：";
			cin >> x; x -= 1;
			cin >> y; y -= 'A';
			if (setBoard(x, y, MAN) == 0 && x >= 6 && x <= 8 && y >= 6 && y <= 8) //是否下在3*3范围内
				break;
			else
				cout << "请选择正确的位置落子！" << endl;
		}
		step[0].x = x;
		step[0].y = y;
		Print_Checkerboard();
	}
	//电脑先手
	else if (COM == WHITE)
	{
		int m, n;
		srand((unsigned)time(NULL));
		do {
			m = random(6, 8);
			n = random(6, 8);
		} while (setBoard(m, n, COM) != 0);
		step[0].x = m;
		step[0].y = n;
		Print_Checkerboard();
	}
}

void ManToCom::ThirdStep(Step step[])
{
	int x;
	char y;

	//人先手
	if (MAN == BLACK)
	{
		while (true) {
			cout << "请落子：";
			cin >> x; x -= 1;
			cin >> y; y -= 'A';
			if (setBoard(x, y, MAN) == 0 && x >= 5 && x <= 9 && y >= 5 && y <= 9) //是否下在5*5范围内
				break;
			else
				cout << "请选择正确的位置落子！" << endl;
		}
		step[1].x = x;
		step[1].y = y;
		Print_Checkerboard();
	}
	//电脑先手
	else if (COM == BLACK)
	{
		int m, n;
		srand((unsigned)time(NULL));
		do {
			m = random(5, 9);
			n = random(5, 9);
		} while (setBoard(m, n, COM) != 0);
		step[1].x = m;
		step[1].y = n;
		Print_Checkerboard();
	}
}

int ManToCom::WhetherChange(Step step[])
{
	int k, i, j;
	for (i = 0; i < 8; i++)
	{
		if (step[0].x == Lib[i]->x && step[0].y == Lib[i]->y)
		{
			for (j = 1; j <= 4; j++)
			{
				if (step[1].x == Lib[i][j].x && step[1].y == Lib[i][j].y)
					  return -1;
			}
		}
	}
	return 0;
}

void ManToCom::ForthStep(Step step[])
{
	int t, m;
	cout << "是否交换？ 1.是   2.否" << endl;

	if (MAN == WHITE)
	{
		cin >> m;
		if (m == 1)
		{
			cout << "白方选择交换" << endl;
			t = COM;
			COM = MAN;
			MAN = t;
		}
		else
			cout << "白方选择不交换" << endl;
	}
	else
	{
		if (WhetherChange(step) == 0)
		{
			cout << "白方选择交换" << endl;
			t = COM;
			COM = MAN;
			MAN = t;
		}
		else
			cout << "白方选择不交换" << endl;
	}

}

void ManToCom::Print_Menu2()
{
	int x, tx, ty, who_first;
	char y;
	Step step[2];
	//确定是否先手
	Print_Checkerboard();
	cout << "请选择是否先手\n1.是\t2.否" << endl;
	cin >> who_first;

	FirstStep(who_first);
	SecondStep(step);
	ThirdStep(step);
	ForthStep(step);

	if (COM == WHITE)
	{
		tx = step[1].x;
		ty = step[1].y;
		minmaxSearch(1, tx, ty);
		setBoard(tx, ty, COM);
		Print_Checkerboard();
	}
	while (1)
	{
		while (true) {
			cout << "请落子：";
			cin >> x; x -= 1;
			cin >> y; y -= 'A';
			if (setBoard(x, y, MAN) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Print_Checkerboard();
		if (IsWin(x, y) == 0)
		{
			cout << "恭喜你获胜了!" << endl;
			break;
		}
		tx = x, ty = y;
		minmaxSearch(2, tx, ty);
		setBoard(tx, ty, COM);
		Print_Checkerboard();
		if (IsWin(tx, ty) == 0)
		{
			cout << "很遗憾你输了!" << endl;
			break;
		}
	}
}

#endif

