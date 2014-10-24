//
//  TestLayer1.h
//  Test02
//
//  Created by liu geng on 14-5-22.
//
//

#ifndef __Test02__TestLayer1__
#define __Test02__TestLayer1__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define Interface(_n_) void t##_n_()
#define Implemention(_n_) void TestLayer1::t##_n_()

#define CALL(__FUNC_IDX__) \
void TestLayer1::test() {\
	CUR_TEST = __FUNC_IDX__;\
	t##__FUNC_IDX__();\
}


class TestLayer1 : public Layer {

public:

	Interface(8);

	// make teakey
	Interface(7);

	// create image with alpha from jpg and mask pair
	Interface(6);

	// convert png to jpg and mask images pair
	Interface(5);

	// split images from plist file
	Interface(4);

	// format time
	Interface(3);

	// lambda
	Interface(2);

	// remove_if
	Interface(1);

public:
	void test();

    virtual bool init();

    static Scene* scene();

    CREATE_FUNC(TestLayer1);

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
    void onTouchMoved(Touch *pTouch, Event *pEvent);
    void onTouchEnded(Touch *pTouch, Event *pEvent);

private:
	Size _win;
	Point _center;
	int CUR_TEST;
};

#endif /* defined(__Test02__TestLayer1__) */
