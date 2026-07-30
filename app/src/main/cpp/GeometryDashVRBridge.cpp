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

JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_vrActivityCreated(
        JNIEnv* env,
        jclass,
        jobject surface)
{
    log::info("VR Activity created");

    if (!s_vm) {
        env->GetJavaVM(&s_vm);
    }

    ANativeWindow* window = ANativeWindow_fromSurface(env, surface);

    VRManager::get().setSurface(window);
    VRManager::get().startVR();
}


JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_vrActivityResumed(
        JNIEnv*,
        jclass)
{
    log::info("VR Activity resumed");

    VRManager::get().resume();
}


JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_vrActivityPaused(
        JNIEnv*,
        jclass)
{
    log::info("VR Activity paused");

    VRManager::get().pause();
}


JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_JniToCpp_vrActivityDestroyed(
        JNIEnv* env,
        jclass)
{
    log::info("VR Activity destroyed");

    VRManager::get().stopVR();

    if (s_activity) {
        env->DeleteGlobalRef(s_activity);
        s_activity = nullptr;
    }
}

}
