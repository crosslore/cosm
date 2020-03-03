/**
 * \file arena_cache_block_drop.hpp
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

#ifndef INCLUDE_COSM_FORAGING_EVENTS_ARENA_CACHE_BLOCK_DROP_HPP_
#define INCLUDE_COSM_FORAGING_EVENTS_ARENA_CACHE_BLOCK_DROP_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <memory>

#include "rcppsw/er/client.hpp"
#include "rcppsw/patterns/visitor/visitor.hpp"
#include "rcppsw/types/discretize_ratio.hpp"
#include "rcppsw/types/type_uuid.hpp"

#include "cosm/foraging/events/arena_block_op_visit_set.hpp"
#include "cosm/events/cell2D_op.hpp"
#include "cosm/cosm.hpp"
#include "cosm/foraging/ds/arena_map_locking.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace cosm::foraging::repr {
class arena_cache;
} // namespace repr

NS_START(cosm, foraging, events, detail);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * \class arena_cache_block_drop
 * \ingroup foraging events detail
 *
 * \brief Created whenever a robot drops a block in a cache.
 *
 * The cache usuage penalty, if there is one, is not assessed during the event,
 * but at a higher level.
 */
class arena_cache_block_drop : public rer::client<arena_cache_block_drop>,
                         public cevents::cell2D_op {
 private:
  struct visit_typelist_impl {
    using inherited = boost::mpl::joint_view<arena_block_op_visit_typelist,
                                             cell2D_op::visit_typelist>;

    using value = inherited;
  };

 public:
  using visit_typelist = visit_typelist_impl::value;

  ~arena_cache_block_drop(void) override = default;

  arena_cache_block_drop(const arena_cache_block_drop& op) = delete;
  arena_cache_block_drop& operator=(const arena_cache_block_drop& op) = delete;

  /**
   * \brief Perform actual cache block drop in the arena, taking/releasing locks
   * as needed.
   */
  void visit(cfds::arena_map& map);

 protected:
  /**
   * \brief Initialize a arena_cache_block_drop event caused by a robot dropping
   * a block.
   *
   * \param arena_block The block to drop in the cache (MUST be owned by arena).
   * \param cache Cache to drop into (owned by arena).
   * \param resolution Arena resolution.
   * \param locking Is locking needed around block accesses?
   */
  arena_cache_block_drop(crepr::base_block2D* arena_block,
                         cfrepr::arena_cache* cache,
                         const rtypes::discretize_ratio& resolution,
                         const cfds::arena_map_locking& locking);

 private:
  void visit(cds::cell2D& cell);
  void visit(fsm::cell2D_fsm& fsm);
  void visit(crepr::base_block2D& block);
  void visit(cfrepr::arena_cache& cache);

  /* clang-format off */
  const cfds::arena_map_locking  mc_locking;
  const rtypes::discretize_ratio mc_resolution;

  crepr::base_block2D*           m_arena_block;
  cfrepr::arena_cache*           m_cache;
  /* clang-format on */
};

/**
 * \brief We use the picky visitor in order to force compile errors if a call to
 * a visitor is made that involves a visitee that is not in our visit set
 * (i.e. remove the possibility of implicit upcasting performed by the
 * compiler).
 */
using arena_cache_block_drop_visitor_impl =
    rpvisitor::precise_visitor<arena_cache_block_drop,
                               arena_cache_block_drop::visit_typelist>;

NS_END(detail);

class arena_cache_block_drop_visitor : public detail::arena_cache_block_drop_visitor_impl {
  using detail::arena_cache_block_drop_visitor_impl::arena_cache_block_drop_visitor_impl;
};

NS_END(events, foraging, cosm);

#endif /* INCLUDE_COSM_FORAGING_EVENTS_ARENA_CACHE_BLOCK_DROP_HPP_ */
