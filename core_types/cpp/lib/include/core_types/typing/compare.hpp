# ifndef BASE_TYPES_TYPING_COMPARE
# define BASE_TYPES_TYPING_COMPARE
#include <type_traits>
#include "core_types/typing/types.hpp"


namespace core_types
{

template<
typename T, typename V, typename = std::enable_if_t<
    (std::is_arithmetic_v<T> && std::is_arithmetic_v<V>) ||
    (std::is_same_v<T, V>)
>>
bool cmp_greater_(T t, V v) { return t > v; }
bool cmp_greater_(timestamptz_ t, text_ v);
bool cmp_greater_(date_ t, text_ v);


template<
typename T, typename V, typename = std::enable_if_t<
    (std::is_arithmetic_v<T> && std::is_arithmetic_v<V>) ||
    (std::is_same_v<T, V>)
>>
bool cmp_less_(T t, V v) { return t < v; }
bool cmp_less_(timestamptz_ t, text_ v);
bool cmp_less_(date_ t, text_ v);


template<typename T, typename V>
int compare_ (const wrapper<T>& t, const wrapper<V>& v) {
    if  (cmp_less_(t.value(), v.value())) {
        return -1;
    } else if (cmp_greater_(t.value(), v.value())) {
        return 1;
    }
    return 0;
}


}

#endif
