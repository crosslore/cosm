/**
 * \file arena_map_locking.hpp
 *
 * \copyright 2020 John Harwell, All rights reserved.
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

#ifndef INCLUDE_COSM_ARENA_ARENA_MAP_LOCKING_HPP_
#define INCLUDE_COSM_ARENA_ARENA_MAP_LOCKING_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcppsw/common/common.hpp"
#include "rcppsw/utils/maskable_enum.hpp"

/*******************************************************************************
 * Namespaces/Decls
 ******************************************************************************/
NS_START(cosm, arena);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
enum class arena_map_locking {
  ekNONE_HELD = 1 << 0,
  ekBLOCKS_HELD = 1 << 1,
  ekCACHES_HELD = 1 << 2,
  ekGRID_HELD = 1 << 3,
  ekALL_HELD = ekNONE_HELD | ekBLOCKS_HELD | ekCACHES_HELD | ekGRID_HELD
};
NS_END(arena, cosm);

#endif /* INCLUDE_COSM_ARENA_ARENA_MAP_LOCKING_HPP_ */
