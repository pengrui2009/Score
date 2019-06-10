#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
// #include <stdio.h> 
// #include <stdlib.h> 
// #include <string.h>
//#include <conio.h> 

// #define N 3
// struct  student 
// {
//     char name[10];
//     char no[10];
//     char sex;
//     int  age;
//     char bnote[100];
// };

using namespace std;

struct StudentScore{
    int serialNum;//序号
    int id;//学号
    string name;//姓名
    string major;//专业
    float regularScore;//平时成绩
    float midtermScore;//期中成绩
    float examScore;//期末成绩 
    float finalScore;//总评成绩
};

StudentScore stu[10000];
int totalcount = 0;

//输出到屏幕
void printScore(StudentScore *stu) 
{
    cout << "序号    :" << stu->serialNum << endl;
    cout << "学号    :" << stu->id << endl;
    cout << "姓名    :" << stu->name << endl;
    cout << "专业    :" << stu->major << endl;
    cout << "平时成绩 :" << stu->regularScore << endl;
    cout << "期中成绩 :" << stu->midtermScore << endl;
    cout << "期末成绩 :" << stu->examScore << endl;
    cout << "总评成绩 :" << stu->finalScore << endl;
}

//解析一行文本
void parseScore(StudentScore *s, string str) 
{
    //1     200637096       王莎莎      保险0605        85      80      51
    if(s != NULL )
    {
        int flag = 0;
        int flag1 = 0;
        string temp ;

        //
        for(auto iter = str.begin(); iter != str.end(); ++iter)
        {
            if((*iter != ' ') && (*iter != '\t'))
            {
                //有效数据标志
                flag1 = 1;
                temp += *iter;
            } else {
                if(!flag1)
                {
                    continue;
                }
                
                //数据内容
                switch(flag)
                {
                case 0:
                    s->serialNum = stoi(temp);
                    flag++;
                    break;
                case 1:
                    s->id = stoi(temp);
                    flag++;
                    break;
                case 2:
                    s->name = temp;
                    flag++;
                    break;
                case 3:
                    s->major = temp;
                    flag++;
                    break;
                case 4:
                    s->regularScore = stof(temp);
                    flag++;
                    break;
                case 5:
                    s->midtermScore = stof(temp);
                    flag++;
                    break;
                case 6:
                    s->examScore = stof(temp);
                    flag++;
                    break;
                default:
                    break;
                }
                temp.clear();
                flag1 = 0;
            }
        }
        s->examScore = stof(temp);

        // printScore(s);
    }

    
}

//从文件读取
bool readFromFile(StudentScore *s, int count, string inputFileName) 
{
    int i = 0;
    ifstream ifile;
    string line;
    ifile.open(inputFileName);

    getline(ifile, line);
    // cout << line << endl;

    while(ifile)
    {
        getline(ifile, line);
        //防止重复读取最后一行
        if(ifile.peek() == '\n')
            break;

        parseScore(&s[i++], line);

        totalcount++;

        if(i >= count)
        {
            return false;;            
        }
    }

    return true;
}

struct MajorInfo {
    string major;
    int count;
};

//统计班上各专业人数并写入文件
void calculateMajor (StudentScore *s, int count)
{
    int flag = 1;
    vector<MajorInfo> vm;
    ofstream fout("major.txt");

    for(int i=0 ; i< count; i++)
    {
        flag = 0;
        for(auto iter = vm.begin(); iter != vm.end(); iter++)
        {
            if(s[i].major.compare(iter->major) == 0)
            {
                flag = 1;
                iter->count++;
            }
        }

        if(!flag)
        {
            MajorInfo temp;

            temp.major = s[i].major;
            temp.count = 1;

            vm.push_back(temp);
        }
    }
    fout << "班级专业\t\t数量" << endl;
    for(auto iter = vm.begin(); iter != vm.end(); iter++)
    {
        fout << iter->major << "\t\t" << iter->count << endl;
    }

    fout.close();
}

//计算总评成绩
void calculateFinalScore (StudentScore *s, int count) 
{
    for(int i = 0; i < count; i++)
    {
        s[i].finalScore = s[i].regularScore * 0.1 + s[i].midtermScore * 0.3 + s[i].examScore * 0.6;
    }
}

bool myfunction(StudentScore a, StudentScore b)
{
    return (a.finalScore < b.finalScore);
}

//排序函数，总成绩降序排，
void sortScoreDesc(StudentScore *s, int count) 
{
    sort(&s[0], &s[count], myfunction);
}

//排序可以链表也可以数组
void writeToFile(StudentScore *s, int count,string outputFileName)
{
    ofstream fout(outputFileName);

    fout <<"序号\t\t学号\t\t姓名\t\t班级\t\t平时成绩\t\t期中成绩\t\t期末成绩\t\t总评成绩"<< endl;
    for(int i=0; i< count; i++)
    {
        // printScore(&s[i]);
        fout << s[i].serialNum << "\t\t" << s[i].id  << "\t" << s[i].name << "\t\t" \
        << s[i].major << "\t" << s[i].regularScore << "\t\t\t" << s[i].midtermScore << "\t\t\t" \
        << s[i].examScore << "\t\t\t" << s[i].finalScore << endl;
    }

    fout.close();
}



int main(int argc, char *argv[])
{
    bool ret;
    
    //string str = "1     200637096       王莎莎      保险0605        85      80      51";
    //parseScore(&stu, str);
    ret = readFromFile(stu, 10000, "score.txt");
    if(ret == false)
    {
        return -1;
    }
    
    calculateMajor(stu, totalcount);
    
    calculateFinalScore(stu, totalcount);
    
    sortScoreDesc(stu, totalcount);
    
    writeToFile(stu, totalcount, "result.txt");

    return 0;
}
