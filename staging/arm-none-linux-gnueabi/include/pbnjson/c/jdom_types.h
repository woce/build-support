/* @@@LICENSE
*
*      Copyright (c) 2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
LICENSE@@@ */

/*
 * jparse_types.h
 *
 *  Created on: Sep 24, 2009
 */

#ifndef JDOM_TYPES_H_
#define JDOM_TYPES_H_

#include "jcallbacks.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The assumptions that can be made while parsing the input to build the JSON value in memory.
 * This allows the library to pick certain optimization strategies that may be faster but less
 * safe depending on what format the input takes.
 */
typedef enum {
	/**
	 * Make no assumptions about the input - safest.  Use this if you are unsure about the characteristics of the
	 * relationship between the input & the DOM object that gets generated, use this.
	 */
	DOMOPT_NOOPT = 0,
	/**
	 * Inidicates that the lifetime of the input buffer outlives
	 * when the DOM object is freed completely.
	 * NOTE: This includes copies as well.
	 */
	DOMOPT_INPUT_OUTLIVES_DOM = 1,
	/**
	 * Indicates that the input buffer will not be modified.
	 */
	DOMOPT_INPUT_NOCHANGE = 2,
	/**
	 * Indicates that the input buffer is actually NULL terminated.  Thus the actual allocated buffer in the raw_buffer
	 * structure will be m_len + 1 (m_str[m_len] is 0)
	 */
	DOMOPT_INPUT_NULL_TERMINATED,
} JDOMOptimization;

/**
 * The combination of both conditions allows us to ensure
 * that it is safe to create the DOM without actually copying anything out of the input string.
 */
#define DOMOPT_INPUT_OUTLIVES_WITH_NOCHANGE (DOMOPT_INPUT_OUTLIVES_DOM | DOMOPT_INPUT_NOCHANGE)

/**
 * Convenience type representing a bit-wise combination of ::JDOMOptimization values.
 */
typedef unsigned int JDOMOptimizationFlags;

typedef enum {
	JFileOptNoOpt = 0
	, JFileOptMMap = 1
} JFileOptimization;

typedef unsigned int JFileOptimizationFlags;

#ifdef __cplusplus
}
#endif

#endif /* JDOM_TYPES_H_ */
