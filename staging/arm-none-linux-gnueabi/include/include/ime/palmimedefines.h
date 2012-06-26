/* @@@LICENSE
*
*      Copyright (c) 2010 - 2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */

#ifndef PALM_IME_DEFINES_H
#define PALM_IME_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cstring>

namespace PalmIME {

// type of the currently focused field
enum FieldType
{
	FieldType_Text = 0,
	FieldType_Password,
	FieldType_Search,
	FieldType_Range,
	FieldType_Email,
	FieldType_Number,
	FieldType_Phone,
	FieldType_URL,
	FieldType_Color
};

// actions that can be handled by the currently focused field
enum FieldAction
{
	FieldAction_None 		= 0x0,
	FieldAction_Done 		= 0x1,	// obsolete. Kept for simpler submissions
	FieldAction_Next 		= 0x2,
	FieldAction_Previous 	= 0x8,
	FieldAction_Search 		= 0x10	// obsolete. Kept for simpler submissions
};

// Misc flags & attributes of the currently focused field
enum FieldFlags
{
	FieldFlags_None			= 0x0,
	FieldFlags_Emoticons	= 0x1	// show graphic emoticons in place of textual emoticons
};

// information about the currently focused field
struct EditorState {

	FieldType	type;
	FieldAction	actions;
	FieldFlags	flags;
	char		enterKeyLabel[40];	// utf8 encoded

	EditorState(FieldType inType = FieldType_Text, FieldAction inActions = FieldAction_None, FieldFlags inFlags = FieldFlags_None) :
		type(inType), actions(inActions), flags(inFlags)
	{
		enterKeyLabel[0] = 0;
	}

	bool operator==(const EditorState& other) const {
		return type == other.type && actions == other.actions && flags == other.flags && strncmp(enterKeyLabel, other.enterKeyLabel, sizeof(enterKeyLabel)) == 0;
	}
};

/**
 * Define default language for keyboard layout
 */
#define IME_KBD_LANG_English      ((uint16_t)(0x0009))
#define IME_KBD_LANG_French       ((uint16_t)(0x000C))
#define IME_KBD_LANG_German       ((uint16_t)(0x0007))

/**
 * Define secondary keyboard layout code
 */
#define IME_KBD_SEC_PhonePad      ((uint16_t)0x0600)
#define IME_KBD_SEC_REGQwerty     ((uint16_t)0x0900)

}

#ifdef __cplusplus
}
#endif

#endif /* PALM_IME_DEFINES_H */
