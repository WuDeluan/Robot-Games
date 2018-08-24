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
	int PreJudge_IsFour(int &x, int &y); //预判是否出现必须防守的情况
	int PreJudge_IsFive(int &x, int &y); //预判是否有连子的可能
	int PreJudge(int &x, int &y);  //搜索前的预判
	int IsLegal(int x, int y); //是否存在禁手
	int Evaluate(); //估值函数，对某一局面的估值
	void Analysis(int x, int y);  //对某一点的估值判断
	int minmaxSearch(int depth, int &tx, int &ty);
	int MaxSearch(int depth, int tx, int ty);
	int MinSearch(int depth, int tx, int ty);
	int Alphabeta(int &tx, int &ty, int depth, int a, int b, int player);
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
int Gobang_Rules::PreJudge_IsFour(int &x, int &y)
{
	int i, j, tx, ty, len, k;
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
		k = 0;
		if (len == 4)
		{
			/*if (side1[0] == '#' && side2[0] == '#')
				k = 1;
			else if (side1[0] == '#' && side2[0] == '1')
				k = 1;
			else if (side1[0] == '1' && side2[0] == '#')
				k = 2;*/
			if (side1[0] == '#')
				k = 1;
			else if (side2[0] == '#')
				k = 2;
		}
		else if (len == 3)
		{
			/*if (side1[0] == '1' && side2.compare(0, 2, "#0") == 0)
				k = 2;
			else if (side1.compare(0, 2, "#0") == 0 && side2[0] == '1')
				k = 1;
			else if (side1.compare(0, 3, "#01") == 0)
				k = 1;
			else if (side2.compare(0, 3, "#01") == 0)
				k = 2;*/
			if (side1.compare(0, 2, "#0") == 0)
				k = 1;
			else if (side2.compare(0, 2, "#0") == 0)
				k = 2;
		}
		else if (len == 2)
		{
			if (side1.compare(0, 3, "#00") == 0)
				k = 1;
			else if (side2.compare(0, 3, "#00") == 0)
				k = 2;
		}
		else if (len == 1)
		{
			/*if (side1.compare(0, 4, "#000") == 0 && side2[0] == '#')
				k = 1;
			else if (side1[0] == '#' && side2.compare(0, 4, "#000") == 0)
				k = 2;
			else if (side1 == "#0001" && side2[0] == '#')
				k = 1;
			else if (side2 == "#0001" && side1[0] == '#')
				k = 2;
			else if (side2[0] == '1' && side1.compare(0, 4, "#000") == 0)
				k = 1;
			else if (side1[0] == '1' && side2.compare(0, 4, "#000") == 0)
				k = 2;*/
			if (side1.compare(0, 4, "#000") == 0)
				k = 1;
			else if (side2.compare(0, 4, "#000") == 0)
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

//预判是否有连子的可能
int Gobang_Rules::PreJudge_IsFive(int &x, int &y)
{
	int tx, ty, m, n, i, len;
	int Side = COM;
	for (m = 0; m < 15; m++)
	{
		for (n = 0; n < 15; n++)
		{
			if (Gobang::getBoard(m, n) == EMPTY)
			{
				Gobang::setBoard(m, n, COM);
				for (i = 0; i < 4; i++) //四个方向上进行查找
				{
					tx = m; ty = n;
					len = 0; //初始化各变量
					//找到一个方向上距离最远的同颜色棋子位置
					while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && Gobang::getBoard(tx, ty) == Side)
					{
						tx -= Direct[i][0];
						ty -= Direct[i][1];
					}
					tx += Direct[i][0];
					ty += Direct[i][1];
					//往反方向记录连续棋子个数
					while (tx >= 0 && tx < 15 && ty >= 0 && ty < 15 && Gobang::getBoard(tx, ty) == Side)
					{
						len++;
						tx += Direct[i][0];
						ty += Direct[i][1];
					}
					if (len == 5)
					{
						x = m; y = n;
						return 1;
					}
				}
				Gobang::setEmpty(m, n);
			}
		}
	}
	return 0;
}

//搜索前的预判
int Gobang_Rules::PreJudge(int &x, int &y)
{
	if (PreJudge_IsFive(x, y) == 0)  //不构成连子
	{
		if (PreJudge_IsFour(x, y) == 0)  //没有必须的防守
			return 0;
	}
	return 1;
}

//是否存在禁手
int Gobang_Rules::IsLegal(int x, int y)
{
	int i, j, tx, ty, len = 0;
	int four = 0, three = 0;
	string side1, side2;
	int Color = Gobang::getBoard(x, y);
	for (i = 0; i < 4; i++)
	{
		len = 0;
		tx = x; ty = y;
		side1.clear(); side2.clear();
		while (Gobang::getBoard(tx, ty) == Color)
		{
			tx -= Direct[i][0];
			ty -= Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx -= Direct[i][0], ty -= Direct[i][1]) {
			if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side1 += '#';
			else if (Gobang::getBoard(tx, ty) == Color && tx >= 0 && ty >= 0)
				side1 += '0';
			else
				side1 += '1';
		}
		tx += Direct[i][0] * 4;
		ty += Direct[i][1] * 4;
		while (Gobang::getBoard(tx, ty) == Color && tx >= 0 && ty >= 0)
		{
			len++;
			TypeRecord[tx][ty][i] = ANALSISED;
			tx += Direct[i][0];
			ty += Direct[i][1];
		}
		for (j = 0; j < 3; j++, tx += Direct[i][0], ty += Direct[i][1]) {
			if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
				side2 += '#';
			else if (Gobang::getBoard(tx, ty) == Color && tx >= 0 && ty >= 0)
				side2 += '0';
			else
				side2 += '1';
		}

		if (len == 4)
		{
			if (side1[0] == '#' && side2[0] == '#')
				four++;
			if (side1[0] == '1' && side2[0] == '#' || side1[0] == '#' && side2[0] == '1')
				four++;
		}
		else if (len == 3)//考虑一个方向上的两端同时出现活三等的情况
		{
			if (side1.compare(0, 2, "#0") == 0)
				four++;
			if (side2.compare(0, 2, "#0") == 0)
				four++;
			if (side1.compare(0, 2, "##") == 0 && side2.compare(0, 2, "##") == 0)
				three++;
		}
		else if (len == 2) 
		{
			if (side1.compare(0, 3, "#00") == 0)
				four++;
			if (side2.compare(0, 3, "#00") == 0)
				four++;
			if (side1[0] == '#' && side2.compare(0, 3, "#0#") == 0)
				three++;
			if (side2[0] == '#' && side1.compare(0, 3, "#0#") == 0)
				three++;
		}
		//长度为1的情况待补充
	}

	if (three > 1 || four > 1)
		return 1;
	else
		return 0;
}

//估值函数，对某一局面的估值
int Gobang_Rules::Evaluate()
{
	int x, y, k;
	int Side;
	memset(TypeRecord, TOBEANALSIS, sizeof(TypeRecord));
	memset(TypeCount, 0, sizeof(TypeCount));
	for (x = 0; x < 15; x++)
		for (y = 0; y < 15; y++)
			if (Gobang::getBoard(x, y) != EMPTY)
				Analysis(x, y);

	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			Side = Gobang::getBoard(x, y);
			if (Side != EMPTY)
			{
				for (k = 0; k < 4; k++)
				{
					switch (TypeRecord[x][y][k])
					{
					case FIVE://五连
						TypeCount[Side][FIVE]++; break;
					case FOUR://活四
						TypeCount[Side][FOUR]++; break;
					case FFOUR://冲四
						TypeCount[Side][FFOUR]++; break;
					case DFOUR://死四
						TypeCount[Side][DFOUR]++; break;
					case THREE://活三
						TypeCount[Side][THREE]++; break;
					case STHREE://眠三
						TypeCount[Side][STHREE]++; break;
					case DTHREE://眠三
						TypeCount[Side][DTHREE]++; break;
					case TWO://活二
						TypeCount[Side][TWO]++; break;
					case STWO://眠二
						TypeCount[Side][STWO]++; break;
					default:break;
					}
				}
			}
		}
	}

	//如果已五连,返回极值
	if (TypeCount[COM][FIVE])
		return 9999;
	else if (TypeCount[MAN][FIVE])
		return -9999;

	//两个冲四等于一个活四
	if (TypeCount[COM][FFOUR] > 1)
		TypeCount[COM][FOUR]++;
	if (TypeCount[MAN][FFOUR] > 1)
		TypeCount[MAN][FOUR]++;

	int CValue = 0, MValue = 0;

	if (TypeCount[COM][FOUR])
		return 9990;//活四,白胜返回极值
	if (TypeCount[COM][FFOUR])
		return 9980;//冲四,白胜返回极值
	if (TypeCount[MAN][FOUR])
		return -9970;//白无冲四活四,而黑有活四,黑胜返回极值
	if (TypeCount[MAN][FFOUR] && TypeCount[MAN][THREE])
		return -9960;//而黑有冲四和活三,黑胜返回极值
	if (TypeCount[COM][THREE] && TypeCount[MAN][FFOUR] == 0)
		return 9950;//白有活三而黑没有四,白胜返回极值
	if (TypeCount[MAN][THREE] > 1 && TypeCount[WHITE][FFOUR] == 0 && TypeCount[COM][THREE] == 0 && TypeCount[COM][STHREE] == 0)
		return -9940;//黑的活三多于一个,而白无四和三,黑胜返回极值
	if (TypeCount[COM][THREE] > 1)
		CValue += 2000;//白活三多于一个,白棋价值加2000
	else //否则白棋价值加200
	{
		if (TypeCount[COM][THREE])
			CValue += 200;
	}
	if (TypeCount[MAN][THREE] > 1)
		MValue += 500;//黑的活三多于一个,黑棋价值加500
	else //否则黑棋价值加100
	{
		if (TypeCount[MAN][THREE])
			MValue += 100;
	}
	//每个眠三加10
	if (TypeCount[COM][STHREE])
		CValue += TypeCount[COM][STHREE] * 10;
	//每个眠三加10
	if (TypeCount[MAN][STHREE])
		MValue += TypeCount[MAN][STHREE] * 10;
	//每个活二加4
	if (TypeCount[COM][TWO])
		CValue += TypeCount[COM][TWO] * 4;
	//每个活二加4
	if (TypeCount[MAN][STWO])
		MValue += TypeCount[MAN][TWO] * 4;
	//每个眠二加1
	if (TypeCount[COM][STWO])
		CValue += TypeCount[COM][STWO];
	//每个眠二加1
	if (TypeCount[MAN][STWO])
		MValue += TypeCount[MAN][STWO];

	//加上所有棋子的位置价值
	for (x = 0; x < 15; x++)
		for (y = 0; y < 15; y++)
		{
			Side = Gobang::getBoard(x, y);
			if (Side != EMPTY)
				if (Side == COM)
					CValue += PosValue[x][y];
				else
					MValue += PosValue[x][y];
		}

	//返回估值
	return CValue - MValue;
}

