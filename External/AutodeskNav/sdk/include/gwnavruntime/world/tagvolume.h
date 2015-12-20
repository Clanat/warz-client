/*
* Copyright 2013 Autodesk, Inc. All rights reserved.
* Use of this software is subject to the terms of the Autodesk license agreement and any attachments or Appendices thereto provided at the time of installation or download,
* or which otherwise accompanies this software in either electronic or hard copy form, or which is signed by you and accepted by Autodesk.
*/



// primary contact: LAPA - secondary contact: LASI
#ifndef Navigation_TagVolume_H
#define Navigation_TagVolume_H

#include "gwnavruntime/world/worldelement.h"
#include "gwnavruntime/math/box3f.h"
#include "gwnavruntime/spatialization/tagvolumespatialization.h"
#include "gwnavruntime/dynamicnavmesh/tagvolumeexpander.h"


namespace Kaim
{

class TagVolumeBlob;
class BoxObstacle;
class CylinderObstacle;
class VisualColor;


enum TagVolumeExtendOptions
{
	ExtendTagVolume_WithAltitudeTolerance_Above = 1,      ///< Indicates that In each database, the altitude tolerance off the Database will be added to Zmax
	ExtendTagVolume_WithAltitudeTolerance_Below = 1 << 1, ///< Indicates that In each database, the altitude tolerance off the Database will be removed from Zmin
	ExtendTagVolume_WithEntityHeight_Below      = 1 << 2, ///< Indicates that In each database, the altitude tolerance off the Database will be removed from Zmin
};

/// Class used to provide TagVolume initialization parameters.
class TagVolumeInitConfig
{
public:

	// ---------------------------------- Main API Functions ----------------------------------

	TagVolumeInitConfig() { SetDefaults(); }

	/// Sets all members to their default value.
	void SetDefaults()
	{
		m_points.Clear();
		m_navTag.Clear();
		m_world = KY_NULL;
		m_databaseBinding = KY_NULL;
		m_altitudeMin = 0.0f;
		m_altitudeMax = 0.0f;
		m_extendOptions = ExtendTagVolume_WithAltitudeTolerance_Below;
	}

	// ---------------------------------- Initialization ----------------------------------

	void SetContour(const Vec2f* points, KyUInt32 pointCount);
	void InitFromTagVolumeBlob(const TagVolumeBlob& blob);
	void Init4PointsContour(const Vec2f& center, const Vec2f& v1, const Vec2f& v2);
	void Init6PointsContour(const Vec2f& center, const Vec2f& v1, const Vec2f& v2, const Vec2f& v3);
	void InitFromBox(const Transform& transform, const Vec3f& localCenter, const Vec3f& localHalfExtents, DatabaseBinding* databaseBinding);


public://Internal
	void InitFromBlob(const TagVolumeBlob& tagVolumeBlob);

public:
	// ---------------------------------- Public Data Members ----------------------------------

	/// Mandatory: you must provide a World when calling TagVolume::Init().
	World* m_world;

	/// Defines the Databases in which the TagVolume will be spatialized. If let
	/// to KY_NULL, World's default DatabaseBinding will be used (spatializes on
	/// all Databases).
	Ptr<DatabaseBinding> m_databaseBinding;

	/// This DynamicNavTag will be translated as NavTag in the DynamicNavMesh floors
	/// generated in the TagVolume.
	DynamicNavTag m_navTag;

	KyArray<Vec2f, MemStat_TagVolume> m_points;
	KyFloat32 m_altitudeMin;
	KyFloat32 m_altitudeMax;
	TagVolumeExtendOptions m_extendOptions;
};


/// This class represents runtime-defined volumes with customized NavTag.
/// At runtime, TagVolumes are spatialized and then integrated into the
/// DynamicNavMesh. TagVolumes are either:
/// - directly added to a World by yourself (like other WorldElement) to
///   specify a custom area, or
/// - automatically generated by BoxObstacle and CylinderObstacle instances
///   when you set DoesTriggerTagVolume to true.
class TagVolume: public WorldElement
{
	KY_DEFINE_NEW_DELETE_OPERATORS(MemStat_TagVolume)
	KY_CLASS_WITHOUT_COPY(TagVolume)

public:
	enum WorldStatus
	{
		WorldStatus_NotInit = 0,
		WorldStatus_Added,
		WorldStatus_NotAdded,
		WorldStatus_Unknown
	};

