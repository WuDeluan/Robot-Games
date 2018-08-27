#ifndef GOBANG_STEPS_H
#define GOBANG_STEPS_H

#include "Gobang_Rules.h"

class Gobang_Steps : public Gobang_Rules, public Gobang {
public:
	void Opening(); //指定开局
	void ForthStep(); //三手交换选择
	void FifthStep(); //打点选择
	void Continue();
	void Print_Menu1();
};

//人人界面
void Gobang_Steps::Print_Menu1()
{
	int x;
	char y;
	int tx, ty;
	Gobang::Print_Checkerboard();
	while (1)
	{
		while (true) {
			cout << "请黑方落子：";
			cin >> x; cin >> y;
			if (Gobang::setBoard(15 - x, y - 'A', BLACK) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Gobang::Print_Checkerboard();
		if (Gobang::IsWin(15 - x, y - 'A') == 0)
			cout << "黑方获胜!" << endl;
		tx = 15 - x; ty = y - 'A';
		if (PreJudge(tx, ty) != 0)
		{
			Gobang::setBoard(tx, ty, WHITE);
			Gobang::Print_Checkerboard();
		}

		while (true) {
			cout << "请白方落子：";
			cin >> x; cin >> y;
			if (Gobang::setBoard(15 - x, y - 'A', WHITE) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Gobang::Print_Checkerboard();
		if (Gobang::IsWin(15 - x, y - 'A') == 0)
			cout << "白方获胜!" << endl;
		tx = 15 - x; ty = y - 'A';
		if (PreJudge(tx, ty) != 0)
		{
			Gobang::setBoard(tx, ty, BLACK);
			Gobang::Print_Checkerboard();
		}
	}
}

//指定开局
void Gobang_Steps::Opening()
{
	int m, x;
	char y;
	cout << "是否先手？\n 1.是\t2.否" << endl;
	cin >> m;
	if (m == 1)  //人先手
	{
		MAN = BLACK; COM = WHITE; //确定双方执棋颜色
		cout << "请输入打点数："; cin >> points; //输入打点数
		cout << "请指定开局：" << endl;
		//黑1
		while (true)
		{
			cout << "黑1："; cin >> x; cin >> y;
			if (x == 8 && y == 'H') { //位置正确性判断
				Gobang::setBoard(15 - x, y - 'A', BLACK);
				Gobang::Print_Checkerboard();
				break;
			}
			else
				cout << "黑1应落在天元处！" << endl;
		}
		//白2
		while (true)
		{
			cout << "白2："; cin >> x; cin >> y;
			if (x >= 7 && x <= 9 && y >= 'G' && y <= 'I' && Board[15 - x][y - 'A'] == EMPTY) { //位置正确性判断
				Gobang::setBoard(15 - x, y - 'A', WHITE);
				Gobang::Print_Checkerboard();
				steps[0].x = 15 - x; steps[0].y = y - 'A'; //记录白2棋子坐标
				break;
			}
			else
				cout << "请输入正确的位置坐标！" << endl;
		}
		//黑3
		while (true)
		{
			cout << "黑3: "; cin >> x; cin >> y;
			if (x >= 6 && x <= 10 && y >= 'F' && y <= 'J' && Board[15 - x][y - 'A'] == EMPTY) //位置正确性判断
			{
				Gobang::setBoard(15 - x, y - 'A', BLACK);
				Gobang::Print_Checkerboard();
				steps[1].x = 15 - x; steps[1].y = y - 'A'; //记录黑3棋子坐标
				break;
			}
			else
				cout << "请输入正确的位置坐标！" << endl;
		}
	}
	else if (m == 2) //电脑先手
	{
		srand((unsigned)time(NULL));
		points = random(1, 3);
		MAN = WHITE; COM = WHITE;  //确定双方执棋颜色
		cout << "黑方给出的打点数为：" << points << endl;
		Gobang_Rules::SpecificOpening(); //电脑指定开局
		Gobang::Print_Checkerboard();
	}
}

//三手交换选择
void Gobang_Steps::ForthStep()
{
	int m, x; char y;
	if (MAN == WHITE) //人为白方
	{
		cout << "请选择是否交换棋子？\n1.是\t2.否" << endl;
		cin >> m;
	}
	else if (COM == WHITE) //电脑为白方
		m = Gobang_Rules::WhetherChange(steps);

	//电脑下白4
	if (m == 1) {
		COM = WHITE; MAN = BLACK;
		Gobang_Rules::WhiteFour(); //白4坐标确定
		Gobang::Print_Checkerboard();
	}
	//人下白4
	else if (m == 2) {
		COM = BLACK; MAN = WHITE;
		while (true)
		{
			cout << "请输入白4坐标："; cin >> x; cin >> y;
			if (x >= 6 && x <= 10 && y >= 'F' && y <= 'J' && Board[15 - x][y - 'A'] == EMPTY) { //坐标正确性判断
				Gobang::setBoard(15 - x, y - 'A', WHITE);
				Gobang::Print_Checkerboard();
				break;
			}
			else
				cout << "请输入正确的位置坐标！" << endl;
		}
	}
}

//打点选择
void Gobang_Steps::FifthStep()
{
	int i, x, z; char y;
	//人为黑方
	if (MAN == BLACK)
	{
		//人给出打点位置坐标
		cout << "请给出 " << points << " 个打点坐标：" << endl;
		for (i = 0; i < points; i++)
		{
			while (true)
			{
				cout << "第 " << i + 1 << " 个坐标: "; cin >> x; cin >> y;
				if (x >= 0 && x <= 14 && y >= 'A' && y <= 'O' && Board[15 - x][y - 'A'] == EMPTY) //位置正确性判断 
				{
					Gobang::setBoard(15 - x, y - 'A', BLACK);
					Gobang::Print_Checkerboard(); //打印打点后的棋盘
					steps[i + 2].x = 15 - x; steps[i + 2].y = y - 'A'; //记录黑5棋子坐标
					break;
				}
				else
					cout << "请输入正确的位置坐标！" << endl;
			}
		}

		//电脑选择一个棋子作为黑5
		for (i = 0; i < points; i++) //清空打点的棋子
			Gobang::setBack();
		Gobang_Rules::SaveOnePoint(x, z); //给出黑5坐标
		(COM == BLACK) ? cout << "（黑方）" : cout << "（白方）";
		cout << "选择的坐标是：(" << 15 - x << " , " << (char)(z + 'A') << ")" << endl;
		Gobang::setBoard(x, z, BLACK); //落子
		steps[2].x = x; steps[2].y = z; //记录黑5棋子坐标
		Gobang::Print_Checkerboard(); //打印当前棋盘
	}
	//电脑为黑方
	else if (COM == BLACK)
	{
		//电脑给出打点位置坐标
		for (i = 0; i < points; i++)
		{
			BlackFive(x, z);
			cout << "第 " << i + 1 << " 个棋子: " << "(" << 15 - x << " , " << char(z + 'A') << ")" << endl;
		}
		Gobang::Print_Checkerboard(); //打印打点后的棋盘
		//人选择一个棋子作黑5
		while (true)
		{
			cout << "请选择要保留的棋子坐标："; cin >> x; cin >> y;
			if (x >= 0 && x <= 14 && y >= 'A' && y <= 'O') //位置正确性判断 
				break;
			else
				cout << "请输入正确的位置坐标！" << endl;
		}
		for (i = 0; i < points; i++) //清空打点的棋子
			Gobang::setBack();
		Gobang::setBoard(15 - x, y - 'A', BLACK); //落子
		steps[2].x = 15 - x; steps[2].y = y - 'A'; //记录黑5棋子坐标
		Gobang::Print_Checkerboard(); //打印当前棋盘
	}
}

void Gobang_Steps::Continue()
{
	int x, y, tx, ty;
	char z;
	if (COM == WHITE)
	{
		tx = steps[2].x;
		ty = steps[2].y;
		if (PreJudge(tx, ty) == 0)
			//minmaxSearch(2, tx, ty);
		    NegaScoutSearch(2, -INFINITY, +INFINITY, COM);
		cout << "（白方）落子：" << "(" << 15 - X << " , " << char(Y + 'A') << ")" << endl;
		Gobang::setBoard(X, Y, COM);
		Gobang::Print_Checkerboard();
	}

	while (1)
	{
		while (true) {
			//人
			(MAN == BLACK) ? cout << "（黑方）请落子：" : cout << "（白方）请落子：";
			cin >> x; cin >> z;
			x = 15 - x;
			y = z - 'A';
			if (Gobang::setBoard(x, y, MAN) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Gobang::Print_Checkerboard();
		if (Gobang::IsWin(x, y) == 0)
		{
			cout << "恭喜你获胜了!" << endl;
			break;
		}
		//电脑
		tx = x, ty = y;
		if (PreJudge(tx, ty) == 0)
			 //minmaxSearch(3, tx, ty);
			NegaScoutSearch(2, -INFINITY, +INFINITY, COM);
		Gobang::setBoard(X, Y, COM);
		(COM == BLACK) ? cout << "（黑方）落子：" : cout << "（白方）落子：";
		cout << "(" << 15 - tx << " , " << char(ty + 'A') << ")" << endl;
		Gobang::Print_Checkerboard();
		if (Gobang::IsWin(tx, ty) == 0)
		{
			cout << "很遗憾你输了!" << endl;
			break;
		}
	}
}



#endif 
