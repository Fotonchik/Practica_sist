#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include"resource.h"
#include <algorithm>    // подключаем sort
#include <vector> 

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static int  scrlv, cIndex;
int* val[] = { &scrlv,  &cIndex };
const int VNUM = 100;
const int Combo_size = 100;
int combo[100];
INT_PTR CALLBACK Dialog1(HWND, UINT, WPARAM, LPARAM);
TCHAR szAppName[] = _T("BigDialog");
HINSTANCE hInst;
HWND hCB;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG lpMsg;
	hInst = hInstance;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(152, 251, 152));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return 0;
	hWnd = CreateWindow(szAppName, _T("Task 3"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessageW(&lpMsg);
	}
	return (int)lpMsg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	static HBRUSH hBrush, hBrushStatic;
	static int cyChar;
	static TCHAR szbuffer[10];

	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Диалог");
	TCHAR str1[] = _T("Открыть");
	switch (msg)
	{
	case WM_CREATE:
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, ID_STDDIALOG, str1);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hwnd, hMenu);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_STDDIALOG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, Dialog1);
			break;
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush, hBrushStatic;

	static int scrlv;
	static HWND  vScroll, hWndList, hWndComboBox;
	int i;

	for ( i = 0; i < Combo_size; i++)
	{
		combo[i] = rand() %100;
	}; 
	std::vector<int> combo(combo, combo + 100);
	sort(combo.begin(), combo.end()); 

	char p[100];

	switch (msg)
	{

	case WM_CTLCOLORSTATIC:
		SetBkColor((HDC)wParam, (RGB(1, 120, 40)));

		return (LRESULT)hBrushStatic;
		break;
	case WM_CTLCOLORDLG:

		hBrushStatic = CreateSolidBrush(RGB(152, 251, 152));

		SetBkColor((HDC)wParam, GetSysColor(RGB(152, 251, 152)));
		return (LRESULT)hBrushStatic;
		break;
	case WM_SYSCOLORCHANGE:
		DeleteObject(hBrushStatic);
		break;
	case WM_INITDIALOG:
		scrlv = ::scrlv;
		SetDlgItemInt(hDlg, IDC_VSCR, scrlv, 0);
		vScroll = GetDlgItem(hDlg, IDC_SCROLLBAR2);
		SetScrollRange(vScroll, SB_CTL, 0, VNUM, FALSE);
		SetScrollPos(vScroll, SB_CTL, scrlv, TRUE);
		hWndComboBox = GetDlgItem(hDlg, IDC_COMBO1);

		for ( i = 1; i < Combo_size; i++)
		{
			
			SendMessage(hWndComboBox, CB_ADDSTRING,  0,
				(LPARAM)_itot(combo[i], (wchar_t*)p, 10));
		}
		SendMessage(hWndComboBox, CB_SETCURSEL, cIndex, 0L);
		return TRUE;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOC:
			cIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
			
			::scrlv = scrlv;
			InvalidateRect(GetParent(hDlg), NULL, TRUE);
		case IDCANCEL:
			return EndDialog(hDlg, 0);
		}
		return TRUE;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			scrlv--;
			break;
		case SB_LINEDOWN:
			scrlv++;
			break;
		case SB_PAGEUP:
			scrlv -= VNUM / 10;
			break;
		case SB_PAGEDOWN:
			scrlv += VNUM / 10;
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			scrlv = HIWORD(wParam);
			break;
		}
		scrlv = max(0, min(scrlv, VNUM));
		if (scrlv != GetScrollPos(vScroll, SB_CTL)) {
			SetScrollPos(vScroll, SB_CTL, scrlv, TRUE);
			SetDlgItemInt(hDlg, IDC_VSCR, scrlv, 0);
		}
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}