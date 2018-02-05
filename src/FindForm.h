#ifndef _FINDFORM_H_
#define _FINDFORM_H_
#include <Windows.h>
BOOL CALLBACK FindFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnItDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnCommend(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnChooseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);



#endif