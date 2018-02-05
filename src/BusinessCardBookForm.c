#include "BusinessCardBookForm.h"
#include "Businesscardbook.h"
#include "PutForm.h"
#include "FindForm.h"
#include "resource.h"
#include "PullOutForm.h"
#include <CommCtrl.h>
#include <stdio.h>
#include <stdlib.h>
#include "IndexBook.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance, LPSTR lpCmdLine, int nCmdShow){
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_BusinessCardBookForm), NULL, BusinessCardBookProc);
	return 0;
}

BOOL CALLBACK BusinessCardBookProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message)
	{
	case WM_INITDIALOG:	ret = BusinessCardBookForm_OnItDialog(hWnd, wParam, lParam);		break;
	case WM_COMMAND:	ret = BusinessCardBookForm_OnCommend(hWnd, wParam, lParam);		break;
	case WM_CLOSE:		ret = BusinessCardBookForm_OnClose(hWnd, wParam, lParam);		break;
	default:			ret = FALSE;		break;
	}
	return ret;
}

BOOL BusinessCardBookForm_OnItDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardBook *businessCardBook;
	BusinessCard *cardIndex;

	IndexBook *indexBook;
	Index(*indexes);
	Index index;
	
	TCHAR length[8];
	Long count;
	Long *indexCount = 0;
	Long i = 0;
	Long j = 0;
	
	HWND hTree;
	HTREEITEM companys;
	HTREEITEM company;
	HTREEITEM parent;

	TVINSERTSTRUCT ti = { 0, };
	
	// 1.1 ����ö�� �غ��Ѵ�.
	businessCardBook = (BusinessCardBook*)malloc(sizeof(BusinessCardBook));
	BusinessCardBook_Create(businessCardBook);
	
	// 1.2 �����Ѵ�.
	count = Load(businessCardBook);

	// 1.3 ����ö�� �غ��Ѵ�.
	indexBook = (IndexBook*)malloc(sizeof(IndexBook));
	IndexBook_Create(indexBook);

	cardIndex = BusinessCardBook_First(businessCardBook);

	// 1.4 ����� ������ ������ŭ �ݺ��Ѵ�.
	while (i < count){
		Add(indexBook, cardIndex);
		cardIndex = BusinessCardBook_Next(businessCardBook);
		i++;
	}

	// 1.5 ����ö���� �����Ѵ�.
	IndexBook_Arrange(indexBook);

	// �����쿡 ����ö ���̱�
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardBook);

	if (count > 0){
		// 1.6 ù��° �������� �̵��Ѵ�.
		cardIndex = BusinessCardBook_First(businessCardBook);

		// 1.7 ù��° ������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)cardIndex->personal.email);

		// 1.8 ȸ��(�ε���)����� �����.
		MakeList(indexBook, &indexes, &indexCount);

		//��Ʈ����
		ti.hParent = NULL;
		ti.hInsertAfter = TVI_FIRST;
		ti.item.mask = TVIF_TEXT | TVIF_PARAM;
		ti.item.pszText = "ȸ���";
		companys = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBOOK), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&ti);
		parent = TreeView_GetParent(companys, TVGN_PARENT);
		// 1.9 ���ΰ�����ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < indexBook->length)
		{
			index = indexes[i];
			// 1.9.1 Ʈ���信 ��ȣ�׸��� �߰��Ѵ�. TVM_XXX
			ti.hParent = companys;
			ti.hInsertAfter = TVI_LAST;
			ti.item.mask = TVIF_TEXT | TVIF_PARAM ;
			ti.item.pszText = index.name;
			company = SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBOOK), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&ti);
			
			// 1.9.2 ������ ��뷮��ŭ �ݺ��Ѵ�. 
			j = 0;
			while (j < index.length) {
				// 1.9.2.1 Ʈ���信 ������ ����Ѵ�. 
				cardIndex = Index_GetAt(&index, j);
				ti.hParent = company;
				ti.hInsertAfter = TVI_LAST;
				ti.item.pszText = cardIndex->personal.name;
				ti.item.mask = TVIF_TEXT | TVIF_PARAM;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEXBOOK), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&ti);
				j++;
			}
			i++;
		}
		
		// 1.10 Ʈ���信 ���õ� ������ ǥ���Ѵ�.

		// 1.11 ������ ������ ����Ѵ�.
		sprintf(length, "%d", businessCardBook->length);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)length);

		// 1.12 ������ ��ġ�� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"1");
	}
	else{
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_LENGTH), WM_SETTEXT, (WPARAM)0, (LPARAM)"0");
	}

	return FALSE;
}

