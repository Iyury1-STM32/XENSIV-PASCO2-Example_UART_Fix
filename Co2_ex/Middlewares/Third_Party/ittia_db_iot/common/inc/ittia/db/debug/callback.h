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

#ifndef DB_CALLBACK_H
#define DB_CALLBACK_H

#include <ittia/db.h>

C_HEADER_BEGIN

enum
{
	DB_CALLBACK_NONE,
	DB_ASSERT_CALLBACK,

    DB_CONN_OPEN_CALLBACK,  /* db_conn_callback_t */
    DB_CONN_CLOSE_CALLBACK, /* db_conn_callback_t */

    DB_TABLE_OPEN_CALLBACK,
    DB_TABLE_CLOSE_CALLBACK,
    
    DB_TX_BEGIN_CALLBACK,
    DB_TX_WRITER_CALLBACK,
    DB_TX_PREPARING_CALLBACK,
    DB_TX_PREPARED_CALLBACK,
    DB_TX_COMMITTING_CALLBACK,
    DB_TX_COMMITTED_CALLBACK,
    DB_TX_ABORTING_CALLBACK,
    DB_TX_ABORTED_CALLBACK
};

typedef struct callback_event_t
{
	int     event_code;
    int     callback_id;
    size_t  event_size;
    void *  user_data;
} callback_event_t;

typedef struct db_assert_callback_t
{
	callback_event_t callback_info;
} db_assert_callback_t;

typedef struct db_conn_callback_t
{
    callback_event_t callback_info;

    db_t hdb;
} db_conn_callback_t;

typedef struct db_tx_callback_t
{
    callback_event_t callback_info;

    db_t hdb;
    uint64_t txid;
} db_tx_callback_t;

#ifdef WIN32
#	define DBEXPORT	__declspec(dllexport)
#	define DBCALL	__stdcall
#else
#	define DBEXPORT
#	define DBCALL
#endif


typedef int (DBCALL * db_callback_t)(callback_event_t*);

/* returns callback id */
DBDLL_API int           _db_add_callback(db_t, int callback_name, db_callback_t, void * user_data);
DBDLL_API db_result_t   _db_remove_callback(db_t, int callback_id );
DBDLL_API db_result_t   _db_set_callback_data(db_t, int callback_id, void * user_data, void **);
DBDLL_API db_result_t   _db_get_callback_data(db_t, int callback_id, void **);

C_HEADER_END

#endif /* DB_CALLBACK_H */
