#include "Businesscardbook.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void BusinessCardBook_Create(BusinessCardBook *businessCardBook){
	Create(&(businessCardBook->list));
	businessCardBook->length = 0;
	businessCardBook->current = NULL;
}

BusinessCard* Put(BusinessCardBook *businessCardBook, BusinessCard businessCard){
	AppendFromTail(&(businessCardBook->list), &businessCard, sizeof(businessCard));
	businessCardBook->current = (businessCardBook->list.current + 1);
	businessCardBook->length++;
	return businessCardBook->current;
}

void BusinessCardBook_Find(BusinessCardBook *businessCardBook, char(*name), BusinessCard**(*indexes), Long *count){
	Long i = 0;
	*count = 0;
	Node* (*nodeIndexes);

	if ((*indexes) != NULL){
		free(*indexes);
		(*indexes) = NULL;
	}
	*indexes = (BusinessCard*(*))calloc(businessCardBook->length, sizeof(BusinessCard*));
	LinearSarchDuplicate(&businessCardBook->list, name, &nodeIndexes, &count, CompareName);
	while (i < count){
		(*indexes)[i] = nodeIndexes[i] + 1;
		i++;
	}
	if (nodeIndexes != NULL){
		free(nodeIndexes);
	}
}

BusinessCard PullOut(BusinessCardBook *businessCardBook, BusinessCard *index){
	BusinessCard businessCard;
	Node *nodeIndex;

	businessCard = (*index);
	nodeIndex = LinearSarchUnique(&businessCardBook->list, index, CompareCard);
	Delete(&businessCardBook->list, nodeIndex);
	if (businessCardBook->list.current != NULL){
		businessCardBook->current = businessCardBook->list.current + 1;
	}
	else{
		businessCardBook->current = NULL;
	}
	businessCardBook->length--;

	return businessCard;
}

void BusinessCardBook_Destroy(BusinessCardBook *businessCardBook){
	Destroy(&businessCardBook->list);
}

BusinessCard* BusinessCardBook_First(BusinessCardBook *businessCardBook){
	First(&businessCardBook->list);
	businessCardBook->current = businessCardBook->list.current + 1;
	return businessCardBook->current;
}

BusinessCard* BusinessCardBook_Previous(BusinessCardBook *businessCardBook){
	Previous(&businessCardBook->list);
	businessCardBook->current = businessCardBook->list.current + 1;
	return businessCardBook->current;
}

BusinessCard* BusinessCardBook_Next(BusinessCardBook *businessCardBook){
	Next(&businessCardBook->list);
	businessCardBook->current = businessCardBook->list.current + 1;
	return businessCardBook->current;
}

BusinessCard* BusinessCardBook_Last(BusinessCardBook *businessCardBook){
	Last(&businessCardBook->list);
	businessCardBook->current = businessCardBook->list.current + 1;
	return businessCardBook->current;
}

BusinessCard* FindByCompanyName(BusinessCardBook *businessCardBook, char(*CompanyName)) {
	BusinessCard *index = NULL;
	Node *nodeIndex;
	nodeIndex=LinearSarchUnique(&businessCardBook->list, CompanyName, compareCompanyName);
	if (nodeIndex != NULL){
		index = nodeIndex + 1;
	}
	return index;
}

Long Save(BusinessCardBook *businessCardBook){
	Long companyCode;
	Company company;
	BusinessCard *previous = NULL;
	FILE *companyFile;
	FILE *personalFile;

	int flag;
	companyFile = fopen("company.dat", "wb+");
	personalFile = fopen("personal.dat", "wb");
	if (companyFile != NULL&&personalFile != NULL){
		First(&businessCardBook->list);
		if (businessCardBook->list.head != NULL){
			businessCardBook->current = businessCardBook->list.current + 1;
			while (previous != businessCardBook->current){
				companyCode = 1;
				fseek(companyFile, 0, SEEK_SET);
				flag = fread(&company, sizeof(Company), 1, companyFile);
				while (flag == 1 && strcmp(businessCardBook->current->company.name, company.name) != 0){
					companyCode++;
					flag = fread(&company, sizeof(Company), 1, companyFile);
				}
				if (flag < 1){
					fwrite(&(businessCardBook->current->company), sizeof(Company), 1, companyFile);
				}
				fwrite(&companyCode, sizeof(Long), 1, personalFile);
				fwrite(&(businessCardBook->current->personal), sizeof(Personal), 1, personalFile);
				previous = businessCardBook->current;
				Next(&businessCardBook->list);
				businessCardBook->current = businessCardBook->list.current + 1;
			}
		}
		fclose(companyFile);
		fclose(personalFile);
	}
	return businessCardBook->length;
}

Long Load(BusinessCardBook *businessCardBook){
	BusinessCard businessCard;
	Long companyCode;
	Long companyCount;
	FILE *companyFile;
	FILE *personalFile;
	int flag;
	companyFile = fopen("company.dat", "rb");
	personalFile = fopen("personal.dat", "rb");

	if (personalFile != NULL&&companyFile != NULL){
		fread(&companyCode, sizeof(Long), 1, personalFile);
		flag=fread(&(businessCard.personal), sizeof(Personal), 1, personalFile);
		while (flag==1&&!feof(personalFile)){
			fseek(companyFile, 0, SEEK_SET);
			flag=fread(&businessCard.company, sizeof(Company), 1, companyFile);
			companyCount = 1;
			while (flag==1 && companyCode != companyCount){
				companyCount++;
				flag = fread(&businessCard.company, sizeof(Company), 1, companyFile);
			}
			AppendFromTail(&businessCardBook->list, &businessCard, sizeof(BusinessCard));
			businessCardBook->current = businessCardBook->list.current+1;
			businessCardBook->length++;
			fread(&companyCode, sizeof(Long), 1, personalFile);
			flag = fread(&(businessCard.personal), sizeof(Personal), 1, personalFile);
		}
		
		fclose(companyFile);
		fclose(personalFile);
	}
	return businessCardBook->length;
}

BusinessCard BusinessCard_GetAt(BusinessCardBook* businessCardBook,Node *index){
	BusinessCard businessCard;
	GetAt(&businessCardBook->list, index, &businessCard, sizeof(BusinessCard));
	return businessCard;
}

int compareCompanyName(void *one, void *other){
	Company *company = (Company*)one;
	char(*key) = (char(*))other;
	return strcmp(company->name, key);
}
/*int compareCompany(void *one, void *other){
	Company *company = (Company*)one;
	Company *company1 = (Company*)other;
	return strcmp(company->name, company1->name);
}*/

int CompareName(void *one, void *other){
	BusinessCard *businessCard = (BusinessCard*)one;
	char(*key) = (char(*))other;
	return strcmp(businessCard->personal.name, key);
}

int CompareCard(void *one, void *other){
	int ret;
	BusinessCard *businessCard = (BusinessCard*)one;
	BusinessCard *businessCard1 = (BusinessCard*)other;
	if (businessCard == businessCard1){
		ret = 0;
	}
	else{
		ret = -1;
	}
	return ret;
}