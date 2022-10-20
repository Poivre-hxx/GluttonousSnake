#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <iomanip>
#define DETA_X 1
#define DETA_Y 1
#define EDGE_THICKNESS 1

using namespace std;

bool gameOver, fruitFlash, isFullWidth;
bool isPause = false;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[1000], tailY[1000];
int nTail = 1;
int change = 1;
int mode = 0;
string player;
string p[100];
int bit = 0;
int s[100];
const int FRAME_PER_SECOND = 25; //�㶨��֡��
const int SKIP_TICKS = 1000 / FRAME_PER_SECOND;

DWORD next_Game_Tick = GetTickCount();

int sleep_Time = 0;
#define DIFFICULTY_FACTOR 50

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void setPos(int X, int Y) //������ʾ�ұ���ʾ��
{
    COORD pos;
    if (isFullWidth)
        pos.X = 2 * X + 4;
    else
        pos.X = X + 2;
    pos.Y = Y + 2;

    SetConsoleCursorPosition(h, pos);
}
void setPos_final(int X, int Y) //������ʾ��Ϸ��������
{
    COORD pos;
    if (isFullWidth)
        pos.X = 2 * X + 2;
    else
        pos.X = X + 1;
    pos.Y = Y + 2;

    SetConsoleCursorPosition(h, pos);
}

