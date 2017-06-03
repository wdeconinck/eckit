/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#define BOOST_TEST_MODULE test_eckit_parser

#include "ecbuild/boost_test_framework.h"

//#include "eckit/log/Log.h"
#include "eckit/parser/YAMLParser.h"

#include "eckit/testing/Setup.h"

using namespace std;
using namespace eckit;

using namespace eckit::testing;

BOOST_GLOBAL_FIXTURE(Setup);

BOOST_AUTO_TEST_SUITE( test_eckit_parser_yaml )

//----------------------------------------------------------------------------------------------------------------------

#define QUOTE(...) #__VA_ARGS__
#if 0

BOOST_AUTO_TEST_CASE( test_eckit_yaml_parser_from_istream ) {
    std::istringstream in(QUOTE({ "a" : [true, false, 3],
                                  "b" : 42.3 ,
                                  "c" : null,
                                  "d" : "y\n\tr\rh",
                                  "e" : "867017db84f4bc2b5078ca56ffd3b9b9"}
                                ));
    YAMLParser p(in);

    Value v = p.parse();

//    Log::info() << "yaml " << v << std::endl;

    BOOST_TEST_MESSAGE( v );
    BOOST_TEST_MESSAGE( v["a"] );
    BOOST_TEST_MESSAGE( v["a"][2] );

    BOOST_CHECK( v.isMap() );
    BOOST_CHECK_EQUAL( v.as<ValueMap>().size(), 5 );

    BOOST_CHECK( v["a"].isList() );
    BOOST_CHECK_EQUAL( v["a"].as<ValueList>().size(), 3 );


    BOOST_CHECK( v["a"][0].isBool() );
    BOOST_CHECK_EQUAL( v["a"][0].as<bool>(), true );

    BOOST_CHECK( v["a"][1].isBool() );
    BOOST_CHECK_EQUAL( v["a"][1].as<bool>(), false );

    BOOST_CHECK( v["a"][2].isNumber() );
    BOOST_CHECK_EQUAL( (int) v["a"][2], 3 );

    BOOST_CHECK( v["b"].isDouble() );
    BOOST_CHECK_LT( v["b"].as<double>() - 42.3, 1E-12 );

    BOOST_CHECK( v["c"].isNil() );

    BOOST_CHECK( v["d"].isString() );

    BOOST_CHECK( v["e"].isString() );
    BOOST_CHECK_EQUAL( v["e"].as<string>(), "867017db84f4bc2b5078ca56ffd3b9b9" );
}
#endif
//----------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( test_eckit_yaml_1 ) {
    Value v =  YAMLParser::decodeFile("2.1.yaml");
    std::cout << "2.1.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_2 ) {
    Value v =  YAMLParser::decodeFile("2.2.yaml");
    std::cout << "2.2.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_3 ) {
    Value v =  YAMLParser::decodeFile("2.3.yaml");
    std::cout << "2.3.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_4 ) {
    Value v =  YAMLParser::decodeFile("2.4.yaml");
    std::cout << "2.4.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_5 ) {
    Value v =  YAMLParser::decodeFile("2.5.yaml");
    std::cout << "2.5.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_6 ) {
    Value v =  YAMLParser::decodeFile("2.6.yaml");
    std::cout << "2.6.yaml " << v << std::endl;
}

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_7 ) {
    Value v =  YAMLParser::decodeFile("2.7.yaml");
    std::cout << "2.7.yaml " << v << std::endl;
}
*/

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_8 ) {
    Value v =  YAMLParser::decodeFile("2.8.yaml");
    std::cout << "2.8.yaml " << v << std::endl;
}
*/

BOOST_AUTO_TEST_CASE( test_eckit_yaml_9 ) {
    Value v =  YAMLParser::decodeFile("2.9.yaml");
    std::cout << "2.9.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_10 ) {
    Value v =  YAMLParser::decodeFile("2.10.yaml");
    std::cout << "2.10.yaml " << v << std::endl;
}

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_11 ) {
    Value v =  YAMLParser::decodeFile("2.11.yaml");
    std::cout << "2.11.yaml " << v << std::endl;
}
*/

BOOST_AUTO_TEST_CASE( test_eckit_yaml_12 ) {
    Value v =  YAMLParser::decodeFile("2.12.yaml");
    std::cout << "2.12.yaml " << v << std::endl;
}
/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_13 ) {
    Value v =  YAMLParser::decodeFile("2.13.yaml");
    std::cout << "2.13.yaml " << v << std::endl;
}
*/
/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_14 ) {
    Value v =  YAMLParser::decodeFile("2.14.yaml");
    std::cout << "2.14.yaml " << v << std::endl;
}
*/
/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_15 ) {
    Value v =  YAMLParser::decodeFile("2.15.yaml");
    std::cout << "2.15.yaml " << v << std::endl;
}
*/
/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_16 ) {
    Value v =  YAMLParser::decodeFile("2.16.yaml");
    std::cout << "2.16.yaml " << v << std::endl;
}
*/

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_17 ) {
    Value v =  YAMLParser::decodeFile("2.17.yaml");
    std::cout << "2.17.yaml " << v << std::endl;
}
*/

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_18 ) {
    Value v =  YAMLParser::decodeFile("2.18.yaml");
    std::cout << "2.18.yaml " << v << std::endl;
}
*/

BOOST_AUTO_TEST_CASE( test_eckit_yaml_19 ) {
    Value v =  YAMLParser::decodeFile("2.19.yaml");
    std::cout << "2.19.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_20 ) {
    Value v =  YAMLParser::decodeFile("2.20.yaml");
    std::cout << "2.20.yaml " << v << std::endl;
}


