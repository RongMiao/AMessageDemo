#define LOG_TAG "PlayerDemo"
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/ADebug.h>
#include "PlayerDemo.h"

int main() {
    using namespace android;

    ALOGD("tid = %d, func = %s", gettid(), __func__);
    sp<ALooper> looper = new ALooper;
    looper->setName("PlayerDemo");
    looper->start();
    sp<PlayerDemo> player = new PlayerDemo(looper);
    looper->registerHandler(player);

    player->setDataSource("ABC.mp4");

    sp<AMessage> format = new AMessage;
    format->setInt32("width", 1920);
    format->setInt32("height", 1080);
    player->prepare(format);

    player->start();

    sp<AMessage> format2;
    player->getFormat(format2);
    int width, height;
    CHECK(format->findInt32("width", &width));
    CHECK(format->findInt32("height", &height));
    ALOGD("[%s %d] width = %d, height = %d", __FUNCTION__, __LINE__, width, height);

    player->stop();

    sleep(5);
    looper->stop();

    return 0;
}


/*
06-12 15:44:59.693  5316  5316 D PlayerDemo: tid = 5316, func = main
06-12 15:44:59.695  5316  5316 D PlayerDemo: [PlayerDemo 11]
06-12 15:44:59.695  5316  5316 D PlayerDemo: [setDataSource 24]
06-12 15:44:59.695  5316  5316 D PlayerDemo: [prepare 32]
06-12 15:44:59.695  5316  5317 D PlayerDemo: [onMessageReceived 66] url = ABC.mp4
06-12 15:44:59.695  5316  5317 D PlayerDemo: [onMessageReceived 77] width = 1920, height = 1080
06-12 15:45:02.696  5316  5316 D PlayerDemo: [start 41]
06-12 15:45:02.696  5316  5316 D PlayerDemo: [getFormat 48]
06-12 15:45:02.697  5316  5317 D PlayerDemo: [onMessageReceived 85] starting ...
06-12 15:45:02.698  5316  5316 D PlayerDemo: [main 31] width = 1920, height = 1080
06-12 15:45:02.698  5316  5316 D PlayerDemo: [stop 54]
06-12 15:45:02.698  5316  5317 D PlayerDemo: [onMessageReceived 102] stop ...
06-12 15:45:07.699  5316  5316 D PlayerDemo: [~PlayerDemo 17]

*/