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
#include "GraphicsHelper.h"

#include "Init.h"

//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

cGraphicsHelper::cGraphicsHelper(cInit *apInit)
{
	mpInit = apInit;

	mpLowLevelGfx = mpInit->mpGame->GetGraphics()->GetLowLevel();
	mpTexManager = mpInit->mpGame->GetResources()->GetTextureManager();

	mpDrawer = mpInit->mpGame->GetGraphics()->GetDrawer();

	mpFont =mpInit->mpGame->GetResources()->GetFontManager()->CreateFontData("font_menu_small.fnt");

	mvVtx.resize(4);
}

cGraphicsHelper::~cGraphicsHelper()
{

}

//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

void cGraphicsHelper::ClearScreen(const cColor &aColor)
{
	mpLowLevelGfx->SetClearColor(aColor);
	mpLowLevelGfx->ClearScreen();
}

//-----------------------------------------------------------------------

void cGraphicsHelper::DrawTexture(iTexture *apTex, const cVector3f& avPos, const cVector3f& avSize,
								  const cColor &aColor)
{
	mpLowLevelGfx->SetDepthTestActive(false);
	mpLowLevelGfx->PushMatrix(eMatrix_ModelView);
	mpLowLevelGfx->SetIdentityMatrix(eMatrix_ModelView);
	mpLowLevelGfx->SetOrthoProjection(mpLowLevelGfx->GetVirtualSize(),-1000,1000);

	mvVtx[0] = cVertex(avPos + cVector3f(0,0,0),	cVector2f(0.01f,0.01f),aColor );
	mvVtx[1] = cVertex(avPos + cVector3f(avSize.x,0,0),	cVector2f(0.99f,0.01f),aColor);
	mvVtx[2] = cVertex(avPos + cVector3f(avSize.x,avSize.y,0),cVector2f(0.99f,0.99f),aColor);
	mvVtx[3] = cVertex(avPos +  cVector3f(0,avSize.y,0),	cVector2f(0.01f,0.99f),aColor);

	mpLowLevelGfx->SetBlendActive(false);

	for(int i=0;i<6;++i) mpLowLevelGfx->SetTexture(i,NULL);

	mpLowLevelGfx->SetTexture(0,apTex);

	mpLowLevelGfx->DrawQuad(mvVtx);

	mpLowLevelGfx->SetTexture(0,NULL);

	mpLowLevelGfx->PopMatrix(eMatrix_ModelView);
}

//-----------------------------------------------------------------------

void cGraphicsHelper::DrawLoadingScreen(const tString &asFile)
{
	iTexture *pTex= NULL;

	if(asFile != "")
		pTex = mpTexManager->Create2D(asFile,false);

	if(pTex || asFile == "")
	{
		ClearScreen(cColor(0,0));

		if(pTex) DrawTexture(pTex,cVector3f(0,0,0),cVector2f(800,600),cColor(1,1));

		mpFont->Draw(cVector3f(400,300,50),22,cColor(1,1),eFontAlign_Center,
					_W("%ls"),kTranslate("LoadTexts", "Loading").c_str());

		mpDrawer->DrawAll();

		SwapBuffers();
	}

	if(pTex) mpTexManager->Destroy(pTex);
}

//-----------------------------------------------------------------------

void cGraphicsHelper::SwapBuffers()
{
	mpLowLevelGfx->SwapBuffers();
}


//-----------------------------------------------------------------------
