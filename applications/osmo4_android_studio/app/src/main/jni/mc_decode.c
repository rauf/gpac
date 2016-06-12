#include <jni.h>
#include <string.h>

#include "com_gpac_Osmo4_Decoder.h"

//#include <gpac/modules/codec.h>

#include "media/NdkMediaCodec.h"
#include "media/NdkMediaExtractor.h"
#include "media/NdkMediaFormat.h"


// for native window JNI
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>


#include<android/log.h>

#define TAG "Native Decoder"
#define LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, TAG,  __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, TAG,  __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN, TAG,  __VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, TAG,  __VA_ARGS__)


typedef struct {
    ANativeWindow *window;
    AMediaCodec *codec;
    AMediaExtractor *extractor;
    bool isPlaying;
    __u32 width;
    __u32 height;
} MCDec;



    //select track using MediaExtractor
    __u32 selectTrack(MCDec *dec) {
        int trackCount = (int) AMediaExtractor_getTrackCount(dec->extractor);
        size_t i;
        LOGV("Total num. of tracks: %d", trackCount);
        for (i = 0; i < trackCount; ++i) {
            AMediaFormat *format = AMediaExtractor_getTrackFormat(dec->extractor, i);

            char *mime;

            bool b = AMediaFormat_getString(format, AMEDIAFORMAT_KEY_MIME, &mime);

            if(!b) {
                LOGE("No mime type");
                return -1;
            }
            else LOGI("Track num.: %d, mime type: %s ", i, mime);

            if (!strncmp(mime, "video/", 6)) {
                LOGI("Selected Track num.: %d, mime type: %s", i, mime);
                AMediaExtractor_selectTrack(dec->extractor, i);

                AMediaExtractor_selectTrack(dec->extractor, i);
                dec->codec = AMediaCodec_createDecoderByType(mime);
                AMediaCodec_configure(dec->codec, format, dec->window, NULL, 0);
                AMediaFormat_delete(format);
                AMediaCodec_start(dec->codec);
                //dec->width = AMediaFormat_getInteger(AMediaFormat_KEY_WIDTH);
                //dec->height = AMediaFormat_getInteger(AMediaFormat_KEY_HEIGHT);
                LOGI(TAG, "Video size = %d x %d ",dec->width, dec->height);
                return i;
            }

        }
        LOGE("Video Track not found");
        return  -1;
    }



/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    init
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_gpac_Osmo4_Decoder_init
  (JNIEnv * env, jobject obj, jstring jpath) {

    /*
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

*/




  }

/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    setPlaying
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_com_gpac_Osmo4_Decoder_setPlaying
  (JNIEnv * env, jobject obj, jboolean isPlaying) {

  }

/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    setSurface
 * Signature: (Landroid/view/Surface;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_gpac_Osmo4_Decoder_setSurface
  (JNIEnv * env, jobject obj, jobject surface) {

  }

/*
 * Class:     com_gpac_Osmo4_Decoder
 * Method:    release
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gpac_Osmo4_Decoder_release
  (JNIEnv * env, jobject obj) {

  }
