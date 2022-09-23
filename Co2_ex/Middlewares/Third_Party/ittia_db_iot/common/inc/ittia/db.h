/**************************************************************************/
/*                                                                        */
/*      Copyright (c) 2005-2019 by ITTIA L.L.C. All rights reserved.      */
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
 * Entry point for the ITTIA DB C API.
 *
 * @copydoc CAPI
 */

#ifndef ITTIA_DB_H
#define ITTIA_DB_H

#include <ittia/os/os_config.h>
#include <ittia/os/os_byte_order.h>
#include <ittia/os/os_cpu.h>
#include <ittia/os/os_wait_time.h>
#include <ittia/db/db_defs.h>
#include <ittia/db/db_error.h>

C_HEADER_BEGIN

/* supported API versions */
#define DB_API_100 0x100u
#define DB_API_101 0x101u
#define DB_API_102 0x102u
#define DB_API_103 0x103u
#define DB_API_104 0x104u
#define DB_API_105 0x105u
#define DB_API_106 0x106u
#define DB_API_107 0x107u
#define DB_API_108 0x108u
#define DB_API_109 0x109u
#define DB_API_10A 0x10Au
#define DB_API_10B 0x10Bu
#define DB_API_10C 0x10Cu
#define DB_API_10D 0x10Du
#define DB_API_10E 0x10Eu
#define DB_API_10F 0x10Fu
#define DB_API_110 0x110u
#define DB_API_111 0x111u
#define DB_API_112 0x112u
#define DB_API_113 0x113u

#ifndef DB_API_VER
/** Current API version number. @see db_init. */
#define DB_API_VER DB_API_113
#endif

#if (DB_API_VER < DB_API_100) || (DB_API_VER > DB_API_113)
#error "Unsupported API version"
#endif

#ifdef DB_RELAX
#define DB_DECLARE_HANDLE(name) typedef void * name
#else
#define DB_DECLARE_HANDLE(name) typedef struct name##_s * name
#endif

/* types */
/** Database handle. @see CAPIDatabase @ingroup CAPIDatabase */
DB_DECLARE_HANDLE(db_t);
/** Row handle. @see CAPIRow @ingroup CAPIRow */
DB_DECLARE_HANDLE(db_row_t);
/** Cursor handle. @see CAPICursor @ingroup CAPICursor */
DB_DECLARE_HANDLE(db_cursor_t);
/** Sequence handle. @see CAPISequence @ingroup CAPISequence */
DB_DECLARE_HANDLE(db_sequence_t);
/** Lock handle. @see CAPIDatabase @ingroup CAPIDatabase */
DB_DECLARE_HANDLE(db_hlock_t);
/** Database column type. @see CAPIDataTypes @ingroup CAPIDataTypes */
DB_DECLARE_HANDLE(db_coltype_t);
/** Variable type. @see CAPIDataTypes @ingroup CAPIDataTypes */
DB_DECLARE_HANDLE(db_vartype_t);
/** Change notification handle. */
DB_DECLARE_HANDLE(db_notify_t);

#ifdef __cplusplus
#define DB_RESULT_CONST(value) reinterpret_cast<db_result_t>(value)
#define DB_LEN_CONST(value) static_cast<db_len_t>(value)
#define DB_COLTYPE_CONST(value) reinterpret_cast<db_coltype_t>(value)
#define DB_VARTYPE_CONST(value) reinterpret_cast<db_vartype_t>(value)
#else
#define DB_RESULT_CONST(value) (db_result_t)(value)
#define DB_LEN_CONST(value) (db_len_t)(value)
#define DB_COLTYPE_CONST(value) (db_coltype_t)(value)
#define DB_VARTYPE_CONST(value) (db_vartype_t)(value)
#endif

/** Heap pointer type. Reserved for future use: always use NULL for arguments
 * of this type. */
typedef struct db_heap_s * db_heap_t;

#define DB_NAME(x) x
/** Type for characters in name strings. Applicable to table, field,
 * index, and sequence names
 */
typedef char  db_objname_t;

/** Wait time type. A value of #DB_WTIME_FAIL indicates an error. @see db_set_timeout, db_get_timeout, DB_WTIME_FAIL */
typedef os_wait_time_t db_wtime_t;
/** Flag bits data type. */
typedef int32_t        db_flags_t;
/** Variable address data type. @see db_bind_t::data_ptr, db_bind_t::data_ind */
typedef intptr_t       db_addr_t;
/** API version type. @see db_init */
typedef uint16_t       db_api_t;

/**
 * Standard allocator for API data structures. This is declared at the
 * beginning of API data structures to manage memory allocation. Always
 * initialize this with #DB_ALLOC_INITIALIZER.
 *
 * @ingroup CAPI
 *
 * @see db_oid_t, db_indexdef_t, db_tabledef_t
 */
typedef struct db_alloc_t
{
    db_heap_t  heap;
    uint16_t   mask;
} db_alloc_t;

/** Initialize the db_alloc member in API data structures. @see db_alloc_t */
#define DB_ALLOC_INITIALIZER() { NULL, 0 }

/** @addtogroup Errors
 *  @{ */

/** API call result. @see DB_OK, DB_FAIL, Errors */
typedef struct rc_s *         db_result_t;

/** A result of success. No error code was set. @see Errors */
#define DB_OK                 DB_RESULT_CONST(1)

/** A result of failure for functions that return #db_result_t. An error code was set.
 * @see get_db_error, Errors. */
#define DB_FAIL               DB_RESULT_CONST(0)
/** A result of failure for functions that return #db_wtime_t. An error code was set.
 * @see get_db_error, Errors. */
#define DB_WTIME_FAIL         (DB_WAIT_FOREVER - 1)
/** A result of failure for functions that return #db_len_t. An error code was set.
 * @see get_db_error, Errors. */
#define DB_LEN_FAIL           DB_LEN_CONST(-0x100)


#define DB_WAIT_FOREVER     OS_WAIT_FOREVER
/** @} */

#if DB_API_VER >= DB_API_10F
typedef enum
{
    DB_SEEK_BEFORE_FIRST,
    DB_SEEK_FIRST,
    DB_SEEK_NEXT,
    DB_SEEK_PRIOR,
    DB_SEEK_LAST,
    DB_SEEK_AFTER_LAST,

    DB_SEEK_RELATIVE,
    DB_SEEK_ABSOLUTE
} db_seek_position_t;

#define DB_IS_BEFORE_FIRST  (1)
#define DB_IS_AFTER_LAST    (2)
#endif

/** @name Data Types
 *  @{ */
/** @ingroup CAPIDataTypes */
typedef char        db_ansi_t;    /**< ANSI string character type. */
typedef uint8_t     db_utf8_t;    /**< UTF8 string character type. */
typedef uint16_t    db_utf16_t;   /**< UTF16 string character type. */
typedef uint32_t    db_utf32_t;   /**< UTF32 string character type. */
typedef float32_t   db_float32_t; /**< 32-bit floating point type. */
typedef float64_t   db_float64_t; /**< 64-bit floating point type. */
typedef db_bool_t   db_boolean_t; /**< Boolean type. */

#if OS_CPU_LEN == 64
typedef int64_t     db_len_t;     /**< Field length data type (usually in bytes). A value of #DB_LEN_FAIL indicates an error. @see DB_LEN_FAIL */
#else
typedef int32_t     db_len_t;     /**< Field length data type (usually in bytes). A value of #DB_LEN_FAIL indicates an error. @see DB_LEN_FAIL */
#endif
typedef int32_t     db_fieldno_t; /**< Field index number data type. */

typedef void *      db_object_t;  /**< Bound object data type. */
typedef int32_t     db_rep_address_t;  /**< Replication address type. */
/** @} Data Types */

/* 64-bit integer placeholders, can be used instead of strict int64 */

/**
 * Large integer (64-bit) data type.
 * @ingroup CAPIDataTypes
 *
 * @see db_seqvalue_t
 */
typedef union
{
    BYTE_ORDER_STRUCT( int32_t high, uint32_t low ) int32;

#ifdef HAVE_INT64
    int64_t int64;
#else
    db_AlignType __alignment; /* enforce alignment rules */
#endif
} db_largeint_t;

/**
 * Unsigned large integer (64-bit) data type.
 * @ingroup CAPIDataTypes
 */
typedef union db_ulargeint_t
{
    BYTE_ORDER_STRUCT( uint32_t high, uint32_t low ) uint32;

#ifdef HAVE_INT64
    uint64_t uint64;
#else
    db_AlignType __alignment; /* enforce alignment rules */
#endif
} db_ulargeint_t;

/**
 * Date data type
 * @ingroup CAPIDataTypes
 *
 * @see db_datetime_t
 */
typedef struct db_date_t
{
    uint16_t year;
    uint16_t month;
    uint16_t day;
} db_date_t;

#if DB_API_VER >= DB_API_106
/**
 * ODBC-compatible date structure.
 */
typedef struct db_odbc_date_t
{
    int16_t year;
    uint16_t month;
    uint16_t day;
} db_odbc_date_t;
#endif

/**
 * Time data type
 * @ingroup CAPIDataTypes
 *
 * @see db_datetime_t
 */
typedef struct db_time_t
{
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
} db_time_t;

#if DB_API_VER >= DB_API_106
/**
 * ODBC-compatible time structure.
 */
typedef struct db_odbc_time_t
{
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
} db_odbc_time_t;
#endif

/**
 * Date and time data type
 * @ingroup CAPIDataTypes
 *
 * @see db_timestamp_t
 */
typedef struct db_datetime_t
{
    db_date_t date;
    db_time_t time;
} db_datetime_t;

/**
 * Timestamp data type
 * @ingroup CAPIDataTypes
 */
typedef struct db_timestamp_t
{
    db_datetime_t datetime;
    uint32_t      microsec;
} db_timestamp_t;

#if DB_API_VER >= DB_API_106
/**
 * ODBC-compatible timestamp structure.
 */
typedef struct db_odbc_timestamp_t
{
    int16_t year;
    uint16_t month;
    uint16_t day;
    
    uint16_t hour;
    uint16_t minute;
    uint16_t second;
    
    uint32_t      fraction;
} db_odbc_timestamp_t;
#endif

#if DB_API_VER >= DB_API_10C
/*
 * ODBC-compatible interval structure.
 */

/**
 * Interval qualifier.
 */
typedef enum 
{
    DB_ODBC_INTERVAL_YEAR                = 1,
    DB_ODBC_INTERVAL_MONTH               = 2,
    DB_ODBC_INTERVAL_DAY                 = 3,
    DB_ODBC_INTERVAL_HOUR                = 4,
    DB_ODBC_INTERVAL_MINUTE              = 5,
    DB_ODBC_INTERVAL_SECOND              = 6,
    DB_ODBC_INTERVAL_YEAR_TO_MONTH       = 7,
    DB_ODBC_INTERVAL_DAY_TO_HOUR         = 8,
    DB_ODBC_INTERVAL_DAY_TO_MINUTE       = 9,
    DB_ODBC_INTERVAL_DAY_TO_SECOND       = 10,
    DB_ODBC_INTERVAL_HOUR_TO_MINUTE      = 11,
    DB_ODBC_INTERVAL_HOUR_TO_SECOND      = 12,
    DB_ODBC_INTERVAL_MINUTE_TO_SECOND    = 13
} db_odbc_interval_qualifier_t;

/**
 * Year-month interval data.
 */
typedef struct
{
   uint32_t year;
   uint32_t month; 
} db_odbc_year_month_interval_t;

/**
 * Day-time interval data.
 */
typedef struct
{
   uint32_t day;
   uint32_t hour;
   uint32_t minute;
   uint32_t second;
   uint32_t fraction;
} db_odbc_day_second_interval_t;

/**
 * ODBC-compatible interval structure.
 */
typedef struct db_odbc_interval_t
{
    db_odbc_interval_qualifier_t    interval_type;
    int16_t                         interval_sign;
    union {
        db_odbc_year_month_interval_t   year_month;
        db_odbc_day_second_interval_t   day_second;
    } intval;
    
} db_odbc_interval_t;

/** A time interval represented as a number; units depend on the selected variable type. */
typedef int64_t db_interval_t;

/** A timestamp represented as the number of microseconds since 1970-01-01 00:00:00. */
typedef int64_t db_timestamp_usec_t;

#endif

/**
 * BLOB access data type. A field is bound to this data structure to obtain
 * access to the data in a BLOB field. Set #offset and #chunk_size to select
 * the portion of the blob that should be read or written by #db_fetch or
 * #db_update. The data will be read from or written to the memory addressed by
 * chunk_data.
 *
 * @ingroup CAPIDataTypes
 */
typedef struct db_blob_t
{
    db_len_t    blob_size;   /**< Actual BLOB size, filled at read.
                             * Set blob_size to truncate or expand BLOB during
                             * write operation. */
    db_len_t    offset;      /**< Offset of data to read or write. */
    db_len_t    chunk_size;  /**< Size of chunk to read or write. */
    db_len_t    actual_size; /**< Size of fetched chunk. */
    void *      chunk_data;  /**< Contents of field to read or update. */
} db_blob_t;

/** @} Data Types */

/** Default value for dboid_t::oid_tag.
 * @ingroup CAPIBookmarks */
#define DB_OID_TAG_NONE 0

/** Database object identity. This object identifies a specific table or row.
 * @ingroup CAPIBookmarks
 *
 * Initialize with #DB_OID_INITIALIZER.
 *
 * @see db_get_bookmark, db_goto_bookmark, db_lock, db_unlock
 */
typedef struct db_oid_t
{
    db_alloc_t db_alloc; /* the structure is likely to contain dynamic data
                          * in the following releases
                          */

#if DB_API_VER >= DB_API_100

    /** Object id tag. Initialize value to 0 (#DB_OID_TAG_NONE). All other
     * values are reserved for internal use. */
    uint16_t  oid_tag;

    /** The remainder of this structure is subject to change and should be
     * considered private. */
    union
    {
        struct { uint32_t pid; uint32_t tid; }      tableid_;
        struct { uint32_t pid; uint32_t tid; uint64_t rid; } rowid_;
#if DB_API_VER >= DB_API_10E
        struct
        {
            uint32_t pid;
            uint32_t tid;
            uint8_t vk_size;
            uint8_t vk_data[ DB_VAR_RID_MAX ];
        } varrowid_;
#endif
    } u;

#endif
} db_oid_t;

/**
 * Initializer for #db_oid_t.
 * @ingroup CAPIBookmarks
 *
 * Usage:
 * @code
 * dboid_t oid = DB_OID_INITIALIZER();
 * @endcode
 */
#define DB_OID_INITIALIZER() { DB_ALLOC_INITIALIZER() , DB_OID_TAG_NONE }

/* inline types */

/**
 * ITTIA DB library configuration.
 * @ingroup CAPIConfiguration
 *
 * @see db_config_init, db_config_destroy, db_set_config, db_get_config
 */
typedef struct db_config_t
{
#if DB_API_VER >= DB_API_100
    int concurrency;

    /** Memory optimization strategy */
    int memory_mode;

    /** Approximate number of concurrent transactions expected */
    int transactions;
#endif
} db_config_t;

/** 
 * Encryption call-back function.
 *
 * @ingroup CAPIDatabase
 *
 * Encrypt the data stored in the buffer @a data of size @a size.
 * Encryption should be performed in-place and cannot alter the size of
 * the @a data buffer.
 * 
 * @param udata  User-defined data stored in db_crypt_t::udata.
 * @param offset The page number where the data is stored. @a offset
 *               can be used to seed encryption algorythm.
 * @param data   Data to encrypt in-place.
 * @param size   Size of the data to encrypt.
 * 
 * @returns #DB_NOERROR. Other error codes are reserved for future use.
 */
typedef int (DB_CALLBACK * db_encrypt_t)(void * udata,
                                         uint32_t offset,
                                         void * data,
                                         size_t size);

/** 
 * Decryption call-back function.
 *
 * @ingroup CAPIDatabase
 *
 * Decrypt the data stored in the buffer @a data of size @a size.  Decryption
 * should be performed in-place and cannot alter the size of the @a data
 * buffer.
 * 
 * @param udata  User-defined data stored in db_crypt_t::udata.
 * @param offset The page number where the data is stored. @a offset
 *               can be used to seed encryption algorythm.
 * @param data   Data to decrypt in-place.
 * @param size   Size of the data to decrypt.
 * 
 * @returns #DB_NOERROR. Other error codes are reserved for future use.
 */
typedef int (DB_CALLBACK * db_decrypt_t)(void * udata,
                                         uint32_t offset,
                                         void * data,
                                         size_t size);

/**
 * Encryption hook interface.
 *
 * @ingroup CAPIDatabase
 *
 * To perform encryption, initialize db_file_storage_config_t::crypt with
 * values for encrypt, decrypt, and optionally udata. The same encryption
 * algorithm that is used to create a database must be used every time the
 * database is opened.
 *
 * @see db_file_storage_config_t::crypt
 */
typedef struct db_crypt_t
{

    void * udata;          /**< User data passed to call-backs (optional). */
    db_encrypt_t encrypt;  /**< Encryption hook. */
    db_decrypt_t decrypt;  /**< Decryption hook. */

} db_crypt_t;

#if DB_API_VER >= DB_API_10C
/**
 * Authorization credentials for a password-protected or encrypted database.
 * @ingroup CAPIDatabase
 */
typedef struct db_auth_info_s
{
    uint32_t        cipher_type;
    const void *    cipher_data;
    uint32_t        cipher_data_size;

    const db_ansi_t * user_name;
    const db_ansi_t * password;
} db_auth_info_t;

DBDLL_API db_result_t db_auth_info_init( db_auth_info_t * );
DBDLL_API db_result_t db_auth_info_destroy( db_auth_info_t * );
#endif /* DB_API_10C */

