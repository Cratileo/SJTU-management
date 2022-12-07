#include <ctime>
#include<random>
#include"Win_define.h"

const HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);//返回标准输出设备句柄
const HANDLE in = GetStdHandle(STD_INPUT_HANDLE);//返回标准输入设备句柄

std::random_device rd;                  //初始化随机数器
std::default_random_engine e(rd());     //选择默认随机数引擎

    //控制光标位置 
void gotoxy(const int x, const int y, std::string str)
{
    HANDLE hout;
    COORD coord;
    coord.X = x;
    coord.Y = y;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hout, coord);
    std::cout << str;
}

    void gotoxy(const int x, const int y)
    {
        HANDLE hout;
        COORD coord;
        coord.X = x;
        coord.Y = y;
        hout = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hout, coord);
    }

    void color(int c) {  //设置颜色 
        switch (c)
        {
        case red:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); break;
        case green:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); break;
        case yellow:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); break;
        case blue:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;
        case white:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
        case purple:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE); break;
        }
    }

    //产生一个 [l,r] 范围的随机数 
    int random(int l, int r) 
    {
        std::uniform_int_distribution<time_t> u(l, r);
        return u(e);

    }

    //检测按键是否按下
    bool check(char ch)  //检测某个按键是否按下，按下返回 true，否则返回 false，参数：按键表示的字符
    {
        if (KEY_DOWN(ch)) return true;
        else return false;
    }

    //清屏
    void cls()
    {
        system("cls");
    }

    //设置窗口标题
    void titleset(const char* title)
    {
        SetConsoleTitleA(title);
    }

    //初始化窗口界面和大小
    void setconsoleborder(int set_cols, int set_lines, int set_buffer_cols, int set_buffer_lines)
    {
        COORD maxscreen = GetLargestConsoleWindowSize(out);
        SMALL_RECT rect;
        rect.Top = 0;
        rect.Left = 0;
        rect.Bottom = set_lines - 1;
        rect.Right = set_cols - 1;
        COORD crd;
        crd.X = (set_buffer_cols == -1 || set_buffer_cols < set_cols) ? set_cols : set_buffer_cols;
        crd.Y = (set_buffer_lines == -1 || set_buffer_lines < set_lines) ? set_lines : set_buffer_lines;
        int cur_cols, cur_lines, cur_buffer_cols, cur_buffer_lines;
        CONSOLE_SCREEN_BUFFER_INFO binfo;
        GetConsoleScreenBufferInfo(out, &binfo);
        cur_cols = binfo.srWindow.Right - binfo.srWindow.Left + 1;	//可见窗口的列数
        cur_lines = binfo.srWindow.Bottom - binfo.srWindow.Top + 1;	//可见窗口的行数
        cur_buffer_cols = binfo.dwSize.X;							//缓冲区的列数
        cur_buffer_lines = binfo.dwSize.Y;							//缓冲区的行数

        cls();
        if (crd.X <= cur_buffer_cols) {
            if (crd.Y <= cur_buffer_lines) {
                SetConsoleWindowInfo(out, true, &rect);//设置窗口
                SetConsoleScreenBufferSize(out, crd);//设置缓冲区
            }
            else {
                COORD tmpcr;
                tmpcr.X = cur_buffer_cols;
                tmpcr.Y = crd.Y;
                SetConsoleScreenBufferSize(out, tmpcr);//设置缓冲区

                SetConsoleWindowInfo(out, true, &rect);//设置窗口
                SetConsoleScreenBufferSize(out, crd);//设置缓冲区
            }
        }
        else {
            if (crd.Y >= cur_buffer_lines) {
                SetConsoleScreenBufferSize(out, crd);//设置缓冲区
                SetConsoleWindowInfo(out, true, &rect);//设置窗口
            }
            else {
                COORD temp;
                temp.X = crd.X;
                temp.Y = cur_buffer_lines;
                SetConsoleScreenBufferSize(out, temp);//设置缓冲区

                SetConsoleWindowInfo(out, true, &rect);//设置窗口
                SetConsoleScreenBufferSize(out, crd);//设置缓冲区
            }
        }
    }

    void hidecursor() {
        CONSOLE_CURSOR_INFO temp;
        temp.bVisible = 0;
        temp.dwSize = 1;
        SetConsoleCursorInfo(out, &temp);
    }

    void showcursor() {
        CONSOLE_CURSOR_INFO temp;
        temp.bVisible = 1;
        temp.dwSize = 25;
        SetConsoleCursorInfo(out, &temp);
    }

    void fixconsolesize() {
        SetWindowLongPtrA(
            GetConsoleWindow(),
            GWL_STYLE,
            GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE)
            & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
    }

    int checknum(int arr[], int n)  //获取键盘输入的字符并返回给调用函数进行匹配,由arr提供要匹配字符的编码
    {
        while (1)
        {
            int keyin = _getch() - 48;
            for (int i = 0; i < n; i++)
                if (arr[i] == keyin) return keyin;
        }
    }

    void printline(int x)
    {
        for (int i = 1; i <= 150; i++)
            gotoxy(i, x, "-");
    }