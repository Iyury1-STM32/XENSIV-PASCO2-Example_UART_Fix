/**************************************************************************/
/*                                                                        */
/*      Copyright (c) 2005-2018 by ITTIA L.L.C. All rights reserved.      */
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

/**
 * @file
 *
 * FatFS file I/O interface.
 *
 * http://elm-chan.org/fsw/ff/00index_e.html
 */
#ifndef FATFS_FILE_H
#define FATFS_FILE_H

#include "ittia/os/os_config.h"

#ifdef HAVE_FATFS_FILE

#ifdef HAVE_THREADS
#include "ittia/os/os_mutex.h"
#endif

#include "ff_gen_drv.h"

C_HEADER_BEGIN

/**
 * Information about an open file or other collection of blocks.
 */
typedef struct fatfs_file_t
{
    /** File object. */
    FIL fhandle;

#ifdef HAVE_THREADS
    os_mutex_t cs;
#endif

} fatfs_file_t;

C_HEADER_END

#endif /* HAVE_FATFS_FILE */

#endif /* __FATFS_FILE_H__ */
