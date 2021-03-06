/**
 * \file block_cluster_vector.hpp
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

#ifndef INCLUDE_COSM_FORAGING_DS_BLOCK_CLUSTER_VECTOR_HPP_
#define INCLUDE_COSM_FORAGING_DS_BLOCK_CLUSTER_VECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>

#include "cosm/cosm.hpp"
#include "cosm/repr/base_block2D.hpp"
#include "cosm/repr/base_block3D.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, foraging);

namespace repr {
template<typename T>
class block_cluster;
} // namespace repr

NS_START(ds);

using block2D_cluster_vector_type = const cfrepr::block_cluster<crepr::base_block2D>*;
using block3D_cluster_vector_type = const cfrepr::block_cluster<crepr::base_block3D>*;

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
using block2D_cluster_vector = std::vector<block2D_cluster_vector_type>;
using block3D_cluster_vector = std::vector<block3D_cluster_vector_type>;

template<typename TBlockType>
using block_cluster_vector = std::vector<const cfrepr::block_cluster<TBlockType>*>;

NS_END(ds, foraging, cosm);

#endif /* INCLUDE_COSM_DS_BLOCK_CLUSTER_VECTOR_HPP_ */
