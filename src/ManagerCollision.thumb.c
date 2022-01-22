#include "GBATypes.h"
#include "GBAObject.h"
#include "ManagerOAM.h"
#include "UtilCommonValues.h"

//Checn Collision according to character
//To be improved with direction
/*s32 checkCollision
(
	CHARACTER_ATTR* charaCheck,
	SpritePlanePosition* sprite_posNew,
	SpritePlanePosition* sprite_posCurr
)
{
	int i,j;
	int l1,l2,r1,r2,t1,t2,b1,b2;
	int dir;
	u32 nCollision = getNumChar();
	CHARACTER_ATTR *collide;
	SpritePlanePosition collidePosition;
	
	getDirection(&charaCheck->T_D_A_OI, &dir);
	
	for(i = charaCheck->positionList + 1; i<nCollision; i++)
	{
		collide = CharList[i];

		getPosFromCharAtt(collide, &collidePosition);
		
		t1 = sprite_posNew->y - charaCheck->stats[COLLISIONWIDTH];
		t2 = collidePosition.y - collide->stats[COLLISIONWIDTH];
		b1 = sprite_posNew->y - charaCheck->stats[COLLISIONWIDTH];
		b2 = collidePosition.y + collide->stats[COLLISIONWIDTH];
			
		if(t1>b2) break;
		if(b1<t2) break;
			
		l1 = sprite_posNew->x - charaCheck->stats[COLLISIONLENGTH];
		l2 = collidePosition.x - collide->stats[COLLISIONLENGTH];
		r1 = sprite_posNew->x + charaCheck->stats[COLLISIONLENGTH];
		r2 = collidePosition.x + collide->stats[COLLISIONLENGTH];
	
		if(r1<l2) continue;
		if(l1>r2) continue;

		//check here for direction where collision occured
		*sprite_posNew = *sprite_posCurr;
		setDirectionChecked(dir, &charaCheck->aiPathFind);
		setDirectionChecked((dir+1)&7, &charaCheck->aiPathFind);
		setDirectionChecked((dir-1)&7, &charaCheck->aiPathFind);
		return COLLIDE;
	}
	
	for(i = charaCheck->positionList - 1; i >= 0; i--)	
	{
		collide = CharList[i];
		
		getPosFromCharAtt(collide, &collidePosition);

		t1 = sprite_posNew->y - charaCheck->stats[COLLISIONWIDTH];
		t2 = collidePosition.y - collide->stats[COLLISIONWIDTH];
		b1 = sprite_posNew->y + charaCheck->stats[COLLISIONWIDTH];
		b2 = collidePosition.y + collide->stats[COLLISIONWIDTH];
			
		if(t1>b2) break;
		if(b1<t2) break;
			
		l1 = sprite_posNew->x - charaCheck->stats[COLLISIONLENGTH];
		l2 = collidePosition.x - collide->stats[COLLISIONLENGTH];
		r1 = sprite_posNew->x + charaCheck->stats[COLLISIONLENGTH];
		r2 = collidePosition.x + collide->stats[COLLISIONLENGTH];
	
		if(r1<l2) continue;
		if(l1>r2) continue;

		*sprite_posNew = *sprite_posCurr;
		setDirectionChecked(dir, &charaCheck->aiPathFind);
		setDirectionChecked((dir+1)&7, &charaCheck->aiPathFind);
		setDirectionChecked((dir-1)&7, &charaCheck->aiPathFind);
		return COLLIDE;
	}
	return NOCOLLIDE;
}

const s32 x16X16[8] = {0,1,1,1,0,-1,-1,-1};
const s32 y16X16[8] = {1,1,0,-1,-1,-1,0,1};

s32 checkBGCollision16X16
(
	CHARACTER_ATTR* chara,
	SpritePlanePosition* sprite_posNew,
	SpritePlanePosition* sprite_posCurr
)
{
	BG_object2Layers* backGround = getBackground();
	s32 positionX, positionY;
//	u32 blockX, blockY;
//	u32 quarterScrPos,*collisionBlock, collisionTile;
	u32 collisionTile;
	s32 direction;
	s32 status = NOCOLLIDE;
	int i;
	
	getDirection(&chara->T_D_A_OI, &direction);

	for(i = -1; i<2; i++)
	{
		//Get position in map
		positionX = sprite_posNew->x + 
		chara->stats[COLLISIONWIDTH]*x16X16[(direction + i)&7];
		
		if(positionX<0)
			positionX = 0;
		
		positionY = sprite_posNew->y + 
		chara->stats[COLLISIONLENGTH]*y16X16[(direction + i)&7];
		
		if(positionY<0)
			positionY = 0;
	
		collisionTile = backGround->collision[((positionY>>3)*backGround->collisionWidth) + (positionX>>6)];
		//Get value shift
		collisionTile = (collisionTile>>(MAXBITSHIFT - (((positionX&63)>>3)*4)))&15;

		if(collisionTile > 0)
		{
			//To be added: specific collision reaction
			*sprite_posNew = *sprite_posCurr;
			setDirectionChecked((direction + i)&7, &chara->aiPathFind);
			status = COLLIDE;
		}
	}
	return status;
}
/*
const s32 x32X32[16] = {0,8,15,15,15,15,15,8, 
						0,-8,-15,-15,-15,-15,-15,-8};
const s32 y32X32[16] = {15,15,15,8,0,-8,-15,-15,
						-15,-15,-15,-8,0,8,15,15};

s32 checkBGCollision32X32(CHARACTER_ATTR* chara)
{
	BG_object2Layers* backGround = getBackground();
	s32 positionX, positionY;
	u32 blockX, blockY;
	u32 quarterScrPos,*collisionBlock, collisionTile;
	int i;

	for(i = -2; i<3; i++)
	{
		//Get position in map
		positionX = backGround->H0 + chara->sprite_posNew.x + 
		x32X32[(chara->direction*2 + i)&15];
		
		if(positionX<0)
			positionX = 0;
		
		positionY = backGround->V0 + chara->sprite_posNew.y + 
		y32X32[(chara->direction*2 + i)&15];
		
		if(positionY<0)
			positionY = 0;
	
		//Get collision block where character is positioned
		blockX = positionX>>8;
		blockY =  (positionY>>8)*backGround->width;
	
		collisionBlock = &backGround->collision[blockX*HALFMAPBLOCK + blockY*HALFMAPBLOCK];
		
		//Get quarter screen area
		positionX -= blockX*MAPBLOCK;
		positionY -= (positionY>>8)*MAPBLOCK;
	
		quarterScrPos = positionX>>6;
		//Get collision value
		collisionTile = collisionBlock[((positionY>>3)*4) + quarterScrPos];
	
		//Get value shift
		if(((collisionTile>>(MAXBITSHIFT - (((positionX - 
			quarterScrPos*QUARTERMAPBLOCK)>>3)*4)))&15) > 0)
		{
			//To be added: specific collision reaction
			chara->sprite_posNew = chara->sprite_pos;
			return COLLIDE;
		}
	}
	return NOCOLLIDE;
}*/