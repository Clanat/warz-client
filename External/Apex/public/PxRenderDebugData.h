/*
 * Copyright 2009-2011 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */

#ifndef PX_RENDER_DEBUG_DATA_H
#define PX_RENDER_DEBUG_DATA_H

/*!
\file
\brief debug rendering classes and structures
*/

#include "foundation/PxVec3.h"
#include "foundation/PxVec2.h"
#include "foundation/PxQuat.h"
#include "foundation/PxMat44.h"
#include "foundation/PxBounds3.h"
#include <new>

namespace physx
{
	namespace general_renderdebug4
	{

PX_PUSH_PACK_DEFAULT

struct DebugPrimitive;
struct DebugGraphDesc;

// This enumeration defines the list of graphics primitives that can be generated by the debug renderer.
		struct DebugCommand
		{
			enum Enum
			{
				SET_CURRENT_RENDER_STATE,	// set the current render state bit flags
				SET_CURRENT_TEXT_SCALE,		// set the floating point scale for 3d text printing.
				SET_CURRENT_COLOR,			// set the current pen color
				SET_CURRENT_ARROW_COLOR,	// set the current arrow (secondary) color
				SET_CURRENT_TRANSFORM,		// set the current matrix transform for graphics primitives
				SET_CURRENT_RENDER_SCALE,	// set the current overall render scale.
				SET_CURRENT_ARROW_SIZE,		// set the current size of arrow heads
				SET_CURRENT_USER_POINTER,	// sets the current user pointer.
				SET_CURRENT_USER_ID,		// sets the current user id.
				DEBUG_LINE,					// render a single line segment
				DRAW_GRID,					// render a 3d studio max style grid.
				DEBUG_TEXT,					// display 3d text
				DEBUG_BOUND,				// display a bounding box
				DEBUG_POINT,				// highlight a point
				DEBUG_POINT_SCALE,			// Debug a point with different scale on x/y/z
				DEBUG_QUAD,					// Debug a scaled and oriented screen facing quad
				DEBUG_RECT2D,				// display a 2d rectangle
				DEBUG_GRADIENT_LINE,		// draw a line segment with a unique color for each point.
				DEBUG_RAY,					// draw a ray (line with arrow on the end)
				DEBUG_CYLINDER,				// draw a cylinder assuming the default orientation of the PhysX SDK
				DEBUG_POINT_CYLINDER,		// draw a cylinder between two points
				DEBUG_THICK_RAY,			// draw a thick ray, full 3d arrow head.
				DEBUG_PLANE,				// debug visualization of a plane equation (drawn as concentric circles)
				DEBUG_TRI,					// debug visualize a triangle solid/wireframe determined by the current render state.
				DEBUG_TRI_NORMALS,			// debug visualize a triangle using the provided vertex normals
				DEBUG_GRADIENT_TRI,			// debug visualize a solid shaded triangle with unique vertex colors
				DEBUG_GRADIENT_TRI_NORMALS,	// debug visualize a solid shaded triangle with unique vertex normals and vertex colors
				DEBUG_SPHERE,				// debug visualize a coarse sphere
				DEBUG_SQUASHED_SPHERE,		// debug visualize a sphere that has been squashed
				DEBUG_CAPSULE,				// debug visualize a capsule (assumed PhysX SDK orientation) i.e. Y up is 'height'
				DEBUG_AXES,					// debug visualize a set of axes using thick-rays.
				DEBUG_ARC,					// debug visualize an arc.
				DEBUG_THICK_ARC,			// debug visualize a thick arc
				DEBUG_DETAILED_SPHERE,		// debug visualize a highly detailed sphere
				DEBUG_BLOCK_INFO,			// used internally only.
				DEBUG_GRAPH,                // display a graph
				DEBUG_CAPSULE_TAPERED,		// debug visualize a capsule with y-up as height
				LAST
			};
			static PX_INLINE PxU32 getPrimtiveSize(const DebugPrimitive &p); // returns the size of the data associated with a particular primitive type.
		};



		// The base class for all debug primitives
		struct DebugPrimitive
		{
			DebugPrimitive(void) { };
			DebugPrimitive(DebugCommand::Enum c) : mCommand(c)
			{
			}

