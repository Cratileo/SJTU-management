#include<iomanip>
#include <format>
#include"Win_define.h"
#include"database.h"

using namespace std;

extern string accountNOW;//���ڵ�¼�ߵ��˺ţ�ѧ�ţ�

void initialize();//��ʼ������
void Mainmenu();  //���˵�
void teacher();//��ʦ����ҳ
void studentpage();//ѧ������ҳ
char login();// ��¼����

int main()
{
	initialize();
	while (1)
		Mainmenu();
}

void initialize()
{
	cls();
	titleset("��������ۺ�ϵͳ");
	setconsoleborder(150, 40, 150, 40);
	fixconsolesize();
	hidecursor();
}

void Mainmenu() {
	gotoxy(60, 10, "��ͨ��ѧ�������һվʽϵͳ");
	gotoxy(130, 38, "Alpha 1.0.0");
	char state = login();
	

	cls();
	if (state == 'T') {
		teacher();
		Mainmenu();
	}
	else if (state == 'S') {
		studentpage();
		Mainmenu();
	}
}

char login()
{
	cls();
	while (1) {
		string accountT, passwordT;
		gotoxy(50, 2, R"(      _   _                             _   )");
		gotoxy(50, 3, R"(     | | / \   ___ ___ ___  _   _ _ __ | |_ )");
		gotoxy(50, 4, R"(  _  | |/ _ \ / __/ __/ _ \| | | | '_ \| __|)");
		gotoxy(50, 5, R"( | |_| / ___ \ (_| (_| (_) | |_| | | | | |_ )");
		gotoxy(50, 6, R"(  \___/_/   \_\___\___\___/ \__,_|_| |_|\__|)");

		gotoxy(65, 25, "�˺�:_______________");
		gotoxy(65, 30, "����:______________");
		gotoxy(70, 25);
		showcursor();
		getline(cin, accountT);
		gotoxy(70, 30);
		getline(cin, passwordT);
		hidecursor();
		char state = checkaccount(accountT,passwordT);//��¼��½��Ա���,SΪstudent��TΪteacher
		if (state=='S' || state == 'T')
			return state;
		else {
			gotoxy(95, 28, "* �˺Ų����ڻ��������");
			continue;
		}
	}
}

void teacher() {
	while(1){
		cls();
		gotoxy(70, 10, "��ӭ");
		gotoxy(25, 15, "[1]ѧ��������Ϣ¼��");
		gotoxy(25, 20, "[2]ѧ��������Ϣ¼��");
		gotoxy(25, 25, "[3]������Ϣ��ѯ");
		gotoxy(95, 15, "[4]ѧ������У����");
		gotoxy(95, 20, "[5]ѧ������¥����");
		gotoxy(10, 35, "[ESC]�˳���¼");
		int keyin;
		int tempnum[7] = { 1,2,3,4,5,-21 };
		keyin = checknum(tempnum, 7);
		switch (keyin) {
			case 1: BasicDataStream(); break;
			case 2: PCRDataStream(); break;
			case 3: SearchPCRforTeacher(); break;
			case 4: Application(); break;
			case 5: DormitoryManage(); break;
			case -21: cls();  return;
		}
	}
}

void studentpage() {
	

	int keyin;
	gotoxy(25, 10, "[1]�������ѯ");
	gotoxy(25, 13, "[2]ѧ������У����");
	gotoxy(25, 30, "[ESC]�����ϼ��˵�");
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
		if (keyin == 1 || keyin == 2) break;
	}
	cls();
	if (keyin == 1) {
		SearchPCRforStudent();
		studentpage();
	}
	else if (keyin == 2) {
		StudentApply();
		studentpage();
	}
}
