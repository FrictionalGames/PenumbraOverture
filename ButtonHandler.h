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
#ifndef GAME_BUTTON_HANDLER_H
#define GAME_BUTTON_HANDLER_H

#include "StdAfx.h"

#include "GameTypes.h"

using namespace hpl;

class cInit;
class cPlayer;

class cButtonHandler : public iUpdateable
{
public:
	cButtonHandler(cInit *apInit);
	~cButtonHandler();

	void OnStart();
	void Update(float afTimeStep);
	void Reset();
	void OnExit();
	void OnPostSceneDraw();

	void SetDefaultKeys();

	tString GetActionName(const tString &asInputName,const tString &asSkipAction);

	void ChangeState(eButtonHandlerState aState);
	eButtonHandlerState GetState(){ return mState;}

	bool GetInvertMouseY(){ return mbInvertMouseY;}
	bool GetToggleCrouch(){ return mbToggleCrouch;}
	
	//Settings
	float mfMouseSensitivity;
	bool mbInvertMouseY;
	bool mbToggleCrouch;
private:
	iAction * ActionFromTypeAndVal(const tString& asName,const tString& asType, const tString& asVal);
	void TypeAndValFromAction(iAction *apAction, tString *apType, tString *apVal);
	
	int mlNumOfActions;

	cInit *mpInit;

	cInput* mpInput;
	iLowLevelGraphics *mpLowLevelGraphics;
	iLowLevelHaptic *mpLowLevelHaptic;

	cPlayer *mpPlayer;

	eButtonHandlerState mState;
};



#endif // GAME_BUTTON_HANDLER_H
