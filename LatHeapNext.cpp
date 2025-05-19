#include<stdio.h>
#include<stdlib.h>

struct Heaps {
    int *arr;
    int size;
    int capacity;
};

typedef struct Heaps Heaps;

Heaps* createNewHeap(int capacity){
    Heaps* newHeap = (Heaps*)malloc(sizeof(Heaps));
    newHeap->size = 0;
    newHeap->capacity = capacity;
    newHeap->arr = (int*)malloc(capacity * sizeof(int));
    return newHeap;
}

void swapNum(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heaps* heap, int i){
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->arr[left] > heap->arr[max])
        max = left;
    if (right < heap->size && heap->arr[right] > heap->arr[max])
        max = right;

    if (max != i){
        swapNum(&heap->arr[i], &heap->arr[max]);
        heapify(heap, max);
    }
}

void buildHeap(Heaps *heap){
    for (int i = (heap->size - 1) / 2; i >= 0; i--)
        heapify(heap, i);
}

void increaseKey(Heaps *heap, int index, int value){
    if (index >= heap->size || heap->arr[index] >= value){
        printf("Invalid index or new value is not greater\n");
        return;
    }

    heap->arr[index] = value;
    while (index != 0 && heap->arr[(index - 1) / 2] < heap->arr[index]){
        swapNum(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void insertHeap(Heaps* heap, int value){
	//check heap capacity
    if (heap->size == heap->capacity){
        printf("Heap Overflow!\n");
        return;
    }

    int i = heap->size++; // i = index baru
    heap->arr[i] = value; // arr[i] = value
	
	//Swap ke atas
    while (i != 0 && heap->arr[(i - 1) / 2] < heap->arr[i]){
        swapNum(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
} 

int extractMax(Heaps* heap){
	//check heap kosong atau tidak
    if (heap->size <= 0)
        return -999999;
    if (heap->size == 1){
    	heap->size--;
        return heap->arr[0];	
	}

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapify(heap, 0);
    return root;
}

void deleteHeapByIndex(Heaps* heap, int index){
    if (index >= heap->size){
        printf("Invalid index\n");
        return;
    }

    heap->arr[index] = heap->arr[heap->size - 1];
    heap->size--;

    // Perbaiki heap ke atas atau ke bawah tergantung nilai elemen baru
    if (index > 0 && heap->arr[index] > heap->arr[(index - 1) / 2]){
        // Perlu perbaikan ke atas
        while (index > 0 && heap->arr[index] > heap->arr[(index - 1) / 2]){
            swapNum(&heap->arr[index], &heap->arr[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    } else {
        // Perbaikan ke bawah
        heapify(heap, index);
    }
}

void deleteHeapByValue(Heaps* heap, int value){
	int index = -1;
	
	//cari index dengan value yang dinginkan
	for(int i = 0; i < heap->size; i++){
		if(heap->arr[i] == value){
			index = i;
			break;
		}
	}
	
	    // Validasi jika value tidak ditemukan
    if(index == -1){
        printf("Value not found in heap.\n");
        return;
    }
	
	//Tukar elemen yang ingin dihapus dengan elemen terakhir
	heap->arr[index] = heap->arr[heap->size - 1];
    heap->size--;
	
	// Jika elemen baru lebih besar dari parent, lakukan percolate up
	if(index > 0 && heap->arr[index] > heap->arr[(index - 1) / 2]){
		while (index != 0 && heap->arr[(index - 1) / 2] < heap->arr[index]){
	        swapNum(&heap->arr[index], &heap->arr[(index - 1) / 2]);
	        index = (index - 1) / 2;
	    }
	} else{
		// Jika tidak, lakukan heapify untuk perbaikan ke bawah
		heapify(heap, index);
	}
}

void printHeap(Heaps* heap){
    for (int i = 0; i < heap->size; ++i)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

void freeHeap(Heaps* heap){
    free(heap->arr);
    free(heap);
}

int main(){
    Heaps* heap = createNewHeap(60);
    
    insertHeap(heap, 70);
    insertHeap(heap, 60);
    insertHeap(heap, 55);
    insertHeap(heap, 45);
    insertHeap(heap, 50);

	printHeap(heap);
    
    deleteHeapByValue(heap, 50);
    printHeap(heap);
    
    insertHeap(heap, 50);
    printHeap(heap);
    
    freeHeap(heap);
    return 0;
}
