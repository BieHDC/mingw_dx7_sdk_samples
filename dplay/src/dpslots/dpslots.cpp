//-----------------------------------------------------------------------------
// File: DPSlots.cpp
//
// Desc: Main DPSlots file
//
// Copyright (C) 1996-1999 Microsoft Corporation.  All Rights Reserved.
//-----------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include "dpslots.h"
#include "resource.h"

#if defined(UNICODE) || defined(_UNICODE)
#error This app does not support UNICODE
#endif

// globals
HANDLE          ghReceiveThread = NULL;         // handle of receive thread
DWORD           gidReceiveThread = 0;           // id of receive thread
HANDLE          ghKillReceiveEvent = NULL;      // event used to kill receive thread
HINSTANCE       ghInstance = NULL;              // application instance
CHAR            g_strDatabaseName[MAXSTRLEN];       // database name

//-----------------------------------------------------------------------------
// Function prototypes
//-----------------------------------------------------------------------------
HRESULT         SetupConnection( HINSTANCE hInstance, DPLAYINFO* pDPInfo );
HRESULT         ShutdownConnection( DPLAYINFO* pDPInfo );
DWORD WINAPI    ReceiveThread( VOID* pThreadParameter);
HRESULT         ReceiveMessage( DPLAYINFO* pDPInfo);
VOID            HandleSystemMessage( DPLAYINFO* pDPInfo, DPMSG_GENERIC* pMsg,
                                     DWORD dwMsgSize, DPID idFrom, DPID idTo );
VOID            HandleApplicationMessage( DPLAYINFO* pDPInfo, DPMSG_GENERIC* pMsg,
                                          DWORD dwMsgSize, DPID idFrom, DPID idTo );
CHAR*           GetDirectPlayErrStr( HRESULT hr );




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc:
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int )
{
    DPLAYINFO DPInfo;
    int       iResult = 0;
    HRESULT   hr;

    ghInstance = hInstance;
    srand( GetTickCount() );
    lstrcpy( g_strDatabaseName, DEFAULTDATABASE );

    // Initialize COM library
    hr = CoInitialize( NULL );
    if( FAILED(hr) )
        goto FAILURE;

    // Setup the connection
    hr = SetupConnection( hInstance, &DPInfo );
    if( FAILED(hr) )
        goto FAILURE;

    if( DPInfo.bIsHost )
    {
        // Show the server window
        iResult = DialogBoxParam( hInstance, MAKEINTRESOURCE(IDD_SERVERDIALOG),
                                  NULL, (DLGPROC)ServerWndProc, (LPARAM)&DPInfo );
    }
    else
    {
        // Show the client window
        iResult = DialogBoxParam( hInstance, MAKEINTRESOURCE(IDD_CLIENTDIALOG),
                                  NULL, (DLGPROC)ClientWndProc, (LPARAM)&DPInfo );
    }

FAILURE:
    // Shut down the connection
    hr = ShutdownConnection( &DPInfo );

    // Uninitialize the COM library
    CoUninitialize();

    return iResult;
}




