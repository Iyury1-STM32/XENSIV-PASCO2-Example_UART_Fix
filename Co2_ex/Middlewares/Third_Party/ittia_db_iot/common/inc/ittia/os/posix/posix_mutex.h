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

#ifndef POSIX_MUTEX_H
#define POSIX_MUTEX_H

#include "ittia/os/os_config.h"

#if defined(HAVE_THREADS) && defined(HAVE_POSIX_MUTEX)

#include "ittia/os/std/pthread.h"

C_HEADER_BEGIN

typedef struct
{
    pthread_mutex_t mtx;
}  os_mutex_t;

#define OS_MUTEX_INIT PTHREAD_MUTEX_INITIALIZER

C_HEADER_END

#endif /* HAVE_POSIX_MUTEX */

#endif /* POSIX_MUTEX_H */
