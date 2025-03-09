#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define INITIAL_SIZE 26
int currentSize = INITIAL_SIZE;


struct NodeData{
	char name[1001];
	NodeData *next;
	NodeData *prev;
} *DataCount[INITIAL_SIZE],*Head[INITIAL_SIZE], *Tail[INITIAL_SIZE];

NodeData *createTable(const char *name){
	NodeData *newData = (NodeData*)malloc(sizeof(NodeData));
    if (!newData) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(newData->name, name);
    newData->next = NULL;
    newData->prev = NULL;
    return newData;
}


int hashDivision(const char *name){
    if (name[0] >= 'A' && name[0] <= 'Z') {
        return (name[0] - 'A') % INITIAL_SIZE;
    }
    if (name[0] >= 'a' && name[0] <= 'z') {
        return (name[0] - 'a') % INITIAL_SIZE;
    }
    return 0; // Jika karakter pertama bukan huruf
}

int hashMidSquare(const char *name){
    int num = 0;
    for(int i = 0; i < 3 && name[i] != '\0'; i++){
        num = num * 100 + name[i];
    }

    long long square = (long long)num * num;
    char squareStr[21];
    sprintf(squareStr, "%lld", square);

    int len = strlen(squareStr);
    int midIndex = len / 2 - 1;
    char midDigits[4] = "000"; //initialz

    if (midIndex >= 0 && midIndex + 2 < len) {
        strncpy(midDigits, squareStr + midIndex, 3);
        midDigits[3] = '\0';
    }

    return atoi(midDigits) % INITIAL_SIZE;
}

int hashDigitExtraction(const char *name){
    int num = 0;
    for(int i = 0; i < 3 && name[i] != '\0'; i++){
        num = num * 100 + name[i];
    }
    
    long long square = (long long) num * num;
    char squareStr[21];  
    sprintf(squareStr, "%lld", square); // Konversi ke string
    
    int len = strlen(squareStr);
    if(len < 5) return num % INITIAL_SIZE; // Jika hasil kuadrat terlalu pendek

    int extraction = (squareStr[len-5] - '0') * 100 +
                     (squareStr[len-3] - '0') * 10 +
                     (squareStr[len-1] - '0');

    return extraction % INITIAL_SIZE;
}

int hashRotating(const char *name){
	int hash = hashDivision(name);
	
	for(int i = 0; name[i] != '\0'; i++){
		hash = (hash << 4) ^ (hash >> 28) ^ name[i];
	}
	return abs(hash) % INITIAL_SIZE;
}

//void rehash() {
//    int oldSize = currentSize;
//    int newSize = oldSize * 2;
//    
//    NodeData **newDataCount = (NodeData**)calloc(newSize, sizeof(NodeData*));
//    NodeData **newHead = (NodeData**)calloc(newSize, sizeof(NodeData*));
//    NodeData **newTail = (NodeData**)calloc(newSize, sizeof(NodeData*));
//
//    if (!newDataCount || !newHead || !newTail) {
//        printf("Memory allocation failed during rehash\n");
//        free(newDataCount);
//        free(newHead);
//        free(newTail);
//        return;
//    }
//
//    // Move data from old hash table to new one
//    for (int i = 0; i < oldSize; i++) {
//        NodeData *curr = DataCount[i];
//        if (curr != NULL) {
//            int newIndex = hashDivision(curr->name) % newSize;
//
//            // Handle collisions using **linear probing**
//            while (newDataCount[newIndex] != NULL) {
//                newIndex = (newIndex + 1) % newSize;
//            }
//
//            // ? Create a new node and copy data instead of moving the pointer
//            NodeData *newNode = (NodeData*)malloc(sizeof(NodeData));
//            if (newNode) {
//                *newNode = *curr;  // Copy data
//                newNode->next = NULL;
//                newNode->prev = NULL;
//                newDataCount[newIndex] = newNode;
//            }
//        }
//
//        // Rehash for chaining
//        curr = Head[i];
//        while (curr != NULL) {
//            NodeData *next = curr->next;  // Store next before modifying
//            
//            int newIndex = hashDivision(curr->name) % newSize;
//
//            // ? Create a new node instead of moving pointers
//            NodeData *newNode = (NodeData*)malloc(sizeof(NodeData));
//            if (newNode) {
//                *newNode = *curr;  // Copy data
//                newNode->next = NULL;
//                newNode->prev = NULL;
//
//                if (newHead[newIndex] == NULL) {
//                    newHead[newIndex] = newTail[newIndex] = newNode;
//                } else {
//                    newTail[newIndex]->next = newNode;
//                    newNode->prev = newTail[newIndex];
//                    newTail[newIndex] = newNode;
//                }
//            }
//            curr = next; // Move to the next node in the old chain
//        }
//    }
//
//    // Free old memory
//    for (int i = 0; i < oldSize; i++) {
//        NodeData *curr = Head[i];
//        while (curr != NULL) {
//            NodeData *next = curr->next;
//            free(curr);
//            curr = next;
//        }
//    }
//
//    free(DataCount);
//    free(Head);
//    free(Tail);
//
//    // Update global pointers
//    DataCount = newDataCount;
//    Head = newHead;
//    Tail = newTail;
//    currentSize = newSize; // ? Update hash table size
//}


