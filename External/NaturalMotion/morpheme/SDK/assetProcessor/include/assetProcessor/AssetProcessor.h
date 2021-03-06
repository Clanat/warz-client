// Copyright (c) 2010 NaturalMotion.  All Rights Reserved.
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
#ifndef AP_ASSETPROCESSOR_H
#define AP_ASSETPROCESSOR_H
//----------------------------------------------------------------------------------------------------------------------
#include "NMPlatform/NMPlatform.h"
#include "NMPlatform/NMMemory.h"
#include "NMPlatform/NMBasicLogger.h"

#include "export/mcExport.h"
#include "export/mcExportXml.h"
#include "export/apExportLUA.h"
#include "morpheme/mrManager.h"
#include "morpheme/mrDefines.h"
#include "morpheme/mrDispatcher.h"
#include "morpheme/mrNetwork.h"
#include "morpheme/mrTransitDeadBlend.h"
#include "morpheme/TransitConditions/mrTransitCondition.h"
#include "acAnimInfo.h"

#include <list>
#include <vector>
#include <set>

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \namespace AP
/// \brief Morpheme Asset Processor.
/// \see AssetProcessorModule
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/// \defgroup AssetProcessorModule Asset Processor.
///
/// This library is intended as the central component of all binary asset generation tools.
/// It receives an asset in XML form (as generated by morpheme export) and processes the asset based on its type,
/// generating a runtime binary image. It knows how to traverse the dependency tree of assets, and will ensure that all
/// dependent binary objects are created before generating the final image. It is designed such that all customisable
/// elements of an asset compiler application are exposed as callbacks. For example, for each binary asset produced,
/// this module queries the application to generate a runtime ID (it will never assign an ID by itself). Similarly,
/// packaging of binary data is left entirely to the application, which is informed by the asset processor of the size
/// and location of each binary object produced.
//----------------------------------------------------------------------------------------------------------------------

namespace XMD
{
// forward declarations
class XModel;
}

namespace AP
{
// Forward declarations
class AssetProcessor;
class NetworkDefBuilderBase;
class NodeDefBuilder;
class TransitConditionDefBuilder;
class TransitDeadBlendDefBuilder;
class MessageBuilder;
class PredictionModelBuilder;
class AnalysisProcessor;
class AnalysisConditionBuilder;
class AnalysisPropertyBuilder;

//----------------------------------------------------------------------------------------------------------------------
/// \typedef AP::AssetUID
/// \brief  GUIDS, generally created by Connect to uniquely identify source assets that it has created for compilation
/// in the Asset Compiler.
/// \ingroup AssetProcessorModule
///
/// There must be a 1:1 map between these IDs and the RuntimeAssetID returned by the registered GenUIDFunc that creates
/// runtime IDs in the AssetCompiler.
typedef ME::GUID AssetUID;

//----------------------------------------------------------------------------------------------------------------------
/// \struct AP::ProcessedAsset
/// \ingroup AssetProcessorModule
/// \brief Record of a processed asset.
//----------------------------------------------------------------------------------------------------------------------
struct ProcessedAsset
{
  NMP::Memory::Resource   assetMemory;     ///< The compiled assets memory block.
  MR::Manager::AssetType  assetType;       ///< Type of the asset that this entry is a reference to.
  MR::RuntimeAssetID      uniqueRuntimeID; ///< Unique runtime asset ID obtained from an app callback, to which we
                                           ///< pass the source assets GUID from connect and the source asset name.
  ME::GUID                guid;            ///< Original GUID for asset from connect

