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

/** @file
 *
 * ITTIA DB plugin API.
 *
 * Provides support for plugin libraries that can be loaded at runtime.
 */

#ifndef DB_PLUGIN_H
#define DB_PLUGIN_H

#include "ittia/db.h"

enum
{
	DB_UDCP_PLUGIN = 1
};


C_HEADER_BEGIN

typedef DBDLL_API int   (*db_register_plugin)(int plugin_type, void * plugin_data, db_t);
typedef DBDLL_API int   (*db_plugin_proc)(int api_ver, db_register_plugin, void ** dl_tab, db_t, ...);

DBDLL_API db_result_t   db_load_plugin(const char * name, void ** dl_tab, db_t);

C_HEADER_END


#endif /* DB_PLUGIN_H */
