/**************************************************************************/
/*                                                                        */
/*      Copyright (c) 2005-2022 by ITTIA L.L.C. All rights reserved.      */
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

#ifndef DB_STREAM_H
#define DB_STREAM_H

#include <ittia/db.h>

C_HEADER_BEGIN

/** @addtogroup CAPIStream
 *  @{ */ 

/**
 * @brief The db_stream_graph_t struct defines a streaming graph.
 */
typedef struct db_stream_graph_s* db_stream_graph_t;

/**
 * @brief The db_stream_node_t struct defines a node in a streaming graph.
 */
typedef struct db_stream_node_s* db_stream_node_t;

/**
 * @brief The db_stream_callback_t defines the callback function for a @ db_stream_node_t.
 */
typedef void (*db_stream_callback_t)(db_stream_node_t, void *);

/**
 * Aggregate Types.
 */
enum db_aggregate_t {
    DB_AGGREGATE_COUNT,
    DB_AGGREGATE_SUM,
    DB_AGGREGATE_AVERAGE,
};

/**
 * @brief db_stream_create_graph creates a stream of given memory size.
 * @param [out] graph
 *   Destination for database stream
 * @param mem
 *   Memory used by the database stream
 * @param size
 *   Size of memory used by database stream
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * Use this function to create a graph using @a mem of @a size. The 
 *  stream graph is returned through a reference to @a graph.  
 */
dbstatus_t db_stream_create_graph(db_stream_graph_t * graph, void * mem, size_t size);

/**
 * @brief db_stream_free_graph frees a graph previously created.
 * @param [out] graph
 *   Destination for database connection handle
 * @param peak_memory_size
 *   Name or alias of storage
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  *Use this function to free the memory used by the stream @a graph.
 */
void db_stream_free_graph(db_stream_graph_t graph, size_t * peak_memory_size);

/**
 * @brief db_stream_create_row_input creates an input row to a streaming graph.
 * @param [out] output
 *   Destination node for output row
 * @param graph
 *   Destination graph to add row to 
 * @param field_list
 *   Schema to use for output row
 * @param field_count
 *   Number of fields used in schema
 * @param timestamp_field
 *   Field index number data type
 * @param key_field
 *   Field index number data type
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * This function requires a stream @a graph to be initialized previously to this call.
 *    Use this function to create an input node to a data stream, the created node will be
 *    returned through a reference to @a output.
 * 
 *   * The @a field_list contains the schema for an input row to the node.   
 */
dbstatus_t db_stream_create_row_input(db_stream_node_t * output, db_stream_graph_t graph, const db_fielddef_t * field_list, const db_len_t field_count, db_fieldno_t timestamp_field, db_fieldno_t key_field);

/**
 * @brief db_stream_set_sint32 sets a signed 32 bit integer field of data stream.
 * @param [in] stream
 *   Stream node of field to be set
 * @param field
 *   Destination field to set
 * @param value
 *   Value of stream to set
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  Use this function to set the @a field of the stream node @a stream to the value of @a value.
 */
dbstatus_t db_stream_set_sint32(db_stream_node_t stream, db_fieldno_t field, int32_t value);

/**
 * @brief db_stream_set_uint64 sets an unsigned 64 bit integer field of data stream.
 * @param [in] stream
 *   Stream node of field to be set
 * @param field
 *   Destination field to set
 * @param value
 *   Value of stream to set
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  *  Use this function to set the @a field of the stream node @a stream to the value of @a value.
 */
dbstatus_t db_stream_set_uint64(db_stream_node_t stream, db_fieldno_t field, uint64_t value);

/**
 * @brief db_stream_set_timestamp_usec sets the timestamp field of data stream.
 * @param [in] stream
 *   Stream node of field to be set
 * @param field
 *   Destination field to set
 * @param value
 *   Value of stream to set
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  *  Use this function to set the @a field of the stream node @a stream to the value of @a value.
 */
dbstatus_t db_stream_set_timestamp_usec(db_stream_node_t stream, db_fieldno_t field, db_timestamp_usec_t value);

/**
 * @brief db_stream_set_float32 sets a 32 bit float field of data stream.
 * @param [in] stream
 *   Stream node of field to be set
 * @param field
 *   Destination field to set
 * @param value
 *   Value of stream to set
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  *  Use this function to set the @a field of the stream node @a stream to the value of @a value.
 */
dbstatus_t db_stream_set_float32(db_stream_node_t stream, db_fieldno_t field, db_float32_t value);

