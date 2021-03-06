/** @file "/owlcpp/include/owlcpp/logic/config.hpp"
part of owlcpp project.
Distributed under GNU General Public License; see doc/license.txt.
@date 2011 @author Mikhail K Levin
*******************************************************************************/
#ifndef OWLCPP_LOGIC_CONFIG_HPP_
#define OWLCPP_LOGIC_CONFIG_HPP_

#include "owlcpp/config.hpp"

#ifndef BOOST_SYMBOL_EXPORT
  #define BOOST_SYMBOL_EXPORT
  #define BOOST_SYMBOL_IMPORT
#endif
#if defined(OWLCPP_DYN_LINK) || defined(OWLCPP_LOGIC_DYN_LINK)
#  if defined(OWLCPP_LOGIC_SOURCE)
#     define OWLCPP_LOGIC_DECL BOOST_SYMBOL_EXPORT
#  else
#     define OWLCPP_LOGIC_DECL BOOST_SYMBOL_IMPORT
#  endif
#else
#  define OWLCPP_LOGIC_DECL
#endif

#endif /* OWLCPP_LOGIC_CONFIG_HPP_ */