			DebugCommand::Enum 	mCommand;
		};

		// used to transmit render state, current color or other single unsigned int primitives.
		struct DebugPrimitiveU32 : public DebugPrimitive
		{
			DebugPrimitiveU32(void) { };
			DebugPrimitiveU32(DebugCommand::Enum cmd,PxU32 v) :
			DebugPrimitive(cmd),
				mValue(v)
			{
			}
			PxU32 mValue;
		};

		// used to transmit pointers, or other long integers.
		struct DebugPrimitiveU64 : public DebugPrimitive
		{
			DebugPrimitiveU64(void) { };
			DebugPrimitiveU64(DebugCommand::Enum cmd,PxU64 v) :
			DebugPrimitive(cmd),
				mValue(v)
			{
			}
			PxU64 mValue;
		};

		// used to transmit render scale, text scale, or other single float primitives.
		struct DebugPrimitiveF32 : public DebugPrimitive
		{
			DebugPrimitiveF32(void) { };
			DebugPrimitiveF32(DebugCommand::Enum cmd,PxF32 v) :
			DebugPrimitive(cmd),
				mValue(v)
			{
			}
			PxF32 mValue;
		};
	
		// Defines a primitive for a line segment
		struct DebugLine : public DebugPrimitive
		{
			DebugLine(void) { };
			DebugLine(const PxVec3 &p1,const PxVec3 &p2) :
			DebugPrimitive(DebugCommand::DEBUG_LINE),
				mP1(p1),
				mP2(p2)
			{
			}
			PxVec3	mP1;
			PxVec3	mP2;
		};

		// Defines a primitive to draw a grid visualization
		struct DrawGrid : public DebugPrimitive
		{
			DrawGrid(void) { };
			DrawGrid(bool zup,PxU32 gridSize) :
			DebugPrimitive(DebugCommand::DRAW_GRID),
				mZup(zup),
				mGridSize(gridSize)
			{
			}

			bool	mZup;
			PxU32 	mGridSize;
		};

		// Defines a primitive to transmit a piece of 3d ASCII text.
		#define MAX_DEBUG_TEXT_STRING 96
		struct DebugText : public DebugPrimitive
		{
			DebugText(void) { };
			DebugText(const PxVec3 &position,const PxMat44 &pose,const char *text) : 
			DebugPrimitive(DebugCommand::DEBUG_TEXT),
				mPosition(position),
				mPose(pose)
			{
				const char *source = text;
				char *dest = mText;
				char *stop = &mText[MAX_DEBUG_TEXT_STRING-1];
				while ( *source && dest < stop )
				{
					*dest++ = *source++;
				}
				*dest = 0;
			}
			PxVec3	mPosition; // relative offset from the pose
			PxMat44	mPose;
			char	mText[MAX_DEBUG_TEXT_STRING];
		};

		// Defines a primitive to draw a bounding box
		struct DebugBound : public DebugPrimitive
		{
			DebugBound(void) { };
			DebugBound(const PxVec3 &bmin,const PxVec3 &bmax) : 
			DebugPrimitive(DebugCommand::DEBUG_BOUND),mBmin(bmin),mBmax(bmax)
			{

			}
			PxVec3	mBmin;
			PxVec3	mBmax;
		};

		// Defines a primitive which display a debug point visualization.
		struct DebugPoint : public DebugPrimitive
		{
			DebugPoint(void) {};
			DebugPoint(const PxVec3 &point,PxF32 size) :
			DebugPrimitive(DebugCommand::DEBUG_POINT),
				mPos(point),
				mSize(size)
			{
			}

			PxVec3	mPos;
			PxF32	mSize;
		};


		struct DebugQuad : public DebugPrimitive
		{
			DebugQuad(void) {};
			DebugQuad(const PxVec3 &point,const PxVec2 &scale,PxF32 rotation) :
			DebugPrimitive(DebugCommand::DEBUG_QUAD),
				mPos(point),
				mScale(scale),
				mRotation(rotation)
			{
			}

			PxVec3	mPos;
			PxVec2 mScale;
			PxF32  mRotation;
		};