int hashFolding(const char *name){
	int sum = 0;
	int len = strlen(name);
	
	for(int i = 0; i < len; i += 2){
		int part = name[i];
		if(i + 1 < len){
			part = (part << 8) + name[i + 1];
		}
		sum += part;
	}
	
	return sum % INITIAL_SIZE;
}

void linearDevisionInsert(const char *name){
//	int filled = 0;
//    for (int i = 0; i < INITIAL_SIZE; i++) {
//        if (DataCount[i] != NULL) {
//            filled++;
//        }
//    }
//    
//    if ((float)filled / INITIAL_SIZE >= 0.7) { // Jika lebih dari 70%, rehash
//        rehash();
//    }
//	
    NodeData *temp = createTable(name);
    int index = hashDivision(name);

    if(DataCount[index] == NULL){
        DataCount[index] = temp;
    }
    else{
        int point = index + 1;
        while(DataCount[point] != NULL){
            point = (point + 1) % INITIAL_SIZE;
            if(point == index){ // Jika sudah kembali ke posisi awal, berarti penuh
                printf("FULL\n");
                return;
            }
        }
        DataCount[point] = temp; // Simpan di tempat kosong
    }
}

void linearDigitInsert(const char *name){
//	int filled = 0;
//    for (int i = 0; i < INITIAL_SIZE; i++) {
//        if (DataCount[i] != NULL) {
//            filled++;
//        }
//    }
//    
//    if ((float)filled / INITIAL_SIZE >= 0.7) { // Jika lebih dari 70%, rehash
//        rehash();
//    }
	
    NodeData *temp = createTable(name);
    int index = hashDigitExtraction(name);

    if(DataCount[index] == NULL){
        DataCount[index] = temp;
    }
    else{
        int point = index + 1;
        while(DataCount[point] != NULL){
            point = (point + 1) % INITIAL_SIZE;
            if(point == index){ // Jika sudah kembali ke posisi awal, berarti penuh
                printf("FULL\n");
                return;
            }
        }
        DataCount[point] = temp; // Simpan di tempat kosong
    }
}

void linearMidSquareInsert(const char *name){
//	int filled = 0;
//    for (int i = 0; i < INITIAL_SIZE; i++) {
//        if (DataCount[i] != NULL) {
//            filled++;
//        }
//    }
//    
//    if ((float)filled / INITIAL_SIZE >= 0.7) { // Jika lebih dari 70%, rehash
//        rehash();
//    }
	
    NodeData *temp = createTable(name);
    int index = hashMidSquare(name);

    if(DataCount[index] == NULL){
        DataCount[index] = temp;
    }
    else{
        int point = index + 1;
        while(DataCount[point] != NULL){
            point = (point + 1) % INITIAL_SIZE;
            if(point == index){ //index(point) penuh semua :)
                printf("FULL\n");
                return;
            }
        }
        DataCount[point] = temp;
    }
}

