#include"database.h"
#include"Win_define.h"
#include<format>
using std::cin;
using std::vector;
using std::cout;

extern string accountNOW;//现在登录者的账号（学号）

void StudentApply() {
	cls(); 
	int keyin;
	{
		vector<string>applyinfo;
		Studentinfo proc;
		if (proc.checkapply(applyinfo)) {
			gotoxy(30, 5, "您的申请状态：");
			cout << applyinfo[0];
			{
				gotoxy(30, 10, "出入校方式：");
				cout << applyinfo[5];
				gotoxy(30, 13, "出校时间: ");
				cout << applyinfo[2];
				gotoxy(30, 16, "进校时间: ");
				cout << applyinfo[1];
				gotoxy(30, 19, "申请校区: ");
				cout << applyinfo[4];
			}
			gotoxy(130, 35, "[ESC}退出");

			if (applyinfo[0] != "待审核")
				gotoxy(130, 32, "[1]重新申请");

			else if (applyinfo[0] == "待审核") {
				gotoxy(130, 32, "[1]删除申请");
				gotoxy(130, 34, "[2]修改申请");
			}

			int keyin;
			while (1) {
				keyin = _getch() - 48;
				if (keyin == -21) {
					cls();
					return;
				}
				if (applyinfo[0] != "待审核" && keyin == 1) {
					proc.toapply();
					gotoxy(30, 35, "申请成功");
					Sleep(500);
					cls();
					return;
				}
				if (applyinfo[0] == "待审核" && keyin == 1) {
					proc.deleteapply();
					gotoxy(30, 35, "删除成功");
					Sleep(500);
					cls();
					return;
				}
				if (applyinfo[0] == "待审核" && keyin == 2) {
					proc.changeapply();
					gotoxy(30, 35, "修改成功");
					Sleep(300);
					cls();
					return;
				}

			}
		}
		gotoxy(30, 10, "未查询到申请记录");
		gotoxy(30, 20, "[1]提交新申请");
		gotoxy(30, 25, "[ESC]退出");
		while (1) {
			keyin = _getch() - 48;
			if (keyin == -21) {
				cls();
				return;
			}
			else if (keyin == 1) {
				proc.toapply();
				gotoxy(30, 35, "申请成功");
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
	gotoxy(20, 10, "在下面输入信息（以'；'为多条信息分隔符，以'，'为单条信息内多项的分隔符）");
	gotoxy(20, 12, "例：'姓名：张三，学号：522031145141，电话：54749110，学院：电院，班级：电院2201，寝室楼栋：X83，体温：36.7;'");
	gotoxy(20, 15);
	showcursor();
	getline(cin, temp);
	hidecursor();
	streamprocess(temp);
	gotoxy(20, 30, "输入成功");
	gotoxy(50, 30, "[1]继续输入");
	gotoxy(80, 30, "[ESC]返回上级菜单");
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
	gotoxy(20, 10, "在下面输入信息（以'；'为多条信息分隔符，以'，'为身份信息内多项的分隔符,以'.'作为核酸信息内的分隔符,以换行符为每个人的分隔符）");
	gotoxy(20, 12, "例：'张三,522031145141;2020.02.10.17.08.44.阴性;2022.12.08.17.55.45.阴性");
	gotoxy(20, 13, "     李四,52203xxxxxxx;xxxx.xx.xx.xx.xx.xx.xxxx'(要结束输入的话可以输入一个空行)");
	gotoxy(20, 15);
	showcursor();
	while (1) {
		Studentinfo proc;
		getline(cin, temp);
		if (temp.size() == 0) break;
		proc.PCRprocess(temp);//每次传过去的都是一个人 
	}
	hidecursor();
	gotoxy(20, 30, "输入成功");
	gotoxy(50, 30, "[1]继续输入");
	gotoxy(80, 30, "[ESC]返回上级菜单");
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
	gotoxy(30, 2, "当前存在的待审批条目：");
	proc.teacherapply();
	gotoxy(120, 35, "[ESC]退出");
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
	gotoxy(80, 5, "[1]宿舍楼核酸查询");
	gotoxy(80, 10, "[2]宿舍楼封控管理");
	gotoxy(80, 15, "[ESC]返回");
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
		gotoxy(20, 3, "输入宿舍楼名称");
		showcursor();
		getline(cin, temp);
		hidecursor();
		proc.setstate(temp);
		cin.clear();
	}

	gotoxy(120, 35, "[ESC]退出");
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
	gotoxy(30, 15, "[1]按班级查询核酸信息");
	gotoxy(30, 20, "[2]按学号查询核酸信息");
	gotoxy(30, 35, "[ESC]返回");
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
		gotoxy(20, 3, "输入班级名称  ");		
		getline(cin, temp);
		proc.CheckClassPCR(temp);
		cin.clear();
	}
	else if (keyin == 2) {
		gotoxy(20, 3, "输入学生学号  ");
		getline(cin, temp);
		proc.CheckStudentPCR(temp);
		cin.clear();
	}
	hidecursor();

	gotoxy(30, 35, "[ESC]返回");
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
	proc.CheckStudentPCR(accountNOW);//共用函数，这里传过去的是学生端当前学号
	gotoxy(30, 35, "[ESC]返回");
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
	gotoxy(20, 5, "输入时，请使用‘：’作为信息类与信息间分隔符，请使用‘，’作为信息类间分隔符，请使用‘；’作为信息归属者间分隔符");
	gotoxy(20, 7, "例如：楼名：D27，容量：100，楼长：XXX；楼名：X26，容量：50，楼长：XXX；");
	gotoxy(20, 9, "请输入： ");
	showcursor();

	string s;
	getline(cin, s);
	hidecursor();
	Dormprocess(s);
	gotoxy(20, 30, "输入成功");
	gotoxy(50, 30, "[1]继续输入");
	gotoxy(80, 30, "[ESC]返回上级菜单");
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