#pragma once

/*
 * Copyright (c) 2013 NaturalMotion Ltd. All rights reserved.
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

//----------------------------------------------------------------------------------------------------------------------
//                                  This file is auto-generated
//----------------------------------------------------------------------------------------------------------------------

#ifndef NM_MDF_LEGSTANDINGSUPPORT_H
#define NM_MDF_LEGSTANDINGSUPPORT_H

// include definition file to create project dependency
#include "./Definition/Modules/LegStandingSupport.module"

// external types
#include "euphoria/erLimbTransforms.h"
#include "NMPlatform/NMMatrix34.h"
#include "NMPlatform/NMVector3.h"

// known types
#include "Types/BalanceParameters.h"
#include "Types/LimbControl.h"

// base dependencies
#include "euphoria/erJunction.h"
#include "euphoria/erModule.h"
#include "euphoria/erCharacter.h"

// module data
#include "LegStandingSupportData.h"

namespace MR { struct PhysicsSerialisationBuffer; }

//----------------------------------------------------------------------------------------------------------------------
#ifndef NM_BEHAVIOUR_LIB_NAMESPACE
  #error behaviour library namespace undefined
#endif

namespace NM_BEHAVIOUR_LIB_NAMESPACE
{

class Leg;
struct LegStandingSupportAPIBase;
struct LegStandingSupportUpdatePackage;
struct LegStandingSupportFeedbackPackage;

class LegStandingSupport : public ER::Module
{
public:

  LegStandingSupport(ER::ModuleDataAllocator* mdAllocator, ER::ModuleCon* connectionSet);
  virtual ~LegStandingSupport();

  void update(float timeStep);
  void feedback(float timeStep);

  virtual void clearAllData() NM_OVERRIDE;
  virtual void entry() NM_OVERRIDE;
  virtual void create(ER::Module* parent, int childIndex = -1) NM_OVERRIDE;
  void combineInputs() { m_moduleCon->combineInputs(this); }
  virtual const char* getClassName() const  NM_OVERRIDE { return "LegStandingSupport"; }

  virtual bool storeState(MR::PhysicsSerialisationBuffer& savedState) NM_OVERRIDE;
  virtual bool restoreState(MR::PhysicsSerialisationBuffer& savedState) NM_OVERRIDE;

  // module data blocks
  LegStandingSupportData* data;
  LegStandingSupportInputs* in;
  LegStandingSupportFeedbackOutputs* feedOut;
  LegStandingSupportOutputs* out;

  // owner access
  const Leg* owner;
  virtual const ER::Module* getOwner() const  NM_OVERRIDE { return (const ER::Module*)owner; }

  // module children

  // child module access
  virtual ER::Module* getChild(int32_t) const  NM_OVERRIDE { NMP_ASSERT_FAIL(); return 0; }
  virtual const char* getChildName(int32_t index) const NM_OVERRIDE;
  virtual int32_t getNumChildren() const  NM_OVERRIDE { return 0; }

  // Module packaging
  LegStandingSupportAPIBase* m_apiBase;
  LegStandingSupportUpdatePackage* m_updatePackage;
  LegStandingSupportFeedbackPackage* m_feedbackPackage;

  static NM_INLINE NMP::Memory::Format getMemoryRequirements()
  {
    NMP::Memory::Format result(sizeof(LegStandingSupport), NMP_VECTOR_ALIGNMENT);
    return result;
  }
};

//----------------------------------------------------------------------------------------------------------------------
class LegStandingSupport_Con : public ER::ModuleCon
{
public:

  virtual ~LegStandingSupport_Con();
  static NMP::Memory::Format getMemoryRequirements();

  virtual void create(ER::Module* module, ER::Module* owner) NM_OVERRIDE;
  virtual void buildConnections(LegStandingSupport* module);
  void relocate();
  virtual void combineInputs(ER::Module* module) NM_OVERRIDE;

private:

  ER::Junction
      *junc_in_balanceParameters, 
      *junc_in_enableExternalSupport, 
      *junc_in_rootDesiredTM, 
      *junc_in_stabiliseRootAmount, 
      *junc_in_supportStrengthScale, 
      *junc_in_balancePoseEndRelativeToRoot;

};

//----------------------------------------------------------------------------------------------------------------------
} // namespace NM_BEHAVIOUR_LIB_NAMESPACE

#endif // NM_MDF_LEGSTANDINGSUPPORT_H

