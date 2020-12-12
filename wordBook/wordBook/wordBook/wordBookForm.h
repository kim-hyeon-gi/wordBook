#pragma once
#ifndef _WORDBOOKFORM_H
#define _WORDBOOKFORM_H
#include <windows.h>

BOOL CALLBACK WordBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL WordBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordBookForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif // _WORDBOOKFORM_H