void linearRotatingInsert(const char *name){
//	int filled = 0;
//    for (int i = 0; i < INITIAL_SIZE; i++) {
//        if (DataCount[i] != NULL) {
//            filled++;
//        }
//    }
//    
//    if ((float)filled / INITIAL_SIZE >= 0.7) { // Jika lebih dari 70%, rehash
//        rehash();
//    }
	
    NodeData *temp = createTable(name);
    int index = hashRotating(name);

    if(DataCount[index] == NULL){
        DataCount[index] = temp;
    }
    else{
        int point = index + 1;
        while(DataCount[point] != NULL){
            point = (point + 1) % INITIAL_SIZE;
            if(point == index){ //index(point) penuh semua :)
                printf("FULL\n");
                return;
            }
        }
        DataCount[point] = temp;
    }
}

void linearFoldingInsert(const char *name){
//	int filled = 0;
//    for (int i = 0; i < INITIAL_SIZE; i++) {
//        if (DataCount[i] != NULL) {
//            filled++;
//        }
//    }
//    
//    if ((float)filled / INITIAL_SIZE >= 0.7) { // Jika lebih dari 70%, rehash
//        rehash();
//    }
	
    NodeData *temp = createTable(name);
    int index = hashFolding(name);

    if(DataCount[index] == NULL){
        DataCount[index] = temp;
    }
    else{
        int point = index + 1;
        while(DataCount[point] != NULL){
            point = (point + 1) % INITIAL_SIZE;
            if(point == index){ //index(point) penuh semua :)
                printf("FULL\n");
                return;
            }
        }
        DataCount[point] = temp;
    }
}

void chainingDevisionInsert(const char *name){
	NodeData *temp = createTable(name);
	int index = hashDivision(name);
	
	if(Head[index] == NULL){
		Head[index] = Tail[index] = temp;
	}
	else{
		if(strcmp(Head[index] -> name, name) >= 0){
			temp -> next = Head[index];
			Head[index] -> prev = NULL;
			Head[index] =  temp; 
		}
		
		else if(strcmp(name, Tail[index]->name) > 0){
			temp->prev = Tail[index];
			Tail[index]->next = temp;
			Tail[index] = temp;
		}
		
		else{
			NodeData *curr = Head[index] -> next;
			while(curr != NULL && strcmp(curr->name, name) < 0){
				curr = curr -> next;
			}
			curr -> prev -> next = temp;
			temp -> prev = curr -> prev;
			temp -> next = curr;
			curr -> prev = temp; 
		}	
	}
}

void chainingMidSquareInsert(const char *name){
	NodeData *temp = createTable(name);
	int index = hashMidSquare(name);
	
	if(Head[index] == NULL){
		Head[index] = Tail[index] = temp;
	}
	else{
		if(strcmp(Head[index] -> name, name) >= 0){
			temp -> next = Head[index];
			Head[index] -> prev = NULL;
			Head[index] =  temp; 
		}
		
		else if(strcmp(name, Tail[index]->name) > 0){
			temp->prev = Tail[index];
			Tail[index]->next = temp;
			Tail[index] = temp;
		}
		
		else{
			NodeData *curr = Head[index] -> next;
			while(curr != NULL && strcmp(curr->name, name) < 0){
				curr = curr -> next;
			}
			curr -> prev -> next = temp;
			temp -> prev = curr -> prev;
			temp -> next = curr;
			curr -> prev = temp; 
		}	
	}
}

void chainingDigitInsert(const char *name){
	NodeData *temp = createTable(name);
	int index = hashDigitExtraction(name);
	
	if(Head[index] == NULL){
		Head[index] = Tail[index] = temp;
	}
	else{
		if(strcmp(Head[index] -> name, name) >= 0){
			temp -> next = Head[index];
			Head[index] -> prev = NULL;
			Head[index] =  temp; 
		}
		
		else if(strcmp(name, Tail[index]->name) > 0){
			temp->prev = Tail[index];
			Tail[index]->next = temp;
			Tail[index] = temp;
		}
		
		else{
			NodeData *curr = Head[index] -> next;
			while(curr != NULL && strcmp(curr->name, name) < 0){
				curr = curr -> next;
			}
			curr -> prev -> next = temp;
			temp -> prev = curr -> prev;
			temp -> next = curr;
			curr -> prev = temp; 
		}	
	}
}

