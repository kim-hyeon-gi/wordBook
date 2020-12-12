#pragma once
#ifndef _FINDFORM_H
#define _FINDFORM_H
#include <windows.h>
BOOL CALLBACK FindFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);


#endif // _FINDFORM_H