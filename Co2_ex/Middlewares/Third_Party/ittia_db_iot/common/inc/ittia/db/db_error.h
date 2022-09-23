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


/* Do not edit! This file generated automatically from tools/errors. */

/** @file db_error.h
 *
 * Error handling mechanism
 */

#ifndef DB_ERROR_H
#define DB_ERROR_H

#include "ittia/os/os_error.h"

/** @addtogroup Errors
 * @{ */

/** @name  General Errors */
 /** @{ */
#define DB_INCOMPLETE                     +113 /**< Operation did not finish completely. */
#define DB_EDUPLICATE                     -100 /**< Duplicate value not allowed. */
#define DB_ENOTFOUND                      -101 /**< Item not found. */
#define DB_ENOMOREDATA                    -102 /**< No more data. */
#define DB_EKEYOUTOFRANGE                 -103 /**< Key out of range. */
#define DB_EEMPTYRANGE                    -104 /**< An attempt was made to set an empty range. */
#define DB_EBTREESLOTTOOLARGE             -105 /**< An attempt was made to insert into a B+tree a key and data that is too large. */
#define DB_ENEEDREVALIDATE                -106 /**< B+tree iterator needs revalidation. */
#define DB_ENORECORD                      -107 /**< No record found. */
#define DB_ENAME                          -109 /**< Invalid name. */
#define DB_EROWRANGE                      -110 /**< Too many records in a table. */
#define DB_ESHUTDOWN                      -111 /**< Shutdown is in progress. */
#define DB_ECONNLOCK                      -112 /**< Connection is used by another thread. */
#define DB_ECURSORMODE                    -114 /**< Invald or unsupported cursor mode. */
#define DB_ECIPHER                        -115 /**< Invalid cipher type. */
#define DB_ECIPHERDATA                    -116 /**< Invalid cipher data. */
/** @} */

/** @name  Table Errors */
 /** @{ */
#define DB_ETABLE                         -120 /**< General table error. */
#define DB_ETABLETYPE                     -121 /**< Unknown table type. */
#define DB_ENOTABLE                       -122 /**< No such table. */
#define DB_ENOMEMSTORAGE                  -123 /**< Memory storage is not open, memory_storage_size is 0. */
#define DB_ENOCONSTRAINT                  -125 /**< No such constraint defined. */
#define DB_ETABLEEXISTS                   -126 /**< Table already exists. */
/** @} */

/** @name  Index Errors */
 /** @{ */
#define DB_EINDEX                         -130 /**< General index error. */
#define DB_EPRIMARYDUP                    -131 /**< Multiple primary keys defined. */
#define DB_EFKREFERENCE                   -132 /**< Referenced row not found. */
#define DB_EFKRESTRICTED                  -133 /**< Operation is restricted due to references. */
#define DB_EFKMATCHFULL                   -134 /**< Operation is restricted due to incomplete full row match. */
#define DB_EFKEYDEF                       -135 /**< Invalid foreign key definition. */
#define DB_EFKLIMIT                       -136 /**< Too many cascade operations. */
#define DB_ECLUSTERKEY                    -137 /**< Invalid cluster key. */
/** @} */

/** @name  Field Errors */
 /** @{ */
#define DB_EFIELD                         -140 /**< General field error. */
#define DB_EDUPLICATEFIELDS               -141 /**< Cannot create duplicate fields. */
#define DB_EFIELDSIZE                     -142 /**< Invalid field size. */
#define DB_EBINDSIZE                      -143 /**< Invalid bind size. */
#define DB_EPARAM                         -144 /**< Invalid parameter. */
#define DB_EINDVALUE                      -145 /**< Length indicator value exceeds buffer size or is an invalid negative number. */
#define DB_ENULLFIELD                     -146 /**< Insert or update would violate a NOT NULL constraint, or primary key must be NOT NULL. */
#define DB_EFIELDTYPE                     -147 /**< Invalid field type. */
#define DB_EBLOB                          -148 /**< Invalid blob operation. */
/** @} */

