#include <jni.h>
#include <string>
#include "musicplayer.h"
JavaVM *g_JavaVM;
Musicplayer* musicplayer;
extern "C"
JNIEXPORT void JNICALL
Java_com_mg_media_mediaplayer_MediaJni_start(JNIEnv *env, jobject instance, jstring path_) {
    musicplayer=new Musicplayer();
    musicplayer->music_player_set_javavm(g_JavaVM);
    char* path="/storage/emulated/0/DCIM/cc.aac";
    musicplayer->music_player_play(path,0);
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