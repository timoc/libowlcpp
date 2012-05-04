/** @file "/owlcpp/include/owlcpp/rdf/iri_map.hpp" 
part of owlcpp project.
@n @n Distributed under the Boost Software License, Version 1.0; see doc/license.txt.
@n Copyright Mikhail K Levin 2012
*******************************************************************************/
#ifndef IRI_MAP_HPP_
#define IRI_MAP_HPP_
#include "owlcpp/rdf/ns_map_base.hpp"
#include "owlcpp/detail/id_tracker.hpp"
#include "owlcpp/rdf/node_map_std.hpp"
#include "owlcpp/rdf/std_nodes.hpp"

namespace owlcpp{

/**@brief Store namespace IRIs
*******************************************************************************/
class Iri_map {
public:
   typedef Ns_id id_type;
   typedef Ns_map_base::iterator iterator;
   typedef Ns_map_base::const_iterator const_iterator;
   typedef Ns_map_base::Err Err;

   Iri_map(Node_map_std const& std_map = Node_map_std::get(Nodes_none()))
   : smap_(std_map), tracker_(smap_.ns_id_next()), map_() {}

   std::size_t size() const {return map_.size();}
   const_iterator begin() const {return map_.begin();}
   const_iterator end() const {return map_.end();}

   std::string operator[](const Ns_id iid) const {
      return iid < smap_.ns_id_next() ? smap_[iid] : map_[iid];
   }

   std::string at(const Ns_id iid) const {
      return iid < smap_.ns_id_next() ? smap_.at(iid) : map_.at(iid);
   }

   /**
    @param iri namespace IRI string
    @return pointer to namespace IRI ID or NULL if iri is unknown
   */
   Ns_id const* find_iri(std::string const& iri) const {
      Ns_id const*const id = smap_.find_iri(iri);
      return id ? id : map_.find_iri(iri);
   }

   /**
    @param iid namespace IRI ID
    @return IRI prefix string or "" if no prefix was defined
   */
   std::string prefix(const Ns_id iid) const {
      if( smap_.is_standard(iid) ) return smap_.prefix(iid);
      return map_.prefix(iid);
   }

   /**
    @param pref prefix for namespace IRI
    @return pointer to namespace IRI ID or NULL if prefix is unknown
   */
   Ns_id const* find_prefix(std::string const& pref) const {
      Ns_id const*const id = map_.find_prefix(pref);
      return id ? id : smap_.find_prefix(pref);
   }

   /**
    @param iid namespace IRI ID
    @param pref namespace IRI prefix
    @details Define or re-define the prefix for a standard or user-defined
    namespace IRI.
   */
   void insert_prefix(const Ns_id iid, std::string const& pref) {
      if( pref.empty() ) {
         map_.set_prefix(iid);
         return;
      }
      BOOST_ASSERT( smap_.is_standard(iid) || map_.have(iid) );
      Ns_id const*const iid0 = find_prefix(pref);
      if( iid0 ) {
         if( *iid0 == iid ) return; //prefix already defined for same IRI
         BOOST_THROW_EXCEPTION(
                  Err()
                  << Err::msg_t("prefix reserved for different IRI")
                  << Err::str1_t(pref)
                  << Err::str2_t(at(iid))
                  << Err::str3_t(at(*iid0))
         );
      }
      map_.set_prefix(iid, pref);
   }

   Ns_id insert(std::string const& iri) {
      Ns_id const*const iid = find_iri(iri);
      return iid ? *iid : map_.insert(tracker_.get(), iri );
   }

   void remove(const Ns_id iid) {
      if( iid < smap_.ns_id_next() ) return;
      map_.remove(iid);
      tracker_.push(iid);
   }

   void clear() {
      map_.clear();
      tracker_ = tracker_t(smap_.ns_id_next());
   }

private:
   typedef detail::Id_tracker<id_type> tracker_t;
   Node_map_std const& smap_;
   tracker_t tracker_;
   Ns_map_base map_;
};

}//namespace owlcpp
#endif /* IRI_MAP_HPP_ */
