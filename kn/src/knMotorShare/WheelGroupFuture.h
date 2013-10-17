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
#ifndef kn_WheelGroupFuture_h
#define kn_WheelGroupFuture_h

#include "WheelGroupState.h"

#include "knMath/ATrans.h"

namespace kn
{
  class WheelGroupFuture;
  knMotorShare_Export std::ostream& operator<< (std::ostream& ostr, WheelGroupFuture const& rhs);
  
  //! Sample of wheel group state as expected at a future time.
  class knMotorShare_Export WheelGroupFuture : public WheelGroupState
  {
  public:
    // Special operator new required for classes containing eigen types.
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    ATrans2 offset;

    //! Default constructor.
    WheelGroupFuture() {}
    //! Initializing constructor.
    WheelGroupFuture(ACE_Time_Value const& target,
                     DoubleVector const& p,
                     DoubleVector const& s,
                     double c,
                     double cR,
                     double v,
                     double cA,
                     double cAr,
                     ATrans2 const& o) :
      WheelGroupState(target, p, s, c, cR, v, cA, cAr),
      offset(o)
    {}
  };
}
#endif // kn_WheelGroupFuture_h