		struct DebugPointScale : public DebugPrimitive
		{
			DebugPointScale(void) {};
			DebugPointScale(const PxVec3 &point,PxVec3 size) :
			DebugPrimitive(DebugCommand::DEBUG_POINT_SCALE),
				mPos(point),
				mSize(size)
			{
			}

			PxVec3	mPos;
			PxVec3	mSize;
		};


		// Defines a primitive to display 2d rectangle in screenspace.
		struct DebugRect2d : public DebugPrimitive
		{
			DebugRect2d(void) { };
			DebugRect2d(PxF32 x1,PxF32 y1,PxF32 x2,PxF32 y2) :
			DebugPrimitive(DebugCommand::DEBUG_RECT2D),
				mX1(x1),
				mY1(y1),
				mX2(x2),
				mY2(y2)
			{
			};

			PxF32	mX1;
			PxF32	mY1;
			PxF32	mX2;
			PxF32	mY2;
		};

		// Defines a primitive for a gradient colored line segment
		struct DebugGradientLine : public DebugPrimitive
		{
			DebugGradientLine(void) { };
			DebugGradientLine(const PxVec3 &p1,const PxVec3 &p2,PxU32 c1,PxU32 c2) :
			DebugPrimitive(DebugCommand::DEBUG_GRADIENT_LINE),
				mP1(p1),
				mP2(p2),
				mC1(c1),
				mC2(c2)
			{
			};

			PxVec3	mP1;
			PxVec3	mP2;
			PxU32	mC1;
			PxU32	mC2;
		};

		// Defines a primitive to draw a ray indicator (line segment with arrow-head)
		struct DebugRay : public DebugPrimitive
		{
			DebugRay(void) { };
			DebugRay(const PxVec3 &p1,const PxVec3 &p2) :
			DebugPrimitive(DebugCommand::DEBUG_RAY),
				mP1(p1),
				mP2(p2)
			{
			};

			PxVec3	mP1;
			PxVec3	mP2;
		};

		// Defines a primitive to draw a thick ray (solid shaded arrow head)
		struct DebugThickRay : public DebugPrimitive
		{
			DebugThickRay(void) { };
			DebugThickRay(const PxVec3 &p1,const PxVec3 &p2,PxF32 raySize) :
			DebugPrimitive(DebugCommand::DEBUG_THICK_RAY),
				mP1(p1),
				mP2(p2),
				mRaySize(raySize)
			{
			};

			PxVec3	mP1;
			PxVec3	mP2;
			PxF32	mRaySize;
		};

		// Defines a primitive to visualize a plane equation
		struct DebugPlane : public DebugPrimitive
		{
			DebugPlane(void) { };
			DebugPlane(const PxVec3 &normal,PxF32 dCoff,PxF32 radius1,PxF32 radius2) :
			DebugPrimitive(DebugCommand::DEBUG_PLANE),
				mNormal(normal),
				mD(dCoff),
				mRadius1(radius1),
				mRadius2(radius2)
			{
			};

			PxVec3	mNormal;
			PxF32	mD;
			PxF32	mRadius1;
			PxF32	mRadius2;
		};

		// Defines a primitive to visualize a single triangle, either wireframe, or solid, or both based on the current render state bit flags
		struct DebugTri : public DebugPrimitive
		{
			DebugTri(void) { };
			DebugTri(const PxVec3 &p1,const PxVec3 &p2,const PxVec3 &p3) :
			DebugPrimitive(DebugCommand::DEBUG_TRI),
				mP1(p1),
				mP2(p2),
				mP3(p3)
			{
			};

			PxVec3	mP1;
			PxVec3	mP2;
			PxVec3	mP3;
		};

		struct DebugTriNormals : public DebugPrimitive
		{
			DebugTriNormals(void) { };
			DebugTriNormals(const PxVec3 &p1,const PxVec3 &p2,const PxVec3 &p3,const PxVec3 &n1,const PxVec3 &n2,const PxVec3 &n3) :
			DebugPrimitive(DebugCommand::DEBUG_TRI_NORMALS),
				mP1(p1),mP2(p2),mP3(p3),
				mN1(n1),mN2(n2),mN3(n3)
			{
			};

			PxVec3	mP1;
			PxVec3	mP2;
			PxVec3	mP3;
			PxVec3	mN1;
			PxVec3	mN2;
			PxVec3	mN3;
		};

