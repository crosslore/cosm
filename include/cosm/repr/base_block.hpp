/**
 * \file base_block.hpp
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

#ifndef INCLUDE_COSM_REPR_BASE_BLOCK_HPP_
#define INCLUDE_COSM_REPR_BASE_BLOCK_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcppsw/math/vector2.hpp"
#include "rcppsw/math/vector3.hpp"
#include "rcppsw/patterns/prototype/clonable.hpp"
#include "rcppsw/types/timestep.hpp"
#include "rcppsw/types/type_uuid.hpp"

#include "cosm/repr/block_metadata.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NS_START(cosm, repr);
class unicell_movable_entity2D;
class unicell_movable_entity3D;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class base_block
 * \ingroup cosm repr
 *
 * \brief Base class for representing blocks (i.e. things that robots carry
 * within the arena). Blocks have both real (where they actually live in the
 * world) and discretized locations (where they are mapped to within the arena).
 */
template <typename TEntityType>
class base_block : public TEntityType,
                   public rpprototype::clonable<base_block<TEntityType>> {
 public:
  template <typename T>
  using is2D = std::is_same<TEntityType, unicell_movable_entity2D>;
  template <typename T>
  using is3D = std::is_same<TEntityType, unicell_movable_entity3D>;

  using rloc_type = typename std::conditional<is2D<TEntityType>::value,
                                              rmath::vector2d,
                                              rmath::vector3d>::type;
  using dloc_type = typename std::conditional<is2D<TEntityType>::value,
                                              rmath::vector2z,
                                              rmath::vector3z>::type;

  /**
   * \param dim 2 element vector of the dimensions of the block.
   * \param color The color of the block.
   * \param type The type of the block.
   *
   * Using this constructor, blocks are assigned the next available id, starting
   * from 0.
   */
  base_block(const rloc_type& dim,
             const rutils::color& color,
             const crepr::block_type& type)
      : TEntityType(dim, rtypes::constants::kNoUUID), m_md(color, type) {}

  /**
   * \param dim 2 element vector of the dimensions of the block.
   * \param color The color of the block.
   * \param type The type of the block.
   * \param id The id of the block.
   */
  base_block(const rloc_type& dim,
             const rutils::color& color,
             const crepr::block_type& type,
             const rtypes::type_uuid& id)
      : TEntityType(dim, id), m_md(color, type) {}

  ~base_block(void) override = default;

  /**
   * \brief Disallow direct object comparisons, because we may want to compare
   * for equality in terms of IDs or object locations, and it is better to
   * require explicit comparisons for BOTH, rather than just one. It also makes
   * it unecessary to have to remember which type the comparison operator==()
   * does for this class.
   */
  bool operator==(const base_block& other) const = delete;

  /**
   * \brief Compare two \ref base_block objects for equality based on their
   * ID.
   */
  bool idcmp(const base_block& other) const { return this->id() == other.id(); }

  /**
   * \brief Compare two \ref base_block objects for equality based on their
   * discrete location.
   */
  bool dloccmp(const base_block& other) const {
    return this->dloc() == other.dloc();
  }

  const block_metadata* md(void) const { return &m_md; }
  block_metadata* md(void) { return &m_md; }

  /**
   * \brief Update a block's state given that it has been picked up by a robot.
   *
   * - Update its metadata
   * - Move the block's position out of sight so that it is not discoverable by
   *   other robots.
   */
  void robot_pickup_event(const rtypes::type_uuid& robot_id,
                          const rtypes::timestep& t) {
    m_md.robot_pickup_event(robot_id);
    m_md.first_pickup_time(t);
    move_out_of_sight();
  }

  /**
   * \brief Determine if the block is currently out of sight.
   *
   * This should only happen if the block is being carried by a robot.
   */
  bool is_out_of_sight(void) const {
    return kOutOfSight.dloc == TEntityType::dloc() ||
        kOutOfSight.rloc == TEntityType::rloc();
  }

 private:
  /**
   * \brief Out of sight location blocks are moved to when a robot picks them
   * up, for visualization/rendering purposes.
   */

  struct out_of_sight2D {
    rloc_type rloc{1000.0, 1000.0};
    dloc_type dloc{1000, 1000};
  };

  struct out_of_sight3D {
    rloc_type rloc{1000.0, 1000.0, 0.0};
    dloc_type dloc{1000, 1000, 0};
  };

  using out_of_sight_type = typename std::conditional<is2D<TEntityType>::value,
                                                      out_of_sight2D,
                                                      out_of_sight3D>::type;

  static constexpr const out_of_sight_type kOutOfSight{};


  /**
   * \brief Change the block's location to something outside the visitable space
   * in the arena when it is being carried by robot.
   */
  void move_out_of_sight(void) {
    TEntityType::rloc(kOutOfSight.rloc);
    TEntityType::dloc(kOutOfSight.dloc);
  }

  /* clang-format off */
  block_metadata m_md;
  /* clang-format on */
};

NS_END(repr, cosm);

#endif /* INCLUDE_COSM_REPR_BASE_BLOCK_HPP_ */
