/*
 * Color.h
 *
 *  Created on: 1 déc. 2015
 *      Author: ethel
 */

#ifndef LOG_COLOR_H_
#define LOG_COLOR_H_

#include <ostream>

class Color {
public:
	enum Code {
		FG_RED      = 31,
		FG_GREEN    = 32,
		FG_YELLOW	= 33,
		FG_BLUE     = 34,
		FG_MAGENTA  = 35,
		FG_DEFAULT  = 39,
	};
protected:
	Code code;
public:
	Color(Code pCode);
	friend std::ostream& operator<<(std::ostream& os, const Color& mod) {
		return os << "\033[" << mod.code << "m";
	}

};

#endif /* LOG_COLOR_H_ */