  uint32_t                     id;
  mutable std::set<uint32_t>   parendIDs;
};
typedef std::vector<ProcessedAsset*> ProcessedAssets;
typedef std::multimap<uint32_t, ProcessedAsset*> quickAssetsGUID;                 // multimap because it is possible to generate > 1 runtime asset type against a source asset.
typedef std::map<MR::RuntimeAssetID, ProcessedAsset*> quickAssetsRunID;
typedef std::multimap<const ME::AssetExport*, ProcessedAsset*> quickAssetsSource; // multimap because it is possible to generate > 1 runtime asset type against a source asset.
typedef std::map<const void*, ProcessedAsset*> quickAssetsMemory;
typedef std::map<std::string, AnalysisProcessor*> AnalysisProcessors;
typedef std::map<std::string, AnalysisConditionBuilder*> AnalysisConditionBuilders;
typedef std::map<std::string, AnalysisPropertyBuilder*> AnalysisPropertyBuilders;

//----------------------------------------------------------------------------------------------------------------------
/// \class AP::AssetCompilerPlugin
/// \brief
///
//----------------------------------------------------------------------------------------------------------------------
class AssetCompilerPlugin
{
public:
  //--------------------------
  struct AnimationFileMetadata
  {
    const char* m_animFileName;   ///< We are using, anim name + take name, as a unique identifier,
    const char* m_animTakeName;   ///< so if there are 2 different source anims with the same name and take name
    const char* m_animFormatType; ///< in different source directories this assumption breaks down.
    const char* m_animOptions;    ///< Compression format and options

    uint32_t    m_identifier;

    uint32_t    m_FileNameHash;
    uint32_t    m_TakeNameHash;
    uint32_t    m_FormatTypeHash;
    uint32_t    m_OptionsHash;
    AnimationFileMetadata() : m_identifier(0) {};
    void updateIdentifier();
    NM_INLINE bool operator==(const AnimationFileMetadata& rhs) const { 
      return ((rhs.m_FileNameHash == m_FileNameHash) && (rhs.m_TakeNameHash == m_TakeNameHash) 
                && (rhs.m_FormatTypeHash == m_FormatTypeHash) && (rhs.m_OptionsHash == m_OptionsHash));
    };
  };

  //--------------------------
  struct AnimationFileRigData
  {
    std::vector<const char*>           m_rigNames;        ///< In Names of all the rigs that this animation
                                                          ///<  needs to be processed against.
    std::vector<const MR::AnimRigDef*> m_rigs;            ///< The compiled rig for each of the above rig names.
                                                          ///<  Used for generation of rig to anim maps and
                                                          ///<  calculation of trajectory data.
                                                          ///<  All rigs in group must share the same trajectory
                                                          ///<  components hierarchy.
    const MR::AnimRigDef*              m_conglomerateRig; ///< This rig contains the super set of all animated
                                                          ///<  channels. Note this is not just the set contained
                                                          ///<  by the largest rig to anim map.
    std::vector<const char*>           m_boneNames;       ///< Conglomerated vector of bone names from rigs that
                                                          ///<  this anim can be used with at runtime.
                                                          ///<  Any bone name in this vector that is also
                                                          ///<  referenced by the anim will be compiled into the
                                                          ///<  final animation.
    std::vector<float>                 m_rigScaleFactors; ///< The scale factor required to scale one unit of the
                                                          ///<  source rig asset to one morpheme internal unit.
                                                          
    float                              m_averageRigBoneLength; ///< Used when compiling the animations to detect
                                                               ///< any unchanging position channels
    
    /// \note For mulit-rig animation compiling in batch mode, where the rigs are orignated from foreign networks, 
    ///        the data must be aligned so that the networks own rigs are in front of the arrays to make sure that
    ///        the runtime behaves as expected (transform-buffer allocations, animation sampling etc.)
    void alignTo(const AnimationFileRigData& other);
  };

  //--------------------------
  struct AnimationMetadata
  {
    std::vector<AnimationFileMetadata> animFiles;
    std::vector<AnimationFileRigData>  animRigdata;
  };

public:
  AssetCompilerPlugin(
    AssetProcessor* assetProc,
    MR::Manager* manager);

  virtual ~AssetCompilerPlugin();

  virtual const ProcessedAsset* processAsset(
    ME::AssetExport* const sourceAsset,  ///< Source connect asset structure.
    MR::Manager::AssetType assetTypeToGenerate = MR::Manager::kAsset_Invalid ///< Indicates to the processor what kind of asset it is trying to create
                                                                             ///<  from the source asset data. For example we create a NetworkDef and 
                                                                             ///<  a NetworkPredictionDef from the same source data.
    ) = 0;

  virtual bool dislocateAsset(ProcessedAsset* asset) = 0;

