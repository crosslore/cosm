/**
 * \file dispatcher.cpp
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
#include "cosm/foraging/block_dist/dispatcher.hpp"

#include <limits>

#include "cosm/foraging/block_dist/cluster_distributor.hpp"
#include "cosm/foraging/block_dist/multi_cluster_distributor.hpp"
#include "cosm/foraging/block_dist/powerlaw_distributor.hpp"
#include "cosm/foraging/block_dist/random_distributor.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, foraging, block_dist);
using cds::arena_grid;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
template<typename TBlockType>
dispatcher<TBlockType>::dispatcher(cds::arena_grid* const grid,
                                   const rtypes::discretize_ratio& resolution,
                                   const config::block_dist_config* const config,
                                   double grid_padding)
    : mc_grid_padding(grid_padding),
      mc_resolution(resolution),
      mc_config(*config),
      mc_dist_type(config->dist_type),
      /*
       * All sourced distributions can't occupy more than 70% of either the X or
       * Y dimension in order to avoid physics engine errors in ARGoS near arena
       * walls. See COSM#34. Also, the arena map has a padded grid to help with
       * LOS computation near arena boundaries, so we need to subtract padding
       * twice to get a grid that will be smaller than the arena walls so that
       * no blocks will be destributed ANYWHERE near physics engine/arena map
       * boundaries.
       */
      mc_arena_xrange(grid->xdsize() * 0.15,
                      (grid->xdsize() - mc_grid_padding * 2) * 0.85),
      mc_arena_yrange(grid->ydsize() * 0.15,
                      (grid->ydsize() - mc_grid_padding * 2) * 0.85),
      m_grid(grid),
      m_dist(nullptr) {}

template<typename TBlockType>
dispatcher<TBlockType>::~dispatcher(void) = default;

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
template<typename TBlockType>
bool dispatcher<TBlockType>::initialize(rmath::rng* rng) {
  /* clang-format off */
    cds::arena_grid::view arena = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb()),
                        static_cast<size_t>(mc_arena_yrange.lb())),
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.ub()),
                        static_cast<size_t>(mc_arena_yrange.ub())));

  if (kDistRandom == mc_dist_type) {
    m_dist = std::make_unique<random_distributor<TBlockType>>(arena,
                                                             mc_resolution,
                                                             rng);
  } else if (kDistSingleSrc == mc_dist_type) {
    cds::arena_grid::view area = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb() * 0.75 / 0.15),
                        static_cast<size_t>(mc_arena_xrange.ub())),
        rmath::vector2z(static_cast<size_t>(mc_arena_yrange.lb()),
                        static_cast<size_t>(mc_arena_yrange.ub())));
    m_dist = std::make_unique<cluster_distributor<TBlockType>>(
        area,
        mc_resolution,
        std::numeric_limits<uint>::max(),
        rng);
  } else if (kDistDualSrc == mc_dist_type) {
    cds::arena_grid::view area_l = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb()),
                        static_cast<size_t>(mc_arena_yrange.lb())),
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.ub() * 0.25 / 0.85),
                        static_cast<size_t>(mc_arena_yrange.ub())));
    cds::arena_grid::view area_r = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb() * 0.75 / 0.15),
                        static_cast<size_t>(mc_arena_yrange.lb())),
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.ub()),
                        static_cast<size_t>(mc_arena_yrange.ub())));
    std::vector<cds::arena_grid::view> grids{area_l, area_r};
    m_dist = std::make_unique<multi_cluster_distributor<TBlockType>>(
        grids,
        mc_resolution,
        std::numeric_limits<uint>::max(),
        rng);
  } else if (kDistQuadSrc == mc_dist_type) {
    /*
     * Quad source is a tricky distribution to use with static caches, so we
     * have to tweak the block cluster centers in tandem with the cache
     * locations to ensure that no segfaults result from cache/cache or
     * cache/cluster overlap. See FORDYCA#581, COSM#34.
     */
    cds::arena_grid::view area_l = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb()),
                        static_cast<size_t>(mc_arena_yrange.lb())),
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.ub() * 0.25 / 0.85),
                        static_cast<size_t>(mc_arena_yrange.ub())));
    cds::arena_grid::view area_r = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb() * 0.75 / 0.15),
                        static_cast<size_t>(mc_arena_yrange.lb())),
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.ub()),
                        static_cast<size_t>(mc_arena_yrange.ub())));
    cds::arena_grid::view area_b = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb()),
                        static_cast<size_t>(mc_arena_yrange.lb())),
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.ub()),
                        static_cast<size_t>(mc_arena_yrange.ub() * 0.25 / 0.85)));
    cds::arena_grid::view area_u = m_grid->layer<arena_grid::kCell>()->subgrid(
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.lb()),
                        static_cast<size_t>(mc_arena_yrange.lb() * 0.75 / 0.15)),
        rmath::vector2z(static_cast<size_t>(mc_arena_xrange.ub()),
                        static_cast<size_t>(mc_arena_yrange.ub())));
    std::vector<cds::arena_grid::view> grids{area_l, area_r, area_b, area_u};
    m_dist = std::make_unique<multi_cluster_distributor<TBlockType>>(
        grids,
        mc_resolution,
        std::numeric_limits<uint>::max(),
        rng);
  } else if (kDistPowerlaw == mc_dist_type) {
    auto p = std::make_unique<powerlaw_distributor<TBlockType>>(&mc_config.powerlaw,
                                                                mc_resolution,
                                                                rng);
    if (!p->map_clusters(m_grid)) {
      return false;
    }
    m_dist = std::move(p);
  }
  /* clang-format on */

  return true;
} /* initialize() */

template<typename TBlockType>
bool dispatcher<TBlockType>::distribute_block(TBlockType* block,
                                  cds::const_entity_vector& entities) {
  return m_dist->distribute_block(block, entities);
} /* distribute_block() */

template<typename TBlockType>
bool dispatcher<TBlockType>::distribute_blocks(block_vectorno_type& blocks,
                                               cds::const_entity_vector& entities) {
  return m_dist->distribute_blocks(blocks, entities);
} /* distribute_block() */

/*******************************************************************************
 * Template Instantiations
 ******************************************************************************/
template class dispatcher<crepr::base_block2D>;
template class dispatcher<crepr::base_block3D>;

NS_END(block_dist, foraging, cosm);
