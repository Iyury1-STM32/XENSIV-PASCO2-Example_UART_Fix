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

#ifndef OS_DIR_H
#define OS_DIR_H

#include "ittia/os/os_config.h"

typedef struct os_dir_s * os_dir_t;

#define OS_DIR_NULL_PATH           0u   /* return file names without path name */
#define OS_DIR_MASK_PATH           1u   /* return file names according to the given mask */
#define OS_DIR_FULL_PATH           2u   /* return file names as full path */
#define _OS_DIR_RESULT_PATH     0x07u

#define OS_DIR_ENUM_FILES       0x10u   /* enumerate user files */
#define OS_DIR_ENUM_SUBDIRS     0x20u   /* enumerate user subdirs */
#define OS_DIR_ENUM_SYSFILES    0x40u   /* enumerate system files */
#define OS_DIR_ENUM_SYSDIRS     0x80u   /* enumerate system subdirs */
#define OS_DIR_ENUM_ALL         0xf0u   /* enumerate system subdirs */

C_HEADER_BEGIN

DBDLL_API os_dir_t os_dir_open( const db_fname_t * mask, int);
DBDLL_API const db_fname_t * os_dir_next(os_dir_t, int * type);
DBDLL_API int os_dir_close(os_dir_t);

C_HEADER_END

#endif /* OS_DIR_H */
