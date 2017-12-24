/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of Penumbra Overture.
 *
 * Penumbra Overture is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Penumbra Overture is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Penumbra Overture.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GAME_GRAPHICS_HELPER_H
#define GAME_GRAPHICS_HELPER_H

#include "StdAfx.h"

#include "GameTypes.h"

using namespace hpl;

class cInit;


//---------------------------
class cGraphicsHelper
{
public:
	cGraphicsHelper(cInit *apInit);
	~cGraphicsHelper();

	void ClearScreen(const cColor &aColor);
	void DrawTexture(iTexture *apTex, const cVector3f& avPos, const cVector3f& avSize, const cColor &aColor);

	void DrawLoadingScreen(const tString &asFile);

	void SwapBuffers();

private:
	tVertexVec mvVtx;

	cInit *mpInit;
	iLowLevelGraphics *mpLowLevelGfx;
	cTextureManager *mpTexManager;

    cGraphicsDrawer *mpDrawer;

	iFontData *mpFont;
};

//---------------------------------------------


#endif // GAME_GRAPHICS_HELPER_H
