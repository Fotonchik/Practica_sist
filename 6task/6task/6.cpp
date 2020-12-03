#include<Windows.h>
#include"6.h"

static int lIndex ;
int* val[] = { &lIndex };
HINSTANCE hInstance;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szAppName[] = "6";
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
	wndclass.lpszMenuName = NULL;
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
char szBuff[255];
WPARAM index = 0;
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HWND  hWndList, hConnectButton, hwndEdit;
	int num;
	switch (uMsg) {
	case WM_CREATE:
		hwndEdit = CreateWindow("edit",NULL, WS_CHILD | WS_VISIBLE | WS_BORDER|ES_LEFT
		,0,0,0,0,hwnd,(HMENU)1,
			((LPCREATESTRUCT)lParam)-> hInstance,NULL );
		
		hWndList = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY| WS_VSCROLL | WS_BORDER,
			0, 40, 500, 150, hwnd, (HMENU)IDC_LIST1, hInstance, NULL);

		hConnectButton = CreateWindow("BUTTON", "Добавить ", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 200, 90, 20, hwnd,
			(HMENU)ID_BUTTON, hInstance, NULL);

		SendMessage(hWndList, LB_SETCURSEL, lIndex, 0);
		return 0;
	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		return 0;
	case WM_SIZE:
		MoveWindow(hwndEdit,0,0, 500, 30, TRUE);
		return 0;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case ID_BUTTON: {
			num = SendMessage(hwndEdit, LB_GETCURSEL, 0, 0);
			if (num < 0) {
				MessageBox(hwnd, "Ошибка!", "Сообщение", MB_OK);
				return 0;
			}
			if (num > -1) 
			{
				MessageBox(hwnd, "Кнопка нажата!", "Сообщение", MB_OK);

				SendMessage(hwndEdit, LB_GETTEXT, num, (LPARAM)szBuff);

				char str[80] = { (char)sizeof(str), 0 };  
				int len = (int)::SendMessage(hwndEdit, EM_GETLINE, 0, (LPARAM)str);
				str[len] = '\0';  
 
				::SendDlgItemMessage(hwnd, IDC_LIST1, LB_INSERTSTRING, 0, (LPARAM)(LPCSTR)str);

				SetWindowText(hwndEdit, szBuff);

				SendMessage(hwndEdit, LB_DELETESTRING, num, 0); 
				return 0;
			}
			default: return 0;
		}
		}
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
