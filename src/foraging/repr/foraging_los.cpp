/**
 * \file foraging_los.cpp
 *
 * \copyright 2017 John Harwell, All rights reserved.
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
 *****************************************************************************/
#include "cosm/foraging/repr/foraging_los.hpp"

#include "cosm/ds/cell2D.hpp"
#include "cosm/arena/repr/arena_cache.hpp"

/*******************************************************************************
 * Namespaces/Decls
 ******************************************************************************/
NS_START(cosm, foraging, repr);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
cds::entity_vector foraging_los::blocks(void) const {
  cds::entity_vector blocks{};
  for (uint i = 0; i < xsize(); ++i) {
    for (uint j = 0; j < ysize(); ++j) {
      const cds::cell2D& cell = mc_view[i][j];
      if (cell.state_has_block()) {
        ER_ASSERT(nullptr != cell.block2D() || nullptr != cell.block3D(),
                  "Cell at(%u,%u) in HAS_BLOCK state, but does not have block",
                  i,
                  j);
        blocks.push_back(cell.entity());
      }
    } /* for(j..) */
  }   /* for(i..) */
  return blocks;
} /* blocks() */

cads::bcache_vectorno foraging_los::caches(void) const {
  cads::bcache_vectorno caches;

  for (uint i = 0; i < xsize(); ++i) {
    for (uint j = 0; j < ysize(); ++j) {
      const cds::cell2D& cell = mc_view[i][j];
      if (cell.state_has_cache() || cell.state_in_cache_extent()) {
        auto cache = cell.cache();
        ER_ASSERT(
            nullptr != cache,
            "Cell@%s in HAS_CACHE/CACHE_EXTENT state, but does not have cache",
            cell.loc().to_str().c_str());
        ER_ASSERT(cache->n_blocks() >= carepr::base_cache::kMinBlocks,
                  "Cache%d@%s has too few blocks (%zu < %zu)",
                  cache->id().v(),
                  cache->dloc().to_str().c_str(),
                  cache->n_blocks(),
                  carepr::base_cache::kMinBlocks);
        /*
         * We can't add the cache unconditionally, because cache host cells and
         * extent cells both refer to the same cache, and doing so will give you
         * double references to a single cache in a LOS, which can cause
         * problems with pheromone updating. See #433.
         */
        if (caches.end() == std::find(caches.begin(), caches.end(), cache)) {
          caches.push_back(cache);
        }
      }
    } /* for(j..) */
  }   /* for(i..) */

  return caches;
} /* caches() */

bool foraging_los::contains_loc(const rmath::vector2z& loc) const {
  for (size_t i = 0; i < xsize(); ++i) {
    for (size_t j = 0; j < ysize(); ++j) {
      if (cell(i, j).loc() == loc) {
        return true;
      }
    } /* for(j..) */
  }   /* for(i..) */
  return false;
} /* contains_loc() */

const cds::cell2D& foraging_los::cell(uint i, uint j) const {
  ER_ASSERT(i < mc_view.shape()[0],
            "Out of bounds X access: %u >= %lu",
            i,
            mc_view.shape()[0]);
  ER_ASSERT(j < mc_view.shape()[1],
            "Out of bounds Y access: %u >= %lu",
            j,
            mc_view.shape()[1]);
  return mc_view[i][j];
}

rmath::vector2z foraging_los::abs_ll(void) const {
  return cell(0, 0).loc();
} /* abs_ll() */

rmath::vector2z foraging_los::abs_ul(void) const {
  return cell(0, ysize() - 1).loc();
} /* abs_ul() */

rmath::vector2z foraging_los::abs_lr(void) const {
  return cell(xsize() - 1, 0).loc();
} /* abs_lr() */

rmath::vector2z foraging_los::abs_ur(void) const {
  return cell(xsize() - 1, ysize() - 1).loc();
} /* abs_ur() */

NS_END(repr, foraging, cosm);
