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
 * FileX file I/O interface.
 */
#ifndef FILEX_FILE_H
#define FILEX_FILE_H

#include "ittia/os/os_config.h"

#ifdef HAVE_FILEX_FILE

#include "fx_api.h"
#include "ittia/os/os_mutex.h"

C_HEADER_BEGIN

/**
 * Information about an open file or other collection of blocks.
 */
typedef struct filex_file_t
{
    /** File handle. */
    FX_FILE fhandle;
    FX_MEDIA* media_ptr;
    CHAR* file_name;
    os_mutex_t cs;
} filex_file_t;

C_HEADER_END

DBDLL_API int db_set_filex_media(FX_MEDIA* media);

#endif /* HAVE_FILEX_FILE */

#endif /* FILEX_FILE_H */
