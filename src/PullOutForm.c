#include "Businesscardbook.h"
#include "PullOutForm.h"
#include "resource.h"
#include <stdio.h>

BOOL CALLBACK PullOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG:
		ret = PullOutForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = PullOutForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL PullOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	BusinessCard businessCard;
	HWND instance;
	BusinessCard *index;
	Long current = 1;
	TCHAR current_[8];
	TCHAR length[8];

	//1.����ö �����츦 ã�´�..
	instance = FindWindow("#32770", "����ö");
	businessCardBook = (BusinessCardBook*)GetWindowLong(instance, GWL_USERDATA);

	//2.����ö �������� ����ö���� ������ �̴´�.
	businessCard = PullOut(businessCardBook, businessCardBook->current);

	//3.���� ������ �̱� �����쿡 ����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephone);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.fax);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.homepage);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.mobile);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.email);
	//4.����ö �����쿡 ������ġ�� ������ ����Ѵ�.
	index = businessCardBook->current;
	if (index != NULL){
		SendMessage(GetDlgItem(instance, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(instance, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(instance, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(instance, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(instance, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(instance, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(instance, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		BusinessCardBook_First(businessCardBook);
		while (businessCardBook->current != index){
			current++;
			BusinessCardBook_Next(businessCardBook);
		}
			//5.����ö �����쿡 ������ ������ ����Ѵ�.
			sprintf(current_, "%d", current);
			SendMessage(GetDlgItem(instance, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current_);
			//6.����ö �����쿡 ��ġ�� ����Ѵ�.
			sprintf(length, "%d", businessCardBook->length);
			SendMessage(GetDlgItem(instance, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)length);
		
	}
	return FALSE;
}

BOOL PullOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	BusinessCard businessCard;
	HWND instance;
	int messageID;
	BusinessCard *index;
	TCHAR current[8];
	TCHAR length[8];

	//1.�޼��� �ڽ��� ����.
	messageID = MessageBox(hWnd, "������ �ٽ� ������??","Ȯ��", MB_YESNOCANCEL);
	//2.����ö �����츦 ã�´�.
	instance = FindWindow("#32770", "����ö");
	businessCardBook = (BusinessCardBook*)GetWindowLong(instance, GWL_USERDATA);
	switch (messageID)
	{
	case IDYES:
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_GETTEXT, (WPARAM)128, (LPARAM)businessCard.company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.email);
		
		//3.����ö �������� ����ö�� ������ �ִ´�.
		index = Put(businessCardBook, businessCard);
		SendMessage(GetDlgItem(instance, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(instance, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(instance, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(instance, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(instance, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(instance, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(instance, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		//4.����ö �����쿡 ��ġ�� ����Ѵ�.
		sprintf(current, "%d", businessCardBook->length);
		SendMessage(GetDlgItem(instance, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current);
		sprintf(length, "%d", businessCardBook->length);
		SendMessage(GetDlgItem(instance, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)length);
		EndDialog(hWnd, 0);
		break;
	case IDNO:
		if (businessCardBook->list.head == NULL){
			SendMessage(GetDlgItem(instance, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(instance, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
			SendMessage(GetDlgItem(instance, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
		}
		EndDialog(hWnd, 0);
		break;
	case IDCANCEL:
		break;
	default:
		break;
	}
	return FALSE;
}