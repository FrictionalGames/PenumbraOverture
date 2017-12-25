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
#ifndef GAME_DEATH_MENU_H
#define GAME_DEATH_MENU_H

#include "StdAfx.h"

#include "GameTypes.h"

using namespace hpl;

class cInit;


//---------------------------
class cDeathMenuButton
{
public:
	cDeathMenuButton(cInit *apInit, cVector2f avPos, const tWString& asText);
	virtual ~cDeathMenuButton();

	void OnUpdate(float afTimeStep);

	void OnDraw();

	virtual void OnMouseDown()=0;
	virtual void OnMouseUp()=0;

	void OnMouseOver(bool abOver);

	const cRect2f& GetRect(){return mRect;}

protected:
	float mfAlpha;

	cInit *mpInit;
	cGraphicsDrawer *mpDrawer;

	cVector3f mvPositon;
	cRect2f mRect;

	iFontData *mpFont;

	cVector2f mvFontSize;
	tWString msText;

	bool mbOver;
};

//---------------------------------------------

class cDeathMenuButton_Continue : public cDeathMenuButton
{
public:
	cDeathMenuButton_Continue(cInit *apInit, cVector2f avPos, const tWString& asText) :
								cDeathMenuButton(apInit, avPos, asText){}

	void OnMouseDown();
	void OnMouseUp();
};

//---------------------------------------------

class cDeathMenuButton_BackToMain : public cDeathMenuButton
{
public:
	cDeathMenuButton_BackToMain(cInit *apInit, cVector2f avPos, const tWString& asText) :
								cDeathMenuButton(apInit, avPos, asText){}

	void OnMouseDown();
	void OnMouseUp();
};

//---------------------------------------------

typedef std::list<cDeathMenuButton*> tDeathMenuButtonList;
typedef tDeathMenuButtonList::iterator tDeathMenuButtonListIt;

//---------------------------------------------

class cDeathMenu : public iUpdateable
{
	friend class cDeathMenuButton;
public:
	cDeathMenu(cInit *apInit);
	~cDeathMenu();

	void Reset();

	void OnDraw();

	void Update(float afTimeStep);

	void SetMousePos(const cVector2f &avPos);
	void AddMousePos(const cVector2f &avRel);
	cVector2f GetMousePos(){ return mvMousePos;}

	void OnMouseDown(eMButton aButton);
	void OnMouseUp(eMButton aButton);

	void SetActive(bool abX);
	bool IsActive(){ return mbActive;}

	void OnExit();
private:
	cInit *mpInit;
	cGraphicsDrawer *mpDrawer;

	cGfxObject *mpGfxBackground;

	bool mbMouseIsDown;

	bool mbActive;
	float mfAlpha;

	iFontData *mpFont;

	cVector2f mvMousePos;

	eCrossHairState mLastCrossHairState;

	tDeathMenuButtonList mlstButtons;
};

//---------------------------------------------


#endif // GAME_DEATH_MENU_H
