/**************************************************************************/
/*                                                                        */
/*      Copyright (c) 2005-2021 by ITTIA L.L.C. All rights reserved.      */
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
 * The ITTIA DB IoT Embedded C API.
 */

#ifndef DB_IOT_STORAGE_H
#define DB_IOT_STORAGE_H

#include <ittia/db.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Time series handle. @see CAPITimeSeries @ingroup CAPITimeSeries */
DB_DECLARE_HANDLE(db_time_series_t);
/** Time series query handle. @see CAPITimeSeries @ingroup CAPITimeSeries */
DB_DECLARE_HANDLE(db_time_series_query_t);

/** @addtogroup CAPIDatabase
 *  @{ */ 
/// Open the database object, which must already exist.
#define DB_OPEN_EXISTING       0x000000u
/// Open the database object, creating it if necessary.
#define DB_OPEN_OR_CREATE      0x100000u
/// Create an empty database object, replacing an existing database if necessary.
#define DB_CREATE_OR_OVERWRITE 0x200000u
/// Create an empty database object, which must not already exist.
#define DB_CREATE_NEW          0x300000u

/// Bitmask for open/create flags.
#define DB_OPEN_CREATE_MASK    0x300000u

/**
 * @brief db_open_iot_storage opens or creates a database storage.
 * @param file_name
 *   Name of file or storage media
 * @param alias
 *   (optional) Alias name for connection and close storage
 * @param flags
 *   Specify behavior when database does or does not already exists
 * @param page_size
 *   Size of each database page
 * @param storage_cache_segment
 *   Database page cache memory segment base address
 * @param storage_cache_size
 *   Database page cache memory segment size
 * @param auth_info
 *   (optional) Authorization credentials for a password-protected or encrypted database
 * @returns
 *   DB_NOERROR on success, negative number on failure.
 *
 * If the same database file is already open, db_open_iot_storage does nothing
 * and returns DB_EEXIST.
 */
dbstatus_t db_open_iot_file_storage(const char * file_name, const char * alias, uint32_t flags, int32_t page_size, void * storage_cache_segment, size_t storage_cache_size, db_auth_info_t * auth_info);

/**
 * @brief db_close_storage closes all connections to a database storage and
 * releases all connection handles.
 * @param name
 *   (optional) Name or alias of storage
 * @returns
 *   DB_NOERROR on success, negative number on failure
 *
 * When name is NULL, all databases instances are closed.
 */
dbstatus_t db_close_storage(const char * name);

/**
 * @brief db_connect opens a connection to an open database storage from a single thread.
 * @param [out] handle
 *   Destination for database connection handle
 * @param name
 *   Name or alias of storage
 * @param user_name
 *   (optional) name of an authorized user
 * @param password
 *   (optional) password token
 * @param context
 *   (optional) User connection context
 * @returns
 *   DB_NOERROR on success, negative number on failure
 *
 * Each thread must call this function access the specified database.
 *
 * If the database was opened with an alias, @a name must be an alias.
 */
dbstatus_t db_connect(db_t * handle, const char * name, const char * user_name, const char * password, void * context);

/**
 * @brief db_get_connection_context returns the context pointer associated with
 * a database connection.
 *
 * @param handle
 *   Handle to an ITTIA DB database connection
 * @returns
 *   Context pointer that was originally supplied to db_connect
 */
void * db_get_connection_context(db_t handle);

/**
 * @brief db_disconnect closes a database connection.
 * @param handle
 *   Handle to an ITTIA DB database connection
 * @returns
 *   DB_NOERROR on success, negative number on failure
 *
 */
dbstatus_t db_disconnect(db_t handle);

/**
 * @brief db_flush_file writes cached database changes to disk
 * @param handle
 *   Handle to an ITTIA DB database connection
 * @param flags
 *   Flush mode and completion mode
 * @returns
 *   DB_NOERROR on success, negative number on failure
 *
 * Choose one flush mode flag:
 *
 * - #DB_FLUSH_JOURNAL (default)
 * - #DB_FLUSH_STORAGE
 *
 * Choose one completion mode flag:
 *
 * - #DB_GROUP_COMPLETION (default)
 * - #DB_FORCED_COMPLETION
 *
 * The default flags are sufficient to persist data.
 */
dbstatus_t db_flush_file(db_t handle, db_flags_t flags);
/** @} */

/** @addtogroup CAPITimeSeries
 *  @{ */ 
