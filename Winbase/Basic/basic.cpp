// Acts as a scratchpad to develop the WinAPI stuff
#include <Windows.h>
#include <tchar.h>

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Greetings to Windows.");

	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc,
			10, 10,
			greeting,
			_tcslen(greeting));
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow)
{
	static TCHAR szWndClassName[] = _T("basic_window");
	static TCHAR szTitle[] = _T("Basic Windows Application");

	// Define the window class and fill it with the basics.
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWndClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	// Register the window class now.
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, _T("Call to RegisterClassEx failure."), _T("Basic Windows Application"), NULL);
		return 1;
	}

	// With the window class registered with Windows, now we can use it to create an instance using that
	// class.
	HWND hwnd = CreateWindow(	szWndClassName,
								szTitle,
								WS_OVERLAPPEDWINDOW,
								CW_USEDEFAULT, CW_USEDEFAULT,
								500, 100,
								NULL,
								NULL,
								hInst,
								NULL);

	// With the window created, we can now show have it shown on the screen.
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Message pump.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Message pump has exited, return whatever we were left with from the quit message.
	return (int)msg.wParam;
}