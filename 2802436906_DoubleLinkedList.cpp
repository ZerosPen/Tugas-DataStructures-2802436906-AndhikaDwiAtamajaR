#include<stdio.h>
#include<stdlib.h>

struct Node{
	int num;
	Node *next;
	Node *prev;
}*head, *tail;

Node *createNode(int num){
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	newNode -> num = num;
	newNode -> next = NULL;
	newNode -> prev = NULL;
	
	return newNode;
}

void pushHead(int num){
	Node *temp = createNode(num);
	
	if(!head){
		head = tail = temp;
	}
	
	else{
		temp -> next = head;
		head -> prev = temp;
		head = temp;
	}
}

void pushTail(int num){
	Node *temp = createNode(num);
	
	if(!head){
		head = tail = temp;
	}
	
	else{
		tail -> next = temp;
		temp -> prev = tail;
		tail = temp;
	}
}

void pushMid(int num){
	Node *temp = createNode(num);
	
	if(!head){
		head = tail = temp;
	}
	
	else if (num < head -> num){
		pushHead(num);
	}
	else if(num > tail -> num){
		pushTail(num);
	}
	
	else{
		Node *curr = head -> next;
		while(num > curr -> num){
			curr = curr -> next;
		}
		
		Node *data = curr -> prev;
		curr -> prev = temp;
        data -> next = temp;
        temp -> next = curr;
        temp -> prev = data;
	}
}

void popHead(){
	if(!head){
		return;
	}
	
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	
	else{
		Node *temp = head -> next;
		head -> next = NULL;
		temp -> prev = NULL;
		free(head);
		head = temp;
	}
	
}

void popTail(){
	if(!head){
		return;
	}
	
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	
	else{
		Node *temp = tail -> prev;
		tail -> prev = NULL;
		temp -> next = NULL;
		free(tail);
		tail = temp;
	}
}

void popMid(int num){
	if(!head){
		return;
	}
	
	else if(head == tail){
		free(head);
		head = tail = NULL;
	}
	
	else{
		Node *curr = head -> next;
		
		while(curr -> num != num){
			curr = curr -> next;
		}
		
		Node *front = curr -> prev;
		Node *behind = curr -> next;
		curr -> next = NULL;
		curr -> prev = NULL;
		free(curr);
		front -> next = behind;
		behind -> prev = front;
	}
}


void print(){
	Node *curr = head;
	
	while(curr != NULL){
		printf("%d -> ", curr -> num);
		curr = curr -> next;
	}
}

int main(){
	printf("Linked list\n");
	pushTail(13);
	pushTail(1);
	pushTail(3);
	print();
	printf("\n");
	printf("Mengeluarkan kepala\n");
	popHead();
	print();
	printf("\n");
	printf("Linked list\n");
	pushTail(99);
	pushMid(10);
	pushMid(5);
	pushMid(7);
	print();
	printf("\n");
	printf("Mengeluarkan nilai di tengah\n");
	popMid(7);
	print();
	printf("\n");
	printf("Linked list\n");
	pushTail(21);
	pushTail(6);
	pushTail(101);
	print();
	printf("\n");
	printf("Mengeluarkan belakang\n");
	popTail();
	print();
	
	return 0;
}
