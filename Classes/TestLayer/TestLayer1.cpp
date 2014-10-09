//
//  TestLayer1.cpp
//  Test02
//
//  Created by liu geng on 14-5-22.
//
//

#include "TestLayer1.h"
#include "CustomShaders.h"

CALL(3)

Implemention(3) {

	timeval t;
	gettimeofday(&t, nullptr);
	int64_t tmsec = (int64_t)t.tv_sec*1000 + t.tv_usec/1000;

	time_t tsec = tmsec / 1000;
	tm *timeinfo = localtime(&tsec);
	char buf[32] = {0};
	strftime(buf, 32, "%m月%d日%H时%M分", timeinfo);
	CCLOG("%s", buf);
}

Implemention(2) {

	function<void(int)> f = [](int n) { CCLOG("n is %d", n); };
	f(8);

	int x = 2;
	auto f1 = [&x](int n) {
		stringstream ss;
		ss << "x is " << x << ", and n is " << n;
		return ss.str();
	};

	CCLOG("%s", f1(3).c_str());
}

Implemention(1) {

	vector<int> c { 1, 2, 3, 4, 5, 6, 7 };
	int x = 5;

	remove_if(c.begin(), c.end(), [x](int n){ return n < x; });
	for (auto &i : c) {
		printf("%d ", i);
	}
	printf("\n");

	c.erase(remove_if(c.begin(), c.end(), [x](int n){ return n < x; }), c.end());
	for (auto &i : c) {
		printf("%d ", i);
	}
	printf("\n");
}


#pragma mark

Scene* TestLayer1::scene() {
	Scene *scene = Scene::create();
	TestLayer1 *layer = TestLayer1::create();
	scene->addChild(layer);
	return scene;
}

bool TestLayer1::init() {

	if (!Layer::init()) {
		return false;
	}

	_win = Director::getInstance()->getWinSize();
	_center = Point(_win.width/2, _win.height/2);
	LayerColor *lc = LayerColor::create(Color4B::BLACK, _win.width, _win.height);
	addChild(lc, -1);

	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TestLayer1::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(TestLayer1::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TestLayer1::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	test();

	return true;
}



bool TestLayer1::onTouchBegan(Touch *pTouch, Event *pEvent) {

	return true;
}

void TestLayer1::onTouchMoved(Touch *pTouch, Event *pEvent) {


}

void TestLayer1::onTouchEnded(Touch *pTouch, Event *pEvent) {


}
