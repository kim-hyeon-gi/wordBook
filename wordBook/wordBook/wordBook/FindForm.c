#pragma warning(disable:4996)
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
		case WM_COMMAND:
			ret = FindForm_OnCommand(hWnd, wParam, lParam);
			break;
		case WM_CLOSE:
			ret = FindForm_OnClose(hWnd, wParam, lParam);
			break;
		case WM_NOTIFY:
			ret = FindForm_OnNotify(hWnd, wParam, lParam);
			break;

		default :
			ret = FALSE;
			break;
	}
	return ret;
}

BOOL FindForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN column = { 0, };
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "철자";
	SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "품사";
	SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "뜻";
	SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "예시";
	SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);
	
	SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0 ,(LPARAM) LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;
}
BOOL FindForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long(*indexes);
	indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	EndDialog(hWnd, 0);
	return TRUE;
}

BOOL FindForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
		case IDC_BUTTON_FIND:
			ret = FindForm_OnFindButtonClicked(hWnd, wParam, lParam);
			break;
		case ID_RADIO_SPELLING:
			ret = FindForm_OnSpellingRadioButtonClicked(hWnd, wParam, lParam);
			break;
		case ID_RADIO_MEAN:
			ret = FindForm_OnMeanRadioButtonClicked(hWnd, wParam, lParam);
			break;
		default :
			ret = FALSE;
			break;
	}
	return ret;
}
BOOL FindForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long(*indexes) = NULL; 
	Long index = 0;
	TCHAR spelling[64];
	TCHAR mean[16];
	Long count = 0;
	HWND wordBookFormHwnd;
	WordBook* wordBook = NULL;
	LVITEM item = { 0, };
	TCHAR number[64];
	if (HIWORD(wParam) == BN_CLICKED) {
		if (SendMessage(GetDlgItem(hWnd, ID_RADIO_SPELLING), BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_CHECKED) {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING2), WM_GETTEXT, (WPARAM)64, (LPARAM)spelling);
			wordBookFormHwnd = FindWindow("#32770", "단어장");
			wordBook = (WordBook(*))GetWindowLong(wordBookFormHwnd, GWL_USERDATA);
			if (indexes != NULL) {
				free(indexes);
			}
			FindSpelling(wordBook, spelling, &indexes, &count);
		}
		else if (SendMessage(GetDlgItem(hWnd, ID_RADIO_MEAN), BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_CHECKED) {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN2), WM_GETTEXT, (WPARAM)64, (LPARAM)mean);
			wordBookFormHwnd = FindWindow("#32770", "단어장");
			wordBook = (WordBook(*))GetWindowLong(wordBookFormHwnd, GWL_USERDATA);
			if (indexes != NULL) {
				free(indexes);
			}
			FindMean(wordBook, mean, &indexes, &count);
		}
		SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);
		if (count > 0) {
			item.mask = LVIF_TEXT;
			while (index < count) {
				item.iItem = index;
				item.iSubItem = 0;
				sprintf(number, "%d", index + 1);
				item.pszText = number;
				SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_INSERTITEM, (WPARAM)index, (LPARAM)&item);
				item.iSubItem = 1;
				item.pszText = wordBook->words[index].spelling;
				SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
				item.iSubItem = 2;
				item.pszText = wordBook->words[index].mean;
				SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
				item.iSubItem = 3;
				item.pszText = wordBook->words[index].spelling;
				SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
				item.iSubItem = 4;
				item.pszText = wordBook->words[index].wordClass;
				SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
				index++;
			}
			SetWindowLong(hWnd, GWL_USERDATA, (Long)indexes);
		}
	}
	return TRUE;
}
BOOL FindForm_OnSpellingRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING2), WM_ENABLE, (WPARAM)TRUE, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN2), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN2), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
	}
	return TRUE;
}
BOOL FindForm_OnMeanRadioButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN2), WM_ENABLE, (WPARAM)TRUE, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING2), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING2), WM_ENABLE, (WPARAM)FALSE, (LPARAM)0);
	}
	return TRUE;
}
BOOL FindForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (((NMHDR*)lParam)->idFrom) {
		case IDC_LIST1:
			ret = FindForm_OnListviewItemDoubleClicked(hWnd, wParam, lParam);
			break;
		default:
			ret = FALSE;
			break;
	}
	return TRUE;
}
BOOL FindForm_OnListviewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	HWND wordBookHwnd;
	TCHAR spelling[64];
	TCHAR wordClass[16];
	TCHAR mean[16];
	TCHAR example[256];
	Long(*indexes);
	LVITEM item = { 0, };
	if (((NMHDR*)lParam)->code == NM_DBLCLK) {
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 1;
		item.pszText = spelling;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = mean;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = example;
		item.cchTextMax = 256;
		SendMessage(GetDlgItem(hWnd, IDC_LIST1), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		wordBookHwnd = FindWindow("#32770", "단어장");
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(wordBookHwnd, IDC_LIST), LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM) indexes[index]);

		SendMessage(GetDlgItem(wordBookHwnd, IDC_EDIT_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)spelling);
		SendMessage(GetDlgItem(wordBookHwnd, IDC_COMBO_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordClass);
		SendMessage(GetDlgItem(wordBookHwnd, IDC_EDIT_MEAN), WM_SETTEXT, (WPARAM)0, (LPARAM)mean);
		SendMessage(GetDlgItem(wordBookHwnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)example);
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}