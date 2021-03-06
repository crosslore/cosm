/**
 * \file base_cache.hpp
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

#ifndef INCLUDE_COSM_ARENA_REPR_BASE_CACHE_HPP_
#define INCLUDE_COSM_ARENA_REPR_BASE_CACHE_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <memory>
#include <vector>

#include "rcppsw/patterns/prototype/clonable.hpp"
#include "rcppsw/types/spatial_dist.hpp"

#include "cosm/repr/base_block.hpp"
#include "cosm/repr/colored_entity.hpp"
#include "cosm/repr/unicell_immovable_entity2D.hpp"

#include "cosm/ds/block2D_vector.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, arena, repr);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class base_cache
 * \ingroup arena repr
 *
 * \brief Base class for representating a cache within the arena. Caches do not
 * have state, and if/when a cache becomes empty, it needs to be deleted by an
 * enclosing class. Caches have both real (where they actually live in the
 * world) and discretized locations (where they are mapped to within the arena
 * map).
 */
class base_cache : public crepr::unicell_immovable_entity2D,
                   public crepr::colored_entity,
                   public rpprototype::clonable<base_cache> {
 public:
  /**
   * \param dimension The size of the cache. Does not have to be a multiple of
   *                   the arena resolution, but doing so makes it easier.
   * \param resolution The arena resolution.
   * \param center (X,Y) coordinates of the center of the cache.
   * \param blocks The initial block list for the cache.
   * \param id The ID to assign to the cache; -1 for a new cache, which
   *           will generate a new ID, or any positive # to use the same ID as
   *           an existing cache (used when cloning a cache into a robot's
   *           perception).
   */
  struct params {
    /* clang-format off */
    rtypes::spatial_dist        dimension; /* caches are square */
    rtypes::discretize_ratio    resolution;
    rmath::vector2d             center;
    const cds::block2D_vectorno blocks;
    rtypes::type_uuid           id;
    /* clang-format on */
  };
  /**
   * \brief The minimum # of blocks required for a cache to exist (less than
   * this and you just have a bunch of blocks).
   */
  static constexpr const size_t kMinBlocks = 2;

  explicit base_cache(const params& p);
  ~base_cache(void) override = default;

  /**
   * \brief Disallow direct object comparisons, because we may want to compare
   * for equality in terms of IDs or object locations, and it is better to
   * require explicit comparisons for BOTH, rather than just one. It also makes
   * it unecessary to have to remember which type the comparison operator==()
   * does for this class.
   */
  bool operator==(const base_cache& other) const = delete;

  /**
   * \brief Compare two \ref base_cache objects for equality based on their ID.
   */
  bool idcmp(const base_cache& other) const { return this->id() == other.id(); }

  /**
   * \brief Compare two \ref base_cache objects for equality based on their
   * discrete location.
   */
  bool dloccmp(const base_cache& other) const {
    return this->dloc() == other.dloc();
  }

  /**
   * \brief \c TRUE iff the cache contains the specified block.
   */
  RCSW_PURE bool contains_block(
      const std::shared_ptr<crepr::base_block2D>& c_block) const {
    return contains_block(c_block.get());
  }
  RCSW_PURE bool contains_block(const crepr::base_block2D* const c_block) const {
    return std::find_if(m_blocks.begin(), m_blocks.end(), [&](const auto& b) {
             return b->id() == c_block->id();
           }) != m_blocks.end();
  }
  size_t n_blocks(void) const { return blocks().size(); }

  /**
   * \brief Get a list of the blocks currently in the cache.
   */
  cds::block2D_vectorno& blocks(void) { return m_blocks; }
  const cds::block2D_vectorno& blocks(void) const { return m_blocks; }

  /**
   * \brief Add a new block to the cache's list of blocks.
   *
   * Does not update the block's location.
   */
  void block_add(crepr::base_block2D* block) {
    m_blocks.push_back(block);
  }

  /**
   * \brief Remove a block from the cache's list of blocks.
   *
   * Does not update the block's location.
   */
  void block_remove(crepr::base_block2D* block);

  /**
   * \brief Get the oldest block in the cache (the one that has been in the
   * cache the longest).
   */
  crepr::base_block2D* oldest_block(void) {
    return m_blocks.front();
  }

  std::unique_ptr<base_cache> clone(void) const override final;

  rtypes::timestep creation_ts(void) const { return m_creation; }
  void creation_ts(const rtypes::timestep& ts) { m_creation = ts; }

 private:
  /* clang-format off */
  const rtypes::discretize_ratio mc_resolution;

  static int                     m_next_id;

  rtypes::timestep               m_creation{0};
  cds::block2D_vectorno          m_blocks;
  /* clang-format on */
};

NS_END(repr, arena, cosm);

#endif /* INCLUDE_COSM_ARENA_REPR_BASE_CACHE_HPP_ */
