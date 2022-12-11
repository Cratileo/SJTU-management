#pragma once
#include<string>
#include<vector>
#include<ATLComTime.h>	//定义时间的一个类
#include<sstream>
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
    string temperature = "NA";
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
    long capacity = 0;
    string admin = "NA";
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
    void addinfo();  //维护楼栋信息不完全的内容
};

class Util //信息切分工具
{
public:
    // 函数以单个char字符作为分隔符对string字符串进行分割， 并将分割结果存入vector中，最终返回vector<string>
    static std::vector<string> split(const std::string& s, char delimiter)
    {                                      //  n.	定界符，分隔符;
        std::vector<string> tokens;        // 存放结果
        std::string token;                 // 子串
        std::istringstream tokenStream(s); //使用string s初始化输入流, 标准库头文件 <sstream>
        while (std::getline(tokenStream, token,
            delimiter))
        {                       //  对于输入流，遇到char的delimiter时 就停止 把结果储存在token中, (同时舍弃遇到的这个char), 定义于<string>
            if (!token.empty()) //因为会遇到连续的delimiter的情况，这时候token就是空，这种情况不要放入tokens当中
                tokens.push_back(token);
        }
        return tokens;
    }

    // 函数以string作为分隔符对string字符串进行分割， 并将分割结果存入vector中，最终返回vector<string>
    static std::vector<string> split(const std::string& s, const std::string& delimiter)
    {                                                                               //  n.	定界符，分隔符;
        std::vector<string> tokens;                                                 // 存放结果
        std::string token;                                                          // 子串
        int i = 0, start = 0, sSize = (int)s.size(), dSize = (int)delimiter.size(); // start为字符子串的起始位置
        while (i < sSize)
        {
            if (isDelimiter2(s, i, delimiter))
            {                                       // 此处也可以使用isDelimiter(s, i, delimiter)  如果遇到了分隔符
                token = s.substr(start, i - start); // 分割字符串
                if (!token.empty())
                { // 因为会遇到连续的delimiter的情况，这时候token就是空，这种情况不要放入tokens当中
                    tokens.push_back(token);
                }
                i += dSize; // 跳过分隔符的长度
                start = i;  // 更新子串的起始位置
            }
            else
                i++;
        }
        token = s.substr(start, i - start); // 分割字符串
        if (!token.empty())
        { //因为会遇到连续的delimiter的情况，这时候token就是空，这种情况不要放入tokens当中
            tokens.push_back(token);
        }
        return tokens;
    }

private:
    // 函数判断字符串s从下标i开始的，长为delimiter的字符子串是否和delimiter全等
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

    // 函数判断字符串s从下标i开始的，长为delimiter的字符子串是否和delimiter全等
    static bool isDelimiter2(const std::string& s, int i, const std::string& delimiter)
    {
        return s.substr(i, delimiter.size()) == delimiter;
    }
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
