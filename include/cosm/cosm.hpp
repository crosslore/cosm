/**
 * \file cosm.hpp
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

#ifndef INCLUDE_COSM_COSM_HPP_
#define INCLUDE_COSM_COSM_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcppsw/rcppsw.hpp"

#include "cosm/config.hpp"

/*******************************************************************************
 * Namespaces/Decls
 ******************************************************************************/
/**
 * \defgroup cosm cosm
 * \brief The root namespace for COSM.
* @{
*
* It is better to define the namespace aliases exported by COSM here, rather
* than having them be multiply defined in different downstream projects (DRY
* FTW!).
*
* Convention: Namespace aliases from cosm all start with \c 'c', and the first
* letter of all nested namespaces except the innermost one should be included
* before the innermost. For example, cosm::fsm::metrics should have the \c 'c'
* from \c 'cosm' and the \c 'f' from 'fsm' before the target namespace \c
* 'metrics'.
*
* \defgroup tv tv
* \brief Temporal variance applicators.
*
* \defgroup subsystem subsystem
* \brief Robotic susbystems.
*
* \defgroup hal hal
* \brief Hardware Abstraction Layer
*
* \defgroup kin2D kin2D
* \brief 2D kinematics for wheeled robots.
*
* \defgroup steer2D steer2D
* \brief Steering forces for 2D wheeled robots.
*
* \defgroup convergence convergence
* \brief Swarm convergence measures and calculators.
*
* \defgroup metrics metrics
* \brief Reusable metric interfaces and collectors for robotics.
*
* \defgroup repr repr
* \brief Representation of STUFF that is not strictly a data structure,
*        mathematical construct, etc., but that is used to model things in the
*        real world.
*
* \defgroup controller controller
* \brief Robot controllers.
*
* \defgroup robots robots
* \brief Adaptor layer containing specializations/extensions of controllers,
*        subsystems, etc., that are specific to a particular robot model.
* @{
*
* \defgroup footbot footbot
* \brief Adaptation layer to the ARGoS footbot robot.
*
* @}
*
* \defgroup fsm fsm
* \brief Reusable FSMs not specific to any particular application within swarm
*        robotics.
* @{
*
* \defgroup metrics metrics
* \brief General purpose metric interfaces and collectors for FSMs.
*
* \defgroup vis vis
* \brief Qt visualization bindings.
* @}
*/
namespace cosm {
namespace tv {
namespace metrics {}
} /* namespace tv */

namespace subsystem {}
namespace hal {}
namespace kin2D {}
namespace steer2D {}

namespace convergence {
namespace config {}
}

namespace metrics {
namespace config {}
} /* namespace metrics */

namespace repr {}
namespace controller {
namespace operations {}
namespace metrics {}
} /* namespace controller */

namespace robots {
namespace footbot {}
} /* namespace robots */

namespace fsm {
namespace metrics {}
} /* namespace fsm */

namespace vis {
namespace config {}
} /* namespace vis */

namespace ds {
namespace config {}
namespace operations {}
} /* namespace ds */

namespace pal {
namespace config {}
namespace operations {}
namespace tv {}
} /* namespace pal */

namespace ta {
namespace metrics {}
} /* namespace ta */

namespace foraging {
namespace config {}
namespace block_dist {}
namespace repr {}
namespace ds {}
namespace operations {}
namespace utils {}
namespace oracle {}
} /* namespace foraging */

namespace arena {
namespace operations {}
namespace ds {}
namespace repr {}
namespace metrics {}
namespace config {}

} /* namespace arena */

namespace oracle {
namespace config {}
} /* namespace oracle */

namespace operations {}
} /* namespace cosm */

/** @} */

namespace csubsystem = cosm::subsystem;
namespace cops = cosm::operations;
namespace ccontroller = cosm::controller;
namespace ccops = ccontroller::operations;
namespace ccmetrics = ccontroller::metrics;
namespace cfsm = cosm::fsm;
namespace chal = cosm::hal;
namespace ckin2D = cosm::kin2D;
namespace csteer2D = cosm::steer2D;
namespace crobots = cosm::robots;
namespace crfootbot = crobots::footbot;
namespace ctv = cosm::tv;
namespace cds = cosm::ds;
namespace cdconfig = cds::config;
namespace cdops = cds::operations;
namespace cconvergence = cosm::convergence;
namespace ccconfig = cconvergence::config;
namespace cmetrics = cosm::metrics;
namespace cmconfig = cmetrics::config;
namespace ctv = cosm::tv;
namespace cforaging = cosm::foraging;
namespace cfrepr = cforaging::repr;
namespace cforacle = cforaging::oracle;
namespace cfutils = cforaging::utils;
namespace cfds = cforaging::ds;
namespace cfops = cforaging::operations;
namespace carena = cosm::arena;
namespace cads = carena::ds;
namespace caconfig = carena::config;
namespace cametrics = carena::metrics;
namespace carepr = carena::repr;
namespace caops = carena::operations;
namespace cfconfig = cforaging::config;
namespace cfbd = cforaging::block_dist;
namespace ctvmetrics = ctv::metrics;
namespace crepr = cosm::repr;
namespace cvis = cosm::vis;
namespace cvconfig = cvis::config;
namespace cpal = cosm::pal;
namespace cpops = cpal::operations;
namespace cpconfig = cpal::config;
namespace cptv = cpal::tv;
namespace coracle = cosm::oracle;
namespace coconfig = coracle::config;
namespace cta = cosm::ta;
namespace ctametrics = cta::metrics;

#endif /* INCLUDE_COSM_COSM_HPP_ */
