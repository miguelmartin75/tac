#include <iostream>

#include <tac/type_aligned_container.hpp>

struct A
{
    void printType()
    {
        std::cout << "I'm type A\n";
    }
};

struct B
{
    void printType()
    {
        std::cout << "I'm type B\n";
    }
};

struct printer
{
    template <typename T>
    void operator()(T& obj)
    {
        obj.printType();
    }
};

int main(int argc, char *argv[])
{
    constexpr const unsigned AMOUNT_OF_A_TO_ADD = 2;
    constexpr const unsigned AMOUNT_OF_B_TO_ADD = 3;

    tac::type_aligned_container<A, B> container;

    for (unsigned i = 0u; i < AMOUNT_OF_A_TO_ADD; ++i)
    {
        container.all<A>().emplace_back();
    }

    for (unsigned i = 0u; i < AMOUNT_OF_B_TO_ADD; ++i)
    {
        container.all<B>().emplace_back();
    }

    container.for_all(printer());

    return 0;
}
