//
//  PhysicsEditorLoader.h
//  Test01
//
//  Created by liu geng on 14-9-11.
//
//

#ifndef __Test01__PhysicsEditorLoader__
#define __Test01__PhysicsEditorLoader__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;



class PhysicsEditorLoader {

public:
	Sprite* load(const char *file);

private:
	bool isMember(ValueMap &map, const char *member);
	bool noMember(ValueMap &map, const char *member);
};

#endif /* defined(__Test01__PhysicsEditorLoader__) */
