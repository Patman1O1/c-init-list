#ifndef INIT_LIST_H
#define INIT_LIST_H

#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#define init_list_create(type, array_size, ...) ({                                \
    struct init_list __init_list;                                                 \
    __init_list.size = array_size;                                                \
    __init_list.values_p = (void*)calloc(__init_list.size, sizeof(type));         \
    if (__init_list.values_p == NULL) {                                           \
        exit(errno);                                                              \
    }                                                                             \
                                                                                  \
    if (__init_list.size > 0) {                                                   \
        type __values[] = {__VA_ARGS__};                                          \
        const size_t __values_size = sizeof(__values) / sizeof(__values[0]);      \
        if (__values_size <= __init_list.size && __values_size > 0) {             \
            memcpy(__init_list.values_p, __values, sizeof(type) * __values_size); \
        } else {                                                                  \
            free(__init_list.values_p);                                           \
            errno = E2BIG;                                                        \
            __init_list.values_p = NULL;                                          \
        }                                                                         \
    } else {                                                                      \
        __init_list.values_p = NULL;                                              \
    }                                                                             \
    __init_list;                                                                  \
})


#define init_list_at(type, init_list, index) \
    (assert(init_list.values_p != nullptr),  \
     assert(index < init_list.size),         \
    ((type*)init_list.values_p)[index])      \

struct init_list {
    void* values_p;
    size_t size;
};

extern int init_list_cmp(const struct init_list* lhs_p, const struct init_list* rhs_p);

extern void init_list_free(struct init_list* init_list_p);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef INIT_LIST_H

