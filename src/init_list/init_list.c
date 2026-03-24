#include <init_list/init_list.h>

void init_list_free(struct init_list* init_list_p)  {
    if (init_list_p == nullptr) {
        errno = EFAULT;
        return;
    }

    free(init_list_p->values_p);
    init_list_p->values_p = nullptr;
    init_list_p->size = 0;
}
