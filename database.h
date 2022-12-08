#pragma once
#include<string>
#include<vector>
#include<ATLComTime.h>	//定义时间的一个类
using std::string;
using std::vector;

class Studentinfo {
public:
	//基本数据
	string name = "NA";
	string id = "000";
	string telephone = "000";
	string school = "NA";
	string address = "NA";
	string classnum = "NA";
	string vaccine = "NA";
	//核酸数据
	string PCRstate = "NA";//核酸状态：24小时/48小时/72小时
	bool isTodayPCR = false;//是否是当日核酸
	//审批数据
	string Applystate = "000";
	string ApplyIndate = "000";
	string ApplyOutdate = "000";
	string Applyreason = "NA";
	string Applycampus = "NA";
	string Applyway = "1";
	//核酸数据
	COleDateTime PCRdate;
	string PCRconsequence = "NA";//改为保留最后一次核酸记录

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

	//对studentinfo类的操作
	void Infoprocess(string&);//二次分割数据入库
	string SearchAndCheck(const string&);//数据搜索与查重
	bool checkapply(vector<string>& info);//查询是否存在申请以及返回申请记录
	void toapply();//进行申请
	void deleteapply();//学生删除申请
	void teacherapply();//教师审批出入校
	void CheckClassPCR(string&);//按班级查询核酸信息
	void CheckStudentPCR(string&);//按学号查询核酸信息
	//对dormtory类的操作
	void getPCR(); //获取宿舍楼核酸人数
	void setstate(string&); //设置楼栋状态
	void showdormitory();	//显示按解封时间排序的被封控楼栋
	void PCRprocess(string&);//处理PCR内容
};


char checkaccount(string,string);  //校验输入账号是否存在

void SearchPCRforTeacher();//核酸检测结果教师查询页面

void StudentApply();//进出校申请学生端

void BasicDataStream();//录入基本信息

void PCRDataStream();//录入核酸信息

void streamprocess(string&);	//处理字符串分割

void Application();	//进出校申请教师端

void DormitoryManage();//宿舍楼管理界面

void SearchPCRforStudent();//核酸检测结果查询学生端
