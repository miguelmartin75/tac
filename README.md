# tac

type_aligned_container; a generic container adapter that stores unique types contiguously.

# Example

```c++
struct A {};
struct B {};
struct C {};

tac::type_aligned_container<A, B, C> container;
container.add<A>();
container.add<B>();
container.add<C>();
```

or...

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
