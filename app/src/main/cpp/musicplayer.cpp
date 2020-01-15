//
//  musicplayer.c
//  MGGTVideoPlayer
//
//  Created by 廖健华 on 2019/8/29.
//


#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "musicplayer.h"

static bool loop_flag=true;
static char tmp_url[1024];
static float music_value=1.0;
typedef struct MUSIC_PLAY_INFO_T {
    int          cmd_type;
    char         url[1024];
    bool         loop_flag;
    float        value;
} MUSIC_PLAY_INFO;

Musicplayer::Musicplayer() {
    m_javaVM = NULL;
}

Musicplayer::~Musicplayer() {
    m_javaVM = NULL;
}

int Musicplayer::music_player_set_javavm(JavaVM* JavaVM)
{
     m_javaVM   = JavaVM;
    return 0;
}

MiguEnv Musicplayer::music_player_getenv()
{
    int status;
    MiguEnv ffenv;

    ffenv.bAttatedT = false;
    ffenv.env = NULL;

    status = m_javaVM->GetEnv((void **) &(ffenv.env), JNI_VERSION_1_4);

    if(status < 0)
    {
        status = (m_javaVM)->AttachCurrentThread(&(ffenv.env), NULL);

        if(status < 0)
            ffenv.env = NULL;

        ffenv.bAttatedT = true;
    }

    return ffenv;
}
bool Musicplayer::music_player_detachenv(MiguEnv ffenv)
{
    if(ffenv.bAttatedT)
    {
        (m_javaVM)->DetachCurrentThread();
        return true;
    }

    return false;
}

int Musicplayer::music_inface(char* path,int type, float wp, float lp) {
    MiguEnv local_env = music_player_getenv();
    JNIEnv * env = local_env.env;

    jclass findClass = (env)->FindClass("com/mg/media/mediaplayer/MiGuMusicPlayerTool");
    if(findClass == NULL){
        //LOGE("find ClassMethod class is null");
        return 0;
    }
    jmethodID midStatidMethod = (env)->GetStaticMethodID(findClass, "musicPlayer", "(Ljava/lang/String;IFF)V");
    if(midStatidMethod == NULL){
       // LOGE("cannt find callStaticMethod!");
        return 0;
    }

    //调用 findClass 类里面的静态方法
    jstring paramStr = (env)->NewStringUTF(path);
    (env)->CallStaticVoidMethod(findClass,midStatidMethod,paramStr,type,wp,lp);

    //删除引用
    (env)->DeleteLocalRef(findClass);
    (env)->DeleteLocalRef(paramStr);
    music_player_detachenv(local_env);

    return 0;
}

int Musicplayer::music_player_play(char *path,bool loop)
{
    int ret=0;
    float wp=1.0;
    float lp=0.0;

    MUSIC_PLAY_INFO musicInfo;
    if(!access(path,0))
    {
        musicInfo.cmd_type=1;
        strcpy(musicInfo.url,path);
        strcpy(tmp_url,path);
        musicInfo.loop_flag=loop;
        musicInfo.value=music_value;
        if(!musicInfo.loop_flag)
        {
            wp=0.0;
        }
        music_inface(musicInfo.url,1,wp,lp);
    }
    else
    {
        ret=-1;
    }
    return ret;
}

int Musicplayer::music_player_stop()
{
    int ret=0;

    music_inface(NULL,4,0.0,0.0);
    return ret;
}


int Musicplayer::music_player_pause()
{
    int ret=0;

    music_inface(NULL,2,0.0,0.0);
    return ret;
}

int Musicplayer::music_player_resume()
{
    int ret=0;

    music_inface(NULL,3,0.0,0.0);
    return ret;
}

int Musicplayer::music_player_set_value(float value)
{
    int ret=0;

    music_inface(NULL,5,value,value);
    return ret;
}






