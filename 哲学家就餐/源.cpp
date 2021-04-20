#include<process.h>
#include<Windows.h>
#include<iostream>

#define CHOSPSTICKNUM 5
using namespace std;

//这五个用于承接后续的五个事件
HANDLE Chospsticks[CHOSPSTICKNUM];
HANDLE ISPRINT;
int count1 = -1;
int ticket = 10;
void getChospsticks(int i)
{
	while (ticket > 0)
	{
		if (i % 2 == 1)
		{
			WaitForSingleObject(Chospsticks[i], INFINITE);//等待事件已通知状态
			ResetEvent(Chospsticks[i]);//等到信号后，立刻将事件设置为未通知状态
			WaitForSingleObject(Chospsticks[(i + 4) % 5],INFINITE);
			ResetEvent(Chospsticks[(i + 4) % 5]);
			Sleep(1);//这里sleep一下，确保其他线程处于等待状态
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "哲学家" << i << "正在使用筷子"<<i<<"和"<<(i+4)%5<<"干饭" << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			ticket--;
			Sleep(10000);
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "哲学家" << i << "放下筷子" << i << "和" << (i + 4) % 5 << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			//事件执行完毕，立即将事件设置为已通知
			SetEvent(Chospsticks[i]);
			SetEvent(Chospsticks[(i + 4) % 5]);
			Sleep(1);//这里sleep一下，确保该线程下一次不会抢到执行权。


		}
		else
		{
			WaitForSingleObject(Chospsticks[(i + 4) % 5], INFINITE);//等待事件已通知状态
			ResetEvent(Chospsticks[(i + 4) % 5]);//等到信号后，立刻将事件设置为未通知状态
			WaitForSingleObject(Chospsticks[i], INFINITE);
			ResetEvent(Chospsticks[i]);
			Sleep(1);//这里sleep一下，确保其他线程处于等待状态
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "哲学家" << i << "正在使用筷子" << i << "和" << (i + 4) % 5 << "干饭" << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			ticket--;
			Sleep(10000);
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "哲学家" << i << "放下筷子" << i << "和" << (i + 4) % 5 << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			//事件执行完毕，立即将事件设置为已通知
			SetEvent(Chospsticks[i]);
			SetEvent(Chospsticks[(i + 4) % 5]);
			Sleep(1);//这里sleep一下，确保该线程下一次不会抢到执行权。
		}
	}
}

DWORD WINAPI togetChospsticks(LPVOID lpParameter)
{
	count1++;
	getChospsticks(count1);
	return 0;
}
int main()
{
	for (int j = 0; j < CHOSPSTICKNUM; j++)
	{
		//创建事件：人工重置，初始为未通知
		Chospsticks[j] = CreateEvent(nullptr, TRUE ,FALSE, NULL);
		SetEvent(Chospsticks[j]);//设置事件有信号状态
	}
	ISPRINT = CreateEvent(nullptr, TRUE, FALSE, NULL);
	SetEvent(ISPRINT);
	HANDLE Phychologist[CHOSPSTICKNUM] = { 0 };
	DWORD dwThreadId;
	for (int i = 0; i < CHOSPSTICKNUM; i++)
	{
		Phychologist[i]= CreateThread(
			NULL,		// 默认安全属性
			NULL,		// 默认堆栈大小
			togetChospsticks,	// 线程入口地址（执行线程的函数）
			NULL,		// 传给函数的参数
			0,		// 指定线程立即运行
			&dwThreadId);	// 返回线程的ID号
		printf(" Now another thread has been created. ID = %d \n", dwThreadId);
	}
	for (int j = 0; j < CHOSPSTICKNUM; j++)
	{
		WaitForSingleObject(Phychologist[j], INFINITE);
	}
	for (int i = 0; i < CHOSPSTICKNUM; i++)
	{
		CloseHandle(Phychologist[i]);
	}
	for (int i = 0; i < CHOSPSTICKNUM; i++)
	{
		CloseHandle(Chospsticks[i]);
	}
	
	return 0;



	
}