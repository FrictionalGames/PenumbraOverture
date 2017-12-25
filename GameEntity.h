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
#ifndef GAME_GAME_ENTITY_H
#define GAME_GAME_ENTITY_H

#include "StdAfx.h"

using namespace hpl;

#include "GameTypes.h"
#include "SaveTypes.h"

class cInit;
class iGameEntity;
class cInventoryItem;

//-----------------------------------------

class cGameEntityScript : public iSerializable
{
	kSerializableClassInit(cGameEntityScript)
public:
	cGameEntityScript() : msScriptFunc(""){}

	int mlNum;
	tString msScriptFunc;
};

typedef std::map<tString, cGameEntityScript*> tGameEntityScriptMap;
typedef tGameEntityScriptMap::iterator tGameEntityScriptMapIt;

//-----------------------------------------

typedef std::map<tString, int> tGameEntityVarMap;
typedef tGameEntityVarMap::iterator tGameEntityVarMapIt;

//------------------------------------------

class iGameEntity;

//------------------------------------------

class cGameEntityAnimation_SaveData : public iSerializable
{
	kSerializableClassInit(cGameEntityAnimation_SaveData)
public:
	bool mbActive;
	bool mbLoop;

	float mfWeight;
	float mfFadeStep;
	float mfTimePos;
	float mfSpeed;
};
//------------------------------------------

class iGameEntity_SaveData : public iSerializable
{
	kSerializableClassInit(iGameEntity_SaveData)
public:
	virtual ~iGameEntity_SaveData();

	bool mbActive;

	tString msFileName;

	tString msName;

	float mfHealth;

	float mfMaxExamineDist;
	float mfMaxInteractDist;

	bool mbHasBeenExamined;

	tWString msGameName;
	tWString msDescription;

	bool mbShowDescritionOnce;

	eGameEntityType mType;

	cMatrixf m_mtxTransform;

	//Engine types
	cContainerVec<cEngineBody_SaveData> mvBodies;
	cContainerVec<cEnginePS_SaveData> mvPS;
	cContainerVec<cEnginePS_SaveData> mvBeams;
	cContainerVec<cEngineLight_SaveData> mvLights;
	cContainerVec<cEngineSound_SaveData> mvSounds;

	cEnginePS_SaveData* GetParticleSystem(cParticleSystem3D* apPS);
	cEngineSound_SaveData* GetSoundEntity(cSoundEntity* apSound);

	//Animations
	cContainerVec<cGameEntityAnimation_SaveData> mvAnimations;

	//Callbacks
	cContainerList<cSaveGame_cGameCollideScript> mlstCollideCallbacks;

	cContainerList<cGameEntityScript> mlstCallbackScripts;

	//Script variables
	cContainerList<cScriptVar> mlstVars;

	//Creation
	virtual iGameEntity* CreateEntity()=0;
};

//------------------------------------------

class iGameEntity
{
friend class cPlayer;
public:
	iGameEntity(cInit *apInit, const tString &asName);
	virtual ~iGameEntity();

	const tString& GetName(){ return msName;}

	bool IsActive(){ return mbActive;}
	void SetActive(bool abX);
	virtual void OnSetActive(bool abX){}

	virtual bool IsSaved(){ return mbIsSaved;}

	virtual void OnWorldLoad(){}
	virtual void OnPostLoadScripts(){}
	virtual void OnWorldExit(){}
	virtual void Update(float afTimeStep){}
	virtual void OnDraw(){}
	virtual void OnPostSceneDraw(){}

	void OnUpdate(float afTimeStep);

	eGameEntityType GetType(){ return mType;}

	const tString& GetSubType(){ return msSubType;}

	void SetDescription(const tWString& asDesc){ msDescription = asDesc;}
	const tWString& GetDescription(){ return msDescription;}

	void SetShowDescritionOnce(bool abX){mbShowDescritionOnce = abX;}
	bool GetShowDescritionOnce(){ return mbShowDescritionOnce;}

