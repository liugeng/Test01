//
//  GameScene.h
//  Test01
//
//  Created by liu geng on 14-9-9.
//
//

#ifndef __Test01__GameScene__
#define __Test01__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "Level.h"

USING_NS_CC;

class GameScene : public ParallaxNode {
public:
	static Scene *scene();

	CREATE_FUNC(GameScene);
	bool init();

	void update(float dt);

	void addWayPoint();

	bool onTouchBegin(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);

	CC_SYNTHESIZE(Level*, _level, Level);

private:
	LayerColor *_dotLayer;
	EventListenerTouchOneByOne *_touchListener;
	Sprite *_mask;

};

#endif /* defined(__Test01__GameScene__) */
