#ifndef TICTACTOE_H_INCLUDED
#define TICTACTOE_H_INCLUDED
#include<winbgim.h>
#include<cstdlib>
#include<stdio.h>
#include<iostream>
#include<ctime>

using namespace std;

const int TOP = 100;
const int LEFT = 100;
const int RIGHT = 700;
const int BOTTOM =700;
const int WIDTH = 800;
const int HEIGHT =800;
const int STEP = 200;
const int SPACE = 20;

const int INFINITY = 1000;
const int WIN = INFINITY;
const int LOSE = -INFINITY;
const int DRAW = 0;
const int POSITIONVALUE[3][3] = {{3,2,3},{2,4,2},{3,2,3}};

class TicTacToe
{
public:
    TicTacToe();
    void Init();
    void DrawBoard();
    void DrawX(int x,int y);
    void DrawO(int x,int y);
    void SetSide(int side,int x,int y);
    bool IsWin();
    bool IsFull();
    bool IsLeagle(int x,int y);
    int Value();
    void PlayManToMan();
    void PlayComputerToMan();
    void PlayComputerToComputer();
    int MiniMaxSearch(int depth);
    int MiniSearch(int depth);
    int MaxSearch(int depth);

private:
    int board[3][3];
    int side;
    int depth;
};



#endif // TICTACTOE_H_INCLUDED

#include"TicTacToe.h"

void TicTacToe::Init()
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            board[i][j]=0;
        }
    }
    side = 1;
    depth = 9;
}

TicTacToe::TicTacToe()
{
    Init();
    //board[1][1] = -1;
}

//Draw Board
void TicTacToe::DrawBoard()
{
    line(LEFT + STEP, TOP, LEFT + STEP, BOTTOM);
    line(LEFT + 2*STEP, TOP, LEFT + 2*STEP, BOTTOM);
    line(LEFT, TOP + STEP, RIGHT, TOP + STEP);
    line(LEFT, TOP + 2*STEP, RIGHT, TOP + 2*STEP);

    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j]==1)
            {
                DrawX(i,j);
            }
            else if(board[i][j]==-1)
            {
                DrawO(i,j);
            }
        }
    }
}

void TicTacToe::DrawX(int x,int y)
{
    line(x*STEP + LEFT + SPACE, y*STEP + TOP + SPACE, (x+1)*STEP + LEFT - SPACE, (y+1)*STEP + TOP - SPACE);
    line(x*STEP + LEFT + SPACE, (y+1)*STEP + TOP - SPACE, (x+1)*STEP + LEFT - SPACE, y*STEP + TOP + SPACE);
}

void TicTacToe::DrawO(int x,int y)
{
    circle(x*STEP + STEP/2 + LEFT, y*STEP + STEP/2 + TOP, STEP/2 - SPACE);
}

void TicTacToe::SetSide(int side,int x,int y)
{
    board[x][y] = side;
}

bool TicTacToe::IsFull()
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool TicTacToe::IsLeagle(int x,int y)
{
    if(board[x][y] == 0)
    {
        return true;
    }
    return false;
}

bool TicTacToe::IsWin()
{
    if(board[0][0] + board[1][1] + board[2][2] == 3*side)
    {
        return true;
    }
    if(board[0][2] + board[1][1] + board[2][0] == 3*side)
    {
        return true;
    }
    if(board[0][0] + board[0][1] + board[0][2] == 3*side)
    {
        return true;
    }
    if(board[1][0] + board[1][1] + board[1][2] == 3*side)
    {
        return true;
    }
    if(board[2][0] + board[2][1] + board[2][2] == 3*side)
    {
        return true;
    }
    if(board[0][0] + board[1][0] + board[2][0] == 3*side)
    {
        return true;
    }
    if(board[0][1] + board[1][1] + board[2][1] == 3*side)
    {
        return true;
    }
    if(board[0][2] + board[1][2] + board[2][2] == 3*side)
    {
        return true;
    }
    return false;
}

