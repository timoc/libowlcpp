/** @file "/owlcpp/lib/io/test/triple_store_01_run.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#define BOOST_TEST_MODULE triple_store_01_run
#include "boost/test/unit_test.hpp"
#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/foreach.hpp"
#include "test/exception_fixture.hpp"
#include "test/sample_data.hpp"
#include "owlcpp/io/catalog.hpp"
#include "owlcpp/io/input.hpp"
#include "owlcpp/io/exception.hpp"
#include "owlcpp/io/raptor_wrapper.hpp"
#include "owlcpp/rdf/triple_store.hpp"
#include "owlcpp/rdf/print_triple.hpp"
#include "raptor_to_store.hpp"

namespace owlcpp{ namespace test{

const std::string path1 = sample_files()[13].path;
const std::string iri1 = sample_files()[13].iri;
const std::string ver1 = sample_files()[13].version;
const std::string path2 = sample_files()[0].path;
const std::string iri2 = sample_files()[0].iri;
const std::string ver2 = sample_files()[0].version;
const std::string path3 = sample_files()[3].path;
const std::string iri3 = sample_files()[3].iri;

/**@test
*******************************************************************************/
BOOST_AUTO_TEST_CASE( test_triple_store_01 ) {
   Triple_store ts;
   BOOST_CHECK_EQUAL( ts.map_doc().size(), 0u );
   Check_both cb(iri1, ver1);
   owlcpp::detail::Raptor_to_store rts(ts, path1, cb);
   boost::filesystem::ifstream ifs(path1);
   rts.parse(ifs);
   BOOST_REQUIRE_EQUAL( ts.map_doc().size(), 1u );
   const Doc_id did = *ts.map_doc().begin();
   BOOST_REQUIRE( ts.map_doc().find_path(path1));
   BOOST_CHECK_EQUAL( ts.map_doc().find_path(path1).front(), did);
   BOOST_CHECK_EQUAL( ts[did].path, path1 );
   const Node_id nid1 = ts[did].ontology_iri;
   const Node_id nid2 = ts[did].version_iri;
   BOOST_CHECK_EQUAL( to_string(nid2, ts), ver1 );
   BOOST_CHECK_EQUAL( to_string_full(nid1, ts), iri1 );
   BOOST_FOREACH(const Triple t, ts.map_triple()) {
      std::cout << to_string(t, ts) << '\n';
   }
   std::cout << std::endl;
   BOOST_CHECK_EQUAL( ts.map_triple().size(), 14u );
   BOOST_CHECK( ts.find_doc_iri(iri1) );
}

/**@test
*******************************************************************************/
BOOST_AUTO_TEST_CASE( test_triple_store_02 ) {
   Triple_store ts;
   boost::filesystem::ifstream ifs(path1);
   load(ifs, ts);
   BOOST_CHECK_EQUAL( ts.map_triple().size(), 14u );
}

/**@test
*******************************************************************************/
BOOST_AUTO_TEST_CASE( test_triple_store_03 ) {
   Triple_store ts;
   std::cout << iri1 << ' ' << iri2 << std::endl;
   BOOST_CHECK( ! ts.find_doc_iri("blah") );
   BOOST_CHECK( ! ts.find_doc_iri("blah1") );
   BOOST_CHECK( ! ts.find_doc_iri("blah2") );
   BOOST_CHECK( ! ts.find_doc_iri("blah3") );
   BOOST_CHECK( ! ts.find_doc_iri(iri1) );
   BOOST_CHECK( ! ts.find_doc_iri(iri2) );
   Check_both cb(iri2, ver2);
   owlcpp::detail::Raptor_to_store rts(ts, path2, cb);
   boost::filesystem::ifstream ifs(path2);
   rts.parse(ifs);
   BOOST_CHECK( ! ts.find_doc_iri(iri1) );
   BOOST_CHECK( ts.find_doc_iri(iri2) );
   BOOST_CHECK_EQUAL(rts.imports().size(), 1u);
   BOOST_CHECK_EQUAL(rts.imports().at(0), ver1);
   BOOST_CHECK_EQUAL( ts.map_triple().size(), 3u );
}

/**@test
*******************************************************************************/
BOOST_AUTO_TEST_CASE( test_triple_store_04 ) {
   Triple_store ts;
   Catalog cat;
   add(cat, sample_file_path());
   load_file(path2, ts, cat);
   BOOST_FOREACH(const Triple t, ts.map_triple()) {
      std::cout << to_string(t, ts) << '\n';
   }
   std::cout << std::endl;

   BOOST_CHECK_EQUAL( ts.map_triple().size(), 17u );
}

/**@test
*******************************************************************************/
BOOST_AUTO_TEST_CASE( test_triple_store_05 ) {
   Triple_store ts;
   Catalog cat;
   add(cat, sample_file_path());
   load_file(path3, ts, cat);

   BOOST_CHECK( ts.find_doc_iri(iri3) );
   BOOST_CHECK_GT( ts.map_triple().size(), 18u );
}

/**@test
*******************************************************************************/
BOOST_AUTO_TEST_CASE( parse_invalid_docs ) {
   Triple_store ts;
   Catalog cat;
   add(cat, sample_file_path());

   BOOST_CHECK_THROW(
            load_file(sample_file_path("invalid_01.xml"), ts, cat),
            Input_err
   );

   BOOST_CHECK_THROW(
            load_file(sample_file_path("invalid_02.xml"), ts, cat),
            Input_err
   );

   BOOST_CHECK_THROW(
            load_file(sample_file_path("err_spell_owl.owl"), ts, cat),
            Input_err
   );
}

}//namespace test
}//namespace owlcpp
