#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include <mapnik/value_types.hpp>
#include <mapnik/params.hpp>
#include <mapnik/boolean.hpp>
#include <vector>
#include <algorithm>

namespace detail {

class string_holder {
 public:
    string_holder() :
     member_("member") {}
    std::string const& get_string() const
    {
        return member_;
    }
 private:
    std::string member_;
};

}

int main(int argc, char** argv)
{
    std::vector<std::string> args;
    for (int i=1;i<argc;++i)
    {
        args.push_back(argv[i]);
    }
    bool quiet = std::find(args.begin(), args.end(), "-q")!=args.end();

    try
    {
        mapnik::parameters params;

        // true
        params["bool"] = mapnik::value_integer(true);
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == true));

        params["bool"] = "true";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == true));

        params["bool"] = mapnik::value_integer(1);
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == true));

        params["bool"] = "1";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == true));

        params["bool"] = "True";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == true));

        params["bool"] = "on";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == true));

        params["bool"] = "yes";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == true));

        // false
        params["bool"] = mapnik::value_integer(false);
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == false) );

        params["bool"] = "false";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == false) );

        params["bool"] = mapnik::value_integer(0);
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == false));

        params["bool"] = "0";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == false));

        params["bool"] = "False";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == false));

        params["bool"] = "off";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == false));

        params["bool"] = "no";
        BOOST_TEST( (params.get<mapnik::boolean_type>("bool") && *params.get<mapnik::boolean_type>("bool") == false));

        // strings
        params["string"] = "hello";
        BOOST_TEST( (params.get<std::string>("string") && *params.get<std::string>("string") == "hello") );

        // int
        params["int"] = mapnik::value_integer(1);
        BOOST_TEST( (params.get<mapnik::value_integer>("int") && *params.get<mapnik::value_integer>("int") == 1) );

        // double
        params["double"] = 1.5;
        BOOST_TEST( (params.get<double>("double") && *params.get<double>("double") == 1.5) );

        // value_null
        params["null"] = mapnik::value_null();
        // https://github.com/mapnik/mapnik/issues/2471
        //BOOST_TEST( (params.get<mapnik::value_null>("null") && *params.get<mapnik::value_null>("null") == mapnik::value_null()) );

        std::string value("value");
        params["value"] = value;
        BOOST_TEST(params.get<std::string>("value") == std::string("value"));
        BOOST_TEST(value == std::string("value"));

        // ensure that const member is not moved incorrectly when added to params
        detail::string_holder holder;
        std::string const& holder_member = holder.get_string();
        params["member"] = holder_member;
        BOOST_TEST(params.get<std::string>("member") == std::string("member"));
        BOOST_TEST(holder_member == std::string("member"));
    }
    catch (std::exception const& ex)
    {
        std::cerr << ex.what() << "\n";
        BOOST_TEST(false);
    }

    if (!::boost::detail::test_errors()) {
        if (quiet) std::clog << "\x1b[1;32m.\x1b[0m";
        else std::clog << "C++ parameters: \x1b[1;32m✓ \x1b[0m\n";
        ::boost::detail::report_errors_remind().called_report_errors_function = true;
    } else {
        return ::boost::report_errors();
    }
}
