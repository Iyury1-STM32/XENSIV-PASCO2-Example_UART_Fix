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

#ifndef THREADX_MUTEX_H
#define THREADX_MUTEX_H

#include "ittia/os/os_config.h"

#if defined(HAVE_THREADS) && defined(HAVE_THREADX_THREADS)

#include "ittia/os/threadx/threadx_thread.h"

C_HEADER_BEGIN

typedef struct
{
    TX_MUTEX mtx;
}  os_mutex_t;

C_HEADER_END

#endif /* HAVE_THREADX_THREADS */

#endif /* THREADX_MUTEX_H */
