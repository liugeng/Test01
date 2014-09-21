#include "AppDelegate.h"
#include "TestLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("My Game", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

//	Size s = Director::getInstance()->getWinSize();
//	float scaleX = 960.0 / s.width;
//	float scaleY = 640.0 /s.height;
//	float scale = MAX(scaleX, scaleY);
//	CCLOG("win size: %g, %g, scale: %g", s.width, s.height, scale);
//	glview->setDesignResolutionSize(s.width * scale, s.height * scale, ResolutionPolicy::NO_BORDER);
	glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = TestLayer::scene();

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