BOOL BusinessCardBookForm_OnCommend(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIRST:		ret = BusinessCardBookForm_OnFirstButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_NEXT:		ret = BusinessCardBookForm_OnNextButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_PREVIOUS:	ret = BusinessCardBookForm_OnPreviousButtonClicked(hWnd, wParam, lParam);	break;
	case IDC_BUTTON_LAST:		ret = BusinessCardBookForm_OnLastButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_PUT:		ret = BusinessCardBookForm_OnPutButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_FIND:		ret = BusinessCardBookForm_OnFindButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_PULLOUT:	ret = BusinessCardBookForm_OnPullOutButtonClicked(hWnd, wParam, lParam);		break;
	case IDC_BUTTON_ARRANGE:	ret = BusinessCardBookForm_OnArrangeButtonClicked(hWnd, wParam, lParam);		break;
	default:					ret = FALSE;		break;
	}
	return ret;
}

BOOL BusinessCardBookForm_OnPutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTFORM), NULL, PutFormProc);
	}

	return FALSE;
}

BOOL BusinessCardBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDFORM), NULL, FindFormProc);
	}

	return FALSE;
}

BOOL BusinessCardBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	BusinessCard *index;

	if (HIWORD(wParam) == BN_CLICKED){
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		//1.����ö���� �����Ѵ�.
		
		//Arrange(businessCardBook);
		
		//2.����ö�� ù��° �������� �̵��Ѵ�.
		index = BusinessCardBook_First(businessCardBook);
		//3.ù��° ������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		//5.������ ��ġ�� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"1");
		
	}
	
	return FALSE;
}

BOOL BusinessCardBookForm_OnPullOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PULLOUTFORM), NULL, PullOutFormProc);
	}
	return FALSE;
}

BOOL BusinessCardBookForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	BusinessCard *index;
	
	if (HIWORD(wParam) == BN_CLICKED){
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		
		//1.ù��° �������� �̵��Ѵ�.
		index = BusinessCardBook_First(businessCardBook);
		
		//2.����ö���� ù��° ������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		
		//4.������ ��ġ�� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)"1");
	}

	return FALSE;
}

BOOL BusinessCardBookForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	BusinessCard *index;
	BusinessCard *temp;
	TCHAR current[3];
	Long curr = 1;
	
	if (HIWORD(wParam) == BN_CLICKED){
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		
		//1.���� �������� �̵��Ѵ�.
		index = BusinessCardBook_Previous(businessCardBook);
	
		//2.����ö���� ���������� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		
		//4.������ ��ġ�� ����Ѵ�.
		temp = BusinessCardBook_First(businessCardBook);
		while (temp != index){
			curr++;
			temp = BusinessCardBook_Next(businessCardBook);
		}
		sprintf(current, "%d", curr);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current);
	}

	return FALSE;
}

BOOL BusinessCardBookForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	BusinessCard *index;
	BusinessCard *temp;
	TCHAR current[3];
	Long curr = 1;
	
	if (HIWORD(wParam) == BN_CLICKED){
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		
		//1.���� �������� �̵��Ѵ�.
		index = BusinessCardBook_Next(businessCardBook);
	
		//2.����ö���� ���������� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		
		//4.������ ��ġ�� ����Ѵ�.
		temp = BusinessCardBook_First(businessCardBook);
		while (temp != index){
			curr++;
			temp = BusinessCardBook_Next(businessCardBook);
		}
		sprintf(current, "%d", curr);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current);
	}

	return FALSE;
}

BOOL BusinessCardBookForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	BusinessCard *index;
	TCHAR current[8];
	
	if (HIWORD(wParam) == BN_CLICKED){
		businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
	
		//1.������ �������� �̵��Ѵ�.
		index = BusinessCardBook_Last(businessCardBook);
		
		//2.����ö���� ������������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANYNAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_TELEPHONE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephone);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_HOMEPAGE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.homepage);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_MOBILE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.mobile);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_EMAIL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.email);
		
		//4.������ ��ġ�� ����Ѵ�.
		sprintf(current, "%d", businessCardBook->length);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_CURRENT), WM_SETTEXT, (WPARAM)0, (LPARAM)current);
	}

	return FALSE;
}

BOOL BusinessCardBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BusinessCardBook *businessCardBook;
	
	businessCardBook = (BusinessCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
	Save(businessCardBook);
	
	if (businessCardBook != NULL)
	{
		Save(businessCardBook);
		BusinessCardBook_Destroy(businessCardBook);
		free(businessCardBook);
	}
	EndDialog(hWnd, 0);
	
	return FALSE;
}