/**
 * Database file storage configuration.
 * @ingroup CAPIDatabase
 *
 * Initialize with #db_file_storage_config_init, destroy with
 * #db_file_storage_config_destroy.
 *
 * @see db_create_file_storage, db_open_file_storage
 */
typedef struct db_file_storage_config_t
{

#if DB_API_VER >= DB_API_100

    /** @name File settings
     *  @{ */
    uint32_t file_mode;
    int32_t  page_size;
    /** @} */

    /** @name Cache settings
     *  @{ */
    int32_t buffer_count;
    int32_t flush_buffers;
    /** @} */

    /** @name Journal settings
     *  @{ */
    int32_t journal_type;
    int32_t checkpoint_interval;
    int32_t preallocate;
    /** @} */

    db_crypt_t crypt;

#endif

#if DB_API_VER >= DB_API_106
    /** @name Memory table settings
     *  @{ */
    int32_t memory_page_size;
    int64_t memory_storage_size;
     /** @} */
#endif

#if DB_API_VER >= DB_API_108
    uint16_t journal_buffers;
#endif

#if DB_API_VER >= DB_API_10B
    /** @name Replication settings
     *  @{ */
    db_rep_address_t target_address;
    db_rep_address_t source_address;
     /** @} */
#endif

#if DB_API_VER >= DB_API_10C
    void *  udcp_param;

    const db_auth_info_t * auth_info;
#endif

#if DB_API_VER >= DB_API_10F
    uint32_t journal_age;
#endif

#if DB_API_VER >= DB_API_111
    void * storage_cache_segment;
    size_t storage_cache_size;
#endif

} db_file_storage_config_t;

/**
 * Database memory storage configuration.
 * @ingroup CAPIDatabase
 *
 * Initialize with #db_memory_storage_config_init, destroy with
 * #db_memory_storage_config_destroy.
 *
 * @see db_create_memory_storage, db_open_memory_storage
 */
typedef struct db_memory_storage_config_t
{

#if DB_API_VER >= DB_API_106

    /** @name Open settings
     *  @{ */
    uint32_t open_mode;
    /** @} */

    /** @cond INTERNAL */
    int32_t padding1;
    int32_t padding2;
    int32_t padding3;
    int32_t padding4;
    /** @endcond */

    /** @name Journal settings
     *  @{ */
    int32_t checkpoint_interval;
    int32_t preallocate;
    /** @} */

    /** @cond INTERNAL */
    db_crypt_t padding5;
    /** @endcond */

    /** @name In-memory settings
     *  @{ */
    int32_t memory_page_size;
    int64_t memory_storage_size;
     /** @} */
#endif

#if DB_API_VER >= DB_API_108
    uint16_t journal_buffers;
#endif

#if DB_API_VER >= DB_API_10B
    /** @name Replication settings
     *  @{ */
    db_rep_address_t target_address;
    db_rep_address_t source_address;
     /** @} */
#endif

#if DB_API_VER >= DB_API_10C
    void * udcp_param;

    const db_auth_info_t * auth_info;
#endif

#if DB_API_VER >= DB_API_10F
    uint32_t journal_age;
#endif

} db_memory_storage_config_t;

/** General storage configuration.
 * @ingroup CAPIDatabase
 *
 * @see db_file_storage_config_t, db_storage_config_init,
 * db_storage_config_destroy, db_get_storage_config
 */
typedef struct db_storage_config_t
{

#if DB_API_VER >= DB_API_100
    int32_t      storage_mode;
    union {
        db_file_storage_config_t file_storage;
        db_memory_storage_config_t memory_storage;
    } u;
#endif

} db_storage_config_t;

/** @cond ITTIA_DB_SQL */

/** Disable database security agent.
 * @ingroup CAPISecurity 
 */
#define DB_SECURITY_AGENT_DISABLE  0u

/** Enable database security agent.
 * @ingroup CAPISecurity 
 */
#define DB_SECURITY_AGENT_ENABLE   1u

/** Start training database security agent.
 * @ingroup CAPISecurity 
 */
#define DB_SECURITY_AGENT_TRAINING 2u

/** Field definition.
 * @ingroup CAPISecurity
 *
 */
typedef struct {
    db_flags_t sql_watchdog_flags;
    db_len_t sql_allowed_list_size;
} db_security_agent_t;
/** @endcond */

/** Field definition.
 * @ingroup CAPISchemaTable
 *
 * @see db_tabledef_t::fields
 */
typedef struct db_fielddef_t
{

#if DB_API_VER >= DB_API_100
    db_fieldno_t    fieldno;
    db_objname_t    field_name[DB_MAX_FIELD_NAME + 1];
    db_coltype_t    field_type;
    db_len_t        field_size; /**< Logical field size or scale. */
    db_len_t        field_prec; /**< Logical field precision. */
    db_flags_t      field_flags; /**< @see DB_NULLABLE, DB_NOT_NULL, DB_IDENTITY */
    void *          field_value;   /**< Reserved, should be NULL */

    /***/
    db_len_t        field_width; /**< Physical field width in bytes. */
#endif

} db_fielddef_t;

#if DB_API_VER >= DB_API_102
/** @cond ITTIA_DB_SQL */
/** SQL query parameter definition.
 * @ingroup CAPISQL
 *
 * @see db_get_param
 */
typedef struct db_paramdef_t
{
    db_fieldno_t    paramno;    /**< Parameter number, starting from 0. */
    db_coltype_t    param_type; /**< Column type. */
    db_len_t        param_size; /**< Logical field size or scale. */
    db_len_t        param_prec; /**< Logical field precision. */
    db_flags_t      param_flags; /**< @see DB_NULLABLE, DB_NOT_NULL */
#if 0
    /* Named parameters will be introduced in a future API version. */
    db_objname_t    param_name[DB_MAX_FIELD_NAME + 1];
#endif
} db_paramdef_t;
#endif
/** @endcond */

/* initialize the member */
/** @returns The size of the variable named @a member in a struct of given @a type.
 * @see db_bind_t::data_size */
#define DB_BIND_SIZE(type,member)   sizeof(((type*)DB_STATIC_CAST_ADDRESS)->member)

/** @returns The address offset of the variable named @a member in a struct of
 * given @a type.
 * @see db_bind_t::data_ptr, db_bind_t::data_ind */
#define DB_BIND_OFFSET(type,member) (((db_addr_t)&(((type*)DB_STATIC_CAST_ADDRESS)->member))-DB_STATIC_CAST_ADDRESS)

/** @returns The pointer given as @a var cast as a binding address.
 * @see db_bind_t::data_ptr */
#define DB_BIND_ADDRESS(var)        ((db_addr_t)(void*)(var))

/** Row binding description
 * @ingroup CAPIRow
 *
 * @see db_alloc_row, db_bind_field, db_qseek, db_qfetch, db_qinsert,
 * dbqupdate, db_bind_init, db_bind_destroy
 */
typedef struct db_bind_t
{

#if DB_API_VER >= DB_API_100
    db_fieldno_t   field_no;
    db_vartype_t   data_type;
    db_addr_t      data_ptr;
    db_len_t       data_size;
    db_addr_t      data_ind;

    uint32_t       data_flags;
#endif

} db_bind_t;

/** Statistics on internal buffers.
 *
 * These values can be used to evaluate cache performance.
 * @ingroup CAPIConfiguration
 *
 * @see db_stat_bufmgr
 */
typedef struct db_bufmgr_stat_t
{

#if DB_API_VER >= DB_API_100
    /** Total number of pin requests. */
    db_counter_t pin;

    /** Number of times a page was pinned for the first time. */
    db_counter_t first_pin;

    /** Number of times page was pinned recursively or concurrently. */
    db_counter_t second_pin;

    /** Number of pages that were stolen away after the first hit. */
    db_counter_t stolen;

    /** Number of pages resolved in the first attempt to pin the page. */
    db_counter_t first_hit;

    /** Number of pages missed in the first attempt to pin the page. */
    db_counter_t first_miss;

    /** Number of pages resolved in the second attempt to pin the page. */
    db_counter_t second_hit;

    /** Number of pages missed in the second attempt to pin the page. */
    db_counter_t second_miss;

    /** Number of times a buffer was checked as a possible candidate for a pin. */
    db_counter_t frame_scan;

    /** Number of scanning restarts due to page pin. */
    db_counter_t restart;

    /** Number of times a page was discarded from the cache. */
    db_counter_t discard;

    /** Number of times a page was loaded from a file. */
    db_counter_t page_load;

    /** Total number of times a page was flushed to a file. */
    db_counter_t page_flush;

    /** Number of pages flushed in the background. */
    db_counter_t bg_flush;

    /** Number of pages flushed when a flush was forced. */
    db_counter_t force_flush;

    /** Number of pages flushed when a lazy write was issued. */
    db_counter_t lazy_flush;
#endif

} db_bufmgr_stat_t;

/** Statistics on a specific page in the database or buffer in the cache.
 * @ingroup CAPIConfiguration
 *
 * @see db_stat_buffer, db_stat_page
 */
typedef struct db_buf_stat_t
{

#if DB_API_VER >= DB_API_100

    /** Page that is bound to the buffer or -1 if no page is bound. */
    uint32_t pageno;

    /** Number of times the page was pinned since it was copied into the cache. */
    db_counter_t pin;

    /** Current eviction rank of page. */
    db_counter_t rank;

    /** Page type. */
    int type;

    /** True when buffer is locked, false (0) otherwise. */
    int locked;

    /** True when buffer is fixed, false (0) otherwise. */
    int fixed;
#endif

} db_buf_stat_t;

typedef struct db_file_storage_stat_t
{

#if DB_API_VER >= DB_API_10F

    /** Number of bytes in each page. */
    int32_t page_size;

    /** Total number of pages reserved. */
    uint32_t page_count;

    /** Number of reserved pages currently in use. */
    uint32_t used_page_count;

    /** Number of reserved pages currently available. */
    uint32_t free_page_count;

    /** Number of bytes probably in use. */
    int64_t used_bytes;

    /** Number of bytes definitely available. */
    int64_t free_bytes;
#endif

} db_file_storage_stat_t;
 
/** Lock manager configuration for local lock manager.
 * @ingroup CAPIConfiguration
 *
 * @see db_init_ex
 */
typedef struct lm_local_config_t
{

#if DB_API_VER >= DB_API_100
    /** @name Lock manager configuration
     *  @{ */
    int nlocks;   /**< Maximum number of locks to use at once. */
    int nowners;  /**< Maximum number of lock owners (connections). */
    int nobjects; /**< Maximum database objects to be locked at once. */
    /** @} */
#endif

} lm_local_config_t;

#ifndef _DB_OMIT_LM_MODE_NAMES
#define LM_NONE                  0
#define LM_LOCAL                 1
#endif

/** Lock manager configuration.
 * @ingroup CAPIConfiguration
 *
 * @see db_init_ex
 */
typedef struct lm_config_t
{

#if DB_API_VER >= DB_API_100

    int lm_mode;
    union {
        /*! Local lock manger. Use with <code>lm_mode = _LM_LOCAL</code>. */
        lm_local_config_t local;
    } u;

#endif

} lm_config_t;

/* Library interface */
/** @addtogroup CAPI
 *  @{ */ 

DBDLL_API int                db_init(db_api_t);
DBDLL_API int                db_done(void);

DBDLL_API db_result_t        db_attach_thread(void);
DBDLL_API db_result_t        db_detach_thread(void);

#if DB_API_VER >= DB_API_108

/* initialize memory component */

/** Memory segment for general allocation. */
typedef struct db_memory_segment_s
{
    /**
     * A preallocated buffer of the given size. Use NULL to obtain a buffer
     * from the system allocator.
     */
    void * ptr;

    /** Size of the memory segment, in bytes. */
    size_t size;
} db_memory_segment_t;

/**
 * Configuration for built-in memory allocator. Settings and resources defined
 * here are shared between all database connections.
 */
typedef struct db_memory_config_s
{
    size_t      block_size; /**< Minimum unit of allocation. */
    /**
     * Memory allocation flags. Any combination of:
     * - #DB_MEMFLAGS_TRACE
     */
    db_flags_t  mem_flags;

    /**
     * Enable memory allocation statistics. This incurs additional overhead and
     * should only be used during testing.
     *
     * @see db_mem_statistics, db_done_ex.
     */
#define     DB_MEMFLAGS_TRACE           1

    /**
     * Number of memory segments for the built-in memory allocator. If a
     * single contiguous segment of memory of the desired size is not
     * available, up to eight segments can be defined. Set to zero to use the
     * system memory allocator.
     */
    size_t      num_segs;
    /** List of memory segment definitions. */
    db_memory_segment_t mem_seg[DB_MAX_MEMSEGMENT_COUNT];
} db_memory_config_t;

/** Extended library initialization parameters. */
typedef struct db_init_s
{
    const db_memory_config_t * mem_config;     /**< Memory allocator configuration. */
    const db_config_t * db_config;             /**< Database library configuration. */
    const lm_local_config_t * lm_local_config; /**< Local lock manager configuration. */
    const lm_config_t * lm_config;             /**< General lock manager configuration. Takes precedent over lm_local_config if supplied. */
} db_init_t;

/** Extended library decommissioning parameters. */
typedef struct db_done_s
{
    struct db_mem_statistics_s * mem_statistics; /**< Final memory allocation statistics, if enabled. */
    struct db_api_statistics_s * api_statistics; /**< Final API statistics. */
    struct db_lm_statistics_s  * lm_statistics;  /**< Final lock-manager statistics. */
} db_done_t;

DBDLL_API int                db_init_ex(db_api_t, const db_init_t *);
DBDLL_API int                db_done_ex(db_done_t *);

#endif /* DB_API_108 */

/** @} */

/** @addtogroup CAPIConfiguration
 *  @{ */

DBDLL_API db_result_t        db_set_config(const db_config_t*);
DBDLL_API db_result_t        db_get_config(db_config_t *);

DBDLL_API db_result_t        lm_use_local(const lm_local_config_t*);
DBDLL_API db_result_t        lm_set_config(const lm_config_t*);
DBDLL_API db_result_t        lm_get_config(lm_config_t*);

/** @} */

/** @addtogroup CAPIDatabase
 *  @{ */
DBDLL_API db_t               db_create_file_storage(const db_fname_t*,
                                                    const db_file_storage_config_t*);

DBDLL_API db_t               db_open_file_storage(const db_fname_t*,
                                                  const db_file_storage_config_t*);

#if DB_API_VER >= DB_API_111
DBDLL_API db_result_t        db_remove_file_storage(const db_fname_t* file_uri, const db_auth_info_t * auth_info, db_flags_t flags);
#endif

#if DB_API_VER >= DB_API_10C
DBDLL_API db_result_t        db_set_access_password(db_t, const char *, db_flags_t );
#endif

#if DB_API_VER >= DB_API_106
DBDLL_API db_t               db_create_memory_storage(const db_fname_t*,
                                                      const db_memory_storage_config_t*);

DBDLL_API db_t               db_open_memory_storage(const db_fname_t*,
                                                    const db_memory_storage_config_t*);
#endif

DBDLL_API db_result_t        db_shutdown(db_t, int, void *);

DBDLL_API db_result_t        db_get_storage_config(db_t,
                                                   db_storage_config_t*);

DBDLL_API db_result_t        db_file_storage_config_init(db_file_storage_config_t*);
DBDLL_API db_result_t        db_file_storage_config_destroy(db_file_storage_config_t*);

#if DB_API_VER >= DB_API_106
DBDLL_API db_result_t        db_memory_storage_config_init(db_memory_storage_config_t*);
DBDLL_API db_result_t        db_memory_storage_config_destroy(db_memory_storage_config_t*);
#endif

DBDLL_API db_result_t        db_storage_config_init(db_storage_config_t*);
DBDLL_API db_result_t        db_storage_config_destroy(db_storage_config_t*);
/** @} */

