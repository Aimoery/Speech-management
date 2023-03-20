#pragma once
#include<iostream>
#include<vector>  //ʢ����Ա��Ϣ
#include<map>  //��map�Լ�ֵ�� ��Ӧ��Ա����Ϣ����
#include"Speaker.h"

using namespace std;

class SpeechManger
{
public:
	//���캯������������
	SpeechManger();
	
	//��ʾ�˵�
	void Show_Memu();

	//�˳�ϵͳ
	void ExitSystem();

	~SpeechManger() {}
	
	//��ʼ����Ϣ
	void Init_info();

	//����ѡ����Ϣ
	void createSpeaker();

	//��ʼ����
	void StartSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContect();

	//��ʾ������Ϣ
	void ShowScore();

	//��������
	void SaveRecord();

	//��ȡ������Ϣ
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//��ռ�¼
	void ClearRecord();

public:
	//��¼��һ����Ա������Ϣ
	vector<int> v1;
	//��¼�ڶ�����Ա������Ϣ
	vector<int> v2;
	//��¼���ջ�ʤ����Ա��Ϣ
	vector<int> vVectory;
	//��ֵ�����ڶ�Ӧ������֮���ϵ
	map<int, Speaker> m_Speaker;
	//���������Ϣ
	map<int, vector<string>> m_Record;  //��һ��������죬�ڶ���������˽���Ա��Ϣ

	//�п�
	bool fileIsEmpty;
	int m_Index;
};
