#ifndef Game_About_h
#define Game_About_h

class AboutScene : public cocos2d::CCLayer
{
public:

    virtual bool init();

    static cocos2d::CCScene* scene();

    void menuBackCallback(CCObject* pSender);

    CREATE_FUNC(AboutScene);

};


#endif
