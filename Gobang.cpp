#include "Gobang_Base.h"

int main()
{
	char x, y;
	Gobang G = Gobang();
	G.Print_Checkerboard();
	while (1)
	{
		while(true){
			cout << "请黑方落子：";
			cin >> x;
			cin >> y; 
			if (G.setBoard(x, y, BLACK) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		} 
		G.Print_Checkerboard();
		if (G.IsWin(x, y) == 1)
			cout << "黑方获胜!" << endl;
		while (true) {
			cout << "请白方落子：";
			cin >> x;
			cin >> y;
			if (G.setBoard(x, y, WHITE) == -1)
				cout << "请选择正确的位置落子！" << endl;
			else
				break;
		}
		G.Print_Checkerboard();
		if (G.IsWin(x, y) == 1)
			cout << "白方获胜!" << endl;
	}

}
