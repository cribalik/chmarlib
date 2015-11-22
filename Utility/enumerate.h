#include <cstddef>

namespace detail {
    template<class T>
    struct EnumWrapper {
        T& obj;
        using It = decltype(obj.begin());
        struct Enumerator {
            It it;
            std::size_t i;
            using Val = decltype(*it);
            struct Pair {std::size_t i; Val& v;};
            Enumerator& operator++() {++i; ++it; return *this;}
            Pair operator*() {return Pair{i, *it};}
            bool operator!=(const Enumerator& rhs) const {return it != rhs.it;}
        };
        Enumerator begin() {return Enumerator{obj.begin(),0};}
        Enumerator end() {return Enumerator{obj.end(),0};}
    };
    
    template<class T>
    struct ConstEnumWrapper {
        const T& obj;
        using It = decltype(obj.begin());
        struct ConstEnumerator {
            It it;
            std::size_t i;
            using Val = decltype(*it);
            struct Pair {std::size_t i; const Val& v;};
            ConstEnumerator& operator++() {++i; ++it; return *this;}
            Pair operator*() {return Pair{i, *it};}
            bool operator!=(const ConstEnumerator& rhs) const {return it != rhs.it;}
        };
        ConstEnumerator begin() const {return ConstEnumerator{obj.begin(),0};}
        ConstEnumerator end() const {return ConstEnumerator{obj.end(),0};}
    };
}

template<class T>
detail::EnumWrapper<T> enumerate(T& t) {
    return detail::EnumWrapper<T>{t};
}

template<class T>
const detail::ConstEnumWrapper<T> enumerate(const T& t) {
    return detail::ConstEnumWrapper<T>{t};
}
