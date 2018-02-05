#ifndef _BUSINESSCARDBOOK_H_
#define _BUSINESSCARDBOOK_H_
#include "LinkedList.h"
typedef signed long int Long;

typedef struct _company{
	char name[32];
	char address[64];
	char telephone[12];
	char fax[12];
	char homepage[128];
}Company;

typedef struct _personal{
	char name[11];
	char position[32];
	char mobile[12];
	char email[64];
}Personal;

typedef struct _businesscard{
	Company company;
	Personal personal;
}BusinessCard;

typedef struct _businesscardbook{
	LinkedList list;
	Long length;
	BusinessCard *current;
}BusinessCardBook;

void BusinessCardBook_Create(BusinessCardBook *businessCardBook);
BusinessCard* Put(BusinessCardBook *businessCardBook,BusinessCard businessCard);
void BusinessCardBook_Find(BusinessCardBook *businessCardBook, char(*name), BusinessCard**(*indexes), Long *count);
BusinessCard PullOut(BusinessCardBook *businessCardBook, BusinessCard *index);
void BusinessCardBook_Destroy(BusinessCardBook *businessCardBook);
BusinessCard* BusinessCardBook_First(BusinessCardBook *businessCardBook);
BusinessCard* BusinessCardBook_Previous(BusinessCardBook *businessCardBook);
BusinessCard* BusinessCardBook_Next(BusinessCardBook *businessCardBook);
BusinessCard* BusinessCardBook_Last(BusinessCardBook *businessCardBook);
BusinessCard* FindByCompanyName(BusinessCardBook *businessCardBook, char(*CompanyName));
Long Save(BusinessCardBook *businessCardBook);
Long Load(BusinessCardBook *businessCardBook);
BusinessCard BusinessCard_GetAt(BusinessCardBook* businessCardBook, Node *index);
int compareCompanyName(void *one, void *other);
int CompareName(void *one, void *other);
int CompareCard(void *one, void *other);
#endif