  virtual bool prepareAnimationMetaData(const std::vector<ME::AssetExport*>& sourceAssets, AnimationMetadata** metadata) = 0;

protected:
  AssetProcessor* m_assetProcessor;
};

//----------------------------------------------------------------------------------------------------------------------
/// \class AP::AssetProcessor
/// \brief Handles generation of binary assets from export data.
/// \ingroup AssetProcessorModule
///
/// Calls back into application provided callbacks as described here.
//----------------------------------------------------------------------------------------------------------------------
class AssetProcessor
{
public:
  /// \brief Provides a 1:1 mapping from AssetUID (generated by connect) to a runtime ID that can be
  /// used to identify 1st level assets.
  ///
  /// \param connectID generated by connect.  Must map 1:1 to the MR::RuntimeAssetID returned by this function.
  /// \param assetName Asset name (likely to be specified by the user within connect)
  typedef MR::RuntimeAssetID (*GenUIDFunc)(
    const char* assetName,
    AssetUID    connectID);

  /// \brief Generated assets are returned to the application via this callback.
  ///
  /// The application can write them out immediately or store them and collect them later.
  /// This will be called in reverse dependency order, i.e. if they are loaded at runtime in the order
  /// that they are provided to this callback, all dependencies will be satisfied.
  typedef void (*HandleProcessedAssetFunc)(
    MR::RuntimeAssetID      runtimeID,
    AssetUID                connectID,
    NMP::Memory::Resource   binaryObject,
    MR::Manager::AssetType  binaryObjectType);

  /// \brief Convert source animation data file into runtime format and return an id.
  ///
  /// The id used at runtime for MR to locate animation data by calling back to the application
  /// (The AnimLoaderFunction passed into MR::initMorphemeLib).
  typedef bool (*ProcessAnimFunc)(
    AssetProcessor*                   assetProc,                ///<
    const AssetCompilerPlugin::AnimationFileMetadata* animData, ///< IN: Data defining inputs for the animation file
    const AssetCompilerPlugin::AnimationFileRigData*  rigData,
    const ME::GUID                    rigToAnimMapGUIDbasis,    ///< IN: GUID used as a basis for generation of unique
                                                                ///<     RigToAnimMap GUIDs.
    MR::RuntimeAnimAssetID&           animAssetID,              ///< OUT: Runtime identifier for the animation.
    std::vector<MR::RuntimeAssetID>&  rigToAnimMapAssetIDs      ///< OUT: Asset IDs of generated rig to anim maps from
                                                                ///<      this anim to each rig.
  );

  /// \brief A callback function to finalize processing of the animation library
  typedef bool (*FinalizeProcessAnimsFunc)(
    AssetProcessor*                   assetProc                 ///<
  );

  /// \brief A class to pass initialisation options to the initialise network instance function
  class InitNetworkInstanceArgs
  {
  public:
    InitNetworkInstanceArgs();

  public:
    NMP::Vector3    m_characterStartPosition;
    NMP::Quat       m_characterStartRotation;
    bool            m_queueTrajectory;
    bool            m_queueTransforms;
    bool            m_queueSampledEvents;
    bool            m_queueSyncEventTrack;
    uint32_t        m_startingAnimSetIndex;
    MR::NodeID      m_startStateNodeID;
  };

  /// \brief A class to pass update options to the update network instance function
  class UpdateNetworkInstanceArgs
  {
  public:
    UpdateNetworkInstanceArgs();

  public:
    float           m_updateTime;
    bool            m_absTime;
    bool            m_queueTrajectory;
    bool            m_queueTransforms;
    bool            m_queueSampledEvents;
    bool            m_queueSyncEventTrack;
  };

  typedef bool (*InitNetworkInstanceFunc)(
    AP::AssetProcessor*               assetProc,
    MR::NetworkDef*                   networkDef,               ///< Definition of the network to instance
    const InitNetworkInstanceArgs&    intitArgs
    );

  typedef bool (*UpdateNetworkInstanceFunc)(
    AP::AssetProcessor*               assetProc,
    const UpdateNetworkInstanceArgs&  updateArgs
    );

  typedef bool (*ReleaseNetworkInstanceFunc)(
    AP::AssetProcessor*               assetProc
  );

  typedef bool (*ChangeNetworkAnimSetFunc)(
    AP::AssetProcessor*               assetProc,
    uint32_t                          animSetIndex
  );

