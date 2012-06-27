/**
 *  Copyright (c) 2009 - 2012 Hewlett-Packard Development Company, L.P.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#include <string>

#include <PIpcMessageMacros.h>

#include "SysMgrEventTraits.h"
#include "SysMgrKeyEventTraits.h"
#include "SysMgrMouseEventTraits.h"
#include "SysMgrTouchEventTraits.h"
#include "SysMgrDefs.h"
#include <sys/types.h>

IPC_BEGIN_MESSAGES(View)

// CONTROL MESSAGES

    // launch a web application (only used for launcher and status bar on boot)
    // params: url, window type, application description (json) , process id, launch params, app id of app launching, process id of app launching
    IPC_MESSAGE_CONTROL7(View_Mgr_LaunchUrl, std::string, int, std::string, std::string, std::string, std::string, std::string)

    // launch a web application ("normal" app launching)
    // params: application description (json), launch params, app id of app launching, process if of app launching
    IPC_MESSAGE_CONTROL4(View_ProcMgr_Launch, std::string, std::string, std::string, std::string)

    // launch a web application ("modal" app launching)
    // params: application description (json), launch params, app id of app launching, process id of app launching, is the app being launched headless, is the parent app PDK
    IPC_MESSAGE_CONTROL6(View_ProcMgr_LaunchChild, std::string, std::string, std::string, std::string, bool, bool)

    // launch a web application (redundant as this does a "normal" launch with some pre-filled fields)
    // params: application description (json)
    IPC_MESSAGE_CONTROL1(View_ProcMgr_LaunchBootTimeApp, std::string)

    // close a window by its process id
    // params: process id of the window to close
    IPC_MESSAGE_CONTROL1(View_Mgr_CloseByProcessId, std::string)

    // close all windows (headless included) that belong to an application
    // params: app id of the application to close
    IPC_MESSAGE_CONTROL1(View_Mgr_KillApp, std::string)

    // synchronously close all windows belonging to an application
    // params: app id of the application to close, did the call succeed (out)
    IPC_SYNC_MESSAGE_CONTROL1_1(View_Mgr_SyncKillApp, std::string, bool)

    // sets the orientation of all web apps
    // params: orientation
    IPC_MESSAGE_CONTROL1(View_Mgr_SetOrientation, int)

    // initiate the inspector on a web page
    // params: process id of the window to inspect
    IPC_MESSAGE_CONTROL1(View_Mgr_InspectByProcessId, std::string)

    // clear webkit's DOM cache for all web pages
    IPC_MESSAGE_CONTROL0(View_Mgr_ClearWebkitCache)

    // set javascript flags on all web pages
    // params: javascript flags to set
    IPC_MESSAGE_CONTROL1(View_Mgr_SetJavascriptFlags, std::string)

    // enable/disable webkit debugger
    // params: enable debugger
    IPC_MESSAGE_CONTROL1(View_Mgr_EnableDebugger, bool)

    // perform low memory actions on the WAM side
    // params: perform expensive cleanup operations
    IPC_MESSAGE_CONTROL1(View_Mgr_PerformLowMemoryActions, bool)

    // notifies WAM that the system is shutting down
    IPC_MESSAGE_CONTROL0(View_Mgr_ShutdownEvent)

    // retrieves a list of process id's for all web apps currently running
    // params: include system apps
    IPC_MESSAGE_CONTROL1(View_Mgr_ListOfRunningAppsRequest, bool)

    // delete the HTML5 database for the given domain
    // params: domain
    IPC_MESSAGE_CONTROL1(View_Mgr_DeleteHTML5Database, std::string)

    // notification that the ui has been resized
    // params: width, height
    IPC_MESSAGE_CONTROL2(View_Mgr_UiDimensionsChanged, int, int)

    // tell the webkit process to suspend
    // params: suspend was successful
    IPC_SYNC_MESSAGE_CONTROL0_1(View_Mgr_SuspendWebkitProcess, bool)

    // provide access to shared/global properties
    // params: key to shared buffer containing global properties
    IPC_MESSAGE_CONTROL1(View_Mgr_GlobalProperties, int)

// ROUTED MESSAGES

    // sets focus on a window
    // params: enable focus
    IPC_MESSAGE_ROUTED1(View_Focus, bool)

    // resize a window to the given dimensions
    // params: width, height, resize buffer
    IPC_MESSAGE_ROUTED3(View_Resize, int, int, bool)

    // synchronously resize a window to the given dimensions
    // params: width, height, resize buffer, new buffer key (out)
    IPC_SYNC_MESSAGE_ROUTED3_1(View_SyncResize, int, int, bool, int)

    // synchronously flip the dimensions of a window
    // params: width, height
    IPC_SYNC_MESSAGE_ROUTED2_0(View_Flip, int, int)

    // flip the dimensions of a window
    // params: width, height, screen width, screen height
    IPC_MESSAGE_ROUTED4(View_AsyncFlip, int, int, int, int)

    // inform the backing window about it's new dimensions without actually changing them
    // params: width, height
    IPC_MESSAGE_ROUTED2(View_AdjustForPositiveSpace, int, int)

    // tells a window that the keyboard is shown/hidden
    // params: shown
    IPC_MESSAGE_ROUTED1(View_KeyboardShown, bool)

    // tells a window to close itself
    // params: disable keep-alive
    IPC_MESSAGE_ROUTED1(View_Close, bool)

    // send an input event to a window
    // params: structure containing event information (mouse, accel, gesture, etc.)
    IPC_MESSAGE_ROUTED1(View_InputEvent, SysMgrEventWrapper)

    // send a key event to a window
    // params: structure containing information about a key event
    IPC_MESSAGE_ROUTED1(View_KeyEvent, SysMgrKeyEvent)

    // send a touch event to a window
    // params: structure containing information about a touch event
    IPC_MESSAGE_ROUTED1(View_TouchEvent, SysMgrTouchEvent)

    // informs a window that full screen mode has been enabled (PDK only)
    IPC_MESSAGE_ROUTED0(View_FullScreenEnabled)

    // synchronously informs a window that full screen mode has been disabled (PDK only)
    IPC_SYNC_MESSAGE_ROUTED0_0(View_FullScreenDisabled)

    // changes direct rendering state for a window (enable/disable depending on shared meta data)
    IPC_MESSAGE_ROUTED0(View_DirectRenderingChanged)

    // informs a PDK window to pause itself
    IPC_MESSAGE_ROUTED0(View_Pause)

    // informs a PDK window to resume itself
    IPC_MESSAGE_ROUTED0(View_Resume)

    // informs the web app that its backing window has completed running the requested scene transition
    IPC_MESSAGE_ROUTED0(View_SceneTransitionFinished)

    // perform a cut operation on a window
    IPC_MESSAGE_ROUTED0(View_ClipboardEvent_Cut)

    // perform a copy operation on a window
    IPC_MESSAGE_ROUTED0(View_ClipboardEvent_Copy)

    // perform a paste operation on a window
    IPC_MESSAGE_ROUTED0(View_ClipboardEvent_Paste)

    // perform a select all operation on the currently selected content
    IPC_MESSAGE_ROUTED0(View_SelectAll)

    // sets/replaces a marked-up/composed piece of text in the currently focused input field
    // params: string to replace the current composition
    IPC_MESSAGE_ROUTED1(View_SetComposingText, std::string)

    // commits the current composition string and removes its markup
    IPC_MESSAGE_ROUTED0(View_CommitComposingText)

    // issues an editor action on the currently focused input field
    // params: action to perform (next/previous field, etc.)
    IPC_MESSAGE_ROUTED1(View_PerformEditorAction, int)

    // inserts a string of characters into the currently focused input field
    // params: string to insert
    IPC_MESSAGE_ROUTED1(View_CommitText, std::string)

    // blurs the currently focused input field
    IPC_MESSAGE_ROUTED0(View_RemoveInputFocus)

IPC_END_MESSAGES(View)


IPC_BEGIN_MESSAGES(ViewHost)

// CONTROL MESSAGES

    // a key event was not handled by the ViewHost
    // params: rejected key event
    IPC_MESSAGE_CONTROL1(View_Host_ReturnedKeyEvent, SysMgrKeyEvent)

    // creates a new window (used to create PDK cards, type seems to be irrelevant)
    // params: window key (shmget), type, width, height
    IPC_MESSAGE_CONTROL4(ViewHost_PrepareAddWindow, int, int, int, int)

    // creates a new window (used by WAM)
    // params: window key (shmget), metaDataKey, type, width, height
    IPC_MESSAGE_CONTROL5(ViewHost_PrepareAddWindowWithMetaData, int, int, int, int, int)

    // the window is ready
    // params: window key
    IPC_MESSAGE_CONTROL1(ViewHost_AddWindow, int)

    // the window should be removed/deleted
    // params: window key
    IPC_MESSAGE_CONTROL1(ViewHost_RemoveWindow, int)

    // failure to launch a modal window
    // params: error code
    IPC_MESSAGE_CONTROL1(ViewHost_ModalDismissedAtPreCreate, int)

    // set window properties
    // params: json string representing an object containing properties to set
    IPC_MESSAGE_CONTROL2(ViewHost_SetWindowProperties, int, std::string)

    // focus a window
    // params: window key
    IPC_MESSAGE_CONTROL1(ViewHost_FocusWindow, int)

    // unfocus a window
    // params: window key
    IPC_MESSAGE_CONTROL1(ViewHost_UnfocusWindow, int)

    // tells the system to send a paste event to the active window
    IPC_MESSAGE_CONTROL0(ViewHost_PasteToActiveWindow)

    // tells the system that it can finish booting (all required components in WAM have finished loading)
    IPC_MESSAGE_CONTROL0(ViewHost_BootupFinished)

    // Add, Remove, Clear a content indicator (controls home button lighting)
    // params: event containing the operation to carry out
    IPC_MESSAGE_CONTROL1(ViewHost_NewContentEvent, NewContentIndicatorEventWrapper)

    // Add, Remove, Clear or PlaySound for a banner message
    // params: event containing the operation to carry out
    IPC_MESSAGE_CONTROL1(ViewHost_BannerMessageEvent, BannerMessageEventWrapper)

    // Add, Update, Remove the active call banner from the system
    // params: event containing the operation to carry out
    IPC_MESSAGE_CONTROL1(ViewHost_ActiveCallBannerEvent, ActiveCallBannerEventWrapper)

    // Enter/Exit dock mode (only allowed by the systemui app)
    // params: enable
    IPC_MESSAGE_CONTROL1(ViewHost_EnableDockMode, bool)

    // Cancel all haptics running on the device
    IPC_MESSAGE_CONTROL0(ViewHost_CancelVibrations)

    // tells the system to render a launch glow image anchored at the provided offset (launcher only)
    // params: x offset, y offset
    IPC_MESSAGE_CONTROL2(ViewHost_ApplyLaunchFeedback, int, int)

    // sends a json string containing process id's and app id's of all web apps currently running
    // params: json string contains process/app id's of running apps
    IPC_MESSAGE_CONTROL1(ViewHost_ListOfRunningAppsResponse, std::string)

    // perform low memory actions
    // params: allow expensive clean up
    IPC_MESSAGE_CONTROL1(ViewHost_LowMemoryActionsRequested, bool)

    // notifies system that an app launch was prevented due to low memory
    IPC_MESSAGE_CONTROL0(ViewHost_AppLaunchPreventedUnderLowMemory)

// ROUTED MESSAGES

    // informs a window that a region has been updated
    // params: x, y, width, height
    IPC_MESSAGE_ROUTED4(ViewHost_UpdateWindowRegion, int, int, int, int)

    // informs a window that its entire contents has been updated
    IPC_MESSAGE_ROUTED0(ViewHost_UpdateFullWindow)

    // requests that a window flushes and unlocks its painting buffer
    IPC_MESSAGE_ROUTED0(ViewHost_UpdateWindowRequest)

    // provides the dimensions of the window that are being rendered into
    // params: width, height
    IPC_MESSAGE_ROUTED2(ViewHost_SetVisibleDimensions, int, int)

    // notifies the system that a card window has initiated a scene transition
    // params: width of shared transition buffer, height of shared transition buffer
    IPC_MESSAGE_ROUTED2(ViewHost_SceneTransitionPrepare, int, int)

    // notifies the system that a card can start running the scene transition
    // params: name of the transition to run (push/pop/etc)
    IPC_MESSAGE_ROUTED1(ViewHost_SceneTransitionRun, std::string)

    // notifies the system that a card should cancel out of a prepared/running scene transition
    IPC_MESSAGE_ROUTED0(ViewHost_SceneTransitionCancel)

    // notifies the system that a card window has initiated a cross app scene transition
    IPC_MESSAGE_ROUTED0(ViewHost_SceneTransitionPrepareCrossApp)

    // sets the app id for a window
    // params: app id
    IPC_MESSAGE_ROUTED1(ViewHost_SetAppId, std::string)

    // sets the process id for a window
    // params: process id
    IPC_MESSAGE_ROUTED1(ViewHost_SetProcessId, std::string)

    // sets the app id of the app that launched this window
    // params: app id of the launching app
    IPC_MESSAGE_ROUTED1(ViewHost_SetLaunchingAppId, std::string)

    // sets the process id of the app that launched this window
    // params: process id of the launching app
    IPC_MESSAGE_ROUTED1(ViewHost_SetLaunchingProcessId, std::string)

    // sets the name given to this window
    // params: name
    IPC_MESSAGE_ROUTED1(ViewHost_SetName, std::string)

    // set the sound and sound class for an Alert window
    // params: sound file name, sound class
    IPC_MESSAGE_ROUTED2(ViewHost_Alert_SetSoundParams, std::string, std::string)

    // rectangular area used by the system when displaying this alert on the lock screen
    // params: left, right, top, bottom
    IPC_MESSAGE_ROUTED4(ViewHost_Alert_SetContentRect, int, int, int, int)

    // sets whether this dashboard wants click events sent to it when shown on the lock screen
    // params: allow
    IPC_MESSAGE_ROUTED1(ViewHost_Dashboard_SetClickableWhenLocked, bool)

    // sets whether the dashboard item should be deletable by the user (only certain applications are allowed to use this)
    // params: persistent
    IPC_MESSAGE_ROUTED1(ViewHost_Dashboard_SetPersistent, bool)

    // sets a non-default icon used when a closed dashboard contains this window
    // params: icon file name
    IPC_MESSAGE_ROUTED1(ViewHost_Dashboard_SetIcon, std::string)

    // configure launch options for this card
    // params: event containing launch options for this card
    IPC_MESSAGE_ROUTED1(ViewHost_Card_AppLaunchOptionsEvent, AppLaunchOptionsEventWrapper)

    // notifies the system that this window has finished flipping it's contents
    // params: width, height, screen width (unused), screen height (unused)
    IPC_MESSAGE_ROUTED4(ViewHost_AsyncFlipCompleted, int, int, int, int)

    // reports input focus changes of a window
    // params: focus enabled, information about the current input field
    IPC_MESSAGE_ROUTED2(ViewHost_EditorFocusChanged, bool, PalmIME::EditorState)

    // notifies the system that this window wants/doesn't want touch events sent to it
    // params: allow touch events
    IPC_MESSAGE_ROUTED1(ViewHost_EnableTouchEvents, bool)

    // notifies the system that this window's auto cap state has changed
    // params: enable auto capitilization
    IPC_MESSAGE_ROUTED1(ViewHost_AutoCapChanged, bool)

    // notifies the system that a card window has set a new orientation for itself
    // params: new orientation
    IPC_MESSAGE_ROUTED1(ViewHost_Card_SetAppOrientation, int)

    // notifies the system that a card window has modified orientation locking
    // params: enable free orientation
    IPC_MESSAGE_ROUTED1(ViewHost_Card_SetFreeOrientation, int)

    // notifies the system that a card window has fixed its orientation
    // params: fixed orientation, is portrait
    IPC_MESSAGE_ROUTED2(ViewHost_Card_SetAppFixedOrientation, int, bool)

IPC_END_MESSAGES(ViewHost)