void TicTacToe::PlayManToMan()
{
    DrawBoard();
    int x,y;
    while(true)
    {

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x = mousex();
            y = mousey();

            if(x<TOP || x>BOTTOM || x<LEFT || x>RIGHT)
            {
                clearmouseclick(WM_LBUTTONDOWN);
                cleardevice();
                continue;
            }
            if(y<TOP || y>BOTTOM || y<LEFT || y>RIGHT)
            {
                clearmouseclick(WM_LBUTTONDOWN);
                cleardevice();
                continue;
            }
            if(IsLeagle((x-LEFT)/STEP,(y-TOP)/STEP))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                cleardevice();
                SetSide(side,(x-LEFT)/STEP,(y-TOP)/STEP);
                //cout<<" x= "<<x;
                if(IsWin())
                {
                    if(side == 1)
                    {
                        outtextxy(20,20,const_cast<char*>("red wins"));
                        DrawBoard();
                        break;
                    }
                    else
                    {
                        outtextxy(20,20,const_cast<char*>("blue wins"));
                        DrawBoard();
                        break;
                    }
                }
                if(IsFull())
                {
                    outtextxy(20,20,const_cast<char*>("draw"));
                    DrawBoard();
                    break;
                }
                cout<<Value()<<endl;
                clearmouseclick(WM_LBUTTONDOWN);
                cleardevice();
                side = side * (-1);
                DrawBoard();
            }
            else
            {
                clearmouseclick(WM_LBUTTONDOWN);
                cleardevice();
                DrawBoard();
            }
        }
    }
}

void TicTacToe::PlayComputerToMan()
{
    DrawBoard();
    int x,y;
    while(1)
    {
        if(side == 1)
        {
            int value = MiniMaxSearch(depth);

            cout<<"value = "<<value<<endl;
            x = value/3;
            y = value%3;
            board[x][y] = 1;

            //system("pause");
            DrawBoard();

            if(IsWin())
            {
                outtextxy(20,20,const_cast<char*>("blue wins"));
                DrawBoard();
                break;

            }
            if(IsFull())
            {
                outtextxy(20,20,const_cast<char*>("draw"));
                DrawBoard();
                break;
            }
            side*= -1;

        }

        else
        {
            delay(10);

            if(ismouseclick(WM_LBUTTONUP))
            {
                x = mousex();
                y = mousey();

                if(x<TOP || x>BOTTOM || x<LEFT || x>RIGHT)
                {
                    //clearmouseclick(WM_LBUTTONUP);
                    continue;
                }
                if(y<TOP || y>BOTTOM || y<LEFT || y>RIGHT)
                {
                    //clearmouseclick(WM_LBUTTONUP);
                    continue;
                }
                if(IsLeagle((x-LEFT)/STEP,(y-TOP)/STEP))
                {

                    SetSide(-1,(x-LEFT)/STEP,(y-TOP)/STEP);
                    //cout<<" x= "<<x;
                    if(IsWin())
                    {
                        outtextxy(20,20,const_cast<char*>("blue wins"));
                        DrawBoard();
                        break;

                    }
                    if(IsFull())
                    {
                        outtextxy(20,20,const_cast<char*>("draw"));
                        DrawBoard();
                        break;
                    }
                    cout<<Value()<<endl;
                    DrawBoard();
                    side*= -1;
                    clearmouseclick(WM_LBUTTONUP);
                }

            }
        }
    }
}

void TicTacToe::PlayComputerToComputer()
{
    DrawBoard();
    int x,y;
    while(1)
    {
        delay(1000);
        if(side == 1)
        {
            int value = MiniMaxSearch(depth);

            cout<<"value = "<<value<<endl;
            x = value/3;
            y = value%3;
            board[x][y] = 1;


            //system("pause");
            DrawBoard();

            if(IsWin())
            {
                outtextxy(20,20,const_cast<char*>("blue wins"));
                DrawBoard();
                break;

            }
            if(IsFull())
            {
                outtextxy(20,20,const_cast<char*>("draw"));
                DrawBoard();
                break;
            }
            side*= -1;

        }
        delay(1000);
        if(side == -1)
        {
            int value = MiniMaxSearch(depth);

            cout<<"value = "<<value<<endl;
            x = value/3;
            y = value%3;
            board[x][y] = -1;

            //system("pause");
            DrawBoard();

            if(IsWin())
            {
                outtextxy(20,20,const_cast<char*>("blue wins"));
                DrawBoard();
                break;

            }
            if(IsFull())
            {
                outtextxy(20,20,const_cast<char*>("draw"));
                DrawBoard();
                break;
            }
            side*= -1;

        }
        delay(1000);
    }
}

