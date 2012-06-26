/* @@@LICENSE
*
*      Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */


#include <string>

#include <PIpcMessageMacros.h>
#include <npapi.h>
#if defined(_NPAPI_H_)  // Pre r78002 WebKit defined this.
#include <nppalmdefs.h> // Removed from r78002 WebKit.
#endif
#include "RemoteAdapterTypes.h"
#include "RemoteAdapterParamTraits.h"


/************* VIEW METHODS ******************/
/************* VIEW METHODS ******************/
/************* VIEW METHODS ******************/
IPC_BEGIN_MESSAGES(View)
	IPC_MESSAGE_ROUTED1(View_Generic, NpPalmGeneric)
	IPC_SYNC_MESSAGE_ROUTED1_1(View_GenericWithResponse, NpPalmGeneric, NpPalmGeneric)
IPC_END_MESSAGES(View)


/************* VIEWHOST METHODS ******************/
/************* VIEWHOST METHODS ******************/
/************* VIEWHOST METHODS ******************/
IPC_BEGIN_MESSAGES(ViewHost)
	IPC_MESSAGE_CONTROL1(ViewHost_Generic, NpPalmGeneric)
IPC_END_MESSAGES(ViewHost)
