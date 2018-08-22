#ifndef GOBANG_RULES_H
#define GOBANG_RULES_H

#include "Gobang_Base.h"

class Gobang_Rules : public Gobang
{
public:
	void SpecificOpening(); //指定开局
	int WhetherChange(Point step[]); //是否三手交换判断
	void WhiteFour(); //白4坐标
	void BlackFive(int &x, int &y); //黑5坐标
	void SaveOnePoint(int &x, int &y); //从黑5打点坐标中选择一个
	int IsWin(int x, int y); //判断某一方是否连成五子
	int PreJudge(int &x, int &y); //预判是否出现必须防守的情况
	int Eval(int x, int y);
	int Function(int len, string side1, string side2);
	int minmaxSearch(int depth, int &tx, int &ty);
	int MaxSearch(int depth, int tx, int ty);
	int MinSearch(int depth, int tx, int ty);
	int Alphabeta(int &tx, int &ty,int depth, int a, int b,int player);
};

//指定开局
void Gobang_Rules::SpecificOpening()
{
	srand((unsigned)time(NULL));
	int k = random(0, 25); //随机得到一种开局
	setBoard(7, H, BLACK); //黑1位于(7，H)
	if (k >= 0 && k < 13) //前13种为直指开局
	{
		setBoard(6, H, WHITE); //白2位于(6, H)
		setBoard(15 - Lib[k].x, Lib[k].y, BLACK); //找到对应于棋盘的位置，落子
	}
	else if (k >= 13 && k < 26) //后13种为斜指开局
	{
		setBoard(6, I, WHITE); //白2位于(6, I)
		setBoard(15 - Lib[k].x, Lib[k].y, BLACK); //找到对应于棋盘的位置，落子 
	}
}

//是否三手交换判断
int Gobang_Rules::WhetherChange(Point step[])
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		if (step[0].x == Lib1[i][0].x && step[0].y == Lib1[i][0].y) //符合Lib1中黑2的位置坐标
		{
			for (j = 1; j <= 4; j++)
			{
				if (step[1].x == Lib1[i][j].x && step[1].y == Lib1[i][j].y) //符合黑2坐标对应的白3坐标
				{
					cout << "白方选择交换。" << endl;
					return 2; //交换棋子颜色
				}
			}
		}
	}
	cout << "白方选择不交换。" << endl;
	return 1;
}

//白4坐标
void Gobang_Rules::WhiteFour()
{
	//暂定为由随机数产生
	int x, y;
	while (true)
	{
		srand((unsigned)time(NULL));
		x = random(6, 8);
		y = random(6, 8);
		if (Board[x][y] == EMPTY)//判断该坐标是否已有棋子
		{
			setBoard(x, y, WHITE);
			break;
		}
	}
	cout << "（白方）落子：(" << 15 - x << " , " << char(y + 'A') << ")" << endl;
}

//黑5坐标
void Gobang_Rules::BlackFive(int &x, int &y)
{
	//暂定由随机数产生
	while (true)
	{
		srand((unsigned)time(NULL));
		x = random(5, 9);
		y = random(5, 9);
		if (Board[x][y] == EMPTY)//判断该坐标是否已有棋子
		{
			setBoard(x, y, BLACK);
			break;
		}
	}
}

//从黑5打点坐标中选择一个
void Gobang_Rules::SaveOnePoint(int &x, int &y)
{
	//暂定为第一个打点坐标
	x = steps[2].x;
	y = steps[2].y;
}

