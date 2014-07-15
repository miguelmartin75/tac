# type_aligned_container

A generic container that stores unique types contiguously.

# Example

```c++
struct A {};
struct B {};
struct C {};

type_aligned_container<A, B, C> container;
container.add<A>();
container.add<B>();
container.add<C>();
```

# License

See [[LICENSE]].
