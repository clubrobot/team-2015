/*
 * olog.h
 *
 *  Created on: Nov 12, 2015
 *      Author: gabriel
 */

#ifndef LOG_OLOG_H_
#define LOG_OLOG_H_

#include <ostream>

class olog: public std::ostream {
public:
	olog();
	virtual ~olog();
};

#endif /* LOG_OLOG_H_ */
