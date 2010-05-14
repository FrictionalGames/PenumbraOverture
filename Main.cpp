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
//#include <vld.h>

#include "Init.h"

#include "SDL/SDL.h"

#ifdef WIN32
	#include <windows.h>
#endif

int hplMain(const tString& asCommandLine)
{
	cInit *pInit = hplNew( cInit, () );

	bool bRet = pInit->Init(asCommandLine);
	
	if(bRet==false){
		hplDelete( pInit->mpGame );
		CreateMessageBoxW(_W("Error!"),pInit->msErrorMessage.c_str());
		OpenBrowserWindow(_W("http://support.frictionalgames.com"));
		return 1;
	}

	pInit->Run();

	pInit->Exit();

	hplDelete( pInit );
	
	cMemoryManager::LogResults();

	return 0;
}
