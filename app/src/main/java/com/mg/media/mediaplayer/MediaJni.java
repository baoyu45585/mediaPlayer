package com.mg.media.mediaplayer;

/**
 * @author shenjb@china
 * @since 2020-01-15
 */
public class MediaJni {
    static {
        System.loadLibrary("native-lib");
    }


    public native void start();

    public native void pasue();

    public native void stop();

    public native void resume();
}
