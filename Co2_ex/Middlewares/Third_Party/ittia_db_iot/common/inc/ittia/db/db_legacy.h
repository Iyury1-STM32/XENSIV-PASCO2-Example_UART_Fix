/**************************************************************************/
/*                                                                        */
/*      Copyright (c) 2005-2016 by ITTIA L.L.C. All rights reserved.      */
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

#ifndef ITTIA_DB_LEGACY_H
#define ITTIA_DB_LEGACY_H

#include <ittia/os/os_config.h>

C_HEADER_BEGIN

/* various flags */
/* constants, intentionally made different */
#define _DB_LOCK_DEFAULT          0x00000000
#define _DB_LOCK_SHARED           0x00000001
#define _DB_LOCK_EXCLUSIVE        0x00000002
#define _DB_LOCK_MODE_MASK        0x00000003

/* cursor direction flags*/
#define _DB_SCAN_FORWARD          0x00000004
#define _DB_SCAN_BACKWARD         0x00000008
#define _DB_SCAN_MASK             0x0000000C

/* isolation */
#define _DB_DEFAULT_ISOLATION     0x00000000
#define _DB_READ_COMMITTED        0x00000010
#define _DB_REPEATABLE_READ       0x00000020
#define _DB_SERIALIZABLE          0x00000030
#define _DB_ISOLATION_MASK        0x000000F0

/* information */
#define _DB_CAN_MODIFY            0x00000100
#define _DB_CAN_BOOKMARK          0x00000200
#define _DB_CURSOR_MASK           0x00000300

#define _DB_CURSOR_TYPE_MASK      0x00007000
#define _DB_CURSOR_TYPE_FORWARD   0x00001000
#define _DB_CURSOR_TYPE_STATIC    0x00002000
#define _DB_CURSOR_TYPE_DYNAMIC   0x00003000
#define _DB_CURSOR_TYPE_EXCL      0x00008000

#define _DB_CURSOR_ENCODING_ANSI  0x00000000
#define _DB_CURSOR_ENCODING_UTF8  0x00010000
#define _DB_CURSOR_ENCODING_UTF16 0x00020000
#define _DB_CURSOR_ENCODING_UTF32 0x00030000
#define _DB_CURSOR_ENCODING_MASK  0x00030000

/* resolve */
#if 0
#define _DB_ON_INSERT_SEEK        0x00001000
#define _DB_ON_DELETE_PRIOR       0x00002000
#define _DB_ON_DELETE_NEXT        0x00004000
#define _DB_RESOLVE_MASK          0x00007000
#endif

/* other constants */
/* tx completion */
#define _DB_DEFAULT_COMPLETION    0x00000000
#define _DB_LAZY_COMPLETION       0x01000000
#define _DB_FORCED_COMPLETION     0x02000000
#define _DB_GROUP_COMPLETION      0x03000000
#define _DB_COMPLETION_MASK       0x07000000

/* db_lock extra flags */
#define _DB_TRY_LOCK              0x00010000

#define _DB_INSTANT_LOCK          0x00020000
#define _DB_MANUAL_LOCK           0x00040000
#define _DB_COMMIT_LOCK           0x00060000
#define _DB_LOCK_DURATION_MASK    0x00060000

#define _DB_LOCKING_MASK          0x00070000

/* flush */
#define _DB_FLUSH_JOURNAL         0x00000000
#define _DB_FLUSH_STORAGE         0x10000000
#define _DB_FLUSH_MASK            0x10000000

/* index */
#define _DB_MULTISET_INDEX        0x00000000
#define _DB_UNIQUE_INDEX          0x20000000
#define _DB_PRIMARY_INDEX         0x30000000
#define _DB_INDEX_MODE_MASK       0x30000000
#define _DB_NUMBERED_INDEX        0x40000000
#define _DB_CLUSTERING_INDEX      0x08000000
#define _DB_INDEX_MASK            (_DB_INDEX_MODE_MASK | _DB_NUMBERED_INDEX | _DB_CLUSTERING_INDEX)

/* db_config memory mode */
#define _DB_MEM_TIGHT             1
#define _DB_MEM_COMPACT           2
#define _DB_MEM_LARGE             3

/* field flags */
#define _DB_NULLABLE              0
#define _DB_NOT_NULL              1
#define _DB_NULL_MASK             (_DB_NOT_NULL | _DB_NULLABLE)
#define _DB_IDENTITY              2
#define _DB_GENERATED_MASK        (_DB_IDENTITY)

