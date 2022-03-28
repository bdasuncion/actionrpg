#include "GBATypes.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBAObject.h"
#include "GBABG.h"
#include "GBAInterrupt.h"
#include "ManagerSound.h"
#include "ManagerCharacters.h"

#include "GBATimer.h"
#include "UtilCommonValues.h"

void updateGameStatus() {
//	int time;

//for profiling the whole gameloop
//	profile_start();
	msound_changeBuf();
	moam_update();
	mchar_draw();
	mscr_draw();
//	resetSpecial();

//temp
	//gbatimer_profileStart();
	//copyImageToVRAM();
	//should call draw from function?
	//player->draw(player);
	//timeTotal = gbatimer_profileStop();
		
	mprinter_print();
	gbaint_requestVBlankAck();
}