# 题意
文本文件 score.txt记录学生的原始成绩，statistic.txt存放各专业学生人数的统计情况，原始数据内容如下，总共 40 行。

第 1 列是序号

第 2 列是学号

第 3 列是姓名

第 4 列是专业

第 5 列是平时成绩

第 6 列是期中成绩

第 7 列是期末成绩

第 8 列是总评成绩

总评成绩 = 平时成绩*10% + 期中成绩*30% + 期末成绩*60%

编程目标：计算每个学生的总评成绩，并按总评成绩从高到低排序，将排序后的 结果输出到另外一个文本文件中，并统计班级中各个专业的学生人数，写入statistic.txt文件中。格式如下

第 1 列是序号

第 2 列是学号

第 3 列是姓名

第 4 列是专业

第 5 列是平时成绩

第 6 列是期中成绩

第 7 列是期末成绩

第 8 列是总评成绩，输出的顺序是按总评成绩降序输出。
提示：

struct StudentScore{

int serialNum;//序号

int id;//学号

string name;//姓名

string major;//专业

float regularScore;//平时成绩

float midtermScore;//期中成绩

float examScore;//期末成绩 float finalScore;//总评成绩

};

函数声明建议如下：

void printScore(StudentScore *stu); //输出到屏幕

void parseScore(StudentScore *s, string str); //解析一行文本

bool readFromFile(StudentScore *s, int count, string inputFileName); /
/从文件读取

void calculateMajor (StudentScore *s);//统计班上各专业人数并写入文件

void calculateFinalScore (StudentScore *s, int count); //计算总评成绩

void sortScoreDesc(StudentScore *s, int count); //排序函数，总成绩降序
排，

//排序可以链表也可以数组

void writeToFile(StudentScore *s, int count,string outputFileName); //
输出到文件
# 原始数据内容如下：
```
 序号     学号            姓名        班级        平时成绩      其中成绩    期末成绩    总评成绩
1       200637096       王莎莎      保险0605    85           80         51
2       200641196       邢增一      国金0610    85           83         77
3       200707007       卢月        荣誉0701    85           81         86
4       200720020       李永黎      法学0701    80           77         45
5       200721085       周凯        行管0702    80           75         79
6       200801008       李梦楠      国贸0801    85           79         68
7       200801012       吕跃祥      国贸0801    80           84         76
8       200801050       唐东诚      国贸0802    85           81         42
9       200801075       刘会林      国贸0803    85           80         79
10      200801081       韶雨薇      国贸0803    85           84         70
```