/* insert flags */
#define _DB_INSERT_SEEK_NEW       1
#define _DB_INSERT_SEEK_MASK      0x07

/* update flags */
#define _DB_UPDATE_SEEK_NEW       1
#define _DB_UPDATE_SEEK_NEXT      2
#define _DB_UPDATE_SEEK_PRIOR     3
#define _DB_UPDATE_SEEK_MASK      0x07

/* delete  flags */
#define _DB_DELETE_SEEK_NEXT      1
#define _DB_DELETE_SEEK_PRIOR     2
#define _DB_DELETE_SEEK_MASK      0x07

/* db_config concurrency */
#define _DB_SINGLE_PROCESS        1

/* field length. Each time the field is fetched user can attach
 * a length indicator, which is set to the size of loaded
 * value or can be set into one of special values, described below
 */
#define _DB_FIELD_NULL            ((db_len_t)-1)

/* this is used to indicate null terminated string, when set in length indicator */
#define _DB_NTS                   ((db_len_t)-3)

/* used in blob.blob_size: in order to update blob size to offset + chunk_size
 * during write operation write
 */
#define _DB_BLOB_CHSIZE           ((db_len_t)-4)

/* can be used instead of buffer size in rows to manage memory automatically */
#define _DB_AUTOFIELD             ((db_len_t)-5)

#define _DB_DUPLICATE_SAME_FLAGS  (-1)

/* bind flags */
#define _DB_BIND_ABSOLUTE         0x00000
#define _DB_BIND_RELATIVE         0x00001

/* This flag is used in ODBC */
#define _DB_BIND_LATE_BINDING     0x80000

#define _DB_BIND_MASK (_DB_BIND_ABSOLUTE | _DB_BIND_RELATIVE | _DB_BIND_LATE_BINDING)

#ifndef _DB_OMIT_SEEK_NAMES
#define _DB_SEEK_LESS             DB_SEEK_LESS
#define _DB_SEEK_LESS_OR_EQUAL    DB_SEEK_LESS_OR_EQUAL
#define _DB_SEEK_FIRST_EQUAL      DB_SEEK_FIRST_EQUAL
#define _DB_SEEK_LAST_EQUAL       DB_SEEK_LAST_EQUAL
#define _DB_SEEK_GREATER          DB_SEEK_GREATER
#define _DB_SEEK_GREATER_OR_EQUAL DB_SEEK_GREATER_OR_EQUAL
#define _DB_SEEK_EQUAL            DB_SEEK_EQUAL
#else
typedef enum
{
    _DB_SEEK_LESS,
    _DB_SEEK_LESS_OR_EQUAL,
    _DB_SEEK_FIRST_EQUAL,
    _DB_SEEK_LAST_EQUAL,
    _DB_SEEK_GREATER,
    _DB_SEEK_GREATER_OR_EQUAL,

    _DB_SEEK_EQUAL = _DB_SEEK_FIRST_EQUAL
} db_seek_t;
#endif

#define _DB_UNITYPE_SINT8_TAG       (1)
#define _DB_UNITYPE_UINT8_TAG       (2)
#define _DB_UNITYPE_SINT16_TAG      (3)
#define _DB_UNITYPE_UINT16_TAG      (4)
#define _DB_UNITYPE_SINT32_TAG      (5)
#define _DB_UNITYPE_UINT32_TAG      (6)
#define _DB_UNITYPE_SINT64_TAG      (7)
#define _DB_UNITYPE_UINT64_TAG      (8)

#define _DB_UNITYPE_FLOAT32_TAG     (9)
#define _DB_UNITYPE_FLOAT64_TAG    (10)
/* #define _DB_UNITYPE_FIXED_TAG     (11) */
#define _DB_UNITYPE_CURRENCY_TAG   (12)

#define _DB_UNITYPE_DATE_TAG       (13)
#define _DB_UNITYPE_TIME_TAG       (14)
#define _DB_UNITYPE_DATETIME_TAG   (15)
#define _DB_UNITYPE_TIMESTAMP_TAG  (16)

#define _DB_UNITYPE_ANSISTR_TAG    (17)
#define _DB_UNITYPE_UTF16STR_TAG   (18)
#define _DB_UNITYPE_UTF32STR_TAG   (19)

#define _DB_UNITYPE_BINARY_TAG     (20)
#define _DB_UNITYPE_BLOB_TAG       (21)
#define _DB_UNITYPE_UTF8STR_TAG    (22)

