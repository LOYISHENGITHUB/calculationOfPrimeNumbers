//filename : main.cpp
//author : PenG
//create time : 2019/07/23
//description : ͨ�������¼����������


#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

const int isPrime = 2;
const int hasRecord = 1;
const int notRecord = 0;

const int recordSize = 100000000;

typedef struct
{
	int *results;
	int size;
}PrimeNumbers;

//��������
//����PrimeNumvers�ṹ
PrimeNumbers calculationOfPrimeNumbers(void);

//�������
//�����ṩ��PrimeNumbers�ṹ������
void printPrimeNumbers(PrimeNumbers result);

//��ӡ���ݵ��ļ���
void printToFile(PrimeNumbers result);

int main(void)
{
	PrimeNumbers result;
	clock_t startTime, endTime;
	startTime = clock();
	result = calculationOfPrimeNumbers();
	endTime = clock();
	cout << "run time is : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	printPrimeNumbers(result);

	cout << "anykey to write file!" << endl;
	system("pause");

	//printToFile(result);

	system("pause");

	//ɾ������Ŀռ�
	delete result.results;
	return 0;
}

PrimeNumbers calculationOfPrimeNumbers(void)
{
	
	int *record = new int[recordSize];    //�洢������̵�����

	//0��1�϶�����������2�϶�����������2��ʼ
	record[0] = record[1] = hasRecord;
	record[2] = isPrime;
	//��ʼ��������¼Ϊ��δ��¼��
	for (int i = 3; i < recordSize; i++)
	{
		record[i] = notRecord;
	}
	
	int index = 2;    //��ǰ���������
	unsigned int targetIndex = 0;    //�����Ŀ������
	int times = 0;    //�����ı���
	//����Ч��Χ�ڼ���
	while (index < recordSize)
	{
		times = index;    //���������ӵ�ǰ������ʼ
		targetIndex = index * times;    //Ŀ���������ڵ�ǰ����������������
		//��Ŀ�������ڷ�Χ��ʱѭ��
		while (targetIndex < recordSize)
		{
			//д�������ڵ�ֵΪ���Ѽ�¼��
			record[targetIndex] = hasRecord;

			//����Ŀ������
			targetIndex = index * ++times;
		}
		
		//�ҵ���ǰ���������һ��δ��¼���ݵ�����
		while (record[++index] != notRecord && index < recordSize)
		{
			NULL;
		}
		//����ҵ��������϶�������
		record[index] = isPrime;
	}

	//�����ж��ٸ�����
	int amount = 0;
	for (int i = 0; i < recordSize; i++)
	{
		if (record[i] == isPrime)
		{
			amount++;
		}
	}
	PrimeNumbers prime;
	prime.size = amount;
	//����������������ռ�
	prime.results = new int[amount];
	index = 0;
	//��¼����
	for (int i = 2; i < recordSize; i++)
	{
		if (record[i] == isPrime)
		{
			prime.results[index++] = i;
		}
	}

	return prime;
}

void printPrimeNumbers(PrimeNumbers result)
{
	//for (int i = 0; i < result.size; i++)
	//{
	//	cout << result.results[i] << endl;
	//}
	cout << "size is : " << result.size << endl;
}

void printToFile(PrimeNumbers result)
{
	ofstream file("PrimeNumbers.txt", ios_base::out);
	cout << "Writing file, please wait a minute!" << endl;
	for (int i = 0; i < result.size; i++)
	{
		file << result.results[i] << endl;
		if (i % 1000 == 0)
		{
			cout << (int)((double)i / (double)result.size * 100.0) << "%" << endl;
		}
	}
	cout << "File written success!" << endl;
}