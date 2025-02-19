#include "core_types/macros/register/instanceable.hpp"
#include "core_types/macros/declaration.hpp"
#include "core_types/typing/types.hpp"


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


namespace pt = boost::posix_time;
namespace ldt = boost::local_time;
namespace dt = boost::gregorian;
namespace ct = core_types;


std::shared_ptr<ct::timestamptz> ct::timestamptz::utcnow()
{
    ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
    return ct::timestamptz::now(zone);
}


std::shared_ptr<ct::timestamptz> ct::timestamptz::now(const ldt::time_zone_ptr& zone)
{
    const pt::ptime now = pt::second_clock::local_time();
    return std::make_shared<timestamptz>(timestamptz_(now, zone));
}
