/** @file "/owlcpp/include/owlcpp/rdf/node_store_aux_base.hpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef NODE_STORE_AUX_BASE_HPP_
#define NODE_STORE_AUX_BASE_HPP_
#include "owlcpp/rdf/node_map.hpp"
#include "owlcpp/terms/node_tags_system.hpp"

namespace owlcpp{

/** CRTP base for RDF node stores
*******************************************************************************/
template<class T> struct Node_store_aux_base {

   /**@brief if not already present, store literal node
    @param val literal node string value
    @param type_iri datatype IRI
    @param lang string value language
    @return node ID
   */
   Node_id insert_lit_node(
            std::string const& val,
            std::string const& type_iri = "",
            std::string const& lang = ""
   ) {
      T& self = static_cast<T&>(*this);
      const Node_id nid = self.nodes().insert( Node(terms::N_empty::id(), val));
      //TODO: store type_iri and language
      return nid;
   }

   /**@brief if not already present, store blank node
    @param name node name;
    name is assumed to be unique across all documents stored in Triple_store
    @return node ID
   */
   Node_id insert_blank_node(std::string const& name) {
      T& self = static_cast<T&>(*this);
      return self.nodes().insert( Node(terms::N_blank::id(), name));
   }

};

}//namespace owlcpp
#endif /* NODE_STORE_AUX_BASE_HPP_ */
