#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 10;
int x, y, fruitX, fruitY, score;
vector<int> tailX, tailY;
enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = eDirection::STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (size_t k = 0; k < tailX.size(); k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input() {
    char ch;
    cout<<"1) Use keys w,a,s,d for the respective up, right, down, left movements"<<endl;
    cout<<"2) he letter F represents the food, the letter O is your snake"<<endl;
    cout<<"3) Caution: the snake does not move automatically, after each keys inputs, you must press Entr to proceed."<<endl;
    cout<<"4) Happy struggling :>>"<<endl;
    cout<<"Enter keys below to start: "<<endl;
    cin >> ch;
    switch (ch) {
        case 'a':
            dir = eDirection::LEFT;
            break;
        case 'd':
            dir = eDirection::RIGHT;
            break;
        case 'w':
            dir = eDirection::UP;
            break;
        case 's':
            dir = eDirection::DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
    }
}

void Logic() {
    int prevX = tailX.empty() ? x : tailX.back();
    int prevY = tailY.empty() ? y : tailY.back();
    int prev2X, prev2Y;
    if (!tailX.empty()) {
        tailX.pop_back();
        tailY.pop_back();
    }
    tailX.insert(tailX.begin(), x);
    tailY.insert(tailY.begin(), y);

    switch (dir) {
        case eDirection::LEFT:
            x--;
            break;
        case eDirection::RIGHT:
            x++;
            break;
        case eDirection::UP:
            y--;
            break;
        case eDirection::DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (size_t i = 0; i < tailX.size(); i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
            break;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailX.push_back(prevX);
        tailY.push_back(prevY);
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(100)); // Sleep for a while to control game speed (100 milliseconds)
    }
    return 0;
}

