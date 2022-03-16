#include "FIFO.h"

//--------------------------------------------------------------------------------------------------------------
// creates FIFO buffer
pFIFO_s FifoCreateFIFO(UINT Max)
{ pFIFO_s Point;

  Max++;
  
  if((Point = (pFIFO_s)(malloc(sizeof(FIFO_s)))) == NULL)
  { return NULL;
  }
  if((Point->Data = (UCHAR *)(malloc(Max))) == NULL)
  { free(Point);
    return NULL;
  }
  Point->Head = 1;
  Point->Tail = 0;
  Point->Max  = Max;
  return Point; 
}
//--------------------------------------------------------------------------------------------------------------
// deletes FIFO buffer
void FifoDeleteFIFO(pFIFO_s Point)
{ if(Point != NULL)
  { free(Point->Data);
    free(Point);
  }
}
//--------------------------------------------------------------------------------------------------------------
// creates a pair of FIFO buffers (input/output)
BOOL FifoCreatePairFIFO(pFIFO_s *inPoint, UINT inMax, pFIFO_s *outPoint, UINT outMax)
{ 
  FifoDeletePairFIFO(inPoint, outPoint);
  if((*inPoint = FifoCreateFIFO(inMax)) == NULL)
  { return FALSE;
  }
  
  if((*outPoint = FifoCreateFIFO(outMax)) == NULL)
  { 
    FifoDeleteFIFO(*inPoint);
    return FALSE;
  }
  return TRUE;
}
//--------------------------------------------------------------------------------------------------------------
// deletes a pair of FIFO buffers (input/output)
void FifoDeletePairFIFO(pFIFO_s *inPoint, pFIFO_s *outPoint)
{ 
  if(*inPoint != NULL)
  { FifoDeleteFIFO(*inPoint);
  }
  
  if(*outPoint != NULL)
  { FifoDeleteFIFO(*outPoint);
  }
}
//--------------------------------------------------------------------------------------------------------------
// writes byte in the FIFO
BOOL FifoSetByteToFIFO(pFIFO_s Point, UCHAR Data)
{ 
  if(Point->Head == Point->Tail)
  { return FALSE;
  }
  Point->Data[Point->Head] = Data;
  Point->Head = FifoPointPlus((Point->Head), Point->Max);
  return TRUE;
}
//--------------------------------------------------------------------------------------------------------------
// writes N bytes in the FIFO
UINT FifoSetNBytesToFIFO(pFIFO_s Point, UCHAR *Data, UINT Len)
{ UINT i;
  
  for(i = 0; i < Len; i++)
  { 
    if(FifoSetByteToFIFO(Point, Data[i]) == FALSE)
    { break;
    }
  }
  return i;
}
//--------------------------------------------------------------------------------------------------------------
// reads byte in the FIFO
BOOL FifoGetByteFromFIFO(pFIFO_s Point, UCHAR *Data)
{ 
  if(!FifoKeyhitFIFO(Point))
  { return FALSE;
  }
  
  Point->Tail = FifoPointPlus(Point->Tail, Point->Max);
  *Data = Point->Data[Point->Tail];
  return TRUE;
}
//--------------------------------------------------------------------------------------------------------------
// reads N bytes in the FIFO
UINT FifoGetNBytesFromFIFO(pFIFO_s Point, UCHAR *Data, UINT Len)
{ UINT i;
  
  for(i = 0; i < Len; i++)
  { 
    if(FifoGetByteFromFIFO(Point, &Data[i]) == FALSE)
    { break;
    }
  }
  return i;
}
//--------------------------------------------------------------------------------------------------------------
// returns the number of unprocessed bytes in the FIFO
UINT FifoKeyhitFIFO(pFIFO_s Point)
{ if(Point->Head > Point->Tail)
  {
		return (Point->Head - Point->Tail - 1); 
  }else
  { 
		return (Point->Max - (Point->Tail - Point->Head) - 1); 
  }
}
//--------------------------------------------------------------------------------------------------------------
// increments the pointer based onthe lenght of FIFO
UINT FifoPointPlus(UINT p, UINT max)
{ if(++p >= max)
  { p = 0;
  }
  return p;
} 
//--------------------------------------------------------------------------------------------------------------
// overwrites all  unprocessed bytes from FIFO to FIFO
BOOL FifoFIFO2FIFO(pFIFO_s inPoint, pFIFO_s outPoint)
{ UCHAR Data;
// while returns the number of unprocessed bytes in the FIFO
  while(FifoKeyhitFIFO(inPoint))       
  { // overflow
    if(outPoint->Head == outPoint->Tail)
    { 
      return FALSE;
    }
    FifoGetByteFromFIFO(inPoint, &Data);
    if(FifoSetByteToFIFO(outPoint, Data) == FALSE)
    { return FALSE;
    }
  }
  return TRUE;
}



