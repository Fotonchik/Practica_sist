#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>

HBRUSH hBlueBrush, hYellowBrush;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;
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
	wc.lpszMenuName = NULL; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(130, 200, 250));//Закрашивание окна
	if (!RegisterClass(&wc)) return 0;//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(WinName,//Имя класса окна
		_T("Задание А12"),//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y Размеры окна
		CW_USEDEFAULT,//Width
		CW_USEDEFAULT,//Height
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

	HPEN hPen;
	switch (message)
	{
	case WM_CREATE:
		hBlueBrush = CreateSolidBrush(RGB(130, 200, 250));
		hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); 
		SelectPen(hdc, hYellowBrush); 
		hPen = CreatePen(PS_SOLID, 1, RGB(130, 200, 250));
		SelectObject(hdc, hPen);
		Ellipse(hdc, 10, 10, 200, 200);
		SelectPen(hdc, hBlueBrush);
		Ellipse(hdc, 130, 40, 230, 130);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
