//
//  TestLayer1.cpp
//  Test02
//
//  Created by liu geng on 14-5-22.
//
//

#include "TestLayer1.h"
#include "CustomShaders.h"

#define R(_VAL_) *((unsigned char*)(_VAL_))
#define G(_VAL_) *((unsigned char*)(_VAL_)+1)
#define B(_VAL_) *((unsigned char*)(_VAL_)+2)
#define A(_VAL_) *((unsigned char*)(_VAL_)+3)

CALL(7)


Implemention(7) {

	Sprite *sp = Sprite::create("tank.png");
	sp->setPosition(_center);
	addChild(sp);

	GLProgram *program = GLProgram::createWithByteArrays(testshader_vert, frozen_frag);
	sp->setGLProgram(program);

}

Implemention(6) {

	Sprite *sp = Sprite::create("swordman.jpg");
	sp->setPosition(_center);
	addChild(sp);


	Texture2D *tex = Director::getInstance()->getTextureCache()->addImage("swordman_mask.jpg");
	tex->retain();

	GLProgram *program = GLProgram::createWithByteArrays(testshader_vert, imageAlpha_frag);
	sp->setGLProgram(program);

	GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(program);
	state->setUniformTexture("u_masktex", tex);

}

Implemention(5) {

	string path = FileUtils::getInstance()->getWritablePath();
	CCLOG("save path: %s", path.c_str());

	Image *img = new Image;
	img->initWithImageFile("swordman.png");
	img->saveToFile((path+"swordman.jpg").c_str());

	unsigned int *data = (unsigned int*)img->getData();
	for (int i = 0; i < img->getHeight(); i++) {
		for (int j = 0; j < img->getWidth(); j++) {
			unsigned int &pixel = data[i*img->getWidth()+j];
			R(&pixel) = G(&pixel) = B(&pixel) = A(&pixel);
		}
	}
	img->saveToFile((path+"swordman_mask.jpg").c_str());

	delete img;
}

Implemention(4) {

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("swordman.plist");

	ValueMap value = FileUtils::getInstance()->getValueMapFromFile("swordman.plist");
	ValueMap frames = value["frames"].asValueMap();
	for (auto it : frames) {
		CCLOG("%s", it.first.c_str());

		Sprite *sp = Sprite::createWithSpriteFrameName(it.first.c_str());

		RenderTexture *rt = RenderTexture::create(sp->getContentSize().width*2, sp->getContentSize().height*2, Texture2D::PixelFormat::RGBA8888);
		rt->begin();
		sp->setAnchorPoint(Point::ZERO);
		sp->setScale(2);
		sp->visit();
		rt->end();
		Director::getInstance()->getRenderer()->render();

		rt->saveToFile(it.first.c_str());
	}

	CCLOG("end");
}

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
	LayerColor *lc = LayerColor::create(Color4B::GRAY, _win.width, _win.height);
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
