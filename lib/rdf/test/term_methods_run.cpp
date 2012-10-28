/** @file "/owlcpp/lib/rdf/test/term_methods_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define BOOST_TEST_MODULE term_methods_run
#include "boost/test/unit_test.hpp"
#include "test/exception_fixture.hpp"
#include "owlcpp/terms/node_tags_owl.hpp"
#include "owlcpp/terms/term_methods.hpp"

namespace owlcpp{ namespace test{

BOOST_GLOBAL_FIXTURE( Exception_fixture );

/**
*******************************************************************************/
BOOST_AUTO_TEST_CASE( case01 ) {
   char const* iri1 = "http://www.w3.org/2002/07/owl#Class";
   BOOST_CHECK_EQUAL(to_string(terms::T_owl_Class()), iri1);
   BOOST_CHECK_EQUAL(to_string_short(terms::T_owl_Class()), "owl:Class");
   BOOST_CHECK( comparison(iri1, 35, terms::T_owl_Class()));
   BOOST_CHECK( ! comparison("httt://www.w3.org/2002/07/owl#Class", terms::T_owl_Class()));
   BOOST_CHECK( ! comparison("http://www.w3.org/2002/07/owl/Class", terms::T_owl_Class()));
   BOOST_CHECK( ! comparison("http://www.w3.org/2002/07/owl#Clasu", terms::T_owl_Class()));

   BOOST_CHECK( comparison(std::string(iri1), terms::T_owl_Class()));
}

}//namespace test
}//namespace owlcpp