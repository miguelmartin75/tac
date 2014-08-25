#ifndef TAC_DETAIL_DEFAULT_ALIGNED_CONTAINER_HPP
#define TAC_DETAIL_DEFAULT_ALIGNED_CONTAINER_HPP

#include <vector>

namespace tac
{
    namespace detail
    {
        template <typename T>
        using default_aligned_container = std::vector<T>;
    }
}

#endif // TAC_DETAIL_DEFAULT_ALIGNED_CONTAINER_HPP
