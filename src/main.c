#include "Businesscardbook.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	BusinessCardBook businessCardBook;
	BusinessCard businessCard;
	BusinessCard *index;
	BusinessCard busin;
	BusinessCard* (*indexes)=NULL;
	Long count;
	Create(&businessCardBook);
	strcpy(businessCard.company.name, "�Ｚ");
	strcpy(businessCard.company.address, "����");
	strcpy(businessCard.company.telephone, "01025341111");
	strcpy(businessCard.company.fax, "032123");
	strcpy(businessCard.company.homepage, "����");
	strcpy(businessCard.personal.name, "�ڱ浿");
	strcpy(businessCard.personal.position, "�̻�");
	strcpy(businessCard.personal.mobile, "20312322");
	strcpy(businessCard.personal.email, "12412@wiejd.com");
	//businessCard.next = NULL;
	index=Put(&businessCardBook, businessCard);
	busin=PullOut(&businessCardBook, index);
	Put(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", busin.company.name, busin.company.address, busin.company.telephone, busin.company.fax, busin.company.homepage,
		busin.personal.name, busin.personal.position, busin.personal.mobile, busin.personal.email);
	strcpy(businessCard.company.name, "LG");
	strcpy(businessCard.company.address, "������");
	strcpy(businessCard.company.telephone, "01021211111");
	strcpy(businessCard.company.fax, "12344");
	strcpy(businessCard.company.homepage, "�ϳ���");
	strcpy(businessCard.personal.name, "��浿");
	strcpy(businessCard.personal.position, "�ǹ�");
	strcpy(businessCard.personal.mobile, "12333");
	strcpy(businessCard.personal.email, "12212@wiejd.com");
	//businessCard.next = NULL;
	index = Put(&businessCardBook, businessCard);
	busin = PullOut(&businessCardBook, index);
	Put(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", busin.company.name, busin.company.address, busin.company.telephone, busin.company.fax, busin.company.homepage,
		busin.personal.name, busin.personal.position, busin.personal.mobile, busin.personal.email);
	strcpy(businessCard.company.name, "KT");
	strcpy(businessCard.company.address, "����");
	strcpy(businessCard.company.telephone, "4444111");
	strcpy(businessCard.company.fax, "0123323");
	strcpy(businessCard.company.homepage, "����");
	strcpy(businessCard.personal.name, "���浿");
	strcpy(businessCard.personal.position, "ȸ��");
	strcpy(businessCard.personal.mobile, "203144422");
	strcpy(businessCard.personal.email, "1212@wiejd.com");
	//businessCard.next = NULL;
	index = Put(&businessCardBook, businessCard);
	busin = PullOut(&businessCardBook, index);
	Put(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", busin.company.name, busin.company.address, busin.company.telephone, busin.company.fax, busin.company.homepage,
		busin.personal.name, busin.personal.position, busin.personal.mobile, busin.personal.email);
	strcpy(businessCard.company.name, "KdT");
	strcpy(businessCard.company.address, "��d��");
	strcpy(businessCard.company.telephone, "44��44111");
	strcpy(businessCard.company.fax, "01233d23");
	strcpy(businessCard.company.homepage, "����");
	strcpy(businessCard.personal.name, "�ֱ浿");
	strcpy(businessCard.personal.position, "ȸ��");
	strcpy(businessCard.personal.mobile, "203144422");
	strcpy(businessCard.personal.email, "1212@wiejd.com");
	//businessCard.next = NULL;
	index = Put(&businessCardBook, businessCard);
	Find(&businessCardBook, "���浿", &indexes, &count);
	//busin = PullOut(&businessCardBook, indexes[0]);
	printf("%s\n", indexes[0]->company.name);
	
	First(&businessCardBook);
	//Last(&businessCardBook);
	printf("ù��°:%s\n", businessCardBook.current->personal.name);
	Arrange(&businessCardBook);
	First(&businessCardBook);
	while (businessCardBook.current != NULL){
		printf("%s\n", businessCardBook.current->personal.name);
		businessCardBook.current = businessCardBook.current->next;
	}
	printf("\n");
	First(&businessCardBook);
	Last(&businessCardBook);
	printf("%s\n", businessCardBook.current->personal.name);
	Previous(&businessCardBook);
	printf("%s\n", businessCardBook.current->personal.name);
	Previous(&businessCardBook);
	printf("%s\n", businessCardBook.current->personal.name);
	Previous(&businessCardBook);
	printf("%s\n", businessCardBook.current->personal.name);
	Previous(&businessCardBook);
	printf("%s\n", businessCardBook.current->personal.name);
	Previous(&businessCardBook);
	printf("%s\n", businessCardBook.current->personal.name);	printf("\n");
	Next(&businessCardBook);
	printf("%s\n", businessCardBook.current->personal.name);
	return 0;
}