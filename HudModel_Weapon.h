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
#ifndef GAME_HUD_MODEL_WEAPON_H
#define GAME_HUD_MODEL_WEAPON_H

#include "StdAfx.h"
#include "GameTypes.h"

#include "PlayerHands.h"

using namespace hpl;

class cMeleeWeaponAttack
{
public:
	cHudModelPose mStart;
	cHudModelPose mEnd;
	
	float mfAttackLength;
	float mfChargeLength;
	float mfTimeOfAttack;

	float mfMaxImpulse;
	float mfMinImpulse;

	float mfMinMass;
	float mfMaxMass;

	float mfMinDamage;
	float mfMaxDamage;

	cVector3f mvSpinMul;

	float mfDamageRange;
	cVector3f mvDamageSize;

	float mfAttackRange;

	float mfAttackSpeed;
	int mlAttackStrength;

	tString msHitPS;
	int mlHitPSPrio;

	tString msSwingSound;
	tString msChargeSound;
	tString msHitSound;

	iCollideShape *mpCollider;
	cBoundingVolume mBV;
};

//-------------------------------------------

class cMeleeRayCallback : public iPhysicsRayCallback
{
public:
	void Reset();
	bool OnIntersect(iPhysicsBody *pBody,cPhysicsRayParams *apParams);

	iPhysicsBody *mpClosestBody;
	float mfShortestDist;
	cVector3f mvPosition;
	cVector3f mvNormal;
};

//-------------------------------------------

class cHudModel_WeaponMelee : public iHudModel
{
	friend class cPlayerHands;
public:
	cHudModel_WeaponMelee();

	void LoadData(TiXmlElement *apRootElem);
	
	void OnAttackDown();
	void OnAttackUp();

	bool OnMouseMove(const cVector2f &avMovement);

	bool UpdatePoseMatrix(cMatrixf& aPoseMtx, float afTimeStep);
	
	void PostSceneDraw();

	bool IsAttacking();

	cVector3f GetHapticSize(){ return mvHapticSize;}
	float GetHapticScale(){ return mfHapticScale;}
	cVector3f GetHapticRot(){ return mvHapticRot;}


	cMeleeWeaponAttack* GetAttack(int alX){return  &mvAttacks[alX];}
private:
	void ResetExtraData();

	void Attack();
	void HitBody(iPhysicsBody *apBody);

	void PlaySound(const tString &asSound);
	
	void LoadExtraEntites();
	void DestroyExtraEntities();

	bool mbDrawDebug;

	int mlCurrentAttack;
	int mlAttackState;
	float mfTime;

	float mfHapticScale;
	cVector3f mvHapticSize;
	cVector3f mvHapticRot;

	cMatrixf m_mtxPrevPose;
	cMatrixf m_mtxNextPose;
	
	float mfMoveSpeed;

	bool mbButtonDown;
	bool mbAttacked;

	cMeleeRayCallback mRayCallback;
	
	std::vector<cMeleeWeaponAttack> mvAttacks;

	iLowLevelHaptic *mpLowLevelHaptic;
	iHapticForce *mpHHitForce;
};

//-------------------------------------------

#endif // GAME_HUD_MODEL_WEAPON_H