//对某一点的估值判断
void Gobang_Rules::Analysis(int x, int y)
{
	int i, j, tx, ty, len = 0;
	string side1, side2;
	int Color = Gobang::getBoard(x, y);
	for (i = 0; i < 4; i++)
	{
		if (TypeRecord[x][y][i] == TOBEANALSIS)
		{
			len = 0;
			tx = x; ty = y;
			side1.clear(); side2.clear();
			while (Gobang::getBoard(tx, ty) == Color)
			{
				tx -= Direct[i][0];
				ty -= Direct[i][1];
			}
			for (j = 0; j < 5; j++, tx -= Direct[i][0], ty -= Direct[i][1]) {
				if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
					side1 += '#';
				else if (Gobang::getBoard(tx, ty) == Color && tx >= 0 && ty >= 0)
					side1 += '0';
				else
					side1 += '1';
			}
			tx += Direct[i][0] * 6;
			ty += Direct[i][1] * 6;
			while (Gobang::getBoard(tx, ty) == Color && tx >= 0 && ty >= 0)
			{
				len++;
				TypeRecord[tx][ty][i] = ANALSISED;
				tx += Direct[i][0];
				ty += Direct[i][1];
			}
			for (j = 0; j < 5; j++, tx += Direct[i][0], ty += Direct[i][1]) {
				if (Gobang::getBoard(tx, ty) == EMPTY && tx >= 0 && ty >= 0)
					side2 += '#';
				else if (Gobang::getBoard(tx, ty) == Color && tx >= 0 && ty >= 0)
					side2 += '0';
				else
					side2 += '1';
			}

			if (len >= 5)
			{
				//cout << "五连" << endl; 
				TypeRecord[x][y][i] = FIVE;
			}
			else if (len == 4)
			{
				if (side1[0] == '#' && side2[0] == '#')
				{
					//cout << "活四" << endl;
					TypeRecord[x][y][i] = FOUR;
				}
				else if (side1[0] == '1' && side2[0] == '#' || side1[0] == '#' && side2[0] == '1')
				{
					//cout << "冲四" << endl;
					TypeRecord[x][y][i] = FFOUR;
				}
				else if (side1[0] == '1' && side2[0] == '1')
				{
					//cout << "死四" << endl;
					TypeRecord[x][y][i] = DFOUR;
				}
			}
			else if (len == 3)
			{
				if (side1.compare(0, 2, "#0") == 0 || side2.compare(0, 2, "#0") == 0)
				{
					//cout << "冲四" << endl;
					TypeRecord[x][y][i] = FFOUR;
				}
				else if (side1.compare(0, 2, "##") == 0 && side2.compare(0, 2, "##") == 0)
				{
					//cout << "连活三" << endl;
					TypeRecord[x][y][i] = THREE;
				}
				else if (side1[0] == '1' && side2.compare(0, 2, "##") == 0 || side1.compare(0, 2, "##") == 0 && side2[0] == '1')
				{
					//cout << "眠三" << endl;
					TypeRecord[x][y][i] = STHREE;
				}
				else if (side1.compare(0, 2, "#1") == 0 && side2.compare(0, 2, "#1") == 0)
				{
					//cout << "眠三" << endl; 
					TypeRecord[x][y][i] = STHREE;
				}
				else if (side1[0] == '1' && side2[0] == '1')
				{
					//cout << "死三" << endl; 
					TypeRecord[x][y][i] = DTHREE;
				}
			}
			else if (len == 2)
			{
				if (side1.compare(0, 3, "#00") == 0 || side2.compare(0, 3, "#00") == 0)
				{
					//cout << "冲四" << endl;
					TypeRecord[x][y][i] = FFOUR;
				}
				else if (side1[0] == '#' && side2.compare(0, 3, "#0#") == 0 || side1.compare(0, 3, "#0#") == 0 && side2[0] == '#')
				{
					//cout << "跳活三" << endl;
					TypeRecord[x][y][i] = THREE;
				}
				else if (side1[0] == '1' && side2.compare(0, 3, "#1#") == 0 || side1.compare(0, 3, "#1#") == 0 && side2[0] == '1')
				{
					//cout << "眠三" << endl;
					TypeRecord[x][y][i] = STHREE;
				}
				else if (side1[0] == '#' && side2.compare(0, 3, "#10") == 0 || side1.compare(0, 3, "#10") == 0 && side2[0] == '#')
				{
					//cout << "眠三" << endl;
					TypeRecord[x][y][i] = STHREE;
				}
				else if (side1.compare(0, 3, "##0") == 0 || side2.compare(0, 3, "##0") == 0)
				{
					//cout << "眠三" << endl;
					TypeRecord[x][y][i] = STHREE;
				}
				else if (side1.compare(0, 2, "##") == 0 && side2.compare(0, 2, "##") == 0)
				{
					//cout << "活二" << endl;
					TypeRecord[x][y][i] = TWO;
				}
				else if (side1[0] == '1' && side2.compare(0, 3, "###") == 0 || side1.compare(0, 3, "###") == 0 && side2[0] == '1')
				{
					//cout << "眠二" << endl;
					TypeRecord[x][y][i] = STWO;
				}
			}
			//其他情况待补充
		}
	}
}

