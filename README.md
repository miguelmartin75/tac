# tac

type_aligned_container; a generic container adapter that stores unique types contiguously.

# Example

If you would like to see compile-able examples, please see the [examples](examples) directory.

## type_aligned_container

This container requires you to have the types
passed in as arguments to the type itself. 

This container actually requires C++14, because of `std::get<T>()`.

```c++
struct A {};
struct B {};
struct C {};

tac::type_aligned_container<A, B, C> container;
container.add<A>();
container.add<B>();
container.add<C>();
```

## type_aligned_container_dyn

This container does not require you to have the types pass in
as template arguments to the type itself. Instead, if you add
a new type to the container, it will allocate (with new) a container
to allocate the objects of the new type. This requires a check
eveytime you add, and thus can be more expensive than the above container.

```c++
struct A {};
struct B {};
struct C {};

tac::type_aligned_container_dyn<> container;
container.add<A>();
container.add<B>();
container.add<C>();
```

# License

See [LICENSE](LICENSE).
