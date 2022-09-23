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

/* @file
 *
 * File I/O
 */

#ifndef OS_FILE_H
#define OS_FILE_H

/* file subsystem */
#include "ittia/os/os_config.h"

/* for OS_MAX_PATH */
#include "ittia/os/std/io.h"
#include "ittia/os/std/windows.h"

#ifndef OS_MAX_PATH
#define OS_MAX_PATH OS_MAX_PATH_
#endif

/* open and create flags */

#define OS_FILE_READ       0x00001  /* open file for read access */
#define OS_FILE_WRITE      0x00002  /* open file for write access */

#define OS_FILE_CREATE     0x00008  /* create file if not exists, or open existing */
#define OS_FILE_TRUNCATE   0x00010  /* truncate file to zero length */
#define OS_FILE_NEW        0x00020  /* create file if not exists fail otherwise when used with OS_FILE_CREATE */

#define OS_FILE_BINARY     0x00040  /* open file in binary mode, implicit for OS_FILE_BLOCK */

#define OS_FILE_BLOCK      0x00100  /* optimize file for block access */
#define OS_FILE_NOCACHE    0x00200  /* disable os caching on file, used with OS_FILE_BLOCK */
#define OS_FILE_TEMPORARY  0x00400  /* delete file after closing */
#define OS_FILE_THREAD     0x00800  /* enable thread safe file access */
#define OS_FILE_UTF8_NAME  0x04000  /* file name is in UTF-8 encoding */
#define OS_FILE_CRASHFS    0x08000  /* enable crashfs file interface wrapper */

/* lock flags */
#define OS_LOCK_NONE       0x00000
#define _OS_LOCK_READ      0x01000  /* another process cannot read */
#define _OS_LOCK_WRITE     0x02000  /* another process cannot write */

#define OS_LOCK_EXCL       (_OS_LOCK_READ | _OS_LOCK_WRITE)
#define OS_LOCK_SHARE      (_OS_LOCK_WRITE)
#define OS_LOCK_MASK       (_OS_LOCK_READ | _OS_LOCK_WRITE)

/* file system tag */
#define OS_FILE_FS_MASK    0xF0000  /* mask for supported file systems */

/* file system tags */
#define OS_FILE_DEFFS      0x00000
#define OS_FILE_WIN32      0x10000
#define OS_FILE_POSIX      0x20000
#define OS_FILE_YAFFS      0x30000
#define OS_FILE_UCFS       0x40000
#define OS_FILE_RAMFS      0x50000
#define OS_FILE_STDIO      0x60000
#define OS_FILE_FILEX      0x70000
#define OS_FILE_FATFS      0x80000
/* HAVE_EXAMPLE_FILE: Add new file interface tags above this line. */
#define OS_FILE_EXAMPLE    0xF0000

/* os_full_path flags */
#define OS_FULL_PATH_UTF8       1   /* file name is in UTF-8 */
#define OS_FULL_PATH_IDENTITY   2   /* create identity name */

C_HEADER_BEGIN

/* declare file type */
typedef struct os_file_s * os_file_t;

/* declare functions */

/* block random access file */
DBDLL_API os_file_t os_file_open(const db_fname_t *, uint32_t flags );
DBDLL_API int os_file_close(os_file_t);

DBDLL_API int os_file_flush(os_file_t);

/* read and write blocks from file, used with OS_FILE_BLOCK */
DBDLL_API int os_file_bread(os_file_t, db_off_t off, void *, db_ssize_t size);

#define OS_WRITE_LAZY   10000 /* allow information to be maintained in os cache */
#define OS_WRITE_DIRECT 10001 /* force block to be written to disk */
DBDLL_API int os_file_bwrite(os_file_t, db_off_t off, const void * buf, db_ssize_t size, uint32_t fflags);

/* stream file seek/read/write, whese are not guaranteed to work correctly
 * when file os opened with OS_FILE_BLOCK
 */
/* seek */
#define OS_SEEK_SET 0
#define OS_SEEK_CUR 1
#define OS_SEEK_END 2

DBDLL_API int os_file_seek(os_file_t, db_off_t off, int orig);
DBDLL_API int os_file_read(os_file_t, void *, db_ssize_t size);
DBDLL_API int os_file_write(os_file_t, const void * buf, db_ssize_t size);

/* change size of file */
DBDLL_API int os_file_chsize(os_file_t, db_off_t size);

/* lock or unlock portion of file, see OS_LOCK_* */
DBDLL_API int os_file_lock(os_file_t, db_off_t off, db_off_t size, uint32_t);

/* retrieve file size */
DBDLL_API db_off_t os_file_size(os_file_t);
/* current file position */
DBDLL_API db_off_t os_file_tell(os_file_t);

/* perform the best possible checking if two files refer the same entity,
 * return value:
 * < 0 - error
 * = 0 - files are not equal
 * > 0 - files are equal
 */
DBDLL_API int os_file_equal(os_file_t, os_file_t);

/* find out uniform path to the src_file and fill the buffer (buffer allocated by db_malloc) */
DBDLL_API int os_full_path(const db_fname_t * src_file,
                           db_fname_t * buf,
                           int buf_len,
                           int flags);

/* compare two file pathes */
DBDLL_API int os_pathcmp(const db_fname_t *, const db_fname_t *);
DBDLL_API int os_pathlen(const db_fname_t *);

/*
 * copy no more than dest_len - 1 characters into dest, appending terminating
 * zero.
 * returns number of characters copied, without terminating zero
 */
DBDLL_API int os_pathcpy(db_fname_t * dest, int dest_len, const db_fname_t *);

/* rename file */

DBDLL_API int os_file_rename(const db_fname_t * cur_name, const db_fname_t * new_name);

/* remove file */
DBDLL_API int os_file_remove(const db_fname_t *);

/* check if file exist */
DBDLL_API int os_file_exist(const db_fname_t *);

/* remove files by mask */
DBDLL_API int os_file_remove_mask(const db_fname_t *);

#ifdef DB_ENABLE_TIME_STATISTICS
extern uint64_t elapsed_time_read;
extern uint64_t elapsed_time_write;
#endif

C_HEADER_END

#endif /* OS_FILE_H */
