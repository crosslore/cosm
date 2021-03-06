/**
 * \file base_sm_repository.cpp
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
#include "cosm/pal/config/xml/base_sm_repository.hpp"

#include "rcppsw/control/config/xml/waveform_parser.hpp"

#include "cosm/convergence/config/xml/convergence_parser.hpp"
#include "cosm/arena/config/xml/arena_map_parser.hpp"
#include "cosm/metrics/config/xml/output_parser.hpp"
#include "cosm/oracle/config/xml/aggregate_oracle_parser.hpp"
#include "cosm/tv/config/xml/population_dynamics_parser.hpp"
#include "cosm/vis/config/xml/visualization_parser.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, pal, config, xml);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
base_sm_repository::base_sm_repository(void) noexcept {
  parser_register<cmconfig::xml::output_parser, cmconfig::output_config>(
      cmconfig::xml::output_parser::kXMLRoot);
  parser_register<caconfig::xml::arena_map_parser, caconfig::arena_map_config>(
      caconfig::xml::arena_map_parser::kXMLRoot);
  parser_register<cvconfig::xml::visualization_parser,
                  cvconfig::visualization_config>(
      cvconfig::xml::visualization_parser::kXMLRoot);

  parser_register<coconfig::xml::aggregate_oracle_parser,
                  coconfig::aggregate_oracle_config>(
      coconfig::xml::aggregate_oracle_parser::kXMLRoot);
  parser_register<cconvergence::config::xml::convergence_parser,
                  cconvergence::config::convergence_config>(
      cconvergence::config::xml::convergence_parser::kXMLRoot);

  parser_register<ctv::config::xml::population_dynamics_parser,
                  ctv::config::population_dynamics_config>(
      ctv::config::xml::population_dynamics_parser::kXMLRoot);
}

NS_END(xml, config, pal, cosm);