		struct DebugGradientTri : public DebugPrimitive
		{
			DebugGradientTri(void) { };
			DebugGradientTri(const PxVec3 &p1,const PxVec3 &p2,const PxVec3 &p3,const PxU32 &c1,const PxU32 &c2,const PxU32 &c3) :
			DebugPrimitive(DebugCommand::DEBUG_GRADIENT_TRI),
				mP1(p1),mP2(p2),mP3(p3),
				mC1(c1),mC2(c2),mC3(c3)
			{
			};

			PxVec3	mP1;
			PxVec3	mP2;
			PxVec3	mP3;
			PxU32	mC1;
			PxU32	mC2;
			PxU32	mC3;
		};

		struct DebugGradientTriNormals : public DebugPrimitive
		{
			DebugGradientTriNormals(void) { };
			DebugGradientTriNormals(const PxVec3 &p1,const PxVec3 &p2,const PxVec3 &p3,const PxVec3 &n1,const PxVec3 &n2,const PxVec3 &n3,const PxU32 &c1,const PxU32 &c2,const PxU32 &c3) :
			DebugPrimitive(DebugCommand::DEBUG_GRADIENT_TRI_NORMALS),
				mP1(p1),mP2(p2),mP3(p3),
				mN1(n1),mN2(n2),mN3(n3),
				mC1(c1),mC2(c2),mC3(c3)
			{
			};


			PxVec3	mP1;
			PxVec3	mP2;
			PxVec3	mP3;
			PxVec3	mN1;
			PxVec3	mN2;
			PxVec3	mN3;
			PxU32	mC1;
			PxU32	mC2;
			PxU32	mC3;
		};

		struct DebugSphere : public DebugPrimitive
		{
			DebugSphere(void) { };
			DebugSphere(PxF32 radius, PxU32 subdivision) :
			DebugPrimitive(DebugCommand::DEBUG_SPHERE),
				mRadius(radius),
				mSubdivision(subdivision)
			{
			};

			PxF32	mRadius;
			PxU32	mSubdivision;
		};

		struct DebugSquashedSphere : public DebugPrimitive
		{
			DebugSquashedSphere(void) { };
			DebugSquashedSphere(const PxVec3 &radius, PxU32 subdivision) :
			DebugPrimitive(DebugCommand::DEBUG_SQUASHED_SPHERE),
				mRadius(radius),
				mSubdivision(subdivision)
			{
			};

			PxVec3	mRadius;
			PxU32	mSubdivision;
		};


		struct DebugCapsule : public DebugPrimitive
		{
			DebugCapsule(void) { };
			DebugCapsule(PxF32 radius,PxF32 height,PxU32 subdivision) :
			DebugPrimitive(DebugCommand::DEBUG_CAPSULE),
				mRadius(radius),
				mHeight(height),
				mSubdivision(subdivision)
			{
			};

			PxF32	mRadius;
			PxF32	mHeight;
			PxU32	mSubdivision;
		};

		struct DebugTaperedCapsule : public DebugPrimitive
		{
			DebugTaperedCapsule() {}
			DebugTaperedCapsule(PxF32 radius1, PxF32 radius2, PxF32 height, PxU32 subdivision) :
			DebugPrimitive(DebugCommand::DEBUG_CAPSULE_TAPERED),
				mRadius1(radius1),
				mRadius2(radius2),
				mHeight(height),
				mSubdivision(subdivision)
			{
			}

			PxF32 mRadius1;
			PxF32 mRadius2;
			PxF32 mHeight;
			PxU32 mSubdivision;
		};

		struct DebugPointCylinder : public DebugPrimitive
		{
			DebugPointCylinder(void) { };
			DebugPointCylinder(const PxVec3 &p1,const PxVec3 &p2,PxF32 radius) :
			DebugPrimitive(DebugCommand::DEBUG_POINT_CYLINDER),
				mP1(p1),
				mP2(p2),
				mRadius(radius)
			{
			};

			PxVec3	mP1;
			PxVec3	mP2;
			PxF32	mRadius;
		};


