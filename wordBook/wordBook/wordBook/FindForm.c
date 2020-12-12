#include <stdio.h>
#include "FindForm.h"
#include "wordBook.h"
#include "resource.h"
#include <stdlib.h>
#include <commctrl.h>
#include <string.h>
BOOL CALLBACK FindFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
		case WM_INITDIALOG:
			ret = FindForm_OnInitDialog(hWnd, wParam, lParam);
			break;
		
		case WM_CLOSE:
			ret = FindForm_OnClose(hWnd, wParam, lParam);
			break;

		default :
			ret = FALSE;
			break;
	}
	return ret;
}

BOOL FindForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return TRUE;
}
BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	Long(*indexes);
	EndDialog(hWnd, 0);
	return TRUE;
}