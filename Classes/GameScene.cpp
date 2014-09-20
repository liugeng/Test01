//
//  GameScene.cpp
//  Test01
//
//  Created by liu geng on 14-9-9.
//
//

#include "GameScene.h"

Scene* GameScene::scene() {

	Scene *ret = Scene::create();
	GameScene *layer = GameScene::create();
	ret->addChild(layer);
	return ret;
}

bool GameScene::init() {

	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto offset = Point(visibleSize/2);

	Sprite *background = Sprite::create("HelloWorld.png");
	addChild(background, 1, Point(0.5, 0.8), offset);

	_level = Level::create("desert.png");
	addChild(_level, 2, Point(1, 1), offset);

	_dotLayer = LayerColor::create(Color4B(0, 0, 0, 100));
	_dotLayer->setContentSize(_level->getRT()->getSprite()->getContentSize());
	_dotLayer->ignoreAnchorPointForPosition(false);
	_dotLayer->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addChild(_dotLayer, 3, Point(1, 1), offset);

	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegin, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);

	_mask = Sprite::create("mask.png");
	_mask->setGLProgram(ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
	BlendFunc cut;
    cut ={
        GL_ZERO,
        GL_ONE_MINUS_SRC_ALPHA
    };
	_mask->setBlendFunc(cut);
	_mask->retain();

	//scheduleUpdate();

	return true;
}

void GameScene::addWayPoint() {

	Sprite *sp = _level->getRT()->getSprite();
	CCLOG("anchor: %g, %g, pos: %g, %g", sp->getAnchorPoint().x, sp->getAnchorPoint().y, sp->getPositionX(), sp->getPositionY());

	int x = sp->getBoundingBox().origin.x;
	int y = sp->getBoundingBox().origin.y;
	int w = x + sp->getContentSize().width;
	int h = y + sp->getContentSize().height;

	_level->getRT()->begin();

	int bufferSize = h;

	while (x < w) {

		CCLOG("x: %d", x);

		Color4B *buffer = (Color4B*)malloc(sizeof(Color4B)*bufferSize);
		memset(buffer, 0, sizeof(Color4B)*bufferSize);

		glReadPixels(x, y, 1, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		for (int i = 0; i < bufferSize; i++) {
			CCLOG("alpha: %d, color %d, %d, %d", buffer[i].a, buffer[i].r, buffer[i].g, buffer[i].b);
			if (buffer[i].a > 0) {
				Sprite *sp = Sprite::create("dot.png");
				sp->setPosition(Point(x, i));
				_dotLayer->addChild(sp, 3);
				break;
			}
		}

		x += 20;
		free(buffer);
	}

	_level->getRT()->end();
}

void GameScene::update(float dt) {

	static bool flag = true;
	if (flag) {
		addWayPoint();
		flag = false;
	}
}

bool GameScene::onTouchBegin(Touch *touch, Event *event) {

	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event) {

	//Point p = _dotLayer->convertTouchToNodeSpace(touch);
	Point p = touch->getLocation();
	Sprite *sp = _level->getRT()->getSprite();
	if (!sp->boundingBox().containsPoint(_level->convertTouchToNodeSpace(touch))) {
		return;
	}

	CCLOG("origin %g, %g, content %g, %g", _level->getBoundingBox().origin.x, _level->getBoundingBox().origin.y, _level->getContentSize().width, _level->getContentSize().height);

	_level->getRT()->begin();

	Point t = _dotLayer->convertTouchToNodeSpace(touch);
	CCLOG("t: %g, %g", t.x, t.y);
	_mask->setPosition(t);
	_mask->visit();

	Color4B *c = new Color4B(0, 0, 0, 0);
	glReadPixels(p.x, p.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, c);
	CCLOG("pixel: %d, %d, %d, %d", c->r, c->g, c->b, c->a);
	delete c;
	_level->getRT()->end();

}

