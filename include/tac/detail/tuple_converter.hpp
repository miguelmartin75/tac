#ifndef TAC_DETAIL_TUPLE_CONVERTER_HPP
#define TAC_DETAIL_TUPLE_CONVERTER_HPP

#include <tuple>

namespace tac
{
    namespace detail
    {
        // my code taken from (Miguel Martin):
        // https://gist.github.com/miguelmartin75/c8335ff0af327dc5e5b4
        template<template <typename T> class X>
        struct tuple_converter
        {
            template <typename T, typename... Args>
            struct Deducer
            {
                typedef decltype(std::tuple_cat(std::tuple<X<T>>(), typename Deducer<Args...>::tuple())) tuple;
            };

            template<typename T>
            struct Deducer<T>
            {
                typedef std::tuple<X<T>> tuple;
            };

            template<typename... Args>
            using tuple = typename Deducer<Args...>::tuple;
        };
    }
}


#endif // TAC_DETAIL_TUPLE_CONVERTER_HPP
