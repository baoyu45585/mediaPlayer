package com.mg.media.mediaplayer;

import android.media.AudioManager;
import android.media.MediaPlayer;





public class MiGuMusicPlayerTool {

    private static MediaPlayer myplayer;
    public final static int MIGU_MUSIC_PLAYER_START = 1;
    public final static int MIGU_MUSIC_PLAYER_PAUSE = 2;
    public final static int MIGU_MUSIC_PLAYER_RESUME = 3;
    public final static int MIGU_MUSIC_PLAYER_STOP = 4;
    public final static int MIGU_MUSIC_PLAYER_SET_VALUE = 5;


    public static synchronized void  musicPlayer(String path,int type, float wp, float lp) {


        switch (type) {
            case MIGU_MUSIC_PLAYER_START:
                if (myplayer!=null){
                    myplayer.stop();
                    myplayer = null;
                }
                myplayer = new MediaPlayer();
                myplayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
                if (wp == 1.0f) {
                    myplayer.setLooping(true);
                } else {
                    myplayer.setLooping(false);
                }
                try {
                    myplayer.setDataSource(path);
                    myplayer.prepare();
                    myplayer.start();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                break;

            case MIGU_MUSIC_PLAYER_PAUSE:
                if (myplayer != null && myplayer.isPlaying())
                    myplayer.pause();
                break;

            case MIGU_MUSIC_PLAYER_RESUME:
                if (myplayer != null &&!myplayer.isPlaying())
                    myplayer.start();
                break;

            case MIGU_MUSIC_PLAYER_STOP:
                if (myplayer != null) {
                    myplayer.stop();
                    myplayer = null;
                }

                break;

            case MIGU_MUSIC_PLAYER_SET_VALUE:
                if (myplayer != null)
                    myplayer.setVolume(wp, wp);
                break;

            default:
                break;
        }
    }
}