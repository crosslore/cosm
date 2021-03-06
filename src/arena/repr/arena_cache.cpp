/**
 * \file arena_cache.cpp
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
#include "cosm/arena/repr/arena_cache.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, arena, repr);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
arena_cache::arena_cache(const base_cache::params& p,
                         const rutils::color& light_color)
    : base_cache(p),
      m_light(
          new argos::CLightEntity("cache_light" + rcppsw::to_string(id()),
                                  argos::CVector3(rloc().x(), rloc().y(), 0.0),
                                  argos::CColor(light_color.red(),
                                                light_color.green(),
                                                light_color.blue()),
                                  1.0)) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void arena_cache::reset_metrics(void) {
  m_block_pickups = 0;
  m_block_drops = 0;
  m_penalty_count = rtypes::timestep(0);
} /* reset_metrics() */

NS_END(repr, arena, cosm);
