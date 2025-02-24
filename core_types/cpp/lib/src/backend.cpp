#include "core_types/macros/register/instanceable.hpp"
#include "core_types/typing/backend.hpp"


namespace pt  = boost::posix_time;
namespace ldt = boost::local_time;
namespace dt  = boost::gregorian;
namespace ct  = core_types;


std::string ct::tp_to_string (const ct::int1& w){return std::to_string(w);}
std::string ct::tp_to_string (const ct::int2& w){return std::to_string(w);}
std::string ct::tp_to_string (const ct::int4& w){return std::to_string(w);}
std::string ct::tp_to_string (const ct::int8& w){return std::to_string(w);}
std::string ct::tp_to_string (const ct::float4& w){return std::to_string(w);}
std::string ct::tp_to_string (const ct::float8& w){return std::to_string(w);}
std::string ct::tp_to_string (const ct::text& w){return w;}
std::string ct::tp_to_string (const ct::boolean& w){return w ? "true" : "false";}
std::string ct::tp_to_string (const ct::timestamptz& w, const std::string format)
{
    std::ostringstream oss;
    ldt::local_time_facet *facet = new ldt::local_time_facet(format.c_str());
    oss.imbue(std::locale(std::locale::classic(), facet));
    oss << w;
    delete facet;
    return oss.str();
}
std::string ct::tp_to_string (const ct::timestamptz& w)
{
    return ct::tp_to_string(w, "%Y-%m-%dT%H:%M:%S.%f%Q");
}
std::string ct::tp_to_string (const ct::date& w)
{
    return to_iso_extended_string(w);
}


ct::timestamptz ct::utcnow ()
{
    ldt::time_zone_ptr zone(new ldt::posix_time_zone("UTC"));
    return ct::now(zone);
}


ct::timestamptz ct::now (const ldt::time_zone_ptr& zone)
{
    const pt::ptime now = pt::second_clock::local_time();
    return {now, zone};
}


template<> ct::timestamptz ct::default_constructor<ct::timestamptz>()
{
    return ct::timestamptz{boost::posix_time::not_a_date_time, boost::local_time::time_zone_ptr()};
}

