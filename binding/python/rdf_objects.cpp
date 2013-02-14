/** @file "/owlcpp/binding/python/rdf_objects.cpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2013
*******************************************************************************/
#include "boost/python.hpp"
#include "boost/static_assert.hpp"
namespace bp = boost::python;

#include "owlcpp/rdf/triple.hpp"
#include "owlcpp/rdf/ns_iri.hpp"
#include "owlcpp/rdf/node.hpp"
#include "owlcpp/rdf/print_node.hpp"
#include "owlcpp/rdf/triple_store.hpp"

using owlcpp::Triple;
using owlcpp::Node_id;
using owlcpp::Doc_id;
using owlcpp::Ns_iri;
using owlcpp::Node;
using owlcpp::Triple_store;

Triple* make_triple(
         const Node_id subj, const Node_id pred,
         const Node_id obj, const Doc_id doc
) {
   Triple* t = new Triple();
   t->subj_ = subj;
   t->pred_ = pred;
   t-> obj_ =  obj;
   t-> doc_ =  doc;
   return t;
}

void export_objects() {

   bp::class_<Triple>(
            "Triple",
            "IDs for subject, predicate, object, and document"
   )
      .def(
               "__init__",
               bp::make_constructor(&make_triple)/*,
               (bp::arg("subj"), bp::arg("pred"), bp::arg("obj"), bp::arg("doc"))*/
   )
      .def(str(bp::self))
      .def(bp::self == bp::self)
      .def(bp::self != bp::self)
      .def_readonly("subj_", &Triple::subj_)
      .def_readonly("pred_", &Triple::pred_)
      .def_readonly( "obj_", &Triple:: obj_)
      .def_readonly( "doc_", &Triple:: doc_)
      ;

   bp::class_<Ns_iri>("Ns_iri", "namespace IRI", bp::init<std::string>())
      .def(str(bp::self))
      .def("str", &Ns_iri::str, bp::return_internal_reference<>())
      .def(bp::self == bp::self)
      .def(bp::self == std::string())
   ;

   bp::class_<Node, boost::noncopyable>("Node", "RDF node", bp::no_init)
      .def(str(bp::self))
      .def(bp::self == bp::self)
      .def(bp::self != bp::self)
      ;

   bp::def(
            "to_string",
            static_cast<std::string (*)(Node const&, Triple_store const&)>
            (owlcpp::to_string),
            (bp::arg("node"), bp::arg("store")),
            "return string representation of a node"
   );

   bp::def(
            "to_string",
            static_cast<std::string (*)(const Node_id, Triple_store const&)>
            (owlcpp::to_string),
            (bp::arg("node_id"), bp::arg("store")),
            "return string representation of a node"
   );

   bp::def(
            "to_string_full",
            static_cast<std::string (*)(Node const&, Triple_store const&)>
            (owlcpp::to_string_full),
            (bp::arg("node"), bp::arg("store")),
            "return node string with complete namespace"
   );

   bp::def(
            "to_string_full",
            static_cast<std::string (*)(const Node_id, Triple_store const&)>
            (owlcpp::to_string_full),
            (bp::arg("node_id"), bp::arg("store")),
            "return node string with complete namespace"
   );

   bp::def(
            "to_string_pref",
            static_cast<std::string (*)(Node const&, Triple_store const&)>
            (owlcpp::to_string_pref),
            (bp::arg("node"), bp::arg("store")),
            "return node string with namespace prefix"
   );

   bp::def(
            "to_string_pref",
            static_cast<std::string (*)(const Node_id, Triple_store const&)>
            (owlcpp::to_string_pref),
            (bp::arg("node_id"), bp::arg("store")),
            "return node string with namespace prefix"
   );
}