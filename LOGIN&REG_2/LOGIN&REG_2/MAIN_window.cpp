#include<Windows.h>
#include<tchar.h>
#include <dwmapi.h>
#include<iostream>
#include"loginProcess.h"

using namespace std;

PAINTSTRUCT ps;
int scw = GetSystemMetrics(SM_CXSCREEN);
int sch = GetSystemMetrics(SM_CYSCREEN);

int winh = 500, winw = 500;
int x = (scw - winw) / 2;
int y = (sch - winh) / 2;

int box_w_ = 300;
int box_h_ = 25;
int offset_y = 200;

BOOL isMax;
HWND hUsername, hPassword;
string filename = "DATA.txt";
vector<DATA1>d;
unordered_map<string, string> D;
DATA1 d1;
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg) {
	case WM_PAINT: {
		HDC hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_CREATE:
	{
		HWND tUseranme = CreateWindowEx(0, L"static", L"Username", WS_VISIBLE | WS_CHILD, scw / 2 - box_w_ / 2, sch / 2 - offset_y - 25, box_w_, 25,
			hwnd, nullptr, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

		HWND tPassword = CreateWindowEx(0, L"static", L"Password", WS_VISIBLE | WS_CHILD, scw / 2 - box_w_ / 2, sch / 2 - offset_y + 50, box_w_, 25,
			hwnd, nullptr, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

		hUsername = CreateWindowEx(0, L"Edit", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, scw / 2 - box_w_ / 2, sch / 2 - offset_y, box_w_, 25,
			hwnd, nullptr, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

		hPassword = CreateWindowEx(0, L"Edit", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER, scw / 2 - box_w_ / 2, sch / 2 - offset_y + 75, box_w_, 25,
			hwnd, nullptr, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

		HWND hReg = CreateWindowEx(0, L"Button", L"Register", WS_VISIBLE | WS_CHILD, scw / 2 - 100 / 2, sch / 2 - offset_y + 150, 100, 25,
			hwnd, (HMENU)1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), nullptr);
		SetWindowText(hUsername, L"Enter your username");
		return 0;
	}
	case WM_COMMAND: {
		string u, p;
		wchar_t buffer[256];
		HWND BREG = (HWND)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if (LOWORD(wParam) == 1) {
			
			if (GetWindowText(hUsername, buffer, 256)) {
				std::wstring ws(buffer);
				u = string(ws.begin(), ws.end());
			}
			if (GetWindowText(hPassword, buffer, 256)) {
				std::wstring ws(buffer);
				p = string(ws.begin(), ws.end());
			}
			if (u.empty() || p.empty()) {
				MessageBox(hwnd, L"Username or password cannot be empty.", L"Error", MB_OK | MB_ICONERROR);
				return 0;
			}
			

			d1.username = u;
			d1.password = p;
			D.emplace(u, p);
			d.push_back(d1);
			writeitfile(filename, d);
		}
	}

	case WM_CTLCOLORSTATIC: {
		HDC hstatic = (HDC)wParam;
		SetBkMode(hstatic, TRANSPARENT);
		return (LRESULT)GetStockObject(NULL_BRUSH);
	}

	case DWM_BB_TRANSITIONONMAXIMIZED: {
		isMax = *(BOOL*)lParam;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int _tmain(int argc, _TCHAR* argv[]) {
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.lpszClassName = L"MyWindowClass";
	wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);

	if (!RegisterClass(&wc)) {
		return 1;
	}
	MSG msg = {};
	HWND hwnd;
	if (isMax) {
		hwnd = CreateWindowExW(0, wc.lpszClassName, L"APP",
			WS_CHILDWINDOW, x, y, winw, winh, NULL, NULL, wc.hInstance, NULL);
	}
	else {
		hwnd = CreateWindowExW(0, wc.lpszClassName, L"APP",
			WS_OVERLAPPEDWINDOW, 0, 0, scw, sch, NULL, NULL, wc.hInstance, NULL);
	}
	if (hwnd == nullptr) {
		return 0;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return int(msg.wParam);
}