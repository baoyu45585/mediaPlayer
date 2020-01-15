//
//  musicplayer.h
//  MGGTVideoPlayer
//
//  Created by 廖健华 on 2019/8/29.
//

#ifndef musicplayer_h
#define musicplayer_h
#include <jni.h>

#ifdef __cplusplus
extern "C"
{
#endif


int music_player_set_javavm(JavaVM* JavaVM);
int music_player_play(char *path,bool loop);
int music_player_stop();
int music_player_pause();
int music_player_resume();
/**
 调整音量
 @param value 0.0 ～ 1.0  默认：1.0
 */
int music_player_set_value(float value);
#ifdef __cplusplus
}
#endif

#endif