	bool GetHasBeenExamined(){ return mbHasBeenExamined;}

	void SetGameName(const tWString& asName){ msGameName = asName;}
	const tWString& GetGameName(){ return msGameName;}

	iPhysicsBody *GetBody(int alNum){ return mvBodies[alNum];}
	int GetBodyNum(){ return (int)mvBodies.size();}
	void SetBodies(std::vector<iPhysicsBody*> &avBodies){ mvBodies = avBodies;}

	iPhysicsJoint *GetJoint(int alNum){ return mvJoints[alNum];}
	int GetJointNum(){ return (int)mvJoints.size();}
	void SetJoints(std::vector<iPhysicsJoint*> &avJoints){ mvJoints = avJoints;}

	int GetLightNum(){ return (int)mvLights.size();}
	iLight3D* GetLight(int alX){ return mvLights[alX];}
	void SetLights(std::vector<iLight3D*> &avLights){mvLights = avLights;}


	void SetParticleSystems(std::vector<cParticleSystem3D*> &avParticleSystems){mvParticleSystems = avParticleSystems;}
	void SetBillboards(std::vector<cBillboard*> &avBillboards){mvBillboards = avBillboards;}
	void SetBeams(std::vector<cBeam*> &avBeams){mvBeams = avBeams;}
	void SetSoundEntities(std::vector<cSoundEntity*> &avSoundEntities){mvSoundEntities = avSoundEntities;}

	size_t GetHapticShapeNum(){ return mvHapticShapes.size();}
	iHapticShape* GetHapticShape(size_t alNum){ return mvHapticShapes[alNum];}
	void SetHapticShapes(std::vector<iHapticShape*> &avShapes){mvHapticShapes = avShapes;}

	void DestroyLight(iLight3D *apLight);
	void DestroyParticleSystem(cParticleSystem3D* apPS);
	void DestroyBillboard(cBillboard* apBillboard);
	void SetSoundEntity(cSoundEntity* apSound);

	cMeshEntity *GetMeshEntity(){return mpMeshEntity;}
	void SetMeshEntity(cMeshEntity *apEnity){mpMeshEntity = apEnity;}

	void PlayerPick();
	void PlayerInteract();
	void PlayerExamine();

	virtual void OnPlayerPick(){}
	virtual void OnPlayerInteract(){}
	virtual void OnPlayerExamine();

	virtual bool OnUseItem(cInventoryItem *apItem){return false;}

	virtual void BreakAction(){}

	virtual void OnDamage(float afDamage){}
	virtual void OnDeath(float afDamage){}

	virtual void OnPlayerGravityCollide(iCharacterBody *apCharBody, cCollideData *apCollideData){}

	bool GetHasInteraction(){ return mbHasInteraction;}

	float GetMaxExamineDist(){ return mfMaxExamineDist;}
	void SetMaxExamineDist(float afX){ mfMaxExamineDist = afX;}
	float GetMaxInteractDist(){ return mfMaxInteractDist;}
	void SetMaxInteractDist(float afX){ mfMaxInteractDist = afX;}

	virtual eCrossHairState GetPickCrossHairState(iPhysicsBody *apBody);
	virtual float GetPickedDistance();

	void AddCollideScript(eGameCollideScriptType aType,const tString &asFunc, const tString &asEntity);
	void RemoveCollideScript(eGameCollideScriptType aType,const tString &asFunc);
	void RemoveCollideScriptWithChildEntity(iGameEntity *apEntity);

	void AddScript(eGameEntityScriptType aType,const tString &asFunc);
	void RemoveScript(eGameEntityScriptType aType);

	void CreateVar(const tString &asName, int alVal);
	void SetVar(const tString &asName, int alVal);
	void AddVar(const tString &asName, int alVal);
	int GetVar(const tString &asName);

