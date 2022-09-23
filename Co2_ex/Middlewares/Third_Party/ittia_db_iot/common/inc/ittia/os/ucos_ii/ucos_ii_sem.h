/**************************************************************************/
/*                                                                        */
/*      Copyright (c) 2005-2015 by ITTIA L.L.C. All rights reserved.      */
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

#ifndef ITTIA_OS_UCOS_II_SEM_H
#define ITTIA_OS_UCOS_II_SEM_H

#include "ittia/os/os_config.h"

#if defined(HAVE_THREADS) && defined(HAVE_UCOS_II_THREADS)

#include <ucos_ii.h>

C_HEADER_BEGIN

typedef OS_EVENT * os_sem_t;

C_HEADER_END

#endif /* HAVE_UCOS_II_THREADS */

#endif /* ITTIA_OS_UCOS_II_SEM_H */
