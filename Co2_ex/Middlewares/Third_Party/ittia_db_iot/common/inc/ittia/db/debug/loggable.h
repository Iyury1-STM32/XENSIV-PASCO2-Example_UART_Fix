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

#ifndef DEBUG_LOGGABLE_H
#define DEBUG_LOGGABLE_H

#include <ittia/os/os_config.h>

/* loggable action debugger shared header */

typedef int (LogActionFilter)(int);

DBDLL_API void set_log_break(long p, int);
DBDLL_API void set_log_break_snapshot(long enable);
DBDLL_API long get_log_cur_action();

DBDLL_API void set_log_break_filter(LogActionFilter *);
DBDLL_API int  get_log_break_code(const char *);
DBDLL_API int  set_log_break_mask(char const ** names);

struct AutoActionFilter
{
	LogActionFilter * cur_filter;

	AutoActionFilter() : cur_filter ( NULL) {}
	~AutoActionFilter() { if (cur_filter) set_log_break_filter(NULL); }
	
	void set_filter(LogActionFilter * fn) { set_log_break_filter( fn ); cur_filter = fn; }
};


#endif /* DEBUG_LOGGABLE_H */
