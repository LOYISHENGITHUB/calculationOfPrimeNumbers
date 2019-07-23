//filename : main.cpp
//author : PenG
//create time : 2019/07/23
//description : 通过数组记录法计算素数


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

//计算素数
//返回PrimeNumvers结构
PrimeNumbers calculationOfPrimeNumbers(void);

//输出素数
//根据提供的PrimeNumbers结构输出结果
void printPrimeNumbers(PrimeNumbers result);

//打印数据到文件中
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

	//删除分配的空间
	delete result.results;
	return 0;
}

PrimeNumbers calculationOfPrimeNumbers(void)
{
	
	int *record = new int[recordSize];    //存储计算过程的数组

	//0和1肯定不是素数，2肯定是素数，从2开始
	record[0] = record[1] = hasRecord;
	record[2] = isPrime;
	//初始化其他记录为“未记录”
	for (int i = 3; i < recordSize; i++)
	{
		record[i] = notRecord;
	}
	
	int index = 2;    //当前计算的索引
	unsigned int targetIndex = 0;    //计算的目标索引
	int times = 0;    //索引的倍数
	//在有效范围内计算
	while (index < recordSize)
	{
		times = index;    //索引倍数从当前索引开始
		targetIndex = index * times;    //目标索引等于当前索引乘以索引倍数
		//当目标索引在范围内时循环
		while (targetIndex < recordSize)
		{
			//写索引所在的值为“已记录”
			record[targetIndex] = hasRecord;

			//更新目标索引
			targetIndex = index * ++times;
		}
		
		//找到当前索引后面第一个未记录数据的索引
		while (record[++index] != notRecord && index < recordSize)
		{
			NULL;
		}
		//这个找到的索引肯定是素数
		record[index] = isPrime;
	}

	//数出有多少个素数
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
	//根据素数个数分配空间
	prime.results = new int[amount];
	index = 0;
	//记录素数
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