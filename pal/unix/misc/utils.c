/*++


 Copyright (c) 2006 Microsoft Corporation.  All rights reserved.

 The use and distribution terms for this software are contained in the file
 named license.txt, which can be found in the root of this distribution.
 By using this software in any fashion, you are agreeing to be bound by the
 terms of this license.

 You must not remove this notice, or any other, from this software.


Module Name:

    misc/utils.c

Abstract:

    Miscellaneous helper functions for the PAL, which don't fit anywhere else

--*/

#include "pal/palinternal.h"
#if HAVE_VM_ALLOCATE
#include <mach/message.h>
#endif //HAVE_VM_ALLOCATE

#include "pal/utils.h"
#include "pal/dbgmsg.h"

#include <errno.h>
#include <string.h>


SET_DEFAULT_DEBUG_CHANNEL(MISC);

/*++
Function:
  UTIL_inverse_wcspbrk

  Opposite of wcspbrk : searches a string for the first character NOT in the 
  given set

Parameters :
    LPWSTR lpwstr :   string to search
    LPCWSTR charset : list of characters to search for
                                      
Return value :
    pointer to first character of lpwstr that isn't in the set
    NULL if all characters are in the set                                                                 
--*/
LPWSTR UTIL_inverse_wcspbrk(LPWSTR lpwstr, LPCWSTR charset)
{
    while(*lpwstr)
    {
        if(NULL == PAL_wcschr(charset,*lpwstr))
        {
            return lpwstr;
        }
        lpwstr++;
    }                     
    return NULL;
}


/*++
Function : 
    UTIL_IsReadOnlyBitsSet
    
    Takes a struct stat *
    Returns true if the file is read only,
--*/
BOOL UTIL_IsReadOnlyBitsSet( struct stat * stat_data )
{
    BOOL bRetVal = FALSE;

    /* Check for read permissions. */
    if ( stat_data->st_uid == geteuid() )
    {
        /* The process owner is the file owner as well. */
        if ( ( stat_data->st_mode & S_IRUSR ) && !( stat_data->st_mode & S_IWUSR ) )
        {
            bRetVal = TRUE;
        }
    }
    else if ( stat_data->st_gid == getegid() )
    {
        /* The process's owner is in the same group as the file's owner. */
        if ( ( stat_data->st_mode & S_IRGRP ) && !( stat_data->st_mode & S_IWGRP ) )
        {
            bRetVal = TRUE;
        }
    }
    else
    {
        /* Check the other bits to see who can access the file. */
        if ( ( stat_data->st_mode & S_IROTH ) && !( stat_data->st_mode & S_IWOTH ) )
        {
            bRetVal = TRUE;
        }
    }

    return bRetVal;
}

/*++
Function : 
    UTIL_IsExecuteBitsSet
    
    Takes a struct stat *
    Returns true if the file is executable,
--*/
BOOL UTIL_IsExecuteBitsSet( struct stat * stat_data )
{
    BOOL bRetVal = FALSE;

    if ( (stat_data->st_mode & S_IFMT) == S_IFDIR )
    {
        return FALSE;
    }
    
    /* Check for read permissions. */
    if ( stat_data->st_uid == geteuid() )
    {
        /* The process owner is the file owner as well. */
        if ( ( stat_data->st_mode & S_IXUSR ) )
        {
            bRetVal = TRUE;
        }
    }
    else if ( stat_data->st_gid == getegid() )
    {
        /* The process's owner is in the same group as the file's owner. */
        if ( ( stat_data->st_mode & S_IXGRP ) )
        {
            bRetVal = TRUE;
        }
    }
    else
    {
        /* Check the other bits to see who can access the file. */
        if ( ( stat_data->st_mode & S_IXOTH ) )
        {
            bRetVal = TRUE;
        }
    }

    return bRetVal;
}

