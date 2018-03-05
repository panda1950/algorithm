/************************************************
 * File name: BubbleSort_Base.c
 * Author: panda1949
 * Version: v0.1
 * Data:2018.3.02
 * Copyright: Your copyright notice
 * Description: 快速排序的算法

 ************************************************/
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE		10

void quick_sort(int array[],int maxlen,int begin,int end);

/**
 * name: swap
 * brief: 交换两个数的值
 * param: *a ,*b 要交换的两个数的地址
 * retval: None
 * */
void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * name: quicksort
 * brief:快速排序算法主体
 * param:
 * retval: none
 */
void quick_sort(int array[],int maxlen,int begin,int end)
{
	int i,j;
	if(begin < end)
	{
		i = begin + 1; //将array[begin]作为基准数，从array[beging+1]开始与begin进行比较
		j = end;     //array[end] 是数组最后一位

		while(i < j)
		{
			if(array[i] > array[begin])
			{
				swap(&array[i],&array[j]);
				j--;
			}
			else
			{
				i++;
			}
		}

		if(array[i] >= array[begin])  // 这里必须要取等“>=”，否则数组元素由相同的值时，会出现错误！
		{
	       i--;
		}
		swap(&array[begin],&array[i]);

		quick_sort(array,maxlen,begin,i);
		quick_sort(array,maxlen,j,end);
	}
}


/**
 * name: display
 * brief: 打印数组元素
 * param: array[]数组名称, manlen数组个数
 * retval: None
 * */
void display(int array[], int maxlen)
{
    int i;

    for(i = 0; i < maxlen; i++)
    {
        printf("%-3d", array[i]);
    }
    printf("\n");
}


int main()
{

	int array[BUFF_SIZE] = {12,85,25,16,34,23,49,95,17,61};
	int maxlen = BUFF_SIZE;

	printf("排序前的数组\n");
	display(array, maxlen);

	quick_sort(array,maxlen,0,maxlen-1);

	printf("排序后的数组\n");
	display(array, maxlen);


	return 0;
}

