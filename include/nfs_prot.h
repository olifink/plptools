#ifndef _nfs_prot_h_
#define _nfs_prot_h_

#include "fparam.h"

#ifdef hpux
#include <sys/time.h>
#include <nfs/nfs.h>
#endif
#ifdef linux
# include <sys/time.h>
# include <linux/nfs.h>
#endif
#ifdef __sgi
# include <rpc/types.h>
# include <sys/fs/nfs.h>
# include <sys/fs/nfs_clnt.h>
#endif

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <rpc/types.h>

#define NFS_PORT 2049
#define NFS_MAXDATA 8192
#define NFS_MAXPATHLEN 1024
#define NFS_MAXNAMLEN 255
#define NFS_FHSIZE 32
#define NFS_COOKIESIZE 4
#ifndef NFS_FIFO_DEV
#define NFS_FIFO_DEV -1
#endif
#define NFSMODE_FMT 0170000
#define NFSMODE_DIR 0040000
#define NFSMODE_CHR 0020000
#define NFSMODE_BLK 0060000
#define NFSMODE_REG 0100000
#define NFSMODE_LNK 0120000
#define NFSMODE_SOCK 0140000
#define NFSMODE_FIFO 0010000

#if !defined(hpux) && !defined(linux) && !defined(__sgi)
enum nfsstat {
	NFS_OK = 0,
	NFSERR_PERM = 1,
	NFSERR_NOENT = 2,
	NFSERR_IO = 5,
	NFSERR_NXIO = 6,
	NFSERR_ACCES = 13,
	NFSERR_EXIST = 17,
	NFSERR_NODEV = 19,
	NFSERR_NOTDIR = 20,
	NFSERR_ISDIR = 21,
	NFSERR_FBIG = 27,
	NFSERR_NOSPC = 28,
	NFSERR_ROFS = 30,
	NFSERR_NAMETOOLONG = 63,
	NFSERR_NOTEMPTY = 66,
	NFSERR_DQUOT = 69,
	NFSERR_STALE = 70,
	NFSERR_WFLUSH = 99
};
#endif /* !hpux, linux */

#ifdef linux
typedef enum nfs_stat nfsstat;
#else
typedef enum nfsstat nfsstat;
#endif
bool_t xdr_nfsstat();

#if !defined(hpux) && !defined(linux) && !defined(__sgi)
enum ftype {
	NFNON = 0,
	NFREG = 1,
	NFDIR = 2,
	NFBLK = 3,
	NFCHR = 4,
	NFLNK = 5,
	NFSOCK = 6,
	NFBAD = 7,
	NFFIFO = 8
};
typedef enum ftype ftype;
#endif /* !linux, hpux */

#ifdef __sgi
typedef enum nfsftype ftype;
#endif

#ifdef hpux
typedef enum nfsftype ftype;
#endif
#ifdef linux
typedef enum nfs_ftype ftype;
#endif

bool_t xdr_ftype();

#ifndef linux
struct nfs_fh {
	char data[NFS_FHSIZE];
};
#endif
typedef struct nfs_fh nfs_fh;
bool_t xdr_nfs_fh();

struct nfstime {
	u_int seconds;
	u_int useconds;
};
typedef struct nfstime nfstime;
bool_t xdr_nfstime();

struct fattr {
	ftype type;
	u_int mode;
	u_int nlink;
	u_int uid;
	u_int gid;
	u_int size;
	u_int blocksize;
	u_int rdev;
	u_int blocks;
	u_int fsid;
	u_int fileid;
	nfstime atime;
	nfstime mtime;
	nfstime ctime;
};
typedef struct fattr fattr;
bool_t xdr_fattr();

struct sattr {
	u_int mode;
	u_int uid;
	u_int gid;
	u_int size;
	nfstime atime;
	nfstime mtime;
};
typedef struct sattr sattr;
bool_t xdr_sattr();

typedef char *filename;
bool_t xdr_filename();

typedef char *nfspath;
bool_t xdr_nfspath();

struct attrstat {
	nfsstat status;
	union {
		fattr attributes;
	} attrstat_u;
};
typedef struct attrstat attrstat;
bool_t xdr_attrstat();

struct sattrargs {
	nfs_fh file;
	sattr attributes;
};
typedef struct sattrargs sattrargs;
bool_t xdr_sattrargs();

struct diropargs {
	nfs_fh dir;
	filename name;
};
typedef struct diropargs diropargs;
bool_t xdr_diropargs();

struct diropokres {
	nfs_fh file;
	fattr attributes;
};
typedef struct diropokres diropokres;
bool_t xdr_diropokres();

struct diropres {
	nfsstat status;
	union {
		diropokres diropres;
	} diropres_u;
};
typedef struct diropres diropres;
bool_t xdr_diropres();

struct readlinkres {
	nfsstat status;
	union {
		nfspath data;
	} readlinkres_u;
};
typedef struct readlinkres readlinkres;
bool_t xdr_readlinkres();

struct readargs {
	nfs_fh file;
	u_int offset;
	u_int count;
	u_int totalcount;
};
typedef struct readargs readargs;
bool_t xdr_readargs();

struct readokres {
	fattr attributes;
	struct {
		u_int data_len;
		char *data_val;
	} data;
};
typedef struct readokres readokres;
bool_t xdr_readokres();

struct readres {
	nfsstat status;
	union {
		readokres reply;
	} readres_u;
};
typedef struct readres readres;
bool_t xdr_readres();

