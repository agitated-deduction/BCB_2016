#ifndef _PULLOUTFORM_H
#define _PULLOUTFORM_H
#include<Windows.h>

BOOL CALLBACK PullOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL PullOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PullOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

#endif