#define _DB_UNITYPE_UNDEFINED_TAG  (42)

#define _DB_UNITYPE_ODBC_DATE_TAG       (24)
#define _DB_UNITYPE_ODBC_TIME_TAG       (25)
#define _DB_UNITYPE_ODBC_TIMESTAMP_TAG  (26)

/* skip ODBC types */
#define _DB_UNITYPE_INTERVAL_DAY_TO_SECOND_TAG          (27)
#define _DB_UNITYPE_INTERVAL_YEAR_TO_MONTH_TAG          (28)
#define _DB_UNITYPE_ODBC_INTERVAL_YEAR_TAG              (29)
#define _DB_UNITYPE_ODBC_INTERVAL_MONTH_TAG             (30)
#define _DB_UNITYPE_ODBC_INTERVAL_DAY_TAG               (31)
#define _DB_UNITYPE_ODBC_INTERVAL_HOUR_TAG              (32)
#define _DB_UNITYPE_ODBC_INTERVAL_MINUTE_TAG            (33)
#define _DB_UNITYPE_ODBC_INTERVAL_SECOND_TAG            (34)
#define _DB_UNITYPE_ODBC_INTERVAL_YEAR_TO_MONTH_TAG     (35)
#define _DB_UNITYPE_ODBC_INTERVAL_DAY_TO_HOUR_TAG       (36)
#define _DB_UNITYPE_ODBC_INTERVAL_DAY_TO_MINUTE_TAG     (37)
#define _DB_UNITYPE_ODBC_INTERVAL_DAY_TO_SECOND_TAG     (38)
#define _DB_UNITYPE_ODBC_INTERVAL_HOUR_TO_MINUTE_TAG    (39)
#define _DB_UNITYPE_ODBC_INTERVAL_HOUR_TO_SECOND_TAG    (40)
#define _DB_UNITYPE_ODBC_INTERVAL_MINUTE_TO_SECOND_TAG  (41)

#define _DB_UNITYPE_MAX_TAG                         (42)

/** Column types */
#define _DB_COLTYPE_SINT8_TAG                       _DB_UNITYPE_SINT8_TAG
#define _DB_COLTYPE_UINT8_TAG                       _DB_UNITYPE_UINT8_TAG
#define _DB_COLTYPE_SINT16_TAG                      _DB_UNITYPE_SINT16_TAG
#define _DB_COLTYPE_UINT16_TAG                      _DB_UNITYPE_UINT16_TAG
#define _DB_COLTYPE_SINT32_TAG                      _DB_UNITYPE_SINT32_TAG
#define _DB_COLTYPE_UINT32_TAG                      _DB_UNITYPE_UINT32_TAG
#define _DB_COLTYPE_SINT64_TAG                      _DB_UNITYPE_SINT64_TAG
#define _DB_COLTYPE_UINT64_TAG                      _DB_UNITYPE_UINT64_TAG

#define _DB_COLTYPE_FLOAT32_TAG                     _DB_UNITYPE_FLOAT32_TAG
#define _DB_COLTYPE_FLOAT64_TAG                     _DB_UNITYPE_FLOAT64_TAG
/* #define _DB_COLTYPE_FIXED_TAG                    _DB_UNITYPE_FIXED_TAG */
#define _DB_COLTYPE_CURRENCY_TAG                    _DB_UNITYPE_CURRENCY_TAG

#define _DB_COLTYPE_DATE_TAG                        _DB_UNITYPE_DATE_TAG
#define _DB_COLTYPE_TIME_TAG                        _DB_UNITYPE_TIME_TAG
#define _DB_COLTYPE_DATETIME_TAG                    _DB_UNITYPE_DATETIME_TAG
#define _DB_COLTYPE_TIMESTAMP_TAG                   _DB_UNITYPE_TIMESTAMP_TAG

#define _DB_COLTYPE_ANSISTR_TAG                     _DB_UNITYPE_ANSISTR_TAG
#define _DB_COLTYPE_UTF16STR_TAG                    _DB_UNITYPE_UTF16STR_TAG
#define _DB_COLTYPE_UTF32STR_TAG                    _DB_UNITYPE_UTF32STR_TAG

#define _DB_COLTYPE_BINARY_TAG                      _DB_UNITYPE_BINARY_TAG
#define _DB_COLTYPE_BLOB_TAG                        _DB_UNITYPE_BLOB_TAG
#define _DB_COLTYPE_UTF8STR_TAG                     _DB_UNITYPE_UTF8STR_TAG

