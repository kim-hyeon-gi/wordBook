#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "WordBookForm.h"
#include <stdlib.h>
#include <commctrl.h>
#include "wordBook.h"
#include "resource.h"
#include <winuser.h>
#include <winbase.h>
#include "FindForm.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpzCmdLine, int nCmdShow) {
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_WORDBOOKFORM), NULL, WordBookFormProc);
	return response;
}
BOOL CALLBACK WordBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG:
		ret = WordBookForm_OnInitDialog(hWnd, wParam, lParam);
		break;

	case WM_COMMAND:
		ret = WordBookForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = WordBookForm_OnClose(hWnd, wParam, lParam);
		break;
	default: ret = FALSE;
		break;


	}
	return ret;

}
BOOL WordBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR type[][8] = { "명사","대명사","동사","형용사","부사","전치사","접속사","감탄사" };
	WordBook* wordBook;
	Long count;
	LVITEM item = { 0, };
	LVCOLUMN column = { 0, };
	Long index = 0;
	TCHAR number[64];
	wordBook = (WordBook(*))malloc(sizeof(WordBook));
	Create(wordBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)wordBook);
	count = Load(wordBook);
	column.mask = LVCF_TEXT | LVCF_WIDTH;
	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "철자";
	SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "품사";
	SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "뜻";
	SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 200;
	column.pszText = "예시";
	SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	item.mask = LVIF_TEXT;
	while (index < count) {
		item.iItem = index;
		sprintf(number, "%d", index + 1);
		item.iSubItem = 0; item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
		item.iSubItem = 1; item.pszText = wordBook->words[index].spelling;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2; item.pszText = wordBook->words[index].wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3; item.pszText = wordBook->words[index].mean;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4; item.pszText = wordBook->words[index].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		index++;
	}

	index = 0;
	while (index < sizeof(type) / sizeof(type[0])) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), CB_ADDSTRING, (WPARAM)0, (LPARAM)type[index]);
		index++;
	}
	return TRUE;
}

BOOL WordBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	wordBook = (WordBook(*))GetWindowLong(hWnd, GWL_USERDATA);
	Save(wordBook);
	if (wordBook != NULL) {
		Destroy(wordBook);
	}
	EndDialog(hWnd, 0);
	return TRUE;
}
BOOL WordBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
		case IDC_BUTTON_RECORD:
			ret = WordBookForm_OnRecordButtonClicked(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_FIND:
			ret = WordBookForm_OnFindButtonClicked(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_CORRECT:
			ret = WordBookForm_OnCorrectButtonClicked(hWnd, wParam, lParam);
			break;
		case IDC_BUTTON_ERASE:
			ret = WordBookForm_OnEraseButtonClicked(hWnd, wParam, lParam);
			break;

		default :
			ret = FALSE;
			break;
	}
	return ret;
}
BOOL WordBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (((NMHDR*)lParam)->idFrom) {
		case IDC_LIST:
			ret = WordBookForm_OnListButtonClicked(hWnd, wParam, lParam);
			break;
		default:
			ret = FALSE;
			break;
	}
}
BOOL WordBookForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR spelling[64]; WordBook* wordBook; TCHAR number[64];
	TCHAR wordClass[16]; Long index;
	TCHAR mean[16]; LVITEM item = { 0, };
	TCHAR example[256];
	if (HIWORD(wParam) == BN_CLICKED) {
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM) spelling);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)16, (LPARAM) wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN), WM_GETTEXT, (WPARAM)16, (LPARAM) mean);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)256, (LPARAM) example);

		wordBook = (WordBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(wordBook, spelling, wordClass, mean, example);

		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 0;
		sprintf(number, "%d", index + 1); item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = wordBook->words[index].spelling;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM) index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = wordBook->words[index].wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = wordBook->words[index].mean;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = wordBook->words[index].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

	}
	return TRUE;
}
BOOL WordBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG_FINDFORM), NULL, FindFormProc);
	}
	return TRUE;
}
BOOL WordBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVITEM item = { 0, };
	WordBook* wordBook;
	Long index;
	TCHAR wordClass[16];
	TCHAR mean[16];
	TCHAR example[256];
	if (HIWORD(wParam) == BN_CLICKED) {
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)16, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEAN), WM_GETTEXT, (WPARAM)16, (LPARAM)mean);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)256, (LPARAM)example);
		
		wordBook = (WordBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(wordBook, index, wordClass, mean, example);
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 2;
		item.pszText = wordBook->words[index].wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = wordBook->words[index].mean;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = wordBook->words[index].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

BOOL WordBookForm_OnListViewDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return TRUE;
}

BOOL WordBookForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	LVITEM item = { 0, };
	Long index;
	TCHAR number[64];
	if (HIWORD(wParam) == BN_CLICKED) {
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		wordBook = (WordBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		//Erase(wordBook, index);
		SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);
		item.mask = LVIF_TEXT;
		item.iSubItem = 0;
		while (index < wordBook->length) {
			item.iItem = index;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return TRUE;
}
BOOL WordBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return TRUE;
}
BOOL WordBookForm_OnListButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	return TRUE;
}