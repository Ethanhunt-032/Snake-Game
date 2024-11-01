#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameOver;
const int height =20;
const int width = 20;
int x,y, fruitX,fruitY,score;
int tailX[100],tailY[100];
int nTail;

// FOR SNAKE TO MOVE DIRECTIONS
enum eDirection {STOP=0,UP,DOWN,LEFT,RIGHT};
eDirection dir;

void SetUp(){
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    // creating a fruit
    fruitX = (rand()) % width;
    fruitY = (rand()) % height;
    score =0;
}

void Draw(){
//  This function called many time so every time we clear the screen before creating game;
    system("CLS");

    for(int i=0;i<width+2;i++)
    {
        cout<<"-";
    }
    cout<<endl;

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<=width;j++)
        {
            if(j==0 || j ==width)
            {
                cout<<"|";
            }
            if(i==y && j ==x)
            {
                cout<<"O"; // head of snake
            }
            else if(i==fruitY && j ==fruitX)
            {
                cout<<"#"; // Fruit
            }
            else{ // print the snake on screen

                bool print  =false;
                for(int k=0;k<nTail;k++)
                {
                    if(tailX[k]==j && tailY[k] == i)
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                if(!print) // Other than snake in board is print with empty spaces
                {
                    cout<<" ";
                }
                
            }
        }
        cout<<endl;
    }
    
    for(int i=0;i<width+2;i++)
    {
        cout<<"-";
    }
    cout<<endl;
    // printing score
    cout<<"Score :" <<score<<endl;
}

void Input(){
    if(_kbhit) // IF KEYBOARD IS HIT
    {
        switch(_getch()) // GETTING THE KEY ENTERED
        {
            case 'w' :
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x' :
                gameOver = true;
                break;
        }
    }
}
void Logic(){
    // for movement of tail for every key press
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X,prev2Y;
    tailX[0] =x;
    tailY[0] =y;
    for(int i=1;i<nTail;i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case 'x': 
            gameOver = true; 
            break; 
    }
    
    if (x >= width) x =0; // Snake return from other side
    else if (x <0) x = width -1;

    if (y >= height) y = 0;  // Snake return from other side
    else if (y < 0) y = height - 1;

    if(x == fruitX && y == fruitY) // When EAT fruite - Score, size increased
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

}

int main()
{
    SetUp();
    // continously printing board 
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(40);
    }
    cout<< "Game Over !";
    return 0;
}