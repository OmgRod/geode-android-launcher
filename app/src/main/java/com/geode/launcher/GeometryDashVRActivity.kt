package com.geode.launcher

import android.content.pm.ActivityInfo
import android.os.Bundle
import android.util.Log
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.ViewGroup
import android.view.WindowManager
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat

class GeometryDashVRActivity : AppCompatActivity() {

    private var mSurfaceView: SurfaceView? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE

        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON)

        WindowCompat.setDecorFitsSystemWindows(window, false)
        window.addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN)

        hideSystemUi()

        val surface = createVrRenderSurface()
        mSurfaceView = surface
        setContentView(surface)

        surface.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceCreated(holder: SurfaceHolder) {
                Log.i(TAG, "Surface ready — calling nativeOnCreate")
                GeometryDashVRBridge.nativeOnCreate(holder.surface)
            }
            override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {}
            override fun surfaceDestroyed(holder: SurfaceHolder) {
                Log.i(TAG, "Surface destroyed")
            }
        })

        Log.i(TAG, "GeometryDashVRActivity created")
    }

    override fun onResume() {
        super.onResume()
        hideSystemUi()
        Log.d(TAG, "onResume")
        GeometryDashVRBridge.nativeOnResume()
    }

    override fun onPause() {
        Log.d(TAG, "onPause")
        GeometryDashVRBridge.nativeOnPause()
        super.onPause()
    }

    override fun onDestroy() {
        Log.d(TAG, "onDestroy")
        GeometryDashVRBridge.nativeOnDestroy()
        super.onDestroy()
    }

    override fun onWindowFocusChanged(hasFocus: Boolean) {
        super.onWindowFocusChanged(hasFocus)
        if (hasFocus) hideSystemUi()
    }

    private fun createVrRenderSurface(): SurfaceView {
        return SurfaceView(this).apply {
            layoutParams = ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT
            )
            setZOrderOnTop(false)
        }
    }

    private fun hideSystemUi() {
        WindowInsetsControllerCompat(window, window.decorView).apply {
            hide(WindowInsetsCompat.Type.systemBars())
            systemBarsBehavior =
                WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE
        }
    }

    companion object {
        private const val TAG = "GeodeLauncher/VR"
    }
}

object GeometryDashVRBridge {

    @JvmStatic
    fun nativeOnCreate(surface: android.view.Surface) {
        JniToCpp.vrActivityCreated(surface)
    }

    @JvmStatic
    fun nativeOnResume() {
        JniToCpp.vrActivityResumed()
    }

    @JvmStatic
    fun nativeOnPause() {
        JniToCpp.vrActivityPaused()
    }

    @JvmStatic
    fun nativeOnDestroy() {
        JniToCpp.vrActivityDestroyed()
    }
}
