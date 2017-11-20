// ==++==
//
//   
//    Copyright (c) 2006 Microsoft Corporation.  All rights reserved.
//   
//    The use and distribution terms for this software are contained in the file
//    named license.txt, which can be found in the root of this distribution.
//    By using this software in any fashion, you are agreeing to be bound by the
//    terms of this license.
//   
//    You must not remove this notice, or any other, from this software.
//   
//
// ==--==
using System.IO; 
using System;
public class Co3766LastIndexOf_ooii
{
 public static readonly String s_strActiveBugNums = "";
 public static readonly String s_strDtTmVer       = "";
 public static readonly String s_strClassMethod   = "Array.LastIndexOf(Object[], Object, int StartIndex, int Length)";
 public static readonly String s_strTFName        = "Co3766LastIndexOf_ooii";
 public static readonly String s_strTFAbbrev      = "Co3766";
 public static readonly String s_strTFPath        = "";
 public virtual bool runTest()
   {
   int iCountErrors = 0;
   int iCountTestcases = 0;
   String strLoc="123_er";
   String strInfo = null;
   Console.Out.Write( s_strClassMethod );
   Console.Out.Write( ": " );
   Console.Out.Write( s_strTFPath + s_strTFName );
   Console.Out.Write( ": " );
   Console.Out.Write( s_strDtTmVer );
   Console.Out.WriteLine( " runTest started..." );
   Object o1;
   Char chValue;
   Int16 i16Value;
   int iReturnValue;
   Object[] oArrValues;
   Object[,] o2ArrValues;
   int iStartIndex;
   try
     {
     LABEL_860_GENERAL:
     do
       {
       oArrValues = new Object[cArr.Length];
       for(int i=0; i < cArr.Length; i++)
	 {
	 oArrValues[i]=cArr[i];
	 }
       ++iCountTestcases;
       for(int i=cArr.Length-1; i >= 0 ; i--)
	 {
	 strLoc = "784df_" + i;
	 o1 = cArr[i];
	 iReturnValue = Array.LastIndexOf(oArrValues, o1, i, i+1);
	 if ( iReturnValue != i )
	   {
	   ++iCountErrors;
	   Console.WriteLine( s_strTFAbbrev + "Err_320ye_" + i + ", iReturnValue=="+ iReturnValue );
	   }
	 }
       oArrValues = new Object[i16Arr.Length];
       for(int i=0; i < i16Arr.Length; i++)
	 {
	 oArrValues[i]=i16Arr[i];
	 }
       strLoc = "L_900";
       ++iCountTestcases;
       for(int i=0; i < oArrValues.Length; i++)
	 {
	 o1 = i16Arr[i];
	 iReturnValue = Array.LastIndexOf(oArrValues, o1, i, i+1);
	 if ( iReturnValue != i )
	   {
	   ++iCountErrors;
	   Console.WriteLine( s_strTFAbbrev + "Err_947ps_" + i + ", iReturnValue=="+ iReturnValue );
	   }
	 }
       strLoc = "L_901";
       try
	 {
	 o1 = 16;
	 ++iCountTestcases;
	 iReturnValue = Array.LastIndexOf(null, o1, 0, 1);
	 ++iCountErrors;
	 Console.WriteLine( s_strTFAbbrev + "Err_835xr!  iReturnValue=="+ iReturnValue );
	 }
       catch (ArgumentException ex)
	 {
	 }
       catch (Exception ex)
	 {
	 ++iCountErrors;
	 Console.Error.WriteLine(" Error E_972qr!  , Wrong Exception thrown == " + ex.ToString());
	 Console.WriteLine(ex.StackTrace);
	 }
       strLoc = "L_902";
       oArrValues = new Object[i16Arr.Length];
       for(int i=0; i < i16Arr.Length; i++)
	 {
	 oArrValues[i]=i16Arr[i];
	 }
       strLoc = "L_903";
       try
	 {
	 o1 = 16;
	 ++iCountTestcases;
	 iReturnValue = Array.LastIndexOf(oArrValues, o1, -1, 0);
	 ++iCountErrors;
	 Console.WriteLine( s_strTFAbbrev + "Err_735ds!  iReturnValue=="+ iReturnValue );
	 }
       catch (ArgumentException ex)
	 {
	 }
       catch (Exception ex)
	 {
	 ++iCountErrors;
	 Console.Error.WriteLine(" Error E_975em!  , Wrong Exception thrown == " + ex.ToString());
	 Console.WriteLine(ex.StackTrace);
	 }
       strLoc = "L_904";
       try
	 {
	 o1 = 16;
	 ++iCountTestcases;
	 iReturnValue = Array.LastIndexOf(oArrValues, o1, 0, -1);
	 ++iCountErrors;
	 Console.WriteLine( s_strTFAbbrev + "Err_286cxs!  iReturnValue=="+ iReturnValue );
	 }
       catch (ArgumentException ex)
	 {
	 }
       catch (Exception ex)
	 {
	 ++iCountErrors;
	 Console.Error.WriteLine(" Error E_5y3dg!  , Wrong Exception thrown == " + ex.ToString());
	 Console.WriteLine(ex.StackTrace);
	 }
       strLoc = "L_905";
       oArrValues = new Object[i16Arr.Length];
       for(int i=0; i < i16Arr.Length; i++)
	 {
	 oArrValues[i]=i16Arr[i];
	 }
       strLoc = "L_906";
       iReturnValue = Array.LastIndexOf(oArrValues, null, 0, 0);
       ++iCountTestcases;
       if ( iReturnValue != -1 )	
	 {
	 ++iCountErrors;
	 Console.WriteLine( s_strTFAbbrev + "Err_784dr! iReturnValue=="+ iReturnValue );
	 }
       strLoc = "L_907";
       o1 = 16;
       try {
       iReturnValue = Array.LastIndexOf(oArrValues, o1, 2, 5);
       ++iCountTestcases;
       if ( iReturnValue != -1 )	
	 {
	 ++iCountErrors;
	 Console.WriteLine( s_strTFAbbrev + "Err_468df! iReturnValue=="+ iReturnValue );
	 }
       }
       catch (ArgumentOutOfRangeException aorexc) {
       }
       } while ( false );
     }
   catch (Exception exc_general)
     {
     ++iCountErrors;
     Console.WriteLine( s_strTFAbbrev + "Error Err_8888yyy!  strLoc=="+ strLoc +" ,exc_general=="+ exc_general );
     }
   if ( iCountErrors == 0 ) {   return true; }
   else {  return false;}
   }
 internal static readonly Char[]			cArr	  = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a', 'j', 'i', 'h'};
 internal static readonly Int16[]		i16Arr	= {19, 238, 317, 6, 565, 0, -52, 60, -563, 753, 19, 238, 317};
 internal static readonly Object[]	oArr			= {true, 'k', SByte.MinValue, Byte.MinValue, (short)2, 634, (long)436, (float)1.1, 1.23, "Hello World"};
 internal static readonly Char[,]		c2Arr		  = {{'a', 'b', 'c', 'd', 'e'},
								     {'k', 'l', 'm', 'n', 'o'}};
 public static void Main( String[] args )
   {
   bool bResult = false;	
   Co3766LastIndexOf_ooii oCbTest = new Co3766LastIndexOf_ooii();
   try
     {
     bResult = oCbTest.runTest();
     }
   catch ( Exception exc_main )
     {
     bResult = false;
     Console.WriteLine( s_strTFAbbrev + "FAiL!  Error Err_9999zzz!  Uncaught Exception caught in main(), exc_main=="+ exc_main );
     }
   if ( ! bResult )
     {
     Console.WriteLine( s_strTFAbbrev + s_strTFPath );
     Console.Error.WriteLine( " " );
     Console.Error.WriteLine( "FAiL!  "+ s_strTFAbbrev );  
     Console.Error.WriteLine( " " );
     }
   if ( bResult == true ) Environment.ExitCode = 0; else Environment.ExitCode = 11; 
   }
}
