#define LOG_TAG "PlayerDemo"

#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ALooper.h>
#include <media/stagefright/foundation/ADebug.h>
#include "PlayerDemo.h"

namespace android {
    
PlayerDemo::PlayerDemo(const sp<ALooper> &looper) {
    ALOGD("[%s %d]", __FUNCTION__, __LINE__);
    mLooper = looper;
    //mLooper->registerHandler(this);       // will crash
}

PlayerDemo::~PlayerDemo() {
    ALOGD("[%s %d]", __FUNCTION__, __LINE__);
    mLooper->unregisterHandler(id());
}


status_t PlayerDemo::setDataSource(const AString &url) {
    //mLooper->registerHandler(this);       // can call here
    ALOGD("[%s %d]", __FUNCTION__, __LINE__);
    sp<AMessage> msg = new AMessage(kWhatSetDataSource, this);
    msg->setString("url", url);
    msg->post();
    return OK;
}

status_t PlayerDemo::prepare(const sp<AMessage> &format) {
    ALOGD("[%s %d]", __FUNCTION__, __LINE__);
    sp<AMessage> msg = new AMessage(kWhatPrepare, this);
    msg->setMessage("format", format);
    sp<AMessage> response;
    return msg->postAndAwaitResponse(&response);
    
}

status_t PlayerDemo::start() {
    ALOGD("[%s %d]", __FUNCTION__, __LINE__);
    sp<AMessage> msg = new AMessage(kWhatStart, this);
    msg->post();
    return OK;
}

status_t PlayerDemo::getFormat(sp<AMessage> &format) {
    ALOGD("[%s %d]", __FUNCTION__, __LINE__);
    sp<AMessage> msg = new AMessage(kWhatGetFormat, this);
    return msg->postAndAwaitResponse(&format); 
}

status_t PlayerDemo::stop() {
    ALOGD("[%s %d]", __FUNCTION__, __LINE__);
    sp<AMessage> msg = new AMessage(kWhatStop, this);
    msg->post();
    return OK;
}

void PlayerDemo::onMessageReceived(const sp<AMessage> &msg) {
    switch (msg->what()) {
        case kWhatSetDataSource:
        {
            AString url;
            CHECK(msg->findString("url", &url));
            ALOGD("[%s %d] url = %s", __FUNCTION__, __LINE__, url.c_str());
            break;
        }
        case kWhatPrepare:
        {
            sp<AReplyToken> replyID;
            CHECK(msg->senderAwaitsResponse(&replyID));
            sp<AMessage> format;
            CHECK(msg->findMessage("format", &format));
            CHECK(format->findInt32("width", &mWidth));
            CHECK(format->findInt32("height", &mHeight));
            ALOGD("[%s %d] width = %d, height = %d", __FUNCTION__, __LINE__, mWidth, mHeight);
            sleep(3);
            sp<AMessage> response = new AMessage;
            response->postReply(replyID);
            break;
        }
        case kWhatStart: 
        {
            ALOGD("[%s %d] starting ...", __FUNCTION__, __LINE__);
            break;
        }
        case kWhatGetFormat:
        {
            sp<AReplyToken> replyID;
            CHECK(msg->senderAwaitsResponse(&replyID));
            sp<AMessage> format = new AMessage;
            format->setInt32("width", mWidth);
            format->setInt32("height", mHeight);
            sp<AMessage> response = new AMessage;
            response->setMessage("format", format);
            response->postReply(replyID);
            break;
        }
        case kWhatStop:
        {
            ALOGD("[%s %d] stop ...", __FUNCTION__, __LINE__);
            break;
        }
        default:
            break;
    }
}

}   // android