		struct DebugCylinder : public DebugPrimitive
		{
			DebugCylinder(void) { };
			DebugCylinder(PxF32 radius,PxF32 height,PxU32 subdivision,bool closeSides) :
			DebugPrimitive(DebugCommand::DEBUG_CYLINDER),
				mRadius1(radius),
				mRadius2(radius),
				mHeight(height),
				mSubdivision(subdivision),
				mCloseSides(closeSides)
			{
			};

			DebugCylinder(PxF32 radius1, PxF32 radius2, PxF32 height, PxU32 subdivision, bool closeSides) :
			DebugPrimitive(DebugCommand::DEBUG_CYLINDER),
				mRadius1(radius1),
				mRadius2(radius2),
				mHeight(height),
				mSubdivision(subdivision),
				mCloseSides(closeSides)
			{
			};

			PxF32	mRadius1;
			PxF32	mRadius2;
			PxF32	mHeight;
			PxU32	mSubdivision;
			bool	mCloseSides;
		};

		struct DebugAxes : public DebugPrimitive
		{
			DebugAxes(void) { };
			DebugAxes(const PxMat44 &transform,PxF32 distance,PxF32 brightness) :
			DebugPrimitive(DebugCommand::DEBUG_AXES),
				mTransform(transform),
				mDistance(distance),
				mBrightness(brightness)
			{
			};

			PxMat44	mTransform;
			PxF32	mDistance;
			PxF32	mBrightness;
		};

		struct DebugArc : public DebugPrimitive
		{
			DebugArc(void) { };
			DebugArc(const PxVec3 &center,const PxVec3 &p1,const PxVec3 &p2,PxF32 arrowSize,bool showRoot) :
			DebugPrimitive(DebugCommand::DEBUG_ARC),
				mCenter(center),
				mP1(p1),
				mP2(p2),
				mArrowSize(arrowSize),
				mShowRoot(showRoot)
			{
			};

			PxVec3	mCenter;
			PxVec3	mP1;
			PxVec3	mP2;
			PxF32	mArrowSize;
			bool	mShowRoot;
		};

		struct DebugThickArc : public DebugPrimitive
		{
			DebugThickArc(void) { };
			DebugThickArc(const PxVec3 &center,const PxVec3 &p1,const PxVec3 &p2,PxF32 thickness=0.02f,bool showRoot=false) :
			DebugPrimitive(DebugCommand::DEBUG_THICK_ARC),
				mCenter(center),
				mP1(p1),
				mP2(p2),
				mThickness(thickness),
				mShowRoot(showRoot)
			{
			};

			PxVec3	mCenter;
			PxVec3	mP1;
			PxVec3	mP2;
			PxF32	mThickness;
			bool	mShowRoot;
		};

		struct DebugDetailedSphere : public DebugPrimitive
		{
			DebugDetailedSphere(void) { };
			DebugDetailedSphere(const PxVec3 &pos,PxF32 radius,PxU32 stepCount) :
			DebugPrimitive(DebugCommand::DEBUG_DETAILED_SPHERE),
				mPos(pos),
				mRadius(radius),
				mStepCount(stepCount)
			{
			};

			PxVec3	mPos;
			PxF32	mRadius;
			PxU32	mStepCount;
		};

		struct DebugSetCurrentTransform : public DebugPrimitive
		{
			DebugSetCurrentTransform(void) { };
			DebugSetCurrentTransform(const PxMat44 &m) :
			DebugPrimitive(DebugCommand::SET_CURRENT_TRANSFORM),
				mTransform(m)
			{
			}

			PxMat44		mTransform;
		};

		struct DebugGraphStream : public DebugPrimitive
		{
			DebugGraphStream(void) { mAllocated = false; mBuffer = NULL;};
			DebugGraphStream(const DebugGraphDesc &d);
			~DebugGraphStream(void);

			PxU32 getSize(void) const { return mSize; };
			PxU32 mSize;
			PxU8 *mBuffer;
		private:
			bool mAllocated;
		};


/**
\brief State flags for debug renderable
 */
struct DebugRenderState
{
	enum Enum
	{
		ScreenSpace      = (1<<0),  //!< true if rendering in screenspace
		NoZbuffer        = (1<<1),  //!< true if zbuffering is disabled.
        SolidShaded      = (1<<2),  //!< true if rendering solid shaded.
        SolidWireShaded  = (1<<3),  //!< Render both as a solid shaded triangle and as a wireframe overlay.
        CounterClockwise = (1<<4),  //!< true if winding order is counter clockwise.
        CameraFacing     = (1<<5),  //!< True if text should be displayed camera facing
        InfiniteLifeSpan = (1<<6),  //!< True if the lifespan is infinite (overrides current display time value)
        CenterText       = (1<<7),  //!< True if the text should be centered.
	};
};

// data structure used to track draw groups.  Used internally only.
struct BlockInfo
{
public:

