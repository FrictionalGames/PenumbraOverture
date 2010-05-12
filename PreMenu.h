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
#ifndef GAME_PRE_MENU_H
#define GAME_PRE_MENU_H

#include "StdAfx.h"

#include "GameTypes.h"

using namespace hpl;

class cRaindrop
{
public:
	cVector2f	vPos;
	cVector2f	vDir;
	float		fLength;
	float		fColor;
	
	cGfxObject *mpGfx;
};

class cInit;

//-------------------------------------------------

class cPreMenu : public iUpdateable
{
public:
	cPreMenu(cInit *apInit);
	~cPreMenu();

	void Reset();

	void OnPostSceneDraw();
	
	void OnDraw();
    
	void Update(float afTimeStep);
	
	void OnMouseDown(eMButton aButton);
	void OnButtonDown();

	void SetActive(bool abX);
	bool IsActive(){ return mbActive;}

	void OnExit();
private:
	void LoadConfig();

	cInit *mpInit;
	cGraphicsDrawer *mpDrawer;

	std::vector<iTexture*> mvTextures;
	tStringVec mvTexNames;

	iTexture* mpLogoTexture;
	iTexture* mpEpTexture;

	iFontData *mpFont;
	iFontData *mpTextFont;

	bool mbShowText;
	tWStringVec mvTextRows;
	int mlCurrentTextChar;
	int mlMaxChars;
	float mfNewCharCount;
	float mfClickCount;

	float mfAlpha;
	float mfAlphaAdd;

	int mlState;
	int mlCurrentLogo;

	bool mbActive;

	float mfStateTimer;

	cVector3f mvecLastTextPos;
	
	float mfLastTextSize;
	float mfLastTextColor;
	float mfLastTextSpeed1;
	float mfLastTextSpeed2;

	bool mbFadeWindSound;
	bool mbFadeRainSound;
	bool mbPlayingWindSound;
	bool mbPlayingRainSound;
	bool mbPlayingThunderSound;
	bool mbPlayingMusic;

	float mfFontColor;
	
	bool mbFlash;

	float mfLogoSizeFactor;
	
	float mfRaindropFade;

	cVector3f mvecLogoSize;
	float	mfLogoFade;
	float	mfEpFade;
	float	mfAdd;

	iSoundChannel* mpRainSound;
	iSoundChannel* mpWindSound;

	std::vector<cRaindrop> mvRaindropVector;
	cGfxObject*		mpRaindropGfx;
	cGfxObject*		mpFlashGfx;

};

//---------------------------------------------


#endif // GAME_PRE_MENU_H