  typedef char* (*DeMacroisePathFunc)(
    const char *                      path
  );

  /// \brief Construct an asset processor using the specified functions.
  AssetProcessor(
    GenUIDFunc                genUIDFunc,         ///< Function of type GenUIDFunc, called to generate ids for each
                                                  ///< binary object produced
    HandleProcessedAssetFunc  handleAssetFunc,    ///< Function of type HandleProcessedAssetFunc, called to inform the
                                                  ///< application of newly created binary asset.
    ProcessAnimFunc           processAnimFunc,    ///< Function of type ProcessAnimFunc, called to request the runtime
                                                  ///< data for a given animation.
    FinalizeProcessAnimsFunc  finalizeAnimsFunc,  ///< Function of type FinalizeProcessAnimsFunc, called when all animations
                                                  ///< have been compiled.
    InitNetworkInstanceFunc   initNetworkInstanceFunc,
    UpdateNetworkInstanceFunc updateNetworkInstanceFunc,
    ReleaseNetworkInstanceFunc releaseNetworkInstanceFunc,
    ChangeNetworkAnimSetFunc  changeNetworkAnimSetFunc,
    DeMacroisePathFunc        deMacroisePathFunc, ///< This function takes a path using the $(RootDir) macro and turns it
                                                  ///  into a fully qualified (absolute) path.
    ME::ExportFactory*        exportFactory,      ///< The ExportFactory to be used to read in the source network data.
                                                  ///< This is usually of type ME::ExportFactoryXML.
    const char*               rootDirectory,      ///< The root directory parameter passed to the asset compiler
    NMP::BasicLogger*         messageLogger,      ///< Handles build process information messages.
    NMP::BasicLogger*         errorLogger         ///< Handles build process error messages.
  );

  /// \brief Destroy the asset processor and all processed assets to avoid memory leaks.
  ~AssetProcessor();

  /// \brief This is the main public entry point into a constructed AssetCompiler object. This function will construct
  /// all dependent assets, calling the appropriate callbacks as necessary.
  ///
  /// The asset and its dependents will be compiled in the scope defined by this asset. For example:
  ///   1. The vector may contain a single Animation named fred.xmd. All of the channels in fred.xmd will be converted
  ///      to the dest format as fred is not dependent on anything else.
  ///   2. The vector may contain a set of NetworkDefs to be used in the level of a game. fred.xmd is used in more than
  ///      1 of these NetworkDefs by more than 1 Rig. In this scope we will compile fred.xmd against the bone union of
  ///      the all the dependent Rigs, only compiling those animation channels that are referenced in one or more of the
  ///      Rigs.
  void processAsset(
    ME::AssetExport* sourceAsset ///< AssetExport that has been loaded using the same
                                 ///<  ExportFactory as used to construct this AssetProcessor.
  );

  /// \brief This is the main public entry point into a constructed AssetCompiler object.  This function will construct
  /// all dependent assets, calling the appropriate callbacks as necessary.
  ///
  /// All assets in the sourceAssets vector and their dependents will be compiled in the scope defined by this set of
  /// assets. For example:
  ///   1. The vector may contain a single Animation named fred.xmd. All of the channels in fred.xmd will be converted
  ///      to the dest format as fred is not dependent on anything else.
  ///   2. The vector may contain a set of NetworkDefs to be used in the level of a game. fred.xmd is used in more than
  ///      1 of these NetworkDefs by more than 1 Rig. In this scope we will compile fred.xmd against the bone union of
  ///      the all the dependent Rigs, only compiling those animation channels that are referenced in one or more of the
  ///      Rigs.
  void processAssets(
    std::vector<ME::AssetExport*>& sourceAssets  ///< AssetExport that has been loaded using the same
                                                 ///<  ExportFactory as used to construct this AssetProcessor.
  );

  void decrementProcessedAssetRefCounts();

  bool serializeProcessedAssets();

  /// \brief
  ///
  bool dislocateAsset(ProcessedAsset* asset);

  /// \brief Find an asset in our processed assets vector via the assets runtime ID.
  const ProcessedAsset* findProcessedAsset(
    MR::RuntimeAssetID assetID              ///< Runtime ID of processed asset.
  ) const;

