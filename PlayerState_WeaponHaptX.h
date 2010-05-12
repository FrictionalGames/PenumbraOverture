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
#ifndef GAME_PLAYER_STATE_WEAPON_HAPTX_H
#define GAME_PLAYER_STATE_WEAPON_HAPTX_H

#include "StdAfx.h"
#include "PlayerState.h"

using namespace hpl;

//-----------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// THROW STATE
//////////////////////////////////////////////////////////////////////////

class cHudModel_Throw;

class cPlayerState_ThrowHaptX : public iPlayerState
{
public:
	cPlayerState_ThrowHaptX(cInit *apInit,cPlayer *apPlayer);

	void OnUpdate(float afTimeStep);

	void OnDraw();
	void OnPostSceneDraw();

	bool OnJump();

	void OnStartInteractMode();

	void OnStartInteract();
	void OnStopInteract();
	void OnStartExamine();
	void OnStartHolster();

	bool OnAddYaw(float afVal);
	bool OnAddPitch(float afVal);

	bool OnMoveForwards(float afMul, float afTimeStep);
	bool OnMoveSideways(float afMul, float afTimeStep);

	void EnterState(iPlayerState* apPrevState);
	void LeaveState(iPlayerState* apNextState);

	void OnStartRun();
	void OnStopRun();

	void OnStartCrouch();
	void OnStopCrouch();

	bool OnStartInventory();
	bool OnStartInventoryShortCut(int alNum);

	void SetHudObject(cHudModel_Throw* apHudObject){ mpHudObject = apHudObject;}

private:
	cHudModel_Throw *mpHudObject;
	float mfLastForward;
	float mfLastSideways;
};

//-----------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// WEAPON MELEE STATE
//////////////////////////////////////////////////////////////////////////

class cHudModel_WeaponMelee;

class cPlayerState_WeaponMeleeHaptX : public iPlayerState
{
public:
	
	cPlayerState_WeaponMeleeHaptX(cInit *apInit,cPlayer *apPlayer);
	
	void OnUpdate(float afTimeStep);
	
	void OnDraw();
	void OnPostSceneDraw();
	
	bool OnJump();
	
	void OnStartInteractMode();
	
	void OnStartInteract();
	void OnStopInteract();
	void OnStartExamine();
	void OnStartHolster();
	
	bool OnAddYaw(float afVal);
	bool OnAddPitch(float afVal);
	
	bool OnMoveForwards(float afMul, float afTimeStep);
	bool OnMoveSideways(float afMul, float afTimeStep);
	
	void EnterState(iPlayerState* apPrevState);
	void LeaveState(iPlayerState* apNextState);
	
	void OnStartRun();
	void OnStopRun();
	
	void OnStartCrouch();
	void OnStopCrouch();
	
	bool OnStartInventory();
	
	void SetHudWeapon(cHudModel_WeaponMelee* apHudWeapon){ mpHudWeapon = apHudWeapon;}
	cHudModel_WeaponMelee* GetHudWeapon(){ return mpHudWeapon;}

private:
	void PlaySound(const tString &asSound);
	bool CheckAttack(const cMatrixf& mtxTransform, float afSpeed);
	void HitBody(iPhysicsBody *apBody, float afMinImpulse, float afMaxImpulse,
				float afMinMass, float afMaxMass, 
				float afMinDamage, float afMaxDamage,
				int alStrength);

	iLowLevelHaptic *mpLowLevelHaptic;

	cHudModel_WeaponMelee *mpHudWeapon;
	float mfLastForward;
	float mfLastSideways;

	iCollideShape *mpCollider;
	//iPhysicsBody *mpBody;

	iHapticForce *mpSlowdownForce;
	iHapticForce *mpFeedbackForce;
	iHapticForce *mpImpulseForce;
	
	bool mbCollided;

	cVector3f mvPushBackVec;
	cVector3f mvPushBackPos;

	float mfAttackCount;

	bool mbInteractDown;
	int mlInteractCount;

	cVector3f mvRotation;
	cVector3f mvGoalRotation;
};

//-----------------------------------------------------------------


#endif // GAME_PLAYER_STATE_WEAPON_H
