#ifndef GOBANG_MANTOCOM_H
#define GOBANG_MANTOCOM_H

#include "Gobang_Base.h"

class ManToCom : public Gobang
{
public:
	ManToCom();
	int Judge(int x, int y);
	double Function(int len, string side1, string side2);
};

ManToCom::ManToCom()
{
	Init_Board();
}

int ManToCom::Judge(int x, int y)
{
	int i, j, tx, ty, len;
	int Side = getBoard(x, y);
	string side1, side2;
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
		Function(len, side1, side2);
	}
	return -1;
}

double ManToCom::Function(int len, string side1, string side2)
{
	double Value = 0;
	if (len >= 5)
	{
		cout << "五连" << endl; Value += 100000;
	}
	else if (len == 4)
	{
		if (side1[0] == '#' && side2[0] == '#')
		{
			cout << "活四" << endl; Value += 10000;
		}
		else if (side1[0] == '1' && side2[0] == '#' || side1[0] == '#' && side2[0] == '1')
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1[0] == '#' && side2.compare(0, 2, "#0") == 0 || side1.compare(0, 2, "#0") == 0 && side2[0] == '#')
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1[0] == '1' && side2[0] == '1')
		{
			cout << "死四" << endl; Value += 1000;
		}
	}
	else if (len == 3)
	{
		if (side1[0] == '1' && side2.compare(0, 2, "#0") == 0 || side1.compare(0, 2, "#0") == 0 && side2[0] == '1')
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1.compare(0, 2, "##") == 0 && side2.compare(0, 2, "##") == 0)
		{
			cout << "连活三" << endl; Value += 1000;
		}
		else if (side1[0] == '1' && side2.compare(0, 2, "##") == 0 || side1.compare(0, 2, "##") == 0 && side2[0] == '1')
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1.compare(0, 2, "#1") == 0 && side2.compare(0, 2, "#1") == 0)
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1[0] == '1' && side2[0] == '1')
		{
			cout << "死三" << endl; Value += 100;
		}
	}
	else if (len == 2)
	{
		if (side1 == "#00" || side2 == "#00")
		{
			cout << "冲四" << endl; Value += 5000;
		}
		else if (side1[0] == '#' && side2 == "#0#" || side1 == "#0#" && side2[0] == '#')
		{
			cout << "跳活三" << endl; Value += 1000;
		}
		else if (side1[0] == '1' && side2 == "#1#" || side1 == "#1#" && side2[0] == '1')
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1[0] == '#' && side2 == "10#" || side1 == "10#" && side2[0] == '#')
		{
			cout << "眠三" << endl; Value += 500;
		}
		else if (side1 == "##0" || side2 == "##0")
		{
			cout << "眠三" << endl; Value += 500;
		}
	}
	return Value;


}

#endif

