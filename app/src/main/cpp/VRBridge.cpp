#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "log.hpp"
#include <mutex>

class NativeVRRenderer {
public:
    static NativeVRRenderer& get() {
        static NativeVRRenderer instance;
        return instance;
    }

    void initSurface(JNIEnv* env, jobject surface) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_window) {
            ANativeWindow_release(m_window);
        }
        m_window = ANativeWindow_fromSurface(env, surface);
        log::info("NativeVRRenderer: Surface initialized: %p", m_window);
    }

    void init(int textureId) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_gdTextureId = textureId;
        log::info("NativeVRRenderer: Initialized with Texture ID: %d", textureId);
    }

    void setDistance(float distance) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_screenDistance = distance;
        log::info("NativeVRRenderer: Distance set to: %f", distance);
    }

    void setActive(bool active) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_active = active;
        log::info("NativeVRRenderer: Active set to: %s", active ? "true" : "false");
    }

private:
    std::mutex m_mutex;
    ANativeWindow* m_window = nullptr;
    int m_gdTextureId = 0;
    float m_screenDistance = -2.0f;
    bool m_active = false;
};

extern "C" {

JNIEXPORT void JNICALL
Java_com_geode_launcher_GeometryDashActivity_00024GeometryDashVRBridge_nativeOnCreate(
    JNIEnv* env,
    jobject obj,
    jobject surface
) {
    NativeVRRenderer::get().initSurface(env, surface);
}

JNIEXPORT void JNICALL
Java_com_geode_launcher_VRBridge_initVR(
    JNIEnv* env,
    jobject obj,
    jint gdTextureId
) {
    NativeVRRenderer::get().init(gdTextureId);
}

JNIEXPORT void JNICALL
Java_com_geode_launcher_VRBridge_setScreenDistance(
    JNIEnv* env,
    jobject obj,
    jfloat distance
) {
    NativeVRRenderer::get().setDistance(distance);
}

JNIEXPORT void JNICALL
Java_com_geode_launcher_VRBridge_setVRActive(
    JNIEnv* env,
    jobject obj,
    jboolean active
) {
    NativeVRRenderer::get().setActive(active);
}

}
