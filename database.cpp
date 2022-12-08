#include"Win_define.h"
#include"database.h"
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<format>
#include<memory>
using namespace std;

COleDateTime timenow(COleDateTime::GetCurrentTime());//系统当前时间

extern string accountNOW = "000";  //用户当前账号，登录后会赋值

extern Processtodo proc{};

const char* file = "data.dat";//学生数据文件

const char* domfile = "dom.dat";	//宿舍楼数据文件

char checkaccount(string acc, string pw) {
	ifstream fread;
	vector<vector<string> >serach;
	vector<string>temparr;
	string tempA;

	//account.txt文件内储存账号，密码，学工号,类型四条信息，目前未加密，期望实现RSA加密
	fread.open("account.txt", ios_base::in);
	if (!fread.is_open()) {
		cerr << "ERROR,CAN NOT OPEN THIS FILE.";
		Sleep(300);
		exit(EXIT_FAILURE);
	}

	serach.resize(100);
	int ct = 0;
	fread.ignore();

	while (getline(fread, tempA)) {
		fread >> tempA;
		string temp;
		stringstream ss(tempA);
		while (getline(ss, temp, ','))
			serach[ct].push_back(temp);
		ct++;
	}

	fread.close();
	/*将account.txt中的数据写入serach二维数组中,遍历这个数组匹配账号和密码，
	并返回匹配的账户种类，进入对应的页面，实现账号系统分离*/

	serach.resize(ct - 1);

	for (auto tp : serach) {
		if (tp[0] == acc)
			if (tp[1] == pw) {
				accountNOW = tp[2];
				if (tp[3] == "student") return 'S';
				else if (tp[3] == "teacher") return 'T';
			}
	}
	return 'F';
}

void streamprocess(string& str) {
	stringstream ss(str);
	string temp;
	vector<string>temparr;

	/*用stringstream函数处理输入的字符串，以';'为条目分隔符，','为条目中的信息分隔符*/

	while (getline(ss, temp, ';'))
		temparr.push_back(temp);
	for (auto& arr : temparr) {
		proc.Infoprocess(arr);
	}
}

void Processtodo::Infoprocess(string& str) {
	stringstream ss(str);
	Studentinfo st;
	Dormitory dom;
	string temp;
	vector<string>temparr;

	while (getline(ss, temp, ','))
		temparr.push_back(temp);

	if (temparr.size() != 7)//只能存基本数据，核酸另行输入
	{
		gotoxy(25, 25, "ERROR:数据缺失（部分学生条目信息不全）");
		Sleep(2000);
		return;
	}

	//写入data.dat(二进制方式）   

	//数据查重
	/*if (SearchAndCheck(temparr[1]) != "pass") {
		gotoxy(25, 28, "ERROR:存在重复学号:");
		Sleep(2000);
		return;
	}*/

	ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);	  //这是用来写学生信息的

	if (!fout.is_open()) {
		cerr << "无法打开" << file << ",出现错误";
		Sleep(500);
		exit(EXIT_FAILURE);
	}

	st.name = temparr[0];
	st.id = temparr[1];
	st.telephone = temparr[2];
	st.school = temparr[3];
	st.address = temparr[5];
	st.classnum = temparr[4];
	st.vaccine = temparr[6];

	fout.write((char*)&st, sizeof Studentinfo) << flush;
	fout.close();

	fstream fdom(domfile, ios_base::in | ios_base::out | ios_base::binary);//这是用来写宿舍信息的
	if (!fdom.is_open()) {
		cerr << "无法打开dom.dat,出现错误";
		Sleep(500);
		exit(EXIT_FAILURE);
	}

	fdom.seekg(0);
	long ct = 0;
	while (fdom.read((char*)&dom, sizeof Dormitory)) {
		if (temparr[5] == dom.buildingname) {
			dom.people++;
			//开始写入
			streampos place = ct * sizeof Dormitory;
			fdom.seekg(place);
			fdom.write((char*)&dom, sizeof Dormitory) << flush;

			if (fdom.fail()) {
				cerr << "ERROR,无法读写文件";
				Sleep(600);
				exit(EXIT_FAILURE);
			}
			fdom.close();
			return;
		}
		ct++;
	}
	fdom.close();

	//如果不存在该宿舍楼，追加
	ofstream fdomadd(domfile, ios_base::out | ios_base::app | ios_base::binary);
	dom.buildingname = temparr[5];
	dom.state = "正常";
	dom.people = 1;
	fdomadd.write((char*)&dom, sizeof Dormitory) << flush;
	fdomadd.close();
}

