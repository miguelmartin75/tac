#ifndef DEFAULT_TYPE_ID_GENERATOR_HPP
#define DEFAULT_TYPE_ID_GENERATOR_HPP

#include "type_id.hpp"

class default_type_id_generator
{
public:

    template <typename T>
    type_id operator()()
    {
        return m_nextTypeId++;
    }

    static type_id m_nextTypeId;
};

type_id default_type_id_generator::m_nextTypeId = 0;



#endif // DEFAULT_TYPE_ID_GENERATOR_HPP
