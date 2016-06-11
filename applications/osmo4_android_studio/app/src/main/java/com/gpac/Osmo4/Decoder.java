package com.gpac.Osmo4;

import android.view.Surface;

/**
 * Created by abdul on 9/6/16.
 */
public class Decoder {

    private final String TAG = "VideoDecoder";
    private String path;

    private native void init(String path);
    public native boolean setPlaying(boolean isPlaying);
    public native boolean setSurface(Surface surface);
    public native void release();


    public void setDataSource(String path) {
        this.path = path;
    }

    public void start(){
        init(path);
    }

}