/*++
Function : 
    UTIL_WCToMB_Alloc
    
    Converts a wide string to a multibyte string, allocating the required buffer
    
Parameters :
    LPCWSTR lpWideCharStr : string to convert
    int cchWideChar : number of wide characters to convert
                      (-1 to convert a complete null-termnated string)
    
Return Value :
    newly allocated buffer containing the converted string. Conversion is 
    performed using CP_ACP. Buffer is allocated with malloc(), release it 
    with free().
    In case if failure, LastError will be set.
--*/
LPSTR UTIL_WCToMB_Alloc(LPCWSTR lpWideCharStr, int cchWideChar)
{
    int length;
    LPSTR lpMultiByteStr;

    /* get required buffer length */
    length = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, cchWideChar, 
                                 NULL, 0, NULL, NULL);
    if(0 == length)
    {
        ERROR("WCToMB error; GetLastError returns %#x", GetLastError());
        return NULL;
    }

    /* allocate required buffer */
    lpMultiByteStr = malloc(length);
    if(NULL == lpMultiByteStr)
    {
        ERROR("malloc() failed! errno is %d (%s)\n", errno,strerror(errno));
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return NULL;
    }

    /* convert into allocated buffer */
    length = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, cchWideChar, 
                                 lpMultiByteStr, length, NULL, NULL);
    if(0 == length)
    {
        ASSERT("WCToMB error; GetLastError returns %#x\n", GetLastError());
        free(lpMultiByteStr);
        return NULL;
    }
    return lpMultiByteStr;
}

/*++
Function : 
    UTIL_MBToWC_Alloc
    
    Converts a multibyte string to a wide string, allocating the required buffer
    
Parameters :
    LPCSTR lpMultiByteStr : string to convert
    int cbMultiByte : number of bytes to convert
                      (-1 to convert a complete null-termnated string)
    
Return Value :
    newly allocated buffer containing the converted string. Conversion is 
    performed using CP_ACP. Buffer is allocated with malloc(), release it 
    with free().
    In case if failure, LastError will be set.
--*/
LPWSTR UTIL_MBToWC_Alloc(LPCSTR lpMultiByteStr, int cbMultiByte)
{
    int length;
    LPWSTR lpWideCharStr;

    /* get required buffer length */
    length = MultiByteToWideChar(CP_ACP, 0, lpMultiByteStr, cbMultiByte,
                                      NULL, 0);
    if(0 == length)
    {
        ERROR("MBToWC error; GetLastError returns %#x", GetLastError());
        return NULL;
    }

    /* allocate required buffer */
    lpWideCharStr = malloc(length*sizeof(WCHAR));
    if(NULL == lpWideCharStr)
    {
        ERROR("malloc() failed! errno is %d (%s)\n", errno,strerror(errno));
        return NULL;
    }

    /* convert into allocated buffer */
    length = MultiByteToWideChar(CP_ACP, 0, lpMultiByteStr, cbMultiByte, 
                                      lpWideCharStr, length);
    if(0 == length)
    {
        ASSERT("MCToMB error; GetLastError returns %#x\n", GetLastError());
        free(lpWideCharStr);
        return NULL;
    }
    return lpWideCharStr;
}

#if HAVE_VM_ALLOCATE
/*++
Function:
  UTIL_SetLastErrorFromMach

    Maps a Mach kern_return_t to a Win32 LastError code.
--*/
void
UTIL_SetLastErrorFromMach(
                          kern_return_t MachReturn)
{
    switch (MachReturn)
    {
    case KERN_SUCCESS:
        return;

    case KERN_NO_ACCESS:
    case KERN_INVALID_CAPABILITY:
        SetLastError(ERROR_ACCESS_DENIED);
        break;

    case KERN_TERMINATED:
        SetLastError(ERROR_INVALID_HANDLE);
        break;

    case KERN_INVALID_ADDRESS:
        SetLastError(ERROR_INVALID_ADDRESS);
        break;

    case KERN_NO_SPACE:
        SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        break;

    default:
        ASSERT("Unknown kern_return_t value %d - reporting ERROR_INTERNAL_ERROR\n", MachReturn);
        SetLastError(ERROR_INTERNAL_ERROR);
        break;
    }
}
#endif //HAVE_VM_ALLOCATE

