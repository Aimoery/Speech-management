#include"SpeechManger.h"
#include<algorithm>
#include<deque>
//#include<functional>
#include<numeric>
#include<fstream>

SpeechManger::SpeechManger()
{
	//��ʼ�������б�
	Init_info();
	//������Ա
	createSpeaker();
	//��Ա��Ϣ�Ĳ���
	loadRecord();
}


void SpeechManger::Show_Memu()
{
	cout << "******************************" << endl;
	cout << "*��ӭʹ���ݽ��������̹���ϵͳ*" << endl;
	cout << "********1����ʼ�ݽ�����*******" << endl;
	cout << "********2���鿴�����¼*******" << endl;
	cout << "********3����ձ�����¼*******" << endl;
	cout << "********0���˳���������*******" << endl;
	cout << "******************************" << endl;
	cout << "******************************" << endl;

}
//��ʼ����Ϣ
void SpeechManger::Init_info()
{
	//�������������Ϣ�����¿�ʼ�µ�һ��ɸѡ
	this->v1.clear();
	this->v2.clear();
	this->vVectory.clear();
	this->m_Speaker.clear();

	//��ʼ���ִ�
	this->m_Index = 1;
	//���record����ļ�
	this->m_Record.clear();
}

void SpeechManger::createSpeaker()
{
	string nameSeed = "ABCDEFGHIGKL";
	for (int i = 0; i < 12; i++)
	{
		string nameSpeaker = "ѡ��";
		nameSpeaker += nameSeed[i];

		Speaker sp;
		sp.m_Name = nameSpeaker;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}
		v1.push_back(i + 10001);//ѡ�ֱ��
		//double point = rand() % 60 + 40;  //0~99���
		this->m_Speaker.insert(make_pair(i + 10001, sp));
		//Speaker Sp(nameSpeaker, point);

	}
}

//��ʼ����
void  SpeechManger::StartSpeech()
{
	//1����һ�ֳ�ǩ
	speechDraw();
	//2����һ�ֱ���
	speechContect();
	//3����ʾ�������
	ShowScore();
	//�ڶ��ֱ���
	this->m_Index++;
	//4���ڶ��ֳ�ǩ
	speechDraw();
	//5���ڶ��ֱ���
	speechContect();
	//6����ʾ���ս��
	ShowScore();
	//7���������
	SaveRecord();
	cout << "����������" << endl;
	//����
	//��ʼ�������б�
	Init_info();
	//������Ա
	createSpeaker();
	//��Ա��Ϣ�Ĳ���
	loadRecord();
}

//��ǩ
void  SpeechManger::speechDraw()
{
	cout << "�ڣ�" << this->m_Index << ")�ֱ�����ǩ������£�" << endl;
	cout << "������������������������������������" << endl;
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
	cout << "������������������������������������" << endl;
	system("pause");
}
//����
void SpeechManger::speechContect()
{
	cout << "��" << this->m_Index << "�ֱ�����ʽ��ʼ��" << endl;
	deque<double>d;
	int num = 0;  //��¼��Ա���� 6��һ��
	//׼����ʱ���� ����ʱС��÷�
	multimap<double,int,greater<double>> group;  //��һ��ֵ�Ƿ������ڶ���ֵ�Ǳ��
	vector<int> v_Scr;
	if (this->m_Index==1)
	{
		v_Scr = v1;
	}
	else
	{
		v_Scr = v2;
	}
	//�������в���ѡ��
	for (vector<int>::iterator it = v_Scr.begin(); it != v_Scr.end(); it++)
	{
		num++;
		//��ί���
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 601 + 400) / 10.f;//��1000�ٳ���10��������������
			d.push_back(score);

		}
		sort(d.begin(), d.end(), greater<double>());  //greater������
		d.pop_back();
		d.pop_front();  //����������������β����һ��Ԫ�أ���ȥ����߷֣�ȥ����ͷ֡�

		double sum = accumulate(d.begin(), d.end(), 0.0f); //��0��ʼ���ӷ�
		double ave = sum / (double)d.size();
		//��ֵ����������ķ���
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = ave;
		group.insert(make_pair(ave, *it));  //*it�Ǳ��
		//ÿ6��ȡ��ǰ����
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С�������������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end(); it++)
			{
				cout << it->second << "��ѡ��" << this->m_Speaker[it->second].m_Name << "����Ϊ" << m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;  //���������ڲ�����
			}
			//cout << "������������������������" << endl;
			int n = 0;
			cout << "��" << num / 6 << "���������Ϊ��" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end() && n < 3; it++, n++)
			{
				cout << it->second << "��ѡ��" << this->m_Speaker[it->second].m_Name << "����Ϊ" << m_Speaker[it->second].m_Score[this->m_Index - 1] <<endl;
				//cout << "������������������������" << endl;
				if (this->m_Index == 1)
					v2.push_back(it->second);
				else
					vVectory.push_back(it->second);
			}
			cout << "������������������������" << endl;
			group.clear();
		}
	}
	cout << "��" << this->m_Index << "�ֱ������" << endl;
	system("pause");
}

