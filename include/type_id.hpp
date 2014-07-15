#ifndef TYPE_ID_HPP
#define TYPE_ID_HPP

#include <cstddef> // for size_t

typedef std::size_t type_id;

template <typename TypeIdGenerator, typename T>
type_id get_type_id()
{
    static const type_id id = TypeIdGenerator<T>();
    return id;
}

#endif // TYPE_ID_HPP