//暂不可用
string Processtodo::SearchAndCheck(const string &idT) {
	Studentinfo st;
	fstream finout;
	string defaul{"pass"};
	finout.open(file, ios::in | ios::out | ios::binary);
	if (finout.is_open()) {
		finout.seekg(0);
		while (finout.read((char*)&st, sizeof st)) {
			if (st.id == idT) {
				cout << st.name;
				defaul = idT;
				break;
			}
		}
	}
	finout.close();
	return defaul;
}

bool Processtodo::checkapply(vector<string>& info) {
	ifstream fread;
	{
		Studentinfo st;
		fread.open(file, ios_base::in | ios_base::binary);
		fread.seekg(0);
		while (fread.read((char*)&st, sizeof Studentinfo)) {
			if (st.id == accountNOW) {
				if (st.Applystate != "000") {
					info.push_back(st.Applystate);
					info.push_back(st.ApplyIndate);
					info.push_back(st.ApplyOutdate);
					info.push_back(st.Applyreason);
					info.push_back(st.Applycampus);
					info.push_back(st.Applyway);
					fread.close();
					return true;
				}
				else break;
				//000代表未申请状态，也是初始化状态
			}
		}
	}
	fread.close();
	return false;
}

void Processtodo::toapply() {
	fstream finout;
	finout.open(file, ios::in | ios::out | ios::binary);
	{
		Studentinfo st;
		string name;
		long ct = 0;
		if (!finout.is_open()) {
			cerr << file << " could not be opened";
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
		finout.seekg(0);

		while (finout.read((char*)&st, sizeof Studentinfo)) {
			if (st.id == accountNOW) {
				name = st.name;
				break;
			}
			ct++;
		}
		streampos place = ct * sizeof Studentinfo;	//用于记录该条记录的位置，不必重复重头查，优化程序

		while (1) {
			cls();
			gotoxy(60, 5, "上海交通大学学生进出校审批流程");
			gotoxy(30, 10, "姓名：");
			cout << name;
			gotoxy(70, 10, "学号：");
			cout << accountNOW;
			gotoxy(30, 13, "进出校方式（填数字），[1]仅进校；[2]仅出校;[3]先进后出;[4]先出后进:   ");
			showcursor();
			getline(cin, st.Applyway);

			if (st.Applyway == "1") {
				st.Applyway = "仅进校";
				gotoxy(30, 16, "进校时间，格式YYMMDD，如20221202:  ");
				getline(cin, st.ApplyIndate);
			}
			else if (st.Applyway == "2") {
				st.Applyway = "仅出校";
				gotoxy(30, 16, "出校时间，格式YYMMDD，如20221202:  ");
				getline(cin, st.ApplyOutdate);
			}
			else if (st.Applyway == "3" || st.Applyway == "4") {
				if (st.Applyway == "3") st.Applyway = "先进后出";
				else st.Applyway = "先出后进";
				gotoxy(30, 16, "进校时间，格式YYMMDD，如20221202:  ");
				gotoxy(30, 19, "出校时间，格式YYMMDD，如20221202:  ");
				gotoxy(80, 16);
				getline(cin, st.ApplyIndate);
				gotoxy(80, 19);
				getline(cin, st.ApplyOutdate);
			}
			else {
				cout << "数据错误，重新开始流程";
				Sleep(1000);
				continue;
			}

			gotoxy(30, 22, "选择校区[1]徐汇校区，[2]闵行校区   ");
			getline(cin, st.Applycampus);
			if (st.Applycampus == "1") st.Applycampus = "徐汇校区";
			else if (st.Applycampus == "2") st.Applycampus = "闵行校区";
			gotoxy(30, 25, "理由填写：");
			getline(cin, st.Applyreason);

			//applystate为审批状态（“000”为默认无审批）
			st.Applystate = "待审核";
			if (st.Applycampus != "徐汇校区" && st.Applycampus != "闵行校区") {
				cout << "数据错误，重新开始流程";
				Sleep(1000);
				continue;
			}
			break;
		}
		//开始写入文件
		finout.seekg(place);
		finout.write((char*)&st, sizeof Studentinfo) << flush;
		if (finout.fail()) {
			cerr << "ERROR,无法读写文件";
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
	}
	finout.close();
	hidecursor();
}

void Processtodo::teacherapply() {
	fstream finout;
	finout.open(file, ios::in | ios::out | ios::binary);
	{
		Studentinfo st;
		string name;
		if (!finout.is_open()) {
			cerr << file << " could not be opened";
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
		finout.seekg(0);

		gotoxy(0, 5);
		showcursor();

		long ct = 0;
		while (finout.read((char*)&st, sizeof Studentinfo)) {
			if (st.Applystate == "待审核") {
				cout <<
					format("姓名：{}；学号{}；学院{}；班级：{}；进出校方式：{}；进校时间：{}；出校时间：{}；校区：{}"
					, st.name, st.id, st.school, st.classnum, st.Applyway, st.ApplyIndate, st.ApplyOutdate, st.Applycampus);
				cout << "\n理由：" << st.Applyreason << endl;
				cout << "审批意见：[1]同意；[2]驳回   ";
				while (1) {
					int keyin;
					cin >> keyin;
					if (keyin == 1) {
						st.Applystate = "已通过";
						break;
					}
					else if (keyin == 2) {
						st.Applystate = "已驳回";
						break;
					}
				}
				streampos place = ct * sizeof Studentinfo;
				finout.seekg(place);
				finout.write((char*)&st, sizeof Studentinfo) << flush;
			}
			ct++;
		}
	}
	finout.close();
	hidecursor();
}

void Processtodo::deleteapply() {
	fstream finout;
	finout.open(file, ios::in | ios::out | ios::binary);
	{
		Studentinfo st;
		string name;
		long ct = 0;
		if (!finout.is_open()) {
			cerr << file << " could not be opened";
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
		finout.seekg(0);

		while (finout.read((char*)&st, sizeof Studentinfo)) {
			if (st.id == accountNOW) {
				st.Applystate = "000";
				break;
			}
			ct++;
		}
		streampos place = ct * sizeof Studentinfo;	//用于记录该条记录的位置，不必重复重头查，优化程序
		finout.seekg(place);
		finout.write((char*)&st, sizeof Studentinfo) << flush;
	}
	finout.close();
}

void Processtodo::getPCR() {
	ifstream fread;
	fread.open(domfile, ios_base::in | ios_base::binary);
	fread.seekg(0);
	gotoxy(60, 3, "各楼栋核酸信息如下");
	gotoxy(0, 5, "楼栋          总人数          已检测人数");
	gotoxy(0, 7);
	{
		Dormitory dom;
		while (fread.read((char*)&dom, sizeof Dormitory))
			cout << format("{}             {}             {}", dom.buildingname, dom.people, dom.PCRpeople) << endl;
	}
	fread.close();
}

void Processtodo::setstate(string& dormname) {
	fstream finout;
	finout.open("dom.dat", ios::in | ios::out | ios::binary);
	{
		Dormitory dom;
		long ct = 0;
		bool flag = false;

		if (!finout.is_open()) {
			cerr << file << " could not be opened";
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
		finout.seekg(0);

		while (finout.read((char*)&dom, sizeof Dormitory)) {
			if (dom.buildingname == dormname) {
				flag = true;
				break;
			}
			ct++;
		}

		if (!flag) {
			gotoxy(80, 15, "找不到该宿舍楼信息");
			return;
		}

		streampos place = ct * sizeof Dormitory;
		gotoxy(30, 5, "宿舍状态：");
		cout << dom.state;

		if (dom.state == "封控") {
			CString start, end;//封控起始与开始时间标识
			start = dom.starttime.Format(_T("%Y年%m月%d日"));
			end = dom.endtime.Format(_T("%Y年%m月%d日"));

			gotoxy(30, 8, "起始时间: ");
			wcout << (CT2A)start;
			gotoxy(30, 11, "结束时间: ");
			wcout << (CT2A)end;

			gotoxy(30, 15, "修改");
			printline(14);
			gotoxy(30, 17, "解除该楼封控:[Y/N](按键盘上的对应按键)   ");
			int keyin;
			while (1) {
				keyin = _getch();
				if (keyin == 121) {
					dom.state = "正常";
					break;
				}
				else if (keyin == 110)
					break;
			}
		}
		else {
			gotoxy(30, 12, "修改");
			printline(13);
			gotoxy(30, 15, "设置该楼封控:[Y/N](按键盘上的对应按键)   ");
			int keyin;
			while (1) {
				keyin = _getch();
				if (keyin == 121) {
					dom.state = "封控";
					int styear, stmonth, stday, edyear, edmonth, edday;
					showcursor();
					while (1) {
						gotoxy(30, 17, "起始时间：");
						cin >> styear;
						gotoxy(45, 17, "年  ");
						cin >> stmonth;
						gotoxy(55, 17, "月  ");
						cin >> stday;
						gotoxy(65, 17, "日");
						
						gotoxy(30, 20, "结束时间：");
						cin >> edyear;
						gotoxy(45, 20, "年  ");
						cin >> edmonth;
						gotoxy(55, 20, "月  ");
						cin >> edday;
						gotoxy(65, 20, "日");

						dom.starttime.SetDate(styear, stmonth, stday);
						dom.endtime.SetDate(edyear, edmonth, edday);
						COleDateTimeSpan ts = dom.endtime - dom.starttime;//校验解封日期必须大于封控日期
						cin.ignore();

						if (dom.starttime.GetStatus() != COleDateTime::valid|| ts.GetTotalSeconds() <= 0|| dom.starttime<timenow) {
							cerr << "时间填写错误！";
							cls();
							continue;
						}
						break;
					}

					break;
				}
				else if (keyin == 110)
					break;
			}
		}
		//开始写入
		finout.seekg(place);
		finout.write((char*)&dom, sizeof Dormitory) << flush;
		if (finout.fail()) {
			cerr << "ERROR,无法读写文件";
			Sleep(1000);
			exit(EXIT_FAILURE);
		}
	}
	finout.close();
	hidecursor();
}

void Processtodo::showdormitory() {
	ifstream fread;
	fread.open(domfile, ios_base::in | ios_base::binary);
	fread.seekg(0);
	{
		Dormitory dom;

		struct build {
			string name;
			COleDateTime endT;
		};

		build temp[20];
		int ct = 0;

		while (fread.read((char*)&dom, sizeof Dormitory)) {
			if (dom.state == "封控") {
				temp[ct].endT = dom.endtime;
				temp[ct].name = dom.buildingname;
				ct++;
			}
		}
		gotoxy(20, 3, "封控楼栋信息汇总");
		gotoxy(0, 5, "楼栋                          解封时间");
		gotoxy(0, 7);
		if (ct == 0) return;

		//排序
		for (int i = 0; i < ct - 1; i++)
			for (int j = 0; j < ct - 1 - i; j++)
				if (temp[j].endT > temp[j + 1].endT)
					swap(temp[j], temp[j + 1]);
		//按解封时间先后排序
		for (int i = 0; i < ct; i++)
			cout << temp[i].name << "                             " << (CT2A)temp[i].endT.Format(_T("%Y年%m月%d日")) << endl;
	}
	fread.close();
}

void Processtodo::PCRprocess(string& info) {
	stringstream ss(info);
	string temp;
	string accountT;
	vector<string>temparr;

	/*这里传过来的info是一个人的信息，但可以包含至多五天的核酸信息*/

	/*用stringstream函数处理输入的字符串，以';'为条目分隔符，'.'为条目中的信息分隔符*/

	while (getline(ss, temp, ';'))
		temparr.push_back(temp);
	
	stringstream ac(temparr[0]);
	while(getline(ac, accountT, ','));

	fstream finout;//写入学生文件
	finout.open(file, ios::in | ios::out | ios::binary);
	fstream fdom;//写入该学生关联的宿舍
	fdom.open(domfile, ios::in | ios::out | ios::binary);
	{
		Studentinfo st;
		Dormitory dom;
		PCR tempPCR;
		finout.seekg(0);
		fdom.seekg(0);
		long ctstu = 0, ctdom = 0;//记录文件写入位置 

		while (finout.read((char*)&st, sizeof Studentinfo)) {
			if (accountT == st.id) {
				temparr.erase(temparr.begin(), temparr.begin() + 1);//将数组首的姓名学号去除，只留下核算信息
				int count = 1;//用来记录条目，便于报错时指出是第几条信息出错
				COleDateTimeSpan ts = 100;	//计算现在时间与其核酸时间的差值
				if(st.pcrinfo.size()>5)
					st.pcrinfo.resize(1);//初始化计数

				for (auto tp : temparr) {
					stringstream pcr(tp);		//对每一个单条核酸信息进行处理
					vector<string>concequence;

					while (getline(pcr, temp, '.'))
						concequence.push_back(temp);
					
					if (concequence.size() != 7) {
						cerr << "第" << count << "条数据不全（时间或结果丢失）";
						Sleep(200);
						continue;
					}

					tempPCR.PCRconsequence = concequence[6];
					tempPCR.PCRdate.SetDateTime(stoi(concequence[0]), stoi(concequence[1]), stoi(concequence[2]),
												stoi(concequence[3]), stoi(concequence[4]), stoi(concequence[5]));

					if (st.pcrinfo.size() == 5) //储存最多五次核酸记录
						st.pcrinfo.erase(st.pcrinfo.begin());

					COleDateTimeSpan tempT = timenow - tempPCR.PCRdate;	//计算现在时间与其核酸时间的差值
					if (tempT < ts) ts = tempT;
					st.pcrinfo.push_back(tempPCR);
				}

				//学生信息录入到此结束，现在是楼栋信息维护
				while (fdom.read((char*)&dom, sizeof Dormitory)) {
					if (st.address == dom.buildingname) {
						if (ts.GetTotalDays() == 0)
							dom.PCRpeople++;
						break;
					}
					ctdom++;
				}

				if (ts.GetTotalHours() <= 24)
					st.PCRstate = "24小时核酸";
				else if (ts.GetTotalHours() <= 48)
					st.PCRstate = "48小时核酸";
				else if (ts.GetTotalHours() <= 72)
					st.PCRstate = "72小时核酸";
				else if (ts.GetTotalHours() <= 168)
					st.PCRstate = "七天内核酸";
				else
					st.PCRstate = "未查询到最近七天核酸信息";

				if (ts.GetTotalDays() == 0)	//设置当日核酸状况
					st.isTodayPCR = true;

				//开始写入
				streampos stuplace = ctstu * sizeof Studentinfo;
				streampos domplace = ctdom * sizeof Dormitory;
				finout.seekg(stuplace);
				fdom.seekg(domplace);

				finout.write((char*)&st, sizeof Studentinfo) << flush;
				fdom.write((char*)&dom, sizeof Dormitory) << flush;

				finout.close();
				fdom.close();
				return;
			}
			ctstu++;
		}
	}

	//遍历后无该生信息
	cerr << "找不到该学生";
	finout.close();
	fdom.close();
	Sleep(600);
	return;
}

void Processtodo::CheckClassPCR(string&classinfo) {
	ifstream fread;
	int classpeople = 0;//某班人数
	int PCRpeople = 0;//某班做核酸人数
	{
		Studentinfo st;
		fread.open(file, ios_base::in | ios_base::binary);
		fread.seekg(0);
		while (fread.read((char*)&st, sizeof Studentinfo)) {
			if (classinfo == st.classnum) {
				classpeople++;
				if (st.isTodayPCR)
					PCRpeople++;
			}
		}
		gotoxy(30, 10, "班级：   ");
		cout << classinfo;
		gotoxy(30, 14, "总人数：  ");
		cout << classpeople;
		gotoxy(30, 18, "当日做核酸人数");
		cout << PCRpeople;
	}
	fread.close();
}

void Processtodo::CheckStudentPCR(string& num) {
	ifstream fread;
	{
		Studentinfo st;
		fread.open(file, ios_base::in | ios_base::binary);
		fread.seekg(0);
		while (fread.read((char*)&st, sizeof Studentinfo)) {
			if (num == st.id) {
				gotoxy(40, 5, "查询到以下核酸信息");
				gotoxy(0, 9);
				for (auto p : st.pcrinfo) {
					CString timeT;
					timeT = p.PCRdate.Format(_T("%Y年%m月%d日"));
					cout << format("检测时间：{}   结果：{}", (CT2A)timeT, p.PCRconsequence) << endl;
				}
			}
		}
	}
	fread.close();
}