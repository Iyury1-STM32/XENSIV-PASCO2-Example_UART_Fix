/**************************************************************************/
/*                                                                        */
/*      Copyright (c) 2005-2011 by ITTIA L.L.C. All rights reserved.      */
/*                                                                        */
/*  This software is copyrighted by and is the sole property of ITTIA     */
/*  L.L.C.  All rights, title, ownership, or other interests in the       */
/*  software remain the property of ITTIA L.L.C.  This software may only  */
/*  be used in accordance with the corresponding license agreement.  Any  */
/*  unauthorized use, duplication, transmission, distribution, or         */
/*  disclosure of this software is expressly forbidden.                   */
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */
/*  written consent of ITTIA L.L.C.                                       */
/*                                                                        */
/*  ITTIA L.L.C. reserves the right to modify this software without       */
/*  notice.                                                               */
/*                                                                        */
/*  info@ittia.com                                                        */
/*  http://www.ittia.com                                                  */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

#ifndef OS_FAIL_H
#define OS_FAIL_H

#include "ittia/os/os_config.h"

#ifdef DB_ENABLE_FAILURE

#include "ittia/os/os_dump.h"

/* simple failure simulation framework.
 * The idea is to perform random failures on several services.
 * library calls fs_failure() to check if it is necessary to fail.
 * the fs_failure() would fork the process and return true in
 * the child process. at the same time child process becomes non-safe
 * i.e. it should not affect the external state somehow.
 * this could be checked calling fs_safe(). it would return non-zero
 * then it is safe to modify the external state and zero if not.
 */
enum
{
    FS_MALLOC,
    FS_FILE_OPEN,
    FS_FILE_READ,
    FS_FILE_WRITE,
    FS_FILE_FLUSHING,
    FS_FILE_FLUSH,
    FS_MAX,
};

typedef enum
{
    FS_ACTION_NONE,
    FS_ACTION_FORK,
    FS_ACTION_EXEC,
    FS_ACTION_QUIT,
    FS_ACTION_FAIL,
    FS_ACTION_IGNORE
} fs_Action;

/* execution stages */
enum
{
    FS_PREPARE, FS_TEST, FS_CLEANUP, FS_DONE
};

C_LINKAGE DBDLL_API int fs_setup(const char * mode_string);
C_LINKAGE DBDLL_API void fs_stage(int);
C_LINKAGE DBDLL_API int fs_failure(int service);
C_LINKAGE DBDLL_API int fs_check(int service);
C_LINKAGE DBDLL_API int fs_safe(void);

C_LINKAGE DBDLL_API void fs_process_disable(void);
C_LINKAGE DBDLL_API void fs_process_enable(void);

C_LINKAGE DBDLL_API void fs_thread_disable(void);
C_LINKAGE DBDLL_API void fs_thread_enable(void);

C_LINKAGE DBDLL_API int fs_process_set(const char *, const char *);
C_LINKAGE DBDLL_API int fs_thread_set(const char *, const char *);

#ifdef DB_DEBUG
#define FS_CHECK(service)                   (fs_failure(service) ? os_trace_output(__FILE__, __LINE__, -1, "Simulating failure"), DB_EDBGFAILURE : DB_NOERROR)
#define FS_THROW_RES(service, result)       if (!fs_failure(service)) {} else return os_trace_output(__FILE__, __LINE__, -1, "Simulating failure"), result
#else
#define FS_CHECK(service)                   (fs_failure(service) ? DB_EDBGFAILURE : DB_NOERROR)
#define FS_THROW_RES(service, result)       if (!fs_failure(service)) {} else return result
#endif

C_LINKAGE int  fs_begin(void);
C_LINKAGE int  fs_done(void);
C_LINKAGE int  fs_enable_break(int service);
C_LINKAGE int  fs_disable_break(int service);
C_LINKAGE int  fs_set_break(int service, long count, fs_Action);
C_LINKAGE int  fs_have_break(int service);
C_LINKAGE long fs_reset_break_count(int service);
C_LINKAGE long fs_get_break_count(int service);
C_LINKAGE long fs_get_cur_count(int service);
C_LINKAGE void fs_set_guard_frame(void);
C_LINKAGE void fs_reset_guard_frame(void);

#else

#define fs_failure(service)     (0)
#define fs_safe()               (!0)
#define FS_CHECK(service)       (DB_NOERROR)
#define FS_THROW_RES(service, result)

#endif /* DB_ENABLE_FAILURE */

#endif /* OS_FAIL_H */