/** @name  Sequence Errors */
 /** @{ */
#define DB_ESEQ                           -150 /**< General sequence error. */
#define DB_ESEQ_OVERFLOW                  -151 /**< Sequence overflow: no unique values remain. */
#define DB_ESEQ_NOCURVAL                  -152 /**< Sequence does not yet have a current value, get the next value first. */
/** @} */

/** @name  Row Errors */
 /** @{ */
#define DB_EINVALROWTYPE                  -160 /**< Invalid row type. */
#define DB_EINVALKEYTYPE                  -161 /**< Invalid key type. */
#define DB_EKEYTOOSHORT                   -162 /**< Key is too short. */
#define DB_ERECORDSIZE                    -163 /**< Record size is too large for chosen page size. */
/** @} */

/** @name  Data Errors */
 /** @{ */
#define DB_EBOOKMARK                      -167 /**< Bookmark is not valid. */
#define DB_EINVALIDINTERVAL               -168 /**< Invalid INTERVAL type literal. */
#define DB_ECURSOR                        -169 /**< Invalid cursor for the given operation. */
#define DB_EDATA                          -170 /**< Invalid field data value. */
#define DB_ECONVERT                       -171 /**< Incompatible types: conversion is not possible. */
/** @} */

/** @name  Kernel Errors */
 /** @{ */
#define DB_ENOBUFFER                      -172 /**< No available buffers. */
/** @} */

/** @name  Data Errors */
 /** @{ */
#define DB_EINVTYPE                       -173 /**< Invalid column/var type. */
/** @} */

/** @name  Kernel Errors */
 /** @{ */
#define DB_ESTORAGE                       -174 /**< Storage not recognized as a valid database. */
#define DB_ECRC                           -175 /**< CRC verification failed: database integrity has been compromised. */
#define DB_ERECOVERY                      -176 /**< Storage needs crash recovery. */
#define DB_EUNDOSPACE                     -177 /**< Overflow in undo log space, unable to write entries required for rollback. */
#define DB_EJOURNALTYPE                   -178 /**< Invalid journal type. */
#define DB_EJOURNAL                       -179 /**< Invalid journal or missing log file. */
#define DB_EJOURNALCRC                    -180 /**< Journal CRC validation failed. */
#define DB_EPREPARED                      -181 /**< Prepared transactions support is required to complete operation. */
#define DB_ENOJOURNALREC                  -182 /**< Requested journal record not found. */
#define DB_EINVPAGE                       -183 /**< Invalid page number. */
#define DB_EREADONLY                      -184 /**< Storage is in the read only mode. */
#define DB_ENOPAGESPACE                   -185 /**< Storage run out of disk space. */
#define DB_EPASSWORD                      -186 /**< Access password is not valid or access is denied. */
#define DB_EJOURNALWRITE                  -187 /**< Unable to write journal file. */
#define DB_EINCOMPATIBLE                  -188 /**< Incompatible storage format. */
/** @} */

/** @name  Transaction Errors */
 /** @{ */
#define DB_ENOTX                          -190 /**< No transaction is active. */
#define DB_ETXSTATE                       -191 /**< The operation cannot be performed in the current transaction state. */
#define DB_ETXACTIVE                      -192 /**< Transaction is already running. */
#define DB_ESAVEPOINTEXIST                -193 /**< Savepoint already exists. */
#define DB_ENOSAVEPOINT                   -194 /**< Specified savepoint does not exist. */
#define DB_ETXKIND                        -195 /**< Operation cannot be performed for such transaction type (for example, local commit cannot be done on prepared transaction). */
#define DB_EDTMXID                        -196 /**< Invalid DTM xid provided. */
#define DB_EBADTX                         -197 /**< Transaction cannot continue and must abort. */
/** @} */

/** @name  Shared Access Errors */
 /** @{ */
