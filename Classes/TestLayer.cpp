//
//  TestLayer.cpp
//  Test02
//
//  Created by liu geng on 14-5-22.
//
//

#include "TestLayer.h"
#include "PhysicsEditorLoader.h"
#include "CustomShaders.h"
#include "Global.h"

CALL(10)


#define R(_VAL_) *((unsigned char*)_VAL_)
#define G(_VAL_) *((unsigned char*)_VAL_+1)
#define B(_VAL_) *((unsigned char*)_VAL_+2)
#define A(_VAL_) *((unsigned char*)_VAL_+3)

Sprite *_background10 = nullptr;
Image *_sourceImg = nullptr;
Image *_holeImg = nullptr;
Implemention(10) {

	if (!isRunning()) {
		return;
	}

	if (!_background10) {
		/**
		 *  1.make background Image: _sourceData
		 *	2.make hole Image: _holeData
		 *	3.change _sourceData according to _holeData
		 *	4.make new texture from _sourceData, and pass it to background
		 */
		_background10 = Sprite::create("desert.png");
		_background10->setAnchorPoint(Point::ZERO);
		addChild(_background10);

		Size s = _background10->getContentSize();

		// 1
		RenderTexture *rt = RenderTexture::create(s.width, s.height, Texture2D::PixelFormat::RGBA8888);
		rt->begin();
		_background10->visit();
		rt->end();
		Director::getInstance()->getRenderer()->render();

		/* Caller is responsible for releasing it by calling delete. */
		_sourceImg = rt->newImage();
		rt->saveToFile("rtsave.png");
		_sourceImg->saveToFile((FileUtils::getInstance()->getWritablePath()+"imgsave.png").c_str());

		// 2
		Sprite *hole = Sprite::create("hole.png");
		hole->setAnchorPoint(Point::ZERO);

		rt = RenderTexture::create(hole->getContentSize().width, hole->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
		rt->begin();
		hole->visit();
		rt->end();
		Director::getInstance()->getRenderer()->render();

		_holeImg = rt->newImage();
		
		addHoleAt10(100, 200);

	} else {

		static int i = 1;
		addHoleAt10((++i)*100, 200);
	}
}

void TestLayer::addHoleAt10(int posx, int posy) {

	// no color means erase
	// white color means remain

	// change pixels
	unsigned int *sourceData = (unsigned int*)_sourceImg->getData();
	unsigned int *holeData = (unsigned int*)_holeImg->getData();

	// if r, g, b, a all larger then limit value, handle it as white color
	unsigned char limit = 150;

	// make color darker
//	unsigned char weight = -50;

	posy = _sourceImg->getHeight()-_holeImg->getHeight()-posy;
	int maxx = MIN(posx+_holeImg->getWidth(), _sourceImg->getWidth());
	int maxy = MIN(posy+_holeImg->getHeight(), _sourceImg->getHeight());
	for (int i = posx; i < maxx; i++) {
		for (int j = posy; j < maxy; j++) {
			unsigned int *srcPixel = sourceData + j * _sourceImg->getWidth() + i;
			//*srcPixel = 0xffffffff;

			unsigned int *holePixel = holeData + (j-posy) * _holeImg->getWidth() + (i-posx);


			if (A(holePixel) == 0) {
				*srcPixel = 0;

			} else if (A(srcPixel) > 0 && !(R(holePixel) >= limit &&
											G(holePixel) >= limit &&
											B(holePixel) >= limit &&
											A(holePixel) >= limit)) {

//				*srcPixel = *holePixel;

				float factor = fabsf(j-posy-_holeImg->getHeight()/2)/(_holeImg->getHeight()/2);
				factor = sqrt(factor);
				*srcPixel = changeDarker(holePixel, factor);
			}
		}
	}



	Texture2D *tex = new Texture2D;
	tex->initWithImage(_sourceImg);

	_background10->setTexture(tex);
	tex->release();
}

unsigned int TestLayer::changeDarker(unsigned int *val, float factor) {

	// factor is 0 ~ 1.0
	if (fabsf(factor-1.0) < FLT_EPSILON || factor > 1.0) {
		return *val;
	}

	unsigned char r = R(val);
	unsigned char g = G(val);
	unsigned char b = B(val);

	r *= factor;
	g *= factor;
	b *= factor;

	r = MAX(0, MIN(255, r));
	g = MAX(0, MIN(255, g));
	b = MAX(0, MIN(255, b));

	int ret;
	R(&ret) = r;
	G(&ret) = g;
	B(&ret) = b;
	A(&ret) = 0xff;

	return ret;
}


Sprite *_background9 = nullptr;
Sprite *_hole = nullptr;
RenderTexture *_canvas = nullptr;
RenderTexture *_reference = nullptr;
Implemention(9) {

	if (!isRunning()) {
		return;
	}

	if (!_background9) {
		_background9 = Sprite::create("desert.png");
		_background9->setAnchorPoint(Point::ZERO);
		addChild(_background9);


		_hole = Sprite::create("hole.png");
		_hole->setBlendFunc({
			GL_SRC_ALPHA,
			GL_ZERO
		});
		_hole->setAnchorPoint(Point::ZERO);
		_hole->retain();


		Size s = _background9->getContentSize();

		_canvas = RenderTexture::create(s.width, s.height, Texture2D::PixelFormat::RGBA8888);
		_canvas->retain();
		_canvas->begin();
		_background9->visit();
		_canvas->end();
		Director::getInstance()->getRenderer()->render();


		_reference = RenderTexture::create(s.width, s.height, Texture2D::PixelFormat::RGBA8888);
		_reference->retain();
		_reference->begin();
		_background9->visit();
		_reference->end();
		Director::getInstance()->getRenderer()->render();


		_background9->setTexture(_canvas->getSprite()->getTexture());
		_background9->setFlippedY(true);


	} else {
		static int i = 0;
		addHoleAt9((++i)*100, 200);
	}


}

void TestLayer::addHoleAt9(float posx, float posy) {

	Point p(posx, posy);

	static bool first = true;
	if (first) {
		_background9->setPosition(-p);
	} else {
		_background9->setPosition(-p/2);
	}

	RenderTexture *tempRt = RenderTexture::create(_hole->getContentSize().width, _hole->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
	tempRt->begin();
	_background9->visit();
	tempRt->end();
	Director::getInstance()->getRenderer()->render();
//	tempRt->saveToFile("t9.png");


	tempRt->getSprite()->setAnchorPoint(Point::ZERO);
	tempRt->getSprite()->setPosition(p);
	tempRt->getSprite()->setBlendFunc({
		GL_SRC_ALPHA,
		GL_ZERO
	});

	_reference->begin();
	tempRt->getSprite()->visit();
	_reference->end();
	Director::getInstance()->getRenderer()->render();
//	_saved->saveToFile("t91.png");


	_canvas->begin();
	_hole->setPosition(p);
	_hole->visit();
	_canvas->end();


	_background9->setPosition(Point::ZERO);


	GLProgram *program = nullptr;
	if (first) {
		first = false;
		program = GLProgram::createWithByteArrays(ccPositionTextureColor_vert, correctcolor_frag9);
		_background9->setGLProgram(program);
	} else {
		program = _background9->getGLProgram();
	}

	GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(program);
	state->setUniformTexture("u_masktex", _reference->getSprite()->getTexture());
}



Sprite *_desert8 = nullptr;
RenderTexture *_render8 = nullptr;
RenderTexture *_tempRt8 = nullptr;
Implemention(8) {

	if (!isRunning()) {
		return;
	}

	if (!_render8) {
		_desert8 = Sprite::create("farm.png");
		_desert8->setAnchorPoint(Point::ZERO);
		Size s = _desert8->getContentSize();

		_render8 = RenderTexture::create(s.width, s.height, Texture2D::PixelFormat::RGBA8888);
		addChild(_render8);

		_render8->begin();
		_desert8->visit();
		_render8->end();

		_render8->getSprite()->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

		addHoleAt8(100, 200);

	} else {
		static int i = 0;
		addHoleAt8(100+(++i)*100, 200);
	}
}

void TestLayer::addHoleAt8(float posx, float posy) {


	// 480x320  100x200


	Point p(posx, posy);
	LogVec2("draw pos", p);
	// 100x200 100x200
	// 200x200 400x400
	// 300x200 600x400
	// 400x200 800x400

	Sprite *hole = Sprite::create("hole.png");
	hole->setAnchorPoint(Point::ZERO);
	hole->setPosition(p);
	hole->setBlendFunc({
		GL_SRC_ALPHA,
		GL_ZERO
	});



	static int flag = 1;
	if (flag) {
//		_render8->getSprite()->setPosition(-p);
		p *= -1;
		flag = 0;
	} else {
		/**
		 *  ?
		 */
//		_render8->getSprite()->setPosition(-p/2);
		p *= -1/2;
	}



	Size s = _render8->getSprite()->getContentSize();

	_render8->getSprite()->setPosition(p);

	RenderTexture *oldRt = _tempRt8;

	_tempRt8 = RenderTexture::create(hole->getContentSize().width, hole->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
	_tempRt8->retain();

	_tempRt8->begin();
	_render8->getSprite()->visit();
	_tempRt8->end();
	Director::getInstance()->getRenderer()->render();
	_tempRt8->saveToFile("tempT.png");

	_render8->getSprite()->setPosition(Point::ZERO);


	_render8->begin();
	hole->visit();
	_render8->end();



	GLProgram *program = _render8->getGLProgram();
	if (!program) {
		program = GLProgram::createWithByteArrays(ccPositionTextureColor_vert, correctcolor_frag8);
		_render8->getSprite()->setGLProgram(program);
	}
	GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(program);

	float x = posx/s.width;
	float y = posy/s.height;
	Size maskSize = hole->getContentSize();
	state->setUniformVec4("u_maskrect", Vec4(x, y, maskSize.width/s.width+x, maskSize.height/s.height+y));
	state->setUniformTexture("u_masktex", _tempRt8->getSprite()->getTexture());


	CC_SAFE_RELEASE(oldRt);
}




Sprite *_desert7 = nullptr;
RenderTexture *_render = nullptr;
RenderTexture *_tempRt = nullptr;
Implemention(7) {

	if (!isRunning()) {
		return;
	}

	if (!_render) {
		_desert7 = Sprite::create("desert.png");
		_desert7->setAnchorPoint(Point::ZERO);
		Size s = _desert7->getContentSize();

		_render = RenderTexture::create(s.width, s.height, Texture2D::PixelFormat::RGBA8888);
//		_render->setPosition(_center);
		addChild(_render);

		LogVec2("render anc", _render->getAnchorPoint());
		LogRect("render bound", _render->getBoundingBox());


		_render->begin();
		_desert7->visit();
		_render->end();

		_render->getSprite()->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

		addHoleAt7(100, 200);

	} else {
		static int i = 0;
		addHoleAt7(100+(++i)*100, 200);
	}


}

void TestLayer::addHoleAt7(float posx, float posy) {

	Point anc = _render->getSprite()->getAnchorPoint();
	CCLOG("anc: %g, %g", anc.x, anc.y);

	Point pos = _render->getPosition();
	_render->setPosition(Point::ZERO);

//	_render->getSprite()->setAnchorPoint(Point::ZERO);


	RenderTexture *oldRt = _tempRt;
	Size s = _render->getSprite()->getContentSize();
	_tempRt = RenderTexture::create(s.width, s.height, Texture2D::PixelFormat::RGBA8888);
	_tempRt->retain();

	_tempRt->begin();
	_render->cocos2d::Node::visit();
	_tempRt->end();
	Director::getInstance()->getRenderer()->render();
//	_tempRt->saveToFile("tempT.png");

//	_render->getSprite()->setAnchorPoint(Point::ANCHOR_MIDDLE);
//	_render->setPosition(pos);


	Sprite *hole = Sprite::create("hole1.png");
	hole->setAnchorPoint(Point::ZERO);
	hole->setPosition(Point(posx, posy));
	//	hole->setBlendFunc( {
	//		GL_DST_ALPHA,
	//        GL_ZERO
	//	} );

	//	Sprite *hole2 = Sprite::create("hole1.png");
	//	hole2->setAnchorPoint(Point::ZERO);
	//	hole2->setPosition(Point(200, 200));
	//	hole2->setBlendFunc( {
	//		GL_DST_ALPHA,
	//        GL_ZERO
	//	} );


	_render->begin();
	hole->visit();
	//	hole2->visit();
	_render->end();



	GLProgram *program = GLProgram::createWithByteArrays(ccPositionTextureColor_vert, correctcolor_frag);
	GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(program);
	state->setUniformTexture("u_masktex", _tempRt->getSprite()->getTexture());
	_render->getSprite()->setGLProgram(program);

	CC_SAFE_RELEASE(oldRt);
}

Sprite *_desert6 = nullptr;
Implemention(6) {

	if (!isRunning()) {
		return;
	}

	if (!_desert6) {
		_desert6 = Sprite::create("desert.png");
		_desert6->setPosition(getContentSize().width/2, _desert6->getContentSize().height/2);
		addChild(_desert6);

	} else {

		static int i = 0;
		addHoleAt((++i)*100, 200);
	}
}

void TestLayer::addHoleAt(float posx, float posy) {

	Size backSize = _desert6->getContentSize();

	Sprite *mask = Sprite::create("hole.png");
	Size maskSize = mask->getContentSize();

	Point p(posx, backSize.height-posy);


	Sprite *temp = Sprite::createWithSpriteFrame(_desert6->getSpriteFrame());
	temp->setPosition(_desert6->getPosition());
	temp->setFlippedY(true);



	GLProgram *program = GLProgram::createWithByteArrays(testshader_vert, testshader_frag);
	GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(program);



	p.y = backSize.height - p.y;

	float x = p.x/backSize.width;
	float y = p.y/backSize.height;
	state->setUniformVec4("u_maskrect", Vec4(x, y, maskSize.width/backSize.width+x, maskSize.height/backSize.height+y));
	state->setUniformTexture("u_masktex", mask->getTexture());
	temp->setGLProgram(program);




	RenderTexture *rt = RenderTexture::create(backSize.width, backSize.height, Texture2D::PixelFormat::RGBA8888);
	rt->begin();
	temp->visit();
	rt->end();


	//	string path = (FileUtils::getInstance()->getWritablePath()+"t.png");
	//	CCLOG("save path: %s", path.c_str());
	//	rt->saveToFile("t.png", Image::Format::PNG);

	_desert6->setSpriteFrame(rt->getSprite()->getSpriteFrame());

}


Implemention(5) {

	if (!isRunning()) {
		return;
	}

	Sprite *desert = Sprite::create("desert.png");
	desert->setPosition(getContentSize().width/2, desert->getContentSize().height/2);
	addChild(desert);

	GLProgram *program = GLProgram::createWithByteArrays(testshader_vert, testshader_frag);
	GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(program);


	Sprite *mask = Sprite::create("hole.png");
	mask->setFlippedY(true);

	Sprite *mask1 = Sprite::create("hole.png");
	mask1->setFlippedY(true);

	RenderTexture *rt = RenderTexture::create(desert->getContentSize().width, desert->getContentSize().height, Texture2D::PixelFormat::RGBA8888);
	rt->beginWithClear(1, 1, 1, 1);
	drawHoleAt(mask, Point(100, 300));
	drawHoleAt(mask1, Point(200, 300));
	rt->end();
	rt->retain();

	string path = (FileUtils::getInstance()->getWritablePath()+"t.png");
	CCLOG("save path: %s", path.c_str());
	rt->saveToFile("t.png", Image::Format::PNG);

	state->setUniformVec4("u_maskrect", Vec4(0, 0, 1, 1));
	state->setUniformTexture("u_masktex", rt->getSprite()->getTexture());
	desert->setGLProgram(program);


}

void TestLayer::drawHoleAt(Sprite *img, const Point &p) {

	img->setPosition(p);

	img->setBlendFunc({
		GL_ONE_MINUS_DST_ALPHA,
        GL_SRC_ALPHA
	});

	img->visit();
	img->setBlendFunc({
		GL_ONE_MINUS_DST_ALPHA,
		GL_ZERO
	});
	img->visit();
}

Implemention(4) {

	Sprite *desert = Sprite::create("desert.png");
	desert->setPosition(getContentSize().width/2, desert->getContentSize().height/2);
	addChild(desert);

	GLProgram *program = GLProgram::createWithByteArrays(testshader_vert, testshader_frag);
	GLProgramState *state = GLProgramState::getOrCreateWithGLProgram(program);

	Texture2D *mask = Director::getInstance()->getTextureCache()->addImage("hole.png");
	if (!mask) {
		CCLOG("create mask texture failed");
		return;
	}

	/**
	 *  u_maskrect: 标示遮罩图的现实区域，坐标按比例传递，值0.0~1.0
	 */
	state->setUniformVec4("u_maskrect", Vec4(0.1, 0.3, mask->getContentSize().width/desert->getContentSize().width+0.1, mask->getContentSize().height/desert->getContentSize().height+0.3));
	state->setUniformTexture("u_masktex", mask);
	desert->setGLProgram(program);
}


Sprite *_desert = nullptr;
Sprite *_tank = nullptr;
Implemention(3) {

	PhysicsEditorLoader loader;
	_desert = loader.load("desert.plist");
	_desert->getPhysicsBody()->setDynamic(false);
	_desert->setPosition(getContentSize().width/2, _desert->getContentSize().height/2);
	addChild(_desert);


	_tank = loader.load("tank.plist");
	_tank->setPosition(100, 400);
	addChild(_tank);
}

Sprite *s2 = nullptr;
Path clp = {
	IntPoint(45, 0),
	IntPoint(41, -16),
	IntPoint(32, -31),
	IntPoint(21, -40),
	IntPoint(0, -45),
	IntPoint(-19, -42),
	IntPoint(-34, -32),
	IntPoint(-45, -17),
	IntPoint(-48, 1),
	IntPoint(-45, 19),
	IntPoint(-34, 33),
	IntPoint(-18, 44),
	IntPoint(0, 47),
	IntPoint(17, 43),
	IntPoint(32, 32),
	IntPoint(43, 18)
};
Implemention(2) {

	s2 = Sprite::create();
	s2->setContentSize(Size(300, 300));
	s2->setPhysicsBody(PhysicsBody::createBox(Size(300, 300)));
	s2->setPosition(_center.x, s2->getContentSize().height/2);
	s2->getPhysicsBody()->setDynamic(false);
	addChild(s2);


}

Path TestLayer::shapeToPath(PhysicsShapePolygon *shape) {

	Path p;
	for (int i = 0; i < shape->getPointsCount(); i++) {
		Point ver = shape->getPoint(i);
		p.push_back(IntPoint(ver.x, ver.y));
	}
	return p;
}

Paths TestLayer::shapesToPaths(const Vector<PhysicsShape*>& shapes) {

	Paths ret;
	for (auto shape : shapes) {
		PhysicsShapePolygon *polygon = dynamic_cast<PhysicsShapePolygon*>(shape);
		if (polygon) {
			ret.push_back(shapeToPath(polygon));
		} else {
			CCLOG("Warnging: shape is not a polygon");
		}
	}
	return ret;
}

PhysicsShapePolygon* TestLayer::pathToShape(ClipperLib::Path &p) {

	Vec2 *points = new Vec2[p.size()];
	for (int i = 0; i < p.size(); i++) {
		points[i] = Point(p[i].X, p[i].Y);
	}
	PhysicsShapePolygon *ret = PhysicsShapePolygon::create(points, p.size());
	delete [] points;
	return ret;
}


Path TestLayer::addOffsetToPath(Path &p, const Point &offset) {

	Path ret;
	for (int i = 0; i < p.size(); i++) {
		ret.push_back(IntPoint(p[i].X + offset.x, p[i].Y + offset.y));
	}
	return ret;
}

void TestLayer::drawPath(Path &p) {

	Vec2 *points = new Vec2[p.size()];
	for (int i = 0; i < p.size(); i++) {
		points[i] = Point(p[i].X, p[i].Y);
	}

	_draw->clear();
	_draw->drawPolygon(points, p.size(), Color4F(0, 255, 0, 0), 1, Color4F::WHITE);
	delete [] points;
}

void TestLayer::printPath(Path &p) {

	CCLOG("print path: %p", &p);
	for (auto &point : p) {
		CCLOG("%lld, %lld", point.X, point.Y);
	}
}

void TestLayer::validWinding(cocos2d::Vec2 *points, int size) {

	for(int i=0; i<size; i++){
		Vec2 &a = points[i];
		Vec2 &b = points[(i+1)%size];
		Vec2 &c = points[(i+2)%size];

		Vec2 t = b-a;
		Vec2 t1 = c-a;

		if(t.x*t1.y-t.y*t1.x > 0.0f){
			for (int j = 0; j < size/2; j++) {
				CC_SWAP(points[j], points[size-1-j], Vec2);
			}
			break;
		}
	}
}

bool TestLayer::isValid(cocos2d::Vec2 *points, int size) {

	for(int i=0; i<size; i++){
		Vec2 &a = points[i];
		Vec2 &b = points[(i+1)%size];
		Vec2 &c = points[(i+2)%size];

		Vec2 t = b-a;
		Vec2 t1 = c-a;

		if(t.x*t1.y-t.y*t1.x > 0.0f){
			return false;
		}
	}
	return true;
}


Implemention(1) {

	Path sub = {
		IntPoint(100, 100),
		IntPoint(300, 100),
		IntPoint(300, 200),
		IntPoint(100, 200)
	};

	drawPath(sub);

	Path clp = {
		IntPoint(150, 150),
		IntPoint(250, 150),
		IntPoint(250, 250),
		IntPoint(150, 250)
	};

	Path big = {
		IntPoint(50, 50),
		IntPoint(350, 50),
		IntPoint(350, 250),
		IntPoint(50, 250)
	};

	drawPath(big);

	Clipper clip;
	clip.AddPath(sub, ptSubject, true);
	clip.AddPath(big, ptClip, true);
	Paths solution;
	clip.Execute(ctDifference, solution);

	if (solution.empty()) {
		CCLOG("solution is empty");
	}

	for (auto &path : solution) {
		for (auto &p : path) {
			CCLOG("p: %lld, %lld", p.X, p.Y);
		}
		drawPath(path);
	}
}


#pragma mark

Scene* TestLayer::scene() {
	Scene *scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Point(0, -100));
	//	scene->getPhysicsWorld()->setDebugDrawMask(1);

	TestLayer *layer = TestLayer::create();
	scene->addChild(layer);
	return scene;
}

bool TestLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	_win = Director::getInstance()->getWinSize();
	_center = Point(_win.width/2, _win.height/2);
	LayerColor *lc = LayerColor::create(Color4B::GRAY, _win.width, _win.height);
	addChild(lc, -1);

	_draw = DrawNode::create();
	addChild(_draw, 10);

	EventListenerTouchOneByOne *touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TestLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(TestLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TestLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


	setPhysicsBody(PhysicsBody::createEdgeBox(_win));
	getPhysicsBody()->setPositionOffset(_win/2);

	test();

	return true;
}



bool TestLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {

	return true;
}

void TestLayer::onTouchMoved(Touch *pTouch, Event *pEvent) {


}

void TestLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {

	CCLOG(__FUNCTION__);

	switch (CUR_TEST) {

		case 1:

			break;

		case 2: {

			//			((Scene*)getParent())->getPhysicsWorld()->setDebugDrawMask(0);

			Paths subs = shapesToPaths(s2->getPhysicsBody()->getShapes());

			// combine paths
			Path subject = subs[0];
			for (int i = 1; i < subs.size(); i++) {
				Clipper clip;
				clip.AddPath(subject, ptSubject, true);
				clip.AddPath(subs[i], ptClip, true);
				Paths solution;
				bool ret = clip.Execute(ctUnion, solution);
				subject = solution[0];
				CCLOG("combine ret: %d", ret);
			}


			Path clp2 = addOffsetToPath(clp, pTouch->getLocation()-s2->getPosition());

			s2->getPhysicsBody()->removeAllShapes();
			_draw->clear();

			//			for (auto &sub : subs) {

			Clipper clip;
			clip.AddPath(subject, ptSubject, true);
			clip.AddPath(clp2, ptClip, true);
			Paths solution;
			clip.Execute(ctDifference, solution);

			if (solution.empty()) {
				CCLOG("no solution");
				//					continue;
				return;
			}


			for (auto &solu : solution) {

				vector<p2t::Point*> vertexs;
				for (auto &point : solu) {
					vertexs.push_back(new p2t::Point(point.X, point.Y));
				}

				p2t::CDT cdt(vertexs);
				cdt.Triangulate();
				vector<p2t::Triangle*> triangles = cdt.GetTriangles();

				for (auto triangle : triangles) {
					Vec2 *points = new Vec2[3];
					for (int i = 0; i < 3; i++) {
						p2t::Point *p = triangle->GetPoint(i);
						points[i] = Vec2(p->x, p->y);
					}

					validWinding(points, 3);
					if (!isValid(points, 3)) {
						continue;
					}

					CCLOG("Triangle: (%g, %g), (%g, %g), (%g, %g)", points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y);

					PhysicsShapePolygon *shape = PhysicsShapePolygon::create(points, 3);
					s2->getPhysicsBody()->addShape(shape);


					//						for (int i = 0; i < 3; i++) {
					//							points[i] += s2->getPosition();
					//						}
					//						_draw->drawPolygon(points, 3, Color4F(0, 255, 0, 255), 1, Color4F::BLACK);


					delete [] points;
				}
			}
			//			}
		}

		case 3: {

			Paths subs = shapesToPaths(_desert->getPhysicsBody()->getShapes());

			// combine paths
			//			Path subject = subs[0];
			//			for (int i = 1; i < subs.size(); i++) {
			//				Clipper clip;
			//				clip.AddPath(subject, ptSubject, true);
			//				clip.AddPath(subs[i], ptClip, true);
			//				Paths solution;
			//				bool ret = clip.Execute(ctUnion, solution);
			//				subject = solution[0];
			//				CCLOG("combine ret: %d", ret);
			//			}


			Path clp2 = addOffsetToPath(clp, pTouch->getLocation()-_desert->getPosition());

			_desert->getPhysicsBody()->removeAllShapes();
			_draw->clear();

			for (auto &sub : subs) {

				Clipper clip;
				clip.AddPath(sub, ptSubject, true);
				clip.AddPath(clp2, ptClip, true);
				Paths solution;
				clip.Execute(ctDifference, solution);

				if (solution.empty()) {
					CCLOG("no solution");
					continue;
				}


				for (auto &solu : solution) {

					vector<p2t::Point*> vertexs;
					for (auto &point : solu) {
						vertexs.push_back(new p2t::Point(point.X, point.Y));
					}

					p2t::CDT cdt(vertexs);
					cdt.Triangulate();
					vector<p2t::Triangle*> triangles = cdt.GetTriangles();

					for (auto triangle : triangles) {
						Vec2 *points = new Vec2[3];
						for (int i = 0; i < 3; i++) {
							p2t::Point *p = triangle->GetPoint(i);
							points[i] = Vec2(p->x, p->y);
						}

						validWinding(points, 3);
						if (!isValid(points, 3)) {
							continue;
						}


						PhysicsShapePolygon *shape = PhysicsShapePolygon::create(points, 3);
						_desert->getPhysicsBody()->addShape(shape);
						
						
						delete [] points;
					}
				}
				
			}
		}
			
		case 5: {
			t5();
			break;
		}
			
		case 6: {
			t6();
			break;
		}
			
		case 7: {
			t7();
			break;
		}

		case 8: {
			t8();
			break;
		}

		case 9: {
			t9();
			break;
		}

		case 10: {
			t10();
			break;
		}
			
		default:
			break;
	}
	
	
}
