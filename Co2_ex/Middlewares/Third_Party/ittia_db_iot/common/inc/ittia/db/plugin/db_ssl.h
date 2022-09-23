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
 * SSL plugin for ITTIA DB.
 *
 * This plugin provides a user-defined connection protocol for ITTIA DB that
 * uses SSL/TLS.
 */

#ifndef DB_SSL_H
#define DB_SSL_H

#include <ittia/db.h>

#if DB_API_VER < DB_API_10C
#error "SSL plugin requires DB_API_10C or greater."
#endif

#ifdef ITTIADB_OPENSSL_EXPORTS
#   define ITTIADB_OPENSSL_PUBLIC DB_EXPORT
#elif defined(ITTIADB_OPENSSL_DLL)
#   define ITTIADB_OPENSSL_PUBLIC DB_IMPORT
#else
#   define ITTIADB_OPENSSL_PUBLIC
#endif

C_HEADER_BEGIN

/**
 * SSL plugin options.
 */
typedef struct
{
    size_t       size; /* set size of sizeof(db_ssl_options_t) */
    const char * ssl_bind_addr;
    const char * ssl_bind_port;

    const char * ca_file;
    const char * ca_path;
    const char * certificate_chain_file;
    const char * private_key_file;
    const char * private_key_passphrase;

    int anonymous_dh;
    const char * dh_512_file;
    const char * dh_1024_file;
    const char * dh_2048_file;
    const char * dh_4096_file;

    int verify_peer_cert;
    int require_peer_cert;
    int verify_depth;

    const char * ca_data;

} db_ssl_options_t;

/**
 * SSL plugin environment.
 */
typedef struct
{
    size_t       size;
    int (*ssl_get_options)(int server, db_ssl_options_t * );
    int (*ssl_set_options)(int server, const db_ssl_options_t * );
    const char * (*ssl_protocol_name)();
} db_ssl_env_t;

ITTIADB_OPENSSL_PUBLIC const db_udcp_info_t * db_ssl_udcp_info(void);
ITTIADB_OPENSSL_PUBLIC const db_ssl_env_t * db_ssl_get_env(void);

/** Register statically linked SSL plugin. */
#define DB_SSL_REGISTER(plugin_handle)  (db_udcp_register(db_ssl_udcp_info()) ? *(plugin_handle) = (void*)db_ssl_get_env(), DB_OK: DB_FAIL)
/** Unregister SSL plugin. */
#define DB_SSL_UNREGISTER()             (db_udcp_unregister(db_ssl_udcp_info()->udcp_proto_name))

/** @cond IGNORE */
#define _db_ssl_call(plugin_handle, member)            \
    (plugin_handle == NULL || (((db_ssl_env_t*)plugin_handle)->size <= offsetof(db_ssl_env_t, member))) ? DB_FAILURE : ((db_ssl_env_t*)plugin_handle)->member

#define _db_ssl_fcall(plugin_handle, member, failure)  \
    (plugin_handle == NULL || (((db_ssl_env_t*)plugin_handle)->size <= offsetof(db_ssl_env_t, member))) ? failure : ((db_ssl_env_t*)plugin_handle)->member
/** @endcond */

/** Get SSL protocol name. */
#define db_ssl_protocol_name(plugin_handle)    \
    (_db_ssl_fcall(plugin_handle, ssl_protocol_name, NULL)())

/** Get SSL server options. */
#define db_ssl_get_server_options(plugin_handle, options)    \
    (_db_ssl_call(plugin_handle, ssl_get_options)(1, options))

/** Set SSL Server options. */
#define db_ssl_set_server_options(plugin_handle, options)    \
    (_db_ssl_call(plugin_handle, ssl_set_options)(1, options))

/** Get SSL client options. */
#define db_ssl_get_client_options(plugin_handle, options)    \
    (_db_ssl_call(plugin_handle, ssl_get_options)(0, options))

/** Set SSL client options. */
#define db_ssl_set_client_options(plugin_handle, options)    \
    (_db_ssl_call(plugin_handle, ssl_set_options)(0, options))

C_HEADER_END

#endif /* DB_SSL_H */
