/**
 * \file task_visualizer.hpp
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
#ifndef INCLUDE_COSM_VIS_TASK_VISUALIZER_HPP_
#define INCLUDE_COSM_VIS_TASK_VISUALIZER_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "rcppsw/er/client.hpp"

#include "cosm/cosm.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace argos {
class CQTOpenGLUserFunctions;
}
NS_START(cosm);
namespace ta {
class logical_task;
} /* namespace ta */
NS_START(vis);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * \class task_visualizer
 * \ingroup cosm vis
 *
 * \brief Renders the task that a robot is currently executing in text above the
 * robot for visualization/debugging purposes.
 */
class task_visualizer : public rer::client<task_visualizer> {
 public:
  task_visualizer(argos::CQTOpenGLUserFunctions* qt, double text_vis_offset)
      : ER_CLIENT_INIT("cosm.vis.task_visualizer"),
        m_text_vis_offset(text_vis_offset),
        m_qt(qt) {}

  task_visualizer(const task_visualizer& op) = delete;
  task_visualizer& operator=(const task_visualizer& op) = delete;

  /**
   * \brief Draw visualizations related to task execution:
   *
   * - The task name
   *
   * \param current_task The current task the robot is executing.
   */
  void draw(const ta::logical_task* current_task);

  /* clang-format off */
  double                               m_text_vis_offset{0.0};
  argos::CQTOpenGLUserFunctions* const m_qt{nullptr};
  /* clang-format on */
};

NS_END(cosm, vis);

#endif /* INCLUDE_COSM_VIS_TASK_VISUALIZER_HPP_ */
