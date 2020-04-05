#include <ole2.h>

/*
 * DPACCOUNTDESC
 * Used to describe a user membership account
 */
typedef struct 
{
    DWORD dwSize;                   // Size of structure
    DWORD dwFlags;                  // Not used. Must be zero.
    union
    {                               // Account identifier
        LPWSTR  lpszAccountID;      // Unicode
        LPSTR   lpszAccountIDA;     // ANSI
    };
} DPACCOUNTDESC, FAR *LPDPACCOUNTDESC;

typedef const DPACCOUNTDESC FAR *LPCDPACCOUNTDESC;
