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

/**
 * @file
 *
 * ITTIA DB file I/O interface using fopen from stdio.h.
 */
#ifndef STDIO_FILE_H
#define STDIO_FILE_H

#include "ittia/os/os_config.h"

#ifdef HAVE_STDIO_FILE

#ifdef HAVE_THREADS
#include "ittia/os/os_mutex.h"
#endif

#include <ittia/os/std/io.h>

#ifndef HAVE_STDIO_H
#error Must define HAVE_STDIO_H to use the stdio file interface.
#endif

C_HEADER_BEGIN

/**
 * Information about an open file or other collection of blocks.
 */
typedef struct stdio_file_t
{
    /** File handle or other unique identifier. */
    FILE* fhandle;

#ifdef HAVE_THREADS
    os_mutex_t cs;
#endif

} stdio_file_t;

C_HEADER_END

#endif /* HAVE_STDIO_FILE */

#endif /* STDIO_FILE_H */
