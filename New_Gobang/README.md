# 五子棋

## Aug 18 2018


### 1.构造基本功能函数
   - void Print_Checkerboard() //打印棋盘 
   - int setBoard(int x, int y, int Piece_Color) //落子，x,y为位置坐标，Piece_Color为棋子颜色 
   - int setEmpty(int x, int y) //置空 
   - int getBoard(int x, int y) //返回当前位置的棋子颜色 
   - int setBack() //撤销操作
   - int IsWin(int x,int y) //是否连成五子
### 2.构造指定开局、三手交换
   - 指定开局:SpecificOpening() //程序中保存26种开局的白3位置坐标，由随机数产生开局
   - 三手交换判断：WhetherChange(Point step[]) //程序保存需进行交换的开局情况，若匹配则交换
   
   
   
## Aug 19 2018


### 1.五手N打
   - WhiteFour() //白4在（6，8）范围内有随机数产生
   - BlackFive(int &x, int &y) //黑5打点坐标，暂由随机数在（5，9）范围内给出
   - SaveOnePoint(int &x,int &y) //打点选择，暂为保留第一个点
### 2.构造交互函数
   - void Opening() 
   <br>void ForthStep()
   <br>void FifthStep()




## Aug 20 2018  &  Aug 21 2018
 
 
### 1.预判断函数 
   - int PreJudge(int &x, int &y)
      对方落子后，若形成活三、冲四等情况，必须进行防守
### 2.估值函数
   - Eval(int x, int y) //对给出的某一点进行四个方向上的搜索，并记录连子情况
   - Function(int len, string side1, string side2) //对连子的两端进行判断，给出估计值
### 3.极大极小值搜索
   - minmaxSearch(int depth, int &tx, int &ty)
     <br>MaxSearch(int depth, int tx, int ty)
     <br>MinSearch(int depth, int tx, int ty)
