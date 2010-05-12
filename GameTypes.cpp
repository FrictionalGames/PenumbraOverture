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
#include "GameTypes.h"

#include "GameEntity.h"

//////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

cGameCollideScript::cGameCollideScript()
{
	msFuncName[0]=""; msFuncName[1]=""; msFuncName[2]="";
	mbCollides = false;
	mbDeleteMe = false;
}

//-----------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
// SERIALIZE
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------

kBeginSerializeBase(cGameTimer)
kSerializeVar(msName,eSerializeType_String)
kSerializeVar(msCallback,eSerializeType_String)

kSerializeVar(mbGlobal,eSerializeType_Bool)

kSerializeVar(mfTime,eSerializeType_Float32)

kSerializeVar(mbDeleteMe,eSerializeType_Bool)
kSerializeVar(mbPaused,eSerializeType_Bool)
kEndSerialize()
//-----------------------------------------------------------------------

kBeginSerializeBase(cSaveGame_cGameCollideScript)
kSerializeVarArray(msFuncName,eSerializeType_String,3)
kSerializeVar(msEntity, eSerializeType_String)
kSerializeVar(mbCollides, eSerializeType_Bool)
kEndSerialize()

//-----------------------------------------------------------------------

void cSaveGame_cGameCollideScript::LoadFrom(cGameCollideScript *apScript)
{
	msEntity = apScript->mpEntity->GetName();
	mbCollides = apScript->mbCollides;
	for(int i=0;i<3;++i) msFuncName[i] = apScript->msFuncName[i];
}

//-----------------------------------------------------------------------

void cSaveGame_cGameCollideScript::SaveTo(cGameCollideScript *apScript)
{
	apScript->mbCollides = mbCollides;
	for(int i=0;i<3;++i)  apScript->msFuncName[i] = msFuncName[i];
}

//-----------------------------------------------------------------------
