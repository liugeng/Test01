//
//  TestLayer.cpp
//  Test02
//
//  Created by liu geng on 14-5-22.
//
//

#include "TestLayer.h"


CALL(1)


Implemention(1) {


}


#pragma mark

Scene* TestLayer::scene() {
	Scene *scene = Scene::create();
	TestLayer *layer = TestLayer::create();
	scene->addChild(layer);
	return scene;
}

bool TestLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	_win = Director::getInstance()->getWinSize();
	_center = Point(_win.width/2, _win.height/2);
	LayerColor *lc = LayerColor::create(Color4B::GRAY, _win.width, _win.height);
	addChild(lc, -1);

	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TestLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	test();

	return true;
}



bool TestLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {

	return true;
}

void TestLayer::onTouchMoved(Touch *pTouch, Event *pEvent) {


}

void TestLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {


}
