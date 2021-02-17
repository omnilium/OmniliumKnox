#include "private/pch.h"

#include "Knox.h"

#include "../version.h"

constexpr int WINDOW_WIDTH = 600;
constexpr int WINDOW_HEIGHT = 400;

knox::app::Knox::Knox() {
	HICON hIcon = LoadIcon(GetModuleHandle(nullptr), MAKEINTRESOURCE(APP_ICON));

    _rpApp = App::Create();

    _rpWindow = Window::Create(_rpApp->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
		false, kWindowFlags_Titled | kWindowFlags_Resizable);
	SendMessage(HWND(_rpWindow->native_handle()), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
	SendMessage(HWND(_rpWindow->native_handle()), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));

	_rpApp->set_window(*_rpWindow);

    _rpOverlay = Overlay::Create(*_rpWindow, 1, 1, 0, 0);
    _rpOverlay->Resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	_rpOverlay->view()->LoadURL("file:///app.html");

	_rpApp->set_listener(this);
	_rpWindow->set_listener(this);
	_rpOverlay->view()->set_load_listener(this);
	_rpOverlay->view()->set_view_listener(this);
}

knox::app::Knox::~Knox() = default;

void knox::app::Knox::Run() {
	_rpApp->Run();
}

void knox::app::Knox::OnUpdate() {
    // No update routines yet.
}

void knox::app::Knox::OnClose() {
    // No close routines yet.
}

void knox::app::Knox::OnResize(uint32_t width, uint32_t height) {
	_rpOverlay->Resize(width, height);
}

void knox::app::Knox::OnFinishLoading(ultralight::View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const String& url) {
    // No finish loading routines yet.
}

void knox::app::Knox::OnDOMReady(ultralight::View* caller,
	uint64_t frame_id,
	bool is_main_frame,
	const String& url) {
    // No DOM ready routines yet.
}

void knox::app::Knox::OnChangeCursor(ultralight::View* caller,
	Cursor cursor) {
	_rpWindow->SetCursor(cursor);
}

void knox::app::Knox::OnChangeTitle(ultralight::View* caller,
	const String& title) {
	_rpWindow->SetTitle(title.utf8().data());
}
