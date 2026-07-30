#include <jni.h>
#include "VRManager.hpp"

extern "C" {

JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_startVR(
    JNIEnv*,
    jobject
) {
    VRManager::get().startVR();
}

JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_pauseVR(
    JNIEnv*,
    jobject
) {
    VRManager::get().pause();
}

JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_resumeVR(
    JNIEnv*,
    jobject
) {
    VRManager::get().resume();
}

JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_stopVR(
    JNIEnv*,
    jobject
) {
    VRManager::get().stopVR();
}

JNIEXPORT void JNICALL
Java_com_customRobTop_JniToCpp_setScreenDistance(
    JNIEnv*,
    jobject,
    jfloat distance
) {
    VRManager::get().setScreenDistance(distance);
}

}