void SpeechManger::ShowScore()
{
	cout << "��" << this->m_Index<< "�ֽ�����Ϣ���£�" << endl;
	vector<int> v_Scr;
	if (this->m_Index == 1)
		v_Scr = v2;
	else
		v_Scr = vVectory;
	for (vector<int>::iterator it = v_Scr.begin(); it != v_Scr.end(); it++)
	{
		cout << "���Ϊ��" << *it << "����Ϊ��" << this->m_Speaker[(*it)].m_Name << "����Ϊ��" << this->m_Speaker[(*it)].m_Score[this->m_Index-1] <<endl;
		//cout << this->m_Speaker[(*it)].m_Name;
	}
	cout << endl;
	system("pause");
	/*system("cls");
	this->Show_Memu();*/
}

void  SpeechManger::SaveRecord()
{
	ofstream ofs;//����fstream��ͷ�ļ�
	ofs.open("speaker.csv", ios::out | ios::app);   //�����ļ�Ϊspeaker.csv��ios::appΪ���벢���ϵ�������
	for (vector<int>::iterator it = vVectory.begin(); it != vVectory.end(); it++)
	{ 
		ofs << *it << "," << this->m_Speaker[*it].m_Name << "," << this->m_Speaker[*it].m_Score[1] <<",";
	}
	ofs<<endl;
	ofs.close();
	cout << "����ɹ�" << endl;
	//ͬʱ���¼�¼��Ϊ��
	this->fileIsEmpty = false;
	//system("pause");
	//system("cls");

}
//��ȡ������Ϣ
void  SpeechManger::loadRecord()
{
	ifstream ifs;
	ifs.open("speaker.csv", ios::in);
	if (!ifs.is_open())
	{
		fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return ;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		fileIsEmpty = true;
		return ;
	}
	//�ļ������Ҳ�Ϊ��
	ifs.putback(ch);//��������ļ����
	this->fileIsEmpty = false;
	string data;
	int index = 0;
	//for (int i = 0; i < 3; i++)
	while(ifs>>data)
	{ 
		vector<string> v;//�����Ϣ
		int pos = -1;//�ַ���λ��
		int start = 0;//��ʼλ��0
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//cout << "δ�ҵ��Ӵ�" << endl;
				break;
			}
			string temp = data.substr(start, pos - start); //��ȡ����
			start = pos + 1;//��һ�ֽ�ȡ��ʽ
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
		cout << it->first << "��ϢΪ" << it->second[0]<<endl;
	}*/
}
//��ʾ�����¼
void SpeechManger::showRecord()
{
	//cout << this->m_Record.size() <<endl;
	if (this->fileIsEmpty == true)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		
		for(int i = 0; i < this->m_Record.size(); i++)
		{
			cout << m_Record.size() << endl;
			cout << "��" << i + 1 << "������ɼ��������£�" << endl
				<< "�ھ����Ϊ" << this->m_Record[i][0] << "ѡ������Ϊ��" << this->m_Record[i][1] << "�÷�Ϊ��" << this->m_Record[i][2] << endl
				<< "�Ǿ����Ϊ" << this->m_Record[i][3] << "ѡ������Ϊ��" << this->m_Record[i][4] << "�÷�Ϊ��" << this->m_Record[i][5] << endl
				<< "�������Ϊ" << this->m_Record[i][6] << "ѡ������Ϊ��" << this->m_Record[i][7] << "�÷�Ϊ��" << this->m_Record[i][8] << endl;
		}
	}
	//system("pause");
	//system("cls");
}

void SpeechManger::ClearRecord()
{
	int sure;
	cout << "�Ƿ�ȷ����գ�" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	cin >> sure;

	switch (sure)
	{
	case 1:
	{
		ofstream ofs;
		ofs.open("Speaker.csv", ios::trunc);//truncΪ�򿪲�ɾ����������
		ofs.close();
		//����
		//��ʼ�������б�
		Init_info();
		//������Ա
		createSpeaker();
		//��Ա��Ϣ�Ĳ���
		loadRecord();
		cout << "��ճɹ�"<<endl;
	}
		break;
	case 2:
		break;
	default:
		cout << "����������������룺" << endl;
		ClearRecord();
		break;
	}
}

void SpeechManger::ExitSystem()
{
	cout << "��ӭ�ٴ�ʹ��" << endl;
	system("pause"); 
	exit(0);
}
