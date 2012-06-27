// @@@LICENSE
//
//      Copyright (c) 2008-2012 Hewlett-Packard Development Company, L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#ifndef media_LunaConnector_h
#define media_LunaConnector_h

#include <lunaservice.h>

namespace media {

/**
 * An interface (pure abstract class) that couples a client of the media api to a media
 * object (client stubs) using a luna service for communication.  
 * <p>
 * The connection to the luna bus is made by calling 
 * the <code>connectToBus()</code> method.  
 * <p>
 * The media object will call <code>connected()</code> when a connection is
 * established and the media object is valid.  The media object will try to 
 * maintain a connection automatically so if the connection is lost the connected
 * method may be called more than once.
 * <p>
 * The normal lifetime of a connection will be the lifetime of the media object
 * (i.e. when no more smart pointers reference it the media object will be deleted
 * and no longer connected).  
 */
class LunaConnector {
public:
    virtual ~LunaConnector() {}

    /**
     * Called by the media object when a connection has been made.
     */
    virtual void connected() = 0;

    /**
     * Called by the media object to create a connection to the luna bus.
     */
    virtual LSPalmService* connectToBus() = 0;

    /**
     * Called by the media object if the connection has been lost.
     */
    virtual void disconnected() { }

    /**
     * The default luna connection functionality.
     */
    static LSPalmService* defaultConnection(GMainLoop* l);
};

} // namespace media

#endif // media_LunaConnector_h
