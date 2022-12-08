#include"Win_define.h"

const HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);//���ر�׼����豸���
const HANDLE in = GetStdHandle(STD_INPUT_HANDLE);//���ر�׼�����豸���

    //���ƹ��λ�� 
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

    //����
    void cls()
    {
        system("cls");
    }

    //���ô��ڱ���
    void titleset(const char* title)
    {
        SetConsoleTitleA(title);
    }

    //��ʼ�����ڽ���ʹ�С
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
        cur_cols = binfo.srWindow.Right - binfo.srWindow.Left + 1;	//�ɼ����ڵ�����
        cur_lines = binfo.srWindow.Bottom - binfo.srWindow.Top + 1;	//�ɼ����ڵ�����
        cur_buffer_cols = binfo.dwSize.X;							//������������
        cur_buffer_lines = binfo.dwSize.Y;							//������������

        cls();
        if (crd.X <= cur_buffer_cols) {
            if (crd.Y <= cur_buffer_lines) {
                SetConsoleWindowInfo(out, true, &rect);//���ô���
                SetConsoleScreenBufferSize(out, crd);//���û�����
            }
            else {
                COORD tmpcr;
                tmpcr.X = cur_buffer_cols;
                tmpcr.Y = crd.Y;
                SetConsoleScreenBufferSize(out, tmpcr);//���û�����

                SetConsoleWindowInfo(out, true, &rect);//���ô���
                SetConsoleScreenBufferSize(out, crd);//���û�����
            }
        }
        else {
            if (crd.Y >= cur_buffer_lines) {
                SetConsoleScreenBufferSize(out, crd);//���û�����
                SetConsoleWindowInfo(out, true, &rect);//���ô���
            }
            else {
                COORD temp;
                temp.X = crd.X;
                temp.Y = cur_buffer_lines;
                SetConsoleScreenBufferSize(out, temp);//���û�����

                SetConsoleWindowInfo(out, true, &rect);//���ô���
                SetConsoleScreenBufferSize(out, crd);//���û�����
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

    int checknum(int arr[], int n)  //��ȡ����������ַ������ظ����ú�������ƥ��,��arr�ṩҪƥ���ַ��ı���
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