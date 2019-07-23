//filename : main.cpp
//author : PenG
//create time : 2019/07/23
//description : 通过数组记录法计算素数
//version : 2.0

#include <iostream>
#include <fstream>
#include <ctime>    //用于计算算法运行时间

using namespace std;

const int isPrime = 2;    //标记，是素数
const int hasRecord = 1;    //标记，已经记录过
const int notRecord = 0;    //标记，还没有记录

const int recordSize = 100000000;    //记录数组的最大尺寸，不是能计算的最大的素数

//利用一个机构体存储素数和计算的素数的个数
typedef struct
{
	int *results;    //指针，指向记录素数的数组
	int size;    //该数组的大小
}PrimeNumbers;

//计算素数，返回PrimeNumvers结构数据
PrimeNumbers calculationOfPrimeNumbers(void);

//输出素数，根据提供的PrimeNumbers结构向屏幕输出结果
void printPrimeNumbers(PrimeNumbers result);

//输出数据到文件中
void printToFile(PrimeNumbers result);

int main(void)
{
	PrimeNumbers result;    //存储计算结果
	
	clock_t startTime, endTime;    //用于计算算法运行时间
	startTime = clock();
	
	//计算并获得计算结果
	result = calculationOfPrimeNumbers();
	
	endTime = clock();
	cout << "run time is : " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

	printPrimeNumbers(result);

	//由于输出文件时间比较长，这里注释掉
	//cout << "anykey to write file!" << endl;
	//system("pause");
	//printToFile(result);

	system("pause");

	
	delete result.results;    //删除分配的空间
	
	return 0;
}

//素数计算算法,calculationOfPrimeNumbers函数调用
void calculate(int *record)
{
	int index = 2;    //当前计算的索引，从第一个素数开始计算
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
}
//获取并返回计算结果，calculationOfPrimeNumbers函数调用
PrimeNumbers getCalculationResults(int *record)
{
	int amount = 0;    //素数个数
	int index = 0;    //当前计算的索引
	//数出有多少个素数
	for (int i = 0; i < recordSize; i++)
	{
		if (record[i] == isPrime)
		{
			amount++;
		}
	}
	PrimeNumbers prime;
	prime.size = amount;    //写入素数个数
	prime.results = new int[amount];    //根据素数个数分配空间
	
	//把素数数据写入到结果中
	for (int i = 2; i < recordSize; i++)
	{
		if (record[i] == isPrime)
		{
			prime.results[index++] = i;
		}
	}
	return prime;
}

//计算素数，返回PrimeNumvers结构数据
PrimeNumbers calculationOfPrimeNumbers(void)
{
	int *record = new int[recordSize];    //存储计算过程的数组

	record[0] = hasRecord;    //0和1肯定不是素数
	record[1] = hasRecord;
	record[2] = isPrime;    //2肯定是素数
	
	//初始化其他记录为notRecord
	for (int i = 3; i < recordSize; i++)
	{
		record[i] = notRecord;
	}
	
	//开始素数计算
	calculate(record);
	
	//返回计算结果
	return getCalculationResults(record);
}

//输出素数，根据提供的PrimeNumbers结构向屏幕输出结果
void printPrimeNumbers(PrimeNumbers result)
{
	//由于输出的结果比价多，不能全部看到，所以不需要了
	//for (int i = 0; i < result.size; i++)
	//{
	//	cout << result.results[i] << endl;
	//}
	cout << "size is : " << result.size << endl;
}

//输出数据到文件中
void printToFile(PrimeNumbers result)
{
	ofstream file("PrimeNumbers.txt", ios_base::out);
	
	cout << "Writing file, please wait a minute!" << endl;
	for (int i = 0; i < result.size; i++)
	{
		file << result.results[i] << endl;
		//这部分提供写文件的进度
		if (i % 10000 == 0)
		{
			cout << (int)((double)i / (double)result.size * 100.0) << "%" << endl;
		}
	}
	cout << "File written success!" << endl;
}
