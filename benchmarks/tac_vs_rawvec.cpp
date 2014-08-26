#include <iostream>
#include <vector>
#include <chrono>

#include <tac/type_aligned_container.hpp>

typedef double Seconds;
inline Seconds GetTimeNow()
{
    using namespace std;
 
    return chrono::duration_cast<chrono::duration<Seconds, std::ratio<1> > >(chrono::high_resolution_clock::now().time_since_epoch()).count();
}

struct A
{
    double x;
};

struct B
{
    double y;
};

struct C
{
    double z;
};

struct E
{
    int x;
    char c;
};

struct F
{
    long long f;
};


int main(int argc, char *argv[])
{
    static const std::size_t DEFAULT_AMOUNT_OF_ABCS_TO_MAKE = 1000000;

    std::size_t AMOUNT_OF_ABCS_TO_MAKE = DEFAULT_AMOUNT_OF_ABCS_TO_MAKE;

    if(argc == 2)
    {
        AMOUNT_OF_ABCS_TO_MAKE = atoi(argv[1]);
    }
    else if(argc > 2)
    {
        std::cerr << "incorrect usage.\n";
        std::cerr << argv[0] << " <number_of_abcs_to_make>\n";
        return 1;
    }

    struct ABCEF
    {
        A a;
        B b;
        C c;
        E e;
        F f;
    };

    std::cout << "Doing benchmark with: " << AMOUNT_OF_ABCS_TO_MAKE << " amount of ABC's\n\n";


    std::cout << "testing type_aligned_container<A, B, C>...\n";
    {
        tac::type_aligned_container<A, B, C, E, F> cont; 

        {
            auto t1 = GetTimeNow();
            for (unsigned i = 0u; i < AMOUNT_OF_ABCS_TO_MAKE; ++i)
            {
                cont.add<A>();
                cont.add<B>();
                cont.add<C>();
                cont.add<E>();
                cont.add<F>();
            }
            auto t2 = GetTimeNow();

            std::cout << "Took: " << t2 - t1 << " seconds ";
            std::cout << "to alloc for type_aligned_container<A, B, C>\n";
        }

        {
            cont.all<A>()[0].x = 6;
            cont.all<B>()[0].y = 2;
            cont.all<C>()[0].z = 3;

            cont.all<E>()[0].x = 3;
            cont.all<E>()[0].c = 'e';

            cont.all<F>()[0].f = 100000;


            Seconds timeToPerformOnDataSet1;
            Seconds timeToPerformOnDataSet2;
        
            std::cout << "crunching data set 1 {A, B, C}\n";
            {
                auto t1 = GetTimeNow();
                for (unsigned i = 0u; i < AMOUNT_OF_ABCS_TO_MAKE; ++i)
                {
                    auto temp = cont.all<B>()[i].y * cont.all<C>()[i].z;
                    cont.all<A>()[i].x = temp * temp * temp;
                }
                auto t2 = GetTimeNow();

                timeToPerformOnDataSet1 = t2 - t1;

                std::cout << "Took: " << timeToPerformOnDataSet1 << " seconds ";
                std::cout << "to perform operations on data set 1 for type_aligned_container.\n";
            }

            std::cout << "crunching data set 2 {E, F}\n";
            {
                auto t1 = GetTimeNow();
                for (unsigned i = 0u; i < AMOUNT_OF_ABCS_TO_MAKE; ++i)
                {
                    auto temp = cont.all<E>()[i].x * cont.all<E>()[i].c;
                    cont.all<F>()[i].f = temp * temp * temp;
                }
                auto t2 = GetTimeNow();

                timeToPerformOnDataSet2 = t2 - t1;

                std::cout << "Took: " << timeToPerformOnDataSet2 << " seconds ";
                std::cout << "to perform operations on data set 1 for type_aligned_container.\n";
            }

            std::cout << "Total time: " << timeToPerformOnDataSet1 + timeToPerformOnDataSet2 << " seconds.\n"; 
        }
    }

    std::cout << '\n';

    std::cout << "testing vector<ABCEF>...\n";
    {
        std::vector<ABCEF> cont;

        {
            auto t1 = GetTimeNow();
            for (unsigned i = 0u; i < AMOUNT_OF_ABCS_TO_MAKE; ++i)
            {
                cont.emplace_back();
            }
            auto t2 = GetTimeNow();

            std::cout << "Took: " << t2 - t1 << " seconds ";
            std::cout << "to alloc for vector<ABC>\n";
        }

        {
            cont[0].a.x = 6;
            cont[0].b.y = 2;
            cont[0].c.z = 3;

            cont[0].e.x = 3;
            cont[0].e.c = 'e';

            cont[0].f.f = 100000;

            Seconds timeToPerformOnDataSet1;
            Seconds timeToPerformOnDataSet2;
        
            std::cout << "crunching data set 1 {A, B, C}\n";
            {
                auto t1 = GetTimeNow();
                for (unsigned i = 0u; i < cont.size(); ++i)
                {
                    auto temp = cont[i].b.y * cont[i].c.z;
                    cont[i].a.x = temp * temp * temp;
                }
                auto t2 = GetTimeNow();

                timeToPerformOnDataSet1 = t2 - t1;

                std::cout << "Took: " << timeToPerformOnDataSet1 << " seconds ";
                std::cout << "to perform operations on data set 1 for vector.\n";
            }

            std::cout << "crunching data set 2 {E, F}\n";
            {
                auto t1 = GetTimeNow();
                for (unsigned i = 0u; i < cont.size(); ++i)
                {
                    auto temp = cont[i].e.x * cont[i].e.c;
                    cont[i].f.f = temp * temp * temp;
                }
                auto t2 = GetTimeNow();

                timeToPerformOnDataSet2 = t2 - t1;

                std::cout << "Took: " << timeToPerformOnDataSet2 << " seconds ";
                std::cout << "to perform operations on data set 1 for vector.\n";
            }

            std::cout << "Total time: " << timeToPerformOnDataSet1 + timeToPerformOnDataSet2 << " seconds.\n";
        }
    }

    return 0;
}
