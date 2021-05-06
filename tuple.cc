#include <type_traits>
#include <iostream>

template<typename... Types>
class Tuple;

template<typename Head, typename...Tail>
class Tuple<Head, Tail...> {
private:
    Head head;
    Tuple<Tail...> tail;
public:
    Tuple() {}

    Tuple(Head const& head, Tuple<Tail...> const& tail) 
        : head(head), tail(tail) {}

    Tuple(Head const& head, Tail const&... tail) 
        : head(head), tail(tail...) {}

    template<typename VHead, typename... VTail,
             typename = std::enable_if_t<sizeof...(VTail)==sizeof...(Tail)>>
    Tuple(VHead&& vhead, VTail&&... vtail) 
        : head(std::forward<VHead>(vhead)),
          tail(std::forward<VTail>(vtail)...) {}

    template<typename VHead, typename... VTail,
             typename = std::enable_if_t<sizeof...(VTail)==sizeof...(Tail)>>
    Tuple(Tuple<VHead, VTail...> const& other)
        : head(other.getHead()),
          tail(other.getTail()) {}

    Head& getHead() {
        return head;
    }

    Head const& getHead() const {
        return head;
    }

    Tuple<Tail...>& getTail() {
        return tail;
    }

    Tuple<Tail...> const& getTail() const {
        return tail;
    }
};

template<>
class Tuple<> {
};

template<unsigned N>
struct TupleGet {
    template<typename Head, typename...Tail>
    static auto apply(Tuple<Head, Tail...> const& t) {
        return TupleGet<N-1>::apply(t.getTail());
    }
};

template<>
struct TupleGet<0> {
    template<typename Head, typename... Tail>
    static Head const& apply(Tuple<Head, Tail...> const& t) {
        return t.getHead();
    }
};

template<unsigned N, typename... Types>
auto get(Tuple<Types...> const& t) {
    return TupleGet<N>::apply(t);
}

template<typename... Types>
auto makeTuple(Types&&... elems) {
    return Tuple<std::decay_t<Types>...>(std::forward<Types>(elems)...);
}

bool operator==(Tuple<> const&, Tuple<> const&) {
    return true;
}

template<typename Head1, typename... Tail1,
         typename Head2, typename... Tail2,
         typename = std::enable_if_t<sizeof...(Tail1) == sizeof...(Tail2)>>
bool operator==(Tuple<Head1, Tail1...> const& lhs, Tuple<Head2, Tail2...> const& rhs) {
    return lhs.getHead() == rhs.getHead() &&
           lhs.getTail() == rhs.getTail();
}


template<typename... Types>
struct IsEmpty {
    static constexpr bool value = true;
};
template<>
struct IsEmpty<Tuple<>> {
    static constexpr bool value = true;
};


template<typename Head, typename... Tail>
class FrontT;
template<typename Head, typename... Tail>
class FrontT<Tuple<Head, Tail...>> {
public:
    using Type = Head;
};


template<typename Head, typename... Tail>
class PopFrontT;
template<typename Head, typename... Tail>
class PopFrontT<Tuple<Head, Tail...>> {
public:
    using Type = Tuple<Tail...>;
};
template<typename Tuple>
using PopFront = typename PopFrontT<Tuple>::Type;


template<typename... Types>
class PushFrontT;
template<typename... Types, typename Element>
class PushFrontT<Tuple<Types...>, Element> {
public:
    using Type = Tuple<Element, Types...>;
};
template<typename Elements, typename NewElement>
using PushFront = typename PushFrontT<Elements, NewElement>::Type;


template<typename... Types>
class PushBackT;
template<typename... Types, typename Element>
class PushBackT<Tuple<Types...>, Element> {
public:
    using Type = Tuple<Types..., Element>;
};
template<typename Tuple, typename NewElement>
using PushBack = typename PushBackT<Tuple, NewElement>::Type;


template<typename... Types, typename V>
PushFrontT<Tuple<Types...>, V>
push_front_v(Tuple<Types...> const& tuple, V const& value) {
    return PushFront<Tuple<Types...>, V>(value, tuple);
}


template<typename V>
Tuple<V> push_back_v(Tuple<> const&, V const& value) {
    return Tuple<V>(value);
}
// recursive case
template<typename Head, typename... Tail, typename V>
Tuple<Head, Tail..., V>
push_back_v(Tuple<Head, Tail...> const& tuple, V const& value) {
    return Tuple<Head, Tail..., V>(tuple.getHead(),
                    push_back_v(tuple.getTail(), value));
}

template<typename...  Types>
PopFront<Tuple<Types...>>
pop_front_v(Tuple<Types...> const& tuple) {
    return tuple.getTail();
}

int main() {
    Tuple<int, double, std::string> t1(17, 3.14, "Hello World!");
    std::cout << "t1 -> (" << get<0>(t1)
                         << ", " << get<1>(t1) 
                         << ", " << get<2>(t1) 
                         << ")" << std::endl;

    Tuple<int, double, std::string> t2(t1);

    auto t3 = makeTuple(17, 3.14, "Foobar");
    std::cout << "t3 -> (" << get<0>(t3)
                         << ", " << get<1>(t3) 
                         << ", " << get<2>(t3) 
                         << ")" << std::endl;

    using NewTuple = PopFront<PushBack<decltype(t3), bool>>;
    NewTuple t4(get<1>(t3), get<2>(t3), true);
    std::cout << "t4 -> (" << get<0>(t4) 
                         << ", " << get<1>(t4) 
                         << ", " << get<2>(t4) 
                         << ")" << std::endl;

    Tuple<int, double, std::string> t5(17, 3.14, "Weizhuangzhe");
    auto t6 = pop_front_v(push_back_v(t5, true));
    std::cout << "t6 -> (" << get<0>(t6) 
                         << ", " << get<1>(t6) 
                         << ", " << get<2>(t6) 
                         << ")" << std::endl;

    return 0;
}
