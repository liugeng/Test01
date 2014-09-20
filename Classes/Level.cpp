//
//  Level.cpp
//  Test01
//
//  Created by liu geng on 14-9-9.
//
//

#include "Level.h"

USING_NS_CC;

Level* Level::create(const std::string &filename) {

    auto lvl = new Level();

    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB5A1);
    auto sp = Sprite::create(filename);
    Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA8888);
    Size size = sp->getContentSize();

	lvl->setContentSize(size);
	Sprite *dot = Sprite::create("dot.png");

    auto ret = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGB5A1);
    lvl->addChild(ret);
    lvl->setRT(ret);

    //** need to draw the default sprite
    ret->begin();
    sp->setAnchorPoint(Point::ZERO);
    sp->visit();
	dot->setAnchorPoint(Point::ZERO);
	dot->visit();
    ret->end();
    Director::getInstance()->getRenderer()->render();

	dot->setPosition(Point::ZERO);
	lvl->addChild(dot);

    lvl->autorelease();

    return lvl;
}
