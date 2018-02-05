#ifndef _POSTCARDFORM_H_
#define _POSTCARDFORM_H_
#include <Windows.h>
BOOL CALLBACK PostBookProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL PostBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PostBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PostBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PostBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PostBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL PostBookForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#endif//_POSTCARDFORM_H