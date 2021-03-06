/**
 * \file arena_map_parser.hpp
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

#ifndef INCLUDE_COSM_ARENA_CONFIG_XML_ARENA_MAP_PARSER_HPP_
#define INCLUDE_COSM_ARENA_CONFIG_XML_ARENA_MAP_PARSER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <memory>

#include "cosm/arena/config/arena_map_config.hpp"
#include "cosm/foraging/config/xml/blocks_parser.hpp"
#include "cosm/ds/config/xml/grid_parser.hpp"
#include "cosm/repr/config/xml/nest_parser.hpp"

#include "cosm/cosm.hpp"
#include "rcppsw/config/xml/xml_config_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, arena, config, xml);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class arena_map_parser
 * \ingroup arena config xml
 *
 * \brief Parses XML parameters for \ref arena_map into \ref arena_map_config.
 */
class arena_map_parser final : public rconfig::xml::xml_config_parser {
 public:
  using config_type = arena_map_config;

  /**
   * \brief The root tag that all arena map parameters should lie under in the
   * XML tree.
   */
  static constexpr const char kXMLRoot[] = "arena_map";

  void parse(const ticpp::Element& node) override RCSW_COLD;
  bool validate(void) const override RCSW_ATTR(cold, pure);

  RCSW_COLD std::string xml_root(void) const override { return kXMLRoot; }

 private:
  RCSW_COLD const rconfig::base_config* config_get_impl(void) const override {
    return m_config.get();
  }

  /* clang-format off */
  std::shared_ptr<config_type>    m_config{nullptr};
  cds::config::xml::grid_parser   m_grid{};
  cfconfig::xml::blocks_parser    m_blocks{};
  crepr::config::xml::nest_parser m_nest{};
  /* clang-format on */
};

NS_END(xml, config, arena, cosm);

#endif /* INCLUDE_COSM_ARENA_CONFIG_ML_ARENA_MAP_PARSER_HPP_ */
