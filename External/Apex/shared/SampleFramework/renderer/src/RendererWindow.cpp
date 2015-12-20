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
#include <RendererWindow.h>
#include <RendererMemoryMacros.h>
#include <SamplePlatform.h>
#include <stdio.h>

using namespace SampleRenderer;

RendererWindow::RendererWindow(void) : m_platform(NULL), m_isOpen(false)
{
	m_platform = SampleFramework::createPlatform(this);
}

bool RendererWindow::hasFocus() const
{
	return m_platform->hasFocus();
}

void RendererWindow::setFocus(bool b) 
{
	m_platform->setFocus(b);
}

RendererWindow::~RendererWindow(void)
{
	DELETESINGLE(m_platform);
}

bool RendererWindow::open(PxU32 width, PxU32 height, const char *title, bool fullscreen)
{
	bool ok         = false;
	RENDERER_ASSERT(width && height, "Attempting to open a window with invalid width and/or height.");
	if(width && height)
	{
		ok = m_platform->openWindow(width, height, title, fullscreen);
#if !defined(RENDERER_WINDOWS)
		onOpen();
		m_isOpen = true;
#endif
	}
	return ok;
}

void RendererWindow::close(void)
{
	m_platform->closeWindow();
#if !defined(RENDERER_WINDOWS)
	if(isOpen())
	{
		m_isOpen = false;
		onClose();
	}
#endif
}

bool RendererWindow::isOpen(void) const
{
	bool open = m_platform->isOpen();
#if !defined(RENDERER_WINDOWS)
	open = m_isOpen;
#endif
	return open;
}

// update the window's state... handle messages, etc.
void RendererWindow::update(void)
{
	m_platform->update();
#if defined(RENDERER_MACOSX)
	if (isOpen())
	{
		if (!m_platform->updateWindow())
		{
			close();
		}
	}
    return;
#endif

#if defined(RENDERER_ANDROID)
	if (!m_platform->isOpen())
		return;
#endif

	if(isOpen())
	{
		onDraw();
	}
}

void RendererWindow::setSize(PxU32 width, PxU32 height)
{
	m_platform->setWindowSize(width, height);
}

// get the window's title...
void RendererWindow::getTitle(char *title, PxU32 maxLength) const
{
	m_platform->getTitle(title, maxLength);
}

// set the window's title...
void RendererWindow::setTitle(const char *title)
{
	m_platform->setTitle(title);
}
