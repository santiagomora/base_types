#include "core_types/macros/register/instanceable.hpp"
#include "core_types/typing/backend.hpp"


namespace pt  = boost::posix_time;
namespace ldt = boost::local_time;
namespace dt  = boost::gregorian;
namespace ct  = core_types;

namespace core_types
{

std::string to_str (const int1& w){return std::to_string(w);}
std::string to_str (const int2& w){return std::to_string(w);}
std::string to_str (const int4& w){return std::to_string(w);}
std::string to_str (const int8& w){return std::to_string(w);}
std::string to_str (const float4& w){return std::to_string(w);}
std::string to_str (const float8& w){return std::to_string(w);}
std::string to_str (const text& w){return w;}
std::string to_str (const boolean& w){return w ? "true" : "false";}
std::string to_str (const timestamptz& w, const std::string format)
{
    std::ostringstream oss;
    ldt::local_time_facet *facet = new ldt::local_time_facet(format.c_str());
    oss.imbue(std::locale(std::locale::classic(), facet));
    oss << w;
    delete facet;
    return oss.str();
}
std::string to_str (const timestamptz& w)
{
    return to_str(w, "%Y-%m-%dT%H:%M:%S.%f%Q");
}
std::string to_str (const date& w)
{
    return to_iso_extended_string(w);
}


timestamptz utcnow ()
{
    ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
    return now(zone);
}


timestamptz now (const ldt::time_zone_ptr& zone)
{
    const pt::ptime now = pt::second_clock::local_time();
    return {now, zone};
}


template<> timestamptz default_constructor<timestamptz>()
{
    return timestamptz{boost::posix_time::not_a_date_time, boost::local_time::time_zone_ptr()};
}

}
