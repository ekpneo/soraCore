/* -*- C++ -*- *****************************************************************
 * Copyright (c) 2013 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.

******************************************************************************/
#ifndef kn_Frame_h
#define kn_Frame_h

#include "knFrameStore_Export.h"
#include "knMath/ATrans.h"

#include <string>

namespace kn
{
  /**
   * Class representing a named coordinate transform.
   *
   * This class is mostly used in combination with the TreeNode
   * class to create a frame tree.
   */
  class knFrameStore_Export Frame
  {
  public:

    class Extras
    {
    public:
      virtual ~Extras() throw() {}
      virtual Extras * clone() = 0;
    };

    /**
     * Default constructor.
     */
    Frame() : m_extras(NULL) {}

    /**
     * Initializing constructor.
     */
    Frame(std::string const& name, ATrans3 const& trans) :
      m_trans(trans),
      m_name(name),
      m_extras(NULL)
    {}

    Frame(std::string const& name) :
      m_trans(ATrans3::Identity()),
      m_name(name),
      m_extras(NULL)
    {}

    Frame(Frame const& rhs) :
      m_trans(rhs.m_trans),
      m_name(rhs.m_name),
      m_extras((rhs.m_extras == NULL)? NULL : rhs.m_extras->clone())
    {}

    ~Frame() throw()
    {
      delete m_extras;
    }

    Frame& operator = (Frame const& rhs) {
      if (&rhs != this) {
        m_name = rhs.m_name;
        m_trans = rhs.m_trans;
        delete m_extras;
        m_extras = (rhs.m_extras == NULL)? NULL : rhs.m_extras->clone();
      }
      return *this;
    }

    /// @{ Accessor methods

    /** Access name field. */
    std::string const& name() const throw() {
      return m_name;
    }
    /** Set name field. */
    void set_name(std::string const& name) {
      m_name = name;
    }
    /** Access transform field. */
    ATrans3 const& transform() const throw() {
      return m_trans;
    }
    /** Mutable access to transform field. */
    ATrans3& transform() throw() {
      return m_trans;
    }
    /** Set transform field. */
    void set_transform(ATrans3 const& trans) {
      m_trans = trans;
    }

    Extras * extras() const throw() {
      return m_extras;
    }

    void set_extras(Extras * extras) {
      delete m_extras;
      m_extras = extras;
    }
    /// @}

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  protected:
    ATrans3 m_trans;
    std::string m_name;
    Extras * m_extras;
  };
}
#endif // kn_Frame_h
