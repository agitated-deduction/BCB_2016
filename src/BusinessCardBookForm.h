#ifndef _BUSINESSCARDBOOKFORM_H_
#define _BUSINESCCARDBOOKFORM_H_
#include <windows.h>

BOOL CALLBACK BusinessCardBookProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnItDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnCommend(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnPutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnPullOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL BusinessCardBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);



#endif //_BUSINESSCARDBOOKFORM_H_