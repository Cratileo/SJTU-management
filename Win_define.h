#pragma once
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#include<string>
#include<Windows.h>
#include<conio.h>
#include<iostream>

	//���ƹ��λ�� 
void gotoxy(const int x, const int y, std::string str);

void gotoxy(const int x, const int y);

const int blue = 0, yellow = 1, red = 2, green = 3, purple = 4, white = 5;//��ɫ���� 
void color(int c); //������ɫ 

	//����һ�� [l,r] ��Χ������� 
int random(int l, int r);

	//��ⰴ���Ƿ���
bool check(char ch);  //���ĳ�������Ƿ��£����·��� true�����򷵻� false��������������ʾ���ַ�

	//����
void cls();

	//���崰�ڱ���
void titleset(const char* title);

	//���ô��ڴ�С
void setconsoleborder(int cols, int lines, int buffer_cols, int buffer_lines);

void hidecursor();   //���ع��

void showcursor();   //��ʾ���

void fixconsolesize();   //���ô��ڴ�С�ı�

int checknum(int arr[], int n);  //����������-Beta��

void printline(int x);  //��x����ʾһ��ֱ��