/************************************************
 * File name: BubbleSort_Base.c
 * Author: panda1949
 * Version: v0.1
 * Data:2018.3.02
 * Copyright: Your copyright notice
 * Description: 冒泡排序的算法

 ************************************************/

#include <stdio.h>
#include <assert.h>

void BobbleSort_Base(int *arr,int length);
void BobbleSort_optimization(int *arr,int length);

int main()
{
	int arr [5] = {7,6,5,4,3};
	int length;
	int i;
	length = sizeof(arr) / sizeof(arr[0]); //计算数组中元素的个数

	printf("the length is %d\n",length);
	for(i = 0; i < length; i++)
		{
			printf("%d \n", arr[i]);
		}
	printf("Now sort begin\n");

	printf("Base sort is\n");
	BobbleSort_Base(arr,length);
	printf("Optimization sort is\n");
	BobbleSort_optimization(arr,length);
// 直接在函数中进行排序
/*
	for(i = 0; i <length-1; i++)
		for(j = 0; j<length-1; j++ )
		{
			if(arr[j]>arr[j+1])
			{
				arr[j] = arr[j]^arr[j+1];
				arr[j+1] = arr[j]^arr[j+1];
				arr[j] = arr[j]^arr[j+1];
			}
			printf("the i is %d, the j is %d ,the arr[j] is %d \n",i,j, arr[j]);
		}
*/

	printf("the sorted number is: \n");
	for(i = 0; i < length; i++)
	{
		printf("%d \n", arr[i]);
	}

	return 0;
}

/**
 * name   void BubbleSort_Base()
 * brief  进行最基本的冒泡排序，不进行任何优化
 * param  *arr 要排序数组的地址，length要排序的数据长度
 * retval None
**/
void BobbleSort_Base(int *arr,int length)
{
	assert(arr != NULL);
	int i,j;
	for(i = 0; i <length-1; i++)
		for(j = 0; j<length-1; j++ )
		{
			if( *(arr +j) > *(arr +j+1) )
			{
				if(*(arr +j) > *(arr +j+1))
				{
					arr[j] = arr[j]^arr[j+1];
					arr[j+1] = arr[j]^arr[j+1];
					arr[j] = arr[j]^arr[j+1];
				}
			}
			printf("the i is %d, the j is %d ,the arr[j] is %d \n",i,j, arr[j]);
		}
}

/**
 * name   BobbleSort_optimization()
 * brief  进行冒泡排序，并对内循环次数进行优化，比较后的数据就不再进行比较了
 * param  *arr: 要排序数组的地址，length: 要排序的数据长度
 * retval None
**/
void BobbleSort_optimization(int *arr,int length)
{
	assert(arr != NULL);
	int i,j;
	for(i = 0; i <length-1; i++)
		for(j = 0; j<length-1-i; j++ )
		{
			if( *(arr +j) > *(arr +j+1) )
			{
				if(*(arr +j) > *(arr +j+1))
				{
					arr[j] = arr[j]^arr[j+1];
					arr[j+1] = arr[j]^arr[j+1];
					arr[j] = arr[j]^arr[j+1];
				}
			}
			printf("the i is %d, the j is %d ,the arr[j] is %d \n",i,j, arr[j]);
		}
}



