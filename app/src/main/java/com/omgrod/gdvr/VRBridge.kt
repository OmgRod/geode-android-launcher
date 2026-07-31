package com.omgrod.gdvr

object VRBridge {
    init {
        System.loadLibrary("launcherfix")
    }

    external fun initVR(gdTextureId: Int)
    external fun setScreenDistance(distance: Float)
    external fun setVRActive(active: Boolean)
}
