#ifndef TYPE_ALIGNED_CONTAINER_DYN_HPP
#define TYPE_ALIGNED_CONTAINER_DYN_HPP

#include <vector>
#include <memory>

#include "type_id.hpp"
#include "default_type_id_generator.hpp"

/// \brief A container that will align it's contents by type (dynamically).
/// 
/// The reason this is dynamic, is so that you do not have to specify the types
/// that this container stores; and therefore will be c++98 compatible.
/// 
/// \tparam TypeIdGenerator The type_id generator (defaults to default_type_id_generator)
/// \tparam AlignedContainer The container type (defaults to std::vector<T>)
template <typename TypeIdGenerator = default_type_id_generator, template<typename T> typename AlignedContainer = std::vector<T>>
class type_aligned_container_dyn
{
private:

    struct base_aligned_container
    {
        virtual ~base_aligned_alocator();
    };

    template <typename T>
    struct aligned_container : public base_aligned_alocator
    {
        AlignedContainer<T> container;
    };

public:

    template <typename T>
    using aligned_container = AlignedContainer;

    /// Adds 
    template <typename T>
    void add()
    {
        auto typeId = get_type_id(type_id_generator);
        // resize if we need to
        if(m_containers.size() <= typeId) 
        {
            m_containers.resize(typeId + 1);
        }

        m_containers[typeId].reset(new aligned_alocator<T>);
    }

    /// Retrieves all objects of type T within the container
    /// \tparam T The type of object you wish to retrieve
    /// \return An array of all of T within the container
    template <typename T>
    aligned_container<T>& all()
    {
        return *static_cast<array_type<T>*>(m_containers[get_type_id<T>()]);
    }

    template <typename T>
    const aligned_container<T>& all() const
    {
        return *static_cast<array_type<T>*>(m_containers[get_type_id<T>()]);
    }
    
    /// Clears the container
    void clear()
    {
        for(auto& c : m_containers)
        {
            if(c != nullptr)
            {
                c->clear();
            }
        }
    }

    template <typename T, typename F>
    void for_each(F f)
    {
        auto& c = all<T>();
        for(auto& i : c)
        {
            F(i);
        }
    }

private:

    ArrayType<base_aligned_container> m_containers;
};


#endif // TYPE_ALIGNED_CONTAINER_DYN_HPP
