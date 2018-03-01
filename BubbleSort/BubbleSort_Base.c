/*
 *  BubbleSort_Base.c
 *  冒泡排序的基本算法
 *  Created on: 2018年3月1日
 *  Author: panda1949
 */


#include <stdio.h>
int main()
{
	printf("\n Bubble Bort Base copyrigth \n");
	//printf("Please enter five number:");

	int arr[5] = {6,3,7,2,1};
	int length ;
	int i =0,j =0;

	length = sizeof(arr) / sizeof(arr[0]); //计算数组中元素的个数
	for(i = 1; i <length; i++)
		for(j = 0; j<length; j++ )
		{
			if(arr[i]<arr[j])
			{
				arr[i] = arr[i]^arr[j];
				arr[j] = arr[i]^arr[j];
				arr[i] = arr[i]^arr[j];
			}

		}

	printf("the sorted number is: \n");
	for(i = 0; i < length; i++)
	{
		printf("%d \n", arr[i]);
	}

	return 0;
}

//void BubbleSort()
