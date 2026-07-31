package org.cocos2dx.lib

import android.app.Activity
import android.content.Context
import com.customRobTop.BaseRobTopActivity

open class Cocos2dxActivity : Activity() {
    companion object {
        private var sContext: Context? = null

        @JvmStatic
        fun getContext(): Context? {
            return sContext ?: BaseRobTopActivity.getMe()?.get()
        }

        @JvmStatic
        fun setContext(context: Context) {
            sContext = context
        }

        @JvmStatic
        fun openURL(url: String) {
            BaseRobTopActivity.openURL(url)
        }
    }
}