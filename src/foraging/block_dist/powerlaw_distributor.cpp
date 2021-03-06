/**
 * \file powerlaw_distributor.cpp
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
#include "cosm/foraging/block_dist/powerlaw_distributor.hpp"

#include <algorithm>
#include <cmath>

#include "cosm/ds/arena_grid.hpp"
#include "cosm/foraging/config/block_dist_config.hpp"
#include "cosm/repr/base_block2D.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, foraging, block_dist);
using cosm::ds::arena_grid;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
template<typename TBlockType>
powerlaw_distributor<TBlockType>::powerlaw_distributor(
    const config::powerlaw_dist_config* const config,
    const rtypes::discretize_ratio& resolution,
    rmath::rng* rng_in)
    : ER_CLIENT_INIT("cosm.foraging.block_dist.powerlaw"),
      base_distributor<TBlockType>(rng_in),
      mc_resolution(resolution),
      m_n_clusters(config->n_clusters),
      m_pwrdist(config->pwr_min, config->pwr_max, 2) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
template<typename TBlockType>
bool powerlaw_distributor<TBlockType>::distribute_block(TBlockType* block,
                                               cds::const_entity_vector& entities) {
  /*
   * If we get here than either all clusters of the specified capacity are
   * full and/or one or more are not full but have additional entities
   * contained within their boundaries that are taking up space (i.e. caches).
   *
   * So, change cluster size and try again.
   */
  for (auto& l : m_dist_map) {
    for (auto& dist : l.second) {
      ER_INFO(
          "Attempting distribution: block%d -> cluster [capacity=%u,count=%zu]",
          block->id().v(),
          l.first,
          dist.block_clusters().front()->block_count());

      if (dist.distribute_block(block, entities)) {
        return true;
      }
    } /* for(&dist..) */
  }   /* for(l..) */

  ER_FATAL_SENTINEL("Unable to distribute block to any cluster");
  return false;
} /* distribute_block() */

template<typename TBlockType>
typename powerlaw_distributor<TBlockType>::cluster_paramvec powerlaw_distributor<TBlockType>::guess_cluster_placements(
    cds::arena_grid* const grid,
    const std::vector<uint>& clust_sizes) {
  cluster_paramvec config;

  for (size_t i = 0; i < clust_sizes.size(); ++i) {
    uint x = rng()->uniform(clust_sizes[i] / 2 + 1,
                            grid->xdsize() - clust_sizes[i] / 2 - 1);
    uint y = rng()->uniform(clust_sizes[i] / 2 + 1,
                            grid->ydsize() - clust_sizes[i] / 2 - 1);
    uint x_max = x + static_cast<uint>(std::sqrt(clust_sizes[i]));
    uint y_max = y + clust_sizes[i] / (x_max - x);

    /*
     * Cast needed so that clusters can correctly be constructed later, and they
     * DO need to be able to modify their grid view. Here we do not need it, so
     * we have to cast.
     */
    auto view = grid->layer<arena_grid::kCell>()->subgrid(rmath::vector2z(x, x_max),
                                                          rmath::vector2z(y, y_max));
    RCSW_UNUSED rmath::vector2z loc = (*view.origin()).loc();
    ER_TRACE("Guess cluster%zu placement x=[%lu-%lu], y=[%lu-%lu], size=%u",
             i,
             loc.x() + view.index_bases()[0],
             loc.x() + view.index_bases()[0] + view.shape()[0],
             loc.y() + view.index_bases()[1],
             loc.y() + view.index_bases()[1] + view.shape()[1],
             clust_sizes[i]);
    config.push_back({view, clust_sizes[i]});
  } /* for(i..) */
  return config;
} /* guess_cluster_placements() */

