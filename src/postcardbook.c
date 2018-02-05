#include "postcardbook.h"
#include <stdlib.h>
#include <stdio.h>

void PostCardBook_Create(PostCardBook *pcb, Long capacity){
	pcb->Addresses = (Address(*))calloc(capacity, sizeof(Address));
	pcb->capacity = capacity;
	pcb->length = 0;
}

Long PostCardBook_Load(PostCardBook *pcb){
	Long i, j, k = 0, code;
	Address address, *temp;
	char line[256], word[43];
	FILE *file;
	file = fopen("PostCodeBook.txt", "rt");
	if (file != NULL){
		fgets(line, 256, file);
		fgets(line, 256, file);
		while (!feof(file)){
			if (pcb->length >= pcb->capacity){
				temp = (Address(*))calloc(pcb->capacity + 1, sizeof(Address));
				j = 0;
				while (j <= pcb->length){
					temp[j] = pcb->Addresses[j];
					j ++;
				}
				if (pcb->Addresses != NULL){
					free(pcb->Addresses);
				}
				pcb->Addresses = temp;
				pcb->capacity += 1;
			}
			code = 1;
			i = 0;
			while (line[i] != '\0'){
				j = 0;
				while (line[i] != '\t'&&line[i] != '\n'){
					word[j] = line[i];
					j++;
					i++;
				}
				word[j] = '\0';
				switch (code){
				case 1:strcpy(address.zipcode, word);
					break;
				case 2:strcpy(address.sido, word);
					break;
				case 3:strcpy(address.gugun, word);
					break;
				case 4:strcpy(address.dong, word);
					break;
				case 5:strcpy(address.ri, word);
					break;
				case 6:strcpy(address.bldg, word);
					break;
				case 7:strcpy(address.st_bunji, word);
					break;
				case 8:strcpy(address.ed_bunji, word);
					break;
				case 9:strcpy(address.seq, word);
					break;
				default:
					break;
				}
				code++;
				i++;
			}
			pcb->Addresses[k] = address;
			k++;
			pcb->length++;
			fgets(line, 256, file);
		}
	}
	return pcb->length;
}

void PostCardBook_Find(PostCardBook *pcb, char(*dong), Long *count, Long* (*indexes)){
	Long i=0, j=0, k=0, m=0;
	char key[27];
	char temp[27];
	*count = 0;
	*indexes = (Long(*))calloc(pcb->length, sizeof(Long));
	while (dong[i] != '\0'){
		i = i + 1;
	}
	while (j < i - 2){
		key[j] = dong[j];
		j++;
	}
	key[j] = '\0';
	while (k <= pcb->length){
		j = 0;
		while (j < i - 2){
			temp[j] = pcb->Addresses[k].dong[j];
			j++;
		}
		temp[j] = '\0';
		if (strcmp(key, temp) == 0){
			(*indexes)[m] = k;
			m++;
			(*count)++;
		}
		k++;
	}
}

void PostCardBook_Destroy(PostCardBook *pcb){
	if (pcb->Addresses != NULL){
		free(pcb->Addresses);
	}
}