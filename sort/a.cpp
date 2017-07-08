#include <iostream>
#include <stack>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//归并排序（非递归）

void Merge(int *arr, int len, int gap)//gap为归并段的长度
{
	int low1 = 0;//第一个归并段的起始下标
	int high1 = low1+gap-1; //第一个归并段的起始下标
	int low2 = high1+1;
	int high2 = low2 + gap - 1 > len - 1 ? len - 1 : low2 + gap - 1;

	int *brr = new int[len];

	int i = 0; 
	while (low2 < len)
	{
		//两个归并段都有数据
		while (low1 <= high1 && low2 <= high2)
		{
			if (arr[low1] <= arr[low2])
			{
				brr[i++] = arr[low1++];
			}
			else
			{
				brr[i++] = arr[low2++];
			}
		}
		while (low1 <= high1)
		{
			brr[i++] = arr[low1++];
		}
		while (low2 <= high2)
		{
			brr[i++] = arr[low2++];
		}
		low1 = high2 + 1;
		high1 = low1 + gap - 1;
		low2 = high1 + 1;
		high2 = low2 + gap - 1 > len - 1 ? len - 1 : low2 + gap - 1;

	}
	while (low1 < len)
	{
		brr[i++] = arr[low1++];
	}
	for (int i = 0; i < len; ++i)
	{
		arr[i] = brr[i];
	}
	delete[]brr;
}

void MergeSort(int *arr, int len)
{
	for (int i = 1; i < len; i *= 2)
	{
		Merge(arr,len,i);
	}
}


//堆排序
void Adjust(int *arr,int start,int end)//调整函数的时间复杂度是O（logn）
{
	if (arr == NULL && start <= end)
	{
		return;
	}
	int tmp = arr[start];
	for (int i = 2*start+1; i < end; i=2*i+1)
	{
		if ((i + 1 <= end) && (arr[i] < arr[i + 1]))
		{
			i++;
		}//i保存左右孩子较大值的的下标
		if (arr[i] > tmp)
		{
			arr[start] = arr[i];
			start = i;//start保存父节点的下标
		}
		else
		{
			break;
		}
	}
	arr[start] = tmp;
}

void HeapSort(int *arr, int len)//建堆的时候从最后一个非叶子节点开始
{
	int tmp;
	int i;
	for (i = (len - 1 - 1) / 2; i >= 0; --i)//建立大根堆的时间复杂度为O（nlogn）
	{
		Adjust(arr,i,len-1);
	}

	for (i = 0; i < len - 1; ++i)
	{
		tmp = arr[0];
		arr[0] = arr[len - 1 - i];
		arr[len - 1 - i] = tmp;
		Adjust(arr, 0, len - 1 - i-1);
	}	
}

//简单选择排序(的优化是锦标排序)
void SelectSort(int *arr, int len)
{
	if (arr == NULL || len < 1)
	{
		return;
	}
	int tmp;
	int minIndex;
	int j;
	for (int i = 0; i < len; ++i)
	{
		minIndex = i;
		for (j = i + 1; j < len; ++j)
		{
			if (arr[minIndex] > arr[j])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			tmp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = tmp;
		}
	}
}


//快序排序（非递归）(利用栈为辅助空间，保存每次划分的数组中对应的一组下标)
int Partition(int *arr, int low, int high)
{
	if (arr == NULL)
	{
		return -1;
	}
	int tmp = arr[low];
	while (low < high)
	{
		while (low < high && arr[high] >= tmp)
		{
			--high;
		}
		if (low == high)
		{
			break;
		}
		else
		{
			arr[low] = arr[high];
		}
		while (low < high && arr[low] <= tmp)
		{
			++low;
		}
		if (low == high)
		{
			break;
		}
		else
		{
			arr[high] = arr[low];
		}
	}
	arr[low] = tmp;
	return low;
}

