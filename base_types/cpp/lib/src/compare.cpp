#include "base_types/types.hpp"


namespace base_types
{
    bool cmp_less_(timestamptz_ t, text_ v) { return t < timestamptz::parse_from_string(v); }
    bool cmp_less_(date_ t, text_ v) { return t < date::parse_from_string(v); }

    bool cmp_greater_(timestamptz_ t, text_ v) { return t > timestamptz::parse_from_string(v); }
    bool cmp_greater_(date_ t, text_ v) { return t > date::parse_from_string(v); }
}
