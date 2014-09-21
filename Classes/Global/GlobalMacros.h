//
//  GlobalMacros.h
//  Test01
//
//  Created by liugeng on 14-9-20.
//
//

#ifndef Test01_GlobalMacros_h
#define Test01_GlobalMacros_h

/**
 *  打印时间消耗
 *  TIME_INIT("...")
 *	do something
 *	TIME_PRINT("...")
 *	...
 *	TIME_TOTAL()
 */
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


/**
 *  打印二维向量
 */
#define LogVec2(__des__, __vec2__) \
CCLOG("%s: (%g, %g)", __des__, __vec2__.x, __vec2__.y);

/**
 *  打印Rect
 */
#define LogRect(__des__, __rect__) \
CCLOG("%s: (%g, %g, %g, %g)", __des__, __rect__.origin.x, __rect__.origin.y, __rect__.size.width, __rect__.size.height)

#endif
