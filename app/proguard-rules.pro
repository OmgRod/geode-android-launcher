# Add wildcard keep rules to all of the library code in use
-keep class org.fmod.** { *; }
-keep class org.cocos2dx.lib.** { *; }
-keep class com.customRobTop.** { *; }

-keepclassmembers class com.omgrod.gdvr.GeometryDashActivity {
    public void launchQuestVRMode();
}

-keepclassmembers class com.customRobTop.BaseRobTopActivity {
    public static java.lang.ref.WeakReference getMe();
}

# note: if you're going to add more rules, consider the @Keep annotation
# this should really only be kept to non-custom code