	BlockInfo(void)
	{
		mHashValue = 0;
		mVisibleState = true;
		mChanged = false;
	}

	PxU32 getHashValue(void) const
	{
		return mHashValue;
	}

	PxMat44		mPose;  // transform for block of data
	PxU32		mHashValue;
	bool		mVisibleState;
	bool		mChanged; // a semaphore indicating that the state has changed for this block
};



// The current render state data block.
class RenderState
{
public:

	RenderState()
	{
		mStates = 0;
		mColor = 0xcfcfcfcf; // needs to be symmetric to be platform independent.
		mDisplayTime = 0.0001f;
		mArrowColor = 0x5f5f5f5f; // needs to be symmetric to be platform independent.
		mArrowSize = 0.1f;
		mRenderScale = 1;
		mTextScale = 1;
		mUserPtr = NULL;
		mUserId = 0;
		mPose = NULL;
		mBlockInfo = NULL;
		mChangeCount = 0;
		mCurrentPose = PxMat44::createIdentity();
	}

	RenderState(PxU32 s,PxU32 c,PxF32 d,PxU32 a,PxF32 as,PxF32 rs,PxF32 ts)
	{
		mStates = s;
		mColor = c;
		mDisplayTime = d;
		mArrowColor = a;
		mArrowSize = as;
		mRenderScale = rs;
		mTextScale = ts;
		mUserPtr = 0;
		mUserId = 0;
		mPose = NULL;
		mCurrentPose = PxMat44::createIdentity();
		mBlockInfo = NULL;
		mChangeCount = 0;
	}

	PX_INLINE bool isScreen(void) const { return (mStates & DebugRenderState::ScreenSpace); }
	PX_INLINE bool isUseZ(void) const { return !(mStates & DebugRenderState::NoZbuffer); }
	PX_INLINE bool isSolid(void) const { return (mStates & (DebugRenderState::SolidShaded | DebugRenderState::SolidWireShaded)) ? true : false; }
	PX_INLINE bool isClockwise(void) const { return !(mStates & DebugRenderState::CounterClockwise); }
	PX_INLINE bool isWireframeOverlay(void) const { return (mStates & DebugRenderState::SolidWireShaded) ? true : false; }
	PX_INLINE bool isWireframe(void) const
	{
		bool ret = true;
		if ( isSolid() && !isWireframeOverlay() )
		{
			ret = false;
		}
		return ret;
	}

	PX_INLINE  PxF32 getDisplayTime(void) const
	{
		return (mStates & DebugRenderState::InfiniteLifeSpan) ? PX_MAX_F32 : mDisplayTime;
	}

	PX_INLINE bool isCentered(void) const { return (mStates & DebugRenderState::CenterText) ? true : false; }
	PX_INLINE bool isCameraFacing(void) const { return (mStates & DebugRenderState::CameraFacing) ? true : false; }
	PX_INLINE bool isCounterClockwise(void) const { return (mStates & DebugRenderState::CounterClockwise) ? true : false; }
	PX_INLINE void * getUserPtr(void) const { return mUserPtr; };
	PX_INLINE PxI32 getUserId(void) const { return mUserId; };

	PX_INLINE void incrementChangeCount(void) { mChangeCount++; };
	PX_INLINE PxU32 getChangeCount(void) const { return mChangeCount; };

	PX_INLINE PxU32 setRenderState(DebugRenderState::Enum state)
	{
		mStates|=state;
		return mStates;
	}

	PX_INLINE PxU32 clearRenderState(DebugRenderState::Enum state)
	{
		mStates&=~state;
		return mStates;
	}

	PX_INLINE bool hasRenderState(DebugRenderState::Enum state) const
	{
		return (state&mStates) ? true : false;
	}

