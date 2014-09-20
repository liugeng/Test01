//
//  Global.h
//  Test01
//
//  Created by liu geng on 14-9-11.
//
//

#ifndef __Test01__Global__
#define __Test01__Global__

#include <iostream>
#include <vector>
#include <string>



#define TIME_INIT(str) \
uint64_t debug_t0, debug_t1, debug_t2;\
timeval debug_tv;\
std::string debug_str = str;\
gettimeofday(&debug_tv, 0);\
debug_t0 = debug_t1 = debug_tv.tv_sec * 1000 + debug_tv.tv_usec / 1000;\
CCLOG("【 --- %s --- 】\n", str);\

#define TIME_PRINT(str) {\
	gettimeofday(&debug_tv, 0);\
	debug_t2 = debug_tv.tv_sec * 1000 + debug_tv.tv_usec / 1000;\
	CCLOG("【 (%s) %s: %lld 】\n", debug_str.c_str(), str, debug_t2 - debug_t1);\
	debug_t1 = debug_t2;\
}

#define TIME_TOTAL() {\
	gettimeofday(&debug_tv, 0);\
	debug_t2 = debug_tv.tv_sec * 1000 + debug_tv.tv_usec / 1000;\
	CCLOG("【 --- (%s) total: %lld --- 】\n\n", debug_str.c_str(), debug_t2 - debug_t0);\
}



#define LogVec2(__des__, __vec2__) \
CCLOG("%s: (%g, %g)", __des__, __vec2__.x, __vec2__.y);

#define LogRect(__des__, __rect__) \
CCLOG("%s: (%g, %g, %g, %g)", __des__, __rect__.origin.x, __rect__.origin.y, __rect__.size.width, __rect__.size.height)

/**
 *	切割字符串
 */
extern std::vector<std::string> ClipStr(const std::string& str, const char *pSign);

#endif /* defined(__Test01__Global__) */
