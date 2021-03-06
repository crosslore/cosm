/**
 * \file dist2D_metrics.hpp
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

#ifndef INCLUDE_COSM_METRICS_SPATIAL_DIST2D_METRICS_HPP_
#define INCLUDE_COSM_METRICS_SPATIAL_DIST2D_METRICS_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcppsw/math/vector2.hpp"
#include "rcppsw/metrics/base_metrics.hpp"
#include "rcppsw/rcppsw.hpp"
#include "rcppsw/math/radians.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, metrics, spatial);

/******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * \class dist2D_metrics
 * \ingroup metrics spatial
 *
 * \brief Defines the metrics to be collected from swarms regarding spatial
 * distributions of robots within 2D space.
 */
class dist2D_metrics : public virtual rmetrics::base_metrics {
 public:
  dist2D_metrics(void) = default;

  /**
   * \brief Return a single robot's current position in 2D space in real
   * coordinates.
   */
  virtual rmath::vector2d pos2D(void) const = 0;

  /**
   * \brief Return a single robot's discretized position in 2D space.
   */
  virtual rmath::vector2z dpos2D(void) const = 0;

  /**
   * \brief Return a single robot's current heading in 2D space.
   */
  virtual rmath::radians heading2D(void) const = 0;
};

NS_END(spatial, metrics, cosm);

#endif /* INCLUDE_COSM_METRICS_spatial_DIST2D_METRICS_HPP_ */
