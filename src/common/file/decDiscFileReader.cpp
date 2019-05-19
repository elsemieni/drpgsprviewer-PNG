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
#include "decDiscFileReader.h"
#include "../exceptions.h"

// class decDiscFileReader
///////////////////////////
// constructor, destructor
decDiscFileReader::decDiscFileReader(const char *Filename){
	if(!Filename) THROW(dueInvalidParam);
	p_Filename = NULL;
	p_File = NULL;
	try{
		if(!(p_Filename = new char[strlen(Filename)+1])) THROW(dueOutOfMemory);
		strcpy(p_Filename, Filename);
		if(!(p_File = fopen(Filename, "rb"))) THROW(dueFileNotFound);
		if(fseek(p_File, 0, SEEK_END)) THROW(dueReadFile);
		p_Length = (int)ftell(p_File);
		if(fseek(p_File, 0, SEEK_SET)) THROW(dueReadFile);
	}catch(duException){
		if(p_File) fclose(p_File);
		if(p_Filename) delete [] p_Filename;
		throw;
	}
}
decDiscFileReader::~decDiscFileReader(){
	fclose(p_File);
	delete [] p_Filename;
}
// management
const char *decDiscFileReader::GetFilename(){
	return (const char *)p_Filename;
}
int decDiscFileReader::GetLength(){
	return p_Length;
}
int decDiscFileReader::GetPosition(){
	return (int)ftell(p_File);
}
// seeking
void decDiscFileReader::SetPosition(int Position){
	if(fseek(p_File, Position, SEEK_SET)) THROW(dueReadFile);
}
void decDiscFileReader::MovePosition(int Offset){
	if(fseek(p_File, Offset, SEEK_CUR)) THROW(dueReadFile);
}
void decDiscFileReader::SetPositionEnd(int Position){
	if(fseek(p_File, Position, SEEK_END)) THROW(dueReadFile);
}
// reading
void decDiscFileReader::Read(void *Buffer, int Size){
	if(fread(Buffer, Size, 1, p_File) != 1) THROW(dueReadFile);
}
