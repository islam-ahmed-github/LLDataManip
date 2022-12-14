/*
 * Jsons.c
 *
 *  Created on: Dec 20, 2019
 *      Author: Islam Ahmed
 */



#include "Commons.h"





 uint32 CalculateCorrelation( const uint8* A , const uint8* B , uint32 Len )
{
  uint32 DiffSum = 0 , i ;
  for(i=0; i< Len;i++)
  {
      DiffSum += (A[i]-B[i]);
      if(DiffSum>0) return DiffSum;
  }
  return 0;
}





uint32 Jsons_AddKV( const uint8* KeyNULLTerminated, const uint8* ValueNULLTerminated, uint8 IsStringValue ,uint8* Dest, uint32 DestCurrentLen)
{
    uint32 Index = 0,  i=0;

    if(DestCurrentLen==0)
    {
       Dest[0] = '{';
       Dest[1] = '\n';
       Index   =  2 ;
    }
    else
    {
       Index = DestCurrentLen-3;
       Dest[Index]= ',';
       Dest[Index+1] = '\n';
       Index+=2;
    }

       Dest[Index]= '"';  Index++;
       while(KeyNULLTerminated[i]!='\0')
        {
          Dest[Index] = KeyNULLTerminated[i];
          Index++;
          i++;
        }
       Dest[Index] = '"';  Index++;
       Dest[Index] = ':';  Index++;
       if(IsStringValue){ Dest[Index] = '"';  Index++;}
       i=0;
       while(ValueNULLTerminated[i]!='\0')
        {
          Dest[Index] = ValueNULLTerminated[i];
          Index++;
          i++;
        }
       if(IsStringValue){ Dest[Index] = '"';  Index++;}
        Dest[Index] = '\n';  Index++;
        Dest[Index] = '}';   Index++;
        Dest[Index] = '\0';  Index++;

        return Index; // length including null termination character
}// end function








uint32  Jsons_GetValue( const uint8* JsonNULLTerminated , const uint8* KeyNULLTerminated, uint8* ValueDest)
{

    uint32 Kstart = 1;
    uint32 Klen   = 0;
    uint8 KinLen  = 0;
    while( KeyNULLTerminated[KinLen]!='\0' ) KinLen++;

  while(JsonNULLTerminated[Kstart]!='\0')
  {
    while(JsonNULLTerminated[Kstart]!='"')Kstart++;
    Kstart++;
    Klen = 0;
    while(JsonNULLTerminated[Kstart+Klen]!='"')Klen++;

    if( (KinLen==Klen)  && (CalculateCorrelation( (uint8*)(JsonNULLTerminated+Kstart) , KeyNULLTerminated,Klen)==0) )// this key matched
    {
     // copy value
      if(JsonNULLTerminated[Kstart+Klen+2]=='"')
      {
          Kstart= Kstart+Klen+3;
          Klen = 0 ;
          while(JsonNULLTerminated[Kstart+Klen]!='"')
            {
              ValueDest[Klen] = JsonNULLTerminated[Kstart+Klen];
              Klen++;
            }
      }
      else
      {
          Kstart= Kstart+Klen+2;
          Klen = 0 ;
          while( (JsonNULLTerminated[Kstart+Klen]!=',') && (JsonNULLTerminated[Kstart+Klen]!='}') )
            {
              ValueDest[Klen] = JsonNULLTerminated[Kstart+Klen];
              Klen++;
            }
      }

         ValueDest[Klen]='\0';
         return Klen+1;
    }
    else // key not matched
    {
          Kstart+=Klen;
          while((JsonNULLTerminated[Kstart]!=',') && (JsonNULLTerminated[Kstart]!='}') )Kstart++;
          if(JsonNULLTerminated[Kstart]=='}') return 0 ;
    }
 }// end outter while

 return 0 ;

}// end function
