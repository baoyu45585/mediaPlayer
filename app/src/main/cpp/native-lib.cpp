#include <jni.h>
#include <string>
#include "musicplayer.h"
JavaVM *g_JavaVM;

extern "C"
JNIEXPORT void JNICALL
Java_com_mg_media_mediaplayer_MediaJni_start(JNIEnv *env, jobject instance) {

   music_player_set_javavm(g_JavaVM);
    char* path="/storage/emulated/0/DCIM/cc.aac";
   music_player_play(path,1);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mg_media_mediaplayer_MediaJni_pasue(JNIEnv *env, jobject instance) {
    music_player_pause();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mg_media_mediaplayer_MediaJni_stop(JNIEnv *env, jobject instance) {

    music_player_stop();

}



jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv *env;
    g_JavaVM = vm;
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
    {
        return -1;
    }
    return JNI_VERSION_1_4;

}

extern "C"
JNIEXPORT void JNICALL
Java_com_mg_media_mediaplayer_MediaJni_resume(JNIEnv *env, jobject instance) {
    music_player_resume();

}