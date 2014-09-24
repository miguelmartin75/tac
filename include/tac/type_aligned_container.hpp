#ifndef TAC_TYPE_ALIGNED_CONTAINER_HPP
#define TAC_TYPE_ALIGNED_CONTAINER_HPP

#include <tuple>
#include <vector>
#include <utility>

#include <tac/detail/tuple_converter.hpp>
#include <tac/detail/default_aligned_container.hpp>

namespace tac
{
    /// \brief A container that will align it's contents by type.
    /// 
    /// You can think of a type_aligned_container as basically, converting
    /// tuple<T1, T2, ..., Tn> to tuple<vector<T1>, vector<T2>, ..., vector<Tn>>.
    /// 
    /// \tparam Types The types you wish this container to store
    template <typename... Types>
    struct type_aligned_container
    {
        template <typename T>
        using aligned_container = detail::default_aligned_container<T>;

        enum : std::size_t
        {
            AMOUNT_OF_TYPES = sizeof...(Types)
        };

        /// Retrieves all objects of type T within the container
        /// \tparam T The type of object you wish to retrieve
        /// \return An array of all of T within the container
        template <typename T>
        aligned_container<T>& all()
        {
            return std::get<aligned_container<T>>(m_containers);
        }

        template <typename T>
        const aligned_container<T>& all() const
        {
            return std::get<aligned_container<T>>(m_containers);
        }

        template <typename F>
        void for_all(F f)
        {
            impl_tuple_for_each(m_containers, for_all_functor_impl<F>{f});
        }

        /// Clears the container
        void clear()
        {
            impl_tuple_for_each(m_containers, clear_container_functor_impl());
        }

    private:

        template <typename F>
        struct for_all_functor_impl
        {
            template <typename T>
            void operator()(T& container)
            {
                for(auto& x : container)
                {
                    f(x);
                }
            }
            F f;
        };

        struct clear_container_functor_impl
        {
            template <typename T>
            void operator()(T& container)
            {
                container.clear();
            }
        };

        template<typename F, std::size_t I = 0, typename... Tp>
        typename std::enable_if<I == sizeof...(Tp), void>::type
        impl_tuple_for_each(std::tuple<Tp...>& t, F f)
        { }

        template<typename F, std::size_t I = 0, typename... Tp>
        typename std::enable_if<I < sizeof...(Tp), void>::type
        impl_tuple_for_each(std::tuple<Tp...>& t, F f)
        {
            f(std::get<I>(t));
            impl_tuple_for_each<F, I + 1, Tp...>(t, f);
        }


        /// the containers for all the types
        typename detail::tuple_converter<aligned_container>::template tuple<Types...> m_containers;
    };

}

#endif // TAC_TYPE_ALIGNED_CONTAINER_HPP
