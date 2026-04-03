#ifndef EXPORT_H
#define EXPORT_H

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#ifndef INIT_LIST_STATIC_DEFINE
#  include <init-list/export_shared.h>
#else
#  include <init-list/export_static.h>
#endif // #ifndef INIT_LIST_STATIC_DEFINE

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef EXPORT_H

