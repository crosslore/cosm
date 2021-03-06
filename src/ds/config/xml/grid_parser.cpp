/**
 * \file grid_parser.cpp
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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "cosm/ds/config/xml/grid_parser.hpp"

#include "rcppsw/utils/line_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, ds, config, xml);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void grid_parser::parse(const ticpp::Element& node) {
  /*
   * May not exist if we are parsing part of an XML tree for perception that
   * does not use grids.
   */
  if (nullptr != node.FirstChild(kXMLRoot, false)) {
    ticpp::Element gnode = node_get(node, kXMLRoot);
    m_config = std::make_unique<config_type>();

    std::vector<std::string> res;
    rcppsw::utils::line_parser parser(' ');
    res = parser.parse(gnode.GetAttribute("size"));

    XML_PARSE_ATTR(gnode, m_config, resolution);
    m_config->lower.set(0, 0);
    m_config->upper.set(std::atoi(res[0].c_str()), std::atoi(res[1].c_str()));
  }
} /* parse() */

bool grid_parser::validate(void) const {
  RCSW_CHECK(m_config->resolution.v() > 0.0);
  RCSW_CHECK(m_config->upper.x() > 0.0);
  RCSW_CHECK(m_config->upper.y() > 0.0);
  return true;

error:
  return false;
} /* validate() */

NS_END(xml, config, ds, cosm);
