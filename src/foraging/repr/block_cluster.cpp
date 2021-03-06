/**
 * \file block_cluster.cpp
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
#include "cosm/foraging/repr/block_cluster.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, foraging, repr);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
template<typename TBlockType>
typename block_cluster<TBlockType>::block_vectorro_type block_cluster<TBlockType>::blocks(void) const {
  block_vectorro_type ret;
  for (uint i = 0; i < xdimd(); ++i) {
    for (uint j = 0; j < ydimd(); ++j) {
      auto& cell = block_cluster::cell(i, j);
      ER_ASSERT(!cell.state_has_cache(),
                "Cell@%s in HAS_CACHE state",
                cell.loc().to_str().c_str());
      ER_ASSERT(!cell.state_in_cache_extent(),
                "Cell@%s in CACHE_EXTENT state",
                cell.loc().to_str().c_str());
      if constexpr (std::is_same<TBlockType, crepr::base_block2D>::value) {
          if (cell.state_has_block()) {
            ER_ASSERT(nullptr != cell.block2D(),
                      "Cell@%s null block2D",
                      cell.loc().to_str().c_str());
            ret.push_back(cell.block2D());
          }
        } else if constexpr (std::is_same<TBlockType, crepr::base_block2D>::value) {
          if (cell.state_has_block()) {
            ER_ASSERT(nullptr != cell.block3D(),
                      "Cell@%s null block3D",
                      cell.loc().to_str().c_str());
            ret.push_back(cell.block3D());
          }
        }
    } /* for(j..) */
  }   /* for(i..) */
  return ret;
} /* blocks() */

/*******************************************************************************
 * Template Instantiations
 ******************************************************************************/
template class block_cluster<crepr::base_block2D>;
template class block_cluster<crepr::base_block3D>;

NS_END(repr, foraging, cosm);
