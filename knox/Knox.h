#pragma once

#include <AppCore/AppCore.h>

using namespace ultralight;

namespace knox::app {
    class Knox : public AppListener,
                 public WindowListener,
                 public LoadListener,
                 public ViewListener {
    public:
        Knox();

        ~Knox() override;

        // Start the run loop.
        virtual void Run();

        // This is called continuously from the app's main loop.
        void OnUpdate() override;

        // This is called when the window is closing.
        void OnClose() override;

        // This is called whenever the window resizes.
        void OnResize(uint32_t width, uint32_t height) override;

        // This is called when the page finishes a load in one of its frames.
        void OnFinishLoading(ultralight::View* caller,
                uint64_t frame_id,
                bool is_main_frame,
                const String& url) override;

        // This is called when the DOM has loaded in one of its frames.
        void OnDOMReady(ultralight::View* caller,
                uint64_t frame_id,
                bool is_main_frame,
                const String& url) override;

        // This is called when the page requests to change the Cursor.
        void OnChangeCursor(ultralight::View* caller,
                Cursor cursor) override;

        void OnChangeTitle(ultralight::View* caller,
                const String& title) override;

    private:
        RefPtr<App> _rpApp;
        RefPtr<Window> _rpWindow;
        RefPtr<Overlay> _rpOverlay;
    };
}