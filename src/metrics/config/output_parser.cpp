/**
 * \file output_parser.cpp
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
#include "cosm/metrics/config/xml/output_parser.hpp"

#include "rcppsw/utils/line_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, metrics, config, xml);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void output_parser::parse(const ticpp::Element& node) {
  ticpp::Element onode = node_get(node, kXMLRoot);
  m_config = std::make_unique<config_type>();

  std::vector<std::string> res, res2;

  m_metrics_parser.parse(onode);
  if (m_metrics_parser.is_parsed()) {
    m_config->metrics =
        *m_metrics_parser.config_get<metrics_parser::config_type>();
  }

  XML_PARSE_ATTR(onode, m_config, output_root);
  XML_PARSE_ATTR(onode, m_config, output_dir);
} /* parse() */

bool output_parser::validate(void) const {
  return m_metrics_parser.validate();
} /* validate() */

NS_END(xml, config, metrics, cosm);
