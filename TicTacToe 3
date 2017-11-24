#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#define null 0
#define INIFITY 1000
#define DRAW 0
#define MAN -1
#define COM 1
using namespace std;

class TicTacToe {
public:
	void initGame();
	int setBoard(int i, int player);
	int getBoard(int i);
	bool IsFull();
	bool IsEmpty();
	int IsWin();
	int eval();
	void ManFirst();
	void ComFirst();
	int minmaxSearch(int depth);
	int MinSearch(int depth);
	int MaxSearch(int depth);
	void Print();
private:
	int board[9];
	vector<string> Board;
};

void TicTacToe::initGame()
{
	int i, j;
	for (i = 0; i < 9; i++)
		board[i] = null;
	Board = {
		" --- --- --- ",
		"|   |   |   |",
		" --- --- --- ",
		"|   |   |   |",
		" --- --- --- ",
		"|   |   |   |",
		" --- --- --- "
	};
}

int TicTacToe::setBoard(int i, int player)
{
	if (board[i] == null)
	{
		board[i] = player;
		(player == COM) ? Board[(i / 3) * 2 + 1][(i % 3) * 4 + 2] = 'O' : Board[(i / 3) * 2 + 1][(i % 3) * 4 + 2] = 'X';
	}
	else if (board[i] != null)
		return -1;
}

int TicTacToe::getBoard(int i)
{
	return board[i];
}

bool TicTacToe::IsFull()
{
	for (int i = 0; i < 9; i++)
		if (board[i] == null)
			return false;
	return true;
}

bool TicTacToe::IsEmpty()
{
	for (int i = 0; i < 9; i++)
		if (board[i] != null)
			return false;
	return true;
}

int TicTacToe::IsWin()
{
	if (eval() == +INIFITY)
		return COM;
	else if (eval() == -INIFITY)
		return MAN;
	else if (IsFull())
		return DRAW;
}

int TicTacToe::eval()
{
	int temp[9] = { 0 };
	int i, j;
	int line[8][3] = {
		{ 0,1,2 },{ 3,4,5 },{ 6,7,8 },
		{ 0,3,6 },{ 1,4,7 },{ 2,5,8 },
		{ 0,4,8 },{ 2,4,6 } };
	for (i = 0; i < 9; i++)
		temp[i] = board[i];
	int win = 0;
	int lose = 0;
	for (i = 0; i < 8; i++)
	{
		int sum = 0;
		for (j = 0; j < 3; j++)
			sum += temp[line[i][j]];
		if (sum == 3)
			return +INIFITY;
		else if (sum == -3)
			return -INIFITY;
		else if (-3 < sum < 0)
			lose++;
		else if (0 < sum < 3)
			win++;
	}
	return win - lose;
}

void TicTacToe::ManFirst()
{
	int depth = 9;
	int x, y;
	for (int i = 0; i <= 9; i++)
	{
		cout << "请输入位置坐标：";
		cin >> x;
		cin >> y;
		if (x >= 0 && x <= 2 && y >= 0 && y <= 2 && getBoard(x * 3 + y) == null) {
			system("cls");
			setBoard((x * 3 + y), MAN);
			cout << "人：" << endl;
			Print();
			if (MAN == IsWin()) {
				cout << "您获胜了！！！" << endl;
				break;
			}
			depth--;
			if (IsFull()) {
				cout << "平局 ~~~" << endl;
				break;
			}
			setBoard(minmaxSearch(depth), COM);
			cout << "电脑：" << endl;
			Print();
			if (COM == IsWin()) {
				cout << "很遗憾，您输了！！！" << endl;
				break;
			}
			depth--;
		}
		else
			cout << "该位置已有棋子！ " << endl;
	}
}

void TicTacToe::ComFirst()
{
	int depth = 9;
	int x, y;
	static int k = 0;
	for (int i = 0; i <= 9; i++)
	{
		if (k == 0)
		{
			setBoard(4, COM);
			k = 1;
		}
		else
			setBoard(minmaxSearch(depth), COM);
		cout << "电脑：" << endl;
		Print();
		if (COM == IsWin()) {
			cout << "很遗憾，您输了！！！" << endl;
			break;
		}
		if (IsFull()) {
			cout << "平局 ~~~" << endl;
			break;
		}
		depth--;
		while (1) {
			cout << "请输入位置坐标：";
			cin >> x;
			cin >> y;
			if (x >= 0 && x <= 2 && y >= 0 && y <= 2 && getBoard(x * 3 + y) == null)
				break;
			else
				cout << "该位置已有棋子！" << endl;
		}
		system("cls");
		setBoard((x * 3 + y), MAN);
		cout << "人：" << endl;
		Print();
		if (MAN == IsWin()) {
			cout << "您获胜了！！" << endl;
			break;
		}
		depth--;
	}
}

int TicTacToe::minmaxSearch(int depth)
{
	int bestMoves[9] = { 0 };
	int index = 0;
	int bestValue = -INIFITY;
	if (depth == 0 && IsFull())
		return eval();
	else
	{
		for (int pos = 0; pos < 9; pos++)
		{
			if (board[pos] == null) {
				board[pos] = COM;
				if (eval() == +INIFITY)
				{
					bestMoves[index] = pos;
					board[pos] = null;
					break;
				}
				int value = MinSearch(depth - 1);
				if (value > bestValue)
				{
					bestValue = value;
					index = 0;
					bestMoves[index] = pos;
				}
				else if (value == bestValue)
					bestMoves[++index] = pos;
				board[pos] = null;
			}
		}
	}
	return bestMoves[index];
}

int TicTacToe::MaxSearch(int depth)
{
	int bestValue = -INIFITY;
	if (depth == 0 && IsFull())
		return eval();
	else
	{ 
		int value;
		for (int pos = 0; pos < 9; pos++)
		{
			if (board[pos] == null)
			{
				board[pos] = COM;
				value = MinSearch(depth - 1);
				if (value > bestValue)
					bestValue = value;
				board[pos] = null;
			}
		}
	}
	return bestValue;
}

int TicTacToe::MinSearch(int depth)
{
	int bestValue = INFINITY;
	if (depth == 0 && IsFull())
		return eval();
	else
	{
		int value;
		for (int pos = 0; pos < 9; pos++)
		{
			if (board[pos] == null)
			{
				board[pos] = MAN;
				value = MaxSearch(depth - 1);
				if (value < bestValue)
					bestValue = value;
				board[pos] = null;
			}
		}
	}
	return bestValue;
}

void TicTacToe::Print()
{
	int i, j;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 13; j++)
			cout << Board[i][j];
		cout << endl;
	}
	cout << endl;
}


int main()
{
	TicTacToe T;
	T.initGame();
	T.Print();
	int x;
	cout << "请选择开始方：1.电脑  2.人" << endl;
	cin >> x;
	if (x == 2)
		T.ManFirst();
	else if (x == 1)
		T.ComFirst();
}
