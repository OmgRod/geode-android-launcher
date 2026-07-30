#include <jni.h>
#include <android/log.h>
#include <android/native_window_jni.h>
#include <atomic>
#include <mutex>

#include "log.hpp"

namespace {

JavaVM*  s_vm            = nullptr;
jobject  s_activity      = nullptr;
std::mutex s_activityMtx;

}

extern "C" {

JNIEXPORT jobject JNICALL
geode_vr_getActivityContext(JNIEnv* env) {
    std::lock_guard<std::mutex> lock(s_activityMtx);
    if (!s_activity) return nullptr;
    return env->NewLocalRef(s_activity);
}

JNIEXPORT void JNICALL
geode_vr_releaseActivityContext(JNIEnv* env, jobject localRef) {
    if (localRef) env->DeleteLocalRef(localRef);
}

JNIEXPORT void JNICALL
Java_com_geode_launcher_GeometryDashVRBridge_nativeOnCreate(
        JNIEnv* env,
        jobject thiz,
        jobject surface)
{
    if (!s_vm) {
        env->GetJavaVM(&s_vm);
    }

    {
        std::lock_guard<std::mutex> lock(s_activityMtx);

        if (s_activity) {
            env->DeleteGlobalRef(s_activity);
            s_activity = nullptr;
        }

        s_activity = env->NewGlobalRef(thiz);
    }

    log::info("GeometryDashVRBridge: nativeOnCreate — Activity stored, surface={}",
              static_cast<void*>(surface));

    (void)surface;
}

JNIEXPORT void JNICALL
Java_com_geode_launcher_GeometryDashVRBridge_nativeOnResume(
        JNIEnv* /* env */,
        jobject /* thiz */)
{
    log::info("GeometryDashVRBridge: nativeOnResume");
}

JNIEXPORT void JNICALL
Java_com_geode_launcher_GeometryDashVRBridge_nativeOnPause(
        JNIEnv* /* env */,
        jobject /* thiz */)
{
    log::info("GeometryDashVRBridge: nativeOnPause");
}

JNIEXPORT void JNICALL
Java_com_geode_launcher_GeometryDashVRBridge_nativeOnDestroy(
        JNIEnv* env,
        jobject /* thiz */)
{
    log::info("GeometryDashVRBridge: nativeOnDestroy — releasing Activity reference");

    std::lock_guard<std::mutex> lock(s_activityMtx);
    if (s_activity) {
        env->DeleteGlobalRef(s_activity);
        s_activity = nullptr;
    }
}

} // extern "C"