  /// \brief Find an asset in our processed assets vector via the assets GUID.
  const ProcessedAsset* findProcessedAsset(
    ME::GUID               guid,            ///< GUID of source asset.
    MR::Manager::AssetType assetTypeToFind = MR::Manager::kAsset_Invalid ///< Indicates the asset type we are tring to find.
                                                                         ///< If unspecified, the first matching source asset will be returned.
                                                                         ///< More than 1 processed asset can be created from the same source data.
  ) const;

  /// \brief Find an asset in our processed assets vector via a pointer to its processed asset structure.
  const ProcessedAsset* findProcessedAsset(
    const void*           resource          ///< Memory resource of processed asset.
  ) const;

  /// \brief Process the specified source asset.
  ///
  /// Recursively processes each of its dependent children first.
  const ProcessedAsset* doProcessAsset(
    ME::AssetExport* const sourceAsset,   ///< Source connect asset structure.
    MR::Manager::AssetType assetTypeToGenerate = MR::Manager::kAsset_Invalid ///< Indicates to the processor what kind of asset it is trying to create
                                                                             ///<  from the source asset data. For example we create a NetworkDef and 
                                                                             ///<  a NetworkPredictionDef from the same source data.
    );

  AssetCompilerPlugin::AnimationMetadata* prepareAnimationMetaData(const std::vector<ME::AssetExport*>& networks);

  /// \brief Store a reference to this asset in our vector of processed assets.
  ProcessedAsset* addAsset(
    NMP::Memory::Resource   assetMemory,  ///< The compiled assets memory block.
    MR::Manager::AssetType  assetType,    ///< Type of the asset we are adding to the vector.
    const char*             name,         ///< Name of asset stored in source asset exported from Connect.
    const char*             guid,         ///< GUID of the source asset created and exported from Connect.
    int32_t*                runtimeID = 0 ///< Optional runtime ID.  If this is not specified the genUID function
                                          ///<  will be invoked to generate a runtime ID.
  );

  /// \brief
  ProcessAnimFunc getProcessAnimFunc() { return m_processAnimFunc; }

  /// \brief
  FinalizeProcessAnimsFunc getFinalizeAnimsFunc() { return m_finalizeAnimsFunc; }

  InitNetworkInstanceFunc getInitNetworkInstanceFunc() { return m_initNetworkInstanceFunc; }

  UpdateNetworkInstanceFunc getUpdateNetworkInstanceFunc() { return m_updateNetworkInstanceFunc; }

  ReleaseNetworkInstanceFunc getReleaseNetworkInstanceFunc() { return m_releaseNetworkInstanceFunc; }

  ChangeNetworkAnimSetFunc  getChangeNetworkAnimSetFunc() { return m_changeNetworkAnimSetFunc; }

  DeMacroisePathFunc getDeMacroisePathFunc() { return m_deMacroisePathFunc; }

  /// \brief
  float getRuntimeAssetScaleFactor() const;

  /// \brief
  void setRuntimeAssetScaleFactor(float runtimeAssetScaleFactor);

  /// \brief Check to see if a binary-equivalent version of a mapping already exists in the processed asset list.
  ProcessedAsset* findMatchingMapping(const MR::RigToAnimMap* mapping) const;

  uint32_t getNumProcessedAssetsOfType(MR::Manager::AssetType assetType);

  void getProcessedAssetsOfType(MR::Manager::AssetType assetType, ProcessedAsset** processedAssets);

  /// \brief Accessor to the list of processed assets.
  NM_INLINE const ProcessedAssets& getProcessedAssets() const;
  NM_INLINE ProcessedAssets& getProcessedAssets();

  /// \brief Get the root directory parameter passed to the asset compiler
  const char* getRootDirectory() const;
  /// \brief Set the root directory parameter, overriding that which was passed to the asset compiler
  void setRootDirectory(const char* rootDirectory);

  /// \brief External access to logging system.
  NMP::BasicLogger* getMessageLogger()  { return m_messageLogger; }
  NMP::BasicLogger* getErrorLogger()    { return m_errorLogger; }

  /// \brief
  bool registerNetworkDefBuilder(
    NetworkDefBuilderBase* networkDefBuilder);

