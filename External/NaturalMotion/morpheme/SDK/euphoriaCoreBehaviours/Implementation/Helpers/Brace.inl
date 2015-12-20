#pragma once

/*
* Copyright (c) 2011 NaturalMotion Ltd. All rights reserved.
*
* Not to be copied, adapted, modified, used, distributed, sold,
* licensed or commercially exploited in any manner without the
* written consent of NaturalMotion.
*
* All non public elements of this software are the confidential
* information of NaturalMotion and may not be disclosed to any
* person nor used for any purpose not expressly approved by
* NaturalMotion in writing.
*
*/

#ifndef NM_BRACE_INL
#define NM_BRACE_INL

#include "AutoGenerated/NetworkForceInclude.h"
#include "AutoGenerated/Types/BraceDynamic.h"

#ifndef NM_BEHAVIOUR_LIB_NAMESPACE
  #error behaviour library namespace undefined
#endif
#define SCALING_SOURCE owner->data->dimensionalScaling
#include "euphoria/erDimensionalScalingHelpers.h"

namespace NM_BEHAVIOUR_LIB_NAMESPACE
{
//----------------------------------------------------------------------------------------------------------------------
// module independent brace function, which works equally on arms as well as legs
template<typename OwnerType, typename InType, typename DataType, typename OutType>
void applyBraceDynamic(
  BraceDynamic& dynamic,
  const OwnerType& owner,
  const InType& in,
  DataType& data,
  const ArmAndLegLimbSharedState& limbState,
  const OutType& out,
  const NMP::Vector3& protectPoint,
  const NMP::Vector3& hazardPosition,
  bool armCushion,
  bool inContactWithHazard,
  float clampLength,
  MR::InstanceDebugInterface* MR_OUTPUT_DEBUG_ARG(pDebugDrawInst))
{
  data->importance = 0.0f;
  // This applies some acceleration to the protect velocity.. if impact predictor is running
  // i.e. an improved velocity
  float impactTime = SCALE_TIME(1.0f); // really this should synch with the time specified in hazardResponse
  // Better prediction of the character's motion
  NMP::Vector3 accOffset = 0.5f * in->getProtectState().acceleration * impactTime; // TODO: is this really needed?
  NMP::Vector3 protectVel = in->getProtectState().velocity + accOffset;
  const SpatialTarget protectVec(protectPoint, protectVel);

  SpatialTarget hazardVec(hazardPosition, in->getBraceHazard().velocity);
  MR_DEBUG_DRAW_VECTOR(pDebugDrawInst, MR::VT_Velocity, hazardVec.position, hazardVec.velocity, NMP::Colour::PURPLE);
  MR_DEBUG_DRAW_VECTOR(pDebugDrawInst, MR::VT_Velocity, protectVec.position, protectVec.velocity, NMP::Colour::PURPLE);

  float midStiffness = owner->data->normalStiffness;
  float maxStiffness = owner->data->normalStiffness * 2.0f * in->getBraceHazardImportance();
  NMP::Vector3 hazardNormal = in->getBraceHazard().normal;
  SpatialTarget handFoot(limbState.m_endTM.translation(), limbState.m_endData.velocity);
  MR_DEBUG_DRAW_VECTOR(pDebugDrawInst, MR::VT_Velocity, handFoot.position, handFoot.velocity, NMP::Colour::PURPLE);

  NMP::Vector3 toHazard = hazardVec.position - protectVec.position;
  data->reachDirection = NMP::vNormalise(toHazard);
  if ((hazardVec.velocity - protectVec.velocity).dot(data->reachDirection) >= 0.0f)
  {
    return; // no point in bracing if the hazard isn't chasing
  }

  // this isn't right for intercept... nor is the velocity version
  NMP::Vector3 relVelocity = protectVec.velocity - hazardVec.velocity;
  float relVel = relVelocity.dot(data->reachDirection);
  LimbControl control(0, 0, 0);
  if (!inContactWithHazard) // do intercept
  {
    dynamic.setPositions(protectVec.position, handFoot.position, hazardVec.position);
    dynamic.setVelocities(protectVec.velocity, handFoot.velocity, hazardVec.velocity);

    NMP::Vector3 interceptVelLocal(0, 0, 0);
    float interceptTime = dynamic.findInterceptTime(data->reachDirection, interceptVelLocal);
    if (interceptTime < 0.001f) // not intending to deal with having hit the protection here
      return;
    data->imminence = 1.0f / interceptTime;

    ProcessRequest process;
    data->importance = process.processRequest(1.0f, data->imminence, midStiffness, 1.0f, owner->owner->data->minStiffnessForActing, maxStiffness);
    if (!data->importance)
      return;
    NMP::Vector3 interceptPos = hazardVec.position + hazardVec.velocity * interceptTime;

    // if we're clamping the magnitude (so limb doesn't straighten).
    NMP::Vector3 toEnd = interceptPos - limbState.m_basePosition;
    toEnd.clampMagnitude(clampLength);
    interceptPos = limbState.m_basePosition + toEnd;

    const float interceptDampingRatio = 0.8f; // ideal damping ratio for interceptions is mathematically about 0.8
    control.reinit(midStiffness * process.stiffnessScale, interceptDampingRatio, owner->data->normalDriveCompensation);
    control.setGravityCompensation(1.0f);
    // Note: There is a state change in the IK system that substantially increases the influence of the target
    // normal|orientation when the normal|orientation weight is greater than the position weight.
    control.setTargetPos(interceptPos, 0.99f);

    // When bracing it is important that the end effectors don't get caught on the hazard surface as they can
    // "roll over" when impact velocity tangent to the surface is high, as it often is when the character falls forward.
    // This can cause joint wrist separation.
    control.setTargetNormal(hazardNormal, 1.0f);
    control.setEndSupportAmount(0.0f);
    // Use half ang vel to get better average when changing
    control.setExpectedRootForTarget(limbState.m_rootTM, 1, NMP::Vector3(0, 0, 0), limbState.m_rootData.angularVelocity * 0.5f);
    control.setControlAmount(ER::interceptControl, 1.0f);
    // Increase the skin width to reduce the change of penetration with the hazard
    control.setSkinWidthIncrease(SCALE_DIST(0.2f));

    MR_DEBUG_DRAW_POINT(pDebugDrawInst, interceptPos, SCALE_DIST(0.05f), NMP::Colour::PURPLE);
  }
  else // do buffer
  {
    // new idea for cushion,
    // aim to match the hazard's velocity,
    // do so with an urgency proportional to 1/time to impact
    // this is the most stable form of control I think, and is setting precisely the measure it wants to control (root velocity relative to hazard velocity)
    // the control importance is also based on the uprightness of the cushion, which also seems sensible
    NMP::Vector3 toEnd = in->getCushionPoint() - protectVec.position;
    MR_DEBUG_DRAW_VECTOR(pDebugDrawInst, MR::VT_Delta, protectVec.position, toEnd, NMP::Colour::LIGHT_YELLOW);

    // the uprightness vector is along the direction of the velocity, ie it is in this direction that we need to cushion
    NMP::Vector3 up = NMP::vNormalise(hazardVec.velocity - protectVec.velocity);

    NMP::Vector3 shift(0, 0, 0);
    if (armCushion)
    {
      // shift the root to try and keep protect point above centre of support in the direction of impacting velocity
      shift = toEnd - up * toEnd.dot(up);
    }
    else
    {
      float toEndDist = toEnd.normaliseGetLength();
      float uprightness = NMP::clampValue(-toEnd.dot(up), 0.0f, 1.0f);

      // pull the pelvis down more as less uprightness are angles less appropriate to cushion
      float pullDown = sqrtf(1.0f - NMP::sqr(uprightness)); // now we have a 0 to 1 range where 1 is 45 degrees
      float verticalCollapseFactor = 0.2f;

      // drop the target down by a percentage depending on how much it is leaning over, when leaning at full (45 degrees) drop by a factor of verticalCollapseFactor
      NMP::Vector3 midDir = (toEnd - hazardNormal) / 2.0f;
      shift = toEndDist * midDir * NMP::clampValue(2.0f * pullDown, 0.0f, 1.0f) * verticalCollapseFactor;
    }

    float distanceToTarget = toHazard.normaliseGetLength();

    // note the 3 value because we are attempting a cubic cushion (impact acc = 0)
    data->imminence = relVel / (3.0f * NMP::maximum(distanceToTarget, dynamic.minReachDistance));

    // here I adjust the stiffness to account for the fact that the character is touching an object with mass,
    // therefore the root won't move with as much stiffness as suggested by the arm's stiffness value.
    // This multiplication may not be needed when we get a system in to change the effective mass when parts touch objects.
    float stiffnessReduction = 1.0f / dynamic.getBufferStiffnessScale();

    // note that we don't reduce down the scale fact, this means he can use more strength than maxStrength but
    // he isn't using any more acceleration because he's pushing against a heavy object... this may change if
    // we scale the apparent hand mass when in contact
    ProcessRequest process;
    data->importance = process.processRequest(1.0f, data->imminence, midStiffness * stiffnessReduction, 1, owner->owner->data->minStiffnessForActing * stiffnessReduction, maxStiffness);
    if (!data->importance)
    {
      return;
    }

    // Now create the control structure based on calculations above
    NMP::Vector3 rootTarget = limbState.m_rootTM.translation() + shift;
    control.reinit(midStiffness * process.stiffnessScale, owner->owner->data->normalDampingRatio, owner->data->normalDriveCompensation);
    control.setGravityCompensation(1.0f);

    // on leg, allow it to follow root velocity, for better results
    NMP::Vector3 rootVel = limbState.m_rootData.velocity;
    NMP::Vector3 targVel;
    if (armCushion)
      targVel = rootVel;
    else
      targVel = handFoot.velocity;

    // Note: There is a state change in the IK system that substantially increases the influence of the target
    // normal|orientation when the normal|orientation weight is greater than the position weight.

    control.setTargetPos(handFoot.position, 0.6f, targVel);
    if (armCushion)
    {
      // When bracing it is important that the end effectors don't get caught on the hazard surface as they can
      // "roll over" when impact velocity tangent to the surface is high, as it often is when the character falls forward.
      // This can cause joint wrist separation.
      control.setTargetNormal(hazardNormal, 1.0f);
    }
    control.setEndSupportAmount(0.0f);
    // When bracing it looks better to absorb the impacts rather than fight them, so make the
    // implicit stiffness 0.
    control.setImplicitStiffness(0.0f);
    MR_DEBUG_DRAW_VECTOR(pDebugDrawInst, MR::VT_Delta, 
      limbState.m_rootTM.translation(), shift, 
      NMP::Colour(ER::getDefaultColourForControl(ER::bufferControl), 255));

    ER::LimbTransform newRoot = limbState.m_rootTM;
    newRoot.translation() = rootTarget;

    // correct cushioning would drive only half way towards the targetVel, so this is over-cushioning, by a factor of 2
    NMP::Vector3 hazardVel;
    if (armCushion)
    {
      hazardVel = hazardVec.velocity;
    }
    else // on leg, allow it to follow root velocity
    {
      hazardVel = rootVel;
      hazardVel += up * up.dot(hazardVec.velocity - rootVel);
    }

    control.setExpectedRootForTarget(newRoot, 1, hazardVel);
    control.setControlAmount(ER::bufferControl, 1.0f);
  }
  if (in->getSwivelAmountImportance() > 0.0f)
  {
    control.setSwivelAmount(in->getSwivelAmount());
  }
  if (!armCushion)
  {
    NMP::Vector3 interceptPos = control.getTargetPos();
    if (!inContactWithHazard)
    {
      if (!owner->canReachPoint(interceptPos, data->doingBrace))
        return;
      if (!in->getShouldBrace()) // if we want to brace but its better that another leg braces, then return
        return;
    }
  }
  out->setControl(control, data->importance);
}
}

#endif
