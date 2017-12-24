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
#ifndef GAME_GAME_MUSIC_HANDLER_H
#define GAME_GAME_MUSIC_HANDLER_H

#include "StdAfx.h"

#include "GameTypes.h"

using namespace hpl;

class cInit;
class cMapHandler;
class cGameMusicHandler_GlobalSave;
class iGameEnemy;

//----------------------------------------

class cGameMusic
{
friend class cGameMusicHandler;
public:
	cGameMusic();

	void Reset();

private:
	tString msFile;

	bool mbLoop;
	float mfVolume;
};

//----------------------------------------

typedef std::set<iGameEnemy*> tAttackerSet;
typedef tAttackerSet::iterator tAttackerSetIt;

class cGameMusicHandler : public iUpdateable
{
public:
	cGameMusicHandler(cInit *apInit);
	~cGameMusicHandler();

	void OnStart();
	void Update(float afTimeStep);
	void Reset();

	void OnWorldLoad();
	void OnWorldExit();

	void LoadFromGlobal(cGameMusicHandler_GlobalSave *apSave);
	void SaveToGlobal(cGameMusicHandler_GlobalSave *apSave);

	void Play(const tString &asFile, bool abLoop,float afVolume, float afFade, int alPrio);
	void Stop(float afFade, int alPrio);

	void AddAttacker(iGameEnemy *apEntity);
	void RemoveAttacker(iGameEnemy *apEntity);
	bool AttackerExist(iGameEnemy *apEntity);

private:
	void PlayHighestPriority();

	cInit *mpInit;
	cMusicHandler *mpMusicHandler;

	std::vector<cGameMusic> mvGameMusic;
	int mlMaxPrio;

	int mlCurrentMaxPrio;

	tAttackerSet m_setAttackers;

	bool mbAttackPlaying;
	float mfAttackPlayCount;
	float mfAttackStopCount;

	bool mbEnemyClosePlaying;
	float mfEnemyCloseCount;
	float mfEnemyGoneCount;
};



#endif // GAME_GAME_MUSIC_HANDLER_H
