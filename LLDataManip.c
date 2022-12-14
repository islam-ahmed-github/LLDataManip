/*
 * LLDataManip.c
 *
 *  Created on: Jan 6, 2020
 *      Author: Islam Ahmed
 */




#include "stdlib.h"
#include "inttypes.h"
#include "stdio.h"
#include <string.h>


#define DEBUG 0




static uint8  DM_Is_DecimalChar( uint8 AsciiOfDecimalChar0_9)
{
      switch( AsciiOfDecimalChar0_9)
      {
          case'0':    return 0;
          case'1':    return 1;
          case'2':    return 2;
          case'3':    return 3;
          case'4':    return 4;
          case'5':    return 5;
          case'6':    return 6;
          case'7':    return 7;
          case'8':    return 8;
          case'9':    return 9;
          default:    return 255;
      }

}


static uint8  DM_Is_DecimalChar2( const uint8* AsciiOfDecimalChar0_9 , uint32 len)
{
  if(0==len) return 0;
  for(uint32 i = 0 ; i< len ; i++)
  {
 	if(DM_Is_DecimalChar(AsciiOfDecimalChar0_9[i])==255) return 0;
  }
  return 1;
}





static uint8  DM_CharToNumerical( uint8 DecimalChar0_9)
{
      switch(DecimalChar0_9)
      {
          case'0':    return 0;
          case'1':    return 1;
          case'2':    return 2;
          case'3':    return 3;
          case'4':    return 4;
          case'5':    return 5;
          case'6':    return 6;
          case'7':    return 7;
          case'8':    return 8;
          case'9':    return 9;
          default:    return 255;
      }

}






uint64  DM_CharArrayToNumerical( const uint8* DecimalCharArray0_9 , uint8 len )
{

	uint8 i=0;
    uint64 factor=1;
    uint64 Sum=0 ;

     if(len<1) return 0xFFFFFFFFFFFFFFFF;
     if(DM_Is_DecimalChar2(  DecimalCharArray0_9 , len)==0) return  0xFFFFFFFFFFFFFFFF;



#if(DEBUG==1)
     uint64  Mul=0;
     uint8 tempN=0;
     printf("  ___ inside function len= %d",len);
#endif


     for(i =len-1 ; i<255 ;i--)
     {



#if(DEBUG==1)

    	 tempN = DM_CharToNumerical(DecimalCharArray0_9[i]);
    	  Mul = ( tempN  *factor);
    	  Sum += Mul;
    	 printf("\n inside func inside for i = %d ",i);
    	 printf("  ___ char= %d",tempN);
    	 printf("  __ fac= %" PRIu64, factor);
    	 printf("  __Mul= %" PRIu64,Mul);
    	 printf("  __sum= %"PRIu64, Sum);

#else
    	 Sum += ( DM_CharToNumerical(DecimalCharArray0_9[i]) *factor);
#endif
    	 factor*=10;



     }// end for
   return(uint64)Sum;
} // end func




char DM_CharArrayToNumerical2( const char* DecimalChArr09NullTerminated,  unsigned char StrLen, unsigned int * dest )
{

	unsigned char i=0;
    unsigned long  factor=1;
    unsigned long  Sum=0;
   // unsigned char  len = strlen(DecimalCharArray0_9);

     if(StrLen<1) return 0;
     if( DM_Is_DecimalChar2((const uint8*)DecimalChArr09NullTerminated,StrLen)==0  ) return 0;



#if(DEBUG==1)
     unsigned long   Mul=0;
     char tempN=0;
     printf("  ___ inside function len= %d", StrLen);
#endif


     for(i = StrLen-1; i<255; i--)
     {



#if(DEBUG==1)

    	 tempN = DM_CharToNumerical(DecimalChArr09NullTerminated[i]);
    	  Mul = ( tempN  *factor);
    	  Sum += Mul;
    	 printf("\n inside func inside for i = %d ",i);
    	 printf("  ___ char= %d",tempN);
    	 printf("  __ fac= %" PRIu64, factor);
    	 printf("  __Mul= %" PRIu64,Mul);
    	 printf("  __sum= %"PRIu64, Sum);

#else
    	 Sum += ( DM_CharToNumerical(DecimalChArr09NullTerminated[i]) *factor);
#endif
    	 factor*=10;



     }// end for


   *dest = (unsigned long )Sum;

   return 1;


} // end func










static uint8 To_Assci(uint8 num)
{
	switch(num)
	{

	case 0:   return'0';
	case 1:   return'1';
	case 2:   return'2';
	case 3:   return'3';
	case 4:   return'4';
	case 5:   return'5';
	case 6:   return'6';
	case 7:   return'7';
	case 8:   return'8';
	case 9:   return'9';
	default:  return 0 ;
	}
}




uint8 DM_NumericalToCharArray(uint8* destination,uint32 num)
{
	uint8 x=0;
	uint8 i= 0;
	uint  y=num;
	if(num==0)
	{
		destination[0]=To_Assci(0);
		i=1;
	}//end if
	else
	{
		while(y>0)
		{
		y/=10;
		i++;
		}

      for( uint8 j=i-1 ;num>0; j--)
	  {
	     x=num%10;
	     destination[j]=To_Assci(x);
	     num/=10;
	  }//end for
	}// end else

	destination[i]='\0';
	 return i;
}







uint32 DM_ReverseEndians32(uint32 arg)
{

	uint32 val = 0;
	uint8* ptr = &arg;
	if(0==arg) return0;

	val|=((uint32)(ptr[0])<<24);
	val|=((uint32)(ptr[1])<<16);
	val|=((uint32)(ptr[2])<<8);
	val|=((uint32)(ptr[3]));

	return val;

}




uint16 DM_ReverseEndians16(uint16 arg)
{
	uint16 val = 0;
	uint8* ptr = &arg;
    if(0==arg) return0;
	val|=((uint16)(ptr[0])<<8);
	val|=((uint16)(ptr[1]));

	return val;
}




















