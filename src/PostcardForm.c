#include "PostcardForm.h"
#include "postcardbook.h"
#include "resource.h"
#include <CommCtrl.h>
#include <stdio.h>

BOOL CALLBACK PostBookProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	BOOL ret;
	switch (message)
	{
	case WM_INITDIALOG:
		ret = PostBookForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = PostBookForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_NOTIFY:
		ret = PostBookForm_OnNotify(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = PostBookForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}
	return ret;

}

BOOL PostBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam){
	PostCardBook *pcb;

	LVCOLUMN column = { 0, };
	pcb = (PostCardBook(*))malloc(sizeof(PostCardBook));
	PostCardBook_Create(pcb, 60000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)pcb);
	PostCardBook_Load(pcb);
	column.mask = LVCF_TEXT | LVCF_WIDTH;
	column.cx = 50;
	column.pszText = "锅龋";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 300;
	column.pszText = "林家";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 140;
	column.pszText = "快祈锅龋";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return FALSE;
}

BOOL PostBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BOOL ret;

	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_FIND:
		ret = PostBookForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL PostBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam){
	BOOL ret;

	switch (wParam)
	{
	case IDC_LIST_ADDRESS:
		ret = PostBookForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL PostBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam){
	PostCardBook *pcb;

	pcb = (PostCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
	if (pcb != NULL)
	{
		free(pcb);
	}
	EndDialog(hWnd, 0);

	return FALSE;
}

BOOL PostBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	TCHAR dong[27];
	TCHAR number[64];
	TCHAR address[256];
	Long(*indexes);
	Long count;
	LVITEM item = { 0, };
	Long i = 0;
	PostCardBook *pcb;
	
	if (HIWORD(wParam) == BN_CLICKED){
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_DONG), WM_GETTEXT, (WPARAM)27, (LPARAM)dong);
		pcb = (PostCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		PostCardBook_Find(pcb, dong, &count, &indexes);
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);
		item.mask = LVIF_TEXT;
		while (i < count){
			item.iItem = i;
			item.iSubItem = 0;
			sprintf(number, "%d", i + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
			sprintf(address, "%s %s %s %s %s %s %s", pcb->Addresses[indexes[i]].sido, pcb->Addresses[indexes[i]].gugun,
				pcb->Addresses[indexes[i]].dong, pcb->Addresses[indexes[i]].ri, pcb->Addresses[indexes[i]].bldg, pcb->Addresses[indexes[i]].st_bunji, pcb->Addresses[indexes[i]].ed_bunji);
			item.iSubItem = 1;
			item.pszText = address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = pcb->Addresses[i].zipcode;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			i++;
		}
		if (indexes != NULL){
			free(indexes);
			indexes = NULL;
		}
	}

	return FALSE;
}

BOOL PostBookForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam){
	TCHAR address[256];
	TCHAR zipcode[8];
	TCHAR caption[256];
	HWND instance;
	LVITEM item = { 0, };
	Long index;
	PostCardBook *pcb;

	item.mask = LVIF_TEXT;
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		item.cchTextMax = 256;
		item.iSubItem = 1;
		item.pszText = address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.cchTextMax = 8;
		item.iSubItem = 2;
		item.pszText = zipcode;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ADDRESS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		sprintf(caption, "%s %s", zipcode, address);
		instance = FindWindow("#32770", "持扁");
		SendMessage(GetDlgItem(instance, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)caption);
		SendMessage(GetDlgItem(instance, IDC_EDIT_ADDRESS), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);
		SendMessage(GetDlgItem(instance, IDC_EDIT_ADDRESS), EM_SETSEL, (WPARAM)strlen(caption), (LPARAM)strlen(caption));
		pcb = (PostCardBook*)GetWindowLong(hWnd, GWL_USERDATA);
		PostCardBook_Destroy(pcb);
		EndDialog(hWnd, 0);
		//MessageBox(hWnd, (LPCTSTR)caption, (LPCTSTR)"林家", MB_OK | MB_ICONINFORMATION);
	}
	return FALSE;
}
