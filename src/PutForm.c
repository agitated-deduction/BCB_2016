#include "Businesscardbook.h"
#include "PutForm.h"
#include "PostcardForm.h"
#include "resource.h"
#include <stdio.h>

BOOL CALLBACK PutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG:
		ret = PutForm_OnItDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = PutForm_OnCommend(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = PutForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL PutForm_OnItDialog(HWND hWnd, WPARAM wParam, LPARAM lParam){
	CHAR position[][16] = { "사장", "이사", "부장", "대리", "과장", "전무" };
	CHAR domain[][16] = { "naver.com", "gmail.com","yahoo.co.kr","nate.com"};
	Long i = 0;
	//1.직책리스트를 준비한다.
	//2.도메인 리스트를 준비한다.
	while (i < sizeof(position)/sizeof(position[0])){
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)position[i]);
		i++;
	}
	i = 0;
	while (i < sizeof(domain) / sizeof(domain[0])){
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)domain[i]);
		i++;
	}
	return FALSE;
}

BOOL PutForm_OnCommend(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_PUT:
		ret = PutForm_OnPutButtonClicked(hWnd, wParam, lParam);
		break; 
	case IDC_BUTTON_POST:
		ret = PutForm_OnPostButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_EDIT_COMPANYNAME:
		ret = PutForm_OnCompanyNameKillFocus(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;
}

BOOL PutForm_OnPostButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_POSTFORM), NULL, PostBookProc);
	}
	return FALSE;
}

BOOL PutForm_OnPutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCard businessCard;
	BusinessCardBook *businessCardBook;
	BusinessCard *index;
	TCHAR length[8];
	TCHAR current[8];
	HWND instance;
	TCHAR email[32];
	TCHAR domain[16];

	if (HIWORD(wParam) == BN_CLICKED) {
		//1.명함을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANYNAME), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONE), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_HOMEPAGE), WM_GETTEXT, (WPARAM)128, (LPARAM)businessCard.company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), WM_GETTEXT, (WPARAM)32, (LPARAM)businessCard.personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MOBILE), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAIL), WM_GETTEXT, (WPARAM)64, (LPARAM)email);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), WM_GETTEXT, (WPARAM)16, (LPARAM)domain);
		sprintf(businessCard.personal.email, "%s@%s", email, domain);

		//2.명함철 윈도우를 찾는다.
		instance = FindWindow("#32770", "명함철");
		businessCardBook = (BusinessCardBook*)GetWindowLong(instance, GWL_USERDATA);

		//3.명함철 윈도우의 명함철에 명함을 넣는다.
		index = Put(businessCardBook,businessCard);

		//4.명함철윈도우에 넣은 명함을 출력한다.
		SendMessage(GetDlgItem(instance, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(instance, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(instance, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(instance, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(instance, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(instance, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(instance, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);

		//5.명함의 개수와 위치를 출력한다.
		sprintf(length, "%d", businessCardBook->length);
		SendMessage(GetDlgItem(instance, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)length);

		//4.명함의 위치를 출력한다.
		sprintf(current, "%d", businessCardBook->length);
		SendMessage(GetDlgItem(instance, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current);
		EndDialog(hWnd, 0);
	}
	
	return FALSE;
}

BOOL PutForm_OnCompanyNameKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam){
	TCHAR companyname[32];
	BusinessCardBook *businessCardBook;
	HWND instance;
	BusinessCard *index;
	if (HIWORD(wParam) == EN_KILLFOCUS){
		//1.상호를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANYNAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyname);
		//2.명함철 윈도우를 찾는다.
		instance = FindWindow("#32770", "명함철");
		//3.명함철 윈도우에 명함철에서 상호를 찾는다.
		businessCardBook = (BusinessCardBook*)GetWindowLong(instance, GWL_USERDATA);
		index = FindByCompanyName(businessCardBook, companyname);
		//4.찾았으면 회사를 출력한다.
		if (index != NULL){
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		}
	}
	return FALSE;
}

BOOL PutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam){
	EndDialog(hWnd, 0);
	return FALSE;
}