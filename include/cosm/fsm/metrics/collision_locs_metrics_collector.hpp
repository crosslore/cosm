/**
 * \file collision_locs_metrics_collector.hpp
 *
 * \copyright 2019 John Harwell, All rights reserved.
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

#ifndef INCLUDE_COSM_FSM_METRICS_COLLISION_LOCS_METRICS_COLLECTOR_HPP_
#define INCLUDE_COSM_FSM_METRICS_COLLISION_LOCS_METRICS_COLLECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <list>

#include "rcppsw/metrics/spatial/grid2D_metrics_collector.hpp"
#include "cosm/cosm.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, fsm, metrics);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class collision_locs_metrics_collector
 * \ingroup fsm metrics
 *
 * \brief Collector for \ref collision_metrics as a 2D grid of where robots
 * most frequently encounter other robots.
 *
 * Metrics MUST be collected serially; concurrent updates to the gathered stats
 * are not supported.
 */
class collision_locs_metrics_collector final : public rmetrics::spatial::grid2D_metrics_collector<rmetrics::spatial::cell_avg> {
 public:
  /**
   * \param ofname The output file name.
   * \param interval Collection interval.
   * \param dims Dimensions of the arena.
   * \param mode The selected output mode.
   */
  collision_locs_metrics_collector(const std::string& ofname,
                                   const rtypes::timestep& interval,
                                   const rmetrics::output_mode& mode,
                                   const rmath::vector2z& dims) :
      grid2D_metrics_collector(ofname, interval, mode, dims) {}

  void collect(const rmetrics::base_metrics& metrics) override;
};

NS_END(metrics, fsm, cosm);

#endif /* INCLUDE_COSM_FSM_METRICS_COLLISION_LOCS_METRICS_COLLECTOR_HPP_ */
