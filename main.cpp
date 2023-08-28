#define LOG_TAG "PlayerDemo"
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/ADebug.h>
#include "PlayerDemo.h"

#if 0
// 基本功能测试
int main() {
    using namespace android;

    ALOGD("tid = %d, func = %s", gettid(), __func__);
    sp<ALooper> looper = new ALooper;
    looper->setName("PlayerDemo");
    looper->start();
    sp<PlayerDemo> player = new PlayerDemo(looper);
    player->init();
    player->setDataSource("ABC.mp4");

    sp<AMessage> format = new AMessage;
    format->setInt32("width", 1920);
    format->setInt32("height", 1080);
    player->prepare(format);

    player->start();

    sp<AMessage> format2;
    player->getFormat(format2);
    int width, height;
    CHECK(format2->findInt32("width", &width));
    CHECK(format2->findInt32("height", &height));
    ALOGD("[%s %d] width = %d, height = %d", __FUNCTION__, __LINE__, width, height);

    player->stop();

    // sleep 5s，等待所有 message 处理完毕
    sleep(5);
    looper->stop();

    return 0;
}

/*
08-07 05:42:45.186  5417  5417 D PlayerDemo: tid = 5417, func = main
08-07 05:42:45.187  5417  5417 D PlayerDemo: [PlayerDemo 11]
08-07 05:42:45.187  5417  5417 D PlayerDemo: [setDataSource 27]
08-07 05:42:45.187  5417  5417 D PlayerDemo: [prepare 35]
08-07 05:42:45.187  5417  5418 D PlayerDemo: [onMessageReceived 71] process kWhatSetDataSource, url = ABC.mp4
08-07 05:42:45.187  5417  5418 D PlayerDemo: [onMessageReceived 82] process kWhatPrepare, width = 1920, height = 1080
08-07 05:42:48.187  5417  5417 D PlayerDemo: [start 44]
08-07 05:42:48.187  5417  5417 D PlayerDemo: [getFormat 51]
08-07 05:42:48.187  5417  5418 D PlayerDemo: [onMessageReceived 90] process kWhatStart, starting ...
08-07 05:42:51.188  5417  5418 D PlayerDemo: [onMessageReceived 92] process kWhatStart, ending ...
08-07 05:42:51.188  5417  5418 D PlayerDemo: [onMessageReceived 97] process kWhatGetFormat
08-07 05:42:51.188  5417  5417 D PlayerDemo: [main 31] width = 1920, height = 1080
08-07 05:42:51.188  5417  5417 D PlayerDemo: [stop 59]
08-07 05:42:51.188  5417  5418 D PlayerDemo: [onMessageReceived 110] process kWhatStop, stop ...
08-07 05:42:56.188  5417  5417 D PlayerDemo: [~PlayerDemo 17]
*/

#endif

#if 1
// looper stop 测试
int main() {
    using namespace android;

    ALOGD("tid = %d, func = %s", gettid(), __func__);
    sp<ALooper> looper = new ALooper;
    looper->setName("PlayerDemo");
    looper->start();
    sp<PlayerDemo> player = new PlayerDemo(looper);
    player->init();
    player->setDataSource("ABC.mp4");

    player->start();

    player->stop();
    
    // sleep 1s，确保进入到 start
    sleep(1);
    ALOGD("[%s %d] looper stop begin", __FUNCTION__, __LINE__);
    looper->stop();
    ALOGD("[%s %d] looper stop end", __FUNCTION__, __LINE__);
    return 0;
}

/*
08-07 05:50:16.171  5599  5599 D PlayerDemo: tid = 5599, func = main
08-07 05:50:16.172  5599  5599 D PlayerDemo: [PlayerDemo 11]
08-07 05:50:16.172  5599  5599 D PlayerDemo: [setDataSource 27]
08-07 05:50:16.172  5599  5599 D PlayerDemo: [start 44]
08-07 05:50:16.172  5599  5599 D PlayerDemo: [stop 59]
08-07 05:50:16.172  5599  5600 D PlayerDemo: [onMessageReceived 71] process kWhatSetDataSource, url = ABC.mp4
08-07 05:50:16.172  5599  5600 D PlayerDemo: [onMessageReceived 90] process kWhatStart, starting ...
08-07 05:50:17.172  5599  5599 D PlayerDemo: [main 82] looper stop begin
08-07 05:50:19.172  5599  5600 D PlayerDemo: [onMessageReceived 92] process kWhatStart, ending ...
08-07 05:50:19.172  5599  5599 D PlayerDemo: [main 84] looper stop end
08-07 05:50:19.172  5599  5599 D PlayerDemo: [~PlayerDemo 17]
*/
# endif