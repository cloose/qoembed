#ifndef QOEMBED_GLOBAL_H
#define QOEMBED_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QOEMBED_LIBRARY)
#  define QOEMBEDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QOEMBEDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QOEMBED_GLOBAL_H
