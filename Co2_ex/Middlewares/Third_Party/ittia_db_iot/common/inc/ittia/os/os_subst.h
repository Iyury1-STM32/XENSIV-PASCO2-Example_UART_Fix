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

#ifndef OS_SUBST_H
#define OS_SUBST_H

#include "ittia/os/os_thread.h"

typedef struct os_subst_s os_subst_t;

C_LINKAGE DBDLL_API os_subst_t * os_subst_create(void);
C_LINKAGE DBDLL_API void os_subst_destroy(os_subst_t *);
#ifdef HAVE_THREADS
C_LINKAGE DBDLL_API void os_subst_clean(os_subst_t *, os_thread_t * thread, const char * name);
#endif
C_LINKAGE DBDLL_API const char * os_subst_get(os_subst_t *, const char * name, int len);
C_LINKAGE DBDLL_API int os_subst_thread_set(os_subst_t *, const char  * name, const char  * value);
C_LINKAGE DBDLL_API int os_subst_process_set(os_subst_t *, const char  * name, const char  * value);

C_LINKAGE DBDLL_API int os_subst( os_subst_t * subst, const char * format, int len, char * dest_buf, size_t size);

#endif /* OS_SUBST_H */
