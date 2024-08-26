#include "GBATypes.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBAObject.h"
#include "GBABG.h"
#include "GBAInterrupt.h"
#include "ManagerSound.h"
#include "ManagerCharacters.h"
#include "ManagerGame.h"
#include "ManagerScrDisplay.h"
#include "ManagerPrinter.h"
#include "ManagerOAM.h"

#include "GBATimer.h"
#include "UtilCommonValues.h"

void updateGameStatus() {
	if (!isUpdateGameState()) {
		msound_changeBuf();
		gbaint_requestVBlankAck();
		return;
	}
	msound_changeBuf();
	moam_update();
	mchar_draw();
	mscr_draw();

	mprinter_print();
	gbaint_requestVBlankAck();
}