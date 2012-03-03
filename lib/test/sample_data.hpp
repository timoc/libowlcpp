/** @file "/owlcpp/lib/test/sample_data.hpp"
part of owlcpp project.
@n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2010
*******************************************************************************/
#ifndef SAMPLE_DATA_HPP_
#define SAMPLE_DATA_HPP_
#include <string>
#include <vector>
#include "boost/preprocessor/stringize.hpp"
#include "boost/filesystem.hpp"
#include "boost/assign/list_of.hpp"

#ifndef SAMPLE_DATA_DIR
#error SAMPLE_DATA_DIR needs to be defined
#endif
#ifndef TEMPORARY_DIR
#error TEMPORARY_DIR needs to be defined
#endif

namespace owlcpp{ namespace test{

inline std::string sample_file_path(const std::string& name = "") {
   static const boost::filesystem::path path(BOOST_PP_STRINGIZE(SAMPLE_DATA_DIR));
   return (path / name).string();
}

inline std::string temp_file_path(const std::string& name = "") {
   std::string sf( BOOST_PP_STRINGIZE(TEMPORARY_DIR) );
   sf += '/';
   sf += name;
   return sf;
}

/**
*******************************************************************************/
struct Sample_info {
   Sample_info(std::string const& path_, std::string const& iri_, std::string const& version_)
   : path(sample_file_path(path_)), iri(iri_), version(version_) {}
   std::string path;
   std::string iri;
   std::string version;
};

std::vector<Sample_info> const& sample_files() {
   static const std::vector<Sample_info> v = boost::assign::list_of<Sample_info>
   ("version_test_b.owl", "http://purl.obolibrary.org/obo/ido/dev/version_test.owl", "http://purl.obolibrary.org/obo/ido/dev/version_test_b.owl")
   ("imports_test_01.owl", "http://purl.obolibrary.org/obo/ido/dev/imports_test_01.owl", "")
   ("negative_property_assertion_01.owl", "http://owl.semanticweb.org/page/New-Feature-NegativeObjectPropertyAssertion-001", "")
   ("one_eq_two_01.owl", "http://example.com/one_eq_two_01.owl", "")
   ("owl2-rl-rules-fp-differentFrom.owl", "http://owl.semanticweb.org/page/Owl2-rl-rules-fp-differentFrom", "")
   ("owl2-rl-rules-fp-sameAs.owl", "http://owl.semanticweb.org/page/Owl2-rl-rules-fp-sameAs", "")
   ("owl2-rl-rules-ifp-differentFrom.owl", "http://owl.semanticweb.org/page/Owl2-rl-rules-ifp-differentFrom", "")
   ("owl2-rl-rules-ifp-sameAs.owl", "http://owl2.test/rules/owl2-rl-rules-ifp-sameAs", "")
   ("propertyChain_01.owl", "http://owl.semanticweb.org/page/New-Feature-ObjectPropertyChain-001", "")
   ("test_01.owl", "http://purl.obolibrary.org/obo/ido/dev/test_01.owl", "http://purl.obolibrary.org/obo/ido/dev/test_01a.owl")
   ("transitive_property.owl", "http://purl.org/obo/owl/transitive_property", "")
   ("union_01.owl", "http://www.ifomis.org/bfo/union", "")
   ("og_01.owl", "og_01.owl", "")
//   ("", "", "")
   ;
   return v;
}

}//namespace test
}//namespace owlcpp

#endif /* SAMPLE_DATA_HPP_ */
