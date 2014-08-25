#ifndef TYPE_ALIGNED_CONTAINER_DYN_HPP
#define TYPE_ALIGNED_CONTAINER_DYN_HPP

#include <vector>
#include <utility>
#include <memory>

#include <tac/detail/type_id.hpp>
#include <tac/detail/default_type_id_generator.hpp>

template <typename T>
using default_aligned_container = std::vector<T>;

/// \brief A container that will align it's contents by type (dynamically).
/// 
/// The reason this is dynamic, is so that you do not have to specify the types
/// that this container stores; and therefore will be c++98 compatible.
/// 
/// \tparam TypeIdGenerator The type_id generator (defaults to default_type_id_generator)
/// \tparam AlignedContainer The container type (defaults to std::vector<T>)
template <typename TypeIdGenerator = default_type_id_generator, template<typename T> class AlignedContainer = default_aligned_container>
class type_aligned_container_dyn
{
private:

    struct base_aligned_container_impl
    {
        virtual ~base_aligned_container_impl() { }
    };

    template <typename T>
    struct aligned_container_impl : base_aligned_container_impl
    {
        virtual ~aligned_container_impl() { }
        AlignedContainer<T> container;
    };

public:

    template <typename T>
    using aligned_container = AlignedContainer<T>;

    /// Adds an object of type T
    template <typename T, typename... Args>
    void add(Args&&... args)
    {
        static const auto typeId = get_type_id<T>(m_type_id_generator);

        // if we need to add a container to hold the type...
        // then add it...
        if(m_containers.size() <= typeId) 
        {
            // resize to hold it
            m_containers.resize(typeId + 1);
            // now assign the container to be of the right type
            m_containers[typeId].reset(new aligned_container_impl<T>);
        }

        // add the object...
        all<T>().emplace_back(std::forward<Args>(args)...);
    }

    /// Retrieves all objects of type T within the container
    /// \tparam T The type of object you wish to retrieve
    /// \return An array of all of T within the container
    template <typename T>
    aligned_container<T>& all()
    {
        return static_cast<aligned_container_impl<T>*>(m_containers[get_type_id<T>(m_type_id_generator)].get())->container;
    }

    template <typename T>
    const aligned_container<T>& all() const
    {
        return static_cast<aligned_container_impl<T>*>(m_containers[get_type_id<T>(m_type_id_generator)].get())->container;
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
            f(i);
        }
    }

private:

    TypeIdGenerator m_type_id_generator;
    aligned_container<std::unique_ptr<base_aligned_container_impl>> m_containers;
};


#endif // TYPE_ALIGNED_CONTAINER_DYN_HPP
