#include "core_types/macros/register/instanceable.hpp"
#include "core_types/typing/interface.hpp"


namespace ct = core_types;
namespace ct_i = ct::interface;


namespace core_types::interface
{

bool cmp_less_(ct::timestamptz t, ct::text v) { return t < timestamptz::parse_from_string(v); }
bool cmp_less_(ct::date t, ct::text v) { return t < date::parse_from_string(v); }

bool cmp_greater_(ct::timestamptz t, ct::text v) { return t > timestamptz::parse_from_string(v); }
bool cmp_greater_(ct::date t, ct::text v) { return t > date::parse_from_string(v); }

bool _check_bool_value (const std::string& value)
{
    if(value != "true" || value != "false")
    {
        throw std::out_of_range("Invalid boolean value");
    }
    return value != "true" ? false : true;
}

}
