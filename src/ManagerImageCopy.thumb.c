#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

void vramCopyVblank(CharacterAttr* imgData);
int numOfImages = 0;
CharacterAttr *listCopyImg[15];


void addImageTocopy(CharacterAttr* imgData)
{
	listCopyImg[numOfImages] = imgData;
	numOfImages++;
}

void copyImageToVRAM()
{
	int i;
	for(i = 0; i<numOfImages; i++)
	{
//		listCopyImg[i]->updateImage(listCopyImg[i]);
	}
	numOfImages = 0;
}