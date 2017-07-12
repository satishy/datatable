#ifndef dt_COLUMN_H
#define dt_COLUMN_H
#include <inttypes.h>  // int*_t
#include <stddef.h>    // offsetof
#include "types.h"

typedef struct DataTable DataTable;
typedef struct RowMapping RowMapping;


//==============================================================================

/**
 * Single "data" column within a datatable.
 *
 * The `data` memory buffer is the raw storage of the column's data. The data
 * is stored in the "NFF" format, as described in the "types.h" file. Typically
 * it's just a plain array of primitive types, in which case the `j`-th element
 * can be accessed as `((ctype*)(column->data))[j]`. More complicated types
 * (such as strings) require a more elaborate access scheme.
 *
 * Parameters
 * ----------
 * data
 *     Raw data buffer in NFF format, depending on the column's `stype` (see
 *     specification in "types.h").
 *
 * mtype
 *     "Memory" type of the column -- i.e. where the data is actually stored.
 *     Possible values are MT_DATA (column is stored in RAM) and MT_MMAP
 *     (memory-mapped from disk).
 *
 * stype
 *     Type of data within the column (the enum is defined in types.h). This is
 *     the "storage" type, i.e. how the data is actually stored in memory. The
 *     logical type can be derived from `stype` via `stype_info[stype].ltype`.
 *
 * nrows
 *     Number of elements in this column. For fixed-size stypes, this should be
 *     equal to `alloc_size / stype_info[stype].elemsize`.
 *
 * meta
 *     Metadata associated with the column, if any, otherwise NULL. This is one
 *     of the *Meta structs defined in "types.h". The actual struct used
 *     depends on the `stype`.
 *
 * alloc_size
 *     Size (in bytes) of memory buffer `data`. For columns of type MT_MMAP this
 *     size is equal to the file size.
 *
 * refcount
 *     Number of references to this Column object. It is a common for a single
 *     Column to be reused across multiple DataTables (for example when a new
 *     DataTable is created as a view onto an existing one). In such case the
 *     refcount of the Column should be increased. Any modification to a Column
 *     with refcount > 1 is not allowed -- a copy should be made first. When a
 *     DataTable is deleted, it decreases refcounts of all its constituent
 *     Columns, and once a Column's refcount becomes 0 it can be safely deleted.
 */
typedef struct Column {
    void   *data;        // 8
    void   *meta;        // 8
    int64_t nrows;       // 8
    size_t  alloc_size;  // 8
    int     refcount;    // 4
    MType   mtype;       // 1
    SType   stype;       // 1
    int16_t _padding;    // 2
} Column;



//==============================================================================

Column* make_data_column(SType stype, size_t nrows);
Column* make_mmap_column(SType stype, size_t nrows, const char *filename);
Column* column_extract(Column *self, RowMapping *rowmapping);
RowMapping* column_sort(Column *self, int64_t nrows);
void column_incref(Column *self);
void column_decref(Column *self);


#endif
