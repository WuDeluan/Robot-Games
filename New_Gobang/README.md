# 五子棋



## Aug 18 2018


### 1.构造基本功能函数
   - void Print_Checkerboard()   //打印棋盘 
   - int setBoard(int x, int y, int Piece_Color)   //落子，x,y为位置坐标，Piece_Color为棋子颜色 
   - int setEmpty(int x, int y)   //置空 
   - int getBoard(int x, int y)   //返回当前位置的棋子颜色 
   - int setBack()   //撤销操作
   - int IsWin(int x,int y)   //是否连成五子
### 2.构造指定开局、三手交换
   - 指定开局: SpecificOpening()   //程序中保存26种开局的白3位置坐标，由随机数产生开局
   - 三手交换判断： WhetherChange(Point step[])   //程序保存需进行交换的开局情况，若匹配则交换
   
   
   
## Aug 19 2018


### 1.五手N打
   - WhiteFour()   //白4在（6，8）范围内有随机数产生
   - BlackFive(int &x, int &y)   //黑5打点坐标，暂由随机数在（5，9）范围内给出
   - SaveOnePoint(int &x,int &y)   //打点选择，暂为保留第一个点
### 2.构造交互函数
   - void Opening() 
   - void ForthStep()
   - void FifthStep()



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
     简单遍历整个棋盘，找到空的棋盘位置进行递归搜索，返回估值。由于估值函数太过粗糙，搜索结果糟糕。且当层数加深时，搜索时间较长，搜索效率极低。
     <br>经简单测试，当depth=3时，约需30min给出测试局面的结果。
     
     
     
## Aug 22 2018


### 1.AlphaBeta剪枝搜索
   - int Alphabeta(int &tx, int &ty,int depth, int a, int b,int player)
   <br>传入tx、ty用于存储最佳着法的位置坐标，搜索深度depth，alpha、beta初值设为-INFINITY、+INFINITY,执子方player。
   ```cpp
   //AlphaBeta伪代码
    int Alphabeta(int depth, int alpha, int beta, int player)
    {
	      if (depth == 0)
		       return Evaluate();
	      if (player == COM)
	      {
               MakeMove();
			      value = Alphabeta(depth - 1, alpha, beta, MAN);
			      UnMakeMove();
			      if (value > alpha)
			      {
				      alpha = value;
                  RecordMove();
			      }
			      if (alpha >= beta)
			      	return alpha;
		      return alpha;
	      }
	      else if (player == MAN)
	      {
		         MakeMove();
			      value = Alphabeta(depth - 1, alpha, beta, COM);
			      UnMakeMove();
			      if (value < beta)
			      	beta = value;
			      if (beta <= alpha)
			      	return beta;
		      return beta;
	      }
      }
  ``` 
### 2.其他交互函数
   - Continue()  //执行黑5之后的操作交互
   - Print_Menu1()  //给出人人对弈的界面，方便后续测试
   
   
   
## Aug 23 2018


### 1.修改估值函数
   - int Eveluate();
   - int Analysis(int x, int y);
   <br>    通过查阅资料和参考其他程序代码，修改估值函数，使估值函数对整个局面进行估值，而不是简单的对某一结点周围的局面进行评估。分析时，查找当前
   <br>局面的非空坐标点，获取棋子颜色，对其四个方向上的连子类型进行分析判断，将结果保存于数组`int ypeRecord[15][15][4];`（数组下标分别表示
   <br>位置坐标x、y和方向标记。分析完毕后，对数组`TypeRecord[15][15][4];`进行统计，结果保存在`int TypeCount[2][15];`中（数组下标分别
   <br>表示棋子颜色，连子类型标记).根据数组`TypeCount[2][15];`，对双方进行估值计算，并根据位置重要性价值表`PosValue[15][15]`丰富估计值，
   <br>最后返估计值。
   <br>    估值函数始终返回对电脑方的评价值
   
   
   
## Aug 24 2018


### 1.修改预判断函数
   - int PreJudge_IsFive(int &x, int &y);   //预判是否有连子的可能
   - int PreJudge_IsFour(int &x, int &y);   //预判是否出现必须防守的情况
   <br>在进行搜索算法之前，先判断棋盘的空位中，是否有一处可以使我方连成五子的情况，若有则直接落子。若无，则判断敌方是否有冲四等必须防守的情况，
   <br>若有，则直接落子（这里不直接处理活三的情况，而是通过搜索算法给出）。   
### 2.禁手判断
   - int IsLegal(int x, int y);   //是否存在禁手
   <br>如果存在禁手，则不对该位置进行搜索。
   <br>同时在搜索函数中添加禁手判断函数；在敌方落子后进行禁手判断。
   
   
   
