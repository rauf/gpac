#include <jni.h>
#include <string.h>

#include "com_gpac_Osmo4_Decoder.h"

#include "media/NdkMediaCodec.h"
#include "media/NdkMediaExtractor.h"


// for native window JNI
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#ifndef _Included_com_gpac_Osmo4_Decoder
#define _Included_com_gpac_Osmo4_Decoder
#ifdef __cplusplus


#include<android/log.h>

#define TAG "Native Decoder"
#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, TAG,  __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, TAG,  __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__)



    ANativeWindow *window;
    AMediaCodec *codec;
    AMediaExtractor *extractor;
    bool isPlaying;


    //select track using MediaExtractor
    size_t selectTrack() {
        size_t trackCount = AMediaExtractor_getTrackCount(extractor);

        LOGV("Total num. of tracks: %d", trackCount);
        for (size_t i = 0; i < trackCount; ++i) {
            AMediaFormat *format = AMediaExtractor_getTrackFormat(extractor, i);

            char *mime;

            Bool b = AMediaFormat_getString(format, AMediaFormat_KEY_MIME, &mime);

            if(!b) {
                LOGE("No mime type")
                return;
            }
            else LOGI("Track num.: %d, mime type: %s ", i, mime);

            if (!strncmp(mime, "video/", 6)) {
                LOGI("Selected Track num.: %d, mime type: %s", i, mime);
                AMediaExtractor_selectTrack(extractor, i);

                AMediaExtractor_selectTrack(ex, i);
                codec = AMediaCodec_createDecoderByType(mime);
                AMediaCodec_configure(codec, format, window, NULL, 0);
                AMediaFormat_delete(format);
                AMediaCodec_start(codec);
                videoWidth = AMediaFormat_getInteger(AMediaFormat_KEY_WIDTH);
                videoHeight = AMediaFormat_getInteger(AMediaFormat_KEY_HEIGHT);
                Log.i(TAG, "Video size = " + videoWidth + " x " + videoHeight);
                return i;
            }

        }
        LOGE("Video Track not found");
        return -1;
    }



extern "C" {
#endif
/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    init
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_gpac_Osmo4_Decoder_init
  (JNIEnv * env, jobject obj, jstring jpath) {

    const char* path = env->GetStringUTFChars(jpath, JNI_FALSE);
    LOGV("Data Source path: '%s'", path);

    extractor = AMediaExtractor_new();

    media_status_t err = AMediaExtractor_setDataSource(extractor, path);
    //releasing the strings
    env->ReleaseStringUTFChars(jpath, path);

    if(err != AMEDIA_OK) {
        LOGV("setDataSource failed");
        return;
    }

    LOGV("Data Source Set");

    size_t trackNo = selectTrack();

    if (trackNo < 0)
         return;

    if (codec == NULL)
         return;






  }

/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    setPlaying
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_gpac_Osmo4_Decoder_setPlaying
  (JNIEnv *, jobject, jboolean) {

  }

/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    setSurface
 * Signature: (Landroid/view/Surface;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_gpac_Osmo4_Decoder_setSurface
  (JNIEnv *, jobject, jobject) {

  }

/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    release
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gpac_Osmo4_Decoder_release
  (JNIEnv *, jobject) {

  }

#ifdef __cplusplus
}
#endif
#endif
