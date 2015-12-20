// Copyright (c) 2012 NaturalMotion.  All Rights Reserved.
// Not to be copied, adapted, modified, used, distributed, sold,
// licensed or commercially exploited in any manner without the
// written consent of NaturalMotion.
//
// All non public elements of this software are the confidential
// information of NaturalMotion and may not be disclosed to any
// person nor used for any purpose not expressly approved by
// NaturalMotion in writing.

//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma once
#endif
#ifndef MR_NODE_EXPAND_LIMITS_H
#define MR_NODE_EXPAND_LIMITS_H
//----------------------------------------------------------------------------------------------------------------------
#include "morpheme/mrNetwork.h"
//----------------------------------------------------------------------------------------------------------------------

namespace MR
{

//----------------------------------------------------------------------------------------------------------------------
// Queuing function declarations
Task* nodeExpandLimitsQueueTransforms(
  NodeDef*        node,
  TaskQueue*      queue,
  Network*        net,
  TaskParameter*  dependentParameter);


Task* nodeExpandLimitsQueueTrajectoryDeltaAndTransforms(
  NodeDef*        node,
  TaskQueue*      queue,
  Network*        net,
  TaskParameter*  dependentParameter);

} // namespace MR

//----------------------------------------------------------------------------------------------------------------------
#endif // MR_NODE_EXPAND_LIMITS_H
//----------------------------------------------------------------------------------------------------------------------