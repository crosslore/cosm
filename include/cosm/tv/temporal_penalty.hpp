/**
 * \file temporal_penalty.hpp
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

#ifndef INCLUDE_COSM_TV_TEMPORAL_PENALTY_HPP_
#define INCLUDE_COSM_TV_TEMPORAL_PENALTY_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "cosm/cosm.hpp"
#include "rcppsw/types/timestep.hpp"
#include "rcppsw/types/type_uuid.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace cosm::controller {
class base_controller;
} /* namespace cosm::controller */

NS_START(cosm, tv);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class temporal_penalty
 * \ingroup tv
 *
 * \brief Handles subjecting a robot to a penalty when doing something via a
 * timeout in which the robot will sit still.
 */
class temporal_penalty {
 public:
  /**
   * \brief Initialize the penalty.
   *
   * \param controller The controller for the robot being subjected to the
   *                   penalty.
   * \param id The ID to associate with the penalty.
   * \param penalty The # of timesteps for the penalty.
   * \param start_time The timestep the penalty will start on.
   */
  temporal_penalty(const controller::base_controller* const controller,
                   const rtypes::type_uuid& id,
                   const rtypes::timestep& penalty,
                   const rtypes::timestep& start_time)
      : mc_id(id),
        mc_penalty(penalty),
        mc_start_time(start_time),
        mc_controller(controller) {}

  const controller::base_controller* controller(void) const {
    return mc_controller;
  }
  const rtypes::timestep& start_time(void) const { return mc_start_time; }
  const rtypes::timestep& penalty(void) const { return mc_penalty; }
  const rtypes::type_uuid& id(void) const { return mc_id; }

  bool operator==(const temporal_penalty& other) {
    return this->controller() == other.controller();
  }

  /**
   * \brief If \c TRUE, then the robot has satisfied the block_manipulation
   * penalty.
   */
  bool penalty_satisfied(const rtypes::timestep& current_time) const {
    return current_time - mc_start_time >= mc_penalty;
  }

 private:
  /* clang-format off */
  const rtypes::type_uuid            mc_id;
  const rtypes::timestep             mc_penalty;
  const rtypes::timestep             mc_start_time;
  const controller::base_controller* mc_controller;
  /* clang-format on */
};

NS_END(tv, cosm);

#endif /* INCLUDE_COSM_TV_TEMPORAL_PENALTY_HPP_ */
