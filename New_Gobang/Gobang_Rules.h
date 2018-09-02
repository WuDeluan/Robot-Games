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
	int PreJudge_IsFour(int x, int y); //预判是否出现必须防守的情况
	int PreJudge_IsFive(); //预判是否有连子的可能
	int PreJudge_IsThree(int x, int y); //预判是否存在活三
	int PreJudge(int x, int y);  //搜索前的预判
	int IsLegal(int x, int y);//是否存在禁手 
	int Evaluate(int palyer); //估值函数，对某一局面的估值
	void Analysis(int x, int y);  //对某一点的估值判断
	int CreateMoveList(int depth);  //生成可能的落子点列表
	int minmaxSearch(int depth);  //极大极小值搜索算法
	int MaxSearch(int depth); //极大值搜索算法
	int MinSearch(int depth); //极小值搜索算法
	int Alphabeta(int depth, int alpha, int beta, int plyer);  //αβ剪枝算法
	int NegaScoutSearch(int depth, int alpha, int beta, int player);  //负极侦察搜索
	void MakeMove(Point move, int player);
	void MakeNullMove(Point move);
	void EmptyHashTable(); //将置换表标识置为hash_EMPTY
	int ProbeHash(int depth, int alpha, int beta, Point &bestMove); //检验置换表中元素
	void RecordHash(int depth, int val, int hashf, Point bestMove); //添加元素到置换表中
	int NegaScout_hash(int depth, int alpha, int beta, int player);  //带置换表的负极值搜索
	void ResetHistoryTable(); //清空历史得分表
	int GetHistoryScore(Point move); //获取历史得分
	void AddHistoryScore(int score, Point move); //添加得分
	void SortMoveList(int depth, int MoveCount); //对可能的着法进行排序
	int NegaScout_hash_history(int depth, int alpha, int beta, int player); //带历史得分表的负极值搜索
	void UpdateKillers(Point move, int depth); //更新杀手启发表
	int PVS(int depth, int alpha, int beta, int player);
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

//预判是否有连子的可能
int Gobang_Rules::PreJudge_IsFive()
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
					if (len >= 5)
					{
						best_move.x = m;
						best_move.y = n;
						return 1;
					}
				}
				Gobang::setEmpty(m, n);
			}
		}
	}
	return 0;
}

//预判是否出现必须防守的情况
int Gobang_Rules::PreJudge_IsFour(int x, int y)
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
			if (side1[0] == '#')
				k = 1;
			else if (side2[0] == '#')
				k = 2;
		}
		else if (len == 3)
		{
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
			if (side1.compare(0, 4, "#000") == 0)
				k = 1;
			else if (side2.compare(0, 4, "#000") == 0)
				k = 2;
		}

		if (k == 1)
		{
			best_move.x = p1.x;
			best_move.y = p1.y;
			return 1;
		}
		else if (k == 2)
		{
			best_move.x = p2.x;
			best_move.y = p2.y;
			return 2;
		}
	}
	return 0;
}

//预判是否存在活三并处理
int Gobang_Rules::PreJudge_IsThree(int x, int y)
{
	int i, j, tx, ty, len, k, value1 = 0, value2 = 0;
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
		if (len == 3)
		{
			if ((side1.compare(0, 2, "##") == 0 && side2[0] == '#') || (side1[0] == '#' && side2.compare(0, 2, "##") == 0))
				k = 1;
		}
		else if (len == 2)
		{
			if ((side1.compare(0, 3, "#0#") == 0 && side2[0] == '#') || (side2.compare(0, 3, "#0#") == 0 && side1[0] == '#'))
				k = 1;
		}
		else if (len == 1)
		{
			if ((side1.compare(0, 4, "#00#") == 0 && side2[0] == '#') || (side2.compare(0, 4, "#00#") == 0 && side1[0] == '#'))
				k = 1;
		}

		if (k == 1)
		{
			MakeMove(p1, COM);
			value1 = NegaScoutSearch(1, -INFINITY, +INFINITY, COM);
			MakeNullMove(p1);
			MakeMove(p2, COM);
			value2 = NegaScoutSearch(1, -INFINITY, +INFINITY, COM);
			MakeNullMove(p2);
			if (value1 > value2)
			{
				best_move.x = p1.x;
				best_move.y = p1.y;
			}
			else
			{
				best_move.x = p2.x;
				best_move.y = p2.y;
			}			
			return 1;
		}
	}
	return 0;
}

