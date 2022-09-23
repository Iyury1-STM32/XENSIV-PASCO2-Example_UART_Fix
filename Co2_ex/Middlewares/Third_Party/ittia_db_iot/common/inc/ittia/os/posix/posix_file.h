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

#ifndef POSIX_FILE_H
#define POSIX_FILE_H

#include "ittia/os/os_config.h"

#ifdef HAVE_POSIX_FILE

#ifdef HAVE_THREADS
/* since many C compilers have posix file I/O, we would use
 * platform independent mutexes
 */
#	include "ittia/os/os_mutex.h"

#endif /* HAVE_THREADS */

#include "ittia/os/os_limits.h"

typedef struct posix_file_t
{
    int hdata;

#ifdef HAVE_THREADS
    os_mutex_t cs;
#endif /* HAVE_THREADS */

    /* non zero is file was opened read-only */
    int read_only;
#ifdef HAVE_REALPATH
    char file_name[OS_MAX_PATH + 1];
#endif
} posix_file_t;

#endif /* HAVE_POSIX_FILE */

#endif /* POSIX_FILE_H */
