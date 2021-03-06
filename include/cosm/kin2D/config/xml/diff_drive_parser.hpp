/**
 * \file diff_drive_parser.hpp
 *
 * \copyright 2018 John Harwell, All rights reserved.
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

#ifndef INCLUDE_COSM_KIN2D_CONFIG_XML_DIFF_DRIVE_PARSER_HPP_
#define INCLUDE_COSM_KIN2D_CONFIG_XML_DIFF_DRIVE_PARSER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <memory>

#include "cosm/kin2D/config/diff_drive_config.hpp"
#include "rcppsw/rcppsw.hpp"
#include "rcppsw/config/xml/xml_config_parser.hpp"

/*******************************************************************************
 * Namespaces/Decls
 ******************************************************************************/
NS_START(cosm, kin2D, config, xml);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * \class diff_drive_parser
 * \ingroup kin2D config xml
 *
 * \brief Parses XML configuration relating to the \ref diff_drive into
 * \ref diff_drive_config.
 */
class diff_drive_parser : public rconfig::xml::xml_config_parser {
 public:
  using config_type = diff_drive_config;

  /**
   * \brief The root tag that all diff drive configuration values
   * should lie under in the XML tree.
   */
  static constexpr const char kXMLRoot[] = "diff_drive";

  void parse(const ticpp::Element& node) override RCSW_COLD;
  bool validate(void) const override RCSW_ATTR(cold, pure);

  RCSW_COLD std::string xml_root(void) const override { return kXMLRoot; }

 private:
  RCSW_COLD rconfig::base_config* config_get_impl(void) const override {
    return m_config.get();
  }

  /* clang-format off */
  std::unique_ptr<config_type> m_config{nullptr};
  /* clang-format on */
};

NS_END(xml, config, kin2D, cosm);

#endif /* INCLUDE_COSM_KIN2D_CONFIG_XML_DIFF_DRIVE_PARSER_HPP_ */
