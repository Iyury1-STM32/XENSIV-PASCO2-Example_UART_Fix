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

/* @file
 *
 * Mutexes
 */

#ifndef OS_MUTEX_H
#define OS_MUTEX_H

#include "ittia/os/os_config.h"

#ifdef HAVE_THREADS

#if defined(HAVE_WIN32_THREADS)
#   include "ittia/os/win32/win32_mutex.h"
#elif defined(HAVE_VXWORKS_MUTEX)
#   include "ittia/os/vxworks/vxworks_mutex.h"
#elif defined(HAVE_POSIX_MUTEX)
#   include "ittia/os/posix/posix_mutex.h"
#elif defined(HAVE_FREERTOS_THREADS)
#   include "ittia/os/freertos/ittia_freertos_mutex.h"
#elif defined(HAVE_THREADX_THREADS)
#   include "ittia/os/threadx/threadx_mutex.h"
#elif defined(HAVE_UCOS_II_THREADS)
#   include "ittia/os/ucos_ii/ucos_ii_mutex.h"
#elif defined(HAVE_UCOS_III_THREADS)
#   include "ittia/os/ucos_iii/ucos_iii_mutex.h"
#else
#   include "ittia/os/generic/generic_mutex.h"
#endif 

C_HEADER_BEGIN

DBDLL_API int os_mutex_init(os_mutex_t * mutex);
DBDLL_API int os_mutex_destroy(os_mutex_t * mutex);
DBDLL_API int os_mutex_trylock(os_mutex_t * mutex);
DBDLL_API int os_mutex_lock(os_mutex_t * mutex);
DBDLL_API int os_mutex_unlock(os_mutex_t * mutex);

C_HEADER_END

#endif /* HAVE_THREADS */

#endif /* OS_MUTEX_H */