//搜索前的预判
int Gobang_Rules::PreJudge(int x, int y)
{
	if (PreJudge_IsFive() == 0)  //不构成连子
	{
		if (PreJudge_IsFour(x, y) == 0 && PreJudge_IsThree(x,y) == 0)  //没有必须的防守
			return 0;
	}
	return 1;
}

//是否存在禁手,存在返回0，不存在返回1
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
	}

	if (three > 1 || four > 1)
		return 0;
	else
		return 1;
}

//估值函数，对某一局面的估值
int Gobang_Rules::Evaluate(int player)
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
	if (player == WHITE)
	{
		if (TypeCount[BLACK][FIVE])
			return -9999;
		if (TypeCount[WHITE][FIVE])
			return 9999;
	}
	else
	{
		if (TypeCount[BLACK][FIVE])
			return 9999;
		if (TypeCount[WHITE][FIVE])
			return -9999;
	}

	//两个冲四等于一个活四
	if (TypeCount[COM][FFOUR] > 1)
		TypeCount[COM][FOUR]++;
	if (TypeCount[MAN][FFOUR] > 1)
		TypeCount[MAN][FOUR]++;

	int WValue = 0, BValue = 0;

	if (player == WHITE)//轮到白棋走
	{
		if (TypeCount[WHITE][FOUR])
			return 9990;//活四,白胜返回极值
		if (TypeCount[WHITE][FFOUR])
			return 9980;//冲四,白胜返回极值
		if (TypeCount[BLACK][FOUR])
			return -9970;//白无冲四活四,而黑有活四,黑胜返回极值
		if (TypeCount[BLACK][FFOUR] && TypeCount[BLACK][THREE])
			return -9960;//而黑有冲四和活三,黑胜返回极值
		if (TypeCount[WHITE][THREE] && TypeCount[BLACK][FFOUR] == 0)
			return 9950;//白有活三而黑没有四,白胜返回极值
		if (TypeCount[BLACK][THREE] > 1 && TypeCount[WHITE][FFOUR] == 0 && TypeCount[WHITE][THREE] == 0 && TypeCount[WHITE][STHREE] == 0)
			return -9940;//黑的活三多于一个,而白无四和三,黑胜返回极值
		if (TypeCount[WHITE][THREE] > 1)
			WValue += 2000;//白活三多于一个,白棋价值加2000
		else
			//否则白棋价值加200
			if (TypeCount[WHITE][THREE])
				WValue += 200;
		if (TypeCount[BLACK][THREE] > 1)
			BValue += 500;//黑的活三多于一个,黑棋价值加500
		else
			//否则黑棋价值加100
			if (TypeCount[BLACK][THREE])
				BValue += 100;
		//每个眠三加10
		if (TypeCount[WHITE][STHREE])
			WValue += TypeCount[WHITE][STHREE] * 10;
		//每个眠三加10
		if (TypeCount[BLACK][STHREE])
			BValue += TypeCount[BLACK][STHREE] * 10;
		//每个活二加4
		if (TypeCount[WHITE][TWO])
			WValue += TypeCount[WHITE][TWO] * 4;
		//每个活二加4
		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][TWO] * 4;
		//每个眠二加1
		if (TypeCount[WHITE][STWO])
			WValue += TypeCount[WHITE][STWO];
		//每个眠二加1
		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][STWO];
	}
	else//轮到黑棋走
	{
		if (TypeCount[BLACK][FOUR])
			return 9990;//活四,黑胜返回极值
		if (TypeCount[BLACK][FFOUR])
			return 9980;//冲四,黑胜返回极值
		if (TypeCount[WHITE][FOUR])
			return -9970;//活四,白胜返回极值
		if (TypeCount[WHITE][FFOUR] && TypeCount[WHITE][THREE])
			return -9960;//冲四并活三,白胜返回极值
		if (TypeCount[BLACK][THREE] && TypeCount[WHITE][FFOUR] == 0)
			return 9950;//黑活三,白无四。黑胜返回极值
		if (TypeCount[WHITE][THREE] > 1 && TypeCount[BLACK][FFOUR] == 0 && TypeCount[BLACK][THREE] == 0 && TypeCount[BLACK][STHREE] == 0)
			return -9940;//白的活三多于一个,而黑无四和三,白胜返回极值
			//黑的活三多于一个,黑棋价值加2000
		if (TypeCount[BLACK][THREE] > 1)
			BValue += 2000;
		else
			//否则黑棋价值加200
			if (TypeCount[BLACK][THREE])
				BValue += 200;

		//白的活三多于一个,白棋价值加 500
		if (TypeCount[WHITE][THREE] > 1)
			WValue += 500;
		else
			//否则白棋价值加100
			if (TypeCount[WHITE][THREE])
				WValue += 100;

		//每个眠三加10
		if (TypeCount[WHITE][STHREE])
			WValue += TypeCount[WHITE][STHREE] * 10;
		//每个眠三加10
		if (TypeCount[BLACK][STHREE])
			BValue += TypeCount[BLACK][STHREE] * 10;

		//每个活二加4
		if (TypeCount[WHITE][TWO])
			WValue += TypeCount[WHITE][TWO] * 4;
		//每个活二加4
		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][TWO] * 4;

		//每个眠二加1
		if (TypeCount[WHITE][STWO])
			WValue += TypeCount[WHITE][STWO];
		//每个眠二加1
		if (TypeCount[BLACK][STWO])
			BValue += TypeCount[BLACK][STWO];
	}

	//加上所有棋子的位置价值
	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			Side = Gobang::getBoard(x, y);
			if (Side != EMPTY)
				if (Side == BLACK)
					BValue += PosValue[x][y];
				else
					WValue += PosValue[x][y];
		}
	}

	//返回估值
	if (player == WHITE)
		return WValue - BValue;
	else
		return BValue - WValue;
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
				else if ((side1.compare(0, 2, "##") == 0 && side2[0] == '#' )||( side1[0] == '#' && side2.compare(0, 2, "##") == 0))
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