#define _DB_COLTYPE_UNDEFINED_TAG                   _DB_UNITYPE_UNDEFINED_TAG

/* skip ODBC types */
#define _DB_COLTYPE_INTERVAL_DAY_TO_SECOND_TAG           _DB_UNITYPE_INTERVAL_DAY_TO_SECOND_TAG
#define _DB_COLTYPE_INTERVAL_YEAR_TO_MONTH_TAG           _DB_UNITYPE_INTERVAL_YEAR_TO_MONTH_TAG

#define _DB_COLTYPE_MAX_TAG                         _DB_UNITYPE_MAX_TAG

/* Variable types */
#define _DB_VARTYPE_SINT8_TAG                       _DB_UNITYPE_SINT8_TAG
#define _DB_VARTYPE_UINT8_TAG                       _DB_UNITYPE_UINT8_TAG
#define _DB_VARTYPE_SINT16_TAG                      _DB_UNITYPE_SINT16_TAG
#define _DB_VARTYPE_UINT16_TAG                      _DB_UNITYPE_UINT16_TAG
#define _DB_VARTYPE_SINT32_TAG                      _DB_UNITYPE_SINT32_TAG
#define _DB_VARTYPE_UINT32_TAG                      _DB_UNITYPE_UINT32_TAG
#define _DB_VARTYPE_SINT64_TAG                      _DB_UNITYPE_SINT64_TAG
#define _DB_VARTYPE_UINT64_TAG                      _DB_UNITYPE_UINT64_TAG

#define _DB_VARTYPE_FLOAT32_TAG                     _DB_UNITYPE_FLOAT32_TAG
#define _DB_VARTYPE_FLOAT64_TAG                     _DB_UNITYPE_FLOAT64_TAG
/* #define _DB_VARTYPE_FIXED_TAG                    _DB_UNITYPE_FIXED_TAG */
/* #define _DB_VARTYPE_CURRENCY_TAG                 _DB_UNITYPE_CURRENCY_TAG */

#define _DB_VARTYPE_DATE_TAG                        _DB_UNITYPE_DATE_TAG
#define _DB_VARTYPE_TIME_TAG                        _DB_UNITYPE_TIME_TAG
#define _DB_VARTYPE_DATETIME_TAG                    _DB_UNITYPE_DATETIME_TAG
#define _DB_VARTYPE_TIMESTAMP_TAG                   _DB_UNITYPE_TIMESTAMP_TAG

#define _DB_VARTYPE_ANSISTR_TAG                     _DB_UNITYPE_ANSISTR_TAG
#define _DB_VARTYPE_UTF8STR_TAG                     _DB_UNITYPE_UTF8STR_TAG
#define _DB_VARTYPE_UTF16STR_TAG                    _DB_UNITYPE_UTF16STR_TAG
#define _DB_VARTYPE_UTF32STR_TAG                    _DB_UNITYPE_UTF32STR_TAG

#define _DB_VARTYPE_BINARY_TAG                      _DB_UNITYPE_BINARY_TAG
#define _DB_VARTYPE_BLOB_TAG                        _DB_UNITYPE_BLOB_TAG
#define _DB_VARTYPE_UNDEFINED_TAG                   _DB_UNITYPE_UNDEFINED_TAG

#define _DB_VARTYPE_ODBC_DATE_TAG                   (_DB_UNITYPE_ODBC_DATE_TAG)
#define _DB_VARTYPE_ODBC_TIME_TAG                   (_DB_UNITYPE_ODBC_TIME_TAG)
#define _DB_VARTYPE_ODBC_TIMESTAMP_TAG              (_DB_UNITYPE_ODBC_TIMESTAMP_TAG)

