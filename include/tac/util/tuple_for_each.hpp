#ifndef TAC_UTIL_TUPLE_FOR_EACH_HPP
#define TAC_UTIL_TUPLE_FOR_EACH_HPP

#include <tuple>

namespace tac
{
    template<typename F, std::size_t I = 0, typename... Tp>
    typename std::enable_if<I == sizeof...(Tp), void>::type
    tuple_for_each(std::tuple<Tp...>& t, F f)
    { }

    template<typename F, std::size_t I = 0, typename... Tp>
    typename std::enable_if<I < sizeof...(Tp), void>::type
    tuple_for_each(std::tuple<Tp...>& t, F f)
    {
        f(std::get<I>(t));
        tuple_for_each<F, I + 1, Tp...>(t, f);
    }
}

#endif // TAC_UTIL_TUPLE_FOR_EACH_HPP