void chainingRotateInsert(const char *name){
	NodeData *temp = createTable(name);
	int index = hashRotating(name);
	
	if(Head[index] == NULL){
		Head[index] = Tail[index] = temp;
	}
	else{
		if(strcmp(Head[index] -> name, name) >= 0){
			temp -> next = Head[index];
			Head[index] -> prev = NULL;
			Head[index] =  temp; 
		}
		
		else if(strcmp(name, Tail[index]->name) > 0){
			temp->prev = Tail[index];
			Tail[index]->next = temp;
			Tail[index] = temp;
		}
		
		else{
			NodeData *curr = Head[index] -> next;
			while(curr != NULL && strcmp(curr->name, name) < 0){
				curr = curr -> next;
			}
			curr -> prev -> next = temp;
			temp -> prev = curr -> prev;
			temp -> next = curr;
			curr -> prev = temp; 
		}	
	}
}

void chainingFoldingInsert(const char *name){
	NodeData *temp = createTable(name);
	int index = hashFolding(name);
	
	if(Head[index] == NULL){
		Head[index] = Tail[index] = temp;
	}
	else{
		if(strcmp(Head[index] -> name, name) >= 0){
			temp -> next = Head[index];
			Head[index] -> prev = NULL;
			Head[index] =  temp; 
		}
		
		else if(strcmp(name, Tail[index]->name) > 0){
			temp->prev = Tail[index];
			Tail[index]->next = temp;
			Tail[index] = temp;
		}
		
		else{
			NodeData *curr = Head[index] -> next;
			while(curr != NULL && strcmp(curr->name, name) < 0){
				curr = curr -> next;
			}
			curr -> prev -> next = temp;
			temp -> prev = curr -> prev;
			temp -> next = curr;
			curr -> prev = temp; 
		}	
	}
}

void printDataLinear(){
    for(int i = 0; i < INITIAL_SIZE; i++){
        printf("Index %d: ", i);
        
        if(DataCount[i] == NULL){
            printf("No Data\n");
        }
        else{
            printf("%s\n", DataCount[i]->name);
        }
    }
}

void printDataChaining() {
    for(int i = 0; i < INITIAL_SIZE; i++) {
        printf("Index %d: ", i);
        if(Head[i] == NULL) {
            printf("No Data\n");
        } else {
            NodeData *curr = Head[i];
            while(curr != NULL) {
                printf("%s -> ", curr->name);
                curr = curr->next;
            }
            printf("NULL\n");
        }
    }
}

void mainMenu2(){
	puts("Pilihah 1 cara untuk collision handling");
	puts("1. Linear");
	puts("2. Chaining");
	puts("3. Rehasing");
	puts("4. Back");
}

void mainMenu3(){
	puts("Halo Selamat datang ke data structur :)");
	puts("Pilih : ");
	puts("1. Add ");
	puts("2. print ");
	puts("3. Exit ");
}

