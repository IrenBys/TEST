#ifndef _FIFO_H_
#define _FIFO_H_
//--------------------------------------------------------------------------------------------------------------
#include "main.h"
//--------------------------------------------------------------------------------------------------------------
typedef struct _FIFO_s
{ 
	UINT 	 Head,
				 Tail,
				 Max;
  UCHAR *Data;
	
}FIFO_s, *pFIFO_s;
//--------------------------------------------------------------------------------------------------------------
pFIFO_s FifoCreateFIFO(UINT Max);
void FifoDeleteFIFO(pFIFO_s Point);
BOOL FifoCreatePairFIFO(pFIFO_s *inPoint, UINT inMax, pFIFO_s *outPoint, UINT outMax);
void FifoDeletePairFIFO(pFIFO_s *inPoint, pFIFO_s *outPoint);
BOOL FifoSetByteToFIFO(pFIFO_s Point, UCHAR Data);
UINT FifoSetNBytesToFIFO(pFIFO_s Point, UCHAR *Data, UINT Len);
BOOL FifoGetByteFromFIFO(pFIFO_s Point, UCHAR *Data);
UINT FifoGetNBytesFromFIFO(pFIFO_s Point, UCHAR *Data, UINT Len);
BOOL FifoGetNBytesFromFIFONoChangePoints(pFIFO_s Point, UCHAR *Data, UINT Len);
BOOL FifoSetByteNToFIFONoChangePoints(pFIFO_s Point, UCHAR Data, UINT N);
UINT FifoKeyhitFIFO(pFIFO_s Point);
UINT FifoPointPlus(UINT p, UINT max);
BOOL FifoFIFO2FIFO(pFIFO_s inPoint, pFIFO_s outPoint);

#endif 