#define DB_ENOLOCK                        -200 /**< There are no available lock cells. */
#define DB_EMAXLOCKERS                    -201 /**< There are too many lockers. */
#define DB_EINVLOCK                       -202 /**< Unlock request for a lock that has not been obtained. */
#define DB_EWAITINTR                      -203 /**< Lock waiting interrupted. */
#define DB_ENOLOCKOBJ                     -204 /**< There are no available lock object cells. */
/** @} */

/** @name  Other Errors */
 /** @{ */
#define DB_EUSER                          -210 /**< User generated error. */
#define DB_EAPIVER                        -220 /**< API not initialized or feature not available in this version of the API. */
#define DB_EEVALUATION                    -250 /**< Operation not permitted in evaluation version. */
/** @} */

/** @name  IPC Client/Server Errors */
 /** @{ */
#define DB_EIPCPROTO                      -300 /**< No compatible protocol negotiated  . */
#define DB_EIPCINVAL                      -301 /**< Invalid parameter in IPC message. */
#define DB_EIPCINVALMESSAGETAG            -302 /**< Invalid parameter in IPC message. */
#define DB_EIPCINVALPROCTAG               -303 /**< Invalid procedure tag in IPC CALL message. */
#define DB_EIPCSTORAGEALREADYOPENED       -304 /**< Storage already opened. */
#define DB_EIPCSTORAGENOTOPENED           -305 /**< Storage not opened . */
#define DB_EIPCINVALHANDLE                -306 /**< Invalid object's handle. */
#define DB_EIPCNULLPARAM                  -307 /**< Complex parameter is NULL. */
#define DB_EIPCTOOFEWPARAMS               -308 /**< Too few parameters in message . */
#define DB_EIPCINVALMESSAGESIZE           -309 /**< Invalid message size. */
#define DB_EIPCINVALMESSAGEFORMAT         -310 /**< Invalid message format. */
#define DB_EIPCINVALURL                   -311 /**< Invalid URL format. */
#define DB_EIPCINVALURLSCHEMA             -312 /**< Invalid URL schema . */
#define DB_EIPCENVSTARTUP                 -313 /**< IPC environment startup error. */
#define DB_EIPCACCESS                     -314 /**< Disabled operations. */
#define DB_EIPCMAXCONNECTIONS             -315 /**< Maximum connections is reached  . */
#define DB_EIPCALREADYSTARTED             -316 /**< Server is already running. */
#define DB_EIPCNOLISTENER                 -317 /**< No listeners. */
#define DB_EIPCDISCONNECT                 -318 /**< Connection has been dropped. */
/** @} */

/** @name  SQL Statement Errors */
 /** @{ */
#define DB_ESQLCODESIZETOOLARGE           -400 /**< Generated code exceeds maximum code size. */
#define DB_ESQLTABLENOTEXISTS             -401 /**< Table does not exist. */
#define DB_ESQLINVALIDCOLUMNNAME          -402 /**< Invalid column name. */
#define DB_ESQLCOLUMNAMBIGUOUSLYDEFINED   -403 /**< Column ambiguously defined. */
#define DB_ESQLINCOMPATIBLETYPES          -404 /**< Incompatible types. */
#define DB_ESQLINVALIDFUNCTIONNAME        -405 /**< Invalid function name. */
#define DB_ESQLINVALIDNUMBEROFARGUMENTS   -406 /**< Invalid number of arguments. */
#define DB_ESQLININVALIDARGUMENTTYPE      -407 /**< Invalid argument type. */
/** @} */

/** @name  Data Errors */
 /** @{ */
#define DB_EINVALIDNUMBER                 -408 /**< Invalid number. */
/** @} */

/** @name  SQL Statement Errors */
 /** @{ */