#define _DB_VARTYPE_INTERVAL_DAY_TO_SECOND_TAG           _DB_UNITYPE_INTERVAL_DAY_TO_SECOND_TAG
#define _DB_VARTYPE_INTERVAL_YEAR_TO_MONTH_TAG           _DB_UNITYPE_INTERVAL_YEAR_TO_MONTH_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_YEAR_TAG               _DB_UNITYPE_ODBC_INTERVAL_YEAR_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_MONTH_TAG              _DB_UNITYPE_ODBC_INTERVAL_MONTH_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY_TAG                _DB_UNITYPE_ODBC_INTERVAL_DAY_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_HOUR_TAG               _DB_UNITYPE_ODBC_INTERVAL_HOUR_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_MINUTE_TAG             _DB_UNITYPE_ODBC_INTERVAL_MINUTE_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_SECOND_TAG             _DB_UNITYPE_ODBC_INTERVAL_SECOND_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_YEAR_TO_MONTH_TAG      _DB_UNITYPE_ODBC_INTERVAL_YEAR_TO_MONTH_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY_TO_HOUR_TAG        _DB_UNITYPE_ODBC_INTERVAL_DAY_TO_HOUR_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY_TO_MINUTE_TAG      _DB_UNITYPE_ODBC_INTERVAL_DAY_TO_MINUTE_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY_TO_SECOND_TAG      _DB_UNITYPE_ODBC_INTERVAL_DAY_TO_SECOND_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_MINUTE_TAG     _DB_UNITYPE_ODBC_INTERVAL_HOUR_TO_MINUTE_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_SECOND_TAG     _DB_UNITYPE_ODBC_INTERVAL_HOUR_TO_SECOND_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_MINUTE_TO_SECOND_TAG   _DB_UNITYPE_ODBC_INTERVAL_MINUTE_TO_SECOND_TAG

#define _DB_VARTYPE_MAX_TAG                         _DB_UNITYPE_MAX_TAG

#define _DB_COLTYPE_SINT8     (db_coltype_t)_DB_COLTYPE_SINT8_TAG
#define _DB_COLTYPE_UINT8     (db_coltype_t)_DB_COLTYPE_UINT8_TAG
#define _DB_COLTYPE_SINT16    (db_coltype_t)_DB_COLTYPE_SINT16_TAG
#define _DB_COLTYPE_UINT16    (db_coltype_t)_DB_COLTYPE_UINT16_TAG
#define _DB_COLTYPE_SINT32    (db_coltype_t)_DB_COLTYPE_SINT32_TAG
#define _DB_COLTYPE_UINT32    (db_coltype_t)_DB_COLTYPE_UINT32_TAG
#define _DB_COLTYPE_SINT64    (db_coltype_t)_DB_COLTYPE_SINT64_TAG
#define _DB_COLTYPE_UINT64    (db_coltype_t)_DB_COLTYPE_UINT64_TAG

#define _DB_COLTYPE_FLOAT32   (db_coltype_t)_DB_COLTYPE_FLOAT32_TAG
#define _DB_COLTYPE_FLOAT64   (db_coltype_t)_DB_COLTYPE_FLOAT64_TAG
/* #define _DB_COLTYPE_FIXED     (db_coltype_t)_DB_COLTYPE_FIXED_TAG */
#define _DB_COLTYPE_CURRENCY  (db_coltype_t)_DB_COLTYPE_CURRENCY_TAG

#define _DB_COLTYPE_DATE      (db_coltype_t)_DB_COLTYPE_DATE_TAG
#define _DB_COLTYPE_TIME      (db_coltype_t)_DB_COLTYPE_TIME_TAG
#define _DB_COLTYPE_DATETIME  (db_coltype_t)_DB_COLTYPE_DATETIME_TAG
#define _DB_COLTYPE_TIMESTAMP (db_coltype_t)_DB_COLTYPE_TIMESTAMP_TAG

#define _DB_COLTYPE_ANSISTR   (db_coltype_t)_DB_COLTYPE_ANSISTR_TAG
#define _DB_COLTYPE_UTF8STR   (db_coltype_t)_DB_COLTYPE_UTF8STR_TAG
#define _DB_COLTYPE_UTF16STR   (db_coltype_t)_DB_COLTYPE_UTF16STR_TAG
#define _DB_COLTYPE_UTF32STR   (db_coltype_t)_DB_COLTYPE_UTF32STR_TAG

#define _DB_COLTYPE_BINARY     (db_coltype_t)_DB_COLTYPE_BINARY_TAG
#define _DB_COLTYPE_UNDEFINED  (db_coltype_t)_DB_COLTYPE_UNDEFINED_TAG
#define _DB_COLTYPE_BLOB       (db_coltype_t)_DB_COLTYPE_BLOB_TAG

#define _DB_COLTYPE_INTERVAL_DAY_TO_SECOND               (db_coltype_t)_DB_COLTYPE_INTERVAL_DAY_TO_SECOND_TAG
#define _DB_COLTYPE_INTERVAL_YEAR_TO_MONTH               (db_coltype_t)_DB_COLTYPE_INTERVAL_YEAR_TO_MONTH_TAG

