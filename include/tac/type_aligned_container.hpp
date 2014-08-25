#ifndef TYPE_ALIGNED_CONTAINER_HPP
#define TYPE_ALIGNED_CONTAINER_HPP

#include <cstddef>
#include <vector>

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
        enum : std::size_t
        {
            AMOUNT_OF_TYPES = sizeof...(Types)
        };

    private:

       // TODO
    };
}

#endif // TYPE_ALIGNED_CONTAINER_HPP
