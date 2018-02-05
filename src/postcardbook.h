#ifndef _POSTCARDBOOK_H_
#define _POSTCARDBOOK_H_
typedef signed long int Long;
typedef struct _address
{
	char zipcode[8];
	char sido[5];
	char gugun[18];
	char dong[27];
	char ri[16];
	char bldg[43];
	char st_bunji[10];
	char ed_bunji[10];
	int seq[6];
}Address;

typedef struct _postcardbook
{
	Address (*Addresses);
	int capacity;
	int length;

}PostCardBook;

void PostCardBook_Create(PostCardBook *pcb, Long capacity);
Long PostCardBook_Load(PostCardBook *pcb);
void PostCardBook_Find(PostCardBook *pcb, char(*dong), Long *count, Long* (*indexes));
void PostCardBook_Destroy(PostCardBook *pcb);
#endif