#pragma once
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#include<string>
#include<Windows.h>
#include<conio.h>
#include<iostream>

	//控制光标位置 
void gotoxy(const int x, const int y, std::string str);

void gotoxy(const int x, const int y);

const int blue = 0, yellow = 1, red = 2, green = 3, purple = 4, white = 5;//颜色常量 
void color(int c); //设置颜色 

	//产生一个 [l,r] 范围的随机数 
int random(int l, int r);

	//检测按键是否按下
bool check(char ch);  //检测某个按键是否按下，按下返回 true，否则返回 false，参数：按键表示的字符

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