void Gobang_Rules::MakeMove(Point move, int player)
{
	Gobang::setBoard(move.x, move.y, player);
}

void Gobang_Rules::MakeNullMove(Point move)
{
	Gobang::setEmpty(move.x, move.y);
}

//创建可能的落子列表
int Gobang_Rules::CreateMoveList(int depth)
{
	int x, y;
	int MoveCount = 0;

	if (Killers[depth][0].score != -1) //如果存在启发点，加入列表前端
		MoveList[depth][MoveCount++].move = Killers[depth][0].move;
		if(Killers[depth][1].score != -1)
			MoveList[depth][MoveCount++].move = Killers[depth][1].move;

	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			//位置为空，且周围3×3范围内有棋子
			if (Gobang::getBoard(x, y) == EMPTY && Gobang::IsNeighbor(x, y))
			{
				Gobang::setBoard(x, y, COM);
				if (IsLegal(x, y))
				{
					MoveList[depth][MoveCount].move.x = x;
					MoveList[depth][MoveCount].move.y = y;
					MoveCount++;
				}
				Gobang::setEmpty(x, y);
			}
		}
	}
	return MoveCount;
}

//极大极小值搜索算法
int Gobang_Rules::minmaxSearch(int depth)
{
	int bestValue = -INFINITY;
	int i, MoveCount;
	Point bestMove;
	if (depth == 0)
		return Evaluate(COM);
	else
	{
		MoveCount = CreateMoveList(depth);
		for (i = 0; i < MoveCount; i++)
		{
			MakeMove(MoveList[depth][i].move, COM); //生成棋面
			int value = MinSearch(depth - 1);
			MakeNullMove(MoveList[depth][i].move); //恢复棋面
			if (value > bestValue)
			{
				bestValue = value;
				bestMove = MoveList[depth][i].move;
			}
			else if (value == bestValue)
				bestMove = MoveList[depth][i].move;
		}
	}
	best_move = bestMove;
}

//极大值搜索算法
int Gobang_Rules::MaxSearch(int depth)
{
	int bestValue = -INFINITY, i;
	int MoveCount, value;
	if (depth == 0)
		return Evaluate(COM);
	else
	{
		MoveCount = CreateMoveList(depth);
		for (i = 0; i < MoveCount; i++)
		{
			MakeMove(MoveList[depth][i].move, COM);
			value = MinSearch(depth - 1);
			MakeNullMove(MoveList[depth][i].move);
			if (value > bestValue)
				bestValue = value;
		}
	}
	return bestValue;
}

