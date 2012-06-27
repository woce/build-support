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

#ifndef BUILTIN_H_
#define BUILTIN_H_

#ifdef __GNUC__
#include "gcc/builtins.h"
#endif

#ifdef COMPILER_CHOOSE_EXPR
	#define COMPILER_HAS_CHOOSE_EXPR 1
#else
	#define COMPILER_HAS_CHOOSE_EXPR 0
#endif

#ifdef COMPILER_TEST_TYPE_COMPATIBLE
	#define COMPILER_HAS_TEST_TYPE_COMPATIBLE 1
#else
	#define COMPILER_HAS_TEST_TYPE_COMPATIBLE 0
#endif

#ifdef COMPILER_ISCONSTANT
	#define COMPILER_HAS_ISCONSTANT 1
#else
	#define COMPILER_HAS_ISCONSTANT 0
#endif

#ifdef COMPILER_EXPECT
	#define LIKELY(condition) COMPILER_EXPECT(condition, 1)
	#define UNLIKELY(condition) COMPILER_EXPECT(condition, 0)
#else
	#define LIKELY(condition) (condition)
	#define UNLIKELY(condition) (condition)
#endif

#ifdef COMPILER_PREFETCH
	#define PREFETCH(address) COMPILER_PREFETCH(address)
#else
	#define PREFETCH(address) do {} while (0)
#endif

// some fixups for atomics in case the builtins are defined lazily
#if !defined(ATOMIC_SUB) && !defined(ATOMIC_ADD)
	#if _DEBUG && !ATOMICS_NECESSARY
		// no atomics - in debug mode we can fake this
		#define ATOMIC_SUB(addr, value) ((*addr) -= value)
		#define ATOMIC_ADD(addr, value) ((*addr) += value)
	#endif
#elif !defined(ATOMIC_ADD)
	// define ATOMIC_ADD in terms of sub
	#define ATOMIC_ADD(addr, value) ATOMIC_SUB(addr, -value)
#elif !defined(ATOMIC_SUB)
	// define ATOMIC_SUB in terms of add
	#define ATOMIC_SUB(addr, value) ATOMIC_ADD(addr, -value)
#endif

#if !defined(ATOMIC_SUB) || !defined(ATOMIC_ADD)
	#if ATOMICS_NECESSARY
		#error "No atomics provided - they may be necessary"
	#endif
#endif

#define ATOMIC_INC(addr) ATOMIC_ADD(addr, 1)
#define ATOMIC_DEC(addr) ATOMIC_SUB(addr, 1)

#endif /* BUILTIN_H_ */
