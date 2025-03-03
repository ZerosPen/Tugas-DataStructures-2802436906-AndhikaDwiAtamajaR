#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct Node{
	char letter;
	struct Node *next;
}*top;

struct Node* createTable(const char letter){
	struct Node *newData = (struct Node*)malloc(sizeof(struct Node));
	newData->letter = letter;
    newData->next = NULL;
    
    return newData;
}

void pushTop(const char letter){
	struct Node *temp = createTable(letter);
    
    if (!top) {
        top = temp;
    } else {
        temp->next = top;
        top = temp;
    }
}

char popTop(){
	if(!top) return '\0';
	
	struct Node *temp = top;
	
	char letter = temp -> letter;
	top = top -> next;
	free(temp);
	
	return letter; 
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0; // Lower precedence for non-operators
}


void InfixToPost(const char* infix) {
    printf("Postfix: ");
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        
        if (isalnum(ch)) {
            printf("%c", ch);
        } 
        else if (ch == '(') {
            pushTop(ch);
        } 
        else if (ch == ')') {
            while (top && top->letter != '(') {
                printf("%c", popTop());
            }
            popTop(); // Remove '('
        } 
        else { // Operator case
            while (top && precedence(top->letter) >= precedence(ch)) {
                printf("%c", popTop());
            }
            pushTop(ch);
        }
    }
    
    while (top) {
        printf("%c", popTop());
    }
    
    printf("\n");
}


int main() {
    char infix[100];
    
    puts("Exampel : 4+6*(5-2)/3");
    printf("Enter infix expression: ");
    scanf("%s", infix);
    
    InfixToPost(infix);

    
    return 0;
}


