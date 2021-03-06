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
#ifndef rapid_MacroIo_h
#define rapid_MacroIo_h

#include "rapidIo_Export.h"

#include <iosfwd>

namespace rapid
{
  class MessageParameters;

  class MacroCommandParameters;
  class MacroConfigParameters;
  
  class MacroCommand;
  class MacroConfig;
  
  rapidIo_Export extern std::ostream& operator<< (std::ostream& ostr, MacroCommand const& rhs);
  rapidIo_Export extern std::ostream& operator<< (std::ostream& ostr, MacroConfig const& rhs);
  
  rapidIo_Export void operator<<= (MacroCommand& dst, MacroCommandParameters const& src);
  rapidIo_Export void operator<<= (MacroConfig& config, MacroConfigParameters const& params);
  rapidIo_Export void operator<<= (MacroConfig& config, MessageParameters const& params);
  
  rapidIo_Export void operator>>= (MacroCommand const& src, MacroCommandParameters& dst);
  rapidIo_Export void operator>>= (MacroConfig const& config, MacroConfigParameters& params);
}

#endif // rapid_MacroIo_h