template<typename TBlockType>
bool powerlaw_distributor<TBlockType>::check_cluster_placements(const cluster_paramvec& pvec) {
  for (const cluster_config& p : pvec) {
    bool overlap = std::any_of(pvec.begin(), pvec.end(), [&](const auto& other) {
      /*
         * Can't compare directly (boost multi_array makes a COPY of each
         * element during iteration for some reason, and because the cells
         * have a unique_ptr, that doesn't work), so compare using addresses
         * of elements of the vector, which WILL work.
         */
      if (&other == &p) { /* self */
        return false;
      }
      rmath::vector2z v_loc = (*p.view.origin()).loc();
      rmath::vector2z other_loc = (*other.view.origin()).loc();
      rmath::rangeu v_xrange(v_loc.x() + p.view.index_bases()[0],
                             v_loc.x() + p.view.index_bases()[0] +
                                 p.view.shape()[0]);
      rmath::rangeu v_yrange(v_loc.y() + p.view.index_bases()[1],
                             v_loc.y() + p.view.index_bases()[1] +
                                 p.view.shape()[1]);
      rmath::rangeu other_xrange(other_loc.x() + other.view.index_bases()[0],
                                 other_loc.x() + other.view.index_bases()[0] +
                                     other.view.shape()[0]);
      rmath::rangeu other_yrange(other_loc.y() + other.view.index_bases()[1],
                                 other_loc.y() + other.view.index_bases()[1] +
                                     other.view.shape()[1]);

      return v_xrange.overlaps_with(other_xrange) &&
             v_yrange.overlaps_with(other_yrange);
    });
    if (overlap) {
      return false;
    }
  } /* for(&p..) */
  return true;
} /* check_cluster_placements() */

template<typename TBlockType>
typename powerlaw_distributor<TBlockType>::cluster_paramvec powerlaw_distributor<TBlockType>::
    compute_cluster_placements(cds::arena_grid* const grid, uint n_clusters) {
  ER_INFO("Computing cluster placements for %u clusters", n_clusters);

  std::vector<uint> clust_sizes;
  for (uint i = 0; i < n_clusters; ++i) {
    /* can't have a cluster of size 0 */
    uint index = static_cast<uint>(std::max(1.0, m_pwrdist(rng())));
    ER_DEBUG("Cluster%u size=%u", i, index);
    clust_sizes.push_back(index);
  } /* for(i..) */

  for (uint i = 0; i < kMAX_DIST_TRIES; ++i) {
    auto views = guess_cluster_placements(grid, clust_sizes);
    if (check_cluster_placements(views)) {
      return views;
    }
  } /* for(i..) */
  ER_FATAL_SENTINEL(
      "Unable to place clusters in arena (impossible situation?)");
  return cluster_paramvec{};
} /* compute_cluster_placements() */

template<typename TBlockType>
bool powerlaw_distributor<TBlockType>::map_clusters(cds::arena_grid* const grid) {
  cluster_paramvec config = compute_cluster_placements(grid, m_n_clusters);
  if (config.empty()) {
    ER_WARN("Unable to compute all cluster placements");
    return false;
  }

  for (auto& bclustp : config) {
    m_dist_map[bclustp.capacity].emplace_back(
        bclustp.view, mc_resolution, bclustp.capacity, rng());
  } /* for(i..) */
  for (auto& [clust_size, dist_list] : m_dist_map) {
    ER_INFO("Mapped %zu clusters of capacity %u", dist_list.size(), clust_size);
    for (RCSW_UNUSED auto& dist : dist_list) {
      ER_INFO("Cluster with origin@%s/%s: capacity=%u",
              dist.block_clusters().front()->rloc2D().to_str().c_str(),
              dist.block_clusters().front()->dloc2D().to_str().c_str(),
              dist.block_clusters().front()->capacity());
    } /* for(dist..) */
  }   /* for(&l..) */
  return true;
} /* map_clusters() */

template<typename TBlockType>
ds::block_cluster_vector<TBlockType> powerlaw_distributor<TBlockType>::block_clusters(void) const {
  ds::block_cluster_vector<TBlockType> ret;

  for (auto& l : m_dist_map) {
    for (auto& dist : l.second) {
      auto bclusts = dist.block_clusters();
      ret.insert(ret.end(), bclusts.begin(), bclusts.end());
    } /* for(&d..) */
  }   /* for(i..) */

  return ret;
} /* block_clusters() */

/*******************************************************************************
 * Template Instantiations
 ******************************************************************************/
template class powerlaw_distributor<crepr::base_block2D>;
template class powerlaw_distributor<crepr::base_block3D>;

NS_END(block_dist, foraging, cosm);
