#pragma once
#include<string>
#include<vector>
#include<ATLComTime.h>	//����ʱ���һ����
#include<sstream>
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
    string temperature = "NA";
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
    long capacity = 0;
    string admin = "NA";
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
    void addinfo();  //ά��¥����Ϣ����ȫ������
};

class Util //��Ϣ�зֹ���
{
public:
    // �����Ե���char�ַ���Ϊ�ָ�����string�ַ������зָ �����ָ�������vector�У����շ���vector<string>
    static std::vector<string> split(const std::string& s, char delimiter)
    {                                      //  n.	��������ָ���;
        std::vector<string> tokens;        // ��Ž��
        std::string token;                 // �Ӵ�
        std::istringstream tokenStream(s); //ʹ��string s��ʼ��������, ��׼��ͷ�ļ� <sstream>
        while (std::getline(tokenStream, token,
            delimiter))
        {                       //  ����������������char��delimiterʱ ��ֹͣ �ѽ��������token��, (ͬʱ�������������char), ������<string>
            if (!token.empty()) //��Ϊ������������delimiter���������ʱ��token���ǿգ����������Ҫ����tokens����
                tokens.push_back(token);
        }
        return tokens;
    }

    // ������string��Ϊ�ָ�����string�ַ������зָ �����ָ�������vector�У����շ���vector<string>
    static std::vector<string> split(const std::string& s, const std::string& delimiter)
    {                                                                               //  n.	��������ָ���;
        std::vector<string> tokens;                                                 // ��Ž��
        std::string token;                                                          // �Ӵ�
        int i = 0, start = 0, sSize = (int)s.size(), dSize = (int)delimiter.size(); // startΪ�ַ��Ӵ�����ʼλ��
        while (i < sSize)
        {
            if (isDelimiter2(s, i, delimiter))
            {                                       // �˴�Ҳ����ʹ��isDelimiter(s, i, delimiter)  ��������˷ָ���
                token = s.substr(start, i - start); // �ָ��ַ���
                if (!token.empty())
                { // ��Ϊ������������delimiter���������ʱ��token���ǿգ����������Ҫ����tokens����
                    tokens.push_back(token);
                }
                i += dSize; // �����ָ����ĳ���
                start = i;  // �����Ӵ�����ʼλ��
            }
            else
                i++;
        }
        token = s.substr(start, i - start); // �ָ��ַ���
        if (!token.empty())
        { //��Ϊ������������delimiter���������ʱ��token���ǿգ����������Ҫ����tokens����
            tokens.push_back(token);
        }
        return tokens;
    }

private:
    // �����ж��ַ���s���±�i��ʼ�ģ���Ϊdelimiter���ַ��Ӵ��Ƿ��delimiterȫ��
    static bool isDelimiter(const std::string& s, int i, const std::string& delimiter)
    {
        int j = 0, sSize = (int)s.size(), dSize = (int)delimiter.size();
        while (i < sSize && j < dSize)
        {
            if (s[i] != delimiter[j])
                return false;
            else
            {
                j++;
                i++;
            }
        }
        return j == dSize;
    }

    // �����ж��ַ���s���±�i��ʼ�ģ���Ϊdelimiter���ַ��Ӵ��Ƿ��delimiterȫ��
    static bool isDelimiter2(const std::string& s, int i, const std::string& delimiter)
    {
        return s.substr(i, delimiter.size()) == delimiter;
    }
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
