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
#ifndef GAME_FADE_HANDLER_H
#define GAME_FADE_HANDLER_H

#include "StdAfx.h"

using namespace hpl;

class cInit;

class cFadeHandler : public iUpdateable
{
public:
	cFadeHandler(cInit *apInit);
	~cFadeHandler();

	void FadeOut(float afTime);
	void FadeIn(float afTime);
	bool IsActive();

	void SetWideScreenActive(bool abX);

	void OnStart();
	void Update(float afTimeStep);
	void Reset();
	void OnDraw();
	
private:
	cInit *mpInit;
	cGraphicsDrawer *mpDrawer;

	cGfxObject *mpBlackGfx;

	bool mbActive;
	float mfAlpha;
	float mfAlphaAdd;

	bool mbWideScreenActive;
	float mfWideScreenAlpha;
};


#endif // GAME_FADE_HANDLER_H