//-----------------------------------------------------------------------------
// Name: SetupConnection()
// Desc:
//-----------------------------------------------------------------------------
HRESULT SetupConnection( HINSTANCE hInstance, DPLAYINFO* pDPInfo )
{
    HRESULT     hr;

    ZeroMemory(pDPInfo, sizeof(DPLAYINFO));

    // create event used by DirectPlay to signal a message has arrived
    pDPInfo->hPlayerEvent = CreateEvent(NULL,       // no security
                                         FALSE,     // auto reset
                                         FALSE,     // initial event reset
                                         NULL);     // no name
    if (pDPInfo->hPlayerEvent == NULL)
    {
        hr = DPERR_NOMEMORY;
        goto FAILURE;
    }

    // create event used to signal that the receive thread should exit
    ghKillReceiveEvent = CreateEvent(NULL,      // no security
                                     FALSE,     // auto reset
                                     FALSE,     // initial event reset
                                     NULL);     // no name
    if (ghKillReceiveEvent == NULL)
    {
        hr = DPERR_NOMEMORY;
        goto FAILURE;
    }

    // create thread to receive player messages
    ghReceiveThread = CreateThread(NULL,            // default security
                                   0,               // default stack size
                                   ReceiveThread,   // pointer to thread routine
                                   pDPInfo,     // argument for thread
                                   0,               // start it right away
                                   &gidReceiveThread);
    if (ghReceiveThread == NULL)
    {
        hr = DPERR_NOMEMORY;
        goto FAILURE;
    }

    // try to connect using the lobby
    hr = ConnectUsingLobby(pDPInfo);
    if FAILED(hr)
    {
        // if the error returned is DPERR_NOTLOBBIED, that means we
        // were not launched by a lobby and we should ask the user for
        // connection settings. If any other error is returned it means
        // we were launched by a lobby but there was an error making the
        // connection.

        if (hr != DPERR_NOTLOBBIED)
            ErrorBox((char*)"Could not connect using lobby because of error %s", hr);

        // if there is no lobby connection, ask the user for settings
        hr = ConnectUsingDialog(hInstance, pDPInfo);
        if FAILED(hr)
            goto FAILURE;
    }

    return (DP_OK); 

FAILURE:
    ShutdownConnection(pDPInfo);

    return (hr);
}




//-----------------------------------------------------------------------------
// Name: ShutdownConnection()
// Desc:
//-----------------------------------------------------------------------------
HRESULT ShutdownConnection( DPLAYINFO* pDPInfo )
{
    if( ghReceiveThread )
    {
        // Wake up receive thread and wait for it to quit
        SetEvent( ghKillReceiveEvent );
        WaitForSingleObject( ghReceiveThread, INFINITE );

        CloseHandle( ghReceiveThread );
        ghReceiveThread = NULL;
    }

    if( ghKillReceiveEvent )
    {
        CloseHandle( ghKillReceiveEvent );
        ghKillReceiveEvent = NULL;
    }

    if( pDPInfo->pDPlay )
    {
        if( pDPInfo->dpidPlayer )
        {
            pDPInfo->pDPlay->DestroyPlayer( pDPInfo->dpidPlayer );
            pDPInfo->dpidPlayer = 0;
        }
        pDPInfo->pDPlay->Close();
        pDPInfo->pDPlay->Release();
        pDPInfo->pDPlay = NULL;
    }

    if( pDPInfo->hPlayerEvent )
    {
        CloseHandle( pDPInfo->hPlayerEvent );
        pDPInfo->hPlayerEvent = NULL;
    }

    return DP_OK;
}




//-----------------------------------------------------------------------------
// Name: ReceiveThread()
// Desc:
//-----------------------------------------------------------------------------
DWORD WINAPI ReceiveThread( VOID* lpThreadParameter )
{
    DPLAYINFO* pDPInfo = (DPLAYINFO*)lpThreadParameter;
    HANDLE     eventHandles[2];

    eventHandles[0] = pDPInfo->hPlayerEvent;
    eventHandles[1] = ghKillReceiveEvent;

    // loop waiting for player events. If the kill event is signaled
    // the thread will exit
    while (WaitForMultipleObjects(2, eventHandles, FALSE, INFINITE) == WAIT_OBJECT_0)
    {
        // receive any messages in the queue
        ReceiveMessage(pDPInfo);
    }

    ExitThread(0);

    return (0);
}