	void Damage(float afDamage, int alStrength);
	float GetHealth(){ return mfHealth;}
	void SetHealth(float afHealth);

	void SetToughness(int alX){ mlToughness = alX;}
	int GetToughness(){ return mlToughness;}

	bool GetDestroyMe(){ return mbDestroyMe;}
	bool GetBreakMe(){ return mbBreakMe;}

	void Break(){ mbBreakMe = true;}

	void SetCharBody(iCharacterBody *apCharBody){ mpCharBody = apCharBody;}
	iCharacterBody* SetCharBody(){ return mpCharBody;}

	void SetUpTransMaterials();
	void SetTransActive(bool abX);

	void SetPauseControllers(bool abX){ mbPauseControllers = abX;}
	bool GetPauseControllers(){ return mbPauseControllers;}

	void SetPauseGravity(bool abX){ mbPauseGravity = abX;}
	bool GetPauseGravity(){ return mbPauseGravity;}

	const cMatrixf& GetOnLoadTransform(){ return m_mtxOnLoadTransform;}
	void SetOnLoadTransform(const cMatrixf& a_mtxPose){ m_mtxOnLoadTransform = a_mtxPose;}

	void SetLastImpulse(const cVector3f &avVec){ mvLastImpulse = avVec;}

	const tString& GetFileName(){ return msFileName;}

	cGameEntityScript* GetCallbackScript(eGameEntityScriptType aType) {return mvCallbackScripts[aType];}

	//Save data stuff
	void SetSaveData(iGameEntity_SaveData *apData){mpSaveData = apData;}
	iGameEntity_SaveData *GetSaveData(){ return mpSaveData;}

	virtual iGameEntity_SaveData* CreateSaveData()=0;
	virtual void LoadFromSaveData(iGameEntity_SaveData* apSaveData);
	virtual void SaveToSaveData(iGameEntity_SaveData* apSaveData);
	virtual void SetupSaveData(iGameEntity_SaveData *apSaveData);

protected:
	tString GetScriptCommand(eGameEntityScriptType aType);

	void PreloadModel(const tString &asFile);


	cInit *mpInit;

	bool mbActive;

	tString msFileName;

	bool mbIsSaved;

	bool mbDestroyMe;
	bool mbBreakMe;

	bool mbHasInteraction;

	bool mbHasBeenExamined;

	tString msName;

	tString msSubType;

	float mfHealth;
	int mlToughness;

	tWString msGameName;
	tWString msDescription;

	bool mbShowDescritionOnce;

	float mfMaxExamineDist;
	float mfMaxInteractDist;

	eGameEntityType mType;

	bool mbPauseControllers;
	bool mbPauseGravity;

	cMatrixf m_mtxOnLoadTransform;

	iGameEntity_SaveData *mpSaveData;

	std::vector<iPhysicsBody*> mvBodies;
	std::vector<iPhysicsJoint*> mvJoints;

	std::vector<iHapticShape*> mvHapticShapes;

	std::vector<iLight3D*> mvLights;
	std::vector<cParticleSystem3D*> mvParticleSystems;
	std::vector<cBillboard*> mvBillboards;
	std::vector<cBeam*> mvBeams;
	std::vector<cSoundEntity*> mvSoundEntities;

	bool mbSaveLights;

	cMeshEntity *mpMeshEntity;

	std::vector<iMaterial*> mvNormalMaterials;
	std::vector<iMaterial*> mvTransMaterials;
	bool mbTransActive;
	bool mbTransShadow;

	cVector3f mvLastImpulse;

	std::vector<cMesh*> mvPreloadedBreakMeshes;

	iCharacterBody *mpCharBody;

	cGameEntityScript *mvCallbackScripts[eGameEntityScriptType_LastEnum];
	tGameCollideScriptMap m_mapCollideCallbacks;

	tGameEntityVarMap m_mapVars;

	bool mbUpdatingCollisionCallbacks;
};



#endif // GAME_GAME_ENTITY_H
