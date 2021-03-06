/**
 * \file arrival_force_parser.hpp
 *
 * \copyright 2017 John Harwell, All rights reserved.
 *
 * This file is part of COSM.
 *
 * COSM is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * COSM is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * COSM.  If not, see <http://www.gnu.org/licenses/
 */

#ifndef INCLUDE_COSM_STEER2D_CONFIG_XML_ARRIVAL_FORCE_PARSER_HPP_
#define INCLUDE_COSM_STEER2D_CONFIG_XML_ARRIVAL_FORCE_PARSER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <memory>

#include "rcppsw/rcppsw.hpp"
#include "rcppsw/config/xml/xml_config_parser.hpp"
#include "cosm/steer2D/config/arrival_force_config.hpp"

/*******************************************************************************
 * Namespaces/Decls
 ******************************************************************************/
NS_START(cosm, steer2D, config, xml);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * \class arrival_force_parser
 * \ingroup steer2D config xml
 *
 * \brief Parses XML configuration for \ref arrival_force into \ref
 * arrival_force_config. Assumes it is handed an XML parent in which the child
 * tag \ref kXMLRoot is found.
 *
 * Parameter tags under the XML root are expected to exactly match the names of
 * the fields in the \ref arrival_force_config struct.
 */
class arrival_force_parser final : public rconfig::xml::xml_config_parser {
 public:
  using config_type = arrival_force_config;

  /**
   * \brief The XML root tag that all \ref arrival_force configuration should
   * lie under in the XML tree.
   */
  static constexpr const char kXMLRoot[] = "arrival_force";

  void parse(const ticpp::Element& node) override RCSW_COLD;
  bool validate(void) const override RCSW_ATTR(pure, cold);

  RCSW_COLD std::string xml_root(void) const override { return kXMLRoot; }

 private:
  RCSW_COLD const rconfig::base_config* config_get_impl(void) const override {
    return m_config.get();
  }

  /* clang-format off */
  std::unique_ptr<config_type> m_config{nullptr};
  /* clang-format on */
};

NS_END(xml, config, psteer2D, cosm);

#endif /* INCLUDE_COSM_STEER2D_CONFIG_XML_ARRIVAL_FORCE_PARSER_HPP_ */