	enum IntegrationStatus
	{
		IntegrationStatus_NotIntegrated = 0,
		IntegrationStatus_ToBeIntegrated,
		IntegrationStatus_IntegrationInProcess,
		IntegrationStatus_Integrated,
		IntegrationStatus_ToBeDeintegrated,
		IntegrationStatus_DeintegrationInProcess
	};

	enum ObstacleType
	{
		ObstacleType_Undefined = 0,
		ObstacleType_BoxObstacle,
		ObstacleType_CylinderObstacle
	};

public:
	static  WorldElementType GetStaticType() { return TypeTagVolume; }
	virtual WorldElementType GetType() const { return TypeTagVolume; }

	virtual const char* GetTypeName() const { return "TagVolume"; }

	static const char* GetWorldStatusDescription(WorldStatus status);
	static const char* GetIntegrationStatusDescription(IntegrationStatus status);
	static const char* GetObstacleTypeName(ObstacleType obstacleType);

	TagVolume();
	~TagVolume();

	/// Initialize the TagVolume accordingly to the informations passed through
	/// the TagVolumeInitConfig.
	/// When calling this method, the TagVolume must be NOT in any World. If it
	/// is, this method first call RemoveFromWorld (to prevent dysfunction) but
	/// don't call AddToWorld in any case, leading the TagVolume to be ignored
	/// if AddToWorld is not explicitly called afterwards.
	KyResult Init(const TagVolumeInitConfig& initConfig);

	/// Adds the TagVolume to the World. It becomes active and is going to be
	/// integrated into the dynamicNavMesh.
	/// The RefCount of this instance is incremented by 1.
	/// NOTE: this method has immediate effect: ensure to call this outside of any
	/// Gameware Navigation computation (World::Update() or threaded query
	/// computation). However, the spatialization is not updated immediately, this
	/// will be done in next World::Update().
	void AddToWorld();

	/// Removes the TagVolume from the World.
	/// The RefCount of this instance is decremented by 1.
	/// NOTE: this method has immediate effect: ensure to call this outside of any
	/// Gameware Navigation computation (Kaim::World::Update or threaded query
	/// computation). The spatialization information are immediately invalidated too.
	void RemoveFromWorld();


	// ---------------------------------- Getters ----------------------------------

	const Box3f&           GetAABB()                   const; ///
	KyFloat32              GetAltitudeMin()            const; ///
	KyFloat32              GetAltitudeMax()            const; ///
	KyUInt32               GetPointCount()             const; ///
	const Vec2f*           GetPoints()                 const; ///
	const Vec2f&           GetPoint(KyUInt32 i)        const; ///
	const DynamicNavTag&   GetNavTag()                 const; ///
	WorldStatus            GetWorldStatus()            const; ///
	IntegrationStatus      GetIntegrationStatus()      const; ///
	ObstacleType           GetObstacleType()           const; ///
	void*                  GetObstacleRawPtr()         const; ///
	BoxObstacle*           GetBoxObstacle()            const; ///
	CylinderObstacle*      GetCylinderObstacle()       const; ///
	const DatabaseBinding* GetDatabaseBinding()        const; ///
	TagVolumeExtendOptions GetTagVolumeExtendOptions() const; ///

public: // internal
	virtual void DoSendVisualDebug(VisualDebugServer& server, VisualDebugSendChangeEvent changeEvent); // Inherited from WorldElement
	void SetObstacle(BoxObstacle* obstacle);
	void SetObstacle(CylinderObstacle* obstacle);
	void ResetObstacle();

	void OnIntegrationStart();
	void OnDeIntegrationStart();

	void OnIntegrationDone();
	void OnDeIntegrationDone();

