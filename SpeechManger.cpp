#include"SpeechManger.h"
#include<algorithm>
#include<deque>
//#include<functional>
#include<numeric>
#include<fstream>

SpeechManger::SpeechManger()
{
	//初始化整个列表
	Init_info();
	//创建人员
	createSpeaker();
	//人员信息的插入
	loadRecord();
}


void SpeechManger::Show_Memu()
{
	cout << "******************************" << endl;
	cout << "*欢迎使用演讲比赛流程管理系统*" << endl;
	cout << "********1、开始演讲比赛*******" << endl;
	cout << "********2、查看往届记录*******" << endl;
	cout << "********3、清空比赛记录*******" << endl;
	cout << "********0、退出比赛程序*******" << endl;
	cout << "******************************" << endl;
	cout << "******************************" << endl;

}
//初始化信息
void SpeechManger::Init_info()
{
	//清空所有数据信息，重新开始新的一轮筛选
	this->v1.clear();
	this->v2.clear();
	this->vVectory.clear();
	this->m_Speaker.clear();

	//初始化轮次
	this->m_Index = 1;
	//清空record里的文件
	this->m_Record.clear();
}

void SpeechManger::createSpeaker()
{
	string nameSeed = "ABCDEFGHIGKL";
	for (int i = 0; i < 12; i++)
	{
		string nameSpeaker = "选手";
		nameSpeaker += nameSeed[i];

		Speaker sp;
		sp.m_Name = nameSpeaker;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}
		v1.push_back(i + 10001);//选手编号
		//double point = rand() % 60 + 40;  //0~99随机
		this->m_Speaker.insert(make_pair(i + 10001, sp));
		//Speaker Sp(nameSpeaker, point);

	}
}

//开始比赛
void  SpeechManger::StartSpeech()
{
	//1、第一轮抽签
	speechDraw();
	//2、第一轮比赛
	speechContect();
	//3、显示晋级结果
	ShowScore();
	//第二轮比赛
	this->m_Index++;
	//4、第二轮抽签
	speechDraw();
	//5、第二轮比赛
	speechContect();
	//6、显示最终结果
	ShowScore();
	//7、保存分数
	SaveRecord();
	cout << "本届比赛完成" << endl;
	//重置
	//初始化整个列表
	Init_info();
	//创建人员
	createSpeaker();
	//人员信息的插入
	loadRecord();
}

//抽签
void  SpeechManger::speechDraw()
{
	cout << "第（" << this->m_Index << ")轮比赛抽签结果如下：" << endl;
	cout << "——————————————————" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			cout << *it << "  ";
	}
	else
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			cout << *it << "   ";
	}
	cout << endl;
	cout << "——————————————————" << endl;
	system("pause");
}
//比赛
void SpeechManger::speechContect()
{
	cout << "第" << this->m_Index << "轮比赛正式开始：" << endl;
	deque<double>d;
	int num = 0;  //记录人员个数 6人一组
	//准备临时容器 放临时小组得分
	multimap<double,int,greater<double>> group;  //第一个值是分数，第二个值是编号
	vector<int> v_Scr;
	if (this->m_Index==1)
	{
		v_Scr = v1;
	}
	else
	{
		v_Scr = v2;
	}
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Scr.begin(); it != v_Scr.end(); it++)
	{
		num++;
		//评委打分
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 601 + 400) / 10.f;//用1000再除以10用于做整数计算
			d.push_back(score);

		}
		sort(d.begin(), d.end(), greater<double>());  //greater，大于
		d.pop_back();
		d.pop_front();  //进行排序过后可以首尾各出一个元素，即去掉最高分，去掉最低分。

		double sum = accumulate(d.begin(), d.end(), 0.0f); //从0开始做加法
		double ave = sum / (double)d.size();
		//把值赋给函数类的分数
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = ave;
		group.insert(make_pair(ave, *it));  //*it是编号
		//每6人取出前三名
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次如下" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end(); it++)
			{
				cout << it->second << "号选手" << this->m_Speaker[it->second].m_Name << "分数为" << m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;  //调用数组内部数据
			}
			//cout << "————————————" << endl;
			int n = 0;
			cout << "第" << num / 6 << "组晋级名单为：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end() && n < 3; it++, n++)
			{
				cout << it->second << "号选手" << this->m_Speaker[it->second].m_Name << "分数为" << m_Speaker[it->second].m_Score[this->m_Index - 1] <<endl;
				//cout << "————————————" << endl;
				if (this->m_Index == 1)
					v2.push_back(it->second);
				else
					vVectory.push_back(it->second);
			}
			cout << "————————————" << endl;
			group.clear();
		}
	}
	cout << "第" << this->m_Index << "轮比赛完毕" << endl;
	system("pause");
}

