#ifndef TYPE_ID_HPP
#define TYPE_ID_HPP

#include <cstddef> // for size_t

typedef std::size_t type_id;

template <typename T, typename TypeIdGenerator>
type_id get_type_id(TypeIdGenerator generator)
{
    static const type_id id = generator.template generate<T>();
    return id;
}

#endif // TYPE_ID_HPP