#define _DB_VARTYPE_SINT8      (db_vartype_t)_DB_VARTYPE_SINT8_TAG
#define _DB_VARTYPE_UINT8      (db_vartype_t)_DB_VARTYPE_UINT8_TAG
#define _DB_VARTYPE_SINT16     (db_vartype_t)_DB_VARTYPE_SINT16_TAG
#define _DB_VARTYPE_UINT16     (db_vartype_t)_DB_VARTYPE_UINT16_TAG
#define _DB_VARTYPE_SINT32     (db_vartype_t)_DB_VARTYPE_SINT32_TAG
#define _DB_VARTYPE_UINT32     (db_vartype_t)_DB_VARTYPE_UINT32_TAG
#define _DB_VARTYPE_SINT64     (db_vartype_t)_DB_VARTYPE_SINT64_TAG
#define _DB_VARTYPE_UINT64     (db_vartype_t)_DB_VARTYPE_UINT64_TAG

#define _DB_VARTYPE_FLOAT32    (db_vartype_t)_DB_VARTYPE_FLOAT32_TAG
#define _DB_VARTYPE_FLOAT64    (db_vartype_t)_DB_VARTYPE_FLOAT64_TAG

#define _DB_VARTYPE_DATE       (db_vartype_t)_DB_VARTYPE_DATE_TAG
#define _DB_VARTYPE_TIME       (db_vartype_t)_DB_VARTYPE_TIME_TAG
#define _DB_VARTYPE_DATETIME   (db_vartype_t)_DB_VARTYPE_DATETIME_TAG
#define _DB_VARTYPE_TIMESTAMP  (db_vartype_t)_DB_VARTYPE_TIMESTAMP_TAG

#define _DB_VARTYPE_ODBC_DATE      (db_vartype_t)_DB_VARTYPE_ODBC_DATE_TAG
#define _DB_VARTYPE_ODBC_TIME      (db_vartype_t)_DB_VARTYPE_ODBC_TIME_TAG
#define _DB_VARTYPE_ODBC_TIMESTAMP (db_vartype_t)_DB_VARTYPE_ODBC_TIMESTAMP_TAG

#define _DB_VARTYPE_ANSISTR    (db_vartype_t)_DB_VARTYPE_ANSISTR_TAG
#define _DB_VARTYPE_UTF8STR    (db_vartype_t)_DB_VARTYPE_UTF8STR_TAG
#define _DB_VARTYPE_UTF16STR    (db_vartype_t)_DB_VARTYPE_UTF16STR_TAG
#define _DB_VARTYPE_UTF32STR    (db_vartype_t)_DB_VARTYPE_UTF32STR_TAG

#define _DB_VARTYPE_BINARY     (db_vartype_t)_DB_VARTYPE_BINARY_TAG
#define _DB_VARTYPE_BLOB       (db_vartype_t)_DB_VARTYPE_BLOB_TAG
#define _DB_VARTYPE_UNDEFINED  (db_vartype_t)_DB_VARTYPE_UNDEFINED_TAG

#define _DB_VARTYPE_INTERVAL_DAY_TO_SECOND               (db_vartype_t)_DB_VARTYPE_INTERVAL_DAY_TO_SECOND_TAG
#define _DB_VARTYPE_INTERVAL_YEAR_TO_MONTH               (db_vartype_t)_DB_VARTYPE_INTERVAL_YEAR_TO_MONTH_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_YEAR                   (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_YEAR_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_MONTH                  (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_MONTH_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY                    (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_DAY_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_HOUR                   (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_HOUR_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_MINUTE                 (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_MINUTE_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_SECOND                 (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_SECOND_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_YEAR_TO_MONTH          (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_YEAR_TO_MONTH_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY_TO_HOUR            (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_DAY_TO_HOUR_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY_TO_MINUTE          (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_DAY_TO_MINUTE_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_DAY_TO_SECOND          (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_DAY_TO_SECOND_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_MINUTE         (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_MINUTE_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_SECOND         (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_HOUR_TO_SECOND_TAG
#define _DB_VARTYPE_ODBC_INTERVAL_MINUTE_TO_SECOND       (db_vartype_t)_DB_VARTYPE_ODBC_INTERVAL_MINUTE_TO_SECOND_TAG

