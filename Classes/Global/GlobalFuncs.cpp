//
//  GlobalFuncs.cpp
//  Test01
//
//  Created by liugeng on 14-9-20.
//
//

#include "GlobalFuncs.h"

/**
 *	切割字符串
 */
std::vector<std::string> ClipStr(const std::string& str, const char *pSign) {
	
	char *s = new char[str.length()+1];
	memcpy(s, str.c_str(), str.length());
	s[str.length()] = '\0';
	std::vector<std::string> ret;
	if (str.length()) {
		char *e = strtok(s, pSign);
		if (e) {
			ret.push_back(e);
		} else {
			ret.clear();
			delete [] s;
			return ret;
		}
		
		while (char *e = strtok(NULL, pSign)) {
			ret.push_back(e);
		}
	}
	delete [] s;
	return ret;
}