//极小值搜索算法
int Gobang_Rules::MinSearch(int depth)
{
	int bestValue = INFINITY, i;
	int MoveCount, value;
	if (depth == 0)
		return Evaluate(COM);
	else
	{
		MoveCount = CreateMoveList(depth);
		for (i = 0; i < MoveCount; i++)
		{
			MakeMove(MoveList[depth][i].move, MAN);
			value = MaxSearch(depth - 1);
			MakeNullMove(MoveList[depth][i].move);
			if (value < bestValue)
				bestValue = value;
		}
	}
	return bestValue;
}

//αβ剪枝搜索算法
int Gobang_Rules::Alphabeta(int depth, int alpha, int beta, int player)
{
	int i, value, MoveCount;
	if (depth == 0)
		return Evaluate(COM);
	if (player == COM)
	{
		MoveCount = CreateMoveList(depth);
		for (i = 0; i < MoveCount; i++)
		{

			MakeMove(MoveList[depth][i].move, COM);
			value = Alphabeta(depth - 1, alpha, beta, MAN);
			MakeNullMove(MoveList[depth][i].move);
			if (value > alpha)
			{
				alpha = value;
				best_move = MoveList[depth][i].move;
			}
			if (alpha >= beta)
				return alpha;

		}
		return alpha;
	}
	else if (player == MAN)
	{
		MoveCount = CreateMoveList(depth);
		for (i = 0; i < MoveCount; i++)
		{

			MakeMove(MoveList[depth][i].move, MAN);
			value = Alphabeta(depth - 1, alpha, beta, COM);
			MakeNullMove(MoveList[depth][i].move);
			if (value < beta)
				beta = value;
			if (beta <= alpha)
				return beta;
		}
		return beta;
	}
}

//负值侦察算法
int Gobang_Rules::NegaScoutSearch(int depth, int alpha, int beta, int player)
{
	static int max_depth = depth;
	int i, value, MoveCount;

	if (depth == 0)
		return Evaluate(player);

	MoveCount = CreateMoveList(depth);
	for (i = 0; i < MoveCount; i++)
	{
		MakeMove(MoveList[depth][i].move, player);
		value = -NegaScoutSearch(depth - 1, -beta, -alpha, notplayer(player));
		MakeNullMove(MoveList[depth][i].move);
		if (value >= beta)
			return beta;
		if (value > alpha)
		{
			alpha = value;
			if (depth == max_depth)
				best_move = MoveList[depth][i].move;
		}
	}
	return alpha;
}

//将置换表标识置为hash_EMPTY
void Gobang_Rules::EmptyHashTable()
{
	memset(hashTable, 0, sizeof(HASH)*TableSize);
}

//校验置换表中的元素
int Gobang_Rules::ProbeHash(int depth, int alpha, int beta, Point &bestMove) {
	HASH *phash = &hashTable[ZobristKey & (TableSize - 1)];
	if (phash->key == ZobristKey) {
		if (phash->depth >= depth) {
			if (phash->flags == hash_EXACT) {
				return phash->value;
			}
			if ((phash->flags == hash_ALPHA) && (phash->value <= alpha)) {
				return alpha;
			}
			if ((phash->flags == hash_BETA) && (phash->value >= beta)) {
				return beta;
			}
		}
		//RememberBestMove
		bestMove = phash->best;
	}
	return valUNKNOWN;
}

//添加元素到置换表中
void Gobang_Rules::RecordHash(int depth, int val, int hashf, Point bestMove) {
	HASH *phash = &hashTable[ZobristKey & (TableSize - 1)];
	if (phash->flags != hash_EMPTY && phash->depth > depth)
		return;

	phash->key = ZobristKey;
	phash->best = bestMove;
	phash->value = val;
	phash->flags = hashf;
	phash->depth = depth;
}