/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPISecurity
 *  @{ */
DBDLL_API db_result_t        db_set_security_agent(db_t, const db_security_agent_t * config);
DBDLL_API db_result_t        db_get_security_agent(db_t, db_security_agent_t * config);
/** @} */
/** @endcond */

/** @addtogroup CAPITransaction
 *  @{ */

DBDLL_API db_result_t        db_begin_tx(db_t, db_flags_t);
DBDLL_API db_result_t        db_commit_tx(db_t, db_flags_t);
DBDLL_API db_result_t        db_abort_tx(db_t, db_flags_t);
DBDLL_API db_result_t        db_flush_tx(db_t, db_flags_t);
#if DB_API_VER >= DB_API_105
DBDLL_API int                db_is_active_tx(db_t);
#endif

DBDLL_API db_result_t        db_set_tx_default(db_t, db_flags_t);
DBDLL_API db_flags_t         db_get_tx_default(db_t);

/** @} */

/** @addtogroup CAPIDatabase
 *  @{ */

#if DB_API_VER >= DB_API_107
DBDLL_API db_result_t        db_set_timeout(db_t, db_wtime_t);
DBDLL_API db_wtime_t         db_get_timeout(db_t);
#else
DBDLL_API db_result_t        db_set_timeout(db_wtime_t);
DBDLL_API db_wtime_t         db_get_timeout(void);
#endif

DBDLL_API db_result_t        db_stat_bufmgr(db_t, db_bufmgr_stat_t*);
DBDLL_API db_result_t        db_stat_page(db_t, uint32_t pageno, db_buf_stat_t*);
DBDLL_API db_result_t        db_stat_buffer(db_t, uint32_t bufno, db_buf_stat_t*);

#if DB_API_VER >= DB_API_10F
DBDLL_API db_result_t        db_stat_file_storage(db_t, db_file_storage_stat_t*, db_flags_t);
#endif

#if DB_API_VER >= DB_API_109
DBDLL_API db_result_t        db_backup(db_t, const db_fname_t* dest_file_name, uint32_t file_mode, db_flags_t);
#endif

#if DB_API_VER >= DB_API_10C
/**
 * Online backup settings.
 */
typedef struct db_backup_s
{
    uint32_t            file_mode;
    db_flags_t          backup_flags;

    db_crypt_t          crypt;

    uint32_t            cipher_type;
    const void *        cipher_data;
    uint32_t            cipher_data_size;
} db_backup_t;

DBDLL_API db_result_t        db_backup_ex(db_t, const db_fname_t *  backup_file_name, const db_backup_t *);
#endif

/** @} */

/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPIDistributed
 *  @{ */

#if DB_API_VER >= DB_API_10B

/* two-phase commit support */ 

/**
 * Persistent transaction identifier.
 */
typedef struct db_xid_s
{
    /** Format of the transaction identifier data. */
    int32_t     format_id;
    /** Length of global transaction identifier part in bytes. */
    int32_t     gtrid_length;
    /** Length of branch qualifier part in bytes. */
    int32_t     bqual_length;
    /** Transaction identifier data: global transaction identifier followed by branch qualifier. */
    uint8_t     xid_data[DB_XID_DATA_MAX];
}  db_xid_t;

/** @name Resource Management
 * @{ */

/** Detach prepared transaction from the connection. */
#define DB_RM_DETACH    1

DBDLL_API db_result_t        db_rm_prepare(db_t, const db_xid_t * xid, db_wtime_t, db_flags_t);

/** Recover the first of a list of transactions. */
#define DB_RECOVER_RESTART  1
DBDLL_API db_result_t        db_rm_recover(db_t, db_xid_t*, db_len_t, db_len_t *, db_flags_t);
DBDLL_API db_result_t        db_rm_commit(db_t, const db_xid_t*, db_flags_t);
DBDLL_API db_result_t        db_rm_rollback(db_t, const db_xid_t*, db_flags_t);

/** @} */

/** @name Distributed Transaction Management
 * @{ */
#define DB_DTM_NONE         0  /**< No distributed transaction. */
#define DB_DTM_PREPARED     1  /**< All slaves in a distributed transaction are prepared. */
#define DB_DTM_COMMIT       2  /**< Distributed transaction is committed. */
#define DB_DTM_ROLLBACK     3  /**< Distributed transaction is rolled back. */

/**
 * Distributed transaction information.
 */
typedef struct db_dtm_info_s
{
    /** Transaction state. @see DB_DTM_NONE, DB_DTM_PREPARED, DB_DTM_COMMIT, DB_DTM_ROLLBACK */
	int32_t     tx_state;

    /** Transaction identifier. */
    db_xid_t    xid;
	uint64_t    prepare_time;
    /** Commit timeout in effect when the transaction was committed. */
	db_wtime_t	commit_timeout;
    /** Description of the transaction stored in the log. */
	db_ansi_t   tx_info[DB_DTM_TXINFO_SIZE];
} db_dtm_info_t;

DBDLL_API db_result_t       db_dtm_commit(db_t,
                                          const db_ansi_t * tx_info,
                                          db_t *,
                                          int slave_count,
                                          db_xid_t * xid,
                                          int * unresolved);

DBDLL_API db_result_t       db_dtm_info(db_t, const db_xid_t *, db_dtm_info_t *);

DBDLL_API db_result_t       db_dtm_resolve(db_t,
                                           const db_xid_t *,
                                           db_t *,
                                           int slave_count,
                                           int * unresolved);

DBDLL_API db_result_t       db_dtm_recover(db_t, db_xid_t*, db_len_t, db_len_t *, db_flags_t);

DBDLL_API db_result_t       db_set_commit_timeout(db_t, db_wtime_t);
DBDLL_API db_result_t       db_get_commit_timeout(db_t, db_wtime_t *);

/** @} */

#endif /* DB_API_10B */
/** @endcond */

/** @} */

/** @addtogroup CAPISchemaSequence
 *  @{ */

/** Sequence value data type. @see db_next_sequence */
typedef db_largeint_t      db_seqvalue_t;
#ifndef _DB_OMIT_SEQUENCE_NAMES
#define DB_SEQUENCE_MIN   INT64_MIN
#define DB_SEQUENCE_MAX   INT64_MAX
#endif

/** Sequence definition.
 * @see db_seqdef_init, db_seqdef_destroy, db_create_sequence */
typedef struct db_seqdef_t
{

#if DB_API_VER >= DB_API_100
    /** Sequence name */
    db_objname_t    seq_name[ DB_MAX_SEQUENCE_NAME + 1 ];
    /** Initial sequence value */
    db_seqvalue_t   seq_start;

    /** Reserved for future use */
    db_flags_t      seq_flags;
    /** Reserved for future use */
    db_seqvalue_t   seq_cache_size;
    /** Reserved for future use */
    db_seqvalue_t   seq_min;
    /** Reserved for future use */
    db_seqvalue_t   seq_max;
#endif

} db_seqdef_t;

/* seqdef helpers */
DBDLL_API db_result_t        db_seqdef_init(db_seqdef_t*);
DBDLL_API db_result_t        db_seqdef_destroy(db_seqdef_t*);

/* sequence handling */
DBDLL_API db_result_t        db_create_sequence(db_t,
                                                const db_objname_t *,
                                                const db_seqdef_t *);

DBDLL_API db_result_t        db_drop_sequence(db_t, const db_objname_t *);
#if DB_API_VER >= DB_API_110
DBDLL_API db_result_t        db_rename_sequence(db_t,
                                                const db_objname_t * old_name,
                                                const db_objname_t * new_name);
#endif
DBDLL_API db_result_t        db_describe_sequence(db_t,
                                           const db_objname_t * name,
                                           db_seqdef_t *);

/** @} */

/* Tables and Indexes */

/** @addtogroup CAPISchemaIndex
 *  @{ */

/** Index field definition.
 * @see db_indexdef_t::fields, db_indexfield_init, db_indexfield_destroy */
typedef struct db_indexfield_t
{

#if DB_API_VER >= DB_API_100
    /** Number of the table field to include in the index. */
    db_fieldno_t   fieldno;
    /** Field flags: reserved for future use */
    db_flags_t     field_flags;
#endif

} db_indexfield_t;

DBDLL_API db_result_t        db_indexfield_init(db_indexfield_t*);
DBDLL_API db_result_t        db_indexfield_destroy(db_indexfield_t*);

#ifndef _DB_OMIT_INDEXTYPE_NAMES
/** Index Types */
typedef enum
{
    /** Default index type. */
    DB_INDEXTYPE_DEFAULT,
    /** B+tree index type. */
    DB_INDEXTYPE_BTREE
} db_indextype_t;
#endif

/** Index definition. 
 * @see db_create_index, db_describe_index, db_tabledef_t::indexes,
 * db_indexdef_init, db_indexdef_destroy, db_indexdef_set_indextype,
 * db_indexdef_set_field
 */
typedef struct db_indexdef_t
{
    db_alloc_t        db_alloc;

#if DB_API_VER >= DB_API_100

/** @cond INTERNAL */
#define _DBIDF_MANAGED_FIELDS 0x00001 /* fields are allocated from heap */
#define _DBIDF_INVALID        0x10000 /* object is in invalid state */
/** @endcond */

    /** Type of index. @see DB_INDEXTYPE_DEFAULT. */
    db_indextype_t    index_type;
    /** Name of index. */
    db_objname_t      index_name[DB_MAX_INDEX_NAME + 1];
    /**
     * Index mode.
     * One of:
     * - #DB_MULTISET_INDEX
     * - #DB_UNIQUE_INDEX
     * - #DB_PRIMARY_INDEX
     *
     * Combined with any of:
     * - #DB_NUMBERED_INDEX
     * - #DB_CLUSTERING_INDEX
     */
    db_flags_t        index_mode;
    db_fieldno_t      nfields; /**< Number of indexed fields. */
    db_indexfield_t * fields;  /**< Array of indexes fields. */
#endif

} db_indexdef_t;

DBDLL_API db_result_t        db_indexdef_init(db_indexdef_t*,
                                       db_heap_t heap);
DBDLL_API db_result_t        db_indexdef_destroy(db_indexdef_t*);

DBDLL_API db_result_t        db_indexdef_set_indextype(db_indexdef_t*,
                                                db_indextype_t);

/* manage set of index fields, subject to be extended */
DBDLL_API db_result_t        db_indexdef_set_field_count( db_indexdef_t*,
                                                  db_fieldno_t);
DBDLL_API db_result_t        db_indexdef_set_field( db_indexdef_t*,
                                            db_fieldno_t nfield,
                                            const db_indexfield_t* field);

#ifndef _DB_OMIT_TABLETYPE_NAMES
/**
 * Table Types
 * @ingroup CAPISchemaTable
 */
typedef enum
{
    /** Default table type. */
    DB_TABLETYPE_DEFAULT   = 0,
    /** Key heap table type, stored on disk. */
    DB_TABLETYPE_KHEAP     = 1,
#if DB_API_VER >= DB_API_103
    /** Memory table, stored on in-memory storage. */
    DB_TABLETYPE_MEMORY    = 2,
    /** Clustered table, stored on disk and grouped by a clustering index. */
    DB_TABLETYPE_CLUSTERED = 3,
#endif
#if DB_API_VER >= DB_API_111
    /** Snapshot isolation table, stored on disk and grouped by a clustering index. */
    DB_TABLETYPE_SNAPSHOT  = 4,
    /** Circular sequential table. */
    DB_TABLETYPE_CIRCULAR  = 5,
    /** Record table. */
    DB_TABLETYPE_RECORD    = 6,
#endif
} db_tabletype_t;
#endif

/** @} */

/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPISchemaConstraint
 *  @{ */ 

#if DB_API_VER >= DB_API_10A

/** The action cannot be performed on a referenced row. */
#define DB_FK_ACTION_RESTRICT       0
/** When the action is performed on key fields in a referenced row, the same
 * action is performed on referencing rows. */
#define DB_FK_ACTION_CASCADE        1
/** When the action is performed on key fields in a referenced row, all foreign
 * key fields in referencing rows are set to null. */
#define DB_FK_ACTION_SETNULL        2
/** When the action is performed on key fields in a referenced row, all foreign
 * key fields in referencing rows are set to their default values. */
#define DB_FK_ACTION_SETDEFAULT     3

/** Some fields in the foreign key may be null, in which case no row is
 * referenced. A row is only referenced when no foreign key fields are null. */
#define DB_FK_MATCH_SIMPLE          0
/** All fields in the foreign key must be null if any are null. A row is only
 * referenced when no foreign key fields are null. */
#define DB_FK_MATCH_FULL            1

/** The foreign key cannot be deferred until commit. */
#define DB_FK_NOT_DEFERRABLE        0
/** The foreign key can be deferred until commit. This feature is not
 * implemented. */
#define DB_FK_DEFERRABLE            1

/** The foreign key is initially immediate. */
#define DB_FK_CHECK_IMMEDIATE       0
/** The foreign key is initially deferred. This feature is not implemented. */
#define DB_FK_CHECK_DEFERRED        1

/**
 * Foreign key definition.
 */
typedef struct db_foreign_key_def_s
{
    /** Name of the foreign key constraint. Must be unique for each table. */
    db_objname_t    fk_name  [ DB_INDEX_NAME_SIZE ];
    /** Name of the table referenced by the foreign key. */
    db_objname_t    ref_table[ DB_TABLE_NAME_SIZE ];

    /** How to match multiple fields. @see DB_FK_MATCH_SIMPLE, DB_FK_MATCH_FULL */
    int8_t          match_option;
    /** Action to apply when a referenced key is updated.  @see
     * DB_FK_ACTION_RESTRICT, DB_FK_ACTION_CASCADE, DB_FK_ACTION_SETNULL,
     * DB_FK_ACTION_SETDEFAULT
     */
    int8_t          update_rule;
    /** Action to apply when a referenced row is deleted.  @see
     * DB_FK_ACTION_RESTRICT, DB_FK_ACTION_CASCADE, DB_FK_ACTION_SETNULL,
     * DB_FK_ACTION_SETDEFAULT
     */
    int8_t          delete_rule;
    /** Set whether the constraint can be deferred until commit. @see
     * DB_FK_NOT_DEFERRABLE, DB_FK_DEFERRABLE */
    int8_t          deferrable;
    /** Set whether the constraint is initially deferred until commit. @see
     * DB_FK_CHECK_IMMEDIATE, DB_FK_CHECK_DEFERRED */
    int8_t          check_time;

    /** Number of fields in the foreign key. */
    int8_t          nfields;
    /** List of fields in the foreign key. */
    struct
    {
        /** Field number in the original table. */
        db_fieldno_t    org_field;
        /** Field number in the referenced table. */
        db_fieldno_t    ref_field;
    } fields[ DB_MAX_FOREIGNKEY_FIELD_COUNT ];

} db_foreign_key_def_t;

#endif /* DB_API_10A */

/** @} */
/** @endcond */

/** @addtogroup CAPISchemaTable
 *  @{ */ 

/** Table definition.
 * @see db_create_table, db_describe_table, db_tabledef_init,
 * db_tabledef_destroy, db_tabledef_set_tabletype, db_tabledef_set_field_count,
 * db_tabledef_set_fields, db_tabledef_set_index_count,
 * db_tabledef_set_indexes, db_tabledef_set_index
 */
typedef struct db_tabledef_t
{
    db_alloc_t        db_alloc;

#if DB_API_VER >= DB_API_100
    /* mask flags */
/** @cond INTERNAL */
#define _DBTDF_MANAGED_FIELDS  0x00001u  /* fields are allocated from the heap */
#define _DBTDF_MANAGED_INDEXES 0x00002u  /* indexes are allocated from the heap */
#define _DBTDF_MANAGED_FOREIGNKEYS 0x00004u /* foreing keys are allocated from the heap */
#define _DBTDF_INVALID         0x10000u  /* something went wrong during operations */
/** @endcond */

    /** Table type: @see DB_TABLETYPE_DEFAULT, DB_TABLETYPE_KHEAP, DB_TABLETYPE_MEMORY, DB_TABLETYPE_CLUSTERED. */
    db_tabletype_t    table_type;
    /** Name of the table. */
    db_objname_t      table_name [ DB_MAX_TABLE_NAME + 1 ];

    db_fieldno_t      nfields;    /**< Number of fields in the table. */
    db_fielddef_t*    fields;     /**< Array of fields in the table. */

    db_len_t          nindexes;   /**< Number of indexes on the table. */
    db_indexdef_t*    indexes;    /**< Array of indexes on the table. */
#endif

#if DB_API_VER >= DB_API_10A
    db_len_t              nforeign_keys; /**< Number of foreign keys on the table. */
    db_foreign_key_def_t* foreign_keys;  /**< Array of foreign keys on the table. */
#endif /* DB_API_10A */

} db_tabledef_t;

DBDLL_API db_result_t        db_fielddef_init(db_fielddef_t*);
DBDLL_API db_result_t        db_fielddef_destroy(db_fielddef_t*);

/** @} */

/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPISQL
 *  @{ */ 

#if DB_API_VER >= DB_API_102
DBDLL_API db_result_t        db_paramdef_init(db_paramdef_t*);
DBDLL_API db_result_t        db_paramdef_destroy(db_paramdef_t*);
#endif

/** @} */
/** @endcond */


/** @addtogroup CAPISchemaTable
 *  @{ */ 

DBDLL_API db_result_t        db_tabledef_init(db_tabledef_t*,
                                              db_heap_t heap);
DBDLL_API db_result_t        db_tabledef_destroy(db_tabledef_t*);

DBDLL_API db_result_t        db_tabledef_set_tabletype(db_tabledef_t*,
                                                       db_tabletype_t);

DBDLL_API db_result_t        db_tabledef_set_field_count(db_tabledef_t*,
                                                         db_fieldno_t nfields );
DBDLL_API db_result_t        db_tabledef_set_field (db_tabledef_t*,
                                                    db_fieldno_t nfield,
                                                    const db_fielddef_t*);
DBDLL_API db_result_t        db_tabledef_set_fields(db_tabledef_t*,
                                                    const db_fielddef_t*,
                                                    db_fieldno_t nfields );

/** @} */

/** @addtogroup CAPISchemaIndex
 *  @{ */ 

DBDLL_API db_result_t        db_tabledef_set_index_count(db_tabledef_t*,
                                                         db_len_t nindexes );
DBDLL_API db_result_t        db_tabledef_set_indexes(db_tabledef_t*,
                                                     const db_indexdef_t*,
                                                     db_len_t nindexes );
DBDLL_API db_result_t        db_tabledef_set_index  (db_tabledef_t*,
                                                     db_len_t index,
                                                     const db_indexdef_t*);

/** @} */

/** @addtogroup CAPISchemaTable
 *  @{ */ 

/* table handling */
DBDLL_API db_result_t        db_create_table(db_t,
                                             const db_objname_t *,
                                             const db_tabledef_t *,
                                             db_flags_t);

DBDLL_API db_result_t        db_drop_table(db_t,
                                           const db_objname_t *);

DBDLL_API db_result_t        db_describe_table(db_t,
                                               const db_objname_t *,
                                               db_tabledef_t *,
                                               db_flags_t);

DBDLL_API db_result_t        db_add_field(db_t,
                                          const db_objname_t * table,
                                          const db_fielddef_t*);

#if DB_API_VER >= DB_API_110
DBDLL_API db_result_t        db_rename_table(db_t,
                                      const db_objname_t * old_table_name,
                                      const db_objname_t * new_table_name);

DBDLL_API db_result_t        db_rename_field(db_t,
                                      const db_objname_t * table,
                                      const db_objname_t * old_name,
                                      const db_objname_t * new_name);

DBDLL_API db_result_t        db_update_field(db_t,
                                      const db_objname_t * table,
                                      const db_objname_t * field,
                                      const db_fielddef_t*);
#endif

DBDLL_API db_result_t        db_drop_field(db_t,
                                           const db_objname_t * table,
                                           const db_objname_t * field);

/** @} */

/** @addtogroup CAPISchemaIndex
 *  @{ */ 

DBDLL_API db_result_t        db_create_index(db_t,
                                             const db_objname_t * table,
                                             const db_objname_t * index,
                                             const db_indexdef_t*);

DBDLL_API db_result_t        db_drop_index(db_t,
                                           const db_objname_t * table,
                                           const db_objname_t * index);

DBDLL_API db_result_t        db_describe_index(db_t,
                                               const db_objname_t * table,
                                               const db_objname_t * index,
                                               db_indexdef_t *);

#if DB_API_VER >= DB_API_110
DBDLL_API db_result_t        db_rename_index(db_t,
                                           const db_objname_t * table,
                                           const db_objname_t * old_name,
                                           const db_objname_t * new_name);
#endif

/** @} */

/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPISchemaConstraint
 *  @{ */ 

#if DB_API_VER >= DB_API_10A

DBDLL_API db_result_t        db_tabledef_set_foreign_key_count(db_tabledef_t*, db_len_t);
DBDLL_API db_result_t        db_tabledef_set_foreign_keys(db_tabledef_t*,
                                                          const db_foreign_key_def_t*,
                                                          db_len_t nkeys );
DBDLL_API db_result_t        db_tabledef_set_foreign_key(db_tabledef_t*,
                                                     db_len_t index,
                                                     const db_foreign_key_def_t*);


DBDLL_API db_result_t       db_create_foreign_key(db_t,
                                                  const db_objname_t * table,
                                                  const db_foreign_key_def_t *);

DBDLL_API db_result_t       db_drop_foreign_key(db_t,
                                                  const db_objname_t * table,
                                                  const db_objname_t * fkname);
#endif

#if DB_API_VER >= DB_API_110
DBDLL_API db_result_t       db_rename_foreign_key(db_t,
                                                  const db_objname_t * table,
                                                  const db_objname_t * old_name,
                                                  const db_objname_t * new_name);
#endif

/** @} */
/** @endcond */

/* DML */

/* Data Rows */
/** @addtogroup CAPIRow 
 *  @{ */ 

/* Common Routines */
DBDLL_API db_row_t           db_alloc_row(const db_bind_t *,
                                          db_fieldno_t nbinds);

DBDLL_API db_row_t           db_alloc_cursor_row(db_cursor_t);

DBDLL_API db_result_t        db_free_row(db_row_t);
DBDLL_API db_len_t           db_get_field_size(db_row_t, db_fieldno_t);
DBDLL_API db_vartype_t       db_get_field_type(db_row_t, db_fieldno_t);
DBDLL_API db_len_t           db_get_field_len(db_row_t, db_fieldno_t);
DBDLL_API db_result_t        db_set_field_len(db_row_t, db_fieldno_t, db_len_t);
DBDLL_API void *             db_get_field_buffer(db_row_t, db_fieldno_t);
#if DB_API_VER >= DB_API_106
DBDLL_API db_flags_t         db_get_field_flags(db_row_t hrow, db_fieldno_t nfield );
#endif

DBDLL_API db_len_t           db_get_field_data(db_row_t,
                                               db_fieldno_t,
                                               db_vartype_t  data_type,
                                               void *        data_ptr,
                                               db_len_t      data_size);

DBDLL_API db_result_t        db_set_field_data(db_row_t,
                                               db_fieldno_t,
                                               db_vartype_t   data_type,
                                               const void *   data_ptr,
                                               db_len_t       data_length);

DBDLL_API int                db_is_null(db_row_t, db_fieldno_t);
DBDLL_API db_result_t        db_set_null(db_row_t, db_fieldno_t);

DBDLL_API db_result_t        db_bind_field(db_row_t hrow, const db_bind_t *);
DBDLL_API db_result_t        db_unbind_field(db_row_t, db_fieldno_t);

/** @} */

/** @addtogroup CAPITableCursor 
 *  @{ */ 

/** Table cursor settings. This structure is used to specify settings when
 * creating a cursor on a table. Once the cursor is created, this structure can
 * be destroyed.
 *
 * @see db_table_cursor_init, db_table_cursor_destroy, db_open_table_cursor
 */
typedef struct db_table_cursor_t
{

#if DB_API_VER >= DB_API_100
    /** Index by which to sort the table. */
    const db_objname_t * index;
    /**
     * Available flags (all can be set):
     * - #DB_SCAN_FORWARD: Allow forward scan.
     * - #DB_SCAN_BACKWARD: Allow backward scan.
     * - #DB_CAN_MODIFY: Update/insert/delete are allowed.
     * - #DB_CAN_BOOKMARK: Bookmarks can be used with the cursor.
     * Select one of the following locking modes:
     * - #DB_LOCK_DEFAULT: Use current transaction's locking mode (default).
     * - #DB_LOCK_SHARED: Obtain shared locks when possible.
     * - #DB_LOCK_EXCLUSIVE: Obtain exclusive locks only.
     * Select one of the following isolation levels:
     * - #DB_DEFAULT_ISOLATION: Use current transaction's isolation level (default).
     * - #DB_READ_COMMITTED: Read committed isolation.
     * - #DB_REPEATABLE_READ: Repeatable read isolation.
     * - #DB_SERIALIZABLE: Serializable isolation.
     */
    db_flags_t flags;
#endif

#if DB_API_VER >= DB_API_105
	db_len_t sort_buffer_size;
#endif
} db_table_cursor_t;

DBDLL_API db_result_t        db_table_cursor_init(db_table_cursor_t *);
DBDLL_API db_result_t        db_table_cursor_destroy(db_table_cursor_t *);

DBDLL_API db_cursor_t        db_open_table_cursor(db_t,
                                            const db_objname_t * table,
                                            const db_table_cursor_t *);
/** @} */


/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPISQL 
 *  @{ */ 

#if DB_API_VER >= DB_API_10D
/**
 * Information about a cursor and its capabilities. 
 */
typedef struct
{

/** Table cursor. */
#define DB_CURSOR_KIND_TABLE        1
/** SQL select cursor. */
#define DB_CURSOR_KIND_SELECT       2
/** SQL data definition language cursor. */
#define DB_CURSOR_KIND_DDL          3
/** SQL data manipulation language cursor. */
#define DB_CURSOR_KIND_DML          4
/** SQL transaction control language cursor. */
#define DB_CURSOR_KIND_TCL          5

    int8_t      cursor_kind;            /**< Kind of cursor. */

/** Cursor can browse the result set in any direction. */
#define DB_CURSOR_INFO_BROWSABLE        0x00010u
/** Cursor has a static result set. */
#define DB_CURSOR_INFO_STATIC_CURSOR    0x00020u
/** Cursor has a dynamic result set. */
#define DB_CURSOR_INFO_DYNAMIC_CURSOR   0x00040u

    uint32_t    cursor_info;            /**< Cursor capabilities. */
    int32_t     cursor_type;            /**< Type of cursor for current or next execution. */

} db_cursor_info_t;
#endif
/** @endcond */

#if DB_API_VER >= DB_API_102
DBDLL_API db_cursor_t        db_prepare_sql_cursor(db_t, 
                                                   const char*,
                                                   db_flags_t);

DBDLL_API db_result_t        db_execute(db_cursor_t, db_row_t param_row, db_object_t param_object);
DBDLL_API db_result_t        db_unexecute(db_cursor_t);
DBDLL_API int                db_is_prepared(db_cursor_t);
DBDLL_API int                db_is_browsable(db_cursor_t);

#if DB_API_VER >= DB_API_105
DBDLL_API db_result_t        db_get_row_num(db_cursor_t hcursor, int64_t*);
#endif

DBDLL_API int                db_get_row_count(db_cursor_t);
#if DB_API_VER >= DB_API_10A
DBDLL_API db_result_t        db_get_row_count_ex(db_cursor_t hcursor, int32_t *);
#endif
DBDLL_API db_result_t        db_get_error_message(db_cursor_t, char **sz_msg);

/* SQL query parameters */
DBDLL_API db_row_t           db_alloc_param_row(db_cursor_t);
DBDLL_API int                db_get_param_count(db_cursor_t);
DBDLL_API db_result_t        db_get_param(db_cursor_t,
                                          db_fieldno_t paramno,
                                          db_paramdef_t *);
#endif

#if DB_API_VER >= DB_API_10D
DBDLL_API db_result_t        db_get_cursor_info(db_cursor_t, db_cursor_info_t *);
DBDLL_API db_result_t        db_set_cursor_type(db_cursor_t, int32_t);
#endif

/** @} */

/** @addtogroup CAPICursor
 *  @{ */
DBDLL_API db_cursor_t        db_duplicate_cursor(db_cursor_t,
                                          db_flags_t flags);
DBDLL_API db_result_t        db_close_cursor(db_cursor_t);
DBDLL_API db_flags_t         db_get_cursor_flags(db_cursor_t);

DBDLL_API db_fieldno_t       db_find_field(db_cursor_t, const db_objname_t *);
DBDLL_API db_fieldno_t       db_get_field_count(db_cursor_t);
DBDLL_API db_result_t        db_get_field(db_cursor_t,
                                          db_fieldno_t,
                                          db_fielddef_t *);

DBDLL_API int                db_bof(db_cursor_t);
DBDLL_API int                db_eof(db_cursor_t);

#if DB_API_VER >= DB_API_113
/** Use column-wise binding when fetching multiple rows */
#define DB_ROW_BIND_BY_COLUMN 0

DBDLL_API db_result_t        db_bind_columns(db_cursor_t, const db_bind_t *, db_fieldno_t nbinds, size_t row_array_size, size_t row_bind_type, size_t * num_rows_fetched);

DBDLL_API db_result_t        db_fetch_scroll(db_cursor_t hcursor, db_seek_position_t, int64_t offset, int64_t * num_rows_fetched);

#endif

#if DB_API_VER >= DB_API_10F
DBDLL_API db_result_t        db_set_position(db_cursor_t, db_seek_position_t, int64_t offset, int64_t * );
DBDLL_API db_result_t        db_check_position(db_cursor_t, db_flags_t, db_flags_t *);
#endif

DBDLL_API db_result_t        db_seek_first(db_cursor_t);
DBDLL_API db_result_t        db_seek_next(db_cursor_t);

DBDLL_API db_result_t        db_seek_prior(db_cursor_t);
DBDLL_API db_result_t        db_seek_last(db_cursor_t);
/** @} */

/** @addtogroup CAPITableCursor
 *  @{ */

#ifndef _DB_OMIT_SEEK_NAMES
/** Table seek flags. @ingroup CAPITableCursor @see db_seek, db_qseek. */
typedef enum
{
    /** Less than. */
    DB_SEEK_LESS             = 0,
    /** Less than or equal to. */
    DB_SEEK_LESS_OR_EQUAL    = 1,
    /** First exact match. */
    DB_SEEK_FIRST_EQUAL      = 2,
    /** Last exact match. */
    DB_SEEK_LAST_EQUAL       = 3,
    /** Greater than. */
    DB_SEEK_GREATER          = 4,
    /** Greater than or equal to. */
    DB_SEEK_GREATER_OR_EQUAL = 5,

    /** Equivalent to DB_SEEK_FIRST_EQUAL. */
    DB_SEEK_EQUAL            = DB_SEEK_FIRST_EQUAL
} db_seek_t;
#endif

DBDLL_API db_result_t        db_seek(db_cursor_t,
                                     db_seek_t,
                                     db_row_t,
                                     db_object_t,
                                     db_fieldno_t nfields);

#if DB_API_VER >= DB_API_111
DBDLL_API db_result_t        db_fetch_seek(db_cursor_t hcursor,
                                     db_seek_t seek,
                                     db_row_t hkey,
                                     db_object_t keyobject,
                                     db_fieldno_t nfields,
                                     db_row_t hdestination,
                                     db_object_t destinationobject,
                                     db_flags_t flags);
/** @} */

/** @addtogroup CAPICursor
 *  @{ */
DBDLL_API db_result_t        db_fetch_next(db_cursor_t hcursor,
                                           db_row_t hdestination,
                                           db_object_t destinationobject,
                                           db_flags_t flags);
#endif
/** @} */

/** @addtogroup CAPICursor
 *  @{ */
DBDLL_API db_result_t        db_fetch(db_cursor_t,
                                      db_row_t,
                                      db_object_t);
/** @} */

/** @addtogroup CAPITableCursor
 *  @{ */
DBDLL_API db_result_t        db_insert(db_cursor_t,
                                       db_row_t,
                                       db_object_t,
                                       db_flags_t);

DBDLL_API db_result_t        db_delete(db_cursor_t,
                                       db_flags_t);

DBDLL_API db_result_t        db_update(db_cursor_t,
                                       db_row_t,
                                       db_object_t);

#if DB_API_VER >= DB_API_106
DBDLL_API db_result_t        db_update_flags(db_cursor_t,
                                             db_row_t,
                                             db_object_t,
                                             db_flags_t);
#endif

DBDLL_API db_result_t        db_get_bookmark(db_cursor_t,
                                             db_oid_t *);

DBDLL_API db_result_t        db_goto_bookmark(db_cursor_t,
                                              const db_oid_t *);

DBDLL_API db_result_t        db_set_range(db_cursor_t  h,
                                          db_row_t     low_row,
                                          db_object_t  low_object,
                                          db_fieldno_t low_fields,
                                          db_row_t     high_row,
                                          db_object_t  high_object,
                                          db_fieldno_t high_fields );

#if DB_API_VER >= DB_API_105

DBDLL_API db_result_t        db_add_filter(db_cursor_t h, db_seek_t relation,
                                           db_row_t filter_row, db_object_t filter_row_object,
                                           const db_indexfield_t * fields, db_fieldno_t nfields);

DBDLL_API db_result_t        db_remove_filters(db_cursor_t);

DBDLL_API db_result_t        db_sort(db_cursor_t cursor,
                                     const db_indexfield_t * fields, db_fieldno_t nfields);

DBDLL_API int                db_is_sorted_by(db_cursor_t cursor,
                                             const db_indexfield_t * fields, db_fieldno_t nfields);

DBDLL_API db_result_t        db_get_row_num(db_cursor_t hcursor, int64_t*);

#endif

/* prelininaries */
DBDLL_API db_result_t        db_qseek(db_cursor_t,
                                      db_seek_t,
                                      const db_bind_t*,
                                      db_len_t,
                                      db_object_t,
                                      db_fieldno_t nfields);
/** @} */

/** @addtogroup CAPICursor
 *  @{ */
DBDLL_API db_result_t        db_qfetch(db_cursor_t,
                                       const db_bind_t*,
                                       db_len_t,
                                       db_object_t);
/** @} */

/** @addtogroup CAPITableCursor
 *  @{ */
DBDLL_API db_result_t        db_qinsert(db_cursor_t,
                                        const db_bind_t*,
                                        db_len_t,
                                        db_object_t,
                                        db_flags_t);
DBDLL_API db_result_t        db_qupdate(db_cursor_t,
                                        const db_bind_t*,
                                        db_len_t,
                                        db_object_t);

#if DB_API_VER >= DB_API_106
DBDLL_API db_result_t        db_qupdate_flags(db_cursor_t,
                                              const db_bind_t*,
                                              db_len_t,
                                              db_object_t,
                                              db_flags_t);
#endif

/** @} */

/** @addtogroup CAPISequence
 *  @{ */
DBDLL_API db_sequence_t      db_open_sequence(db_t, const db_objname_t *);
DBDLL_API db_sequence_t      db_duplicate_sequence(db_sequence_t);
DBDLL_API db_result_t        db_close_sequence(db_sequence_t);

DBDLL_API db_result_t        db_next_sequence(db_sequence_t,
                                              db_seqvalue_t*);

DBDLL_API db_result_t        db_curr_sequence(db_sequence_t,
                                              db_seqvalue_t*);
/** @} */


/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPILock
 *  @{ */
DBDLL_API db_hlock_t         db_lock(db_t, const db_oid_t *, db_flags_t lock_mode);
DBDLL_API db_result_t        db_unlock(db_t, const db_oid_t *, db_hlock_t);

DBDLL_API db_hlock_t         db_lock_table(db_t, const db_objname_t *, db_flags_t lock_mode);
DBDLL_API db_result_t        db_get_tableid(db_t, const db_objname_t *, db_oid_t*);
/** @} */
/** @endcond */

/** @addtogroup CAPIBookmark
 *  @{ */
DBDLL_API db_result_t        db_oid_init(db_oid_t*, db_heap_t);
DBDLL_API db_result_t        db_oid_destroy(db_oid_t *);
DBDLL_API db_result_t        db_oid_copy(db_oid_t * dst, const db_oid_t * src);
DBDLL_API int                db_oid_equal(const db_oid_t *, const db_oid_t *);
DBDLL_API db_result_t        db_oid_reset(db_oid_t * dst);
DBDLL_API db_result_t        db_oid_extract_tableid(db_oid_t *, const db_oid_t *);

DBDLL_API int                db_is_noid(const db_oid_t*);
DBDLL_API int                db_is_rowid(const db_oid_t*);
DBDLL_API int                db_is_tableid(const db_oid_t*);
/** @} */

/** @addtogroup CAPIConfiguration
 *  @{ */ 
DBDLL_API db_result_t        db_config_init(db_config_t*);
DBDLL_API db_result_t        db_config_destroy(db_config_t*);

DBDLL_API db_result_t        lm_config_init(lm_config_t*);
DBDLL_API db_result_t        lm_config_destroy(lm_config_t*);

DBDLL_API db_result_t        lm_local_config_init(lm_local_config_t*);
DBDLL_API db_result_t        lm_local_config_destroy(lm_local_config_t*);
/** @} */

/** @addtogroup CAPIRow
 *  @{ */ 
DBDLL_API db_result_t        db_bind_init(db_bind_t*);
DBDLL_API db_result_t        db_bind_destroy(db_bind_t*);
/** @} */


#if DB_API_VER >= DB_API_106
/** @cond INTERNAL */
/** @addtogroup CAPIReserved
 *  @{ */ 
DBDLL_API db_result_t        _db_open_dml_iterator(db_cursor_t, db_row_t param_row, db_object_t param_object);
DBDLL_API db_result_t        _db_dml_iterate(db_cursor_t, db_oid_t *);
DBDLL_API int                _db_is_updating(db_cursor_t);
DBDLL_API int                _db_is_inserting(db_cursor_t);
DBDLL_API db_result_t        _db_dml_update(db_cursor_t, const db_oid_t *, db_row_t);
DBDLL_API db_result_t        _db_dml_copy_field(db_cursor_t, db_fieldno_t, const db_oid_t *from, const db_oid_t *to);
DBDLL_API db_result_t        _db_param_assigned_col_index( db_cursor_t, db_fieldno_t *col, db_fieldno_t param );
/** @} */
/** @endcond */
#endif


#if DB_API_VER >= DB_API_101
/** @addtogroup CAPINotification
 *  @{ */
/** Data change notification event. @see db_wait, db_watch_table, db_goto_bookmark. */
typedef struct db_event_t
{
    uint16_t event_tag; /**< @see DB_WATCH_ROW_INSERT, DB_WATCH_ROW_UPDATE, DB_WATCH_ROW_DELETE */
    union {
        struct {
            uint32_t utid; /**< Notification id */
            db_oid_t row;  /**< Object id for the modified row */
        } row_insert;
        struct {
            uint32_t utid; /**< Notification id */
            db_oid_t row;  /**< Object id for the modified row */
        } row_update;
        struct {
            uint32_t utid; /**< Notification id */
            db_oid_t row;  /**< Object id for the deleted row */
        } row_delete;
    } u;
} db_event_t;

/* changes are monitored per database */
/* turn on waiting for table changes */
DBDLL_API db_result_t  db_watch_table(db_t, const db_objname_t *, db_flags_t /*flags*/, uint32_t utid);
DBDLL_API db_result_t  db_unwatch_table(db_t, const db_objname_t *);
DBDLL_API db_result_t  db_wait(db_t, db_wtime_t, db_event_t*);
#if DB_API_VER >= DB_API_10B
DBDLL_API db_result_t  db_wait_ex(db_t, db_wtime_t, db_event_t*, db_row_t row, db_row_t aux_row);
#endif

/** @} */
#endif /* DB_API_VER >= DB_API_101 */

#if DB_API_VER >= DB_API_10C
/** @cond INTERNAL */

/** User-defined connection protocol plugin handle. */
DB_DECLARE_HANDLE(db_udcp_handle_t);

typedef struct db_udcp_poll_handle_s
{
    db_udcp_handle_t    handle;
    short               events;
    short               revents;

    /* events & revents */
#define DB_UDCP_POLLIN      0x0001u
#define DB_UDCP_POLLPRI     0x0002u
#define DB_UDCP_POLLOUT     0x0004u

    /* revents only */
#define DB_UDCP_POLLERR     0x0100u
#define DB_UDCP_POLLHUP     0x0200u
#define DB_UDCP_POLLNVAL    0x0400u
} db_udcp_poll_handle_t;

typedef struct db_udcp_info_s
{
    const db_fname_t *  udcp_proto_name;
    int                 udcp_capabilities;
#define DB_UDCP_USER_AUTH    1

    int (*udcp_initialize)(void);
    int (*udcp_finalize)(void);

    int (*udcp_close)( db_udcp_handle_t );

    int (*udcp_listen)(db_udcp_handle_t*, void * udcp_param);
    int (*udcp_accept)(db_udcp_handle_t, db_udcp_handle_t *);
    int (*udcp_cancel)(db_udcp_handle_t);

    int (*udcp_connect)( db_udcp_handle_t*, void * udcp_param, const db_fname_t * host, const db_fname_t * port,
        const db_fname_t * user_name, const db_fname_t * password);

    int (*udcp_recv)( db_udcp_handle_t, void * buffer, size_t buffer_size, int timeout, size_t * bytes_recvd, int * time_rest );
    int (*udcp_send)( db_udcp_handle_t, const void * buffer, size_t buffer_size, size_t * bytes_sent );

    int (*udcp_poll)(db_udcp_poll_handle_t *, size_t nfds, int * timeout );
    int (*udcp_alive)(db_udcp_handle_t);

    /* reserved pointers. Should be set to NULL */
    void * udcp_reserved[4];    /* int (*udcp_wait_handle)(db_udcp_handle_t, uintptr_t *); */

} db_udcp_info_t;

typedef struct
{
    const char  * udcp_proto_name;
    void        * udcp_param;
} db_udcp_listen_t;

DBDLL_API db_result_t               db_udcp_register(const db_udcp_info_t *);
DBDLL_API db_result_t               db_udcp_unregister(const db_fname_t * udcp_proto_name);
DBDLL_API const db_udcp_info_t *    db_udcp_find(const db_fname_t * udcp_proto_name);

/** @endcond */
#endif

#if DB_API_VER >= DB_API_104
/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPIServer
 *  @{ */

/**
 * IPC server configuration.
 *
 * @see db_server_config_init, db_server_config_destroy, db_server_start
 */
typedef struct db_server_config_t
{
    /** @name TCP configuration
     *  @{ */
    uint32_t bind_addr;
    uint16_t bind_port;

    uint32_t max_connections;
    /** @} */

#if DB_API_VER >= DB_API_107
    /** @name Shared memory configuration
     *  @{ */
    int                shm_flags;
    uint32_t           shm_mem_size;
    const db_fname_t * shm_name;
    /** @} */
#endif

#if DB_API_VER >= DB_API_10C
    /** @name User-defined connection protocol support
     *  @{ */
    size_t                  udcp_nlisteners;
    const db_udcp_listen_t* udcp_listeners;
    /** @} */
/** @endcond */
#endif

} db_server_config_t;

DBDLL_API db_result_t db_server_config_init(db_server_config_t *);
DBDLL_API db_result_t db_server_config_destroy(db_server_config_t *);

DBDLL_API db_result_t db_server_start(const db_server_config_t *);
DBDLL_API db_result_t db_server_stop(db_flags_t);
DBDLL_API int32_t db_server_connection_count(void);
#if DB_API_VER >= DB_API_10C
DBDLL_API db_result_t db_mount_storage(const db_fname_t * file_name, const db_fname_t * alias, const db_storage_config_t *);
DBDLL_API db_result_t db_unmount_storage(const db_fname_t *);
#endif

/** @} */
#endif /* DB_API_VER >= DB_API_104 */

#if DB_API_VER >= DB_API_105

/** @addtogroup CAPIDatabase
 *  @{ */
DBDLL_API int db_get_prio(db_t);
DBDLL_API int db_set_prio(db_t, int prio);
/** @} */

#endif /* DB_API_VER >= DB_API_105 */

#if DB_API_VER >= DB_API_101
/* static database information */

/** @addtogroup CAPIConfiguration
 *  @{ */

DBDLL_API uintptr_t db_info( db_t, int info_tag );

#if DB_API_VER >= DB_API_105

/* Note: Trace facilities are also listed in oslib/db_dump.h */
#define DB_TRACE_USERMSG    0x00000001u  /**< User message debug facility */
#define DB_TRACE_BUFMGR     0x00000002u  /**< Buffer manager debug facility */
#define DB_TRACE_LOCKMGR    0x00000004u  /**< Lock manager debug facility */
#define DB_TRACE_LOGMGR     0x00000008u  /**< Log manager debug facility */
#define DB_TRACE_SPACEMGR   0x00000010u  /**< Space manager debug facility */
#define DB_TRACE_TXMGR      0x00000020u  /**< Transaction manager debug facility */
#define DB_TRACE_CATALOG    0x00000040u  /**< Catalog debug facility */
#define DB_TRACE_OSLIB      0x00000080u  /**< OS layer debug facility */
#define DB_TRACE_CAPI       0x00000100u  /**< C API debug facility */
#define DB_TRACE_DUMP       0x00000200u  /**< General message debug facility */
#define DB_TRACE_MEMTABLE   0x00000400u  /**< Memory storage component */
#define DB_TRACE_REP        0x00000800u  /**< Replication component */
#define DB_TRACE_BTREE      0x00001000u  /**< Btree component */
#define DB_TRACE_HEAP       0x00002000u  /**< Memory allocations */
#define DB_TRACE_DISKTABLE  0x00004000u  /**< FileStorage component */
#define DB_TRACE_SQL        0x00008000u  /**< SQL component */
#define DB_TRACE_IPC        0x00010000u  /**< IPC client/server component */
#define DB_TRACE_JOURNAL    0x00020000u  /**< Journal rotation and archiving */
#define DB_TRACE_BTREE_TRAV 0x00040000u  /**< Btree component traversal */
#define DB_TRACE_STREAM     0x00080000u  /**< Stream processing */
#define DB_TRACE_MAX        0x70000000u  /**< max possible trace facility */
#define DB_TRACE_ALL        0x7FFFFFFFu  /**< all facilities included */

DBDLL_API void db_set_trace(const char * trace_file, uint32_t enable_mask, uint32_t disable_mask);

#endif /* DB_API_105 */

/** @} */

/** @addtogroup CAPITransaction
 *  @{ */
#if DB_API_VER >= DB_API_107

/** Savepoint handle. @see CAPITransaction @ingroup CAPITransaction */
DB_DECLARE_HANDLE(db_savepoint_t);

#ifndef DB_OMIT_SAVEPOINT_NAMES
/** Set savepoint with default behavior. */
#define DB_SAVEPOINT_DEFAULT    0u
/** Set savepoint only if no existing savepoint has the same name. */
#define DB_SAVEPOINT_UNIQUE     1u
/** Nest savepoints with the same name. */
#define DB_SAVEPOINT_NESTED     2u
/** Replace savepoints with the same name. */
#define DB_SAVEPOINT_OVERRIDE   3u
#endif

DBDLL_API db_savepoint_t     db_set_savepoint(db_t, const db_objname_t *, db_flags_t flags);
DBDLL_API db_savepoint_t     db_find_savepoint(db_t, const db_objname_t *);
DBDLL_API db_result_t        db_release_savepoint(db_t, db_savepoint_t);
DBDLL_API db_result_t        db_rollback_savepoint(db_t, db_savepoint_t);

#endif /* DB_API_107 */
/** @} */

#if DB_API_VER >= DB_API_108
/** Measured statistics item. */
typedef struct db_statitem_s
{
    db_counter_t cur_value; /**< Current value. */
    db_counter_t max_value; /**< Maximum value recorded since last reset. */
} db_statitem_t;

/**
 * Count ITTIA DB C API handles opened by the application to measure resource
 * usage and prevent leaks. If an application closes handles correctly,
 * db.cur_value, cursor.cur_value, and seq.cur_value should be zero when all
 * storages are closed.
 *
 * @see db_api_statistics, db_done_ex
 */
typedef struct db_api_statistics_s
{
    /** True when API statistics are available. Some builds may not collect
     * these statistics. */
    int have_statistics;

    db_statitem_t db;       /**< Number of database handles open. @see db_t */
    db_statitem_t row;      /**< Number of rows open. @see db_row_t */
    db_statitem_t cursor;   /**< Number of cursors open. @see db_cursor_t */
    db_statitem_t seq;      /**< Number of sequences open. @see db_sequence_t */
    db_statitem_t seqdef;   /**< Number of sequence definitions open. @see db_seqdef_t */
    db_statitem_t tabledef; /**< Number of table definitions open. @see db_tabledef_t */
    db_statitem_t indexdef; /**< Number of index definitions open. @see db_indexdef_t */
    db_statitem_t oid;      /**< Number of object IDs open. @see db_oid_t */

} db_api_statistics_t;

/**
 * Lock manager statistics.
 * @see db_lm_statistics, db_done_ex
 */
typedef struct db_lm_statistics_s
{
    /** True when lock manager statistics are available. Some builds may not
     * collect these statistics. */
    int have_statistics;

    db_statitem_t nlocks;   /**< Number of locks in use. */
    db_statitem_t nowners;  /**< Number of connections with open locks. */
    db_statitem_t nobjects; /**< Number of locked database objects. */
} db_lm_statistics_t;

/**
 * Statistics for memory allocation with the built-in allocator. Only memory
 * allocated internally by ITTIA DB is tracked, but the amount can vary with
 * application behavior.
 *
 * @see db_mem_statistics, db_done_ex, db_init_ex
 */
typedef struct db_mem_statistics_s
{
    /**
     * True when memory allocation statistics are available. These statistics
     * are only available when the built-in allocator has been enabled, the
     * #DB_MEMFLAGS_TRACE flag is set, and the QA library is linked.
     *
     * @see db_init_ex */
    int have_statistics;

    db_statitem_t nreq; /**< Number of outstanding allocations. */
    struct
    {
        /** Total heap memory consumed, including overhead, in bytes. */
        db_statitem_t sys;

        /** Total allocated space, excluding overhead, in bytes. */
        db_statitem_t user;

        /** Maximum individual allocation request, in bytes, since reset. */
        size_t max_alloc;
    } actual_bytes;

    struct
    {
        /* Upper bound for the estimated number of blocks required for current
         * allocations. This value is computed as though each request uses at
         * least one full block, even though the actual number of blocks used
         * may be less in practice. */
        db_statitem_t heap;

        /** Maximum number of blocks required for an individual allocation
         * since reset. */
        size_t max_alloc;
    } estimate_blocks;

    size_t num_segs;    /**< Number of segments used for at least one allocation. */
    size_t page_size;   /**< Block size (minimum unit of allocation). */
    size_t heap_size;   /**< Total memory configured for the allocator. */
} db_mem_statistics_t;

#define DB_STATISTICS_QUERY     0   /**< Flag to only query statistics. */
#define DB_STATISTICS_RESET     1   /**< Flag to reset max values after statistics are read. */
#define DB_STATISTICS_ENABLE    2   /**< Flag to enable statistics collection. */
#define DB_STATISTICS_DISABLE   4   /**< Flag to disable statistics collection. */

DBDLL_API int db_api_statistics(db_api_statistics_t *, int);
DBDLL_API int db_lm_statistics(db_lm_statistics_t *, int);
DBDLL_API int db_mem_statistics(db_mem_statistics_t *, int);

#endif /* DB_API_108 */

#if DB_API_VER >= DB_API_109
/** @cond ITTIA_DB_SQL */
/** @addtogroup CAPIReplication Replication
 *  @{ */ 

/** Special value for a peer address column: do not replicate the row with any peer. */
#define DB_REP_ADDRESS_NONE     0
/** Special value for a peer address column: share row with all replication peers. */
#define DB_REP_ADDRESS_ALL      INT32_MAX

#define DB_REP_MODE_NONE        0u   /**< Do not participate in replication. */
#define DB_REP_MODE_IN          1u   /**< Receive changes from replication peers. */
#define DB_REP_MODE_OUT         2u   /**< Send changes to replication peers. */
/** Send and receive changes. */
#define DB_REP_MODE_INOUT       (DB_REP_MODE_IN | DB_REP_MODE_OUT)
/** Relay changes received from one peer to all other peers. */
#define DB_REP_MODE_RELAY       (4u | DB_REP_MODE_INOUT)

/* state column values */
#define DB_REP_STATE_LOCAL      0   /**< Last change was local. */
#define DB_REP_STATE_DELIVERY   1   /**< Last change was local, the row delivery is pending. */
#define DB_REP_STATE_REMOTE     2   /**< Last change was remote. */
#define DB_REP_STATE_DELIVERED  3   /**< Changes were delivered to a peer. */
#define DB_REP_STATE_REFUSED    4   /**< Changes were refused by a peer due to conflicts. */
#define DB_REP_STATE_IGNORED    5   /**< Changes were ignored by a peer. */

/* conflict resolution */

#define DB_REP_RESOLVE_PRIORITY_MIN  0x00001u     /**< Minimum possible priority. */
#define DB_REP_RESOLVE_PRIORITY_MAX  0x000feu     /**< Maximum possible priority. */

/* special priority values */
#define DB_REP_RESOLVE_ACCEPT        0x00000u      /**< Always accept conflicting changes. */
#define DB_REP_RESOLVE_REFUSE        0x000ffu      /**< Always refuse conflicting changes. */
#define DB_REP_RESOLVE_PRIORITY_MASK 0x000ffu      /**< Priority bits for insert_resolve, update_resolve, and delete_resolve. */

/* modifiers */
#define DB_REP_RESOLVE_EXCL          0x01000u       /**< Perform this operation exclusively.
                                                     * Otherwise, insert will update when the row already exists
                                                     * and update will insert when the row doesn't exist.
                                                     */
#define DB_REP_RESOLVE_DISABLE       0x02000u      /**< Disable input operation. */

#define DB_REP_RESOLVE_NOSEND        0x04000u      /**< Do not generate operation. */

#define DB_REP_RESOLVE_NOCVTERROR    0x08000u      /**< Ignore conversion errors. */

/**
 * Replication settings for a table.
 */
typedef struct db_rep_table_info_s
{
    uint32_t     rep_mode;         /**< Replication mode controls if and when a table participates in replication. */
    uint32_t     insert_resolve;   /**< Conflict resolution policy for insert operations. */
    uint32_t     update_resolve;   /**< Conflict resolution policy for update operations. */
    uint32_t     delete_resolve;   /**< Conflict resolution policy for delete operations. */
    db_objname_t peer_column[ DB_MAX_FIELD_NAME + 1];  /**< Name of column used to store peer addresses. */
    db_objname_t state_column[ DB_MAX_FIELD_NAME + 1]; /**< Name of column used to store replication state, for informational purposes only. */
    db_objname_t stamp_column[ DB_MAX_FIELD_NAME + 1]; /**< Conflict resolution stamp column. */
    db_objname_t rid_column[ DB_MAX_FIELD_NAME + 1];   /**< Name of column used to store peer row ID, for informational purposes only. */
    db_objname_t rep_index[ DB_MAX_INDEX_NAME + 1 ];   /**< Name of index used to find rows. */
} db_rep_table_info_t;

/**
 * Replication journal information.
 */
typedef struct db_rep_journal_info_s
{
    db_ulargeint_t journal_num; /**< Journal file number. */
} db_rep_journal_info_t;

#if DB_API_VER >= DB_API_10C
/**
 * Replication snapshot information.
 * @see db_rep_snapshot_ex
 */
typedef struct db_rep_snapshot_info_s
{
    db_flags_t flags;
    const db_auth_info_t * auth_info;
} db_rep_snapshot_info_t;
#endif

DBDLL_API db_result_t db_rep_table_query(db_t,
                    const db_objname_t * table_name, db_rep_table_info_t *);

DBDLL_API db_result_t db_rep_table_set(db_t, const db_objname_t * table_name,
                    const db_rep_table_info_t *, db_flags_t flags);

DBDLL_API db_result_t db_rep_load(db_t, const db_fname_t * journal_name,
                    db_flags_t file_flags);

DBDLL_API db_result_t db_rep_snapshot(db_t,
                                      const db_objname_t * table,
                                      const db_objname_t * peer_name,
                                      db_flags_t);

#if DB_API_VER >= DB_API_10C
DBDLL_API db_result_t db_rep_snapshot_ex(db_t,
                                      const db_objname_t * table,
                                      const db_objname_t * peer_name,
                                      const db_rep_snapshot_info_t *);
#endif

DBDLL_API db_result_t db_get_journal_name(db_t, const db_ulargeint_t*, db_fname_t * name_buf, db_len_t buf_len);
DBDLL_API db_result_t db_rep_journal_info(db_t, db_rep_journal_info_t * );
DBDLL_API db_result_t _db_rep_switch_journal(db_t, db_rep_journal_info_t *);

#define DB_REPTYPE_NONE    0  /**< Replication with peer is disabled. */
#define DB_REPTYPE_ADHOC   1  /**< Ad hoc replication by explicit exchange. */
#define DB_REPTYPE_SYNC    2  /**< Sync replication on commit. */

#define DB_REP_EXCHANGE_AUTH_ONLY 1 /**< Connect and authenticate, but don't send or receive changes. */

/**
 * Replication peer definition.
 */
typedef struct db_rep_peerdef_t
{
    /**
     * Type of replication to use for this peer. One of:
     * - #DB_REPTYPE_NONE
     * - #DB_REPTYPE_ADHOC
     * - #DB_REPTYPE_SYNC
     */
    int32_t             rep_type;

    /**
     * Replication of address configured in peer. This is compared with the
     * replication address stored in the peer database to confirm the peer's
     * identity. It can also be set in a table's peer_column to control which
     * rows are exchanged with which peers.
     */
    db_rep_address_t    peer_address;

    /**
     * Location of the peer database in the same URI format used to open and
     * create database files.
     * @see db_open_database_file
     */
    db_fname_t          peer_uri[DB_MAX_PEER_URI + 1];
} db_rep_peerdef_t;

DBDLL_API db_result_t db_rep_peerdef_init(db_rep_peerdef_t*);
DBDLL_API db_result_t db_rep_peerdef_destroy(db_rep_peerdef_t*);

DBDLL_API db_result_t db_rep_create_peer(db_t, const db_objname_t *, const db_rep_peerdef_t *);
DBDLL_API db_result_t db_rep_drop_peer(db_t, const db_objname_t *);
DBDLL_API db_result_t db_rep_describe_peer(db_t, const db_objname_t *, db_rep_peerdef_t *);
DBDLL_API db_result_t db_rep_alter_peer(db_t, const db_objname_t *, const db_rep_peerdef_t *);
#if DB_API_VER >= DB_API_10C
DBDLL_API db_result_t db_rep_peer_credentials(db_t, const db_objname_t *, const db_auth_info_t*, db_flags_t);
#endif

DBDLL_API db_result_t db_rep_exchange(db_t, const db_objname_t *, db_flags_t);

#if DB_API_VER >= DB_API_112
typedef struct db_rep_exchange_statistics_s
{
    /** Units per second for time members. */
    uint64_t frequency;

    uint64_t send_transaction_count;
    uint64_t recv_transaction_count;

    uint64_t exchange_total_time;
    uint64_t send_start_time;
    uint64_t send_transactions_time;
    uint64_t send_confirmation_time;
    uint64_t send_update_state_time;
    uint64_t recv_transactions_time;
    uint64_t recv_update_state_time;
} db_rep_exchange_statistics_t;
#endif

#if DB_API_VER >= DB_API_10C
/**
 * Replication exchange information.
 */
typedef struct
{
    db_flags_t flags;
    const db_auth_info_t * auth_info;
#if DB_API_VER >= DB_API_112
    db_rep_exchange_statistics_t * exchange_statistics;
#endif
} db_rep_exchange_t;

DBDLL_API db_result_t db_rep_exchange_ex(db_t, const db_objname_t *, const db_rep_exchange_t*);
#endif

/**
 * Database replication configuration.
 */
typedef struct db_rep_config_t
{
    db_rep_address_t rep_address;  /**< Replication address. */
} db_rep_config_t;

DBDLL_API db_result_t db_rep_config_init(db_rep_config_t *);
DBDLL_API db_result_t db_rep_config_destroy(db_rep_config_t *);
DBDLL_API db_result_t db_rep_set_config(db_t, const db_rep_config_t *);
DBDLL_API db_result_t db_rep_get_config(db_t, db_rep_config_t *);

DBDLL_API db_result_t db_rep_request_access(const db_fname_t * uri,
                                            void * udcp_param,
                                            const db_auth_info_t *,
                                            db_rep_config_t *,
                                            db_rep_address_t * peer_address,
                                            db_row_t auth_token,
                                            db_object_t uobject,
                                            db_flags_t flags);

DBDLL_API int db_get_error(void);

/** @} */
/** @endcond */
#endif /* DB_API_109 */



#endif /* DB_API_101 */

#if DB_API_VER >= DB_API_10D
/* Check index consistency. */
DBDLL_API int _db_check_index(db_t,
                                      const db_objname_t * table_name,
                                      const db_objname_t * index_name);

DBDLL_API db_result_t _db_repair_index(db_t,
                                      const db_objname_t * table_name,
                                      const db_objname_t * index_name);
#endif

C_HEADER_END

/* names section. We use underscores to avoid name clashing when
 * wrapper defines own set of names with same purposes
 */

/** @name Lock Type
 *  @{ */
/** @ingroup CAPILock */
#ifndef _DB_OMIT_LOCK_MODE_NAMES
/** Default lock mode. */
#define DB_LOCK_DEFAULT          0x00000000u
/** Obtain shared locks when possible. */
#define DB_LOCK_SHARED           0x00000001u
/** Obtain exclusive locks only. */
#define DB_LOCK_EXCLUSIVE        0x00000002u
#define DB_LOCK_MODE_MASK        0x00000003u
#endif
/** @} */

/** @name Cursor Scan Flags
 *  @{ */
/** @ingroup CAPICursor */
#ifndef _DB_OMIT_SCAN_NAMES
/** Allow forward scan. */
#define DB_SCAN_FORWARD          0x00000004u
/** Allow backward scan. */
#define DB_SCAN_BACKWARD         0x00000008u
#define DB_SCAN_MASK             0x0000000Cu
#endif
/** @} */

/** @name Transaction Isolation Levels
 *  @{ */
/** @ingroup CAPITransaction */
#ifndef _DB_OMIT_ISOLATION_NAMES
/** Default isolation mode. */
#define DB_DEFAULT_ISOLATION     0x00000000u
/** Read committed isolation. */
#define DB_READ_COMMITTED        0x00000010u
/** Repeatable read isolation. */
#define DB_REPEATABLE_READ       0x00000020u
/** Serializable isolation. */
#define DB_SERIALIZABLE          0x00000030u
#define DB_ISOLATION_MASK        0x000000F0u
#endif
/** @} */

/** @name Cursor Capability Flags
 *  @{ */
/** @ingroup CAPICursor */
#ifndef _DB_OMIT_CURSOR_NAMES
/** Update/insert/delete are allowed. */
#define DB_CAN_MODIFY            0x00000100u
/** Bookmarks can be used with the cursor. */
#define DB_CAN_BOOKMARK          0x00000200u
#define DB_CURSOR_MASK           0x00000300u


/** A forward-only cursor cannot seek to prior rows or directly to the last row. */
#define DB_CURSOR_TYPE_FORWARD   0x00001000u
/** A static cursor buffers each row; once visited, the value of a row will not change until the cursor is closed or unexecuted. */
#define DB_CURSOR_TYPE_STATIC    0x00002000u
/** A dynamic cursor is sensitive to changes in the result set, but only if visible to the connection. */
#define DB_CURSOR_TYPE_DYNAMIC   0x00003000u
/** Used in combination with a cursor type; fail if that cursor type is not supported. */
#define DB_CURSOR_TYPE_EXCL      0x00008000u
#define DB_CURSOR_TYPE_MASK      0x00007000u

/** Query string and literals use ANSI encoding. */
#define DB_CURSOR_ENCODING_ANSI  0x00000000u
/** Query string and literals use UTF-8 encoding. */
#define DB_CURSOR_ENCODING_UTF8  0x00010000u
/** Query string and literals use UTF-16 encoding. */
#define DB_CURSOR_ENCODING_UTF16 0x00020000u
/** Query string and literals use UTF-32 encoding. */
#define DB_CURSOR_ENCODING_UTF32 0x00030000u
#define DB_CURSOR_ENCODING_MASK  0x00030000u
#endif

/** @} */

/** @name Transaction Completion Modes
 *  @{ */
/** @ingroup CAPITransaction */
#ifndef _DB_OMIT_COMPLETION_NAMES
/** Default completion mode. */
#define DB_DEFAULT_COMPLETION    0x00000000u
/** Lazy completion. */
#define DB_LAZY_COMPLETION       0x01000000u
/** Immediate completion. */
#define DB_FORCED_COMPLETION     0x02000000u
/** Group completion. */
#define DB_GROUP_COMPLETION      0x03000000u
#define DB_COMPLETION_MASK       0x07000000u
#endif
/** @} */

#define DB_AUTOCOMMIT            0x08000000u

/** @name Lock Duration
 *  @{ */
/** @ingroup CAPILock */
#ifndef _DB_OMIT_LOCKING_NAMES
/** Return immediately if lock can't be granted. */
#define DB_TRY_LOCK              0x00010000u
/** Release lock automatically when transaction is finished. */
#define DB_COMMIT_LOCK           0x00060000u
/** Release lock manually before the transaction is finished. */
#define DB_INSTANT_LOCK          0x00020000u
/** Release lock manually */
#define DB_MANUAL_LOCK           0x00040000u
#define DB_LOCK_DURATION_MASK    0x00060000u
#define DB_LOCKING_MASK          0x00070000u
#endif
/** @} */

/** @name Flush Mode
 *  @{ */
/** @ingroup CAPITransaction */
#ifndef _DB_OMIT_FLUSH_NAMES
/** Flush only the journal. */
#define DB_FLUSH_JOURNAL         0x00000000u
/** Flush both the journal and storage. */
#define DB_FLUSH_STORAGE         0x10000000u
#define DB_FLUSH_MASK            0x10000000u
#endif
/** @} */

/** @name Index Mode
 *  @{ */
/** @ingroup CAPISchemaIndex */
#ifndef _DB_OMIT_INDEX_NAMES
/** Multiset (non-unique) index. */
#define DB_MULTISET_INDEX        0x00000000u
/** Unique index. */
#define DB_UNIQUE_INDEX          0x20000000u
/** Primary key index. */
#define DB_PRIMARY_INDEX         0x30000000u

/** Numbered index. @see db_get_row_num. */
#define DB_NUMBERED_INDEX        0x40000000u
/** The index used to cluster a table. @see DB_TABLETYPE_CLUSTERED. */
#define DB_CLUSTERING_INDEX      0x08000000u
#define DB_INDEX_MASK            (DB_INDEX_MODE_MASK | DB_NUMBERED_INDEX | DB_CLUSTERING_INDEX)
#define DB_INDEX_MODE_MASK       0x30000000u
/** @} */

#endif

#ifndef _DB_OMIT_MEM_NAMES
/** Use minimal amount of memory possible. */
#define DB_MEM_TIGHT             1
/** Use a small amount of memory (several times the minimum). */
#define DB_MEM_COMPACT           2
/** Use a large amount of memory (several orders of magnitude larger than the
 * minimum). */
#define DB_MEM_LARGE             3
#endif

/** @name Field Flags
 *  @{ */
/** @ingroup CAPISchemaTable */
#ifndef _DB_OMIT_FIELD_FLAG_NAMES
/** Field can be NULL. */
#define DB_NULLABLE              0u
/** Field cannot be NULL. */
#define DB_NOT_NULL              1u
#define DB_NULL_MASK             (DB_NOT_NULL | DB_NULLABLE)
/** Field is generated by identity. */
#define DB_IDENTITY              2u
#define DB_GENERATED_MASK        (DB_IDENTITY)
#endif
/** @} */

/** @name Insert Flags
 *  @{ */
/** @ingroup CAPITableCursor */
#ifndef _DB_OMIT_INSERT_FLAG_NAMES
/* insert flags */
/** Move the cursor position to the inserted record. */
#define DB_INSERT_SEEK_NEW       1u
#define DB_INSERT_SEEK_MASK      0x07u
#endif
/** @} */

/** @name Update Flags
 *  @{ */
/** @ingroup CAPITableCursor */
#ifndef _DB_OMIT_UPDATE_FLAG_NAMES
/** Move the cursor position to the new position of the current record, if the
 * record's position has changed after the update. */
#define DB_UPDATE_SEEK_NEW       1u
/** Move the cursor position to the next record, based on the position of the
 * record before the update. */
#define DB_UPDATE_SEEK_NEXT      2u
/** Move the cursor position to the previous record, based on the position of
 * the record before the update. */
#define DB_UPDATE_SEEK_PRIOR     3u
#define DB_UPDATE_SEEK_MASK      0x07
#endif
/** @} */

/** @name Delete Flags
 *  @{ */
/** @ingroup CAPITableCursor */
#ifndef _DB_OMIT_DELETE_FLAG_NAMES
/* delete  flags */
/** Move the cursor position to the next record. */
#define DB_DELETE_SEEK_NEXT      1u
/** Move the cursor position to the prior record. */
#define DB_DELETE_SEEK_PRIOR     2u
#define DB_DELETE_SEEK_MASK      0x07u
#endif
/** @} */

/** @name Length Indicator Values
 *  @{ */
/** @ingroup CAPIRow */
#ifndef _DB_OMIT_BIND_NAMES
/** Indicates that the field is NULL. */
#if DB_API_VER >= DB_API_103
#define DB_FIELD_NULL            DB_LEN_CONST(-1)
#else
#define DB_FIELD_NULL            DB_LEN_CONST(-2)
#endif
/** Treat field as a NULL-terminated string. */
#define DB_NTS                   DB_LEN_CONST(-3)
/** For internal use only. */
#define DB_BLOB_CHSIZE           DB_LEN_CONST(-4)
/** Manage length automatically. */
#define DB_AUTOFIELD             DB_LEN_CONST(-5)
#endif
/** @} */

#ifndef _DB_OMIT_CONCURRENCY_NAMES
/** Only allow concurrent connections from a single process. */
#define DB_SINGLE_PROCESS        1
#endif

/** @name Bind Types
 *  @{ */
/** @ingroup CAPIRow */
#ifndef _DB_OMIT_BIND_NAMES
/** Relative binding using memory offset */
#define DB_BIND_RELATIVE         0x00001u
/** Absolute binding using memory address */
#define DB_BIND_ABSOLUTE         0x00000u
#if DB_API_VER >= DB_API_106
#define DB_BIND_LATE_BINDING     0x80000u

#define DB_BIND_MASK (DB_BIND_ABSOLUTE | DB_BIND_RELATIVE | DB_BIND_LATE_BINDING)
#else
#define DB_BIND_MASK (DB_BIND_ABSOLUTE | DB_BIND_RELATIVE)
#endif
#endif
/** @} */

#ifndef _DB_OMIT_MISC_NAMES
/** Use the original flags when a cursor is duplicated. @see db_duplicate_cursor */
#define DB_DUPLICATE_SAME_FLAGS  (-1)
#endif

#ifndef _DB_OMIT_STORAGE_FLAGS
/** @name File Modes
 * Flags for db_file_storage_config_t::file_mode.
 *  @{ */
/** @ingroup CAPIDatabase */
/** Open database for reading only. */
#define DB_READ_ONLY            0x0001u
/** Disable logging. */
#define DB_NOLOGGING            0x0002u
/** Disable locking. */
#define DB_NOLOCKING            0x0004u
/** File name is in UTF-8 encoding, default is ANSI encoding. */
#define DB_UTF8_NAME            0x0008u
/** Write database pages atomically, even if the storage media does not support atomic writes. */
#define DB_ATOMIC_WRITE         0x0010u
/** Wait for connection lock instead of try lock */
#define DB_CONN_LOCK            0x0020u
/** Open database even if a required log file is missing. */
#define DB_RISK_INCONSISTENCY   0x0040u
#if DB_API_VER >= DB_API_111
/** Use new snapshot file format. */
#define DB_SNAPSHOT_STORAGE     0x0080u
#endif
/** Verify checksums when data is read from the database file. */
#define DB_VERIFY_CHECKSUMS     0x0100u
/** @} File Modes */

/** @name Database Storage Types
 *  @{ */
/** @ingroup CAPIDatabase */
/** File-based storage. */
#define DB_FILE_STORAGE         0x1000u
/** Memory-based storage. */
#define DB_MEMORY_STORAGE       0x2000u
/** @} Database Storage Types */
#define DB_FILE_TYPE_MASK       0xF000u

#if DB_API_VER >= DB_API_102
/** @name File Interfaces
 *  @{ */
/** @ingroup CAPIDatabase */
/** Default file system interface. */
#define DB_FILE_DEFFS           0x00000u
/** Win32 API file system interface. */
#define DB_FILE_WIN32           0x10000u
/** POSIX file system interface. */
#define DB_FILE_POSIX           0x20000u
/** YAFFS file system interface. */
#define DB_FILE_YAFFS           0x30000u
/** uc/FS file system interface. */
#define DB_FILE_UCFS            0x40000u

#if DB_API_VER >= DB_API_103
/** RAM virtual file interface. */
#define DB_FILE_RAMFS           0x50000u
#endif /* DB_API_103 */

/** @cond INTERNAL */
#define DB_FILE_CRASHFS         0x1000000u
/** @endcond */
/** @} File Interfaces */
#define DB_FILE_INTERFACE_MASK  0xF0000u
#endif /* DB_API_102 */

#endif

#ifndef _DB_OMIT_JOURNAL_TYPE_NAMES
/** Default journal (#DB_EXTERNAL_JOURNAL) */
#define DB_DEFAULT_JOURNAL      0x0000u
/** Journal and data are stored in a single file. */
#define DB_INTERNAL_JOURNAL     0x0001u
/** Journal is stored in a separate file. */
#define DB_EXTERNAL_JOURNAL     0x0002u
#if DB_API_VER >= DB_API_103
/** Journal is not stored, but transactions are still atomic. */
#define DB_NULL_JOURNAL         0x0003u
#endif
#if DB_API_VER >= DB_API_104
/** Use non-atomic transactions. Tables and indexes may become inconsistent
 * when an error occurs while the dummy journal is used. */
#define DB_DUMMY_JOURNAL        0x0004u
#endif
#endif

/** @cond INTERNAL */

/** @name Database Data Type Tags
 *  @{ */
#ifndef _DB_OMIT_COLTYPE_TAG_NAMES
#define DB_COLTYPE_SINT8_TAG         (1)
#define DB_COLTYPE_UINT8_TAG         (2)
#define DB_COLTYPE_SINT16_TAG        (3)
#define DB_COLTYPE_UINT16_TAG        (4)
#define DB_COLTYPE_SINT32_TAG        (5)
#define DB_COLTYPE_UINT32_TAG        (6)
#define DB_COLTYPE_SINT64_TAG        (7)
#define DB_COLTYPE_UINT64_TAG        (8)

#define DB_COLTYPE_FLOAT32_TAG       (9)
#define DB_COLTYPE_FLOAT64_TAG      (10)
#define DB_COLTYPE_CURRENCY_TAG     (12)

#define DB_COLTYPE_DATE_TAG         (13)
#define DB_COLTYPE_TIME_TAG         (14)
#define DB_COLTYPE_DATETIME_TAG     (15)
#define DB_COLTYPE_TIMESTAMP_TAG    (16)

#define DB_COLTYPE_ANSISTR_TAG      (17)
#define DB_COLTYPE_UTF8STR_TAG      (22)
#define DB_COLTYPE_UTF16STR_TAG     (18)
#define DB_COLTYPE_UTF32STR_TAG     (19)

#define DB_COLTYPE_BINARY_TAG       (20)
#define DB_COLTYPE_BLOB_TAG         (21)
#define DB_COLTYPE_TIME_SERIES_TAG  (43)
#if DB_API_VER >= DB_API_111
#define DB_COLTYPE_BOOLEAN_TAG      (23)
#endif

#if DB_API_VER >= DB_API_10C
#define DB_COLTYPE_INTERVAL_DAY_TO_SECOND_TAG            (27)
#define DB_COLTYPE_INTERVAL_YEAR_TO_MONTH_TAG            (28)
#endif

#define DB_COLTYPE_UNDEFINED_TAG    (44)

#endif
/** @} */

/** @name C Language Data Type Tags
 *  @{ */
#ifndef _DB_OMIT_VARTYPE_TAG_NAMES
#define DB_VARTYPE_SINT8_TAG       (1)
#define DB_VARTYPE_UINT8_TAG       (2)
#define DB_VARTYPE_SINT16_TAG      (3)
#define DB_VARTYPE_UINT16_TAG      (4)
#define DB_VARTYPE_SINT32_TAG      (5)
#define DB_VARTYPE_UINT32_TAG      (6)
#define DB_VARTYPE_SINT64_TAG      (7)
#define DB_VARTYPE_UINT64_TAG      (8)

#define DB_VARTYPE_FLOAT32_TAG     (9)
#define DB_VARTYPE_FLOAT64_TAG    (10)

#define DB_VARTYPE_DATE_TAG       (13)
#define DB_VARTYPE_TIME_TAG       (14)
#define DB_VARTYPE_DATETIME_TAG   (15)
#define DB_VARTYPE_TIMESTAMP_TAG  (16)
#define DB_VARTYPE_TIMESTAMP_USEC_TAG (42)

#if DB_API_VER >= DB_API_106
#define DB_VARTYPE_ODBC_DATE_TAG      (24)
#define DB_VARTYPE_ODBC_TIME_TAG      (25)
#define DB_VARTYPE_ODBC_TIMESTAMP_TAG (26)
#endif

#define DB_VARTYPE_ANSISTR_TAG    (17)
#define DB_VARTYPE_UTF8STR_TAG    (22)
#define DB_VARTYPE_UTF16STR_TAG   (18)
#define DB_VARTYPE_UTF32STR_TAG   (19)

#define DB_VARTYPE_BINARY_TAG     (20)
#define DB_VARTYPE_BLOB_TAG       (21)
#define DB_VARTYPE_TIME_SERIES_TAG (43)
#if DB_API_VER >= DB_API_111
#define DB_VARTYPE_BOOLEAN_TAG    (23)
#endif

#if DB_API_VER >= DB_API_10C
#define DB_VARTYPE_INTERVAL_DAY_TO_SECOND_TAG            (27)
#define DB_VARTYPE_INTERVAL_YEAR_TO_MONTH_TAG            (28)
#define DB_VARTYPE_ODBC_INTERVAL_YEAR_TAG                (29)
#define DB_VARTYPE_ODBC_INTERVAL_MONTH_TAG               (30)
#define DB_VARTYPE_ODBC_INTERVAL_DAY_TAG                 (31)
#define DB_VARTYPE_ODBC_INTERVAL_HOUR_TAG                (32)
#define DB_VARTYPE_ODBC_INTERVAL_MINUTE_TAG              (33)
#define DB_VARTYPE_ODBC_INTERVAL_SECOND_TAG              (34)
#define DB_VARTYPE_ODBC_INTERVAL_YEAR_TO_MONTH_TAG       (35)
#define DB_VARTYPE_ODBC_INTERVAL_DAY_TO_HOUR_TAG         (36)
#define DB_VARTYPE_ODBC_INTERVAL_DAY_TO_MINUTE_TAG       (37)
#define DB_VARTYPE_ODBC_INTERVAL_DAY_TO_SECOND_TAG       (38)
#define DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_MINUTE_TAG      (39)
#define DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_SECOND_TAG      (40)
#define DB_VARTYPE_ODBC_INTERVAL_MINUTE_TO_SECOND_TAG    (41)
#endif

#define DB_VARTYPE_UNDEFINED_TAG  (44)

#endif
/** @} */

/** @endcond */

/** Evaluates to true if the given column type is any UTF-encoded type.
 * @ingroup CAPIDataTypes */
#define DB_COLTYPE_IS_UTFSTR(a) (a == DB_COLTYPE_UTF8STR || a == DB_COLTYPE_UTF16STR || a == DB_COLTYPE_UTF32STR)

/** @name Database Data Type Identifiers
 *  @{ */
/** @ingroup CAPIDataTypes */
#ifndef _DB_OMIT_COLTYPE_NAMES
/** Signed 8-bit integer column type. SQL data type: sint8. @see db_coltype_t */
#define DB_COLTYPE_SINT8         DB_COLTYPE_CONST(DB_COLTYPE_SINT8_TAG)
/** Unsigned 8-bit integer column type. SQL data type: uint8. @see db_coltype_t */
#define DB_COLTYPE_UINT8         DB_COLTYPE_CONST(DB_COLTYPE_UINT8_TAG)
/** Signed 16-bit integer column type. SQL data type: sint16. @see db_coltype_t */
#define DB_COLTYPE_SINT16        DB_COLTYPE_CONST(DB_COLTYPE_SINT16_TAG)
/** Unsigned 16-bit integer column type. SQL data type: uint16. @see db_coltype_t */
#define DB_COLTYPE_UINT16        DB_COLTYPE_CONST(DB_COLTYPE_UINT16_TAG)
/** Signed 32-bit integer column type. SQL data type: sint32. @see db_coltype_t */
#define DB_COLTYPE_SINT32        DB_COLTYPE_CONST(DB_COLTYPE_SINT32_TAG)
/** Unsigned 32-bit integer column type. SQL data type: uint32. @see db_coltype_t */
#define DB_COLTYPE_UINT32        DB_COLTYPE_CONST(DB_COLTYPE_UINT32_TAG)
/** Signed 64-bit integer column type. SQL data type: sint64. @see db_coltype_t */
#define DB_COLTYPE_SINT64        DB_COLTYPE_CONST(DB_COLTYPE_SINT64_TAG)
/** Unsigned 64-bit integer column type. SQL data type: uint64. @see db_coltype_t */
#define DB_COLTYPE_UINT64        DB_COLTYPE_CONST(DB_COLTYPE_UINT64_TAG)

/** 32-bit floating point column type. SQL data type: float32. @see db_coltype_t */
#define DB_COLTYPE_FLOAT32       DB_COLTYPE_CONST(DB_COLTYPE_FLOAT32_TAG)
/** 64-bit floating point column type. SQL data type: float64. @see db_coltype_t */
#define DB_COLTYPE_FLOAT64       DB_COLTYPE_CONST(DB_COLTYPE_FLOAT64_TAG)
/** Fixed-point currency column type. SQL data type: currency. @see db_coltype_t */
#define DB_COLTYPE_CURRENCY      DB_COLTYPE_CONST(DB_COLTYPE_CURRENCY_TAG)

/** Date column type. SQL data type: date. @see db_coltype_t */
#define DB_COLTYPE_DATE          DB_COLTYPE_CONST(DB_COLTYPE_DATE_TAG)
/** Time column type with seconds precision. SQL data type: time. @see db_coltype_t */
#define DB_COLTYPE_TIME          DB_COLTYPE_CONST(DB_COLTYPE_TIME_TAG)
/** Date and time column type with seconds precision. SQL data type: datetime. @see db_coltype_t */
#define DB_COLTYPE_DATETIME      DB_COLTYPE_CONST(DB_COLTYPE_DATETIME_TAG)
/** Timestamp column type with microsecond precision. SQL data type: timestamp. @see db_coltype_t */
#define DB_COLTYPE_TIMESTAMP     DB_COLTYPE_CONST(DB_COLTYPE_TIMESTAMP_TAG)

/** ANSI character string column type with system default encoding. SQL data type: ansistr(n). @see db_coltype_t */
#define DB_COLTYPE_ANSISTR       DB_COLTYPE_CONST(DB_COLTYPE_ANSISTR_TAG)
/** Unicode character string column type with UTF-8 encoding. SQL data type: utf8str(n). @see db_coltype_t */
#define DB_COLTYPE_UTF8STR       DB_COLTYPE_CONST(DB_COLTYPE_UTF8STR_TAG)
/** Unicode character string column type with UTF-16 encoding. SQL data type: utf16str(n). @see db_coltype_t */
#define DB_COLTYPE_UTF16STR      DB_COLTYPE_CONST(DB_COLTYPE_UTF16STR_TAG)
/** Unicode character string column type with UTF-32 encoding. SQL data type: utf32str(n). @see db_coltype_t */
#define DB_COLTYPE_UTF32STR      DB_COLTYPE_CONST(DB_COLTYPE_UTF32STR_TAG)

/** Binary data column. @see db_coltype_t */
#define DB_COLTYPE_BINARY        DB_COLTYPE_CONST(DB_COLTYPE_BINARY_TAG)
/** Binary large object column type. SQL data type: blob. @see db_coltype_t */
#define DB_COLTYPE_BLOB          DB_COLTYPE_CONST(DB_COLTYPE_BLOB_TAG)
/** Time series large object column type. SQL data type: tlob. @see db_coltype_t */
#define DB_COLTYPE_TIME_SERIES   DB_COLTYPE_CONST(DB_COLTYPE_TIME_SERIES_TAG)

#if DB_API_VER >= DB_API_111
/** Boolean column type. @see db_coltype_t */
#define DB_COLTYPE_BOOLEAN       DB_CLOTYPE_CONST(DB_COLTYPE_BOOLEAN_TAG)
#endif

#if DB_API_VER >= DB_API_10C
/** Interval day to second column type. @see db_coltype_t */
#define DB_COLTYPE_INTERVAL_DAY_TO_SECOND            DB_COLTYPE_CONST(DB_COLTYPE_INTERVAL_DAY_TO_SECOND_TAG)
/** Interval year to month column type. @see db_coltype_t */
#define DB_COLTYPE_INTERVAL_YEAR_TO_MONTH            DB_COLTYPE_CONST(DB_COLTYPE_INTERVAL_YEAR_TO_MONTH_TAG)
#endif

/** Unknown column type. @see db_coltype_t */
#define DB_COLTYPE_UNDEFINED     DB_COLTYPE_CONST(DB_COLTYPE_UNDEFINED_TAG)

/** Evaluates to the column type that matches wchar_t on this platform.
 *
 * @note Use of this macro on a platform that does not support wchar_t will
 * result in a compile error.
 *
 * @see db_coltype_t, DB_COLTYPE_UTF16STR, DB_COLTYPE_UTF32STR
 */
#define DB_COLTYPE_WCHARSTR (sizeof(wchar_t) == sizeof(db_utf16_t) ? DB_COLTYPE_UTF16STR : DB_COLTYPE_UTF32STR)
#endif
/** @} */

/** @name C Language Data Type Identifiers
 *  @{ */
/** @ingroup CAPIDataTypes */
#ifndef _DB_OMIT_VARTYPE_NAMES
/** Signed 8-bit integer variable type. C data type: int8_t. @see db_vartype_t */
#define DB_VARTYPE_SINT8          DB_VARTYPE_CONST(DB_VARTYPE_SINT8_TAG)
/** Unsigned 8-bit integer variable type. C data type: uint8_t. @see db_vartype_t */
#define DB_VARTYPE_UINT8          DB_VARTYPE_CONST(DB_VARTYPE_UINT8_TAG)
/** Signed 16-bit integer variable type. C data type: int16_t. @see db_vartype_t */
#define DB_VARTYPE_SINT16         DB_VARTYPE_CONST(DB_VARTYPE_SINT16_TAG)
/** Unsigned 16-bit integer variable type. C data type: uint16_t. @see db_vartype_t */
#define DB_VARTYPE_UINT16         DB_VARTYPE_CONST(DB_VARTYPE_UINT16_TAG)
/** Signed 32-bit integer variable type. C data type: int32_t. @see db_vartype_t */
#define DB_VARTYPE_SINT32         DB_VARTYPE_CONST(DB_VARTYPE_SINT32_TAG)
/** Unsigned 32-bit integer variable type. C data type: uint32_t. @see db_vartype_t */
#define DB_VARTYPE_UINT32         DB_VARTYPE_CONST(DB_VARTYPE_UINT32_TAG)
/** Signed 64-bit integer variable type. C data type: int64_t. @see db_vartype_t */
#define DB_VARTYPE_SINT64         DB_VARTYPE_CONST(DB_VARTYPE_SINT64_TAG)
/** Unsigned 64-bit integer variable type. C data type: uint64_t. @see db_vartype_t */
#define DB_VARTYPE_UINT64         DB_VARTYPE_CONST(DB_VARTYPE_UINT64_TAG)

/** 32-bit floating point variable type. C data type: #db_float32_t. @see db_vartype_t */
#define DB_VARTYPE_FLOAT32        DB_VARTYPE_CONST(DB_VARTYPE_FLOAT32_TAG)
/** 64-bit floating point variable type. C data type: #db_float64_t. @see db_vartype_t */
#define DB_VARTYPE_FLOAT64        DB_VARTYPE_CONST(DB_VARTYPE_FLOAT64_TAG)

/** Date variable type. C data type: db_date_t. @see db_vartype_t */
#define DB_VARTYPE_DATE           DB_VARTYPE_CONST(DB_VARTYPE_DATE_TAG)
/** Time variable type with seconds precision. C data type: #db_time_t. @see db_vartype_t */
#define DB_VARTYPE_TIME           DB_VARTYPE_CONST(DB_VARTYPE_TIME_TAG)
/** Date and time variable type with seconds precision. C data type: #db_datetime_t. @see db_vartype_t */
#define DB_VARTYPE_DATETIME       DB_VARTYPE_CONST(DB_VARTYPE_DATETIME_TAG)
/** Timestamp variable type with microsecond precision. C data type: #db_timestamp_t. @see db_vartype_t */
#define DB_VARTYPE_TIMESTAMP      DB_VARTYPE_CONST(DB_VARTYPE_TIMESTAMP_TAG)
/** Timestamp variable type with microsecond precision. C data type: #db_timestamp_usec_t. @see db_vartype_t */
#define DB_VARTYPE_TIMESTAMP_USEC DB_VARTYPE_CONST(DB_VARTYPE_TIMESTAMP_USEC_TAG)

#if DB_API_VER >= DB_API_106
/** Date variable type (ODBC-compatible). C data type: db_odbc_date_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_DATE          DB_VARTYPE_CONST(DB_VARTYPE_ODBC_DATE_TAG)
/** Time variable type (ODBC-compatible). C data type: #db_odbc_time_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_TIME          DB_VARTYPE_CONST(DB_VARTYPE_ODBC_TIME_TAG)
/** Timestamp variable type (ODBC-compatible). C data type: #db_odbc_timestamp_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_TIMESTAMP     DB_VARTYPE_CONST(DB_VARTYPE_ODBC_TIMESTAMP_TAG)
#endif

/** ANSI character string variable type with system default encoding. C data type: #db_ansi_t*. @see db_vartype_t */
#define DB_VARTYPE_ANSISTR        DB_VARTYPE_CONST(DB_VARTYPE_ANSISTR_TAG)
/** Unicode character string variable type with UTF-8 encoding. C data type: #db_utf8_t*. @see db_vartype_t */
#define DB_VARTYPE_UTF8STR        DB_VARTYPE_CONST(DB_VARTYPE_UTF8STR_TAG)
/** Unicode character string variable type with UTF-16 encoding. C data type: #db_utf16_t*. @see db_vartype_t */
#define DB_VARTYPE_UTF16STR        DB_VARTYPE_CONST(DB_VARTYPE_UTF16STR_TAG)
/** Unicode character string variable type with UTF-32 encoding. C data type: #db_utf32_t*. @see db_vartype_t */
#define DB_VARTYPE_UTF32STR        DB_VARTYPE_CONST(DB_VARTYPE_UTF32STR_TAG)

/** Binary data column. @see db_vartype_t */
#define DB_VARTYPE_BINARY         DB_VARTYPE_CONST(DB_VARTYPE_BINARY_TAG)
/** Binary large object variable type. C data type: #db_blob_t. @see db_vartype_t */
#define DB_VARTYPE_BLOB           DB_VARTYPE_CONST(DB_VARTYPE_BLOB_TAG)
/** Time series large object variable type. C data type: #db_time_series_t. @see db_vartype_t */
#define DB_VARTYPE_TIME_SERIES    DB_VARTYPE_CONST(DB_VARTYPE_TIME_SERIES_TAG)

#if DB_API_VER >= DB_API_111
/** Boolean data column. */
#define DB_VARTYPE_BOOLEAN        DB_VARTYPE_CONST(DB_VARTYPE_BOOLEAN_TAG)
#endif

#if DB_API_VER >= DB_API_10C
/** Number of microseconds in a day to second time interval. C data type: #db_interval_t. @see db_vartype_t */
#define DB_VARTYPE_INTERVAL_DAY_TO_SECOND            DB_VARTYPE_CONST(DB_VARTYPE_INTERVAL_DAY_TO_SECOND_TAG)
/** Number of months in a year to month time interval. C data type: #db_interval_t. @see db_vartype_t */
#define DB_VARTYPE_INTERVAL_YEAR_TO_MONTH            DB_VARTYPE_CONST(DB_VARTYPE_INTERVAL_YEAR_TO_MONTH_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL                     DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_YEAR                DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_YEAR_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_MONTH               DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_MONTH_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_DAY                 DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_DAY_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_HOUR                DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_HOUR_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_MINUTE              DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_MINUTE_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_SECOND              DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_SECOND_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_YEAR_TO_MONTH       DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_YEAR_TO_MONTH_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_DAY_TO_HOUR         DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_DAY_TO_HOUR_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_DAY_TO_MINUTE       DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_DAY_TO_MINUTE_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_DAY_TO_SECOND       DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_DAY_TO_SECOND_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_MINUTE      DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_MINUTE_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_SECOND      DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_SECOND_TAG)
/** Interval variable type (ODBC-compatible). C data type: db_odbc_interval_t. @see db_vartype_t */
#define DB_VARTYPE_ODBC_INTERVAL_MINUTE_TO_SECOND    DB_VARTYPE_CONST(DB_VARTYPE_ODBC_INTERVAL_MINUTE_TO_SECOND_TAG)
#endif

/** Unknown variable type. @see db_vartype_t */
#define DB_VARTYPE_UNDEFINED      DB_VARTYPE_CONST(DB_VARTYPE_UNDEFINED_TAG)

/** Evaluates to the variable type that matches wchar_t on this platform.
 *
 * @note Use of this macro on a platform that does not support wchar_t will
 * result in a compile error.
 *
 * @see db_vartype_t, DB_VARTYPE_UTF16STR, DB_VARTYPE_UTF32STR
 */
#define DB_VARTYPE_WCHARSTR (sizeof(wchar_t) == sizeof(db_utf16_t) ? DB_VARTYPE_UTF16STR : DB_VARTYPE_UTF32STR)

#endif
/** @} */

#ifndef _DB_OMIT_SHUTDOWN_NAMES
/** Perform a soft shutdown, waiting for all transactions to complete. */
#define DB_SOFT_SHUTDOWN        0
#endif

#ifndef _DB_OMIT_DESCRIBE_TABLE_NAMES
/** Obtain information about fields. */
#define DB_DESCRIBE_TABLE_FIELDS       0x00001u
/** Obtain information about indexes. */
#define DB_DESCRIBE_TABLE_INDEXES      0x00002u
/** Obtain information about foreign keys. */
#define DB_DESCRIBE_TABLE_FOREIGN_KEYS 0x00004u
#define DB_DESCRIBE_TABLE_MASK         0x00007u
#endif

#if DB_API_VER >= DB_API_101 && !defined(_DB_OMIT_WATCH_NAMES)
/** Receive notification when new rows are added to the table. */
#define DB_WATCH_ROW_INSERT          0x00001u
/** Receive notification when an existing row is updated. */
#define DB_WATCH_ROW_UPDATE          0x00002u
/** Receive notification when an existing row is deleted. */
#define DB_WATCH_ROW_DELETE          0x00004u

/** Include a copy of the primary key in the watch row. */
#define DB_WATCH_PRIMARY_KEY         0x00100u
/** Include a copy of all modified fields in the watch row. */
#define DB_WATCH_MODIFIED_FIELDS     0x00200u
/** Include a copy of all bound fields in the watch row. */
#define DB_WATCH_BOUND_FIELDS        0x00400u
/** Include a copy of all fields in the watch row. */
#define DB_WATCH_ALL_FIELDS          0x00800u
#define DB_WATCH_SCOPE_MASK          0x0ff00u

/** Include the original values for any updated fields in the watch aux row. */
#define DB_WATCH_FORMER_VALUES       0x00008u

/** Only watch for events that modify the row (does not restrict insert or delete.) */
#define DB_WATCH_FILTER_MODIFIED     0x10000u
/** Only watch for events that are not caused by the same connection. */
#define DB_WATCH_FILTER_NOT_SELF     0x20000u
#define DB_WATCH_FILTER_MASK         0xf0000u

#endif

#if DB_API_VER >= DB_API_101 && !defined(_DB_OMIT_INFO_NAMES)
/* error return */
/** Error return code from call to db_info. */
#define DB_INFO_ERROR              (~(uintptr_t)0)

/** API Version Number information. Returns an integer value. */

#define DB_INFO_APIVER             1
/** Minimum API Version Number information. Returns an integer value. */
#define DB_INFO_MINAPI             2

/** Major Version Number information. Returns an integer value. */
#define DB_INFO_MAJOR              3
/** Minor Version Number information. Returns an integer value. */
#define DB_INFO_MINOR              4
/** Patch Number information. Returns an integer value. */
#define DB_INFO_PATCH              5
/** Build Number information. Returns an integer value. */
#define DB_INFO_BUILD              6

/** Product name information. Returns pointer to a char string. */
#define DB_INFO_FULL_ANSI_NAME     20
/** Product name information. Returns pointer to a db_utf8_t string. */
#define DB_INFO_FULL_UTF8_NAME     21
/** Product name information. Returns pointer to a db_utf16_t string. */
#define DB_INFO_FULL_UTF16_NAME    22
/** Product name information. Returns pointer to a db_utf32_t string. */
#define DB_INFO_FULL_UTF32_NAME    32

/** Short product name information. Returns pointer to a char string. */
#define DB_INFO_SHORT_ANSI_NAME    24
/** Short product name information. Returns pointer to a db_utf8_t string. */
#define DB_INFO_SHORT_UTF8_NAME    25
/** Short product name information. Returns pointer to a db_utf16_t string. */
#define DB_INFO_SHORT_UTF16_NAME   26
/** Short product name information. Returns pointer to a db_utf32_t string. */
#define DB_INFO_SHORT_UTF32_NAME   27

/** Debug support information. Returns an integer value. */
#define DB_INFO_DEBUG              40
/** Thread support information. Returns an integer value. */
#define DB_INFO_THREAD             41
/** Shared library support information. Returns an integer value. */
#define DB_INFO_SHAREDLIB          42

/** Disposition: Stand-Alone or Client/Server information. Returns an integer value. */
#define DB_INFO_DISPOSITION        44
/** Stand-Alone disposition. Returns disposition value. */
#define DB_DISPOSITION_STANDALONE  0u
/** Client/Server disposition. Returns disposition value. */
#define DB_DISPOSITION_IPCSOCKETS  2u

#if DB_API_VER >= DB_API_103
/** Compiled in options. Returns integer value, a bit field combination of:
 * - #DB_SUPPORT_LOGGING
 * - #DB_SUPPORT_CRYPT
 * - #DB_SUPPORT_WATCHER
 * - #DB_SUPPORT_SEQUENCE
 * - #DB_SUPPORT_BLOB
 * - #DB_SUPPORT_SQL
 * - #DB_SUPPORT_TYPECVT
 * - #DB_SUPPORT_UNICODE
 * - #DB_SUPPORT_DDL
 * - #DB_SUPPORT_ATOMIC_TX
 * - #DB_SUPPORT_REPLICATION
 */
#define DB_INFO_SUPPORT             46
/** Indicates support for recovery logging. */
#define DB_SUPPORT_LOGGING          0x000001u
/** Indicates support for storage-level encryption. */
#define DB_SUPPORT_CRYPT            0x000002u
/** Indicates support for #db_watch_table. */
#define DB_SUPPORT_WATCHER          0x000004u
/** Indicates support for sequence generators. */
#define DB_SUPPORT_SEQUENCE         0x000008u
/** Indicates support for the BLOB field type. */
#define DB_SUPPORT_BLOB             0x000010u
/** Indicates support for SQL queries. */
#define DB_SUPPORT_SQL              0x000020u
/** Indicates support for field type conversion. */
#define DB_SUPPORT_TYPECVT          0x000040u
/** Indicates support for Unicode character string field types. */
#define DB_SUPPORT_UNICODE          0x000080u
/** Indicates support for dynamic schema alteration. */
#define DB_SUPPORT_DDL              0x000100u
/** Indicates support for atomic transactions. */
#define DB_SUPPORT_ATOMIC_TX        0x000200u
/** Indicates support for filtered table cursors. */
#define DB_SUPPORT_FILTERS          0x000400u
/** Indicates support for sorting table cursors without an index. */
#define DB_SUPPORT_SORT             0x000800u
/** Indicates support for atomic operations. */
#define DB_SUPPORT_ATOMIC_OP        0x001000u
/** Indicates support for replication. */
#define DB_SUPPORT_REPLICATION      0x002000u
#endif

#if DB_API_VER >= DB_API_107
/** Locking granularity. Returns one of: #DB_LOCK_LEVEL_NONE, #DB_LOCK_LEVEL_ROW, #DB_LOCK_LEVEL_STORAGE */
#define DB_INFO_LOCK_LEVEL          47
/** Transactions do not hold any locks. */
#define DB_LOCK_LEVEL_NONE          0u
/** Transactions may hold locks on individual rows. */
#define DB_LOCK_LEVEL_ROW           1u
/** Transactions may lock the entire database storage as a whole. */
#define DB_LOCK_LEVEL_STORAGE       2u
#endif

#endif /* _DB_OMIT_INFO_NAMES */

#if DB_API_VER >= DB_API_105 && !defined(_DB_OMIT_PRIO_NAMES)
/** Lowest priority */
#define DB_PRIO_MIN    0
/** Highest priority */
#define DB_PRIO_MAX    31
/** Normal (default) priority */
#define DB_PRIO_NORMAL ((DB_PRIO_MAX + DB_PRIO_MIN ) / 2)
#endif /* _DB_OMIT_PRIO_NAMES */

#if DB_API_VER >= DB_API_107 && !defined(_DB_OMIT_SERVER_NAMES)

/** Enable shared memory client/server protocol. */
#define DB_SERVER_SHM_ENABLE   1

#endif

/** @cond INTERNAL */
#define DB_CIPHER_AES_         0x01000000u
#define DB_CIPHER_HARDWARE_AES_ 0xf1000000u
#define DB_CIPHER_CTR_         0x00010000u
#define DB_CIPHER_TYPE_MASK_   0xff000000u
#define DB_CIPHER_MODE_MASK_   0x00ff0000u
#define DB_CIPHER_PARAM_MASK_  0x0000ffffu
/** @endcond */

#if DB_API_VER >= DB_API_10C && !defined(_DB_OMIT_CIPHER_NAMES)
/** No cipher for encryption and decription. */
#define DB_CIPHER_NONE         0
/** User-defined cipher. @see db_crypt_t */
#define DB_CIPHER_USER         0xff000000u
/** AES-128 in CTR mode. */
#define DB_CIPHER_AES128_CTR   (DB_CIPHER_AES_ | DB_CIPHER_CTR_ | 128u)
/** AES-256 in CTR mode. */
#define DB_CIPHER_AES256_CTR   (DB_CIPHER_AES_ | DB_CIPHER_CTR_ | 256u)
/** AES with hardware-specific configuration and key management in CTR mode. */
#define DB_CIPHER_HARDWARE_AES_CTR (DB_CIPHER_HARDWARE_AES_ | DB_CIPHER_CTR_)
#endif

/** @name Data Binding
 *  @{ */
/** @ingroup CAPIRow */

/** Get the dimension of a static array. The dimension is computed at
 * compile-time, so this value can be used as a constant. */
#define DB_ARRAY_DIM(x) (sizeof(x) / sizeof(x[0]))

/** Bind to the offset of a member variable within a struct. Use this macro to initialize a db_bind_t structure for relative binding. */
#define DB_BIND_STRUCT_MEMBER(field_no, type, bind_struct, member) { field_no, type, DB_BIND_OFFSET(bind_struct, member), DB_BIND_SIZE(bind_struct, member), -1, DB_BIND_RELATIVE }

/** Bind to the address of a non-pointer data type. Use this macro to initialize a db_bind_t structure for absolute binding. */
#define DB_BIND_VAR(field_no, type, var)       { field_no, type, DB_BIND_ADDRESS(&var), sizeof(var), DB_BIND_ADDRESS(NULL), DB_BIND_ABSOLUTE }

/** Bind to the address of a statically allocated array or string. Size is determined by the compiler. Use this macro to initialize a db_bind_t structure for absolute binding. */
#define DB_BIND_STR(field_no, type, var)       { field_no, type, DB_BIND_ADDRESS(var),  sizeof(var), DB_BIND_ADDRESS(NULL), DB_BIND_ABSOLUTE }

/** Bind to a dynamically allocated pointer with a specified size in bytes. Use this macro to initialize a db_bind_t structure for absolute binding. */
#define DB_BIND_PTR(field_no, type, var, size) { field_no, type, DB_BIND_ADDRESS(var),  size,        DB_BIND_ADDRESS(NULL), DB_BIND_ABSOLUTE }

/** Bind to the offset of a member variable and its length indicator within a struct. Use this macro to initialize a db_bind_t structure for relative binding. */
#define DB_BIND_STRUCT_MEMBER_IND(field_no, type, bind_struct, value, ind) { field_no, type, DB_BIND_OFFSET(bind_struct, value), DB_BIND_SIZE(bind_struct, value), DB_BIND_OFFSET(bind_struct, ind), DB_BIND_RELATIVE }

/** Bind to the address of a non-pointer data type and its length indicator. Use this macro to initialize a db_bind_t structure for absolute binding. */
#define DB_BIND_VAR_IND(field_no, type, var, ind)       { field_no, type, DB_BIND_ADDRESS(&var), sizeof(var), DB_BIND_ADDRESS(ind), DB_BIND_ABSOLUTE }

/** Bind to the address of a statically allocated array or string and its length indicator. Size is determined by the compiler. Use this macro to initialize a db_bind_t structure for absolute binding. */
#define DB_BIND_STR_IND(field_no, type, var, ind)       { field_no, type, DB_BIND_ADDRESS(var),  sizeof(var), DB_BIND_ADDRESS(ind), DB_BIND_ABSOLUTE }

/** Bind to a dynamically allocated pointer with a specified size in bytes and its length indicator. Use this macro to initialize a db_bind_t structure for absolute binding. */
#define DB_BIND_PTR_IND(field_no, type, var, size, ind) { field_no, type, DB_BIND_ADDRESS(var),  size,        DB_BIND_ADDRESS(ind), DB_BIND_ABSOLUTE }

/** @} Data Binding */

#endif /* ITTIA_DB_H */
