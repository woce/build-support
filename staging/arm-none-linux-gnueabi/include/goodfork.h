
/** 
* @brief Spawns a child whose execution begins with fn(arg),
*        and ends with the termination of fn(arg)
*
*        Note that the behavior is different than fork() in
*        that no atfork() handlers would get called and execution
*        in the child does not continue after the fork(), but rather
*        from fn(arg).
*
*        THIS FUNCTION MUST BE USED INSTEAD OF FORK in a multi-threaded
*        app.  This is due to a bug in the toolchain with gcc < 4.3
*
* @param  fn 
* @param  arg 
* 
* @retval pid of child or -1 for error.
*/
int good_fork(int (*fn)(void *), void *arg);

/** 
* @brief Spawns a child to run cmdline and waits for termination of cmdline.
*
*        Almost like good old system().
* 
* @param  cmdline 
* 
* @retval
*/
int good_system(const char *cmdline);

/** 
* @brief Spawns a process with args[] where args[0] is the name of the binary
*        to be run.
*
*        A better version than system() that does near equivalent of
*        fork()+execv().
* 
* @param  args 
* 
* @retval pid of child or -1 on error.
*/
int good_spawn(char * const args[]);