void SpeechManger::ShowScore()
{
	cout << "第" << this->m_Index<< "轮晋级信息如下：" << endl;
	vector<int> v_Scr;
	if (this->m_Index == 1)
		v_Scr = v2;
	else
		v_Scr = vVectory;
	for (vector<int>::iterator it = v_Scr.begin(); it != v_Scr.end(); it++)
	{
		cout << "编号为：" << *it << "姓名为：" << this->m_Speaker[(*it)].m_Name << "分数为：" << this->m_Speaker[(*it)].m_Score[this->m_Index-1] <<endl;
		//cout << this->m_Speaker[(*it)].m_Name;
	}
	cout << endl;
	system("pause");
	/*system("cls");
	this->Show_Memu();*/
}

void  SpeechManger::SaveRecord()
{
	ofstream ofs;//包含fstream的头文件
	ofs.open("speaker.csv", ios::out | ios::app);   //保存文件为speaker.csv，ios::app为输入并不断叠加数据
	for (vector<int>::iterator it = vVectory.begin(); it != vVectory.end(); it++)
	{ 
		ofs << *it << "," << this->m_Speaker[*it].m_Name << "," << this->m_Speaker[*it].m_Score[1] <<",";
	}
	ofs<<endl;
	ofs.close();
	cout << "保存成功" << endl;
	//同时更新记录不为空
	this->fileIsEmpty = false;
	//system("pause");
	//system("cls");

}
//读取往届信息
void  SpeechManger::loadRecord()
{
	ifstream ifs;
	ifs.open("speaker.csv", ios::in);
	if (!ifs.is_open())
	{
		fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return ;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		ifs.close();
		fileIsEmpty = true;
		return ;
	}
	//文件存在且不为空
	ifs.putback(ch);//将输入的文件输出
	this->fileIsEmpty = false;
	string data;
	int index = 0;
	//for (int i = 0; i < 3; i++)
	while(ifs>>data)
	{ 
		vector<string> v;//存放信息
		int pos = -1;//字符串位置
		int start = 0;//起始位置0
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//cout << "未找到子串" << endl;
				break;
			}
			string temp = data.substr(start, pos - start); //截取长度
			start = pos + 1;//下一轮截取方式
			//cout << temp << endl;
			v.push_back(temp);
		}
		m_Record.insert(make_pair(index, v));
		index++;
		//cout << index << endl;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		cout << it->first << "信息为" << it->second[0]<<endl;
	}*/
}
//显示往届记录
void SpeechManger::showRecord()
{
	//cout << this->m_Record.size() <<endl;
	if (this->fileIsEmpty == true)
	{
		cout << "文件不存在" << endl;
	}
	else
	{
		
		for(int i = 0; i < this->m_Record.size(); i++)
		{
			cout << m_Record.size() << endl;
			cout << "第" << i + 1 << "届比赛成绩排名如下：" << endl
				<< "冠军编号为" << this->m_Record[i][0] << "选手姓名为：" << this->m_Record[i][1] << "得分为：" << this->m_Record[i][2] << endl
				<< "亚军编号为" << this->m_Record[i][3] << "选手姓名为：" << this->m_Record[i][4] << "得分为：" << this->m_Record[i][5] << endl
				<< "季军编号为" << this->m_Record[i][6] << "选手姓名为：" << this->m_Record[i][7] << "得分为：" << this->m_Record[i][8] << endl;
		}
	}
	//system("pause");
	//system("cls");
}

void SpeechManger::ClearRecord()
{
	int sure;
	cout << "是否确认清空？" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;
	cin >> sure;

	switch (sure)
	{
	case 1:
	{
		ofstream ofs;
		ofs.open("Speaker.csv", ios::trunc);//trunc为打开并删除所有数据
		ofs.close();
		//重置
		//初始化整个列表
		Init_info();
		//创建人员
		createSpeaker();
		//人员信息的插入
		loadRecord();
		cout << "清空成功"<<endl;
	}
		break;
	case 2:
		break;
	default:
		cout << "输入错误，请重新输入：" << endl;
		ClearRecord();
		break;
	}
}

void SpeechManger::ExitSystem()
{
	cout << "欢迎再次使用" << endl;
	system("pause"); 
	exit(0);
}
