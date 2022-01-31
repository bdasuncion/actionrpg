#ifndef GBACharacterType
#define  GBACharacterType

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
	CROW
} CHARACTERTYPE;

typedef void (*FuncCharacterInit)(CharacterAttr *character, ControlTypePool* collection);
typedef void (*FuncCharacterSet)(CharacterAttr *character);
#endif