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

#ifndef CRASHFS_FILE_H
#define CRASHFS_FILE_H

#include "ittia/os/os_config.h"

#ifdef HAVE_CRASHFS_FILE

#include "ittia/os/os_limits.h"
#include "ittia/os/os_file.h"

C_HEADER_BEGIN

/* Error code used when crashfs forces the program to exit. */
#define OS_CRASHFS_FILE_EXIT_CODE 77

/* All writes are performed normally. */
#define OS_CRASHFS_STATE_NORMAL 0
/* Counting down flushes until crashing. */
#define OS_CRASHFS_STATE_COUNTDOWN 1
/* Simulating a crash: some writes may not persist. */
#define OS_CRASHFS_STATE_CRASHING 2

typedef struct crashfs_file_t
{
    /* If a file is crashing, program must exit on close or flush. */
    uint8_t state;

    os_file_t wrapped_file;
    char file_name[OS_MAX_PATH + 1];

    uint32_t flush_count;
    uint32_t min_flushes;

    /* Buffer file contents in memory. */
    uint8_t * contents_buffer;
    db_off_t contents_buffer_size;
    db_off_t file_size;
    db_off_t stream_offset;

} crashfs_file_t;


typedef struct crashfs_config_t
{
    /* If program is crashing, any file can start crashing too. */
    uint8_t state;

    char file_name[OS_MAX_PATH + 1];
    uint32_t flushes;
    uint32_t crash_probability_inverse;
} crashfs_config_t;


DBDLL_API int os_get_crashfs_config(crashfs_config_t *);
DBDLL_API int os_set_crashfs_config(const crashfs_config_t *);

C_HEADER_END

#endif /* HAVE_CRASHFS_FILE */

#endif /* CRASHFS_FILE_H */