//加入置换表的负值侦察搜索
int Gobang_Rules::NegaScout_hash(int depth, int alpha, int beta, int player)
{
	static int max_depth = depth;
	int i, value, MoveCount;
	Point bestMove;

	int hashf = hash_ALPHA;
	if ((value = ProbeHash(depth, alpha, beta, bestMove)) != valUNKNOWN)
		return value;

	if (depth == 0)
	{
		value = Evaluate(player);
		RecordHash(depth, value, hash_EXACT, bestMove);
		return value;
	}

	MoveCount = CreateMoveList(depth);
	for (i = 0; i < MoveCount; i++)
	{
		MakeMove(MoveList[depth][i].move, player);
		value = -NegaScout_hash(depth - 1, -beta, -alpha, notplayer(player));
		MakeNullMove(MoveList[depth][i].move);
		if (value >= beta)
		{
			RecordHash(depth, value, hash_BETA, MoveList[depth][i].move);
			return beta;
		}
		if (value > alpha)
		{
			hashf = hash_EXACT;
			alpha = value;
			//bestMove = MoveList[depth][i].move;
			if (depth == max_depth)
				best_move = MoveList[depth][i].move;
		}

	}

	RecordHash(depth, alpha, hashf, MoveList[depth][i].move);
	return alpha;
}

//获取历史得分
int Gobang_Rules::GetHistoryScore(Point move)
{
	return historyTable[move.x][move.y];
}

//添加得分
void Gobang_Rules::AddHistoryScore(int depth, Point move)
{
	historyTable[move.x][move.y] += 2;
}

void Gobang_Rules::SortMoveList(int depth, int MoveCount)
{
	int i;
	for (i = 0; i < MoveCount; i++)
		MoveList[depth][i].score = GetHistoryScore(MoveList[depth][i].move);

	Gobang::MergeSort(MoveList[depth], MoveCount);
}

int Gobang_Rules::NegaScout_hash_history(int depth, int alpha, int beta, int player)
{
	static int max_depth = depth;
	int i, value, MoveCount;
	Point bestMove;
	int bestValue = -1;

	int hashf = hash_ALPHA;
	if ((value = ProbeHash(depth, alpha, beta, bestMove)) != valUNKNOWN)
		return value;

	if (depth == 0)
	{
		value = Evaluate(player);
		RecordHash(depth, value, hash_EXACT, bestMove);
		return value;
	}

	MoveCount = CreateMoveList(depth);
	SortMoveList(depth, MoveCount);

	for (i = 0; i < MoveCount; i++)
	{
		MakeMove(MoveList[depth][i].move, player);
		value = -NegaScout_hash_history(depth - 1, -beta, -alpha, notplayer(player));
		MakeNullMove(MoveList[depth][i].move);
		if (value >= beta)
		{
			RecordHash(depth, value, hash_BETA, MoveList[depth][i].move);
			AddHistoryScore(depth, MoveList[depth][i].move);
			return beta;
		}
		if (value > alpha)
		{
			hashf = hash_EXACT;
			alpha = value;
			bestValue = i;
			if (depth == max_depth)
				best_move = MoveList[depth][i].move;
		}

	}
	if (bestValue != -1)
		AddHistoryScore(depth, MoveList[depth][i].move);
	RecordHash(depth, alpha, hashf, MoveList[depth][i].move);
	return alpha;
}

void Gobang_Rules::UpdateKillers(Point move, int depth)
{
	if (Killers[depth][0].score != -1) //如果已经存入一个启发点
	{
		if (Killers[depth][0].move.x != move.x || Killers[depth][0].move.y != move.y) //且与当前点不同
		{
			//更新第二个启发点
			Killers[depth][1].move = Killers[depth][0].move; 
			Killers[depth][1].score = +INFINITY - 1; //赋值便于排序
		}
	}
	//更新第一个启发点
	Killers[depth][0].move = move;
	Killers[depth][0].score = +INFINITY;
}

int Gobang_Rules::PVS(int depth, int alpha, int beta, int player)
{
	static int max_depth = depth;
	int i, value, MoveCount, current;
	bool foundPV = false;
	
	if (depth == 0)
		return Evaluate(player);

	MoveCount = CreateMoveList(depth);
	for (i = 0; i < MoveCount; i++)
	{
		MakeMove(MoveList[depth][i].move, player);		
		if (foundPV) 
		{
			value = -PVS(depth - 1, -alpha - 1, -alpha, notplayer(player));
			if ((value > alpha) && (value < beta)) 
			{ // 检查失败
				value = -PVS(depth - 1, -beta, -value, notplayer(player));
			}
		}
		else
			value = -PVS(depth - 1, -beta, -alpha, notplayer(player));
		MakeNullMove(MoveList[depth][i].move);
		
		if (value >= beta)					
			return value;

		if (value > alpha)
		{
			alpha = value;
			foundPV = true;
			if (depth == max_depth)
				best_move = MoveList[depth][i].move;
		}
	}
	return alpha;
}


#endif