//判断某一方是否连成五子
int Gobang_Rules::IsWin(int x, int y)
{
	int i, tx, ty, len;
	int Side = getBoard(x, y);//取得落子颜色
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

//预判是否出现必须防守的情况
int Gobang_Rules::PreJudge(int &x, int &y)
{
	int i, j, tx, ty, len;
	Point p1, p2;
	int Side = Gobang::getBoard(x, y);
	string side1, side2; //记录两端的棋子情况
	for (i = 0; i < 4; i++) //四个方向上进行查找
	{
		tx = x; ty = y;
		len = 0; side1.clear(); side2.clear(); //初始化各变量
		//找到一个方向上距离最远的同颜色棋子位置
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && Gobang::getBoard(tx, ty) == Side)
		{
			tx -= Direct[i][0];
			ty -= Direct[i][1];
		}
		p1.x = tx; p1.y = ty; //记录端点1
		//向该方向往外延申5个点，并记录
		for (j = 0; j < 5; j++, tx -= Direct[i][0], ty -= Direct[i][1]) {
			if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side1 += '#';
			else if (Gobang::getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
				side1 += '0';
			else
				side1 += '1';
		}
		//往反方向还原
		tx += Direct[i][0] * 6;
		ty += Direct[i][1] * 6;
		//往反方向记录连续棋子个数
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && Gobang::getBoard(tx, ty) == Side)
		{
			len++;
			tx += Direct[i][0];
			ty += Direct[i][1];
		}
		p2.x = tx; p2.y = ty; //记录端点2
		//记录另一端五个点的棋子情况
		for (j = 0; j < 5; j++, tx += Direct[i][0], ty += Direct[i][1]) {
			if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side2 += '#';
			else if (Gobang::getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
				side2 += '0';
			else
				side2 += '1';
		}
		//判断具体情况
		int k = 0;
		if (len == 4)
		{
			if (side1[0] == '#' && side2[0] == '#')
				k = 1;
			else if (side1[0] == '#' && side2[0] == '1')
				k = 1;
			else if (side1[0] == '1' && side2[0] == '#')
				k = 2;
		}
		else if (len == 3)
		{
			if (side1[0] == '#' && side2[0] == '#')
				k = 1;
			else if (side1[0] == '1' && side2.compare(0, 2, "#0") == 0)
				k = 2;
			else if (side1.compare(0, 2, "#0") == 0 && side2[0] == '1')
				k = 1;
			else if (side1.compare(0, 3, "#01") == 0)
				k = 1;
			else if (side2.compare(0, 3, "#01") == 0)
				k = 2;
		}
		else if (len == 2)
		{
			if (side1[0] == '#' && side2.compare(0, 3, "#0#") == 0)
				k = 2;
			else if (side1.compare(0, 3, "#0#") == 0 && side2[0] == '#')
				k = 1;
			else if (side1[0] == '1' && side2.compare(0, 3, "#00") == 0)
				k = 2;
			else if (side1.compare(0, 2, "#00") == 0 && side2[0] == '1')
				k = 1;
			else if (side1.compare(0, 3, "#00") == 0)
				k = 1;
			else if (side2.compare(0, 3, "#00") == 0)
				k = 2;

		}
		else if (len == 1)
		{
			if (side1.compare(0, 3, "#000") == 0 && side2[0] == '#')
				k = 1;
			else if (side1[0] == '#' && side2.compare(0, 3, "#00") == 0)
				k = 2;
			else if (side1.compare(0, 4, "#000") == 0)
				k = 1;
			else if (side2.compare(0, 3, "#000") == 0)
				k = 2;
		}

		if (k == 1)
		{
			x = p1.x;
			y = p1.y;
			return 1;
		}
		else if (k == 2)
		{
			x = p2.x;
			y = p2.y;
			return 2;
		}
	}
	return 0;
}

int Gobang_Rules::Eval(int x, int y)
{
	int i, j, tx, ty, len;
	int Side = COM;
	string side1, side2;
	int bestValue = -1;
	for (i = 0; i < 4; i++)
	{
		tx = x; ty = y;
		len = 0;
		side1.clear(); side2.clear();
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && Gobang::getBoard(tx, ty) == Side)
		{
			tx -= Direct[i][0];
			ty -= Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx -= Direct[i][0], ty -= Direct[i][1]) {
			if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side1 += '#';
			else if (Gobang::getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
				side1 += '0';
			else
				side1 += '1';
		}
		tx += Direct[i][0] * 4;
		ty += Direct[i][1] * 4;
		while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && Gobang::getBoard(tx, ty) == Side)
		{
			len++;
			tx += Direct[i][0];
			ty += Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx += Direct[i][0], ty += Direct[i][1]) {
			if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side2 += '#';
			else if (Gobang::getBoard(tx, ty) == Side && tx >= 0 && ty >= 0)
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

int Gobang_Rules::Function(int len, string side1, string side2)
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
			Value += 50000;
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

int Gobang_Rules::minmaxSearch(int depth, int &tx, int &ty)
{
    int bestMoveX, bestMoveY;
	int x, y;
	int bestValue = -INFINITY;
	if (depth == 0)
	    return Eval(tx, ty);
	else
	{
		//for (x = tx - 4; x <= tx + 4; x++)
		for(x = 0;x < 15;x++)
		{
			//for (y = ty - 4; y <= ty + 4; y++)
			for(y = 0;y < 15;y++)
			{
				//if (x >= 0 && x < 15 && y >= 0 && y < 15 && Gobang::getBoard(x, y) == EMPTY)
				if (Gobang::getBoard(x, y) == EMPTY)
				{

					Gobang::setBoard(x, y, COM); 
					if (Eval(x, y) >= +INFINITY)
					{
						tx = x;
						ty = y;
						Gobang::setEmpty(x, y);
						return 1;
					}
					int value = MinSearch(depth - 1, x, y);
					if (value > bestValue)
					{
						bestValue = value;
						bestMoveX = x;
						bestMoveY = y;

					}
					else if (value == bestValue)
					{
						bestMoveX = x;
						bestMoveY = y;
					}
					setEmpty(x, y);
				}
			}
		}
	}
	tx = bestMoveX;
	ty = bestMoveY;
}

int Gobang_Rules::MaxSearch(int depth, int tx, int ty)
{
	int bestValue = -INFINITY, x, y;
	if (depth == 0)
	{
		int L = Eval(tx, ty);
		//cout << "max  " << L << endl;
		return L;
	}
	else
	{
		int value;
		//for (x = tx - 4; x <= tx + 4; x++)
		for (x = 0; x < 15; x++)
		{
			//for (y = ty - 4; y <= ty + 4; y++)
			for (y = 0; y < 15; y++)
			{
				//if (x >= 0 && x < 15 && y >= 0 && y < 15 && Gobang::getBoard(x, y) == EMPTY)
				if (Gobang::getBoard(x, y) == EMPTY)
				{
					setBoard(x, y, COM);
					value = MinSearch(depth - 1, x, y);
					if (value > bestValue)
						bestValue = value;
					setEmpty(x, y);
				}
			}
		}
	}
	//cout <<"                      MAX   "<< bestValue << endl;
	return bestValue;
}

int Gobang_Rules::MinSearch(int depth, int tx, int ty)
{  
	int bestValue = INFINITY, x, y;
	if (depth == 0)
	{
		int L = Eval(tx, ty);
		//cout << "min  " << L << endl;
		return L;
	}
	else
	{
		int value;
		//for (x = tx - 4; x <= tx + 4; x++)
		for (x = 0; x < 15; x++)
		{
			//for (y = ty - 4; y <= ty + 4; y++)
			for (y = 0; y < 15; y++)
			{
				//if (x >= 0 && x < 15 && y >= 0 && y < 15 && Gobang::getBoard(x, y) == EMPTY)
				if(Gobang::getBoard(x, y) == EMPTY)
				{
					setBoard(x, y, MAN); 
					value = MaxSearch(depth - 1, x, y);
					if (value < bestValue)
						bestValue = value;
					setEmpty(x, y); 
				}
			}
		}
	}
	//cout << "                           MIN   " << bestValue << endl;
	return bestValue;
}

int Gobang_Rules::Alphabeta(int &tx, int &ty,int depth, int a, int b,int player)
{
	int x, y, value;
	if (depth == 0)
		return Eval(tx, ty);
	if (player == COM)
	{
		for (x = 0; x < 15; x++)
		{
			for (y = 0; y < 15; y++)
			{
				if (Gobang::getBoard(x, y) == EMPTY)
				{
					Gobang::setBoard(x, y, COM);
					value = Alphabeta(x, y, depth - 1, a, b, MAN);
					if (value > a)
					{
						a = value;
						tx = x;
						ty = y;
					}
					Gobang::setEmpty(x, y);
					if (b <= a)
						break; 
				}	
			}
		}
		return a;
	}
	else if (player == MAN)
	{
		for (x = 0; x < 15; x++)
		{
			for (y = 0; y < 15; y++)
			{
				if (Gobang::getBoard(x, y) == EMPTY)
				{
					Gobang::setBoard(x, y, MAN);
					b = Min(b, Alphabeta(x, y, depth - 1, a, b, COM));
					Gobang::setEmpty(x, y);
					if (b <= a)
						break;				
				}	
			}
		}
		return b;
	}
}

#endif
