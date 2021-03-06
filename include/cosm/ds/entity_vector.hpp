/**
 * \file entity_vector.hpp
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

#ifndef INCLUDE_COSM_DS_ENTITY_VECTOR_HPP_
#define INCLUDE_COSM_DS_ENTITY_VECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

#include "cosm/cosm.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace cosm::repr {
class unicell_entity2D;
class unicell_entity3D;
class entity_base;
} // namespace cosm::repr

NS_START(cosm, ds);

using entity2D_vector_type = crepr::unicell_entity2D*;
using const_entity2D_vector_type = const crepr::unicell_entity2D*;

using entity3D_vector_type = crepr::unicell_entity3D*;
using const_entity3D_vector_type = const crepr::unicell_entity3D*;

using entity_vector_type = crepr::entity_base*;
using const_entity_vector_type = const crepr::entity_base*;

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
using entity2D_vector = std::vector<entity2D_vector_type>;
using const_entity2D_vector = std::vector<const_entity2D_vector_type>;

using entity3D_vector = std::vector<entity3D_vector_type>;
using const_entity3D_vector = std::vector<const_entity3D_vector_type>;

using entity_vector = std::vector<entity_vector_type>;
using const_entity_vector = std::vector<const_entity_vector_type>;

NS_END(ds, cosm);

#endif /* INCLUDE_COSM_DS_ENTITY_VECTOR_HPP_ */
