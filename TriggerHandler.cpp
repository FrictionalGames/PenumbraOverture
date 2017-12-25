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
#include "TriggerHandler.h"

#include "Init.h"
#include "MapHandler.h"
#include "GameEnemy.h"

//////////////////////////////////////////////////////////////////////////
// TRIGGER
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

cGameTrigger::cGameTrigger() : iEntity3D("")
{
	SetRadius(1);
}

//-----------------------------------------------------------------------

void cGameTrigger::SetRadius(float afX)
{
	mfRadius = afX;
	mBoundingVolume.SetSize(mfRadius*2);
}

//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

cTriggerHandler::cTriggerHandler(cInit *apInit)  : iUpdateable("TriggerHandler")
{
	mpInit = apInit;
}

//-----------------------------------------------------------------------

cTriggerHandler::~cTriggerHandler(void)
{
	STLMapDeleteAll(m_mapTriggers);
}

//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// PUBLIC METHODS
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

cGameTrigger* cTriggerHandler::Add(cGameTrigger *apTrigger,eGameTriggerType aType ,
								   const cVector3f &avLocalPos,
								   int alPrio, float afTime, float afRadius)
{
	apTrigger->SetRadius(afRadius);
	apTrigger->mfTimeCount = afTime;
	apTrigger->mlPrio = alPrio;
	apTrigger->mType = aType;
	apTrigger->SetPosition(avLocalPos);

	m_mapTriggers.insert(tGameTriggerMap::value_type(alPrio, apTrigger));

	return apTrigger;
}

//-----------------------------------------------------------------------

void cTriggerHandler::OnStart()
{
	mpMapHandler = mpInit->mpMapHandler;
}

//-----------------------------------------------------------------------

void cTriggerHandler::Update(float afTimeStep)
{
	//////////////////////////////////////////////
	//Go through the enemies and hand them triggers
	tGameEnemyIterator EnemyIt = mpMapHandler->GetGameEnemyIterator();
	while(EnemyIt.HasNext())
	{
		iGameEnemy *pEnemy = EnemyIt.Next();
		if(pEnemy->IsActive()==false || pEnemy->GetUsesTriggers()==false) continue;

		/////////////////////////////////////////
		//Check if it is time to update triggers.
		/*if(pEnemy->GetTriggerUpdateCount() >= pEnemy->GetTriggerUpdateRate())
		{
			pEnemy->SetTriggerUpdateCount(0);
		}
		else
		{
			pEnemy->SetTriggerUpdateCount(pEnemy->GetTriggerUpdateCount() + afTimeStep);
			continue;
		}*/

		/////////////////////////////////////
		//Go through triggers by priority
		tGameTriggerMapIt TriggerIt = m_mapTriggers.begin();
		for(; TriggerIt != m_mapTriggers.end(); ++TriggerIt)
		{
			cGameTrigger *pTrigger = TriggerIt->second;

			//Check if trigger is of right type
			if(!(pTrigger->GetType() & pEnemy->GetTriggerTypes()))
			{
				continue;
			}

			//Check if trigger is in reach
			if(cMath::PointBVCollision(pEnemy->GetPosition(),*pTrigger->GetBoundingVolume()) == false)
			{
				continue;
			}

			//Let enemy handle trigger, if false get next trigger else next enemy.
			if(pEnemy->HandleTrigger(pTrigger))
			{
				break;
			}
		}
	}

	//////////////////////////////////
	//Go through triggers and remove when timer is out.
	tGameTriggerMapIt TriggerIt = m_mapTriggers.begin();
	for(; TriggerIt != m_mapTriggers.end(); )
	{
		cGameTrigger *pTrigger = TriggerIt->second;

		pTrigger->mfTimeCount -= afTimeStep;

		if(pTrigger->mfTimeCount <= 0)
		{
			hplDelete( pTrigger );
			m_mapTriggers.erase(TriggerIt++);
		} else {
			++TriggerIt;
		}
	}
}

//-----------------------------------------------------------------------

void cTriggerHandler::Reset()
{

}
