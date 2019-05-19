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

#include <stdlib.h>
#include "decBaseFileReader.h"
#include "../exceptions.h"


// class decBaseFileReader
///////////////////////////
// destructor
decBaseFileReader::~decBaseFileReader(){
}
// helper functions
bool decBaseFileReader::IsEOF(){
	return GetPosition() == GetLength();
}
// reading
char decBaseFileReader::ReadChar(){
	char vValue;
	Read(&vValue, (int)sizeof(vValue));
	return vValue;
}
unsigned char decBaseFileReader::ReadByte(){
	unsigned char vValue;
	Read(&vValue, (int)sizeof(vValue));
	return vValue;
}
short decBaseFileReader::ReadShort(){
	short vValue;
	Read(&vValue, (int)sizeof(vValue));
	return vValue;
}
unsigned short decBaseFileReader::ReadUShort(){
	unsigned short vValue;
	Read(&vValue, (int)sizeof(vValue));
	return vValue;
}
int decBaseFileReader::ReadInt(){
	int vValue;
	Read(&vValue, (int)sizeof(vValue));
	return vValue;
}
unsigned int decBaseFileReader::ReadUInt(){
	unsigned int vValue;
	Read(&vValue, (int)sizeof(vValue));
	return vValue;
}
float decBaseFileReader::ReadFloat(){
	float vValue;
	Read(&vValue, (int)sizeof(vValue));
	return vValue;
}
char *decBaseFileReader::ReadString8(){
	unsigned char len;
	char *string = NULL;
	Read(&len, (int)sizeof(len));
	try{
		if(!(string = new char[len+1])) THROW(dueOutOfMemory);
		Read(string, len);
		string[len] = '\0';
	}catch(duException){
		if(string) delete [] string;
		throw;
	}
	return string;
}
char *decBaseFileReader::ReadString16(){
	unsigned short len;
	char *string = NULL;
	Read(&len, (int)sizeof(len));
	try{
		if(!(string = new char[len+1])) THROW(dueOutOfMemory);
		Read(string, len);
		string[len] = '\0';
	}catch(duException){
		if(string) delete [] string;
		throw;
	}
	return string;
}
void decBaseFileReader::SkipString8(){
	unsigned char len;
	Read(&len, (int)sizeof(len));
	MovePosition(len);
}
void decBaseFileReader::SkipString16(){
	unsigned short len;
	Read(&len, (int)sizeof(len));
	MovePosition(len);
}