int TicTacToe::Value()
{
    int sideValue = 0;
    int opSideValue = 0;
    int i,j;
    int valueBoard[3][3];
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j] == 0)
            {
                valueBoard[i][j] = side;
            }
            else
            {
                valueBoard[i][j] = board[i][j];
            }
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j] == side)
            {
                sideValue+= POSITIONVALUE[i][j];
            }

        }
    }
    if(valueBoard[0][0] + valueBoard[0][1] + valueBoard[0][2] == 3*side)
    {
        sideValue+=1;
    }
    if(valueBoard[1][0] + valueBoard[1][1] + valueBoard[1][2] == 3*side)
    {
        sideValue+=1;
    }
    if(valueBoard[2][0] + valueBoard[2][1] + valueBoard[2][2] == 3*side)
    {
        sideValue+=1;
    }
    if(valueBoard[0][0] + valueBoard[1][0] + valueBoard[2][0] == 3*side)
    {
        sideValue+=1;
    }
    if(valueBoard[0][1] + valueBoard[1][1] + valueBoard[2][1] == 3*side)
    {
        sideValue+=1;
    }
    if(valueBoard[0][2] + valueBoard[1][2] + valueBoard[2][2] == 3*side)
    {
        sideValue+=1;
    }
    if(valueBoard[0][0] + valueBoard[1][1] + valueBoard[2][2] == 3*side)
    {
        sideValue+=1;
    }
    if(valueBoard[2][0] + valueBoard[1][1] + valueBoard[0][2] == 3*side)
    {
        sideValue+=1;
    }

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j] == 0)
            {
                valueBoard[i][j] = -side;
            }
            else
            {
                valueBoard[i][j] = board[i][j];
            }
        }
    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(board[i][j] == -side)
            {
                opSideValue+= POSITIONVALUE[i][j];
            }

        }
    }
    if(valueBoard[0][0] + valueBoard[0][1] + valueBoard[0][2] == 3*(-side))
    {
        opSideValue+=1;
    }
    if(valueBoard[1][0] + valueBoard[1][1] + valueBoard[1][2] == 3*(-side))
    {
        opSideValue+=1;
    }
    if(valueBoard[2][0] + valueBoard[2][1] + valueBoard[2][2] == 3*(-side))
    {
        opSideValue+=1;
    }
    if(valueBoard[0][0] + valueBoard[1][0] + valueBoard[2][0] == 3*(-side))
    {
        opSideValue+=1;
    }
    if(valueBoard[0][1] + valueBoard[1][1] + valueBoard[2][1] == 3*(-side))
    {
        opSideValue+=1;
    }
    if(valueBoard[0][2] + valueBoard[1][2] + valueBoard[2][2] == 3*(-side))
    {
        opSideValue+=1;
    }
    if(valueBoard[0][0] + valueBoard[1][1] + valueBoard[2][2] == 3*(-side))
    {
        opSideValue+=1;
    }
    if(valueBoard[2][0] + valueBoard[1][1] + valueBoard[0][2] == 3*(-side))
    {
        opSideValue+=1;
    }
    return sideValue - opSideValue;
}

int TicTacToe::MaxSearch(int depth)
{
    int best = -1000;
    int i,j;
    if(depth==0 || IsFull())
    {
        return Value();
    }
    else
    {
        int g;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(board[i][j] == 0)
                {
                    board[i][j] = side;
                    g = MiniSearch(depth - 1);;

                    if(g>best)
                    {
                        best = g;
                    }
                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
}

int TicTacToe::MiniSearch(int depth)
{
    int best = 1000;
    if(depth==0 || IsFull());

    {
        return Value();
    }
    else
    {
        int g;
        int i,j;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(board[i][j] == 0)
                {
                    board[i][j] = -side;
                    g = MaxSearch(depth - 1);
                    if(g<best)
                    {
                        best = g;
                    }
                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
}

int TicTacToe::MiniMaxSearch(int depth)
{
    int best = -1000;
    int i,j;
    if(depth==0 || IsFull())
    {
        return Value();
    }
    else
    {
        int g;
        int x,y;
        for(i=0;i<3;i++)
        {
            for(j=0;j<3;j++)
            {
                if(board[i][j] == 0)
                {
                    board[i][j] = side;
                    g = MiniSearch(depth - 1);
                    if(g>best)
                    {
                        best = g;
                        x = i;
                        y = j;
                    }
                    board[i][j] = 0;
                }
            }
        }
        return 3*x + y;
    }
}

#include<iostream>
#include"TicTacToe.h"
using namespace std;

void Play();

int main()
{
    initwindow(WIDTH,HEIGHT,"TicTacToe");
    Play();
    system("pause");
    return 0;
}

void Play()
{
    TicTacToe t;
    int select;
    cout<<"1. Man To Man"<<endl;
    cout<<"2. Computer To Man"<<endl;
    cout<<"3. Computer To Computer"<<endl;
    cout<<"Please input select:"<<endl;
    while(cin>>select)
    {
        if(select<0)
        {
            break;
        }
        switch(select)
        {
        case 1:
            t.PlayManToMan();
            break;
        case 2:
            t.PlayComputerToMan();
            break;
        case 3:
            t.PlayComputerToComputer();
            break;
        default:
            break;
        }
        t.Init();
        system("pause");
        cout<<"1. Man To Man"<<endl;
        cout<<"2. Computer To Man"<<endl;
        cout<<"3. Computer To Computer"<<endl;
        cout<<"Please input select:"<<endl;
        cleardevice();
        t.DrawBoard();

    }
}