	PX_INLINE void setCurrentColor(PxU32 c1,PxU32 c2)
	{
		mColor = c1;
		mArrowColor = c2;
	}


	PxU32 		mStates;
	PxU32 		mColor;
	PxF32 		mDisplayTime;
	PxU32 		mArrowColor;
	PxF32 		mArrowSize;
	PxF32 		mRenderScale;
	PxF32 		mTextScale;
	PxU32		mChangeCount;
	void 		*mUserPtr;
	PxI32 		 mUserId;
	BlockInfo	*mBlockInfo;
	PxMat44 	*mPose;
	PxMat44		 mCurrentPose;
};

struct DebugBlockInfo : public DebugPrimitive
{
	DebugBlockInfo(void) { };
	DebugBlockInfo(BlockInfo *info) :
	DebugPrimitive(DebugCommand::DEBUG_BLOCK_INFO),
		mInfo(info)
	{
		if ( info )
		{
			new ( &mCurrentTransform ) DebugSetCurrentTransform(info->mPose);
		}
	}
	BlockInfo				*mInfo;
	DebugSetCurrentTransform mCurrentTransform; // contains the transform for this block; updated each time it changes.
};

/**
\brief The maximum number of graphs that can be displayed at one time.  (0-5)
*/
static const PxU32 MAX_GRAPHS			(6);
/**
\brief The width of the graphs (x axis) when created automatically
*/
static const PxF32 GRAPH_WIDTH_DEFAULT	(+0.8f);
/**
\brief The height of the graphs (y axis) when created automatically
*/
static const PxF32 GRAPH_HEIGHT_DEFAULT	(+0.4f);

/**
\brief definition of the debugGraph descriptor used to create graphs
*/
struct DebugGraphDesc 
{
	DebugGraphDesc(void) 
	{ 
		mPoints = NULL;
		mGraphXLabel = NULL;
		mGraphYLabel = NULL;
	};