/* shutdown mode */
#define _DB_SOFT_SHUTDOWN 0  /* perform soft shutdown, waiting all the transactions to complete first */

/* describe table */
#define _DB_DESCRIBE_TABLE_FIELDS       0x00001
#define _DB_DESCRIBE_TABLE_INDEXES      0x00002
#define _DB_DESCRIBE_TABLE_FOREIGN_KEYS 0x00004
#define _DB_DESCRIBE_TABLE_MASK         0x00007

/* watch events */
#define _DB_WATCH_ROW_INSERT          0x00001
#define _DB_WATCH_ROW_UPDATE          0x00002
#define _DB_WATCH_ROW_DELETE          0x00004

#define _DB_WATCH_PRIMARY_KEY         0x00100u  /* include primary key info into watch row */
#define _DB_WATCH_MODIFIED_FIELDS     0x00200u  /* include all the modified fields into the watch row */
#define _DB_WATCH_BOUND_FIELDS        0x00400u  /* include all the bound fields into the watch row */
#define _DB_WATCH_ALL_FIELDS          0x00800u  /* include all the fields into watch row */
#define _DB_WATCH_SCOPE_MASK          0x0ff00u

#define _DB_WATCH_FORMER_VALUES       0x00008u  /* include updated fields into aux row */

#define _DB_WATCH_FILTER_MODIFIED     0x10000u
#define _DB_WATCH_FILTER_NOT_SELF     0x20000u
#define _DB_WATCH_FILTER_MASK         0xf0000u

/* File Modes */
#define _DB_READ_ONLY      0x0001
#define _DB_NOLOGGING      0x0002
#define _DB_NOLOCKING      0x0004
#define _DB_UTF8_NAME      0x0008
#define _DB_ATOMIC_WRITE   0x0010
#define _DB_CONN_LOCK      0x0020
#define _DB_RISK_INCONSISTENCY 0x0040
#define _DB_SNAPSHOT_STORAGE 0x0080

/* Database Storage Types */
#define _DB_FILE_STORAGE   0x1000
#define _DB_MEMORY_STORAGE 0x2000
/* #define _DB_RAW_STORAGE    0x3000 */

#define _DB_FILE_TYPE_MASK 0xF000

/* File Interfaces */
#define _DB_FILE_DEFFS      0x00000
#define _DB_FILE_WIN32      0x10000
#define _DB_FILE_POSIX      0x20000
#define _DB_FILE_YAFFS      0x30000
#define _DB_FILE_UCFS       0x40000
#define _DB_FILE_RAMFS      0x50000
#define _DB_FILE_INTERFACE_MASK 0xF0000

#define _DB_FILE_CRASHFS    0x1000000

#define _DB_DEFAULT_JOURNAL  0x0000
#define _DB_INTERNAL_JOURNAL 0x0001
#define _DB_EXTERNAL_JOURNAL 0x0002
#define _DB_NULL_JOURNAL     0x0003
#define _DB_DUMMY_JOURNAL    0x0004

#define _DB_CIPHER_TYPE_MASK    0xff000000u
#define _DB_CIPHER_MODE_MASK    0x00ff0000u
#define _DB_CIPHER_PARAM_MASK   0x0000ffffu

#define _DB_CIPHER_AES          0x01000000u
#define _DB_CIPHER_CTR          0x00010000u

#define _DB_CIPHER_NONE         0
#define _DB_CIPHER_USER         0xff000000u

#define _DB_CIPHER_AES128_CTR   (_DB_CIPHER_AES | _DB_CIPHER_CTR | 128u)
#define _DB_CIPHER_AES256_CTR   (_DB_CIPHER_AES | _DB_CIPHER_CTR | 256u)

#define _LM_NONE  0
#define _LM_LOCAL 1

#define _DB_SEQUENCE_MIN   INT64_MIN
#define _DB_SEQUENCE_MAX   INT64_MAX

#define _DB_SERVER_SHM_ENABLE   1

#define _DB_PRIO_MIN    0
#define _DB_PRIO_MAX    31
#define _DB_PRIO_NORMAL ((_DB_PRIO_MAX + _DB_PRIO_MIN ) / 2)

#ifndef _DB_OMIT_INDEXTYPE_NAMES
#define _DB_INDEXTYPE_DEFAULT DB_INDEXTYPE_DEFAULT
#define _DB_INDEXTYPE_BTREE   DB_INDEXTYPE_BTREE
#else
typedef enum
{
    _DB_INDEXTYPE_DEFAULT,
    _DB_INDEXTYPE_BTREE
} db_indextype_t;
#endif

