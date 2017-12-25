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
#ifndef GAME_GAME_DAMAGE_AREA_H
#define GAME_GAME_DAMAGE_AREA_H

#include "StdAfx.h"
#include "GameEntity.h"

using namespace hpl;

//------------------------------------------

class cGameDamageArea_SaveData : public iGameEntity_SaveData
{
	kSerializableClassInit(cGameDamageArea_SaveData);
public:
	cVector3f mvSize;

	float mfDamage;
	float mfUpdatesPerSec;
	int mlStrength;
	bool mbDisableObjects;
	bool mbDisableEnemies;

	iGameEntity* CreateEntity();
};

//------------------------------------------

class cGameDamageArea : public iGameEntity
{
#ifdef __GNUC__
	typedef iGameEntity __super;
#endif
	friend class cAreaLoader_GameDamageArea;
public:
	cGameDamageArea(cInit *apInit,const tString& asName);
	~cGameDamageArea(void);

	void OnPlayerPick();

	void Update(float afTimeStep);

	void SetDamage(float afX){ mfDamage = afX;}
	void SetUpdatesPerSec(float afX){ mfUpdatesPerSec = afX;}
	void SetStrength(int alX){ mlStrength = alX;}
	void SetDisableObjects(bool abX){ mbDisableObjects = abX;}
	void SetDisableEnemies(bool abX){ mbDisableEnemies = abX;}

	//SaveObject implementation
	iGameEntity_SaveData* CreateSaveData();
	void SaveToSaveData(iGameEntity_SaveData *apSaveData);
	void LoadFromSaveData(iGameEntity_SaveData *apSaveData);
	void SetupSaveData(iGameEntity_SaveData *apSaveData);

private:
	float mfDamage;
	float mfUpdatesPerSec;
	int mlStrength;
	bool mbDisableObjects;
	bool mbDisableEnemies;

	float mfUpdateCount;
};

//------------------------------------------

class cAreaLoader_GameDamageArea : public iArea3DLoader
{

public:
	cAreaLoader_GameDamageArea(const tString &asName, cInit *apInit);
	~cAreaLoader_GameDamageArea();

	iEntity3D* Load(const tString &asName, const cVector3f &avSize, const cMatrixf &a_mtxTransform,cWorld3D *apWorld);

private:

	cInit *mpInit;
};


#endif // GAME_GAME_DAMAGE_AREA_H
