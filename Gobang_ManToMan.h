#ifndef GOBANG_MANTOMAN_H
#define GOBANG_MANTOMAN_H

#include "Gobang_Base.h"

class ManToMan : public Gobang
{
public:
	ManToMan();
	int IsWin(int x, int y);//判断是否赢棋
	void Print_Menu1();
};

ManToMan::ManToMan()
{
	Init_Board();
}

//判断某一方是否连成五子
int ManToMan::IsWin(int x, int y)
{
	int i, tx, ty, len;
	int Side = getBoard(x,y);//取得落子颜色
	for (i = 0; i < 4; i++)//4个方向的循环
	{
		tx = x; ty = y;//设置观察起点
		len = 0;//设置计数器
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)//连珠条件
		{
			tx -= Direct[i][0];//沿一个方向
			ty -= Direct[i][1];//移动观察点
		}
		tx += Direct[i][0];
		ty += Direct[i][1];
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && getBoard(tx, ty) == Side)//连珠条件
		{
			len++;//计数
			tx += Direct[i][0];//沿相反方向
			ty += Direct[i][1];//移动观察点
		}
		if (len >= 5)//比较连珠数目
			return 0;//获胜
	}
	return -1;//为获胜
}

//打印人人博弈界面
void ManToMan::Print_Menu1()
{
	int x;
	char y;
	Print_Checkerboard();
	while (1)
	{
		while (true) {
			cout << "请黑方落子：";
			cin >> x; x -= 1;
			cin >> y; y -= 'A';
			if (setBoard(x, y, BLACK) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Print_Checkerboard();
		if (IsWin(x, y) == 1)
			cout << "黑方获胜!" << endl;
		while (true) {
			cout << "请白方落子：";
			cin >> x; x -= 1;
			cin >> y; y -= 'A';
			if (setBoard(x, y, WHITE) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		Print_Checkerboard();
		if (IsWin(x, y) == 1)
			cout << "白方获胜!" << endl;
	}
}

#endif