int Gobang_Rules::minmaxSearch(int depth, int &tx, int &ty)
{
	int bestMoveX, bestMoveY;
	int x, y;
	int bestValue = -INFINITY;
	if (depth == 0)
		return Evaluate();
	else
	{
		//for (x = tx - 4; x <= tx + 4; x++)
		for (x = 0; x < 15; x++)
		{
			//for (y = ty - 4; y <= ty + 4; y++)
			for (y = 0; y < 15; y++)
			{
				//if (x >= 0 && x < 15 && y >= 0 && y < 15 && Gobang::getBoard(x, y) == EMPTY)
				if (Gobang::getBoard(x, y) == EMPTY)
				{

					Gobang::setBoard(x, y, COM); //生成棋面
					if (IsLegal(x, y) == 0)
					{
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
					}			
					Gobang::setEmpty(x, y); //恢复棋面
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
		int L = Evaluate();
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
					if (IsLegal(x, y) == 0)
					{
						value = MinSearch(depth - 1, tx, ty);
						if (value > bestValue)
							bestValue = value;
					}
					setEmpty(x, y);
				}
			}
		}
	}
	//cout << "                      MAX   " << bestValue << endl;
	return bestValue;
}

int Gobang_Rules::MinSearch(int depth, int tx, int ty)
{
	int bestValue = INFINITY, x, y;
	if (depth == 0)
	{
		int L = Evaluate();
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
				if (Gobang::getBoard(x, y) == EMPTY)
				{
					setBoard(x, y, MAN);
					if (IsLegal(x, y) == 0)
					{
						value = MaxSearch(depth - 1, tx, ty);
						if (value < bestValue)
							bestValue = value;
					}
					setEmpty(x, y);
				}
			}
		}
	}
	//cout << "                           MIN   " << bestValue << endl;
	return bestValue;
}

int Gobang_Rules::Alphabeta(int &tx, int &ty, int depth, int a, int b, int player)
{
	int x, y, value;
	if (depth == 0)
		return Evaluate();
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
					Gobang::setEmpty(x, y);
					if (value > a)
					{
						a = value;
						tx = x;
						ty = y;
					}					
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
