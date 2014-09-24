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
#include "clipper.hpp"
#include "poly2tri.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace ClipperLib;


#define Interface(_n_) void t##_n_()
#define Implemention(_n_) void TestLayer::t##_n_()

#define CALL(__FUNC_IDX__) \
void TestLayer::test() {\
	CUR_TEST = __FUNC_IDX__;\
	t##__FUNC_IDX__();\
}

class TestLayer : public Layer {

public:

	/**
	 *  直接修改像素
	 */
	Interface(10);
	void addHoleAt10(int posx, int posy);
	unsigned int changeDarker(unsigned int *val, float factor);

	/**
	 *  有明显阴影
	 */
	Interface(9);
	void addHoleAt9(float posx, float posy);

	/**
	 *  在7的基础上只保存部分纹理，failed
	 */
	Interface(8);
	void addHoleAt8(float posx, float posy);

	/**
	 *  画坑前保存旧的纹理，画坑，然后用保存的纹理去修正新图
	 */
	Interface(7);
	void addHoleAt7(float posx, float posy);

	/**
	 *  将添加shader后的图像重绘成一个新的纹理
	 *	ISSUE: 速度较慢，多次重绘后颜色变暗
	 */
	Interface(6);
	void addHoleAt(float posx, float posy);

	/**
	 *  配合Shader和RenderTexture
	 *	ISSUE: 先将遮罩图在画布上画好，再将整体作为遮罩给背景图使用，但是弹坑图上的白色
	 *	部分会遮住其他的弹坑
	 */
	Interface(5);
	void drawHoleAt(Sprite *img, const Point& p);

	/**
	 *  Shader
	 */
	Interface(4);

	/**
	 *  从PhysicsEditor导出文件创建物理对象
	 */
	Interface(3);

	/**
	 *  测试ClipperLib和Poly2tri
	 */
	Interface(2);
	ClipperLib::Path shapeToPath(PhysicsShapePolygon *shape);
	Paths shapesToPaths(const Vector<PhysicsShape*>& shapes);
	PhysicsShapePolygon* pathToShape(Path &p);
	Path addOffsetToPath(Path &p, const Point &offset);
	void drawPath(Path &p);
	void printPath(Path &p);
	void validWinding(Vec2 *points, int size);
	bool isValid(Vec2 *points, int size);

	/**
	 *  测试ClipperLib
	 */
	Interface(1);

	Interface(0);
	
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

	DrawNode *_draw;
};

#endif /* defined(__Test02__TestLayer__) */
