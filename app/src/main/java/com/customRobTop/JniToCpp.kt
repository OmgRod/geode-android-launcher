package com.customRobTop

@Suppress("unused", "KotlinJniMissingFunction")
object JniToCpp {
    init {
        System.loadLibrary("launcherfix")
    }
    
    @JvmStatic
    external fun didCacheInterstitial(str: String?)

    @JvmStatic
    external fun didClickInterstitial()

    @JvmStatic
    external fun didCloseInterstitial()

    @JvmStatic
    external fun didDismissInterstitial()

    @JvmStatic
    external fun everyplayRecordingStopped()

    @JvmStatic
    external fun googlePlaySignedIn()

    @JvmStatic
    external fun hideLoadingCircle()

    @JvmStatic
    external fun itemPurchased(str: String)

    @JvmStatic
    external fun itemRefunded(str: String)

    @JvmStatic
    external fun promoImageDownloaded()

    @JvmStatic
    external fun resumeSound()

    @JvmStatic
    external fun rewardedVideoAdFinished(i: Int)

    @JvmStatic
    external fun rewardedVideoAdHidden()

    @JvmStatic
    external fun setupHSSAssets(str: String?, str2: String?)

    @JvmStatic
    external fun showInterstitialFailed()

    @JvmStatic
    external fun userDidAttemptToRateApp()

    @JvmStatic
    external fun videoAdHidden()

    @JvmStatic
    external fun videoAdShowed()

    @JvmStatic
    external fun vrActivityCreated(surface: android.view.Surface)

    @JvmStatic
    external fun vrActivityResumed()

    @JvmStatic
    external fun vrActivityPaused()

    @JvmStatic
    external fun vrActivityDestroyed()

    @JvmStatic
    external fun startVR()

    @JvmStatic
    external fun pauseVR()

    @JvmStatic
    external fun resumeVR()

    @JvmStatic
    external fun stopVR()

    @JvmStatic
    external fun setScreenDistance(distance: Float)
}