void outPut_s(const string a)
{
    size_t len = a.size();
    for(int i = 0;i<a.size();i++)
    {
        cout << a[i];
        fflush(stdin); // ������뻺����
        Sleep(50);
    }
    cout << endl;
}
void Initial_p()
{
    // int textColor = 0x06;
    // SetConsoleTextAttribute(h, textColor);
    Sleep(1000);
    system("cls");
    setPos(4, 2);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "��";
    // Sleep(50);
    // cout << "I";
    // Sleep(50);
    // cout << "D";
    // Sleep(50);
    // cout << "��" << endl;
    // Sleep(50);
    outPut_s("�����ߣ�����������ID��");
    setPos(4, 4);
    cin >> player;

    setPos(4, 4);
    // cout << "-";
    // Sleep(50);
    // cout << "-";
    // Sleep(50);
    // cout << "L";
    // Sleep(50);
    // cout << "i";
    // Sleep(50);
    // cout << "n";
    // Sleep(50);
    // cout << "k";
    // Sleep(50);
    // cout << " ";
    // Sleep(50);
    // cout << "S";
    // Sleep(50);
    // cout << "t";
    // Sleep(50);
    // cout << "a";
    // Sleep(50);
    // cout << "r";
    // Sleep(50);
    // cout << "t";
    // Sleep(50);
    // cout << "-";
    // Sleep(50);
    // cout << "-";
    // Sleep(100);
    outPut_s("-- Link Start --");
}
void inPutFile(char *filename, string *p, int *s)
{
    ifstream srcFile(filename, ios::in); //���ı�ģʽ��in.txt����
    if (!srcFile)
    { //��ʧ��
        cout << "error opening source file." << endl;
    }
    //��������cin������ifstream����
    int i = 1;
    string x;
    while (srcFile >> x)
    {
        if (i % 2 != 0)
        {
            *p = x;
            p++;
        }
        else
        {
            istringstream ss(x);
            ss >> *s;
            s++;
        }
        i++;
    }
    bit = i / 2;
    srcFile.close();
}
void outPutFile(char *filename, string player, int score)
{
    ofstream destFile(filename, ios::app); //���ı�ģʽ��out.txt��д
    if (!destFile)
    {
        cout << "error opening destination file." << endl;
    }
    destFile.eof();
    destFile << player << " ";
    destFile << score << " ";
    destFile.close();
}
void Initial()
{
    SetConsoleTitleA("Console_̰����");
    COORD dSize = {80, 25};
    SetConsoleScreenBufferSize(h, dSize);     //���û�������С
    CONSOLE_CURSOR_INFO _cursor = {1, false}; //���ù���С�����ع��
    SetConsoleCursorInfo(h, &_cursor);

    isFullWidth = true;
    gameOver = false;
    fruitFlash = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailX[0] = x;
    tailY[0] = y;
    nTail = 1;
    mode = 0;

    for (int i = 0; i < bit; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (s[i] > s[j])
            {
                int ch_s;
                string ch_p;
                ch_s = s[i];
                s[i] = s[j];
                s[j] = ch_s;
                ch_p = p[i];
                p[i] = p[j];
                p[j] = ch_p;
            }
        }
    }
}
void DrawMap()
{
    system("cls");

    int textColor = 0x06;
    SetConsoleTextAttribute(h, textColor);

    setPos(-1, -1); // ���ƶ��ϵ�ǽ
    for (int i = 0; i < width + 2; i++)
        if (isFullWidth)
            cout << "��";
        else
            cout << "#";

    for (int i = 0; i < height; i++)
    {
        setPos(-1, i); //�������ҵ�ǽ
        for (int j = 0; j < width + 2; j++)
        {
            if (j == 0)
                if (isFullWidth)
                    cout << "��";
                else
                    cout << "#";
            else if (j == width + 1)
                if (isFullWidth)
                    cout << "��";
                else
                    cout << "#";
            else if (isFullWidth)
                cout << "  ";
            else
                cout << " ";
        }
        cout << endl;
    }
    setPos(-1, height); //�����·���ǽ
    for (int i = 0; i < width + 2; i++)
        if (isFullWidth)
            cout << "��";
        else
            cout << "#";
}
void Prompt_info(int _x, int _y)
{
    int initialX = 20, initialY = 0;

    SetConsoleTextAttribute(h, 0x0f);
    setPos(_x + initialX, _y + initialY);
    cout << "�� ��Ϸ˵����";
    initialY++;
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  A.������ײ����Ϸ����";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  B.�߿ɴ�ǽ";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    initialY++;
    cout << "�� ����˵��";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� �����ƶ���A";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� �����ƶ���D";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� �����ƶ���S";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� �����ƶ���W";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� ��ʼ��Ϸ�����ⷽ���";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� �˳���Ϸ��x���˳�";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� ��Ϸģʽ�л���G";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    if (mode == 0)
        cout << "        �� ��ǰģʽ���޾�ģʽ";
    if (mode == 1)
        cout << "        �� ��ǰģʽ����ľͼ�";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� ���ߣ�hxx";
    setPos(_x + initialX, _y + initialY);
    initialY++;
    cout << "  �� ��ǰ�Ѷȣ� L" << score / 50 + 1;
}
void Prompt_score(int _x, int _y)
{
    int initialX = 36, initialY = 0;

    SetConsoleTextAttribute(h, 0x0f);
    setPos(_x + initialX, _y + initialY);
    cout << "�� ���ݰ�";
    initialY++;
    initialY++;
    setPos(_x + initialX, _y + initialY);
    cout << "  �� " << setw(10) << "player" << setw(8) << "score";
    if (bit > 10)
        bit = 10;
    for (int i = 0; i < bit; i++)
    {
        if (i == 0)
            SetConsoleTextAttribute(h, 0xcf);
        if (i == 1)
            SetConsoleTextAttribute(h, 0x7f);
        if (i == 2)
            SetConsoleTextAttribute(h, 0x6f);
        if (i > 2)
            SetConsoleTextAttribute(h, 0x0f);
        if (i < 3 && i > 0) //��������
            initialY++;
        initialY++;
        setPos(_x + initialX, _y + initialY);
        cout << "   " << setw(2) << i + 1 << setw(10) << p[i] << setw(8) << s[i];
    }
}
void Input()
{
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
            case 'A':
                if (dir != RIGHT)
                    dir = LEFT;
                break;
            case 'd':
            case 'D':
                if (dir != LEFT)
                    dir = RIGHT;
                break;
            case 'w':
            case 'W':
                if (dir != DOWN) 
                    dir = UP;
                break;
            case 's':
            case 'S':
                if (dir != UP)
                    dir = DOWN;
                break;
            case 'x':
            case 'X':
                gameOver = true;
                break;
            case 'g':
            case 'G':
                mode = !mode;
                break;
            case 224:
                switch (_getch())
                {
                case 72:
                    if (dir != DOWN)
                        dir = UP;
                    break;
                case 80:
                    if (dir != UP)
                        dir = DOWN;
                    break;
                case 75:
                    if (dir != RIGHT)
                        dir = LEFT;
                    break;
                case 77:
                    if (dir != LEFT)
                        dir = RIGHT;
                    break;
                }
                break;
            case 0x0D:
                if (isFullWidth)
                    isFullWidth = false;

                else
                    isFullWidth = true;
                //����һ��ȫ�ǡ���ǵ�ת��
                // DrawMap();
                // Prompt_info(5, 1);
                break;
            case ' ':
                isPause = !isPause;
                break;
            default:
                break;
            }
        }
    }
}
void eraseSnake()
{
    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        if (isFullWidth)
            cout << "  ";
        else
            cout << " ";
    }
}
void Logic()
{
    switch (dir)
    {
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

    // ��Ϸ�����ж�
    // ײǽ��g ( mode == 1 )
    if (mode == 1)
    {
        if (x > width - 1 || x < 0 || y > height - 1 || y < 0)
            gameOver = true;
    }

    for (int i = 1; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (gameOver == false)
    {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;

        for (int i = 1; i < nTail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
        tailX[0] = x;
        tailY[0] = y;
    }
}
void DrawLocally()
{
    // ײǽʱ�Զ����� ( mode == 0 )
    if (mode == 0)
    {
        if (x > width - 1 && dir == RIGHT)
            x = 0;
        else if (x < 0 && dir == LEFT)
            x = width - 1;
        if (y > height - 1 && dir == DOWN)
            y = 0;
        else if (y < 0 && dir == UP)
            y = height - 1;
        tailX[0] = x;
        tailY[0] = y;
    }

    // ��ʾ������Ϣ
    if (isFullWidth == false && change == 0)
    {
        DrawMap();
        Prompt_info(5, 1);
        change = 1;
    }
    else if (isFullWidth == true && change == 1)
    {
        DrawMap();
        Prompt_info(5, 1);
        change = 0;
    }

    // fruitFlash���� fruit ����˸
    if (!fruitFlash)
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
        if (isFullWidth)
            cout << "��";
        else
            cout << "F";
        fruitFlash = true;
    }
    else
    {
        setPos(fruitX, fruitY);
        SetConsoleTextAttribute(h, 0x04);
        if (isFullWidth)
            cout << "  ";
        else
            cout << " ";
        fruitFlash = false;
    }

    // ��������
    for (int i = 0; i < nTail; i++)
    {
        setPos(tailX[i], tailY[i]);
        if (i == 0)
        {
            SetConsoleTextAttribute(h, 0x09);
            if (isFullWidth)
                cout << "��";
            else
                cout << "O";
        }
        else
        {
            SetConsoleTextAttribute(h, 0x0a);
            if (isFullWidth)
                cout << "��";
            else
                cout << "o";
        }
    }

    setPos(0, height + 1);
    SetConsoleTextAttribute(h, 0x06);
    cout << "��Ϸ�÷֣�" << score;

    CONSOLE_CURSOR_INFO _cursor = {1, false};
    SetConsoleCursorInfo(h, &_cursor);

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
void showScore(int _x, int _y)
{
    setPos(_x + 20, _y + 17);
    SetConsoleTextAttribute(h, 0x0f);
    cout << "����ǰ���֣�";
    SetConsoleTextAttribute(h, 0x0c);
    cout << score;
}
void gameOver_info()
{
    if (isFullWidth)
    {
        setPos_final(9, 8);
        SetConsoleTextAttribute(h, 0xec);
        cout << "��Ϸ����";
        setPos_final(5, 9);
        cout << "��Y�����¿�ʼ����N���˳�";
        SetConsoleTextAttribute(h, 0x0f);
    }
    else
    {
        setPos_final(7, 8);
        SetConsoleTextAttribute(h, 0xec);
        cout << "��Ϸ����";
        setPos_final(4, 9);
        cout << "Y���¿�ʼ/N�˳�";
        SetConsoleTextAttribute(h, 0x0f);
    }
}
int main()
{
    int rank = 0;
    bool gameQuit = false;
    Initial_p();
    do
    {
        inPutFile("data_s.txt", p, s);
        Initial();
        DrawMap();
        while (!gameOver)
        {
            Prompt_info(5, 1);
            Prompt_score(5, 1);
            Input();
            if (!isPause)
            {
                eraseSnake();
                Logic();

                DrawLocally();

                //����һ��֡Ƶ���ȶ���������ǰ��ļ��ز���SKIP_TICKS��
                // next_Game_Tick += SKIP_TICKS;
                // sleep_Time = next_Game_Tick - GetTickCount();
                sleep_Time = 200 / (score / DIFFICULTY_FACTOR + 1);

                Sleep(sleep_Time);
                // if (sleep_Time >= 0)
                //     Sleep(sleep_Time);
                showScore(5, 1);
                // Sleep(100);
            }
        }
        gameOver_info();
        outPutFile("data_s.txt", player, score);
        // setPos(0, 23);
        while (gameOver)
        {
            if (_kbhit())
            {
                switch (_getch())
                {
                case 'y':
                case 'Y':
                    gameOver = false;
                    system("cls");
                    break;
                case 'n':
                case 'N':
                    gameOver = false;
                    gameQuit = true;
                    break;
                default:
                    break;
                }
            }
            Sleep(50);
        }

    } while (!gameQuit);
    // system("pause");
    return 0;
}

