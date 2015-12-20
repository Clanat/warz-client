/*
 * Copyright 2008-2012 NVIDIA Corporation.  All rights reserved.
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

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D9)

#include "D3D9RendererMesh.h"
#include "D3D9RendererVertexBuffer.h"
#include "D3D9RendererInstanceBuffer.h"

#include <RendererMeshDesc.h>

#include <SamplePlatform.h>

#pragma warning(disable:4702 4189)

using namespace SampleRenderer;

static D3DVERTEXELEMENT9 buildVertexElement(WORD stream, WORD offset, D3DDECLTYPE type, BYTE method, BYTE usage, BYTE usageIndex)
{
	D3DVERTEXELEMENT9 element;
	element.Stream     = stream;
	element.Offset     = offset;
#if defined(RENDERER_WINDOWS)
	element.Type       = (BYTE)type;
#else
	element.Type       = type;
#endif
	element.Method     = method;
	element.Usage      = usage;
	element.UsageIndex = usageIndex;
	return element;
}

D3D9RendererMesh::D3D9RendererMesh(D3D9Renderer &renderer, const RendererMeshDesc &desc) :
RendererMesh(desc),
	m_renderer(renderer)
{
	m_d3dVertexDecl = 0;

	IDirect3DDevice9 *d3dDevice = m_renderer.getD3DDevice();
	RENDERER_ASSERT(d3dDevice, "Renderer's D3D Device not found!");
	if(d3dDevice)
	{
		PxU32                             numVertexBuffers = getNumVertexBuffers();
		const RendererVertexBuffer *const*vertexBuffers    = getVertexBuffers();
		std::vector<D3DVERTEXELEMENT9> vertexElements;
		for(PxU32 i=0; i<numVertexBuffers; i++)
		{
			const RendererVertexBuffer *vb = vertexBuffers[i];
			if(vb)
			{
				const D3D9RendererVertexBuffer &d3dVb = *static_cast<const D3D9RendererVertexBuffer*>(vb);
				d3dVb.addVertexElements(i, vertexElements);
			}
		}
#if RENDERER_INSTANCING
		if(m_instanceBuffer)
		{
			static_cast<const D3D9RendererInstanceBuffer*>(m_instanceBuffer)->addVertexElements(numVertexBuffers, vertexElements);
		}
#endif
		vertexElements.push_back(buildVertexElement(0xFF, 0, D3DDECLTYPE_UNUSED, 0, 0, 0));

		d3dDevice->CreateVertexDeclaration(&vertexElements[0], &m_d3dVertexDecl);
		RENDERER_ASSERT(m_d3dVertexDecl, "Failed to create Direct3D9 Vertex Declaration.");
	}
}

D3D9RendererMesh::~D3D9RendererMesh(void)
{
	if(m_d3dVertexDecl)
	{
		SampleFramework::SamplePlatform::platform()->D3D9BlockUntilNotBusy(m_d3dVertexDecl);
		m_d3dVertexDecl->Release();
		m_d3dVertexDecl = 0;
	}
}

static D3DPRIMITIVETYPE getD3DPrimitive(RendererMesh::Primitive primitive)
{
	D3DPRIMITIVETYPE d3dPrimitive = D3DPT_FORCE_DWORD;
	switch(primitive)
	{
	case RendererMesh::PRIMITIVE_POINTS:         d3dPrimitive = D3DPT_POINTLIST;     break;
	case RendererMesh::PRIMITIVE_LINES:          d3dPrimitive = D3DPT_LINELIST;      break;
	case RendererMesh::PRIMITIVE_LINE_STRIP:     d3dPrimitive = D3DPT_LINESTRIP;     break;
	case RendererMesh::PRIMITIVE_TRIANGLES:      d3dPrimitive = D3DPT_TRIANGLELIST;  break;
	case RendererMesh::PRIMITIVE_TRIANGLE_STRIP: d3dPrimitive = D3DPT_TRIANGLESTRIP; break;
	case RendererMesh::PRIMITIVE_POINT_SPRITES:  d3dPrimitive = D3DPT_POINTLIST;     break;
	}
	RENDERER_ASSERT(d3dPrimitive != D3DPT_FORCE_DWORD, "Unable to find Direct3D9 Primitive.");
	return d3dPrimitive;
}

static PxU32 computePrimitiveCount(RendererMesh::Primitive primitive, PxU32 vertexCount)
{
	PxU32 numPrimitives = 0;
	switch(primitive)
	{
	case RendererMesh::PRIMITIVE_POINTS:          numPrimitives = vertexCount;                          break;
	case RendererMesh::PRIMITIVE_LINES:           numPrimitives = vertexCount / 2;                      break;
	case RendererMesh::PRIMITIVE_LINE_STRIP:      numPrimitives = vertexCount>=2 ? vertexCount - 1 : 0; break;
	case RendererMesh::PRIMITIVE_TRIANGLES:       numPrimitives = vertexCount / 3;                      break;
	case RendererMesh::PRIMITIVE_TRIANGLE_STRIP:  numPrimitives = vertexCount>=3 ? vertexCount - 2 : 0; break;
	case RendererMesh::PRIMITIVE_POINT_SPRITES:   numPrimitives = vertexCount;                          break;
	}
	RENDERER_ASSERT(numPrimitives, "Unable to compute the number of Primitives.");
	return numPrimitives;
}

void D3D9RendererMesh::renderIndices(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat, RendererMaterial *material) const
{
	IDirect3DDevice9 *d3dDevice = m_renderer.getD3DDevice();
	if(d3dDevice && m_d3dVertexDecl)
	{
		d3dDevice->SetVertexDeclaration(m_d3dVertexDecl);
		Primitive primitive = getPrimitives();
#if RENDERER_INSTANCING
		PxU32 numVertexBuffers = getNumVertexBuffers();
		// Only reset stream source when multiple vertex buffers are given
		//  This fixes issues with several GPU vendors when rendering a given indexed mesh multiple times
		static const physx::PxU32 minVertexBuffersForStreamSourceReset = 2;
		if (numVertexBuffers >= minVertexBuffersForStreamSourceReset)
		{
			for(PxU32 i=0; i<numVertexBuffers; i++)
			{
				d3dDevice->SetStreamSourceFreq((UINT)i, D3DSTREAMSOURCE_INDEXEDDATA | 1);
			}
		}
#endif
		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 1);

		d3dDevice->DrawIndexedPrimitive(getD3DPrimitive(primitive), 0, 0, numVertices, firstIndex, computePrimitiveCount(primitive, numIndices));

		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 0);
	}
}

void D3D9RendererMesh::renderVertices(PxU32 numVertices, RendererMaterial *material) const
{
	IDirect3DDevice9 *d3dDevice = m_renderer.getD3DDevice();
	if(d3dDevice && m_d3dVertexDecl)
	{
		d3dDevice->SetVertexDeclaration(m_d3dVertexDecl);
		Primitive primitive = getPrimitives();
#if RENDERER_INSTANCING	
		PxU32 numVertexBuffers = getNumVertexBuffers();
		for(PxU32 i=0; i<numVertexBuffers; i++)
		{
			d3dDevice->SetStreamSourceFreq((UINT)i, 1);
		}
#endif
		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 1);

		D3DPRIMITIVETYPE d3dPrimitive  = getD3DPrimitive(primitive);
		PxU32            numPrimitives = computePrimitiveCount(primitive, numVertices);
		PX_ASSERT(d3dPrimitive != D3DPT_LINELIST || (numVertices&1)==0); // can't have an odd number of verts when drawing lines...!
		d3dDevice->DrawPrimitive(d3dPrimitive, 0, numPrimitives);

		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 0);
	}
}

void D3D9RendererMesh::renderIndicesInstanced(PxU32 numVertices, PxU32 firstIndex, PxU32 numIndices, RendererIndexBuffer::Format indexFormat,RendererMaterial *material) const
{
	IDirect3DDevice9 *d3dDevice = m_renderer.getD3DDevice();
	if(d3dDevice && m_d3dVertexDecl)
	{
#if RENDERER_INSTANCING
		PxU32 numVertexBuffers = getNumVertexBuffers();
		for(PxU32 i=0; i<numVertexBuffers; i++)
		{
			d3dDevice->SetStreamSourceFreq((UINT)i, D3DSTREAMSOURCE_INDEXEDDATA | m_numInstances);
		}
#endif	

		d3dDevice->SetVertexDeclaration(m_d3dVertexDecl);

		Primitive primitive = getPrimitives();

		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) 
		{
			d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 1);
		}

#if RENDERER_INSTANCING
		d3dDevice->DrawIndexedPrimitive(getD3DPrimitive(primitive), 0, 0, numVertices, firstIndex, computePrimitiveCount(primitive, numIndices));
#else
		const PxU8 *ibuffer = (const PxU8 *)m_instanceBuffer->lock();
		ibuffer+=m_instanceBuffer->getStride()*m_firstInstance;
		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		for (PxU32 i=0; i<m_numInstances; i++)
		{
			PxF32 *dest = (PxF32 *)&m;

			const PxF32 *src = (const PxF32 *)ibuffer;

			dest[0] = src[3];
			dest[1] = src[6];
			dest[2] = src[9];
			dest[3] = src[0];

			dest[4] = src[4];
			dest[5] = src[7];
			dest[6] = src[10];
			dest[7] = src[1];

			dest[8] = src[5];
			dest[9] = src[8];
			dest[10] = src[11];
			dest[11] = src[2];

			dest[12] = 0;
			dest[13] = 0;
			dest[14] = 0;
			dest[15] = 1;

			material->setModelMatrix(dest);
			d3dDevice->DrawIndexedPrimitive(getD3DPrimitive(primitive), 0, 0, numVertices, firstIndex, computePrimitiveCount(primitive, numIndices));
			ibuffer+=m_instanceBuffer->getStride();
		}
#endif

		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) 
		{
			d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 0);
		}
	}
}

void D3D9RendererMesh::renderVerticesInstanced(PxU32 numVertices,RendererMaterial *material) const
{
	IDirect3DDevice9 *d3dDevice = m_renderer.getD3DDevice();
	if(d3dDevice && m_d3dVertexDecl)
	{
#if RENDERER_INSTANCING
		PxU32 numVertexBuffers = getNumVertexBuffers();
		for(PxU32 i=0; i<numVertexBuffers; i++)
		{
			d3dDevice->SetStreamSourceFreq((UINT)i, m_numInstances);
		}
#endif

		d3dDevice->SetVertexDeclaration(m_d3dVertexDecl);

		Primitive primitive = getPrimitives();

		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) 
		{
			d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 1);
		}


#if RENDERER_INSTANCING
		d3dDevice->DrawPrimitive(getD3DPrimitive(primitive), 0, computePrimitiveCount(primitive, numVertices));
#else
		const PxU8 *ibuffer = (const PxU8 *)m_instanceBuffer->lock();
		D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		for (PxU32 i=0; i<m_numInstances; i++)
		{
			PxF32 *dest = (PxF32 *)&m;

			const PxF32 *src = (const PxF32 *)ibuffer;

			dest[0] = src[3];
			dest[1] = src[6];
			dest[2] = src[9];
			dest[3] = src[0];

			dest[4] = src[4];
			dest[5] = src[7];
			dest[6] = src[10];
			dest[7] = src[1];

			dest[8] = src[5];
			dest[9] = src[8];
			dest[10] = src[11];
			dest[11] = src[2];

			dest[12] = 0;
			dest[13] = 0;
			dest[14] = 0;
			dest[15] = 1;


			material->setModelMatrix(dest);

			d3dDevice->DrawPrimitive(getD3DPrimitive(primitive), 0, computePrimitiveCount(primitive, numVertices));

			ibuffer+=m_instanceBuffer->getStride();
		}
#endif

		if(primitive == RendererMesh::PRIMITIVE_POINT_SPRITES) 
		{
			d3dDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, 0);
		}
	}
}

#endif // #if defined(RENDERER_ENABLE_DIRECT3D9)
