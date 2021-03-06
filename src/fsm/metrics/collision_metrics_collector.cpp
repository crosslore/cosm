/**
 * \file collision_metrics_collector.cpp
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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "cosm/fsm/metrics/collision_metrics_collector.hpp"

#include "cosm/fsm/metrics/collision_metrics.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, fsm, metrics);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
collision_metrics_collector::collision_metrics_collector(
    const std::string& ofname_stem,
    const rtypes::timestep& interval)
    : base_metrics_collector(ofname_stem,
                             interval,
                             rmetrics::output_mode::ekAPPEND) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
std::list<std::string> collision_metrics_collector::csv_header_cols(void) const {
  auto merged = dflt_csv_header_cols();
  auto cols = std::list<std::string>{
      /* clang-format off */
    "int_avg_in_avoidance",
    "cum_avg_in_avoidance",
    "int_avg_entered_avoidance",
    "cum_avg_entered_avoidance",
    "int_avg_exited_avoidance",
    "cum_avg_exited_avoidance",
    "int_avg_avoidance_duration",
    "cum_avg_avoidance_duration"
      /* clang-format on */
  };
  merged.splice(merged.end(), cols);
  return merged;
} /* csv_header_cols() */

void collision_metrics_collector::reset(void) {
  base_metrics_collector::reset();
  reset_after_interval();
} /* reset() */

void collision_metrics_collector::collect(const rmetrics::base_metrics& metrics) {
  auto& m = dynamic_cast<const collision_metrics&>(metrics);
  m_interval.n_in_avoidance += static_cast<uint>(m.in_collision_avoidance());
  m_cum.n_in_avoidance += static_cast<uint>(m.in_collision_avoidance());

  m_interval.n_entered_avoidance +=
      static_cast<uint>(m.entered_collision_avoidance());
  m_cum.n_entered_avoidance +=
      static_cast<uint>(m.entered_collision_avoidance());

  m_interval.n_exited_avoidance +=
      static_cast<uint>(m.exited_collision_avoidance());
  m_cum.n_exited_avoidance += static_cast<uint>(m.exited_collision_avoidance());

  if (m.exited_collision_avoidance()) {
    m_interval.avoidance_duration += m.collision_avoidance_duration().v();
    m_cum.avoidance_duration += m.collision_avoidance_duration().v();
  }
} /* collect() */

boost::optional<std::string> collision_metrics_collector::csv_line_build(void) {
  if (!(timestep() % interval() == 0)) {
    return boost::none;
  }
  std::string line;

  line += csv_entry_intavg(m_interval.n_in_avoidance.load());
  line += csv_entry_tsavg(m_cum.n_in_avoidance.load());
  line += csv_entry_intavg(m_interval.n_entered_avoidance.load());
  line += csv_entry_tsavg(m_cum.n_entered_avoidance.load());
  line += csv_entry_intavg(m_interval.n_exited_avoidance.load());
  line += csv_entry_tsavg(m_cum.n_exited_avoidance.load());
  line += csv_entry_intavg(m_interval.avoidance_duration.load());
  line += csv_entry_tsavg(m_cum.avoidance_duration.load(), true);

  return boost::make_optional(line);
} /* csv_line_build() */

void collision_metrics_collector::reset_after_interval(void) {
  m_interval.n_in_avoidance = 0;
  m_interval.n_entered_avoidance = 0;
  m_interval.n_exited_avoidance = 0;
  m_interval.avoidance_duration = 0;
} /* reset_after_interval() */

NS_END(metrics, fsm, cosm);
