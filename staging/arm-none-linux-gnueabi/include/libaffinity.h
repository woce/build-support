// @@@LICENSE
//
//      Copyright (c) 2011-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Set CPU affinity of individual thread.
 *
 * Uses libaffinity to set CPU affinity of an individual thread. Use this instead of
 * sched_setaffinity so that CPU affinity can be managed dynamically: if a CPU is
 * removed for the scheduler's benefit, libaffinity will ensure that affinity is
 * re-established if the CPU is restored.
 *
 * Setting affinity does not pin the cpu and prevent it from being removed.
 *
 * Affinity is not the best term: the thread is forced to run from that CPU, when
 * present, and cannot migrate away. Affinity is not just a suggestion.
 *
 * Affinity can only set to a single CPU at a time: arbitrary ranges or sets of
 * CPUs can not be chosen. Affinity can be specified for a CPU which is not
 * currently available, in which case it will pend.
 *
 * If an affined CPU is not available, the thread will run on CPU0 until the
 * CPU is available. CPU0 is not removable.
 *
 * The pid argument is properly a 'tid' or thread-id. A pid will serve, however
 * only ever one thread/process is affined: if you give your own pid, your
 * primary thread will be affined, but not any secondary threads that already
 * exist.
 *
 * Affinity will be inherited by threads cloned or forked from the affined thread.
 *
 * @param	pid	A pid or thread id (returned by the mythical gettid(). 
 *			The value returned by pthread_self() is not usable for this.)
 *			0 may be supplied, and indicates that the current pid be used.
 * @param	cpu	A numeric CPU number. 0 is the first CPU, use 1 or higher for
 *			other CPUs. 
 * @return		0 for success, or -1 for a failure. Failures are not further defined. errno may be useful.
 *
 */
int libaffinity_set_affinity(int pid, int cpu);

/** @brief Reset CPU affinity of individual thread.
 *
 * Uses libaffinity to reset CPU affinity of individual thread, so that it may run
 * on any available CPU. This is the default state of threads in the system.
 *
 * @param	pid	A pid or thread id (returned by the mythical gettid(). 
 *			The value returned by pthread_self() is not usable for this.)
 *			0 may be supplied, and indicates that the current pid be used.
 * @return		0 for success, or -1 for a failure. Failures are not further defined. errno may be useful.
 *
 */
int libaffinity_reset_affinity(int pid);

/** @brief Get CPU affinity of individual thread.
 *
 * Uses libaffinity to determine the CPU affinity of an individual thread,
 * based on prior settings with libaffinity.  This primary supported usage
 * of this routine is for a library to determine the affinity of the process
 * it is running in, on the assumption that the caller may have previously
 * set the affinity of the process.  Other usages are unsupported.
 *
 * @param	pid	A pid or thread id (returned by the mythical gettid(). 
 *			The value returned by pthread_self() is not usable for this.)
 *			0 may be supplied, and indicates that the current pid be used.
 *
 * @param	affined	A pointer to an int. If non-null, this will receive a value of 0 or 1, indicating whether the thread
 *			has a set affinity.

 * @param	cpu	A pointer to an int. If non-null, this will receive a numeric CPU number. 0 is the first CPU, use 1 or higher for
 *			other CPUs. The program may not actually be running on this CPU if that CPU is not available. Please see pending.
 *
 * @param	pending	A pointer to an int. If non-null, this will receive a value of 0 or 1, indicating whether the thread
 *			is currently running on its affined CPU, or is running on CPU0 pending the affined CPU being available. DO NOT
 *			USE THIS VALUE! It is only provided for diagnostic purposes: in normal operation, a program may switch in and out of
 *			its target CPU at any time, making the pending value unpredictable and inappropriate for programmatic usage.

 * @return		0 for success, or -1 for a failure. Failures are not further defined. errno may be useful.
 */
int libaffinity_get_affinity(int pid, int *affined, int *cpu, int *pending);

/** @brief Get count of CPUs available.
 *
 * Deterimines how many CPUs are available in the system. This provides N for other libaffinity
 * APIs which take or return CPU numbers 0 through N-1. Not all of these CPUs may currently be
 * running.
 *
 * This routine does not return an error case: if anything goes wrong, it will report at least
 * one CPU.
 *
 * @return		A number of CPUs, 1 or greater. In case of error, 1 will be returned.
 *
 */
int libaffinity_get_cpu_count();

#ifdef __cplusplus
};
#endif
