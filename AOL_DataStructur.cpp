#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define N  26

typedef struct triesData {
    char data[1001];
    char desc[1000001];
    struct triesData* childrens[N];
    int is_leaf;
} triesData;

//to make new node for each character from the slang
triesData* newTrieNode() {
	// to allocate memory for a trienode
    triesData* newNode = (triesData*)calloc(1, sizeof(triesData));
    return newNode;
}

//to free trienodee
void free_trienode(triesData* node) {
	//Free the trieNode squence
    for (int i = 0; i < N; i++) {
        if (node->childrens[i] != NULL) {
            free_trienode(node->childrens[i]);
        }
    }
    free(node);
}

//Check The slang
int checkNewSlang(const char *name){
	int len = strlen(name); //count the length of the slang
	if(len < 2) return 1; // if have more than 1 char can move to next procedure
	
	for(int i = 0; i < len; i++){ // to check there are space or not
		if(isspace(name[i])) return 1; // if have a space cant move to next procedure
	}
	return 0;
}

//check the desc of the slang word
int checkNewDesc(const char *desc){
	int wordCount = 0; //counting the word
	for(int i =0 ; desc[i] != '\0'; i++){ // check when each char
		if(isspace(desc[i])){ // when i is space then after space there are character it will be count as next word
			wordCount++;	
		}
	}
	
	return wordCount < 1;
}

// to Insert the data
void insertTriesData(triesData *root, const char *slang, const char *desc) {
    triesData* node = root;
    for (int i = 0; slang[i] != '\0'; i++) { // check each character
        int index = tolower(slang[i]) - 'a'; // find the index each character use to lower to able when CapsLock is on or Double inut with the shift key
        
        if (index < 0 || index >= N) { // check the index if below 0 or more than 26 is not a char
        	return;	
		}
        
        if (node->childrens[index] == NULL) { // if childrens in node is NULL/Empty or ot
            node->childrens[index] = newTrieNode(); // if NULL/Empty input the char to the node
        }
        node = node->childrens[index];
    }
    node->is_leaf = 1;
    strcpy(node->data, slang); //copy the slang to the tries
    strcpy(node->desc, desc); //copy desc of the slang to the tries
}

//Search char or word in Tries
triesData* searchTries(triesData *root, char* word){
	triesData* node = root;
	
	for(int i = 0; word[i] != '\0'; i++){
		int position = (int)tolower(word[i]) - 'a';
		if(position < 0 || position >= N || node->childrens[position] == NULL){
			return 0;
		}
		node = node->childrens[position];
	}
	if (node->is_leaf) 
	{
    return node;
	} 
	else {
	    return NULL;
	}
}

int count = 1;
void traverseSearch(triesData *root){
    if(root == NULL) return;
    if(root->is_leaf){
        printf("%d. %s\n", count++, root->data);
    }
    for(int i = 0; i < N; i++){
        traverseSearch(root->childrens[i]);
    }
}

void printPrefixMatches(triesData *root, const char *prefix) {
    triesData* current = root;
    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = tolower(prefix[i]) - 'a';
        if (index < 0 || index >= N || current->childrens[index] == NULL) {
            printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
            return;
        }
        current = current->childrens[index];
    }
    printf("Words starting with \"%s\":\n", prefix);
    count = 1;
    traverseSearch(current);
}


int found = 0;

void helperTraversePrintAll(triesData *root) {
    if (root == NULL) return;
    if (root->is_leaf) {
        if (!found) {
            puts("List of all slang words in the dictionary:");
            found = 1;
        }
        printf("%d. %s\n", count++, root->data);
    }
    for (int i = 0; i < N; i++) {
        helperTraversePrintAll(root->childrens[i]);
    }
}

void traversePrintAll(triesData *root) {
    count = 1;
    found = 0;
    helperTraversePrintAll(root);
    if (!found) {
        puts("There is no slang word yet in the dictionary.");
    }
}



void menu(){
	triesData *root = newTrieNode();
	int choice;
	
	do{
		printf("\n=== Slang Dictionary Menu ===\n");
   		printf("1. Release a new slang word\n");
	    printf("2. Search a slang word\n");
	    printf("3. View all slang words starting with a certain prefix word\n");
	    printf("4. View all slang words\n");
	    printf("5. Exit\n");
	    printf("Choose: ");
	    scanf("%d", &choice); getchar();
		
		switch (choice){
			case 1:{
				char slang[10001];
	            char desc[100001];
	
	            do {
	                printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
	                scanf("%[^\n]", slang); getchar();
	            } while(checkNewSlang(slang));
	
	            do {
	                printf("Input a new slang word description [Must be more than 2 words]: ");
	                scanf("%[^\n]", desc); getchar();
	            } while(checkNewDesc(desc));
	            
	            
	            triesData *found = searchTries(root, slang);
	            if(found){
	            	insertTriesData(root, slang, desc);
	            	puts("Successfully updated a slang word.");
				} else{
					insertTriesData(root, slang, desc);
	            	puts("Successfully released new slang word.");				
				}
	
	            printf("Press enter to continue...\n"); getchar();
	            
				break;
			}

	        case 2: {
	        	char keySearch[1001];
				do{
					printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
					scanf("%[^\n]", keySearch);getchar();
				}while(checkNewSlang(keySearch));
				
				triesData *found = searchTries(root, keySearch); 
				
				if(found){
					printf("Slang word  : %s\n", found->data);
					printf("Description : %s\n", found->desc);
					printf("Press enter to continue...\n"); getchar();
				}
				else{
					printf("There is no word \"%s\" in the dictionary.\n", keySearch);
					printf("Press enter to continue...\n"); getchar();
				}
				break;
			}
			case 3:{
				char keySearchs[10001];
				printf("Input a prefix to be searched: ");
				scanf("%[^\n]", keySearchs); getchar();
				printPrefixMatches(root, keySearchs);
				break;
			}
			
			case 4:{
				traversePrintAll(root);
				printf("Press enter to continue...\n"); getchar();	
				break;
			}	
			
			case 5:{
				printf("Exiting program...\n");
				break;
			}
			
			default:{
				printf("Invalid menu. Try again.\n");
				break;
			}
				
		}
	}
	while(choice != 5);
	free_trienode(root);
}

int main(){
	menu();
	return 0;
}
