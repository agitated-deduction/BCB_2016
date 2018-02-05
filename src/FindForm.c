#include "Businesscardbook.h"
#include "resource.h"
#include "FindForm.h"
#include <string.h>
#include <stdio.h>

BOOL CALLBACK FindFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG:	ret = FindForm_OnItDialog(hWnd, wParam, lParam);		break;
	case WM_COMMAND:	ret = FindForm_OnCommend(hWnd, wParam, lParam);		break;
	case WM_CLOSE:		ret = FindForm_OnClose(hWnd, wParam, lParam);		break;
	default:			ret = FALSE;		break;
	}
	return ret;
}

BOOL FindForm_OnItDialog(HWND hWnd, WPARAM wParam, LPARAM lParam){

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
	return FALSE;
}

BOOL FindForm_OnCommend(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIRST:		ret = FindForm_OnFindButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_NEXT:		ret = FindForm_OnNextButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_PREVIOUS:	ret = FindForm_OnPreviousButtonClicked(hWnd, wParam, lParam);	break;
	case IDC_BUTTON_LAST:		ret = FindForm_OnLastButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_FIND:		ret = FindForm_OnFindButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_CHOOSE:		ret = FindForm_OnChooseButtonClicked(hWnd, wParam, lParam);		break;
	default:					ret = FALSE;		break;
	}
	return ret;
}

BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCard* (*indexes);

	indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL){
		free(indexes);
		indexes = NULL;
	}
	RemoveProp(hWnd, "count");
	RemoveProp(hWnd, "current");
	EndDialog(hWnd, 0);

	return FALSE;
}

BOOL FindForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	Long count;
	BusinessCardBook *businessCardBook;
	BusinessCard* (*indexes)=NULL;
	TCHAR name[11];
	TCHAR length[8];
	HWND instance;
	Long current = 0;

	if (HIWORD(wParam) == BN_CLICKED){
		//1.성명을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		
		//2.명함철 윈도우를 찾는다.
		instance = FindWindow("#32770", "명함철");
	
		//3.읽은 성명으로 명함철 윈도우 명함철에서 명함을 찾는다.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		businessCardBook = (BusinessCardBook*)GetWindowLong(instance, GWL_USERDATA);
		BusinessCardBook_Find(businessCardBook, name, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (Long)indexes);
		SetProp(hWnd, "count", (HANDLE)count);
		SetProp(hWnd, "current", (HANDLE)current);
		//4.찾은 명하들 중 첫번째 명함을 출력한다.
		if(count > 0){
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->company.telephone);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->company.fax);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->company.homepage);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->personal.mobile);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[0]->personal.email);
			sprintf(length, "%d", count);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)length);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"1");
		}
		else{
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
		}
		
		
	}
	return FALSE;
}

BOOL FindForm_OnChooseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	TCHAR current_[8];
	BusinessCard*(*indexes);
	BusinessCardBook* businessCardBook;
	BusinessCard *businessCard;
	HWND instance;
	Long current,count,index=1;
	if (HIWORD(wParam) == BN_CLICKED){
		//1.찾기 윈도우에 선택된 명함을 읽는다.
		current = (Long)GetProp(hWnd, "current");
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "current");
		businessCard = indexes[current];

		//2.명함철 윈도우를 찾는다.
		instance = FindWindow("#32770", "명함철");
		businessCardBook = (BusinessCardBook*)GetWindowLong(instance, GWL_USERDATA);

		//3.명함철 윈도우에 읽은 명함을 출력한다.
		BusinessCardBook_First(businessCardBook);
		while (businessCardBook->current != businessCard){
			index++;
			BusinessCardBook_Next(businessCardBook);
		}
		SendMessage(GetDlgItem(instance, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(instance, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.telephone);
		SendMessage(GetDlgItem(instance, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.fax);
		SendMessage(GetDlgItem(instance, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.homepage);
		SendMessage(GetDlgItem(instance, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(instance, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);
		SendMessage(GetDlgItem(instance, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.mobile);
		SendMessage(GetDlgItem(instance, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.email);
		//4.위치 출력
		sprintf(current_, "%d",index);
		SendMessage(GetDlgItem(instance, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current_);
		FindForm_OnClose(hWnd, wParam, lParam);
	}
	return FALSE;
}

BOOL FindForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCard*(*indexes);
	BusinessCard *index;
	Long current;
	if (HIWORD(wParam) == BN_CLICKED){
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "current");
		//1.찾은 명함중 첫번째 명함으로 이동한다.
		current = 0;
		index = indexes[current];
		SetProp(hWnd, "current",(HANDLE)current);
		//2.첫번째명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		//4.명함의 위치를 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"1");
	}
	return FALSE;
}

BOOL FindForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
		BusinessCard*(*indexes); 
		Long previous;
		TCHAR current[8];
		if (HIWORD(wParam) == BN_CLICKED){
			indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
			previous = (Long)GetProp(hWnd, "current") -1;
			if (previous >= 0){
				SetProp(hWnd, "current", (HANDLE)previous);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->company.name);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->company.address);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->company.telephone);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->company.fax);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->company.homepage);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->personal.name);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->personal.position);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->personal.mobile);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[previous]->personal.email);
				//4.명함의 위치를 출력한다.
				sprintf(current, "%d", previous+1);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current);
			}
		}
		return FALSE;
	}

BOOL FindForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
		BusinessCard*(*indexes);
		Long next;
		Long count;
		TCHAR current[8];
		if (HIWORD(wParam) == BN_CLICKED){
			indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
			next= (Long)GetProp(hWnd, "current")+1;
			count = (Long)GetProp(hWnd, "count");
			if (next < count){
				SetProp(hWnd, "current", (HANDLE)next);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->company.name);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->company.address);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->company.telephone);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->company.fax);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->company.homepage);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->personal.name);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->personal.position);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->personal.mobile);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)indexes[next]->personal.email);
				//4.명함의 위치를 출력한다.
				sprintf(current, "%d", next+1);
				SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current);
			}
		}
		return FALSE;
	}

BOOL FindForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
		BusinessCard*(*indexes);
		BusinessCard *index;
		Long current;
		Long count;
		TCHAR current_[8];
		if (HIWORD(wParam) == BN_CLICKED){
			indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
			count = (Long)GetProp(hWnd, "count");
			current = (Long)GetProp(hWnd, "current");
			current = count - 1;
			SetProp(hWnd, "current", (HANDLE)current);
			//1.찾은 명함중 첫번째 명함으로 이동한다.
			index = indexes[current];
			//2.첫번째명함을 출력한다.
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
			//4.명함의 위치를 출력한다.
			sprintf(current_, "%d", count);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current_);
		}
		return FALSE;
	}
