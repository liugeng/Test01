//
//  Level.h
//  Test01
//
//  Created by liu geng on 14-9-9.
//
//

#ifndef __Test01__Level__
#define __Test01__Level__

#include <iostream>
#include "cocos2d.h"

class Level :public cocos2d::Node
{
public:
	Level() : _rt(NULL) {}
    static Level* create(const std::string &filename);
    CC_SYNTHESIZE(cocos2d::RenderTexture*, _rt, RT);
};

#endif /* defined(__Test01__Level__) */
