#ifndef DEFAULT_TYPE_ID_GENERATOR_HPP
#define DEFAULT_TYPE_ID_GENERATOR_HPP

#include "type_id.hpp"

namespace tac
{
    namespace detail
    {
        class default_type_id_generator
        {
        public:

            default_type_id_generator() : 
                m_nextTypeId(0) 
            {
            }

            template <typename T>
            type_id generate()
            {
                return m_nextTypeId++;
            }

            type_id last_id_given()
            {
                return m_nextTypeId - 1;
            }

        private:

            type_id m_nextTypeId;
        };

    }
}


#endif // DEFAULT_TYPE_ID_GENERATOR_HPP
