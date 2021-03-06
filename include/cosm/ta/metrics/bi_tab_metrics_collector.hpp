/**
 * \file bi_tab_metrics_collector.hpp
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

#ifndef INCLUDE_COSM_TA_METRICS_BI_TAB_METRICS_COLLECTOR_HPP_
#define INCLUDE_COSM_TA_METRICS_BI_TAB_METRICS_COLLECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <list>
#include <atomic>

#include "rcppsw/metrics/base_metrics_collector.hpp"
#include "rcppsw/rcppsw.hpp"

/*******************************************************************************
 * Namespaces/Decls
 ******************************************************************************/
NS_START(cosm, ta, metrics);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class bi_tab_metrics_collector
 * \ingroup ta metrics
 *
 * \brief Collector for metrics for \ref bi_tab_metrics about task allocation.
 *
 * Metrics CAN be collected in parallel from robots; concurrent updates to the
 * gathered stats are supported. Metrics should only be collected upon
 * completion/abortion of a task. Metrics are written out at the specified
 * interval.
 */
class bi_tab_metrics_collector final : public rmetrics::base_metrics_collector {
 public:
  /**
   * \param ofname_stem Output file name stem.
   * \param interval Collection interval.
   */
  bi_tab_metrics_collector(const std::string& ofname_stem,
                           const rtypes::timestep& interval);

  void reset(void) override;
  void collect(const rmetrics::base_metrics& metrics) override;
  void reset_after_interval(void) override;

  std::list<std::string> csv_header_cols(void) const override;
  boost::optional<std::string> csv_line_build(void) override;

 private:
  struct stats {
    /**
     * \brief # Times subtask 1 was chosen if partitioning was employed.
     */
    std::atomic_uint   subtask1_count{0};

    /**
     * \brief # Times subtask 2 was chosen if partitioning was employed.
     */
    std::atomic_uint   subtask2_count{0};

    /**
     * \brief # Times partitioning was employed when allocating a task,
     */
    std::atomic_uint   partition_count{0};

    /**
     * \brief # Times partitioning was not employed when allocating a task.
     */
    std::atomic_uint   no_partition_count{0};

    /**
     * \brief # Times when task allocation resulted in a different task being
     * executed.
     */
    std::atomic_uint   task_sw_count{0};

    /**
     * \brief # Times when task allocation resulted in a task of a different
     * depth being executed than previous.
     */
    std::atomic_uint   task_depth_sw_count{0};


    /**
     * \brief The average partitioning probability of the root task in the TAB.
     */
    std::atomic<double> partition_prob{0.0};

    /**
     * \brief The average subtask selection probability of the root task in the
     * TAB.
     */
    std::atomic<double> subtask_sel_prob{0.0};
  };
  /* clang-format off */
  struct stats m_interval{};
  struct stats m_cum{};
  /* clang-format on */
};

NS_END(metrics, ta, cosm);


#endif /* INCLUDE_COSM_TA_METRICS_BI_TAB_METRICS_COLLECTOR_HPP_ */
