#include"Win_define.h"
#include"database.h"
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<format>
#include<memory>
using namespace std;

COleDateTime timenow(COleDateTime::GetCurrentTime());//ϵͳ��ǰʱ��

extern string accountNOW = "000";  //�û���ǰ�˺ţ���¼��ḳֵ

extern Processtodo proc{};

const char* file = "data.dat";//ѧ�������ļ�

const char* domfile = "dom.dat";	//����¥�����ļ�

char checkaccount(string acc, string pw) {
	ifstream fread;
	vector<vector<string> >serach;
	vector<string>temparr;
	string tempA;

	//account.txt�ļ��ڴ����˺ţ����룬ѧ����,����������Ϣ��Ŀǰδ���ܣ�����ʵ��RSA����
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
	/*��account.txt�е�����д��serach��ά������,�����������ƥ���˺ź����룬
	������ƥ����˻����࣬�����Ӧ��ҳ�棬ʵ���˺�ϵͳ����*/

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

	/*��stringstream��������������ַ�������';'Ϊ��Ŀ�ָ�����','Ϊ��Ŀ�е���Ϣ�ָ���*/

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

	if (temparr.size() != 7)//ֻ�ܴ�������ݣ�������������
	{
		gotoxy(25, 25, "ERROR:����ȱʧ������ѧ����Ŀ��Ϣ��ȫ��");
		Sleep(2000);
		return;
	}

	//д��data.dat(�����Ʒ�ʽ��   

	//���ݲ���
	/*if (SearchAndCheck(temparr[1]) != "pass") {
		gotoxy(25, 28, "ERROR:�����ظ�ѧ��:");
		Sleep(2000);
		return;
	}*/

	ofstream fout(file, ios_base::out | ios_base::app | ios_base::binary);	  //��������дѧ����Ϣ��

	if (!fout.is_open()) {
		cerr << "�޷���" << file << ",���ִ���";
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

	fstream fdom(domfile, ios_base::in | ios_base::out | ios_base::binary);//��������д������Ϣ��
	if (!fdom.is_open()) {
		cerr << "�޷���dom.dat,���ִ���";
		Sleep(500);
		exit(EXIT_FAILURE);
	}

	fdom.seekg(0);
	long ct = 0;
	while (fdom.read((char*)&dom, sizeof Dormitory)) {
		if (temparr[5] == dom.buildingname) {
			dom.people++;
			//��ʼд��
			streampos place = ct * sizeof Dormitory;
			fdom.seekg(place);
			fdom.write((char*)&dom, sizeof Dormitory) << flush;

			if (fdom.fail()) {
				cerr << "ERROR,�޷���д�ļ�";
				Sleep(600);
				exit(EXIT_FAILURE);
			}
			fdom.close();
			return;
		}
		ct++;
	}
	fdom.close();

	//��������ڸ�����¥��׷��
	ofstream fdomadd(domfile, ios_base::out | ios_base::app | ios_base::binary);
	dom.buildingname = temparr[5];
	dom.state = "����";
	dom.people = 1;
	fdomadd.write((char*)&dom, sizeof Dormitory) << flush;
	fdomadd.close();
}

//�ݲ�����
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
				//000����δ����״̬��Ҳ�ǳ�ʼ��״̬
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
		streampos place = ct * sizeof Studentinfo;	//���ڼ�¼������¼��λ�ã������ظ���ͷ�飬�Ż�����

		while (1) {
			cls();
			gotoxy(60, 5, "�Ϻ���ͨ��ѧѧ������У��������");
			gotoxy(30, 10, "������");
			cout << name;
			gotoxy(70, 10, "ѧ�ţ�");
			cout << accountNOW;
			gotoxy(30, 13, "����У��ʽ�������֣���[1]����У��[2]����У;[3]�Ƚ����;[4]�ȳ����:   ");
			showcursor();
			getline(cin, st.Applyway);

			if (st.Applyway == "1") {
				st.Applyway = "����У";
				gotoxy(30, 16, "��Уʱ�䣬��ʽYYMMDD����20221202:  ");
				getline(cin, st.ApplyIndate);
			}
			else if (st.Applyway == "2") {
				st.Applyway = "����У";
				gotoxy(30, 16, "��Уʱ�䣬��ʽYYMMDD����20221202:  ");
				getline(cin, st.ApplyOutdate);
			}
			else if (st.Applyway == "3" || st.Applyway == "4") {
				if (st.Applyway == "3") st.Applyway = "�Ƚ����";
				else st.Applyway = "�ȳ����";
				gotoxy(30, 16, "��Уʱ�䣬��ʽYYMMDD����20221202:  ");
				gotoxy(30, 19, "��Уʱ�䣬��ʽYYMMDD����20221202:  ");
				gotoxy(80, 16);
				getline(cin, st.ApplyIndate);
				gotoxy(80, 19);
				getline(cin, st.ApplyOutdate);
			}
			else {
				cout << "���ݴ������¿�ʼ����";
				Sleep(1000);
				continue;
			}

			gotoxy(30, 22, "ѡ��У��[1]���У����[2]����У��   ");
			getline(cin, st.Applycampus);
			if (st.Applycampus == "1") st.Applycampus = "���У��";
			else if (st.Applycampus == "2") st.Applycampus = "����У��";
			gotoxy(30, 25, "������д��");
			getline(cin, st.Applyreason);

			//applystateΪ����״̬����000��ΪĬ����������
			st.Applystate = "�����";
			if (st.Applycampus != "���У��" && st.Applycampus != "����У��") {
				cout << "���ݴ������¿�ʼ����";
				Sleep(1000);
				continue;
			}
			break;
		}
		//��ʼд���ļ�
		finout.seekg(place);
		finout.write((char*)&st, sizeof Studentinfo) << flush;
		if (finout.fail()) {
			cerr << "ERROR,�޷���д�ļ�";
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
			if (st.Applystate == "�����") {
				cout <<
					format("������{}��ѧ��{}��ѧԺ{}���༶��{}������У��ʽ��{}����Уʱ�䣺{}����Уʱ�䣺{}��У����{}"
					, st.name, st.id, st.school, st.classnum, st.Applyway, st.ApplyIndate, st.ApplyOutdate, st.Applycampus);
				cout << "\n���ɣ�" << st.Applyreason << endl;
				cout << "���������[1]ͬ�⣻[2]����   ";
				while (1) {
					int keyin;
					cin >> keyin;
					if (keyin == 1) {
						st.Applystate = "��ͨ��";
						break;
					}
					else if (keyin == 2) {
						st.Applystate = "�Ѳ���";
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
		streampos place = ct * sizeof Studentinfo;	//���ڼ�¼������¼��λ�ã������ظ���ͷ�飬�Ż�����
		finout.seekg(place);
		finout.write((char*)&st, sizeof Studentinfo) << flush;
	}
	finout.close();
}

void Processtodo::getPCR() {
	ifstream fread;
	fread.open(domfile, ios_base::in | ios_base::binary);
	fread.seekg(0);
	gotoxy(60, 3, "��¥��������Ϣ����");
	gotoxy(0, 5, "¥��          ������          �Ѽ������");
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
			gotoxy(80, 15, "�Ҳ���������¥��Ϣ");
			return;
		}

		streampos place = ct * sizeof Dormitory;
		gotoxy(30, 5, "����״̬��");
		cout << dom.state;

		if (dom.state == "���") {
			CString start, end;//�����ʼ�뿪ʼʱ���ʶ
			start = dom.starttime.Format(_T("%Y��%m��%d��"));
			end = dom.endtime.Format(_T("%Y��%m��%d��"));

			gotoxy(30, 8, "��ʼʱ��: ");
			wcout << (CT2A)start;
			gotoxy(30, 11, "����ʱ��: ");
			wcout << (CT2A)end;

			gotoxy(30, 15, "�޸�");
			printline(14);
			gotoxy(30, 17, "�����¥���:[Y/N](�������ϵĶ�Ӧ����)   ");
			int keyin;
			while (1) {
				keyin = _getch();
				if (keyin == 121) {
					dom.state = "����";
					break;
				}
				else if (keyin == 110)
					break;
			}
		}
		else {
			gotoxy(30, 12, "�޸�");
			printline(13);
			gotoxy(30, 15, "���ø�¥���:[Y/N](�������ϵĶ�Ӧ����)   ");
			int keyin;
			while (1) {
				keyin = _getch();
				if (keyin == 121) {
					dom.state = "���";
					int styear, stmonth, stday, edyear, edmonth, edday;
					showcursor();
					while (1) {
						gotoxy(30, 17, "��ʼʱ�䣺");
						cin >> styear;
						gotoxy(45, 17, "��  ");
						cin >> stmonth;
						gotoxy(55, 17, "��  ");
						cin >> stday;
						gotoxy(65, 17, "��");
						
						gotoxy(30, 20, "����ʱ�䣺");
						cin >> edyear;
						gotoxy(45, 20, "��  ");
						cin >> edmonth;
						gotoxy(55, 20, "��  ");
						cin >> edday;
						gotoxy(65, 20, "��");

						dom.starttime.SetDate(styear, stmonth, stday);
						dom.endtime.SetDate(edyear, edmonth, edday);
						COleDateTimeSpan ts = dom.endtime - dom.starttime;//У�������ڱ�����ڷ������
						cin.ignore();

						if (dom.starttime.GetStatus() != COleDateTime::valid|| ts.GetTotalSeconds() <= 0|| dom.starttime<timenow) {
							cerr << "ʱ����д����";
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
		//��ʼд��
		finout.seekg(place);
		finout.write((char*)&dom, sizeof Dormitory) << flush;
		if (finout.fail()) {
			cerr << "ERROR,�޷���д�ļ�";
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
			if (dom.state == "���") {
				temp[ct].endT = dom.endtime;
				temp[ct].name = dom.buildingname;
				ct++;
			}
		}
		gotoxy(20, 3, "���¥����Ϣ����");
		gotoxy(0, 5, "¥��                          ���ʱ��");
		gotoxy(0, 7);
		if (ct == 0) return;

		//����
		for (int i = 0; i < ct - 1; i++)
			for (int j = 0; j < ct - 1 - i; j++)
				if (temp[j].endT > temp[j + 1].endT)
					swap(temp[j], temp[j + 1]);
		//�����ʱ���Ⱥ�����
		for (int i = 0; i < ct; i++)
			cout << temp[i].name << "                             " << (CT2A)temp[i].endT.Format(_T("%Y��%m��%d��")) << endl;
	}
	fread.close();
}

void Processtodo::PCRprocess(string& info) {
	stringstream ss(info);
	string temp;
	string accountT;
	vector<string>temparr;

	/*���ﴫ������info��һ���˵���Ϣ�������԰�����������ĺ�����Ϣ*/

	/*��stringstream��������������ַ�������';'Ϊ��Ŀ�ָ�����'.'Ϊ��Ŀ�е���Ϣ�ָ���*/

	while (getline(ss, temp, ';'))
		temparr.push_back(temp);
	
	stringstream ac(temparr[0]);
	while(getline(ac, accountT, ','));

	fstream finout;//д��ѧ���ļ�
	finout.open(file, ios::in | ios::out | ios::binary);
	fstream fdom;//д���ѧ������������
	fdom.open(domfile, ios::in | ios::out | ios::binary);
	{
		Studentinfo st;
		Dormitory dom;
		PCR tempPCR;
		finout.seekg(0);
		fdom.seekg(0);
		long ctstu = 0, ctdom = 0;//��¼�ļ�д��λ�� 

		while (finout.read((char*)&st, sizeof Studentinfo)) {
			if (accountT == st.id) {
				temparr.erase(temparr.begin(), temparr.begin() + 1);//�������׵�����ѧ��ȥ����ֻ���º�����Ϣ
				int count = 1;//������¼��Ŀ�����ڱ���ʱָ���ǵڼ�����Ϣ����
				COleDateTimeSpan ts = 100;	//��������ʱ���������ʱ��Ĳ�ֵ
				if(st.pcrinfo.size()>5)
					st.pcrinfo.resize(1);//��ʼ������

				for (auto tp : temparr) {
					stringstream pcr(tp);		//��ÿһ������������Ϣ���д���
					vector<string>concequence;

					while (getline(pcr, temp, '.'))
						concequence.push_back(temp);
					
					if (concequence.size() != 7) {
						cerr << "��" << count << "�����ݲ�ȫ��ʱ�������ʧ��";
						Sleep(200);
						continue;
					}

					tempPCR.PCRconsequence = concequence[6];
					tempPCR.PCRdate.SetDateTime(stoi(concequence[0]), stoi(concequence[1]), stoi(concequence[2]),
												stoi(concequence[3]), stoi(concequence[4]), stoi(concequence[5]));

					if (st.pcrinfo.size() == 5) //���������κ����¼
						st.pcrinfo.erase(st.pcrinfo.begin());

					COleDateTimeSpan tempT = timenow - tempPCR.PCRdate;	//��������ʱ���������ʱ��Ĳ�ֵ
					if (tempT < ts) ts = tempT;
					st.pcrinfo.push_back(tempPCR);
				}

				//ѧ����Ϣ¼�뵽�˽�����������¥����Ϣά��
				while (fdom.read((char*)&dom, sizeof Dormitory)) {
					if (st.address == dom.buildingname) {
						if (ts.GetTotalDays() == 0)
							dom.PCRpeople++;
						break;
					}
					ctdom++;
				}

				if (ts.GetTotalHours() <= 24)
					st.PCRstate = "24Сʱ����";
				else if (ts.GetTotalHours() <= 48)
					st.PCRstate = "48Сʱ����";
				else if (ts.GetTotalHours() <= 72)
					st.PCRstate = "72Сʱ����";
				else if (ts.GetTotalHours() <= 168)
					st.PCRstate = "�����ں���";
				else
					st.PCRstate = "δ��ѯ��������������Ϣ";

				if (ts.GetTotalDays() == 0)	//���õ��պ���״��
					st.isTodayPCR = true;

				//��ʼд��
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

	//�������޸�����Ϣ
	cerr << "�Ҳ�����ѧ��";
	finout.close();
	fdom.close();
	Sleep(600);
	return;
}

void Processtodo::CheckClassPCR(string&classinfo) {
	ifstream fread;
	int classpeople = 0;//ĳ������
	int PCRpeople = 0;//ĳ������������
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
		gotoxy(30, 10, "�༶��   ");
		cout << classinfo;
		gotoxy(30, 14, "��������  ");
		cout << classpeople;
		gotoxy(30, 18, "��������������");
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
				gotoxy(40, 5, "��ѯ�����º�����Ϣ");
				gotoxy(0, 9);
				for (auto p : st.pcrinfo) {
					CString timeT;
					timeT = p.PCRdate.Format(_T("%Y��%m��%d��"));
					cout << format("���ʱ�䣺{}   �����{}", (CT2A)timeT, p.PCRconsequence) << endl;
				}
			}
		}
	}
	fread.close();
}