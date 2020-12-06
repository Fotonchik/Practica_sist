#include<Windows.h>
#include "7.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szAppName[] = "edit";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	WNDCLASSEX wndclass;
	MSG msg;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground =(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = "menudemo";
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	static HWND hwndEdit; 
	switch (uMsg) {
	case WM_CREATE:
		hwndEdit = CreateWindow("edit",NULL, WS_CHILD | WS_VISIBLE |
			WS_HSCROLL|WS_VSCROLL| WS_BORDER|ES_LEFT|ES_MULTILINE
		|ES_AUTOHSCROLL|ES_AUTOVSCROLL,0,0,0,0,hwnd,(HMENU)1,
			((LPCREATESTRUCT)lParam)-> hInstance,NULL );
		return 0;
		

	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		return 0;
	case WM_SIZE:
		MoveWindow(hwndEdit,0,0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;
	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			if (HIWORD(wParam) == EN_ERRSPACE ||
				HIWORD(wParam) == EN_MAXTEXT)
				MessageBox(hwnd, "Edit comtrol out of space.", szAppName, MB_OK | MB_ICONSTOP);
			return 0;
		}
		else switch (LOWORD(wParam))
		{
		case IDM_NEW:
		case IDM_SAVE:
		case IDM_SAVEAS:
			MessageBeep(0);
			return 0;

		case IDM_EXIT:
			SendMessage(hwndEdit, WM_CLOSE, 0, 0);

			return 0;
		case IDM_UNDO:
			SendMessage(hwndEdit, WM_UNDO, 0, 0);

			return 0;
		case IDM_CUT:
			SendMessage(hwndEdit, WM_CUT, 0, 0);

			return 0;

		case IDM_COPY:
			SendMessage(hwndEdit, WM_COPY, 0, 0);

			return 0;
		case IDM_PASTE:
			SendMessage(hwndEdit, WM_PASTE, 0, 0);
			return 0;

		case IDM_DEL:
			SendMessage(hwndEdit, WM_CLEAR, 0, 0);
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
