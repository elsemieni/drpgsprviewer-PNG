/* 
 * Drag[en]gine Library -- Game Engine
 *
 * Copyright (C) 2004, Plüss Roland ( rptd@gmx.net )
 * 
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later 
 * version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#ifndef __NO_EXCEP_CPP__

// includes
#include "../../config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decException.h"

// definitions
#define STR_NULL	"(null)"

// class duException
//////////////////////
// constructors
duException::duException(const char *Name, const char *Description, const char *Info, const char *File, int Line){
	p_Name = Name;
	p_Desc = Description;
	p_Info = Info;
	p_File = File;
	p_Line = Line;
	if(!p_Name) p_Name = STR_NULL;
	if(!p_Desc) p_Desc = STR_NULL;
	if(!p_Info) p_Info = STR_NULL;
	if(!p_File) p_File = STR_NULL;
	if(p_Line < 0) p_Line = 0;
}
// management
bool duException::IsNamed(const char *Name) const{
	return strcmp(p_Name, Name) == 0;
}
void duException::PrintError(){
	printf("[EXCEPTION OCCURED]\n");
	printf("  Exception:   %s\n", p_Name);
	printf("  Description: %s\n", p_Desc);
	printf("  Infos:       %s\n", p_Info);
	printf("  Source File: %s\n", p_File);
	printf("  Source Line: %i\n", p_Line);
}

#endif