BOOST_AUTO_TEST_CASE( test_eckit_yaml_21 ) {
    Value v =  YAMLParser::decodeFile("2.21.yaml");
    std::cout << "2.21.yaml " << v << std::endl;
}

BOOST_AUTO_TEST_CASE( test_eckit_yaml_22 ) {
    Value v =  YAMLParser::decodeFile("2.22.yaml");
    std::cout << "2.22.yaml " << v << std::endl;
}

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_23 ) {
    Value v =  YAMLParser::decodeFile("2.23.yaml");
    std::cout << "2.23.yaml " << v << std::endl;
}
*/

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_24 ) {
    Value v =  YAMLParser::decodeFile("2.24.yaml");
    std::cout << "2.24.yaml " << v << std::endl;
}
*/

/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_25 ) {
    Value v =  YAMLParser::decodeFile("2.25.yaml");
    std::cout << "2.25.yaml " << v << std::endl;
}
*/
/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_26 ) {
    Value v =  YAMLParser::decodeFile("2.26.yaml");
    std::cout << "2.26.yaml " << v << std::endl;
}
*/
/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_27 ) {
    Value v =  YAMLParser::decodeFile("2.27.yaml");
    std::cout << "2.27.yaml " << v << std::endl;
}
*/
/*
BOOST_AUTO_TEST_CASE( test_eckit_yaml_28 ) {
    Value v =  YAMLParser::decodeFile("2.28.yaml");
    std::cout << "2.28.yaml " << v << std::endl;
}
*/

// BOOST_AUTO_TEST_CASE( test_eckit_yaml_parser_from_file ) {

//     Value v =  YAMLParser::decodeFile("test.yaml");

//     std::cout << "test.yaml " << v << std::endl;

    // BOOST_TEST_MESSAGE( v );
    // BOOST_TEST_MESSAGE( v["a"] );
    // BOOST_TEST_MESSAGE( v["a"][2] );

    // BOOST_CHECK( v.isMap() );
    // BOOST_CHECK_EQUAL( v.as<ValueMap>().size(), 5 );

    // BOOST_CHECK( v["a"].isList() );
    // BOOST_CHECK_EQUAL( v["a"].as<ValueList>().size(), 3 );


    // BOOST_CHECK( v["a"][0].isBool() );
    // BOOST_CHECK_EQUAL( v["a"][0].as<bool>(), true );

    // BOOST_CHECK( v["a"][1].isBool() );
    // BOOST_CHECK_EQUAL( v["a"][1].as<bool>(), false );

    // BOOST_CHECK( v["a"][2].isNumber() );
    // BOOST_CHECK_EQUAL( (int) v["a"][2], 3 );

    // BOOST_CHECK( v["b"].isDouble() );
    // BOOST_CHECK_LT( v["b"].as<double>() - 42.3, 1E-12 );

    // BOOST_CHECK( v["c"].isNil() );

    // BOOST_CHECK( v["d"].isString() );

    // BOOST_CHECK( v["e"].isString() );
    // BOOST_CHECK_EQUAL( v["e"].as<string>(), "769b654c42b759e3604e4fa37f0e721dc4797818" );
// }

//----------------------------------------------------------------------------------------------------------------------
#if 0
BOOST_AUTO_TEST_CASE( test_eckit_parser_parse_to_set ) {


    istringstream in("[ \"a\" , \"b\", \"c\" ]" );
    YAMLParser p(in);
    Value v = p.parse();

//    Log::info() << "yaml " << v << std::endl;


    BOOST_TEST_MESSAGE( v );

    BOOST_CHECK( v.isList() );
    BOOST_CHECK_EQUAL( v.as<ValueList>().size(), 3 );

    BOOST_CHECK( v[0].isString() );
    BOOST_CHECK_EQUAL( v[0].as<string>(), "a" );

    BOOST_CHECK( v[1].isString() );
    BOOST_CHECK_EQUAL( v[1].as<string>(), "b" );

    BOOST_CHECK( v[2].isString() );
    BOOST_CHECK_EQUAL( v[2].as<string>(), "c" );
}

//----------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( test_eckit_parser_parse_to_map ) {
    istringstream in("{ \"a\" : \"AAA\", \"b\" : 0.0 , \"c\" : \"null\", \"d\" : \"\"}" );
    YAMLParser p(in);
    Value v = p.parse();

//    Log::info() << "yaml " << v << std::endl;


    BOOST_TEST_MESSAGE( v );

    BOOST_CHECK( v.isMap() );
    BOOST_CHECK_EQUAL( v.as<ValueMap>().size(), 4 );

    BOOST_CHECK( v["a"].isString() );
    BOOST_CHECK_EQUAL( v["a"].as<string>(), "AAA" );

    BOOST_CHECK( v["b"].isDouble() );
    BOOST_CHECK_EQUAL( v["b"].as<double>(), 0.0 );

    BOOST_CHECK( v["c"].isString() );
    BOOST_CHECK_EQUAL( v["c"].as<string>(), "null" );

    BOOST_CHECK( v["d"].isString() );
    BOOST_CHECK_EQUAL( v["d"].as<string>(), "" );
}

//----------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( test_eckit_parser_eof ) {
    istringstream in("");
    YAMLParser p(in);
    BOOST_CHECK_THROW(p.next(), StreamParser::Error);
}

#endif

//----------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()