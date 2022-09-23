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
 * Make snapshots of all currently opened files.
 */

#ifndef OS_FILE_SNAPSHOT_H
#define OS_FILE_SNAPSHOT_H

#include "ittia/os/os_config.h"

#ifdef DB_FILE_SNAPSHOT

#include "ittia/os/os_file.h"

C_HEADER_BEGIN

typedef void (DB_CALLBACK * os_file_list_snapshot_callback_t)(void* object, const db_fname_t* original_file_name, os_file_t copy_file, const db_fname_t* copy_file_name);

DBDLL_API int os_file_snapshot_set(uint32_t enable);
DBDLL_API int os_file_snapshot_callback(os_file_list_snapshot_callback_t callback, void* object);
DBDLL_API int os_file_snapshot(const db_fname_t* prefix);

C_HEADER_END

#endif

#endif
