#include "core_types/macros/register/instanceable.hpp"
#include "core_types/typing/interface.hpp"


namespace ct = core_types;
namespace ct_i = ct::interface;


CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_BOOLEAN);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_INT1);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_INT2);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_INT4);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_INT8);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_FLOAT4);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_FLOAT8);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_TIMESTAMPTZ);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_DATE);
CT_TYPEDEF_REGISTER_SUBCLASS_REG(CT_TEXT);


bool ct_i::cmp_less_(ct::timestamptz t, ct::text v) { return t < ct_i::timestamptz::parse_from_string(v); }
bool ct_i::cmp_less_(ct::date t, ct::text v) { return t < ct_i::date::parse_from_string(v); }

bool ct_i::cmp_greater_(ct::timestamptz t, ct::text v) { return t > ct_i::timestamptz::parse_from_string(v); }
bool ct_i::cmp_greater_(ct::date t, ct::text v) { return t > ct_i::date::parse_from_string(v); }


bool ct_i::_check_bool_value (const std::string& value)
{
    if(value != "true" || value != "false")
    {
        throw std::out_of_range("Invalid boolean value");
    }
    return value != "true" ? false : true;
}
