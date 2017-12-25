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
#ifndef GAME_GAME_MESSAGE_HANDLER_H
#define GAME_GAME_MESSAGE_HANDLER_H

#include "StdAfx.h"

#include "GameTypes.h"

using namespace hpl;

class cInit;

class cGameMessageHandler;
class cGameMessage
{
public:
	cGameMessage(const tWString &asText, cGameMessageHandler *apMessHandler);

	void Update(float afTimeStep);
	void Draw(iFontData *apFont);

	bool mbActive;

	tWString msText;
	float mfFade;
	float mfFadeAdd;

	cGameMessageHandler *mpMessHandler;
};

typedef std::list<cGameMessage*> tGameMessageList;
typedef tGameMessageList::iterator tGameMessageListIt;

//---------------------------------------

class cGameMessageHandler : public iUpdateable
{
friend class cGameMessage;
public:
	cGameMessageHandler(cInit *apInit);
	~cGameMessageHandler();

	void Add(const tWString& asText);
	void ShowNext();

	void Update(float afTimeStep);
	void OnDraw();
	void Reset();

	void OnWorldLoad();
	void OnWorldExit();

	bool HasMessage(){ return !mlstMessages.empty();}

	void SetOnMessagesOverCallback(const tString& asFunction);

	void SetFocusIsedUsed(bool abX){mbFocusIsedUsed = abX;}

	void SetBlackText(bool abX){ mbBlackText = abX;}

private:
	cInit* mpInit;

	iFontData *mpFont;
	ePlayerState mLastState;
	tString msOverCallback;

	bool mbFocusIsedUsed;

	bool mbBlackText;

	tGameMessageList mlstMessages;
};

#endif // GAME_GAME_MESSAGE_HANDLER_H
