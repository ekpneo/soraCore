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
#include "TrajectoryProvider.h"
#include "RapidExtIoParameters.h"

#include "rapidExtDds/ExtConstants.h"

namespace rapid
{
  namespace ext
  {
    /**
     * ctor
     */
    TrajectoryProvider::TrajectoryProvider(TrajectoryTopicPairParameters const& params) :
      TrajectoryProviderBase(TRAJECTORY_CONFIG_TOPIC,
                             TRAJECTORY_SAMPLE_TOPIC,
                             params)
    {
    }
    
    /**
     * dtor
     */
    TrajectoryProvider::~TrajectoryProvider() throw()
    {
    }
  }
}
