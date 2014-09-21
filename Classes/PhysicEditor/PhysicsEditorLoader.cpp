//
//  PhysicsEditorLoader.cpp
//  Test01
//
//  Created by liu geng on 14-9-11.
//
//

#include "PhysicsEditorLoader.h"

using std::string;
using std::vector;

Sprite* PhysicsEditorLoader::load(const char *file) {

	do {
		string fullpath = FileUtils::getInstance()->fullPathForFilename(file);
		CCLOG("%s: %s", __func__, fullpath.c_str());
		ValueMap dic = FileUtils::getInstance()->getValueMapFromFile(fullpath.c_str());
		if (dic.empty()) {
			CCLOG("read file failed: %s", fullpath.c_str());
			break;
		}

		CC_BREAK_IF(noMember(dic, "bodies"));

		ValueMap bodies = dic["bodies"].asValueMap();
		string name = bodies.begin()->first;

		Sprite *sp = Sprite::create((name+".png").c_str());

		ValueMap image = bodies[name.c_str()].asValueMap();

		if (isMember(image, "anchorpoint")) {
			string anchor = bodies["anchorpoint"].asString();
			//sp->setAnchorPoint(PointFromString(anchor));
		}

		CC_BREAK_IF(noMember(image, "fixtures"));

		ValueVector fixtures = image["fixtures"].asValueVector();

		for (auto &vec : fixtures) {

			ValueMap item = vec.asValueMap();
			CC_BREAK_IF(noMember(item, "polygons"));

			ValueVector polygons = item["polygons"].asValueVector();

			if (!polygons.empty()) {
				sp->setPhysicsBody(PhysicsBody::create());
				//sp->getPhysicsBody()->setPositionOffset(-1*sp->getContentSize()/2);
			}

			for (auto &poly : polygons) {

				ValueVector points = poly.asValueVector();
				Point *p = new Point[points.size()];
				for (int i = 0; i < points.size(); i++) {
					p[i] = PointFromString(points[i].asString());
					//CCLOG("point: %g, %g", p[i].x, p[i].y);
				}

				sp->getPhysicsBody()->addShape(PhysicsShapePolygon::create(p, points.size()));
				delete [] p;
			}
		}

		return sp;

	} while (0);

	return nullptr;
}

bool PhysicsEditorLoader::isMember(ValueMap &map, const char *member) {

	return (map.find(member) != map.end());
}

bool PhysicsEditorLoader::noMember(ValueMap &map, const char *member) {

	if (!isMember(map, member)) {
		CCLOG("xml no member: %s", member);
		return true;
	}
	return false;
}

