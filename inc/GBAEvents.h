#ifndef GBAEvent
#define GBAEvent

#include "GBAObject.h"
#include "GBACharacter.h"

typedef struct EventCharacterActions {
    int status;
	int numberActions;
	int currentAction;
	int actorId;
	CharacterAttr *actionActor;
    const ActionControl *actions;
}ALIGN4 EventCharacterActions;

typedef void (*FuncEventControl)(void *eventControl);

typedef struct EventControl {
    int eventCount;
    int currentEvent;
    EventCharacterActions *actions;
    FuncEventControl eventController;
}ALIGN4 EventControl;
#endif