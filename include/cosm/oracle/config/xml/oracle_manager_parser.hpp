/**
 * \file oracle_manager_parser.hpp
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

#ifndef INCLUDE_COSM_ORACLE_CONFIG_XML_ORACLE_MANAGER_PARSER_HPP_
#define INCLUDE_COSM_ORACLE_CONFIG_XML_ORACLE_MANAGER_PARSER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <memory>

#include "cosm/oracle/config/oracle_manager_config.hpp"
#include "rcppsw/config/xml/xml_config_parser.hpp"
#include "cosm/oracle/config/xml/entities_oracle_parser.hpp"
#include "cosm/oracle/config/xml/tasking_oracle_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, oracle, config, xml);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class oracle_manager_parser
 * \ingroup oracle config xml
 *
 * \brief Parses XML parameters used for oracles at the start of simulation.
 */
class oracle_manager_parser final : public rconfig::xml::xml_config_parser {
 public:
  using config_type = oracle_manager_config;

  /**
   * \brief The root tag that all cache parameters should lie under in the
   * XML tree.
   */
  static constexpr char kXMLRoot[] = "oracle_manager";

  void parse(const ticpp::Element& node) override RCSW_COLD;
  bool validate(void) const override RCSW_ATTR(const, cold);

  RCSW_COLD std::string xml_root(void) const override { return kXMLRoot; }

 private:
  RCSW_COLD const rconfig::base_config* config_get_impl(void) const override {
    return m_config.get();
  }

  /* clang-format off */
  std::unique_ptr<config_type> m_config{nullptr};
  entities_oracle_parser       m_entities{};
  tasking_oracle_parser        m_tasking{};
  /* clang-format on */
};

NS_END(xml, config, oracle, cosm);

#endif /* INCLUDE_COSM_ORACLE_CONFIG_XML_ORACLE_MANAGER_PARSER_HPP_ */