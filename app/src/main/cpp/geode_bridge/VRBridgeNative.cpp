#include <Geode/Geode.hpp>
#include <jni.h>
#include <android/native_window_jni.h>

using namespace geode::prelude;

extern "C" {
    // JNI Function mapped to com.omgrod.gdvr.VRBridge.setSurfaceNative
    JNIEXPORT void JNICALL
    Java_com_omgrod_gdvr_VRBridge_setSurfaceNative(JNIEnv* env, jobject thiz, jobject surface) {
        // 1. Convert Java Surface to ANativeWindow
        ANativeWindow* window = ANativeWindow_fromSurface(env, surface);
        if (!window) {
            log::error("Failed to get ANativeWindow from Surface");
            return;
        }

        // 2. Schedule the window redirection on the main Cocos thread
        Loader::get()->queueInMainThread([window]() {
            auto director = cocos2d::Director::getInstance();
            auto glView = director->getOpenGLView();
            
            if (glView) {
                // Force the engine to use the new window
                glView->setWindow(window);
                log::info("Successfully redirected Cocos2d-x render target!");
            } else {
                log::error("Failed to get OpenGLView");
                ANativeWindow_release(window);
            }
        });
    }
}
