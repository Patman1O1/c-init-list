#include <string.h>

#include <init-list/init_list.h>

#ifdef __cplusplus
extern "C" {
#endif

int init_list_cmp(const struct init_list* lhs_p, const struct init_list* rhs_p) {
    if (lhs_p == nullptr || rhs_p == nullptr) {
        errno = EFAULT;
        return errno;
    }

    if (lhs_p->size > rhs_p->size) {
        return 1;
    }

    if (lhs_p->size < rhs_p->size) {
        return -1;
    }

    return memcmp(lhs_p->values_p, rhs_p->values_p, lhs_p->size);
}

void init_list_free(struct init_list* init_list_p)  {
    if (init_list_p == nullptr) {
        errno = EFAULT;
        return;
    }

    free(init_list_p->values_p);
    init_list_p->values_p = nullptr;
    init_list_p->size = 0;
}

#ifdef __cplusplus
}
#endif