  NetworkDefBuilderBase* getNetworkDefBuilder();

  /// \brief Register a node builder against a node type ID.
  bool registerNodeBuilder(
    MR::NodeType    nodeType,
    NodeDefBuilder* nodeBuilder);

  /// \brief Register a node builder against a node type ID.  If there is an existing builder registered against
  ///  the required type, we overwrite it.
  bool overrideNodeBuilder(
    MR::NodeType    nodeType,
    NodeDefBuilder* nodeBuilder);

  /// \brief Get a node type builder via its node type ID.
  NodeDefBuilder* getNodeBuilder(MR::NodeType nodeType);

  /// \brief Register a TransitCondition builder against a transit condition type ID.
  bool registerTransitConditionDefBuilder(
    MR::TransitConditType       transitConditType,
    TransitConditionDefBuilder* conditionBuilder);

  /// \brief
  TransitConditionDefBuilder* getTransitConditionDefBuilder(MR::TransitConditType transitConditType);

  /// \brief Register a TransitDeadBlend builder against a transit condition type ID.
  bool registerTransitDeadBlendDefBuilder(
    MR::TransitDeadBlendType    transitDeadBlendType,
    TransitDeadBlendDefBuilder* deadBlendBuilder);

  /// \brief
  TransitDeadBlendDefBuilder* getTransitDeadBlendDefBuilder(MR::TransitDeadBlendType transitDeadBlendType);

  /// \brief Register a Message builder against a message type ID.
  bool registerMessageBuilder(MR::MessageType messageType, MessageBuilder* messageBuilder);

  /// \brief Get a message type builder via its message type ID.
  MessageBuilder* getMessageBuilder(MR::MessageType messageType) const;

  /// \brief Register prediction model builder against a prediction model type ID.
  bool registerPredictionBuilder(
    MR::PredictionType      predictionType,
    const char*             typeName,
    PredictionModelBuilder* predictionBuilder);
  
  /// \brief Get a prediction model type builder via its type ID.
  PredictionModelBuilder* getPredictionBuilder(MR::PredictionType predictionType);

  /// \brief Get a prediction model type builder via its type name.
  PredictionModelBuilder* getPredictionBuilder(const char* typeName);
  

  /// \brief Register an analysis processor for processing data.
  bool registerAnalysisProcessor(const char* taskType, AnalysisProcessor* analyser);
  bool unregisterAnalysisProcessor(const char* taskType);
  AnalysisProcessor* getAnalysisProcessorForType(const char* typeName) const;

  /// \brief Register an Analysis Condition for processing data.
  bool registerAnalysisConditionBuilder(const char* conditionType, AnalysisConditionBuilder* condition);
  bool unregisterAnalysisConditionBuilder(const char* conditionType);
  AnalysisConditionBuilder* getAnalysisConditionBuilderForType(const char* conditionType) const;

  /// \brief Register an Analysis Property for processing data.
  bool registerAnalysisPropertyBuilder(const char* propertyType, AnalysisPropertyBuilder* property);
  bool unregisterAnalysisPropertyBuilder(const char* propertyType);
  AnalysisPropertyBuilder* getAnalysisPropertyBuilderForType(const char* propertyType) const;
  NM_INLINE const AnalysisPropertyBuilders& getAnalysisPropertyBuilders() const { return m_analysisPropertyBuilders; }

  /// \brief
  ///
  NM_INLINE void setExceptionOccured(bool state) { m_exceptionOccured = state; }

  /// \brief
  ///
  NM_INLINE bool getExceptionOccured() { return m_exceptionOccured; }

  /// \brief
  ///
  NM_INLINE GenUIDFunc getGenUIDFunc() { return m_genUIDFunc; }

  /// \brief Frees the memory used by the processed assets and clears the vector.
  void freeProcessedAssets();

  /// \brief Initiate new entry to the internal dependency stack.
  ///
  void beginNewAssetProcessing();

  /// \brief Cancel the latest dependency stack entry - if the asset has no compilation outcome etc.
  ///
  void cancelNewAssetProcessing();

