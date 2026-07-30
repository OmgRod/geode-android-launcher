#include "HookManager.hpp"
#include <sys/mman.h>
#include <unistd.h>
#include "log.hpp"
#include "../patcher.hpp"
#include "vr/VRManager.hpp"
#include <dlfcn.h>

static void* original_swapBuffers = nullptr;

void hooked_swapBuffers(void* self) {
    if (VRManager::get().isEnabled()) {
        VRManager::get().update();
    }

    auto original = reinterpret_cast<void (*)(void*)>(original_swapBuffers);
    original(self);
}

void HookManager::init() {
    log::info("HookManager: Initializing...");
    
    void* handle = dlopen("libcocos2dcpp.so", RTLD_LAZY);
    if (!handle) {
        log::error("HookManager: Failed to open libcocos2dcpp.so");
        return;
    }

    original_swapBuffers = dlsym(handle, "_ZN7cocos2d8CCEGLView11swapBuffersEv");
    if (!original_swapBuffers) {
        log::error("HookManager: Failed to find CCEGLView::swapBuffers");
        dlclose(handle);
        return;
    }

    log::info("HookManager: Found swapBuffers at {}", original_swapBuffers);
}
