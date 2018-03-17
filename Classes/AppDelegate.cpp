#include "AppDelegate.h"
#include "LevelGameScene.h"
#include "AndroidScene.h"
#include "SimpleAudioEngine.h"
#include "Admob.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(960, 640);


AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    FileUtils::getInstance()->addSearchPath("fonts/");
    FileUtils::getInstance()->addSearchPath("imgLevel/");
    FileUtils::getInstance()->addSearchPath("imgInGame/");
    FileUtils::getInstance()->addSearchPath("helpGame/");
    FileUtils::getInstance()->addSearchPath("popup/");
    FileUtils::getInstance()->addSearchPath("data/");
    FileUtils::getInstance()->addSearchPath("sound/");
    
    if(UserDefault::getInstance()->getBoolForKey("sound", true)){
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    }
    else{
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
    register_all_packages();
    
    // create a scene. it's an autorelease object
    
    
#if  CC_TARGET_PLATFORM == CC_PLATFORM_IOS
      Admob::getInstance()->init("ca-app-pub-6021678406318751/1003081021","ca-app-pub-6021678406318751/2479814222");
    auto scene = LevelGameScene::createLevelGameScene();
#endif
#if  CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    auto scene = AndroidScene::CreateScene();
#endif
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}