#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>
#include "resource.h"
int sw;
HBRUSH hBlueBrush, hYellowBrush;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;

int DrawGr(HDC hdc);
int APIENTRY _tWinMain(HINSTANCE This, //Дескриптор текущего приложения
	HINSTANCE Prev, //В современных системах всегда 0
	LPTSTR cmd, //Командная строка
	int mode) //Режим отображения окна

{
	HWND hWnd; //Дескриптор главного окна программы
	MSG msg; //Структура для хранения сообщения
	hInst = This;
	WNDCLASS wc;//Класс окна
	//Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; //Имя класса окна
	wc.lpfnWndProc = WndProc; //Имя класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.lpszMenuName = _T("menudemo");; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(64, 224, 208));//Закрашивание окна
	if (!RegisterClass(&wc)) return 0;//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(WinName,//Имя класса окна
		_T("Задание B12"),//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		100,//x
		100,//y Размеры окна
		500,//Width
		500,//Height
		HWND_DESKTOP,//Дескриптор родительской информации нет
		NULL,//Нет меню
		This,//Дескриптор приложения
		NULL);//Дополнительной информации нет
	ShowWindow(hWnd, mode);//Показать окно

	UpdateWindow(hWnd);
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);//Посылает сообщение функции WndProc()
	}
	return 0;
}
//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush;

	HPEN hPen;
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case MI_BLUE:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_hatch:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	case WM_CREATE:
		hBlueBrush = CreateSolidBrush(RGB(64, 224, 208));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (sw == 1) FillRect(hdc, &ps.rcPaint, hBlueBrush);
		if (sw == 2)
			{
				
				hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				SelectObject(hdc, hPen);  
				hBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 255, 255));
				SelectObject(hdc, hBrush);SetBkColor(hdc, RGB(64, 224, 208));
				Rectangle(hdc, 0, 0, 500, 500);
				DeleteObject(hPen);
				DeleteObject(hBrush);
			}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