/**
 * @brief db_set_max_timestamps defines the maxmimum number of timestamps to store 
 *     before ingesting into storage.
 * @param handle
 *   Handle to an ITTIA DB database connection
 * @param max_count
 *   Defines the ingestion amount, or the total number of timestamps queued for ingestion
 * @param pages_per_remove
 *   Number of pages to remove each ingestion
 * @returns
 *   DB_NOERROR on success, negative number on failure
 */
dbstatus_t db_set_max_timestamps(db_t handle, int32_t max_count, int32_t pages_per_remove);
/** @} */

/** @addtogroup CAPIDatabase
 *  @{ */
/**
 * @brief The db_file_info_t struct describes information about a database
 * file storage.
 */
typedef struct db_file_info_s {
    int64_t data_file_bytes;  ///< Size of the the data file(s), in bytes
    int64_t log_file_bytes;   ///< Size of the current log file, in bytes
    int64_t used_data_bytes;  ///< Number of used bytes in the data file(s)
    int64_t time_series_data_bytes;  ///< Size of time series data, excluding overhead, in bytes
} db_file_info_t;

/**
 * @brief db_file_info obtains information about a database file storage.
 * @param handle
 *   Handle to an ITTIA DB database connection
 * @param [out] info
 *   Destination for file information
 * @returns
 *   DB_NOERROR on success, negative number on failure
 */
dbstatus_t db_file_info(db_t handle, db_file_info_t * info);
/** @} */

/** @addtogroup CAPITimeSeries
 *  @{ */ 
/**
 * @brief Set data retention policy for time series data.
 * @param handle
 *   Handle to an ITTIA DB database connection
 * @param retain_data_bytes
 *   Number of bytes of time series data to retain
 * @param max_data_bytes
 *   Maximum number of bytes to allocate for time series data
 * @return
 *   DB_NOERROR on success, negative number on failure
 *
 * After calling this function, time series data will automatically wrap around
 * and replace the oldest timestamps when putting new data. The current data
 * retention policy is persisted.
 *
 * When the size of time series data approaches @a max_data_bytes, data for
 * the oldest timestamps is automatically removed from time series storage.
 * The database will never shrink below @a retain_data_bytes of time series
 * data when old data is removed automatically.
 *
 * Wrap around performance is influenced by the difference between
 * @a max_data_bytes and @a retain_data_bytes. @a max_data_bytes must be at
 * least one database page larger than @a retain_data_bytes.
 */
dbstatus_t db_set_time_series_data_retention(db_t handle, int64_t retain_data_bytes, int64_t max_data_bytes);

/**
 * @brief Convert timestamp data structure to microseconds timestamp
 * @param [out] dest
 *   Timestamp in microseconds since epoch
 * @param src
 *   Timestamp as a data structure
 */
void db_timestamp_to_usec(db_timestamp_usec_t * dest, const db_timestamp_t * src);

/**
 * @brief Convert microseconds timestamp to timestamp data structure.
 * @param [out] dest
 *   Timestamp as a data structure
 * @param src
 *   Timestamp in microseconds since epoch
 */
void db_timestamp_from_usec(db_timestamp_t * dest, db_timestamp_usec_t src);
/** @} */

/** @addtogroup CAPIDatabase
 *  @{ */ 
/**
 * @brief Set the value of a storage variable in a database
 * @param db
 *   Handle to an ITTIA DB database connection
 * @param variable
 *   Number that identifies the variable
 * @param value
 *   Value to write
 * @returns
 *   DB_NOERROR when successful, negative number on failure
 *
 * Up to 16 variables may be stored in each database, numbered 0-15.
 *
 * A transaction is started if no transaction is active. The value is only
 * saved permanently when the transaction is committed.
 */
dbstatus_t db_set_storage_variable(db_t db, db_fieldno_t variable, db_largeint_t value);

/**
 * @brief Read a storage variable from a database
 * @param db
 *   Handle to an ITTIA DB database connection
 * @param variable
 *   Number that identifies the variable
 * @param [out] value
 *   Value to read
 * @returns
 *   DB_NOERROR when successful, negative number on failure
 */
dbstatus_t db_get_storage_variable(db_t db, db_fieldno_t variable, db_largeint_t * value);
/** @} */

/** @addtogroup CAPITimeSeries
 *  @{ */ 