void mainMenu1(){
	
	int choice1 = 0;
	int choice2 = 0;
	char name[1001];
	
	puts("Pilihah 1 cara untuk hashing");
	puts("1. mid-square");
	puts("2. division");
	puts("3. folding");
	puts("4. digit extraction");
	puts("5. rotation");
	puts("6. back");
	
	printf("Pilihan : ");
		scanf("%d", &choice1); getchar();
		
		switch(choice1){
			case 1:
				puts("Kamu memilih metode Mid-square.");
				puts("Masukan nama untuk data");
				printf("Nama : ");
				scanf("%[^\n]", &name); getchar();
				puts("sekarang pilih cara untuk collision handling.");
				mainMenu2();
				printf("Pilihan : ");
				scanf("%d", &choice2); getchar();
				
				switch(choice2){
					case 1:
						linearMidSquareInsert(name);
						break;
						
					case 2:
						chainingMidSquareInsert(name);
						break;
						
					case 3:
						puts("Rehashing diperlukan jika terjadi collision (tabrakan) dan tabel sudah penuh atau tingkat keterisian sudah terlalu tinggi.");
						break;
						
					case 4:
						break;
						
					default:
						printf("There are not collision handling method for that number!\n");
						break;
				}
				
				break;
			
			case 2:
				puts("Kamu memilih metode division.");
				puts("Masukan nama untuk data");
				printf("Nama : ");
				scanf("%[^\n]", &name); getchar();
				puts("sekarang pilih cara untuk collision handling.");
				mainMenu2();
				printf("Pilihan : ");
				scanf("%d", &choice2); getchar();
				
				switch(choice2){
					case 1:
						 linearDevisionInsert(name);
						break;
						
					case 2:
						chainingDevisionInsert(name);
						break;
						
					case 3:
						puts("Rehashing diperlukan jika terjadi collision (tabrakan) dan tabel sudah penuh atau tingkat keterisian sudah terlalu tinggi.");
						break;
						
					case 4:
						break;
						
					default:
						printf("There are not collision handling method for that number!\n");
						break;
				}
				
				break;
				
			case 3:
				puts("Kamu memilih metode folding.");
				puts("Masukan nama untuk data");
				printf("Nama : ");
				scanf("%[^\n]", &name); getchar();
				puts("sekarang pilih cara untuk collision handling.");
				mainMenu2();
				printf("Pilihan : ");
				scanf("%d", &choice2); getchar();
				
				switch(choice2){
					case 1:
						 linearFoldingInsert(name);
						break;
						
					case 2:
						 chainingFoldingInsert(name);
						 break;
						
					case 3:
						puts("Rehashing diperlukan jika terjadi collision (tabrakan) dan tabel sudah penuh atau tingkat keterisian sudah terlalu tinggi.");
						break;
						
					case 4:
						break;
						
					default:
						printf("There are not collision handling method for that number!\n");
						break;
				}
				
				break;
				
			case 4:
				puts("Kamu memilih metode digit extraction.");
				puts("Masukan nama untuk data");
				printf("Nama : ");
				scanf("%[^\n]", &name); getchar();
				puts("sekarang pilih cara untuk collision handling.");
				mainMenu2();
				printf("Pilihan : ");
				scanf("%d", &choice2); getchar();
				
				switch(choice2){
					case 1:
						 linearDigitInsert(name);
						break;
						
					case 2:
						 chainingDigitInsert(name);
						 break;
						
					case 3:
						puts("Rehashing diperlukan jika terjadi collision (tabrakan) dan tabel sudah penuh atau tingkat keterisian sudah terlalu tinggi.");
						break;
						
					case 4:
						break;
						
					default:
						printf("There are not collision handling method for that number!\n");
						break;
				}
				
				break;
				
			case 5:
				puts("Kamu memilih metode rotation.");
				puts("Masukan nama untuk data");
				printf("Nama : ");
				scanf("%[^\n]", &name); getchar();
				puts("sekarang pilih cara untuk collision handling.");
				mainMenu2();
				printf("Pilihan : ");
				scanf("%d", &choice2); getchar();
				
				switch(choice2){
					case 1:
						  linearRotatingInsert(name);
						break;
						
					case 2:
						 chainingRotateInsert(name);
						
					case 3:
						puts("Rehashing diperlukan jika terjadi collision (tabrakan) dan tabel sudah penuh atau tingkat keterisian sudah terlalu tinggi.");
						break;
						
					case 4:
						break;
						
					default:
						printf("There are not collision handling method for that number!\n");
				}
				
				break;
				
			default:
				printf("There are not hashing method for that number!\n");
				break;
		}
	
}

int main(){
	int use = 1;
	do {
    int choice = 0;
    mainMenu3();
    printf("Pilih : ");
    scanf("%d", &choice);
    getchar(); // Clears newline after integer input

    switch (choice) {
        case 1:
            mainMenu1();
            break;

        case 2: {
            int choicePrint = 0;
            printf("\nMau print data linear atau data chaining?\n");
            printf("1. Data Linear\n");
            printf("2. Data Chaining\n");
            printf("Pilih: ");
            scanf("%d", &choicePrint);
            getchar(); // Clear newline

            if (choicePrint == 1) {
                printDataLinear();
                printf("\n");
            } else if (choicePrint == 2) {
                printDataChaining();
                printf("\n");
            } else {
                printf("Pilihan tidak valid. Silakan pilih 1 atau 2.\n");
            }
            break;
        }
		
		case 3:
			use = 0;
			break;
			
        default:
            printf("Pilihan tidak valid. Coba lagi.\n");
            break;
    	}
	} while (use != 0); // Assuming there's a way to exit later

	puts("THX FOR USING OUR APP");
	return 0;
}