//-----------------------------------------------------------------------------
// Name: ReceiveMessage()
// Desc:
//-----------------------------------------------------------------------------
HRESULT ReceiveMessage( DPLAYINFO* pDPInfo )
{
    DPID    idFrom, idTo;
    VOID*   pMsgBuffer      = NULL;
    DWORD   dwMsgBufferSize = 0L;
    HRESULT hr;

    // Loop to read all messages in queue
    do
    {
        // Loop until a single message is successfully read
        do
        {
            // Read messages from any player, including system player
            idFrom = 0;
            idTo   = 0;

            hr = pDPInfo->pDPlay->Receive( &idFrom, &idTo, DPRECEIVE_ALL,
                                           pMsgBuffer, &dwMsgBufferSize );

            // Not enough room, so resize buffer
            if( hr == DPERR_BUFFERTOOSMALL )
            {
                if( pMsgBuffer )
                    GlobalFreePtr( pMsgBuffer );
                pMsgBuffer = GlobalAllocPtr( GHND, dwMsgBufferSize );
                if( pMsgBuffer == NULL )
                    hr = DPERR_OUTOFMEMORY;
            }
        } while( hr == DPERR_BUFFERTOOSMALL );

        if( (SUCCEEDED(hr) ) && ( dwMsgBufferSize >= sizeof(DPMSG_GENERIC) ) )
        {
            // Check for system message
            if( idFrom == DPID_SYSMSG )
            {
                HandleSystemMessage( pDPInfo, (DPMSG_GENERIC*)pMsgBuffer,
                                     dwMsgBufferSize, idFrom, idTo );
            }
            else
            {
                HandleApplicationMessage( pDPInfo, (DPMSG_GENERIC*)pMsgBuffer,
                                          dwMsgBufferSize, idFrom, idTo );
            }
        }
    } while( SUCCEEDED(hr) );

    // Free any memory we created
    if( pMsgBuffer )
        GlobalFreePtr( pMsgBuffer );

    return DP_OK;
}




//-----------------------------------------------------------------------------
// Name: HandleSystemMessage()
// Desc:
//-----------------------------------------------------------------------------
VOID HandleSystemMessage( DPLAYINFO* pDPInfo, DPMSG_GENERIC* pMsg,
                          DWORD dwMsgSize, DPID idFrom, DPID idTo )
{
    if( pDPInfo->bIsHost )
    {
        ServerSystemMessage( pDPInfo, pMsg, dwMsgSize, idFrom, idTo );
    }
    else
    {
        ClientSystemMessage( pDPInfo, pMsg, dwMsgSize, idFrom, idTo );
    }
}




//-----------------------------------------------------------------------------
// Name: HandleApplicationMessage()
// Desc:
//-----------------------------------------------------------------------------
VOID HandleApplicationMessage( DPLAYINFO* pDPInfo, DPMSG_GENERIC* pMsg,
                               DWORD dwMsgSize, DPID idFrom, DPID idTo )
{
    // When using a secure session we should not get any messages here
    // because encrypted messages come through as system messages. Therefore,
    // it is a security hole to process messages here.

    if( pDPInfo->bIsSecure )
        return;

    if( pDPInfo->bIsHost )
    {
        ServerApplicationMessage( pDPInfo, pMsg, dwMsgSize, idFrom, idTo );
    }
    else
    {
        ClientApplicationMessage( pDPInfo, pMsg, dwMsgSize, idFrom, idTo );
    }
}




//-----------------------------------------------------------------------------
// Name: CheckDlgItem()
// Desc:
//-----------------------------------------------------------------------------
VOID CheckDlgItem( HWND hDlg, int nIDDlgItem, BOOL bCheck )
{
    SendDlgItemMessage( hDlg, nIDDlgItem, BM_SETCHECK,
                        (WPARAM)( bCheck ? BST_CHECKED : BST_UNCHECKED ), 0 );
}




//-----------------------------------------------------------------------------
// Name: DlgItemIsChecked()
// Desc:
//-----------------------------------------------------------------------------
BOOL DlgItemIsChecked( HWND hDlg, int nIDDlgItem )
{
    return( ( SendDlgItemMessage( hDlg, nIDDlgItem, BM_GETCHECK, 0, 0 )
              == BST_CHECKED) ? TRUE : FALSE );
}




//-----------------------------------------------------------------------------
// Name: EnableDlgButton()
// Desc:
//-----------------------------------------------------------------------------
VOID EnableDlgButton( HWND hDlg, int nIDDlgItem, BOOL bEnable )
{
    EnableWindow( GetDlgItem( hDlg, nIDDlgItem ), bEnable );
}




