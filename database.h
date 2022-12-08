#pragma once
#include<string>
#include<vector>
#include<ATLComTime.h>	//����ʱ���һ����
using std::string;
using std::vector;

class Studentinfo {
public:
	//��������
	string name = "NA";
	string id = "000";
	string telephone = "000";
	string school = "NA";
	string address = "NA";
	string classnum = "NA";
	string vaccine = "NA";
	//��������
	string PCRstate = "NA";//����״̬��24Сʱ/48Сʱ/72Сʱ
	bool isTodayPCR = false;//�Ƿ��ǵ��պ���
	//��������
	string Applystate = "000";
	string ApplyIndate = "000";
	string ApplyOutdate = "000";
	string Applyreason = "NA";
	string Applycampus = "NA";
	string Applyway = "1";
	//��������
	COleDateTime PCRdate;
	string PCRconsequence = "NA";//��Ϊ�������һ�κ����¼

};

class Dormitory {
public:
	string buildingname = "NA";
	string state = "NA";
	COleDateTime starttime{};
	COleDateTime endtime{};
	long people = 0;
	long PCRpeople = 0;
};

class Processtodo {
public:
	Studentinfo st[100];
	Dormitory dom[40];

	//��studentinfo��Ĳ���
	void Infoprocess(string&);//���ηָ��������
	string SearchAndCheck(const string&);//�������������
	bool checkapply(vector<string>& info);//��ѯ�Ƿ���������Լ����������¼
	void toapply();//��������
	void deleteapply();//ѧ��ɾ������
	void teacherapply();//��ʦ��������У
	void CheckClassPCR(string&);//���༶��ѯ������Ϣ
	void CheckStudentPCR(string&);//��ѧ�Ų�ѯ������Ϣ
	//��dormtory��Ĳ���
	void getPCR(); //��ȡ����¥��������
	void setstate(string&); //����¥��״̬
	void showdormitory();	//��ʾ�����ʱ������ı����¥��
	void PCRprocess(string&);//����PCR����
};


char checkaccount(string,string);  //У�������˺��Ƿ����

void SearchPCRforTeacher();//����������ʦ��ѯҳ��

void StudentApply();//����У����ѧ����

void BasicDataStream();//¼�������Ϣ

void PCRDataStream();//¼�������Ϣ

void streamprocess(string&);	//�����ַ����ָ�

void Application();	//����У�����ʦ��

void DormitoryManage();//����¥�������

void SearchPCRforStudent();//����������ѯѧ����
