#include"database.h"
#include"Win_define.h"
#include<format>
using std::cin;
using std::vector;
using std::cout;

extern string accountNOW;//���ڵ�¼�ߵ��˺ţ�ѧ�ţ�

void StudentApply() {
	cls(); 
	int keyin;
	{
		vector<string>applyinfo;
		Studentinfo proc;
		if (proc.checkapply(applyinfo)) {
			gotoxy(30, 5, "��������״̬��");
			cout << applyinfo[0];
			{
				gotoxy(30, 10, "����У��ʽ��");
				cout << applyinfo[5];
				gotoxy(30, 13, "��Уʱ��: ");
				cout << applyinfo[2];
				gotoxy(30, 16, "��Уʱ��: ");
				cout << applyinfo[1];
				gotoxy(30, 19, "����У��: ");
				cout << applyinfo[4];
			}
			gotoxy(130, 35, "[ESC}�˳�");

			if (applyinfo[0] != "�����")
				gotoxy(130, 32, "[1]��������");

			else if (applyinfo[0] == "�����") {
				gotoxy(130, 32, "[1]ɾ������");
				gotoxy(130, 34, "[2]�޸�����");
			}

			int keyin;
			while (1) {
				keyin = _getch() - 48;
				if (keyin == -21) {
					cls();
					return;
				}
				if (applyinfo[0] != "�����" && keyin == 1) {
					proc.toapply();
					gotoxy(30, 35, "����ɹ�");
					Sleep(500);
					cls();
					return;
				}
				if (applyinfo[0] == "�����" && keyin == 1) {
					proc.deleteapply();
					gotoxy(30, 35, "ɾ���ɹ�");
					Sleep(500);
					cls();
					return;
				}
				if (applyinfo[0] == "�����" && keyin == 2) {
					proc.changeapply();
					gotoxy(30, 35, "�޸ĳɹ�");
					Sleep(300);
					cls();
					return;
				}

			}
		}
		gotoxy(30, 10, "δ��ѯ�������¼");
		gotoxy(30, 20, "[1]�ύ������");
		gotoxy(30, 25, "[ESC]�˳�");
		while (1) {
			keyin = _getch() - 48;
			if (keyin == -21) {
				cls();
				return;
			}
			else if (keyin == 1) {
				proc.toapply();
				gotoxy(30, 35, "����ɹ�");
				Sleep(500);
				cls();
				return;
			}
		}
		
	}
}

void BasicDataStream() {
	cls();
	string temp;
	gotoxy(20, 10, "������������Ϣ����'��'Ϊ������Ϣ�ָ�������'��'Ϊ������Ϣ�ڶ���ķָ�����");
	gotoxy(20, 12, "����'������������ѧ�ţ�522031145141���绰��54749110��ѧԺ����Ժ���༶����Ժ2201������¥����X83�����£�36.7;'");
	gotoxy(20, 15);
	showcursor();
	getline(cin, temp);
	hidecursor();
	streamprocess(temp);
	gotoxy(20, 30, "����ɹ�");
	gotoxy(50, 30, "[1]��������");
	gotoxy(80, 30, "[ESC]�����ϼ��˵�");
	int keyin;
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
		if (keyin == 1) break;
	}

	cls();
	if (keyin == 1)
		BasicDataStream();
}

void PCRDataStream() {
	cls();
	string temp;
	gotoxy(20, 10, "������������Ϣ����'��'Ϊ������Ϣ�ָ�������'��'Ϊ�����Ϣ�ڶ���ķָ���,��'.'��Ϊ������Ϣ�ڵķָ���,�Ի��з�Ϊÿ���˵ķָ�����");
	gotoxy(20, 12, "����'����,522031145141;2020.02.10.17.08.44.����;2022.12.08.17.55.45.����");
	gotoxy(20, 13, "     ����,52203xxxxxxx;xxxx.xx.xx.xx.xx.xx.xxxx'(Ҫ��������Ļ���������һ������)");
	gotoxy(20, 15);
	showcursor();
	while (1) {
		Studentinfo proc;
		getline(cin, temp);
		if (temp.size() == 0) break;
		proc.PCRprocess(temp);//ÿ�δ���ȥ�Ķ���һ���� 
	}
	hidecursor();
	gotoxy(20, 30, "����ɹ�");
	gotoxy(50, 30, "[1]��������");
	gotoxy(80, 30, "[ESC]�����ϼ��˵�");
	int keyin;
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
		if (keyin == 1) break;
	}

	cls();
	if (keyin == 1)
		PCRDataStream();
}

void Application() {
	Studentinfo proc;
	cls();
	gotoxy(30, 2, "��ǰ���ڵĴ�������Ŀ��");
	proc.teacherapply();
	gotoxy(120, 35, "[ESC]�˳�");
	int keyin;
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
	}
}

void DormitoryManage() {
	Dormitory proc;
	cls();
	//proc.addinfo();
	proc.showdormitory();
	gotoxy(80, 5, "[1]����¥�����ѯ");
	gotoxy(80, 10, "[2]����¥��ع���");
	gotoxy(80, 15, "[ESC]����");
	int keyin;
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
		cls();
		proc.getDormPCR();
	}
	else if (keyin == 2) {
		string temp;
		cls();
		gotoxy(20, 3, "��������¥����");
		showcursor();
		getline(cin, temp);
		hidecursor();
		proc.setstate(temp);
		cin.clear();
	}

	gotoxy(120, 35, "[ESC]�˳�");
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
	}
}

void SearchPCRforTeacher() {
	Studentinfo proc;
	cls();
	gotoxy(30, 15, "[1]���༶��ѯ������Ϣ");
	gotoxy(30, 20, "[2]��ѧ�Ų�ѯ������Ϣ");
	gotoxy(30, 35, "[ESC]����");
	int keyin;
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
		if (keyin == 1 || keyin == 2) break;
	}
	cls();

	string temp;
	showcursor();
	if (keyin == 1) {
		gotoxy(20, 3, "����༶����  ");		
		getline(cin, temp);
		proc.CheckClassPCR(temp);
		cin.clear();
	}
	else if (keyin == 2) {
		gotoxy(20, 3, "����ѧ��ѧ��  ");
		getline(cin, temp);
		proc.CheckStudentPCR(temp);
		cin.clear();
	}
	hidecursor();

	gotoxy(30, 35, "[ESC]����");
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
	}
}

void SearchPCRforStudent() {
	Studentinfo proc;
	cls();
	proc.CheckStudentPCR(accountNOW);//���ú��������ﴫ��ȥ����ѧ���˵�ǰѧ��
	gotoxy(30, 35, "[ESC]����");
	while (1) {
		int keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
	}
}

void AddDorm() {
	cls();
	gotoxy(20, 5, "����ʱ����ʹ�á�������Ϊ��Ϣ������Ϣ��ָ�������ʹ�á�������Ϊ��Ϣ���ָ�������ʹ�á�������Ϊ��Ϣ�����߼�ָ���");
	gotoxy(20, 7, "���磺¥����D27��������100��¥����XXX��¥����X26��������50��¥����XXX��");
	gotoxy(20, 9, "�����룺 ");
	showcursor();

	string s;
	getline(cin, s);
	hidecursor();
	Dormprocess(s);
	gotoxy(20, 30, "����ɹ�");
	gotoxy(50, 30, "[1]��������");
	gotoxy(80, 30, "[ESC]�����ϼ��˵�");
	int keyin;
	while (1) {
		keyin = _getch() - 48;
		if (keyin == -21) {
			cls();
			return;
		}
		if (keyin == 1) break;
	}

	cls();
	if (keyin == 1)
		AddDorm();
}