/**
 * @brief Open a named series of timestamp/value pairs
 * @param [out] handle
 *   Reference to the time series
 * @param db
 *   Handle to an ITTIA DB database connection
 * @param name
 *   Name of the time series
 * @param type
 *   Type of data to store in the time series
 * @returns
 *   DB_NOERROR when successful, negative number on failure
 *
 * The time series is uniquely identified in the database by its name. A new
 * time series is added to the database if one does not already exist with the
 * given name.
 *
 * After the time series is opened successfully, a handle is allocated and
 * assigned as output. Pass this handle to other functions that need to operate
 * on the time series. When access to the time series is no longer needed, call
 * db_close_time_series to release the handle.
 */
dbstatus_t db_open_time_series(db_time_series_t * handle, db_t db, const db_ansi_t * name, db_coltype_t type);

/**
 * @brief Invalidate a time series handle and release associated resources
 * @param handle
 *   Reference to the time series
 * @returns
 *   DB_NOERROR when successful, negative number on failure
 *
 * A limited number of time series can be open at once. A time series handle
 * must be closed with when it is no longer needed.
 *
 * The handle is invalidated and must not be used after calling this function.
 */
dbstatus_t db_close_time_series(db_time_series_t handle);

/**
 * @brief Put a timestamp/value pair into a time series
 * @param handle
 *   Reference to the time series
 * @param usec
 *   Microseconds timestamp
 * @param value
 *   Value data
 * @returns
 *   DB_NOERROR when successful, negative number on failure
 *
 * If a value already exists in the series at the given timestamp, it is
 * replaced.
 */
dbstatus_t db_time_series_put_float32(db_time_series_t handle, db_timestamp_usec_t usec, db_float32_t value);

/**
 * @brief Remove the oldest time series data from a database
 * @param handle
 *   Handle to an ITTIA DB database connection
 * @param usec
 *   Lowest timestamp to keep
 * @returns
 *   Number of distinct timestamps removed when successful, negative number on failure
 *
 * Remove all timestamp/value pairs strictly older than @a usec. Any values stored at precisely
 * @a usec are not removed.
 */
dbstatus_t db_time_series_remove_before(db_t handle, db_timestamp_usec_t usec);

#define DB_QUERY_OLDEST_TO_NEWEST   0x00000000u
#define DB_QUERY_NEWEST_TO_OLDEST   0x00000001u

/**
 * @brief Query a time range in a single time series
 *
 * @param handle 
 *   Reference to a prepared time series query
 * @param begin_time
 *   Start timestamp, inclusive
 * @param end_time
 *   End timestamp, exclusive
 * @param [out] timestamp_dest
 *   Destination for timestamp data
 * @param [out] value_dest
 *   Destination for value data
 * @param max_read
 *   Maximum number of timestamp/value pairs to read at once
 * @param [out] next_begin_time
 *   Start timestamp for next batch, if successful
 * @returns
 *   number of timestamp/value pairs read when successful, negative number on
 *   failure
 *
 * Reads up to @a max_read timestamp/value pairs from the series into the
 * arrays @a timestamp_dest and @a value_dest. Timestamps and values are sorted
 * in ascending order by time.
 *
 * If successful, the number of values read is returned and @a next_begin_time
 * is assigned a value that is greater than any returned timestamp, but less
 * than or equal to @a end_time. In the next call to this function, replace
 * the @a begin_time argument with *next_begin_time from the previous call to
 * and repeat until a number less than @a max_read is returned. This will read
 * all timestamp/value pairs in the original time range.
 *
 * Pairs are read greater or equal to the @a begin_time and strictly less than
 * the @a end_time. If no timestamp/value pairs exist in that interval, 0 is
 * returned.
 */
dbstatus_t db_query_time_series_range_float32(db_time_series_t handle, db_timestamp_usec_t begin_time, db_timestamp_usec_t end_time, db_timestamp_usec_t timestamp_dest[], db_float32_t value_dest[], db_len_t max_read, db_timestamp_usec_t * next_begin_time);