  /// \brief informative: get the latest entry to the dependency stack.
  /// \note If you are processing assets "by code" (and thus not using the processAsset method), you may need to make
  ///        sure that the dependency values are correctly increased by calling something like:
  ///           uint32_t lastNewAsset = processor->getLastNewAssetStackValue();
  ///           if (lastNewAsset)
  ///             processedAsset->parendIDs.insert(lastNewAsset);
  ///
  ///           otherwise the dependencies can not be tracked correctly and thus the batch-export might not bundle
  ///           everything needed in your network to run.
  ///
  uint32_t getLastNewAssetStackValue();

  /// Network evaluation
  MR::Network* getNetwork() { return m_network; }
  void setNetwork(MR::Network* network) { m_network = network; }

  /// \return false if specified take is not found in the source XMD data.
  ///
  /// \brief There can be several separate animations/cycles/takes in 1 XMD file so
  /// find the take that we want to process within the XMD data.
  bool findTakeInXMDAnimData(
    const char*                    takename,          // IN: Take to find.
    const XMD::XModel&             xmdAnims,          // IN: XMD anim structure to try and find the take in.
    acAnimInfo&                    animInfo           // Information about the anim and take that we are interested in.
    );

  void listTakesInXMDAnimData(
    const XMD::XModel&             xmdAnims,          // IN: XMD anim structure to try and find the take in.
    acAnimInfos*                   animInfos          // Information about the animation takes that we find
  );

  /// \brief Create a guid string.
  bool makeGUID(std::string& guid);

  /// \brief 
  void setProcessingFailFlag(bool value) { m_processingFailFlag = value; }

  /// \brief 
  bool getProcessingFailFlag() { return m_processingFailFlag; }

protected:

  struct NodeRegistryEntry
  {
    MR::NodeType typeID;
    NodeDefBuilder* nodeBuilder;
  };

  struct TransitConditionRegistryEntry
  {
    MR::TransitConditType       typeID;
    TransitConditionDefBuilder* transitConditionBuilder;
  };

  struct TransitDeadBlendRegistryEntry
  {
    MR::TransitDeadBlendType    typeID;
    TransitDeadBlendDefBuilder* transitDeadBlendBuilder;
  };

  struct MessageRegistryEntry
  {
    MR::MessageType typeID;
    MessageBuilder* messageBuilder;
  };

  struct PredictionRegistryEntry
  {
    MR::PredictionType         typeID;
    const char*                typeName;        ///<  Note the memory for this string is not allocated by the AssetProcessor.
                                                ///<  It is up to the caller of registerPredictionBuilder to manage this memory.
    PredictionModelBuilder* predictionBuilder;
  };


  GenUIDFunc                    m_genUIDFunc;               ///< App callback function for generating a unique runtime
                                                            ///< asset ID  to which we pass the source assets GUID
                                                            ///< from connect and the source asset name.
  HandleProcessedAssetFunc      m_handleProcessedAssetFunc; ///< App callback for storage of processed assets.
                                                            ///< Called on each asset after they have all been compiled.
  ProcessAnimFunc               m_processAnimFunc;          ///< App callback function for compiling a source animation.
  FinalizeProcessAnimsFunc      m_finalizeAnimsFunc;        ///< App callback function when all anims have been compiled.
  InitNetworkInstanceFunc       m_initNetworkInstanceFunc;
  UpdateNetworkInstanceFunc     m_updateNetworkInstanceFunc;
  ReleaseNetworkInstanceFunc    m_releaseNetworkInstanceFunc;
  ChangeNetworkAnimSetFunc      m_changeNetworkAnimSetFunc;
  DeMacroisePathFunc            m_deMacroisePathFunc;

  float                         m_runtimeAssetScaleFactor;  ///< Scale factor to scale one world unit to one internal morpheme unit.
  ProcessedAssets               m_processedAssets;          ///< Vector of all processed assets. Provides quick access
                                                            ///< to assets referenced by other assets.
  quickAssetsGUID               m_procAssetsByGUID;         ///< lookup-map for finding assets faster than in m_processedAssets
  quickAssetsRunID              m_procAssetsByRuntimeID;    ///< lookup-map for finding assets faster than in m_processedAssets
  quickAssetsMemory             m_procAssetsByMemory;       ///< lookup-map for finding assets faster than in m_processedAssets
  std::string                   m_rootDirectory;            ///< The root directory passed to the asset compiler
  NMP::BasicLogger*             m_messageLogger;            ///< Handles build process information messages.
  NMP::BasicLogger*             m_errorLogger;              ///< Handles build process error messages.

