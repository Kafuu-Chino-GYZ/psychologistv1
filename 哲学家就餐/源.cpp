#include<process.h>
#include<Windows.h>
#include<iostream>

#define CHOSPSTICKNUM 5
using namespace std;

//��������ڳнӺ���������¼�
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
			WaitForSingleObject(Chospsticks[i], INFINITE);//�ȴ��¼���֪ͨ״̬
			ResetEvent(Chospsticks[i]);//�ȵ��źź����̽��¼�����Ϊδ֪ͨ״̬
			WaitForSingleObject(Chospsticks[(i + 4) % 5],INFINITE);
			ResetEvent(Chospsticks[(i + 4) % 5]);
			Sleep(1);//����sleepһ�£�ȷ�������̴߳��ڵȴ�״̬
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "��ѧ��" << i << "����ʹ�ÿ���"<<i<<"��"<<(i+4)%5<<"�ɷ�" << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			ticket--;
			Sleep(10000);
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "��ѧ��" << i << "���¿���" << i << "��" << (i + 4) % 5 << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			//�¼�ִ����ϣ��������¼�����Ϊ��֪ͨ
			SetEvent(Chospsticks[i]);
			SetEvent(Chospsticks[(i + 4) % 5]);
			Sleep(1);//����sleepһ�£�ȷ�����߳���һ�β�������ִ��Ȩ��


		}
		else
		{
			WaitForSingleObject(Chospsticks[(i + 4) % 5], INFINITE);//�ȴ��¼���֪ͨ״̬
			ResetEvent(Chospsticks[(i + 4) % 5]);//�ȵ��źź����̽��¼�����Ϊδ֪ͨ״̬
			WaitForSingleObject(Chospsticks[i], INFINITE);
			ResetEvent(Chospsticks[i]);
			Sleep(1);//����sleepһ�£�ȷ�������̴߳��ڵȴ�״̬
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "��ѧ��" << i << "����ʹ�ÿ���" << i << "��" << (i + 4) % 5 << "�ɷ�" << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			ticket--;
			Sleep(10000);
			WaitForSingleObject(ISPRINT, INFINITE);
			ResetEvent(ISPRINT);
			cout << "��ѧ��" << i << "���¿���" << i << "��" << (i + 4) % 5 << endl;
			Sleep(1);
			SetEvent(ISPRINT);
			//�¼�ִ����ϣ��������¼�����Ϊ��֪ͨ
			SetEvent(Chospsticks[i]);
			SetEvent(Chospsticks[(i + 4) % 5]);
			Sleep(1);//����sleepһ�£�ȷ�����߳���һ�β�������ִ��Ȩ��
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
		//�����¼����˹����ã���ʼΪδ֪ͨ
		Chospsticks[j] = CreateEvent(nullptr, TRUE ,FALSE, NULL);
		SetEvent(Chospsticks[j]);//�����¼����ź�״̬
	}
	ISPRINT = CreateEvent(nullptr, TRUE, FALSE, NULL);
	SetEvent(ISPRINT);
	HANDLE Phychologist[CHOSPSTICKNUM] = { 0 };
	DWORD dwThreadId;
	for (int i = 0; i < CHOSPSTICKNUM; i++)
	{
		Phychologist[i]= CreateThread(
			NULL,		// Ĭ�ϰ�ȫ����
			NULL,		// Ĭ�϶�ջ��С
			togetChospsticks,	// �߳���ڵ�ַ��ִ���̵߳ĺ�����
			NULL,		// ���������Ĳ���
			0,		// ָ���߳���������
			&dwThreadId);	// �����̵߳�ID��
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