struct writeargs {
	nfs_fh file;
	u_int beginoffset;
	u_int offset;
	u_int totalcount;
	struct {
		u_int data_len;
		char *data_val;
	} data;
};
typedef struct writeargs writeargs;
bool_t xdr_writeargs();

struct createargs {
	diropargs where;
	sattr attributes;
};
typedef struct createargs createargs;
bool_t xdr_createargs();

struct renameargs {
	diropargs from;
	diropargs to;
};
typedef struct renameargs renameargs;
bool_t xdr_renameargs();

struct linkargs {
	nfs_fh from;
	diropargs to;
};
typedef struct linkargs linkargs;
bool_t xdr_linkargs();

struct symlinkargs {
	diropargs from;
	nfspath to;
	sattr attributes;
};
typedef struct symlinkargs symlinkargs;
bool_t xdr_symlinkargs();

typedef char nfscookie[NFS_COOKIESIZE];
bool_t xdr_nfscookie();

struct readdirargs {
	nfs_fh dir;
	nfscookie cookie;
	u_int count;
};
typedef struct readdirargs readdirargs;
bool_t xdr_readdirargs();

struct entry {
	u_int fileid;
	filename name;
	nfscookie cookie;
	struct entry *nextentry;
};
typedef struct entry entry;
bool_t xdr_entry();

struct dirlist {
	entry *entries;
	bool_t eof;
};
typedef struct dirlist dirlist;
bool_t xdr_dirlist();

struct readdirres {
	nfsstat status;
	union {
		dirlist reply;
	} readdirres_u;
};
typedef struct readdirres readdirres;
bool_t xdr_readdirres();

struct statfsokres {
	u_int tsize;
	u_int bsize;
	u_int blocks;
	u_int bfree;
	u_int bavail;
};
typedef struct statfsokres statfsokres;
bool_t xdr_statfsokres();

struct statfsres {
	nfsstat status;
	union {
		statfsokres reply;
	} statfsres_u;
};
typedef struct statfsres statfsres;
bool_t xdr_statfsres();

#ifndef NFS_PROGRAM
#define NFS_PROGRAM ((u_long)100003)
#endif
#ifndef  NFS_VERSION
#define NFS_VERSION ((u_long)2)
#endif
#ifndef  NFSPROC_NULL
#define NFSPROC_NULL ((u_long)0)
#endif
extern void *nfsproc_null_2 __P((void));
#ifndef  NFSPROC_GETATTR
#define NFSPROC_GETATTR ((u_long)1)
#endif
extern attrstat *nfsproc_getattr_2 __P((struct nfs_fh *fh));
#ifndef  NFSPROC_SETATTR
#define NFSPROC_SETATTR ((u_long)2)
#endif
extern attrstat *nfsproc_setattr_2 __P((struct sattrargs *sa));
#ifndef  NFSPROC_ROOT
#define NFSPROC_ROOT ((u_long)3)
#endif
extern void *nfsproc_root_2 __P((void));
#ifndef  NFSPROC_LOOKUP
#define NFSPROC_LOOKUP ((u_long)4)
#endif
extern diropres *nfsproc_lookup_2 __P((struct diropargs *da));
#ifndef  NFSPROC_READLINK
#define NFSPROC_READLINK ((u_long)5)
#endif
extern readlinkres *nfsproc_readlink_2 __P((struct nfs_fh *fh));
#ifndef  NFSPROC_READ
#define NFSPROC_READ ((u_long)6)
#endif
extern readres *nfsproc_read_2 __P((struct readargs *ra));
#ifndef  NFSPROC_WRITECACHE
#define NFSPROC_WRITECACHE ((u_long)7)
#endif
extern void *nfsproc_writecache_2 __P((void));
#ifndef  NFSPROC_WRITE
#define NFSPROC_WRITE ((u_long)8)
#endif
extern attrstat *nfsproc_write_2 __P((struct writeargs *wa));
#ifndef  NFSPROC_CREATE
#define NFSPROC_CREATE ((u_long)9)
#endif
extern diropres *nfsproc_create_2 __P((struct createargs *ca));
#ifndef  NFSPROC_REMOVE
#define NFSPROC_REMOVE ((u_long)10)
#endif
extern nfsstat *nfsproc_remove_2 __P((struct diropargs *da));
#ifndef  NFSPROC_RENAME
#define NFSPROC_RENAME ((u_long)11)
#endif
extern nfsstat *nfsproc_rename_2 __P((struct renameargs *ra));
#ifndef  NFSPROC_LINK
#define NFSPROC_LINK ((u_long)12)
#endif
extern nfsstat *nfsproc_link_2 __P((struct linkargs *la));
#ifndef  NFSPROC_SYMLINK
#define NFSPROC_SYMLINK ((u_long)13)
#endif
extern nfsstat *nfsproc_symlink_2 __P((struct symlinkargs *sa));
#ifndef  NFSPROC_MKDIR
#define NFSPROC_MKDIR ((u_long)14)
#endif
extern diropres *nfsproc_mkdir_2 __P((struct createargs *ca));
#ifndef  NFSPROC_RMDIR
#define NFSPROC_RMDIR ((u_long)15)
#endif
extern nfsstat *nfsproc_rmdir_2 __P((struct diropargs *da));
#ifndef  NFSPROC_READDIR
#define NFSPROC_READDIR ((u_long)16)
#endif
extern readdirres *nfsproc_readdir_2 __P((struct readdirargs *ra));
#ifndef  NFSPROC_STATFS
#define NFSPROC_STATFS ((u_long)17)
#endif
extern statfsres *nfsproc_statfs_2 __P((struct nfs_fh *fh));

#endif
