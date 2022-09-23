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

#ifndef RAMFS_FILE_H
#define RAMFS_FILE_H

#include "ittia/os/os_config.h"

#ifdef HAVE_RAMFS_FILE

#include "ittia/os/std/windows.h"

C_HEADER_BEGIN

/* quick and dirty ramfs implementation.
 * not thread safe!
 */

typedef struct ramfs_file_t
{
    struct ramfs_file_data_t * file;
    db_size_t pos;
} ramfs_file_t;

C_HEADER_END

#endif /* HAVE_RAMFS_FILE */

#endif