#ifndef _DB_OMIT_TABLETYPE_NAMES
#define _DB_TABLETYPE_DEFAULT   DB_TABLETYPE_DEFAULT
#define _DB_TABLETYPE_KHEAP     DB_TABLETYPE_KHEAP
#define _DB_TABLETYPE_MEMORY    DB_TABLETYPE_MEMORY
#define _DB_TABLETYPE_CLUSTERED DB_TABLETYPE_CLUSTERED
#define _DB_TABLETYPE_SNAPSHOT  DB_TABLETYPE_SNAPSHOT
#define _DB_TABLETYPE_CIRCULAR  DB_TABLETYPE_CIRCULAR
#define _DB_TABLETYPE_RECORD    DB_TABLETYPE_RECORD
#else
typedef enum
{
    _DB_TABLETYPE_DEFAULT   = 0,
    _DB_TABLETYPE_KHEAP     = 1, /* the key heap table */
    _DB_TABLETYPE_MEMORY    = 2, /* in memory table */
    _DB_TABLETYPE_CLUSTERED = 3, /* clustered table */
} db_tabletype_t;
typedef db_tabletype_t_internal db_tabletype_t;
#endif

/* numerical values */
#define _DB_INFO_APIVER        1 /* UINT: api version number */
#define _DB_INFO_MINAPI        2 /* UINT: minimum supported api version */

/* library version */
#define _DB_INFO_MAJOR         3 /* major version number */
#define _DB_INFO_MINOR         4 /* minor version number */
#define _DB_INFO_PATCH         5 /* patch level number */
#define _DB_INFO_BUILD         6 /* build number */

/* strings */
#define _DB_INFO_FULL_ANSI_NAME    20
#define _DB_INFO_FULL_UTF8_NAME    21
#define _DB_INFO_FULL_UTF16_NAME    22
#define _DB_INFO_FULL_UTF32_NAME    23

#define _DB_INFO_SHORT_ANSI_NAME   24
#define _DB_INFO_SHORT_UTF8_NAME   25
#define _DB_INFO_SHORT_UTF16_NAME   26
#define _DB_INFO_SHORT_UTF32_NAME   27

/* library flags */
#define _DB_INFO_DEBUG         40 /* BOOL: debugging */
#define _DB_INFO_THREAD        41 /* BOOL: compiled in threading support */
#define _DB_INFO_SHAREDLIB     45 /* BOOL: compiled as shared library or dll */

#define _DB_INFO_DISPOSITION   44 /* UINT: db library disposition, one of following */
#define _DB_DISPOSITION_STANDALONE  0 /* Stand-alone library embedded in process */
#define _DB_DISPOSITION_IPCSOCKETS  2 /* IPC over sockets */

#define _DB_INFO_SUPPORT       46 /* bitset: set of compiled in options */
#define _DB_SUPPORT_LOGGING     0x000001u
#define _DB_SUPPORT_CRYPT       0x000002u
#define _DB_SUPPORT_WATCHER     0x000004u
#define _DB_SUPPORT_SEQUENCE    0x000008u
#define _DB_SUPPORT_BLOB        0x000010u
#define _DB_SUPPORT_SQL         0x000020u
#define _DB_SUPPORT_TYPECVT     0x000040u
#define _DB_SUPPORT_UNICODE     0x000080u
#define _DB_SUPPORT_DDL         0x000100u
#define _DB_SUPPORT_ATOMIC_TX   0x000200u
#define _DB_SUPPORT_FILTERS     0x000400u
#define _DB_SUPPORT_SORT        0x000800u
#define _DB_SUPPORT_ATOMIC_OP   0x001000u
#define _DB_SUPPORT_REPLICATION 0x002000u

#define _DB_INFO_LOCK_LEVEL          47
#define _DB_LOCK_LEVEL_NONE     0
#define _DB_LOCK_LEVEL_ROW      1
#define _DB_LOCK_LEVEL_STORAGE  2

/* on error */
#define _DB_INFO_ERROR (~(uintptr_t)0)

#define _DB_SAVEPOINT_DEFAULT    0
#define _DB_SAVEPOINT_UNIQUE     1
#define _DB_SAVEPOINT_NESTED     2
#define _DB_SAVEPOINT_OVERRIDE   3

C_HEADER_END

#endif /* ITTIA_DB_LEGACY_H */