	/**
	\brief The number of PxReal data points to graph
	*/
	PxU32	mNumPoints;
	/**
	\brief Pointer to the PxReal data points to graph
	*/
	const PxF32*	mPoints;
	/**
	\brief optional cutoff line drawn horizontally on the graph.  It should be between 0 and mGraphMax.
	0.0f indicates not to draw the cutoff line.
	*/
	PxF32	mCutOffLevel;
	/**
	\brief The maximum value that the graph should be be able to display.
	Noramlly this is slightly larger than the greatest value in the mPoints array to make room for
	future samples that are higher then the current set.
	*/
	PxF32	mGraphMax;
	/**
	\brief The bottom left x coordinate of the graph.
	This is set automatically by the constructor that takes graphNum as an argument.
	NOTE: display coordinates range from -1.0f - + 1.0f
	*/
	PxF32	mGraphXPos;
	/**
	\brief bottom left y coordinate of the graph.
	This is set automatically by the constructor that takes graphNum as an argument.
	NOTE: display coordinates range from -1.0f - + 1.0f
	*/
	PxF32	mGraphYPos;
	/**
	\brief The width of the graph.
	This is set automatically by the constructor that takes graphNum as an argument.
	NOTE: display coordinates range from -1.0f - + 1.0f
	*/
	PxF32	mGraphWidth;
	/**
	\brief The height of the graph.
	This is set automatically by the constructor that takes graphNum as an argument.
	NOTE: display coordinates range from -1.0f - + 1.0f
	*/
	PxF32	mGraphHeight;
	/**
	\brief The color of the data.
	This is set automatically by the constructor that takes graphNum as an argument.
	NOTE: display coordinates range from -1.0f - + 1.0f
	This is set automatically by the constructor that takes graphNum as an argument.
	*/
	PxU32	mGraphColor;
	/**
	\brief The alternate color of the data if mColorSwitchIndex is set to a value that is a valid
	index to the mPoints array.  The points after mColorSwitchIndex are drawn in this color.
	This is set automatically by the constructor that takes graphNum as an argument.
	*/
	PxU32	mArrowColor;
	/**
	\brief A pointer to the label for the X axis.
	*/
	const char*	mGraphXLabel;
	/**
	\brief A pointer to the label for the Y axis.
	*/
	const char*	mGraphYLabel;
	/**
	\brief The (optional!) index in the data set at which to switch the color to the color specified by
	mArrorColor.  By default this is set to -1 indicating that no color switch should be performed.
	*/
	PxU32	mColorSwitchIndex;

};





PX_INLINE PxU32 DebugCommand::getPrimtiveSize(const DebugPrimitive &p)
{
	PxU32 ret;

	switch ( p.mCommand )
	{
	case SET_CURRENT_TRANSFORM:
		ret = sizeof(DebugSetCurrentTransform);
		break;
	case SET_CURRENT_COLOR:
	case SET_CURRENT_RENDER_STATE:
	case SET_CURRENT_ARROW_COLOR:
	case SET_CURRENT_USER_ID:
		ret = sizeof(DebugPrimitiveU32);
		break;
	case SET_CURRENT_USER_POINTER:
		ret = sizeof(DebugPrimitiveU64);
		break;
	case DEBUG_BOUND:
		ret = sizeof(DebugBound);
		break;
	case SET_CURRENT_TEXT_SCALE:
	case SET_CURRENT_RENDER_SCALE:
	case SET_CURRENT_ARROW_SIZE:
		ret = sizeof(DebugPrimitiveF32);
		break;
	case DEBUG_LINE:
		ret = sizeof(DebugLine);
		break;
	case DRAW_GRID:
		ret = sizeof(DrawGrid);
		break;
	case DEBUG_TEXT:
		ret = sizeof(DebugText);
		break;
	case DEBUG_QUAD:
		ret = sizeof(DebugQuad);
		break;
	case DEBUG_POINT:
		ret = sizeof(DebugPoint);
		break;
	case DEBUG_RECT2D:
		ret = sizeof(DebugRect2d);
		break;
	case DEBUG_GRADIENT_LINE:
		ret = sizeof(DebugGradientLine);
		break;
	case DEBUG_RAY:
		ret = sizeof(DebugRay);
		break;
	case DEBUG_CYLINDER:
		ret = sizeof(DebugCylinder);
		break;
	case DEBUG_POINT_CYLINDER:
		ret = sizeof(DebugPointCylinder);
		break;
	case DEBUG_THICK_RAY:
		ret = sizeof(DebugThickRay);
		break;
	case DEBUG_PLANE:
		ret = sizeof(DebugPlane);
		break;
	case DEBUG_TRI:
		ret = sizeof(DebugTri);
		break;
	case DEBUG_TRI_NORMALS:
		ret = sizeof(DebugTriNormals);
		break;
	case DEBUG_GRADIENT_TRI:
		ret = sizeof(DebugGradientTri);
		break;
	case DEBUG_GRADIENT_TRI_NORMALS:
		ret = sizeof(DebugGradientTriNormals);
		break;
	case DEBUG_SPHERE:
		ret = sizeof(DebugSphere);
		break;
	case DEBUG_SQUASHED_SPHERE:
		ret = sizeof(DebugSquashedSphere);
		break;
	case DEBUG_CAPSULE:
		ret = sizeof(DebugCapsule);
		break;
	case DEBUG_AXES:
		ret = sizeof(DebugAxes);
		break;
	case DEBUG_ARC:
		ret = sizeof(DebugArc);
		break;
	case DEBUG_THICK_ARC:
		ret = sizeof(DebugThickArc);
		break;
	case DEBUG_DETAILED_SPHERE:
		ret = sizeof(DebugDetailedSphere);
		break;
	case DEBUG_BLOCK_INFO:
		ret = sizeof(DebugBlockInfo);
		break;
	case DEBUG_GRAPH:
		{
			const DebugGraphStream *d = static_cast< const DebugGraphStream *>(&p);
			ret = d->getSize();
		}
		break;
	case DEBUG_CAPSULE_TAPERED:
		ret = sizeof(DebugTaperedCapsule);
		break;
	case DEBUG_POINT_SCALE:
		ret = sizeof(DebugPointScale);
		break;
	default:
		PX_ALWAYS_ASSERT();
		ret = 0;
		break;
	}
	return ret;
}

PX_POP_PACK

}; // end of namespace
using namespace general_renderdebug4;
}; // end of namespace

#endif // PX_RENDER_DEBUG_DATA_H