/**
 * @brief db_stream_set_float64 sets a 64 bit float field of data stream.
 * @param [in] stream
 *   Stream node of field to be set
 * @param field
 *   Destination field to set
 * @param value
 *   Value of stream to set
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  *  Use this function to set the @a field of the stream node @a stream to the value of @a value.
 */
dbstatus_t db_stream_set_float64(db_stream_node_t stream, db_fieldno_t field, db_float64_t value);

/**
 * @brief db_stream_process processes the fields set currently in the stream.
 * @param [in] stream
 *   Stream to process
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * This function will process the current input(s) of the @a stream at the time of calling it. 
 */
dbstatus_t db_stream_process(db_stream_node_t stream);

/**
 * @brief db_stream_create_row_output creates an output row to a streaming graph.
 * @param [out] output
 *   Destination node for output row
 * @param input
 *   Destination graph to add row to 
 * @param callback
 *   (OPtional) Reference to a callback function 
 * @param argument
 *   (Optional) Argument to callback function
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * Use this function to create a node to process output from the stream @a input using the callback
 *  function (optional) @a callback provided with the optional argument @a argument to the callback function. 
 *  
 *  * The output is returned via reference to the output node by @a output.
 *  
 */
dbstatus_t db_stream_create_row_output(db_stream_node_t * output, db_stream_node_t input, db_stream_callback_t callback, void * argument);

/**
 * @brief db_stream_get_tag gets the tag of an entry in a data stream.
 * @param stream
 *   Destination stream to get tag from
 * @returns
 *   '+' for a new entry in the stream
 *   '-' for a deletion in the stream
 *   'U' for an update in the stream
 * 
 *  * Use this function to get the tag from an entry in a data stream, 
 *    this function can be used inside a callback function to the streaming
 *   node @a stream.
 */
char db_stream_get_tag(db_stream_node_t stream);

/**
 * @brief db_stream_get_transaction_timestamp gets the timestamp value of the most recent transaction.
 * @param stream
 *   Destination node for output row
 * @returns
 *   Timestamp value of transaction
 * 
 *  Use this function to return the latest transaction made from a streaming node.
 */
int64_t db_stream_get_transaction_timestamp(db_stream_node_t stream);

/**
 * @brief db_stream_get_sint32 gets the value of the given field.
 * @param stream
 *   Target stream to get the value from
 * @param field
 *   Field to get the target value from 
 * @returns
 *   Signed 32 bit integer
 * 
 *  * This function returns the value from the output node @a stream at the given field @a field.
 */
int32_t db_stream_get_sint32(db_stream_node_t stream, db_fieldno_t field);

/**
 * @brief db_stream_get_uint32 gets the value of the given field.
 * @param stream
 *   Target stream to get the value from
 * @param field
 *   Field to get the target value from 
 * @returns
 *   Unsigned 32 bit integer
 * 
 *  * This function returns the value from the output node @a stream at the given field @a field.
 */
uint32_t db_stream_get_uint32(db_stream_node_t stream, db_fieldno_t field);

/**
 * @brief db_stream_get_sint64 gets the value of the given field.
 * @param stream
 *   Target stream to get the value from
 * @param field
 *   Field to get the target value from 
 * @returns
 *   Signed 64 bit integer
 * 
 *  * This function returns the value from the output node @a stream at the given field @a field.
 */
int64_t db_stream_get_sint64(db_stream_node_t stream, db_fieldno_t field);

/**
 * @brief db_stream_get_uint64 gets the value of the given field.
 * @param stream
 *   Target stream to get the value from
 * @param field
 *   Field to get the target value from 
 * @returns
 *   Unsigned 64 bit integer
 * 
 *  * This function returns the value from the output node @a stream at the given field @a field.
 */
uint64_t db_stream_get_uint64(db_stream_node_t stream, db_fieldno_t field);

/**
 * @brief db_stream_get_timestamp_usec gets the timestamp of the given field.
 * @param stream
 *   Target stream to get the timestamp from
 * @param field
 *   Field to get the target value from 
 * @returns
 *   Timestamp in microsecond format (us)
 * 
 *  * This function returns the value from the output node @a stream at the given field @a field.
 */
db_timestamp_usec_t db_stream_get_timestamp_usec(db_stream_node_t stream, db_fieldno_t field);

/**
 * @brief db_stream_get_float32 gets the value of the given field.
 * @param stream
 *   Target stream to get the value from
 * @param field
 *   Field to get the target value from 
 * @returns
 *   32 bit float
 * 
 *  * This function returns the value from the output node @a stream at the given field @a field.
 */