//-----------------------------------------------------------------------------
// Name: ErrorBox()
// Desc:
//-----------------------------------------------------------------------------
VOID ErrorBox( LPSTR strError, HRESULT hr )
{
    CHAR str[200];

    wsprintf( str, strError, GetDirectPlayErrStr(hr) );

    MessageBox( NULL, str, "Error", MB_OK );
}




//-----------------------------------------------------------------------------
// Name: GetDirectPlayErrStr()
// Desc:
//-----------------------------------------------------------------------------
CHAR* GetDirectPlayErrStr( HRESULT hr )
{
    switch( hr )
    {
        case DP_OK: return ((char*)"DP_OK");
        case DPERR_ALREADYINITIALIZED: return ((char*)"DPERR_ALREADYINITIALIZED");
        case DPERR_ACCESSDENIED: return ((char*)"DPERR_ACCESSDENIED");
        case DPERR_ACTIVEPLAYERS: return ((char*)"DPERR_ACTIVEPLAYERS");
        case DPERR_BUFFERTOOSMALL: return ((char*)"DPERR_BUFFERTOOSMALL");
        case DPERR_CANTADDPLAYER: return ((char*)"DPERR_CANTADDPLAYER");
        case DPERR_CANTCREATEGROUP: return ((char*)"DPERR_CANTCREATEGROUP");
        case DPERR_CANTCREATEPLAYER: return ((char*)"DPERR_CANTCREATEPLAYER");
        case DPERR_CANTCREATESESSION: return ((char*)"DPERR_CANTCREATESESSION");
        case DPERR_CAPSNOTAVAILABLEYET: return ((char*)"DPERR_CAPSNOTAVAILABLEYET");
        case DPERR_EXCEPTION: return ((char*)"DPERR_EXCEPTION");
        case DPERR_GENERIC: return ((char*)"DPERR_GENERIC");
        case DPERR_INVALIDFLAGS: return ((char*)"DPERR_INVALIDFLAGS");
        case DPERR_INVALIDOBJECT: return ((char*)"DPERR_INVALIDOBJECT");
    //  case DPERR_INVALIDPARAM: return ((char*)"DPERR_INVALIDPARAM");  dup value
        case DPERR_INVALIDPARAMS: return ((char*)"DPERR_INVALIDPARAMS");
        case DPERR_INVALIDPLAYER: return ((char*)"DPERR_INVALIDPLAYER");
        case DPERR_INVALIDGROUP: return ((char*)"DPERR_INVALIDGROUP");
        case DPERR_NOCAPS: return ((char*)"DPERR_NOCAPS");
        case DPERR_NOCONNECTION: return ((char*)"DPERR_NOCONNECTION");
    //  case DPERR_NOMEMORY: return ((char*)"DPERR_NOMEMORY");     dup value
        case DPERR_OUTOFMEMORY: return ((char*)"DPERR_OUTOFMEMORY");
        case DPERR_NOMESSAGES: return ((char*)"DPERR_NOMESSAGES");
        case DPERR_NONAMESERVERFOUND: return ((char*)"DPERR_NONAMESERVERFOUND");
        case DPERR_NOPLAYERS: return ((char*)"DPERR_NOPLAYERS");
        case DPERR_NOSESSIONS: return ((char*)"DPERR_NOSESSIONS");
        case DPERR_PENDING: return ((char*)"DPERR_PENDING");
        case DPERR_SENDTOOBIG: return ((char*)"DPERR_SENDTOOBIG");
        case DPERR_TIMEOUT: return ((char*)"DPERR_TIMEOUT");
        case DPERR_UNAVAILABLE: return ((char*)"DPERR_UNAVAILABLE");
        case DPERR_UNSUPPORTED: return ((char*)"DPERR_UNSUPPORTED");
        case DPERR_BUSY: return ((char*)"DPERR_BUSY");
        case DPERR_USERCANCEL: return ((char*)"DPERR_USERCANCEL");
        case DPERR_NOINTERFACE: return ((char*)"DPERR_NOINTERFACE");
        case DPERR_CANNOTCREATESERVER: return ((char*)"DPERR_CANNOTCREATESERVER");
        case DPERR_PLAYERLOST: return ((char*)"DPERR_PLAYERLOST");
        case DPERR_SESSIONLOST: return ((char*)"DPERR_SESSIONLOST");
        case DPERR_UNINITIALIZED: return ((char*)"DPERR_UNINITIALIZED");
        case DPERR_NONEWPLAYERS: return ((char*)"DPERR_NONEWPLAYERS");
        case DPERR_INVALIDPASSWORD: return ((char*)"DPERR_INVALIDPASSWORD");
        case DPERR_CONNECTING: return ((char*)"DPERR_CONNECTING");
        case DPERR_CONNECTIONLOST: return ((char*)"DPERR_CONNECTIONLOST");
        case DPERR_UNKNOWNMESSAGE: return ((char*)"DPERR_UNKNOWNMESSAGE");
        case DPERR_CANCELFAILED: return ((char*)"DPERR_CANCELFAILED");
        case DPERR_INVALIDPRIORITY: return ((char*)"DPERR_INVALIDPRIORITY");
        case DPERR_NOTHANDLED: return ((char*)"DPERR_NOTHANDLED");
        case DPERR_CANCELLED: return ((char*)"DPERR_CANCELLED");
        case DPERR_ABORTED: return ((char*)"DPERR_ABORTED");
        case DPERR_BUFFERTOOLARGE: return ((char*)"DPERR_BUFFERTOOLARGE");
        case DPERR_CANTCREATEPROCESS: return ((char*)"DPERR_CANTCREATEPROCESS");
        case DPERR_APPNOTSTARTED: return ((char*)"DPERR_APPNOTSTARTED");
        case DPERR_INVALIDINTERFACE: return ((char*)"DPERR_INVALIDINTERFACE");
        case DPERR_NOSERVICEPROVIDER: return ((char*)"DPERR_NOSERVICEPROVIDER");
        case DPERR_UNKNOWNAPPLICATION: return ((char*)"DPERR_UNKNOWNAPPLICATION");
        case DPERR_NOTLOBBIED: return ((char*)"DPERR_NOTLOBBIED");
        case DPERR_SERVICEPROVIDERLOADED: return ((char*)"DPERR_SERVICEPROVIDERLOADED");
        case DPERR_ALREADYREGISTERED: return ((char*)"DPERR_ALREADYREGISTERED");
        case DPERR_NOTREGISTERED: return ((char*)"DPERR_NOTREGISTERED");
        case DPERR_AUTHENTICATIONFAILED: return ((char*)"DPERR_AUTHENTICATIONFAILED");
        case DPERR_CANTLOADSSPI: return ((char*)"DPERR_CANTLOADSSPI");
        case DPERR_ENCRYPTIONFAILED: return ((char*)"DPERR_ENCRYPTIONFAILED");
        case DPERR_SIGNFAILED: return ((char*)"DPERR_SIGNFAILED");
        case DPERR_CANTLOADSECURITYPACKAGE: return ((char*)"DPERR_CANTLOADSECURITYPACKAGE");
        case DPERR_ENCRYPTIONNOTSUPPORTED: return ((char*)"DPERR_ENCRYPTIONNOTSUPPORTED");
        case DPERR_CANTLOADCAPI: return ((char*)"DPERR_CANTLOADCAPI");
        case DPERR_NOTLOGGEDIN: return ((char*)"DPERR_NOTLOGGEDIN");
        case DPERR_LOGONDENIED: return ((char*)"DPERR_LOGONDENIED");
    }

    // For errors not in the list, return HRESULT string
    static CHAR strTemp[12];
    wsprintf( strTemp, "0x%08X", hr );
    return strTemp;
}



