#include"GBAVideo.h"
#include "GBATypes.h"
#include"GBADMA.h"
#include "GBATimer.h"
#include "UtilCommonValues.h"//decompress
//0 = 0000 1 = 0001 2 = 0010 3 = 0011
//4 = 0100 5 = 0101 6 = 0110 7 = 0111
//8 = 1000 9 = 1001 10= 1010 11= 1011
//12= 1100 13= 1101 14= 1110 15= 1111

#define HEADER_IDX 0
#define DATA_IDX 1
#define COMPRESSED_DATA_MIN_LEN 3

const u32 addUncompressedLength[16][16] = 
{
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{3, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0},
	{2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 1, 0},
	{1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
};
//[shiftvalue][compressedData]
const u32 addShift[16][16] = 
{
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{4, 1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1},
	{3, 1, 2, 1, 3, 1, 2, 1, 3, 1, 2, 1, 3, 1, 2, 1},
	{2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct LzssDataHeader
{
	u16 copyLength:4;
	u16 lookbackOffset:12;
}ALIGN2 LzssDataHeader;

void lzssDecompress(u16	*dest, const u32* src)
{
	u32 count = ((src[HEADER_IDX])>>8);;
	u16	*srcData = src + DATA_IDX;
	u32 destIdx = 0;
	u32	dataType = 0;
	u32 lengthUncompressed = 0;
	u32 shiftData = 0;
	u32 compressedData = 0;
	int srcIdx = 0;
	
	for(srcIdx = 0; destIdx<count; )
	{
		if(shiftData == 0)
		{
			dataType = srcData[srcIdx];
			++srcIdx;
		}
		
		compressedData = 0;
		
		while(compressedData == 0 && shiftData<16)
		{
			//From the data type header of the compressed data, use 4 bit values
			//with addUncompressedLength and addShift array instead of shifting each bit
            //one by one.
			compressedData = (dataType>>shiftData)&0xF;
			lengthUncompressed += addUncompressedLength
				[shiftData][compressedData];
			shiftData += addShift[shiftData][compressedData];
		}
		shiftData &= 0xF;

		if(lengthUncompressed > 0)
		{
			if(destIdx + lengthUncompressed >= count)
				lengthUncompressed = count - destIdx;
			
			dma3_cpy16(&dest[destIdx], &srcData[srcIdx], lengthUncompressed);
			
			srcIdx += lengthUncompressed;
			destIdx += lengthUncompressed;
			
			lengthUncompressed = 0;
		}
		
		if(compressedData)
		{
			u32 length, copyFromIndex;
			LzssDataHeader *header = &srcData[srcIdx];
			length = header->copyLength;
			length += COMPRESSED_DATA_MIN_LEN;
			copyFromIndex = destIdx - header->lookbackOffset - 1;
			dma3_cpy16(&dest[destIdx], &dest[copyFromIndex], length);
			
			destIdx += length;
			++srcIdx;
		}
	}
}

u32 lzss2vram(const void* src, u32 id)
{
	u16	*dest = &VRAM->block[SPRITE_BLOCK].tile[id];
	lzssDecompress(dest, src);
	return 0;
}

void LZSSUncomp(void* src, void* dest)
{   
	asm volatile (
	"mov r0, %0\n"
	"mov r1, %1\n"
	"swi 0x12\n"
	:
	:"r" (src), "r" (dest)
	:"r0", "r1"
	);   
}