  bool                          m_processingFailFlag;       ///< If processing of an asset fails for whatever reason this flag will be set.
  
  ME::NetworkDefProcessedDataExport*  m_precomputeDataExport;     ///< Export file of precomputed asset data

  /// Network builder.
  NetworkDefBuilderBase*        m_networkDefBuilder;

  /// Node builders registry.
  NodeRegistryEntry             m_nodeBuilders[MAX_NUM_NODE_TYPES];
  uint32_t                      m_numRegisteredNodeBuilders;

  /// Prediction model builders registry.
  PredictionRegistryEntry       m_predictionBuilders[MR::MAX_NUM_PREDICTION_MODEL_TYPES];
  uint32_t                      m_numRegisteredPredictionBuilders;

  /// Transit condition builders registry.
  TransitConditionRegistryEntry m_transitConditionDefs[MAX_NUM_TRANSIT_COND_TYPES];
  uint32_t                      m_numRegisteredTransitConditionDefBuilders;

  /// Transit dead blend builders registry.
  TransitDeadBlendRegistryEntry m_transitDeadBlendDefs[MAX_NUM_TRANSIT_DEADBLEND_TYPES];
  uint32_t                      m_numRegisteredTransitDeadBlendDefBuilders;

  /// Message builders.
  MessageRegistryEntry          m_messageBuilders[MAX_NUM_MESSAGE_TYPES];
  uint32_t                      m_numRegisteredMessageBuilders;

  /// Analysis processors.
  AnalysisProcessors            m_analysisProcessors;
  AnalysisConditionBuilders     m_analysisConditionBuilders;
  AnalysisPropertyBuilders      m_analysisPropertyBuilders;

  /// simple dependency tracking stack.
  std::stack< uint32_t >        m_dependencyStack;

  /// The internal asset id counter for dependency tracking.
  uint32_t                      m_currentAssetID;

  /// This network instance exists to support Network evaluation in the asset compiler.
  ///  This is required for some nodes such as the closest anim node (when off line processing) 
  ///  and for Network analysis when generating prediction model data.
  MR::Network*                  m_network;

public:
  ///.\brief
  void registerPlugin(AssetCompilerPlugin* plugin);

protected:
  typedef std::vector<AssetCompilerPlugin*>  AssetCompilerPluginsList;
  AssetCompilerPluginsList                    m_plugins;

  /// Did an exception occur during asset processing not all exceptions cause an immediate exit from the asset prcessor.
  bool                                        m_exceptionOccured;

public:
  void outputNodeError(MR::NodeType nodeType, unsigned int nodeID, const char* errorMessage);
  void outputConditionError(MR::TransitConditType conditionType, const char* errorMessage);
  void outputDeadBlendError(MR::TransitDeadBlendType deadBlendType, const char* errorMessage);
  void outputMessageError(MR::MessageType messageType, const char* errorMessage);
};

//----------------------------------------------------------------------------------------------------------------------
// AssetProcessor functions.
//----------------------------------------------------------------------------------------------------------------------
NM_INLINE float AssetProcessor::getRuntimeAssetScaleFactor() const
{
  return m_runtimeAssetScaleFactor;
}

//----------------------------------------------------------------------------------------------------------------------
NM_INLINE void AssetProcessor::setRuntimeAssetScaleFactor(float runtimeAssetScaleFactor)
{
  m_runtimeAssetScaleFactor = runtimeAssetScaleFactor;
}

//----------------------------------------------------------------------------------------------------------------------
NM_INLINE const ProcessedAssets& AssetProcessor::getProcessedAssets() const
{
  return m_processedAssets;
}

//----------------------------------------------------------------------------------------------------------------------
NM_INLINE ProcessedAssets& AssetProcessor::getProcessedAssets()
{
  return m_processedAssets;
}

} // namespace AP

//----------------------------------------------------------------------------------------------------------------------
#endif // AP_ASSETPROCESSOR_H
//----------------------------------------------------------------------------------------------------------------------

