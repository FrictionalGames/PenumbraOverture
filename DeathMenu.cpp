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
#include "DeathMenu.h"

#include "Init.h"
#include "Player.h"
#include "MapHandler.h"
#include "GraphicsHelper.h"
#include "SaveHandler.h"
#include "MainMenu.h"
#include "HapticGameCamera.h"

//////////////////////////////////////////////////////////////////////////
// BUTTON
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

cDeathMenuButton::cDeathMenuButton(cInit *apInit, cVector2f avPos, const tWString& asText)
{
	mpInit = apInit;
	mpDrawer = mpInit->mpGame->GetGraphics()->GetDrawer();

	mvPositon = cVector3f(avPos.x, avPos.y, 40);

	mvFontSize = cVector2f(21,21);
	msText = asText;

	mpFont = mpInit->mpGame->GetResources()->GetFontManager()->CreateFontData("verdana.fnt");

	mRect.w = mpFont->GetLength(mvFontSize,msText.c_str());
	mRect.h = mvFontSize.y +3;
	mRect.x = avPos.x - mRect.w/2;
	mRect.y = avPos.y+3;

	mfAlpha = 0;
	mbOver = false;
}

cDeathMenuButton::~cDeathMenuButton()
{
	mpInit->mpGame->GetResources()->GetFontManager()->Destroy(mpFont);
}

//-----------------------------------------------------------------------

void cDeathMenuButton::OnUpdate(float afTimeStep)
{
	if(mbOver)
	{
		mfAlpha += 0.8f * afTimeStep;
		if(mfAlpha > 1)mfAlpha = 1;
	}
	else
	{
		mfAlpha -= 1.6f * afTimeStep;
		if(mfAlpha < 0)mfAlpha = 0;
	}
}

//-----------------------------------------------------------------------

void cDeathMenuButton::OnDraw()
{
	float fAlpha = mpInit->mpDeathMenu->mfAlpha;

	mpFont->Draw(mvPositon,mvFontSize,cColor(0.8f,0.7f,0.7f,fAlpha),eFontAlign_Center,msText.c_str());

	mpFont->Draw(mvPositon+cVector3f(0,0,1),mvFontSize,cColor(1,0,0,fAlpha*mfAlpha),eFontAlign_Center,msText.c_str());
}

//-----------------------------------------------------------------------

void cDeathMenuButton::OnMouseOver(bool abOver)
{
	mbOver = abOver;
}

//-----------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////
// CONTINUE
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

void cDeathMenuButton_Continue::OnMouseDown()
{
	tWString sAuto = _W("save/auto/") + mpInit->mpSaveHandler->GetLatest(_W("save/auto/"),_W("*.sav"));
	tWString sSpot = _W("save/spot/") + mpInit->mpSaveHandler->GetLatest(_W("save/spot/"),_W("*.sav"));

	tWString sFile = _W("");

	if(sAuto == _W("save/auto/"))
	{
		sFile = sSpot;
	}
	else if(sSpot == _W("save/spot/"))
	{
		sFile = sAuto;
	}
	else
	{
		tWString sSaveDir = mpInit->mpSaveHandler->GetSaveDir();
		cDate dateAuto = FileModifiedDate(sSaveDir +sAuto);
		cDate dateSpot = FileModifiedDate(sSaveDir +sSpot);

		if(dateAuto > dateSpot)
			sFile = sAuto;
		else
			sFile = sSpot;
	}

	if(sFile != _W(""))
		mpInit->mpSaveHandler->LoadGameFromFile(sFile);
}

//-----------------------------------------------------------------------

void cDeathMenuButton_Continue::OnMouseUp()
{

}
//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// BACK TO MAIN
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

void cDeathMenuButton_BackToMain::OnMouseDown()
{
	mpInit->ResetGame(true);
	mpInit->mpMainMenu->SetActive(true);
}

//-----------------------------------------------------------------------

void cDeathMenuButton_BackToMain::OnMouseUp()
{

}
//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

cDeathMenu::cDeathMenu(cInit *apInit)  : iUpdateable("NumericalPanel")
{
	mpInit = apInit;
	mpDrawer = mpInit->mpGame->GetGraphics()->GetDrawer();

	//Load graphics (use notebook background for now).
	mpGfxBackground = mpDrawer->CreateGfxObject("notebook_background.bmp","diffalpha2d");

	mpFont = mpInit->mpGame->GetResources()->GetFontManager()->CreateFontData("verdana.fnt");

	Reset();
}

//-----------------------------------------------------------------------

cDeathMenu::~cDeathMenu(void)
{
	STLDeleteAll(mlstButtons);

	mpDrawer->DestroyGfxObject(mpGfxBackground);
}

//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------

void cDeathMenu::Reset()
{
	mbActive = false;
	mfAlpha =0;
	mbMouseIsDown = false;
}

//-----------------------------------------------------------------------