#define DB_ESQLINVALIDQUALIFIER           -409 /**< Invalid qualifier. */
#define DB_ESQLINCOMPATIBLEROWTYPES       -410 /**< Incompatible row types. */
#define DB_ESQLPARSEERROR                 -411 /**< Error parsing SQL syntax. */
#define DB_ESQLNOTAGROUPBYEXPRESSION      -412 /**< Selected field is not a group-by expression. */
#define DB_ESQLFEATURENOTALLOWED          -413 /**< Feature not allowed. */
#define DB_ESQLDIVIDEBYZERO               -414 /**< Divide by zero. */
#define DB_ESQLTYPECVTNOTIMPLEMENTED      -415 /**< Cannot convert to incompatible type. */
#define DB_ESQLOPERATIONNOTIMPLEMENTED    -416 /**< Operation not implemented. */
#define DB_ESQLINVALIDRELATIONALOPERATOR  -417 /**< Invalid relation. */
#define DB_ESQLROWSIZETOOLARGE            -418 /**< Row size too large. */
#define DB_ESQLNOTSORTABLETYPE            -419 /**< Ordered by non-sortable type. */
#define DB_ESQLNOTENOUGHVALUES            -420 /**< Not enough values specified. */
#define DB_ESQLTOOMANYVALUES              -421 /**< Too many values specified. */
#define DB_ESQLBOOLEXPRESSIONINSELECTLIST -422 /**< Boolean expression in select list. */
#define DB_ESQLENV                        -423 /**< SQL environment error. */
#define DB_ESQLINCONSISTENTPARAMTYPE      -424 /**< Inconsistent parameter type. */
#define DB_ESQLCOULDNOTDEDUCEPARAMTYPE    -425 /**< Could not deduce parameter type from context. */
#define DB_ESQLINVALIDPARAMINDEX          -426 /**< Missing parameter value. */
#define DB_ESQLPARAMCONVERT               -427 /**< Could not convert parameter to required type. */
#define DB_ESQLMIXEDPARAMSTYLE            -428 /**< Mixed parameter style (? and $) not supported. */
#define DB_ESQLINVALIDCOLUMNINDEX         -429 /**< Invalid column number. */
#define DB_ESQLINVALIDSORTCOLUMN          -430 /**< Invalid column number in order by clause. */
#define DB_ESQLINVALIDEXPRTYPE            -431 /**< Invalid expression type, boolean may be expected. */
#define DB_ESQLBINARYLITERAL              -432 /**< Invalid BINARY type literal. */
#define DB_ESQLINVALIDEXTRACTFIELD        -433 /**< Invalid EXTRACT field. */
#define DB_ESQLTIMEOUT                    -499 /**< Timeout in SQL. */
/** @} */

/** @name  Replication Errors */
 /** @{ */
#define DB_EREP_PEERPATH                  -500 /**< Path to peer is unknown. */
#define DB_EREP_PEERADDRESS               -501 /**< Invalid or unset peer address. */
#define DB_EREP_ADDRESS                   -502 /**< Invalid or unset replication address. */
#define DB_EREP_INVADDRESS                -503 /**< The replication address of the other database does not match the expected peer address. */
#define DB_EREP_LOOPBACK                  -504 /**< Attempt to replicate with a database having the same address. */
#define DB_EREP_NOPEER                    -505 /**< Unknown replication peer. */
#define DB_EREP_CONFLICT                  -506 /**< Conflict when propagating to replication peer. */
#define DB_EREP_NOCONN                    -507 /**< Unable to open connection to replication peer. */
#define DB_EREP_BUFSIZE                   -508 /**< Buffer underflow during replication. */
#define DB_EREP_PEERTYPE                  -509 /**< Peer type is not valid. */
#define DB_EREP_INCONSISTENT              -510 /**< Inconsistent replication state, which often indicates that the same replication address was assigned to multiple databases. */
/** @} */

/** @name  Synchronization Errors */
 /** @{ */
#define DB_ESYNC_NODB                     -600 /**< No such database. */
#define DB_ESYNC_DUPLICATEDB              -601 /**< Duplicate databases are not allowed. */
#define DB_ESYNC_CONNECT                  -602 /**< Unable to connect to the sync database. */
/** @} */


/** @} */ /* group: Errors */

#endif /* DB_ERROR_H */