	void OnIntegrationCancelled();
	void OnDeIntegrationCancelled();

	const TagVolumeDatabaseData& GetTagVolumeDatabaseData() const { return m_tagVolumeDatabaseData; }
	TagVolumeDatabaseData& GetTagVolumeDatabaseData() { return m_tagVolumeDatabaseData; }

	KyResult GetExpandedContour(KyFloat32 radius, KyFloat32 mergePointDistance, KyArray<Vec2f>& expandedContour) const;

	// WARNING Very internal. Used only internally during the generation process
	void SetWorld(World* world);
private:
	void PushPolylineFromInitConfigAccordingToWinding(const TagVolumeInitConfig& initConfig);
	// AABB & point array are private to force PushPoint(...) usage to ensure coherency.
	// AABB, point array and NavTag are private to trigger an update when modified.
	// TagVolumeSpatialization is private to force read-only access.
	Box3f m_aabb;
	KyArray<Vec2f, MemStat_TagVolume> m_points;
	DynamicNavTag m_navTag;

	TagVolumeDatabaseData m_tagVolumeDatabaseData;
	TagVolumeExtendOptions m_extendOptions;

	ObstacleType m_obstacleType;
	void* m_obstacleRawPtr;
	TagVolumeCylinderExpander m_cylinderExpander;
	TagVolumeBoxExpander m_boxExpander;

public: // For internal use only
	WorldStatus m_currentWorldStatus;
	WorldStatus m_nextWorldStatus;
	IntegrationStatus m_integrationStatus;

	// visual debug
	bool m_needToSendNewContextBlob;
	bool m_needToSendTagVolumeBlob;
};


KY_INLINE const Box3f&                 TagVolume::GetAABB()                   const { return m_aabb;                                       }
KY_INLINE       KyFloat32              TagVolume::GetAltitudeMin()            const { return m_aabb.m_min.z;                               }
KY_INLINE       KyFloat32              TagVolume::GetAltitudeMax()            const { return m_aabb.m_max.z;                               }
KY_INLINE       KyUInt32               TagVolume::GetPointCount()             const { return m_points.GetCount();                          }
KY_INLINE const Vec2f*                 TagVolume::GetPoints()                 const { return m_points.GetDataPtr();                        }
KY_INLINE const Vec2f&                 TagVolume::GetPoint(KyUInt32 i)        const { return m_points[i];                                  }
KY_INLINE const DynamicNavTag&         TagVolume::GetNavTag()                 const { return m_navTag;                                     }
KY_INLINE TagVolume::WorldStatus       TagVolume::GetWorldStatus()            const { return m_currentWorldStatus;                         }
KY_INLINE TagVolume::IntegrationStatus TagVolume::GetIntegrationStatus()      const { return m_integrationStatus;                          }
KY_INLINE TagVolume::ObstacleType      TagVolume::GetObstacleType()           const { return m_obstacleType;                               }
KY_INLINE void*                        TagVolume::GetObstacleRawPtr()         const { return m_obstacleRawPtr;                             }
KY_INLINE TagVolumeExtendOptions       TagVolume::GetTagVolumeExtendOptions() const { return m_extendOptions;                              }
KY_INLINE const DatabaseBinding*       TagVolume::GetDatabaseBinding()        const { return GetTagVolumeDatabaseData().m_databaseBinding; }
KY_INLINE BoxObstacle*                 TagVolume::GetBoxObstacle()            const
{
	return ((m_obstacleType == ObstacleType_BoxObstacle) ? (BoxObstacle*)m_obstacleRawPtr : KY_NULL);
}
KY_INLINE CylinderObstacle*            TagVolume::GetCylinderObstacle()      const
{
	return ((m_obstacleType == ObstacleType_CylinderObstacle) ? (CylinderObstacle*)m_obstacleRawPtr : KY_NULL);
}

// WARNING Very internal. Used only internally during the generation process
KY_INLINE void TagVolume::SetWorld(World* world)
{
	m_world = world;
}


} // namespace Kaim


#endif //Navigation_TagVolume_H
