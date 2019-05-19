/* 
 * Drag[en]gine Library -- Game Engine
 *
 * Copyright (C) 2004, Plüss Roland ( roland@rptd.dnsalias.net )
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

// includes
#include "../../config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decDiscFileWriter.h"
#include "../exceptions.h"

// class decDiscFileWriter
///////////////////////////
// constructor, destructor
decDiscFileWriter::decDiscFileWriter(const char *Filename, bool append){
	if(!Filename) THROW(dueInvalidParam);
	p_Filename = NULL;
	p_File = NULL;
	try{
		if(!(p_Filename = new char[strlen(Filename)+1])) THROW(dueOutOfMemory);
		strcpy(p_Filename, Filename);
		if(!(p_File = fopen(Filename, append ? "ab" : "wb"))) THROW(dueFileNotFound);
	}catch(duException){
		if(p_Filename) delete [] p_Filename;
		if(p_File) fclose(p_File);
		throw;
	}
}
decDiscFileWriter::~decDiscFileWriter(){
	fclose(p_File);
	delete [] p_Filename;
}
// management
const char *decDiscFileWriter::GetFilename(){
	return (const char *)p_Filename;
}
// reading
void decDiscFileWriter::Write(void *Buffer, int Size){
	if(fwrite(Buffer, Size, 1, p_File) != 1) THROW(dueReadFile);
}
