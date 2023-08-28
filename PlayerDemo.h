#ifndef __PLAYER_DEMO_H__
#define __PLAYER_DEMO_H__

#include <media/stagefright/foundation/AHandler.h>

namespace android {

struct ALooper;
struct AMessage;

class PlayerDemo : public AHandler {
public:
    PlayerDemo(const sp<android::ALooper> &looper);
    status_t init();
    status_t setDataSource(const AString &url);
    status_t prepare(const sp<AMessage> &format);
    status_t start();
    status_t getFormat(sp<AMessage> &format);
    status_t stop();

protected:
    virtual ~PlayerDemo();
    virtual void onMessageReceived(const sp<AMessage> &msg);

    enum {
        kWhatSetDataSource      = 'sDat',
        kWhatPrepare            = 'prep',
        kWhatStart              = 'star',
        kWhatGetFormat          = 'gFor',
        kWhatStop               = 'stop',
    };

private:
    sp<android::ALooper> mLooper;
    int mWidth;
    int mHeight;
};

} // android

#endif // ! __PLAYER_DEMO_H__