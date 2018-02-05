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
	strcpy(businessCard.company.name, "삼성");
	strcpy(businessCard.company.address, "강남");
	strcpy(businessCard.company.telephone, "01025341111");
	strcpy(businessCard.company.fax, "032123");
	strcpy(businessCard.company.homepage, "울집");
	strcpy(businessCard.personal.name, "박길동");
	strcpy(businessCard.personal.position, "이사");
	strcpy(businessCard.personal.mobile, "20312322");
	strcpy(businessCard.personal.email, "12412@wiejd.com");
	//businessCard.next = NULL;
	index=Put(&businessCardBook, businessCard);
	busin=PullOut(&businessCardBook, index);
	Put(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", busin.company.name, busin.company.address, busin.company.telephone, busin.company.fax, busin.company.homepage,
		busin.personal.name, busin.personal.position, busin.personal.mobile, busin.personal.email);
	strcpy(businessCard.company.name, "LG");
	strcpy(businessCard.company.address, "강서구");
	strcpy(businessCard.company.telephone, "01021211111");
	strcpy(businessCard.company.fax, "12344");
	strcpy(businessCard.company.homepage, "니네집");
	strcpy(businessCard.personal.name, "김길동");
	strcpy(businessCard.personal.position, "권무");
	strcpy(businessCard.personal.mobile, "12333");
	strcpy(businessCard.personal.email, "12212@wiejd.com");
	//businessCard.next = NULL;
	index = Put(&businessCardBook, businessCard);
	busin = PullOut(&businessCardBook, index);
	Put(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", busin.company.name, busin.company.address, busin.company.telephone, busin.company.fax, busin.company.homepage,
		busin.personal.name, busin.personal.position, busin.personal.mobile, busin.personal.email);
	strcpy(businessCard.company.name, "KT");
	strcpy(businessCard.company.address, "강동");
	strcpy(businessCard.company.telephone, "4444111");
	strcpy(businessCard.company.fax, "0123323");
	strcpy(businessCard.company.homepage, "옆집");
	strcpy(businessCard.personal.name, "나길동");
	strcpy(businessCard.personal.position, "회장");
	strcpy(businessCard.personal.mobile, "203144422");
	strcpy(businessCard.personal.email, "1212@wiejd.com");
	//businessCard.next = NULL;
	index = Put(&businessCardBook, businessCard);
	busin = PullOut(&businessCardBook, index);
	Put(&businessCardBook, businessCard);
	printf("%s %s %s %s %s %s %s %s %s\n", busin.company.name, busin.company.address, busin.company.telephone, busin.company.fax, busin.company.homepage,
		busin.personal.name, busin.personal.position, busin.personal.mobile, busin.personal.email);
	strcpy(businessCard.company.name, "KdT");
	strcpy(businessCard.company.address, "강d동");
	strcpy(businessCard.company.telephone, "44ㅇ44111");
	strcpy(businessCard.company.fax, "01233d23");
	strcpy(businessCard.company.homepage, "옆집");
	strcpy(businessCard.personal.name, "최길동");
	strcpy(businessCard.personal.position, "회장");
	strcpy(businessCard.personal.mobile, "203144422");
	strcpy(businessCard.personal.email, "1212@wiejd.com");
	//businessCard.next = NULL;
	index = Put(&businessCardBook, businessCard);
	Find(&businessCardBook, "나길동", &indexes, &count);
	//busin = PullOut(&businessCardBook, indexes[0]);
	printf("%s\n", indexes[0]->company.name);
	
	First(&businessCardBook);
	//Last(&businessCardBook);
	printf("첫번째:%s\n", businessCardBook.current->personal.name);
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