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
#ifndef GAME_HUD_MODEL_THROW_H
#define GAME_HUD_MODEL_THROW_H

#include "StdAfx.h"
#include "GameTypes.h"

#include "PlayerHands.h"

using namespace hpl;

class cInventoryItem;

//-------------------------------------------

class cHudModel_Throw : public iHudModel
{
	friend class cPlayerHands;
public:
	cHudModel_Throw();

	void LoadData(TiXmlElement *apRootElem);
	
	void OnStart();

	void OnAttackDown();
	void OnAttackUp();

	bool OnMouseMove(const cVector2f &avMovement);

	bool UpdatePoseMatrix(cMatrixf& aPoseMtx, float afTimeStep);

	void SetItem(cInventoryItem *apItem){ mpItem = apItem;}
private:
	void ResetExtraData();

	bool mbButtonDown;
	float mfChargeCount;

	cHudModelPose mChargePose;

	float mfChargeTime;
	float mfMinImpulse;
	float mfMaxImpulse;

	float mfReloadTime;

	cVector3f mvTorque;

	tString msChargeSound;
	tString msThrowSound;

	tString msThrowEntity;

	cInventoryItem *mpItem;
};

//-------------------------------------------

#endif // GAME_HUD_MODEL_THROW_H
