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
	count = 3;  //Load(wordBook);
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



	return TRUE;
}
