/**
 * \file argos_rda_adaptor.hpp
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

#ifndef INCLUDE_COSM_PAL_TV_ARGOS_RDA_ADAPTOR_HPP_
#define INCLUDE_COSM_PAL_TV_ARGOS_RDA_ADAPTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>

#include "rcppsw/er/client.hpp"

#include "cosm/tv/switchable_tv_generator.hpp"
#include "cosm/tv/robot_dynamics_applicator.hpp"
#include "cosm/cosm.hpp"
#include "cosm/pal/argos_sm_adaptor.hpp"
#include "cosm/pal/argos_swarm_iterator.hpp"
#include "cosm/controller/block_carrying_controller.hpp"
#include "cosm/controller/irv_recipient_controller.hpp"

/*******************************************************************************
 * Namespaces/Decls
 ******************************************************************************/
NS_START(cosm, pal, tv);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class argos_rda_adaptor
 * \ingroup pal
 *
 * \brief Adapts \ref ctv::robot_dynamics_applicator to work within the ARGoS
 * simulator.
 */
template<typename TControllerType>
class argos_rda_adaptor final : public rer::client<argos_rda_adaptor<TControllerType>>,
                                public ctv::robot_dynamics_applicator {
 public:
  static_assert(std::is_base_of<controller::irv_recipient_controller, TControllerType>::value,
                "TControllerType not derived from irv_recipient_controller");
  static_assert(std::is_base_of<controller::block_carrying_controller, TControllerType>::value,
                "TControllerType not derived from block_carrying_controller");

  argos_rda_adaptor(
      const ctv::config::robot_dynamics_applicator_config* config,
      const cpal::argos_sm_adaptor* const sm)
      : ER_CLIENT_INIT("cosm.pal.argos_rda_adaptor"),
        robot_dynamics_applicator(config),
        mc_sm(sm) {}

  argos_rda_adaptor(const argos_rda_adaptor&) = delete;
  const argos_rda_adaptor& operator=(const argos_rda_adaptor&) = delete;

  double avg_motion_throttle(void) const override {
    double accum = 0.0;
    auto cb = [&](auto& controller) {
      accum += controller->applied_movement_throttle();
    };

    cpal::argos_swarm_iterator::controllers<argos::CFootBotEntity,
                                            TControllerType,
                                            cpal::iteration_order::ekSTATIC>(
                                                mc_sm, cb, kARGoSRobotType);
    return accum / mc_sm->GetSpace().GetEntitiesByType(kARGoSRobotType).size();
  }

  void update(void) override {
    if (!motion_throttling_enabled()) {
      return;
    }
    rtypes::timestep t(mc_sm->GetSpace().GetSimulationClock());
    auto cb = [&](auto& controller) {
      motion_throttler(controller->entity_id())
      ->toggle(controller->is_carrying_block());
      motion_throttler(controller->entity_id())->update(t);
    };

    cpal::argos_swarm_iterator::controllers<argos::CFootBotEntity,
                                            TControllerType,
                                            cpal::iteration_order::ekSTATIC>(
                                                mc_sm, cb, kARGoSRobotType);
  }

 private:
  /* clang-format off */
  const cpal::argos_sm_adaptor* const mc_sm;
  /* clang-format on */
};

NS_END(tv, pal, cosm);

#endif /* INCLUDE_COSM_PAL_TV_ARGOS_RDA_ADAPTOR_HPP_ */
