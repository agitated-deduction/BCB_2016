#ifndef _PUTFORM_H_
#define _PUTFORM_H_
#include <Windows.h>

BOOL CALLBACK PutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL PutForm_OnItDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PutForm_OnCommend(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PutForm_OnPutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PutForm_OnCompanyNameKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PutForm_OnPostButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif