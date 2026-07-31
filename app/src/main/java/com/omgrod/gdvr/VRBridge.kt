package com.omgrod.gdvr

import android.view.Surface

/**
 * Bridge for communicating between the Kotlin VR environment
 * and the C++ Geode/Cocos2d-x engine.
 */
object VRBridge {
    // Name of the compiled Geode mod library
    private const val LIBRARY_NAME = "geode_vr_bridge"

    init {
        try {
            System.loadLibrary(LIBRARY_NAME)
        } catch (e: UnsatisfiedLinkError) {
            // Log error in a production implementation
        }
    }

    /**
     * Passes a [Surface] to the native Geode environment
     * for engine rendering redirection.
     */
    external fun setSurfaceNative(surface: Surface)
}
