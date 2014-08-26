# tac_vs_rawvec.cpp

This benchmark mainly compares allocation and number crunching for two
datasets, which are contained within one 'data structure'.

The first data set is {A, B, C} and the second is {E, F}. Multiplication
is just done for both datasets, so that there is some number crunching
for comparision.

The "tac" method of doing things is just a type_aligned_container<A, B, C, E, F>, which
will store each type in it's own container (vector in this case). The "rawvec" method of doing things is storing all the types into one vector/array, i.e. a `vector<ABCEF>`, where `ABCEF` is a POD storing objects A, B, C, E, and F.

Here is some sample output:


```
$ clang++ tac_vs_rawvec.cpp -std=c++1y -I../include -O3
$ ./a.out 100000000
Doing benchmark with: 100000000 amount of ABC's

testing type_aligned_container<A, B, C>...
Took: 9.94569 seconds to alloc for type_aligned_container<A, B, C>
crunching data set 1 {A, B, C}
Took: 3.00813 seconds to perform operations on data set 1 for type_aligned_container.
crunching data set 2 {E, F}
Took: 1.99562 seconds to perform operations on data set 1 for type_aligned_container.
Total time: 5.00375 seconds.

testing vector<ABCEF>...
Took: 9.73354 seconds to alloc for vector<ABC>
crunching data set 1 {A, B, C}
Took: 4.07561 seconds to perform operations on data set 1 for vector.
crunching data set 2 {E, F}
Took: 5.34217 seconds to perform operations on data set 1 for vector.
Total time: 9.41777 seconds.
```

As you can see, iterating and doing some number crunching with the "tac" is a bit faster than storing all the types into one vector. However, the "rawvec" method is a bit faster for allocation it seems.