/**
 * @brief Query a time range in any number of time series
 *
 * @param [out] handle
 *   Reference to query state
 * @param db
 *   Handle to an ITTIA DB database connection
 * @param [in,out] series_name_list
 *   (optional) Array of series names to include in query result
 * @param series_count
 *   Number of names in @a series_name_list
 * @param begin_time
 *   (optional) Start timestamp, inclusive
 * @param end_time
 *   (optional) End timestamp, exclusive
 * @param flags
 *   Query flags
 * @returns
 *   The actual number of time series in the query result, or a negative number
 *   on failure
 *
 * If @a series_name_list is NULL, the query result will include all time
 * series with values in the given time range.
 *
 * If @a begin_time or @a end_time is NULL, the query result will not have a
 * lower or upper bound, respectively.
 *
 * Query flags accepted:
 *
 * - DB_QUERY_OLDEST_TO_NEWEST: sort results from oldest to newest timestamp
 * - DB_QUERY_NEWEST_TO_OLDEST: sort results from newest to oldest timestamp
 *
 * After the query is prepared successfully, a handle is allocated and
 * assigned as output. Pass this handle to other functions that need to operate
 * on the time series. When access to the time series is no longer needed, call
 * db_close_time_series_query to release the handle.
 */
dbstatus_t db_prepare_time_series_query(db_time_series_query_t * handle, db_t db, const char* series_name_list[], db_len_t series_count, db_timestamp_usec_t * begin_time, db_timestamp_usec_t * end_time, db_flags_t flags);

/**
 * @brief Count distinct timestamps in a time series query
 * @param handle
 *   Reference to a prepared time series query
 * @param [out] read_timestamp_count
 *   Number of distinct timestamps read from the query so far.
 * @param [out] total_timestamp_estimate
 *   Estimate of the total number of distinct timestamps in the query
 * @returns
 *   Negative number on failure
 *
 * Immediately after preparing a query, the @a read_timestamp_count starts at
 * zero, then increments each time db_fetch_next_timestamp_float32 returns with
 * a different timestamp. If @a read_timestamp_count is NULL, the count is not
 * assigned.
 *
 * The @a total_timestamp_estimate is assigned the approximate number of
 * distinct timestamp values in the time range specified when the query
 * was prepared. The accuracy of the estimate will generally improve after
 * part of the query has been read, and will be equal to @a read_timestamp_count
 * after the entire query result has been read.
 *
 * If @a total_timestamp_estimate is null NULL, the estimate is not calculated
 * or assigned. Calculating the estimate is comparable in cost to
 * db_fetch_next_timestamp_float32.
 */
dbstatus_t db_count_timestamps(db_time_series_query_t handle, int32_t * read_timestamp_count, int32_t * total_timestamp_estimate);

/**
 * @brief Invalidate a time series query handle and release associated resources
 * @param handle
 *   Reference to a prepared time series query
 * @returns
 *   Negative number on failure
 *
 * A limited number of time series queries can be open at once. A time series
 * query handle must be closed with when it is no longer needed.
 *
 * The handle is invalidated and must not be used after calling this function.
 */
dbstatus_t db_close_time_series_query(db_time_series_query_t handle);

/**
 * @brief Get the name of a time series in a query results
 * @param handle
 *   Reference to a prepared time series query
 * @param fieldno
 *   Query column number
 * @returns
 *   Name of the time series in the specified column
 *
 * The @a fieldno must be strictly less than the number of series in the query,
 * returned by db_prepare_time_series_query.
 *
 * The pointer returned by `db_get_time_series_name` is only valid until the
 * next use of the same database connection. Either call this function each
 * time the name of a time series is needed, or copy the string data before
 * calling this function again.
 */
const char * db_get_time_series_name(db_time_series_query_t handle, db_fieldno_t fieldno);

/**
 * @brief Fetch values for the next timestamp in a query results
 * @param handle
 *   Reference to a prepared time series query
 * @param [out] timestamp
 *   Destination for timestamp
 * @param [out] fieldno_list
 *   Array of field numbers
 * @param [out] value_list
 *   Array of values
 * @param list_size
 *   Size of @a field_list and @a value_list
 * @returns
 *   Number of fieldno/value pairs read, or a negative number on failure
 *
 * Reads data for the next timestamp in the query result. Call this function
 * repeatedly to read all query results.
 *
 * The next timestamp is assigned to @a timestamp. An array of fieldno and
 * value pairs are assigned to @a fieldno_list and @a value_list. If a time
 * series does not have a value at the timestamp, it is not included in these
 * lists. The lists are sorted in fieldno order.
 *
 * This function reads up to @a list_size values for the next timestamp. If
 * more values are available, the next call to this function will continue to
 * read from the same timestamp.
 *
 */
dbstatus_t db_fetch_next_timestamp_float32(db_time_series_query_t handle, db_timestamp_usec_t * timestamp, db_fieldno_t fieldno_list[], db_float32_t value_list[], db_len_t list_size);
/** @} */

#ifdef __cplusplus
}
#endif

#endif // DB_IOT_STORAGE_H
