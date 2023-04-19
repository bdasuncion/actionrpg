#ifndef GBACharacterType
#define  GBACharacterType

#include "GBAObject.h"
#include "GBACharacter.h"

typedef enum CHARACTERTYPE {
    NONE = -1,
	STARTPLAYABLECHARTYPE,
    ALISA = STARTPLAYABLECHARTYPE,
	NAMELESS,
	ENDPLAYABLECHARACTERTYPE = NAMELESS,
	GHOSTHAND,
	GHOSTMAN,
	KNIGHTMARE,
	WEREWOLF,
	CROW,
	ZOMBIE
} CHARACTERTYPE;

typedef struct PaletteIdControl {
    u16 id:4;
	PALETTESTATUS status:1;
	CHARACTERTYPE type;
}ALIGN4 PaletteIdControl;

//typedef void (*FuncCharacterInit)(CharacterAttr *character, ControlTypePool* collection);
//typedef void (*FuncCharacterSet)(CharacterAttr *character);
#endif