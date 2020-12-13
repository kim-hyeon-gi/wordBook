#pragma once
#ifndef _FINDFORM_H
#define _FINDFORM_H
#include <windows.h>
BOOL CALLBACK FindFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnSpellingRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnMeanRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindForm_OnListviewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);


#endif // _FINDFORM_H