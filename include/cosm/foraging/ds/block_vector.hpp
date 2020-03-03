/**
 * \file block_vector.hpp
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

#ifndef INCLUDE_COSM_FORAGING_DS_BLOCK_VECTOR_HPP_
#define INCLUDE_COSM_FORAGING_DS_BLOCK_VECTOR_HPP_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <vector>
#include <memory>

#include "cosm/cosm.hpp"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace cosm::repr {
class base_block2D;
}

NS_START(cosm, foraging, ds);

using block_vectoro_type = std::shared_ptr<crepr::base_block2D>;
using block_vectorno_type = crepr::base_block2D*;
using block_vectorro_type = const crepr::base_block2D*;

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
/**
 * \class block_vectoro
 * \ingroup foraging ds
 *
 * \brief Specialization of \ref std::vector indicating the blocks are OWNED by
 * this class.
 *
 * Has a \ref to_str() method for more convenient debugging.
 */
class block_vectoro : public std::vector<block_vectoro_type> {
 public:
  using std::vector<block_vectoro_type>::vector;
  using value_type = std::vector<block_vectoro_type>::value_type;

  /**
   * \brief Get a string representation of the vector contents.
   */
  std::string to_str(void) const;
};

/*
 * \brief Specialization of \ref std::vector indicating the blocks are NOT owned
 * by this class.
 *
 * Has a \ref to_str() method for more convenient debugging.
 */
class block_vectorno : public std::vector<block_vectorno_type> {
 public:
  using std::vector<block_vectorno_type>::vector;
  using value_type = std::vector<block_vectorno_type>::value_type;

  /**
   * \brief Get a string representation of the vector contents.
   */
  std::string to_str(void) const;
};

/*
 * \brief Specialization of \ref std::vector indicating the blocks are NOT owned
 * by this class and have read only access.
 *
 * Has a \ref to_str() method for more convenient debugging.
 */
class block_vectorro : public std::vector<block_vectorro_type> {
 public:
  using std::vector<block_vectorro_type>::vector;
  using value_type = std::vector<block_vectorro_type>::value_type;

  /**
   * \brief Get a string representation of the vector contents.
   */
  std::string to_str(void) const;
};

NS_END(ds, foraging, cosm);

#endif /* INCLUDE_COSM_FORAGING_DS_BLOCK_VECTOR_HPP_ */
