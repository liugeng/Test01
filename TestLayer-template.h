//
//  TestLayer.h
//  Test02
//
//  Created by liu geng on 14-5-22.
//
//

#ifndef __Test02__TestLayer__
#define __Test02__TestLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define Interface(_n_) void t##_n_()
#define Implemention(_n_) void TestLayer::t##_n_()

#define CALL(__FUNC_IDX__) \
void TestLayer::test() {\
	CUR_TEST = __FUNC_IDX__;\
	t##__FUNC_IDX__();\
}


class TestLayer : public Layer {

public:

	Interface(1);
	
public:
	void test();

    virtual bool init();

    static Scene* scene();

    CREATE_FUNC(TestLayer);

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
    void onTouchMoved(Touch *pTouch, Event *pEvent);
    void onTouchEnded(Touch *pTouch, Event *pEvent);

private:
	Size _win;
	Point _center;
	int CUR_TEST;
};

#endif /* defined(__Test02__TestLayer__) */