## Aug 25 2018


### 1.负值侦察搜索
   - int NegaScoutSearch(int depth, int alpha, int beta, int player)
   ```cpp
      //负值侦察伪代码
       int NegaScoutSearch(int depth, int alpha, int beta, int player)
       {
	          if (depth == 0)
		            return Evaluate(player);
               MakeMove();
		         value = -NegaScoutSearch(depth - 1, -beta, -alpha, notplayer(player));
		         UnMakeMove();
		         if (value >= beta)
			        return beta;
		         if (value > alpha)
		       {
			        alpha = value;
			        if (depth == max_depth)
                   RecordMove();  
		        }     
	       return alpha;
        }
   ```
   - 负值侦察在Alphabeta的基础上进行修改。当函数递归时，Alpha和Beta不但取负数而且位置交换了。这样就使函数值在每一次递归中改变评价的角度，
    <br>以反映双方棋手的交替着子，并且它们的目标是对立的。所以，相应的估值函数在返回值应与形成估值局面的棋子颜色相对应，而不只是对电脑方。
    - max_depth由 `static int max_depth = depth;` 定义，当达到最大搜索层，且更新alpha时，保存位置。    
### 2.修改估值函数
   - int Evaluate(int player)
   <br>    根据负值侦察的要求，向估值函数中传入执子方。根据执子方进行相应的估值。当执子方为COM时，返回`com_value - man_Value`,反之，返回
   <br>`man_Value - com_Value`。
   <br>    将AlphaBeta中估值函数的参数player始终置为COM




### Aug 26 2018

## 1.置换表
 - U64 rand64(); //随机生成64位校验码
 ```cpp
   U64 rand64()
	{
		return rand() ^ ((U64)rand() << 15) ^ ((U64)rand() << 30) ^ ((U64)rand() << 45) ^ ((U64)rand() << 60);
	}
  ```
  - 主置换表是一个散列数组，每个散列项看上去像这样：
  ```cpp
        typedef struct tagHASH {
	      U64 key;  //64位校验码
	      int depth;  //深度
	      int flags;  //数据类型标记（hash_EXACT, hash_ALPHA, hash_BETA）
	      int value;  //估值
	      Point best;  //有利落子点
      } HASH;
  ```
  - void InitializeHashKey(); //初始化检验码
  - void RecordHash(int depth, int val, int hashf, Point bestMove); //添加元素到置换表中
  - int ProbeHash(int depth, int alpha, int beta, Point &bestMove); //检验置换表中元素
  ```cpp
       int ProbeHash(int depth, int alpha, int beta, Point &bestMove) {
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
		      bestMove = phash->best;
	      }
	      return valUNKNOWN;
      }
   ```
  
 ### 2.加入置换表的负值侦察函数
 ```cpp
       /加入置换表的负值侦察搜索
      intNegaScout_hash(int depth, int alpha, int beta, int player)
      {
	         int hashf = hash_ALPHA;
	         if ((value = ProbeHash(depth, alpha, beta, bestMove)) != valUNKNOWN)
		         return value;

	         if (depth == 0)
	         {
		         value = Evaluate(player);
	         	RecordHash(depth, value, hash_EXACT, bestMove);
	         	return value;
	         }
               MakeMove();
		         value = -NegaScout_hash(depth - 1, -beta, -alpha, notplayer(player));
		         UnMakeMove();
		         if (value >= beta)
		         {
			         RecordHash(depth, value, hash_BETA, bestMove);
			         return beta;
		         }
		         if (value > alpha)
		         {
		         	hashf = hash_EXACT;
		         	alpha = value;
			         RecordMove()
			         if (depth == max_depth)
			          RecordBestMove()
		         }

	         }
	         RecordHash(depth, alpha, hashf, bestMove);
	         return alpha;
         }
 
 ```
 
 
 ## Aug 17 2018
 
 ### 1.裁剪棋盘
    - int IsNeighbor(int tx, int ty)   //位置周围3×3范围内是否有棋子
    - int Gobang_Rules::CreateMoveList(int depth)   //创建可能的落子列表
    <br>在搜索前，遍历整个棋盘，找到棋盘范围内位置为空，周围3×3范围内有棋子，且落子后无禁手的位置，保存至数组`MoveList[depth][MoveCount]`
    <br>(数组下标表示所在深度、合理着法位置的数量标记）。
 ### 2.修改搜索函数
     <br>将搜索函数中用于遍历全盘的代码改为遍历`Movelist`。
