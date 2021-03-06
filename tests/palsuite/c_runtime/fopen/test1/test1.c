/*=====================================================================
**
** Source:  test1.c
**
** Purpose: Tests the PAL implementation of the fopen function. 
**          This test simply attempts to open a number of files
**          with different modes.  It checks to ensure a valid
**          file pointer is returned.  It doesn't do any checking
**          to ensure the mode is really what it claims.  And checks
**          for a NULL pointer when attempts to open a directory.
**  
** 
**  Copyright (c) 2006 Microsoft Corporation.  All rights reserved.
** 
**  The use and distribution terms for this software are contained in the file
**  named license.txt, which can be found in the root of this distribution.
**  By using this software in any fashion, you are agreeing to be bound by the
**  terms of this license.
** 
**  You must not remove this notice, or any other, from this software.
** 
**
**===================================================================*/
                                 
#include <palsuite.h>

struct testCase
{
    int CorrectResult;
    char mode[20];
};

int __cdecl main(int argc, char **argv)
{
  
    FILE *fp;
    char name[128];
    int i;

    struct testCase testCases[] = 
        {
            {0,  "r"},  {1, "w"},   {1,  "a"},
            {0,  "r+"}, {1,  "w+"}, {1,  "a+"},
            {1,  "wt"}, {1,  "wb"}, {1,  "wS"},
            {1,  "w+c"},{1,  "w+n"}, {1, "wR"},
            {1,  "wT"}, {1,  "wD"},  {0, "tw"} 
        };

    if (PAL_Initialize(argc, argv))
    {
        return FAIL;
    }

  
  
    for(i = 0; i < sizeof(testCases) / sizeof(struct testCase); i++)
    {
        strcpy(name,"testfiles");
        strcat(name,testCases[i].mode);
      
        fp = fopen(name,testCases[i].mode);
      
        if ((fp == 0 && testCases[i].CorrectResult != 0)  ||
            (testCases[i].CorrectResult == 0 && fp != 0) )
        {
            Fail("ERROR: fopen returned incorrectly "
                   "opening a file in %s mode.  Perhaps it opened a "
                   "read only file which didn't exist and returned a correct "
                   "pointer?",testCases[i].mode);
        }    

        memset(name, '\0', 128);
        
    }      

    /* When attempt to open a directory fopen should returned NULL */
    if ( fopen(".", "r") != NULL)
    {
        Fail("ERROR: fopen returned non-NULL when trying to open a directory"
             " the returned value was %d\n", fp);
    }
  
    PAL_Terminate();
    return PASS;
}
   

