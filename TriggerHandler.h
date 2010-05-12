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
#ifndef GAME_TRIGGER_HANDLER_H
#define GAME_TRIGGER_HANDLER_H

#include "StdAfx.h"

#include "GameTypes.h"

using namespace hpl;

class cInit;
class cMapHandler;

//----------------------------------------

class cGameTrigger : public iEntity3D
{
friend class cTriggerHandler;
public:
	cGameTrigger();
	virtual ~cGameTrigger(){}
	
	int GetPrio(){ return mlPrio;}
	float GetTimeCount(){ return mfTimeCount;}
	eGameTriggerType GetType(){ return mType;}
	
	float GetRadius(){ return mfRadius;}
	void SetRadius(float afX);

	cBoundingVolume* GetBoundingVolume(){ return &mBoundingVolume;}
	
	virtual tString GetEntityType(){ return "GameTrigger"; }

protected:
	int mlPrio;
	float mfTimeCount;
	eGameTriggerType mType;
private:
	float mfRadius;
};

typedef std::multimap<int, cGameTrigger*, std::greater<int> > tGameTriggerMap;
typedef tGameTriggerMap::iterator tGameTriggerMapIt;

//----------------------------------------

class cTriggerHandler : public iUpdateable
{
public:
	cTriggerHandler(cInit *apInit);
	~cTriggerHandler();

	cGameTrigger* Add(cGameTrigger *apTrigger,eGameTriggerType aType , const cVector3f &avLocalPos,
												int alPrio, float afTime, float afRadius);

	void OnStart();
	void Update(float afTimeStep);
	void Reset();
private:
	cInit *mpInit;
	cMapHandler *mpMapHandler;

	tGameTriggerMap m_mapTriggers;
};



#endif // GAME_TRIGGER_HANDLER_H