void QuickSort(int *arr,int len)
{
	std::stack<int>  st;//栈为辅助空间，保存low和high

	int low = 0; 
	int high = len - 1;
	int par = Partition(arr,low,high);
	if (par > low + 1)
	{
		st.push(low);
		st.push(par-1);
	}
	if (par < high - 1)
	{
		st.push(par+1);
		st.push(high);
	}
	while (!st.empty())
	{
		high = st.top();
		st.pop();
		low = st.top();
		st.pop();

		par = Partition(arr,low,high);
		if (par > low + 1)
		{
			st.push(low);
			st.push(par-1);
		}
		if (par < high - 1)
		{
			st.push(par+1);
			st.push(high);
		}
	}
}

//快序排序(递归)
//int Partition(int *arr, int low,int high)//以一个基准，排序的结果
//{
//	if (arr == NULL)
//	{
//		return -1; 
//	}
//	int tmp = arr[low];
//	while (low < high)
//	{
//		while (low < high && arr[high] >= tmp)
//			--high;
//		if (low == high)
//		{
//			break;
//		}
//		else
//		{
//			arr[low] = arr[high];
//		}
//		while (low < high && arr[low] <= tmp)
//			++low;
//		if (low == high)
//		{
//			break;
//		}
//		else
//		{
//			arr[high] = arr[low];
//		}
//	}
//	arr[low] = tmp;
//	return low;
//}
//
//void Quick(int *arr, int start, int end)
//{
//	int par = Partition(arr, start, end - 1);
//	if (par > start + 1)
//	{
//		Quick(arr,start,par-1);
//	}
//	if (par < end - 1)
//	{
//		Quick(arr,par+1,end);
//	}
//}
//
//void QuickSort(int *arr, int len)
//{
//	
//	if (arr == NULL || len < 1)
//	{
//		return;
//	}
//	Quick(arr,0,len);
//}

//冒泡排序
void BubbleSort(int *arr, int len)
{
	if (arr == NULL || len <= 1)
	{
		return ;
	}
	for (int i = 1; i < len; ++i)
	{
		for (int j = 0; j < len - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

//希尔排序
void shell(int *arr, int len, int gap)
{
	if (arr == NULL || len <= 1 || gap <= 0)
	{
		return ; 
	}
	int j;
	for (int i = gap; i < len; ++i)
	{
		int tmp = arr[i];
		for (j = i - gap; j >= 0; j -= gap)
		{
			if (arr[j] <= tmp)
			{
				break;
			}
			else
			{
				arr[j + gap] = arr[j];
			}
		}
		arr[j + gap] = tmp;
	}
}

void ShellSort(int *arr, int len)
{
	if (arr == NULL || len <= 1)
	{
		return;
	}
	int brr[] = {5,3,1};
	int blen = sizeof(brr) / sizeof(brr[0]);
	for (int i = 0; i < blen; ++i)
	{
		shell(arr,len,brr[i]);
	}
}



//直接插入排序
void InsertSort(int *arr,int len)
{
	if (arr == NULL || len <= 1)
	{
		return;
	}
	int tmp, j;
	for (int i = 1; i < len; ++i)
	{
		tmp = arr[i];
		for (j = i - 1; j >= 0; --j)
		{
			if (arr[j] <= tmp)
			{
				break;
			}
			else
			{
				arr[j + 1] = arr[j];
			}
		}
		arr[j+1] = tmp;
	}
}

int main()
{
	int arr[] = {34,2,1,7,45,23,12,11,8,0,7,13,9,4,35};
	int len = sizeof(arr) / sizeof(arr[0]);
	//InsertSort(arr,len);
	//ShellSort(arr,len);
	//BubbleSort(arr,len);
	//QuickSort(arr,len);
	//SelectSort(arr,len);
	//HeapSort(arr,len);
	//MergeSort(arr,len);
	/*for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << std::endl;
	}*/

	int a = 3;
	int b = 5;
	int *p = &a;
	int &c = b;
	return 0;
}