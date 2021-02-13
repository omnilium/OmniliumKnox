#include "Knox.h"

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400

Knox::Knox() {
  app_ = App::Create();

  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
    false, kWindowFlags_Titled | kWindowFlags_Resizable);
  app_->set_window(*window_.get());

  overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);
  OnResize(window_->width(), window_->height());
  overlay_->view()->LoadURL("file:///app.html");

  app_->set_listener(this);
  window_->set_listener(this);
  overlay_->view()->set_load_listener(this);
  overlay_->view()->set_view_listener(this);
}

Knox::~Knox() {
}

void Knox::Run() {
  app_->Run();
}

void Knox::OnUpdate() {

}

void Knox::OnClose() {
}

void Knox::OnResize(uint32_t width, uint32_t height) {
  overlay_->Resize(width, height);
  inspectorOverlay_->Resize(width, height);
}

void Knox::OnFinishLoading(ultralight::View* caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String& url) {
}

void Knox::OnDOMReady(ultralight::View* caller,
                       uint64_t frame_id,
                       bool is_main_frame,
                       const String& url) {
}

void Knox::OnChangeCursor(ultralight::View* caller,
                           Cursor cursor) {
  window_->SetCursor(cursor);
}

void Knox::OnChangeTitle(ultralight::View* caller,
                          const String& title) {
  window_->SetTitle(title.utf8().data());
}
