/* Generated automatically from ./Modules/config.c.in by makesetup. */
/* -*- C -*- ***********************************************
Copyright (c) 2000, BeOpen.com.
Copyright (c) 1995-2000, Corporation for National Research Initiatives.
Copyright (c) 1990-1995, Stichting Mathematisch Centrum.
All rights reserved.

See the file "Misc/COPYRIGHT" for information on usage and
redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
******************************************************************/

/* Module configuration */

/* !!! !!! !!! This file is edited by the makesetup script !!! !!! !!! */

/* This file contains the table of built-in modules.
   See create_builtin() in import.c. */

#include "Python.h"

#ifdef __cplusplus
extern "C" {
#endif


extern PyObject* PyInit_atexit(void);
extern PyObject* PyInit_faulthandler(void);
extern PyObject* PyInit_posix(void);
extern PyObject* PyInit__signal(void);
extern PyObject* PyInit__tracemalloc(void);
extern PyObject* PyInit__codecs(void);
extern PyObject* PyInit__collections(void);
extern PyObject* PyInit_errno(void);
extern PyObject* PyInit__io(void);
extern PyObject* PyInit_itertools(void);
extern PyObject* PyInit__sre(void);
extern PyObject* PyInit__thread(void);
extern PyObject* PyInit_time(void);
extern PyObject* PyInit__weakref(void);
extern PyObject* PyInit__abc(void);
extern PyObject* PyInit__functools(void);
extern PyObject* PyInit__locale(void);
extern PyObject* PyInit__operator(void);
extern PyObject* PyInit__stat(void);
extern PyObject* PyInit__symtable(void);
extern PyObject* PyInit_pwd(void);
extern PyObject* PyInit__asyncio(void);
extern PyObject* PyInit__bisect(void);
extern PyObject* PyInit__contextvars(void);
extern PyObject* PyInit__csv(void);
extern PyObject* PyInit__datetime(void);
extern PyObject* PyInit__decimal(void);
extern PyObject* PyInit__heapq(void);
extern PyObject* PyInit__json(void);
extern PyObject* PyInit__lsprof(void);
extern PyObject* PyInit__multiprocessing(void);
extern PyObject* PyInit__opcode(void);
extern PyObject* PyInit__pickle(void);
extern PyObject* PyInit__queue(void);
extern PyObject* PyInit__random(void);
extern PyObject* PyInit__socket(void);
extern PyObject* PyInit__statistics(void);
extern PyObject* PyInit__struct(void);
extern PyObject* PyInit__typing(void);
extern PyObject* PyInit__zoneinfo(void);
extern PyObject* PyInit_array(void);
extern PyObject* PyInit_audioop(void);
extern PyObject* PyInit_binascii(void);
extern PyObject* PyInit_cmath(void);
extern PyObject* PyInit_math(void);
extern PyObject* PyInit_mmap(void);
extern PyObject* PyInit_select(void);
extern PyObject* PyInit__elementtree(void);
extern PyObject* PyInit_pyexpat(void);
extern PyObject* PyInit__blake2(void);
extern PyObject* PyInit__md5(void);
extern PyObject* PyInit__sha1(void);
extern PyObject* PyInit__sha256(void);
extern PyObject* PyInit__sha512(void);
extern PyObject* PyInit__sha3(void);
extern PyObject* PyInit__codecs_cn(void);
extern PyObject* PyInit__codecs_hk(void);
extern PyObject* PyInit__codecs_iso2022(void);
extern PyObject* PyInit__codecs_jp(void);
extern PyObject* PyInit__codecs_kr(void);
extern PyObject* PyInit__codecs_tw(void);
extern PyObject* PyInit__multibytecodec(void);
extern PyObject* PyInit_unicodedata(void);
extern PyObject* PyInit__posixsubprocess(void);
extern PyObject* PyInit__posixshmem(void);
extern PyObject* PyInit_fcntl(void);
extern PyObject* PyInit_grp(void);
extern PyObject* PyInit_ossaudiodev(void);
extern PyObject* PyInit_resource(void);
extern PyObject* PyInit_spwd(void);
extern PyObject* PyInit_syslog(void);
extern PyObject* PyInit_termios(void);
extern PyObject* PyInit__crypt(void);
extern PyObject* PyInit__bz2(void);
extern PyObject* PyInit__ctypes(void);
extern PyObject* PyInit__lzma(void);
extern PyObject* PyInit_zlib(void);
extern PyObject* PyInit_readline(void);
extern PyObject* PyInit__ssl(void);
extern PyObject* PyInit__hashlib(void);
extern PyObject* PyInit_xxsubtype(void);

/* -- ADDMODULE MARKER 1 -- */

extern PyObject* PyMarshal_Init(void);
extern PyObject* PyInit__imp(void);
extern PyObject* PyInit_gc(void);
extern PyObject* PyInit__ast(void);
extern PyObject* PyInit__tokenize(void);
extern PyObject* _PyWarnings_Init(void);
extern PyObject* PyInit__string(void);

struct _inittab _PyImport_Inittab[] = {

    {"atexit", PyInit_atexit},
    {"faulthandler", PyInit_faulthandler},
    {"posix", PyInit_posix},
    {"_signal", PyInit__signal},
    {"_tracemalloc", PyInit__tracemalloc},
    {"_codecs", PyInit__codecs},
    {"_collections", PyInit__collections},
    {"errno", PyInit_errno},
    {"_io", PyInit__io},
    {"itertools", PyInit_itertools},
    {"_sre", PyInit__sre},
    {"_thread", PyInit__thread},
    {"time", PyInit_time},
    {"_weakref", PyInit__weakref},
    {"_abc", PyInit__abc},
    {"_functools", PyInit__functools},
    {"_locale", PyInit__locale},
    {"_operator", PyInit__operator},
    {"_stat", PyInit__stat},
    {"_symtable", PyInit__symtable},
    {"pwd", PyInit_pwd},
    {"_asyncio", PyInit__asyncio},
    {"_bisect", PyInit__bisect},
    {"_contextvars", PyInit__contextvars},
    {"_csv", PyInit__csv},
    {"_datetime", PyInit__datetime},
    {"_decimal", PyInit__decimal},
    {"_heapq", PyInit__heapq},
    {"_json", PyInit__json},
    {"_lsprof", PyInit__lsprof},
    {"_multiprocessing", PyInit__multiprocessing},
    {"_opcode", PyInit__opcode},
    {"_pickle", PyInit__pickle},
    {"_queue", PyInit__queue},
    {"_random", PyInit__random},
    {"_socket", PyInit__socket},
    {"_statistics", PyInit__statistics},
    {"_struct", PyInit__struct},
    {"_typing", PyInit__typing},
    {"_zoneinfo", PyInit__zoneinfo},
    {"array", PyInit_array},
    {"audioop", PyInit_audioop},
    {"binascii", PyInit_binascii},
    {"cmath", PyInit_cmath},
    {"math", PyInit_math},
    {"mmap", PyInit_mmap},
    {"select", PyInit_select},
    {"_elementtree", PyInit__elementtree},
    {"pyexpat", PyInit_pyexpat},
    {"_blake2", PyInit__blake2},
    {"_md5", PyInit__md5},
    {"_sha1", PyInit__sha1},
    {"_sha256", PyInit__sha256},
    {"_sha512", PyInit__sha512},
    {"_sha3", PyInit__sha3},
    {"_codecs_cn", PyInit__codecs_cn},
    {"_codecs_hk", PyInit__codecs_hk},
    {"_codecs_iso2022", PyInit__codecs_iso2022},
    {"_codecs_jp", PyInit__codecs_jp},
    {"_codecs_kr", PyInit__codecs_kr},
    {"_codecs_tw", PyInit__codecs_tw},
    {"_multibytecodec", PyInit__multibytecodec},
    {"unicodedata", PyInit_unicodedata},
    {"_posixsubprocess", PyInit__posixsubprocess},
    {"_posixshmem", PyInit__posixshmem},
    {"fcntl", PyInit_fcntl},
    {"grp", PyInit_grp},
    {"ossaudiodev", PyInit_ossaudiodev},
    {"resource", PyInit_resource},
    {"spwd", PyInit_spwd},
    {"syslog", PyInit_syslog},
    {"termios", PyInit_termios},
    {"_crypt", PyInit__crypt},
    {"_bz2", PyInit__bz2},
    {"_ctypes", PyInit__ctypes},
    {"_lzma", PyInit__lzma},
    {"zlib", PyInit_zlib},
    {"readline", PyInit_readline},
    {"_ssl", PyInit__ssl},
    {"_hashlib", PyInit__hashlib},
    {"xxsubtype", PyInit_xxsubtype},

/* -- ADDMODULE MARKER 2 -- */

    /* This module lives in marshal.c */
    {"marshal", PyMarshal_Init},

    /* This lives in import.c */
    {"_imp", PyInit__imp},

    /* This lives in Python/Python-ast.c */
    {"_ast", PyInit__ast},

    /* This lives in Python/Python-tokenizer.c */
    {"_tokenize", PyInit__tokenize},

    /* These entries are here for sys.builtin_module_names */
    {"builtins", NULL},
    {"sys", NULL},

    /* This lives in gcmodule.c */
    {"gc", PyInit_gc},

    /* This lives in _warnings.c */
    {"_warnings", _PyWarnings_Init},

    /* This lives in Objects/unicodeobject.c */
    {"_string", PyInit__string},

    /* Sentinel */
    {0, 0}
};


#ifdef __cplusplus
}
#endif