void cDeathMenu::OnDraw()
{
	if(mfAlpha == 0) return;

	mpDrawer->DrawGfxObject(mpGfxBackground,cVector3f(0,0,0),cVector2f(800,600),cColor(1,mfAlpha));

	mpFont->DrawWordWrap(	cVector3f(400,210,40),500,25,24,cColor(0.7f,0.3f,0.3f),eFontAlign_Center,
							kTranslate("DeathMenu","YouAreDead").c_str());

	////////////////////////////////
	// Update buttons
	tDeathMenuButtonListIt it = mlstButtons.begin();
	for(; it != mlstButtons.end(); ++it)
	{
		cDeathMenuButton *pButton = *it;

		pButton->OnDraw();
	}
}

//-----------------------------------------------------------------------

void cDeathMenu::Update(float afTimeStep)
{
	////////////////////////////////
	// Check active and fade
	if(mbActive==false)
	{
		mfAlpha -=2.5f * afTimeStep;
		if(mfAlpha < 0)mfAlpha =0;
		return;
	}
	else
	{
		//Bad hack fix... owell
		mpInit->mpPlayer->SetCrossHairState(eCrossHairState_Pointer);

		mfAlpha += 2.3f * afTimeStep;
		if(mfAlpha >1)mfAlpha =1;
	}

	////////////////////////////////
	// Update buttons
	tDeathMenuButtonListIt it = mlstButtons.begin();
	for(; it != mlstButtons.end(); ++it)
	{
		cDeathMenuButton *pButton = *it;

		pButton->OnUpdate(afTimeStep);

		if(cMath::PointBoxCollision(mvMousePos,pButton->GetRect()))
		{
			pButton->OnMouseOver(true);
		}
		else
		{
			pButton->OnMouseOver(false);
		}
	}
}

//-----------------------------------------------------------------------

void cDeathMenu::SetMousePos(const cVector2f &avPos)
{
	mvMousePos = avPos;
	mpInit->mpPlayer->SetCrossHairPos(mvMousePos);
}
void cDeathMenu::AddMousePos(const cVector2f &avRel)
{
	mvMousePos += avRel;

	if(mvMousePos.x < 0) mvMousePos.x =0;
	if(mvMousePos.x >= 800) mvMousePos.x =800;
	if(mvMousePos.y < 0) mvMousePos.y =0;
	if(mvMousePos.y >= 600) mvMousePos.y =600;

	mpInit->mpPlayer->SetCrossHairPos(mvMousePos);
}

//-----------------------------------------------------------------------

void cDeathMenu::OnMouseDown(eMButton aButton)
{
	////////////////////////////////
	// Update buttons
	tDeathMenuButtonListIt it = mlstButtons.begin();
	for(; it != mlstButtons.end(); ++it)
	{
		cDeathMenuButton *pButton = *it;

		if(cMath::PointBoxCollision(mvMousePos,pButton->GetRect()))
		{
			pButton->OnMouseDown();
		}
	}

	mbMouseIsDown = true;
}

void cDeathMenu::OnMouseUp(eMButton aButton)
{
	////////////////////////////////
	// Update buttons
	tDeathMenuButtonListIt it = mlstButtons.begin();
	for(; it != mlstButtons.end(); ++it)
	{
		cDeathMenuButton *pButton = *it;

		if(cMath::PointBoxCollision(mvMousePos,pButton->GetRect()))
		{
			pButton->OnMouseUp();
		}
	}

	mbMouseIsDown = false;
}

//-----------------------------------------------------------------------

void cDeathMenu::SetActive(bool abX)
{
	if(mbActive == abX) return;

	mbActive = abX;

	if(mbActive)
	{
		if(mpInit->mbHasHaptics)
			mpInit->mpPlayer->GetHapticCamera()->SetActive(false);

		mLastCrossHairState = mpInit->mpPlayer->GetCrossHairState();

		mpInit->mpPlayer->SetCrossHairPos(mvMousePos);
		mpInit->mpPlayer->SetCrossHairState(eCrossHairState_Pointer);

		STLDeleteAll(mlstButtons);

		//Continue
		tWString sAuto = mpInit->mpSaveHandler->GetLatest(_W("save/auto/"),_W("*.sav"));
		tWString sSpot = mpInit->mpSaveHandler->GetLatest(_W("save/spot/"),_W("*.sav"));
		if(sAuto != _W("") || sSpot != _W(""))
		{
			mlstButtons.push_back(hplNew( cDeathMenuButton_Continue, (mpInit,cVector2f(400,290),kTranslate("DeathMenu","Continue"))) );
		}

		//Back to Main
		mlstButtons.push_back(hplNew( cDeathMenuButton_BackToMain, (mpInit,cVector2f(400,350),kTranslate("DeathMenu","BackToMainMenu")) ) );
	}
	else
	{
		if(mpInit->mbHasHaptics)
			mpInit->mpPlayer->GetHapticCamera()->SetActive(true);

		mpInit->mpPlayer->SetCrossHairState(mLastCrossHairState);
		mpInit->mpPlayer->SetCrossHairPos(cVector2f(400,300));
	}
}

//-----------------------------------------------------------------------

void cDeathMenu::OnExit()
{
	SetActive(false);
}

//-----------------------------------------------------------------------
