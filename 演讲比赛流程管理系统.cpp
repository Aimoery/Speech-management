// 演讲比赛流程管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include"SpeechManger.h"
#include <iostream>
#include<ctime>

int main()
{
    //随机数种子
    srand((unsigned int)time(NULL));
    //测试代码
    /*for (map<int, Speaker>::iterator it = sp.m_Speaker.begin(); it != sp.m_Speaker.end(); it++)
    {
        cout << "编号为：" << it->first << "姓名为：" << it->second.m_Name << "第一轮分数为：" << it->second.m_Score[0]
                                                                           <<"第二轮分数为："<< it->second.m_Score[1]<<endl;
    }*/
    SpeechManger sp;
    while (true)
    {
        sp.Show_Memu();
        int choice;
        cout << "请输入您的选择：" << endl;
        cin >> choice;//接受用户的选项
        switch (choice)
        {
        case 1:
            //开始演讲比赛
            sp.StartSpeech();
            break;
        case 2:
            //查看往届比赛记录
            sp.showRecord();
            break;
        case 3:
            //清空比赛记录
            sp.ClearRecord();
            break;
        case 0:
            //退出
            sp.ExitSystem();
            break;
        }
        system("pause");
        system("cls");
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
