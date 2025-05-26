#include<stdio.h>

//MinHeap
int minHeap[100];
int maxHeap[100];
int dataCount = 1;
int heapType;

int getParentIndex(int index)
{
	return index/2;
}

int getLeftIndex(int index)
{
	return index*2;
}

int getRightIndex(int index)
{
	return index*2 +1;
}

void viewHeap()
{
	if (dataCount <= 1) {
		printf("Your Heap is Empty. Insert more data!\n\n");
		return;
	}
	for (int i = 1; i < dataCount; i++) {
		if (heapType == 1) {
			printf("MinHeap[%2d] = %d\n", i, minHeap[i]);
		} else {
			printf("MaxHeap[%2d] = %d\n", i, maxHeap[i]);
		}
	}
	puts("");
}

void swapValue(int parentIndex, int currIndex)
{	
	if (heapType == 1){
		int temp = minHeap[parentIndex];
		minHeap[parentIndex] = minHeap[currIndex];
		minHeap[currIndex] = temp;
	} 
	if (heapType == 2){
		int temp = maxHeap[parentIndex];
		maxHeap[parentIndex] = maxHeap[currIndex];
		maxHeap[currIndex] = temp;
	}
}

void HeapUp(int index)
{	
	if(index <=1 ) return; //kondisinya kosong
	
	else if (heapType == 1 ){
		
		int parentIndex = getParentIndex(index);
		//masih memenuhi kondisi min-heap
		if(minHeap[parentIndex] <= minHeap[index]) return;
		
		//kalo nggk sesuai kondisi min-heap
		swapValue(parentIndex,index);
		//pengecekan kondisi secara rekursif
		HeapUp(parentIndex);	
	}
	else if (heapType == 2){
		int parentIndex = getParentIndex(index);
		//masih memenuhi kondisi max-heap
		if(maxHeap[parentIndex] >= maxHeap[index]) return;
		
		//kalo nggk sesuai kondisi max-heap
		swapValue(parentIndex,index);
		//pengecekan kondisi secara rekursif
		HeapUp(parentIndex);
	}
}

void HeapDown(int index)
{	
	if(index >= dataCount) return;//ketika kondisinya kosong

	else if (heapType == 1){
	
		int smallest = index;//parent
		int leftValue = getLeftIndex(index);//left child
		int rightValue = getRightIndex(index);//right child
		
		if(minHeap[leftValue] < minHeap[smallest] && leftValue < dataCount)
			smallest = leftValue;
		
		if(minHeap[rightValue] < minHeap[smallest] && rightValue < dataCount)
			smallest = rightValue;
		
		//masih memenuhi kriteria min-heap
		if(smallest == index) return;
		
		//pengecekan kondisi secara rekursif
		HeapDown(smallest);
	}
	else if (heapType == 2){
	
		int max = index;//parent
		int leftValue = getLeftIndex(index);//left child
		int rightValue = getRightIndex(index);//right child
		
		if(maxHeap[leftValue] > maxHeap[max] && leftValue < dataCount)
			max = leftValue;
		
		if(maxHeap[rightValue] > maxHeap[max] && rightValue < dataCount)
			max = rightValue;
		
		//masih memenuhi kriteria min-heap
		if(max == index) return;
		
		//pengecekan kondisi secara rekursif
		HeapDown(max);
	}
}

void push(int input) {
	if (heapType == 1) {
		minHeap[dataCount] = input;
	} 
	if (heapType == 2) {
		maxHeap[dataCount] = input;
	}
	HeapUp(dataCount);
	dataCount++;
}

int pop()
{	
	int removed;
	if (heapType == 1) {
		removed = minHeap[1];
		swapValue(1, dataCount - 1);
		dataCount--;
		HeapDown(1);
	} else {
		removed = maxHeap[1];
		swapValue(1, dataCount - 1);
		dataCount--;
		HeapDown(1);
	}
	return removed;
}

void createMenu()
{
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Exit\n");
}

int main()
{	
	printf("Do want Heap Min or Heap Max?\n");
	puts("1. Min");
	puts("2. Max");
	printf("Select the heap : ");
	scanf("%d", &heapType); getchar();
	
	int input = -1, num;
	do
	{
		printf("Data:\n",dataCount);
		viewHeap();
		createMenu();
		
		do
		{
			printf("input your choice: ");
			scanf("%d", &input); getchar();
		} while(input < 1 || input > 3);
	
		switch(input)
		{
			case 1: printf("What data should be inputted into the heap?");
				scanf("%d", &num);getchar();
				push(num);
				printf("%d has been inputted into the heap\n\n", num);
				getchar();
				break;
			case 2: if(dataCount<=1)
				{
					printf("Your heap is empty. Insert more data!\n\n");
				}
				else
				{
					printf("%d has been deleted\n\n", pop());
				}
				getchar();
				break;
		}
	}while (input!=3);
	
	//return 0;
}
	
