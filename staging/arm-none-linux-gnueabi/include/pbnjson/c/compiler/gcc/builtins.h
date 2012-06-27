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

#if !__cplusplus
	#define COMPILER_CHOOSE_EXPR(condition, expr1, expr2) __builtin_choose_expr(condition, expr1, expr2)
	#define COMPILER_TEST_TYPE_COMPATIBLE(type1, type2) __builtin_types_compatible_p(type1, type2)
#endif

#define COMPILER_ISCONSTANT(var_or_value) __builtin_constant_p(var_or_value)
#define COMPILER_PREFETCH(address, rw, locality) __builtin_prefetch(address)
#define COMPILER_EXPECT(value1, value2) __builtin_expect(value1, value2)

#if __PJ_MINIMUM_GCC_VERSION(3, 3, 0)
	#define DBL_QUIET_NAN __builtin_nan("")
#endif

#if HAVE_GCC_ATOMICS
	#define ATOMIC_ADD(addr, val) __sync_add_and_fetch(addr, val)
	#define ATOMIC_SUB(addr, val) __sync_sub_and_fetch(addr, val)
#endif
