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

#ifndef UCFS_FILE_H
#define UCFS_FILE_H

#include "ittia/os/os_config.h"

#ifdef HAVE_UCFS_FILE

#ifdef HAVE_THREADS
/* since many C compilers have POSIX file I/O, we would use
 * platform independent mutexes
 */
#	include "ittia/os/os_mutex.h"

#endif

#include "ittia/os/os_limits.h"

typedef struct ucfs_file_t
{
    void* hdata;

#ifdef HAVE_THREADS
    os_mutex_t cs;
#endif

    /* non zero when is file was opened read-only */
    int read_only;

    uint32_t block_size;
} ucfs_file_t;

#endif /* HAVE_UCFS_FILE */

#endif /* UCFS_FILE_H */
