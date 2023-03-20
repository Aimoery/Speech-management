#pragma once
#include<iostream>
#include<vector>  //盛放人员信息
#include<map>  //用map以键值对 对应人员及信息代号
#include"Speaker.h"

using namespace std;

class SpeechManger
{
public:
	//构造函数和析构函数
	SpeechManger();
	
	//显示菜单
	void Show_Memu();

	//退出系统
	void ExitSystem();

	~SpeechManger() {}
	
	//初始化信息
	void Init_info();

	//创建选手信息
	void createSpeaker();

	//开始比赛
	void StartSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContect();

	//显示晋级信息
	void ShowScore();

	//保存数据
	void SaveRecord();

	//读取往届信息
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空记录
	void ClearRecord();

public:
	//记录第一轮人员分数信息
	vector<int> v1;
	//记录第二轮人员分数信息
	vector<int> v2;
	//记录最终获胜的人员信息
	vector<int> vVectory;
	//键值对用于对应人与人之间关系
	map<int, Speaker> m_Speaker;
	//存放往届信息
	map<int, vector<string>> m_Record;  //第一个数代表届，第二个数代表此届人员信息

	//判空
	bool fileIsEmpty;
	int m_Index;
};
