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
#include <string.h>
#include "decBaseFileWriter.h"

// class decBaseFileWriter
///////////////////////////
// destructor
decBaseFileWriter::~decBaseFileWriter(){
}
// writing
void decBaseFileWriter::WriteChar(char Value){
	Write(&Value, (int)sizeof(Value));
}
void decBaseFileWriter::WriteByte(unsigned char Value){
	Write(&Value, (int)sizeof(Value));
}
void decBaseFileWriter::WriteShort(short Value){
	Write(&Value, (int)sizeof(Value));
}
void decBaseFileWriter::WriteUShort(unsigned short Value){
	Write(&Value, (int)sizeof(Value));
}
void decBaseFileWriter::WriteInt(int Value){
	Write(&Value, (int)sizeof(Value));
}
void decBaseFileWriter::WriteUInt(unsigned int Value){
	Write(&Value, (int)sizeof(Value));
}
void decBaseFileWriter::WriteFloat(float Value){
	Write(&Value, (int)sizeof(Value));
}
void decBaseFileWriter::WriteString(const char *String){
	Write( (void*)String, strlen(String) );
}
void decBaseFileWriter::WriteString8(const char *String){
	unsigned char vLen = (unsigned char)strlen(String);
	Write(&vLen, sizeof(vLen));
	Write((void*)String, vLen);
}
void decBaseFileWriter::WriteString16(const char *String){
	unsigned short vLen = (unsigned short)strlen(String);
	Write(&vLen, sizeof(vLen));
	Write((void*)String, vLen);
}
