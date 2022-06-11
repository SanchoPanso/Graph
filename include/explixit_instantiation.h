#ifndef GRAPH_EXPLIXIT_INSTANTIATION_H
#define GRAPH_EXPLIXIT_INSTANTIATION_H

#include <cstdint>

#define EXPLICIT_INSTANTIATION(CLASSNAME)   \
    template class CLASSNAME<int8_t>;       \
    template class CLASSNAME<int16_t>;      \
    template class CLASSNAME<int32_t>;      \
    template class CLASSNAME<int64_t>;      \
                                            \
    template class CLASSNAME<float>;        \
    template class CLASSNAME<double>;       \

#endif
