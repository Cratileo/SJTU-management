#pragma once
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#include<string>
#include<Windows.h>
#include<conio.h>
#include<iostream>

	//控制光标位置 
void gotoxy(const int x, const int y, std::string str);

void gotoxy(const int x, const int y);

	//清屏
void cls();

	//定义窗口标题
void titleset(const char* title);

	//设置窗口大小
void setconsoleborder(int cols, int lines, int buffer_cols, int buffer_lines);

void hidecursor();   //隐藏光标

void showcursor();   //显示光标

void fixconsolesize();   //禁用窗口大小改变

int checknum(int arr[], int n);  //输入数检测机-Beta版

void printline(int x);  //在x行显示一条直线