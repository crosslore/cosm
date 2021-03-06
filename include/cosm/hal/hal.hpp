/**
 * \file hal.hpp
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

#ifndef INCLUDE_COSM_HAL_HAL_HPP_
#define INCLUDE_COSM_HAL_HAL_HPP_

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
/*
 * \brief The configuration definition to compile for the footbot robot within
 * the ARGoS simulator.
 */
#define HAL_TARGET_ARGOS_FOOTBOT 1

/*
 * \brief The configuration definition to compile for the Lego Mindstorm EV3
 * robot.
 */
#define HAL_TARGET_LEGO_EV3 2

#endif /* INCLUDE_COSM_HAL_HAL_HPP_ */