db_float32_t db_stream_get_float32(db_stream_node_t stream, db_fieldno_t field);

/**
 * @brief db_stream_get_float64 gets the value of the given field.
 * @param stream
 *   Target stream to get the value from
 * @param field
 *   Field to get the target value from 
 * @returns
 *   64 bit float
 * 
 *  * This function returns the value from the output node @a stream at the given field @a field.
 */
db_float64_t db_stream_get_float64(db_stream_node_t stream, db_fieldno_t field);

/**
 * @brief db_stream_create_queue creates a buffer of stream results in a queue. 
 * @param [out] output
 *   Target node to queue results in
 * @param input
 *   Input node that inserts rows to the queue
 * @param queue_row_count
 *   Maximum number of entries to store in the queue 
 * @returns
 *   DB_NOERROR on success, negative number on failure
 */
dbstatus_t db_stream_create_queue(db_stream_node_t * output, db_stream_node_t input, size_t queue_row_count);

/**
 * @brief db_stream_queue_next creates a buffer of stream results in a queue. 
 * @param [out] output
 *   Target node to queue results in
 * @param input
 *   Input node that inserts rows to the queue
 * @param queue_row_count
 *   Maximum number of entries to store in the queue 
 * @returns
 *   DB_NOERROR on success, negative number on failure
 */
dbstatus_t db_stream_queue_next(db_stream_node_t queue);

/**
 * @brief db_stream_create_filter_uint64 creates a filter on the input node.
 * @param [out] output
 *   Output node from filter
 * @param input
 *   Input node to supply row to filter on 
 * @param field
 *   Field of input row to apply filter to
 * @param compare_op
 *   Type of filter to apply 
 * @param value
 *   Value to use with filter 
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * Use this function to create a filter on a streaming node. The @a compare_op will be applied on the @a input
 *   node on the given @a field using the @a value.
 * 
 *  The output node containing the applied filter is returned through reference to @a output. 
 */
dbstatus_t db_stream_create_filter_uint64(db_stream_node_t * output, db_stream_node_t input, db_fieldno_t field, db_seek_t compare_op, uint64_t value);

/**
 * @brief db_stream_create_time_interval_window creates a range of timestamps called a window.
 * @param [out] output
 *   Output node with window applied
 * @param input
 *   Input node that supplies row to window 
 * @param window_size
 *   Size of the window, in microseconds (us)
 * @param buffer_row_count
 *   Size of the buffer to queue the window (number of entries)
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * Use this function to create a time window on a streaming node. The time window will have a @a window_size amount of time. 
 *   The @a buffer_row_count indicates the number of entries that get buffered before processed into the window.
 * 
 *  The output node containing the applied filter is returned through reference to @a output. 
 */
dbstatus_t db_stream_create_time_interval_window(db_stream_node_t * output, db_stream_node_t input, db_timestamp_usec_t window_size, int32_t buffer_row_count);

/**
 * @brief db_stream_create_aggregates creates a list of aggregates to apply. 
 * @param [out] output
 *   Output node with aggregate(s) applied
 * @param input
 *   Input node that supplies entries to the aggregates
 * @param field_list
 *   Fields to apply to aggregate, 
 *    Note - the number of entries in the field list must match the number of entries
 *      in the aggregate list 
 * @param aggregate_list
 *   List of aggregates to apply to input
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * This function creates a list of aggregates to be applied on the given @a field_list.
 * 
 *  The output node containing the applied filter is returned through reference to @a output. 
 */
dbstatus_t db_stream_create_aggregates(db_stream_node_t * output, db_stream_node_t input, db_fieldno_t * field_list, enum db_aggregate_t * aggregate_list, size_t aggregate_count);

/**
 * @brief db_stream_create_join_all_within joins a number of input nodes into one output.
 * @param [out] output
 *   Output node with join applied
 * @param input_list
 *   List of input nodes to join on
 * @param join_key_list
 *   List of keys to join inputs on
 * @param join_source_count
 *   Numer of inputs to join on
 * @param within_time_interval
 *   Window of time (in microseconds) to join on
 * @returns
 *   DB_NOERROR on success, negative number on failure
 * 
 *  * This function joins the row entries from the stream nodes defined in @a input_list according the keys defined in the @a join_source_count 
 *   and within the time interval defined by @a within_time_interval.
 */
dbstatus_t db_stream_create_join_all_within(db_stream_node_t * output, db_stream_node_t * input_list, db_fieldno_t * join_key_list, int32_t join_source_count, int64_t within_time_interval);
/** @} */

C_HEADER_END

#endif // DB_STREAM_H
