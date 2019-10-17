#include<bits/stdc++.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>
#include <unistd.h>
long interval = 700000;
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x,y,fruitX,fruitY,score;
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
int tailX[100],tailY[100];
int nTail;
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

void Setup () {
    gameOver = false;
    dir =STOP;
    x =width/2;
    y = height/2;
    fruitX = rand()%width;
    fruitY = rand()% height;
    score =0;
}
void Draw () {
    system("clear");
    for(int i =0;i<width;i++) {
        cout<< "#";
    }
    cout <<endl;
    for(int i=0;i<height;i++) {
        for(int j =0;j<width;j++) {
            if(j == 0 || j == width-1) {
                cout << "#";
            }
            else {
                if(j==x && i ==y) {
                    cout << "0";
                }
                else if(j==fruitX && fruitY == i) {
                    cout << "F";
                }
                else {
                    bool print = false;
                    for(int k =0;k<nTail;k++) {
                        if(tailX[k] ==j && tailY[k] ==i) {
                            cout << "0";
                            print = true;
                        }
                    }
                    if(!print) {
                            cout << " ";

                        }

                }
            }

        }
        cout << endl;
    } 

    for(int i =0;i<width;i++) {
        cout<< "#";
    }
    cout <<endl;
    cout << "Score: " << score <<endl;

}
void Input() {
    if(_kbhit()) {
        char k;
        cin >> k;
        switch (k) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X,prev2Y;
    tailX[0] = x;
    tailY[0] =y;
    for(int i=1;i<nTail;i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x>width || y >height || x<0 || y<0) { 
        gameOver = true;
    }
    for(int i =0;i<nTail;i++) {
        if(tailX[i] ==x && tailY[i] ==y) {
            gameOver = true;
        }
    }
    if(x == fruitX && y == fruitY) {
        fruitX = rand()%width;
        fruitY = rand()%height;
        nTail++;
        score+=10;
        interval-=2000;
    }
}

int main() {
    Setup();
    while(!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(interval);
    }
    cout << "#####################################"<<" GAME OVER,your score is " <<score <<" ####################################"<<endl;

    return 0;
}