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

#ifndef media_MediaClient_h
#define media_MediaClient_h

#include <boost/shared_ptr.hpp>
#include <string>
#include <glib.h>

namespace media {

class MediaPlayer;
class MediaCaptureV3;
class Clonk;
class MediaResourceManager;
class ManagedMediaResource;
class LunaConnector;

/**
 * Class to act as a factory for creating c++ media clients.  At some point there
 * may be multiple transports available.  Currently there is only luna service.
 */
class MediaClient {
public:

    /**
     * Factory method to create a media player client using a luna service
     * as the transport.
     * 
     * @param connector  the implementation of the luna bus connection logic.  The
     * lifetime of the object passed in is expected to exceed the lifetime of the 
     * smart pointer to the media object returned.
     */
    static boost::shared_ptr<MediaPlayer> createLunaMediaPlayer(LunaConnector& connector);

    /**
     * Factory method to create a media capture client using a luna service
     * as the transport.
     * 
     * @param connector  the implementation of the luna bus connection logic.  The
     * lifetime of the object passed in is expected to exceed the lifetime of the 
     * smart pointer to the media object returned.
     */
    static boost::shared_ptr<MediaCaptureV3> createLunaMediaCapture(LunaConnector& connector);

    /**
     * Factory method to create a clonk client using a luna service as the
     * transport.
     *
     * @param connector  the implementation of the luna bus connection logic.  The
     * lifetime of the object passed in is expected to exceed the lifetime of the
     * smart pointer to the media object returned.
     */
    static boost::shared_ptr<Clonk> createLunaMediaClonk(LunaConnector& connector);


    /**
     * Factory method to connect to an existing media player using a luna service
     * as the transport.
     * 
     * @param uri the location of existing player
     */
    static boost::shared_ptr<MediaPlayer> connectLunaMediaPlayer(const std::string& uri, LunaConnector* l);

    // THIS METHOD IS DEPRECATED!!
    static boost::shared_ptr<MediaPlayer> connectLunaMediaPlayer(const std::string& uri, GMainLoop* l);

    /**
     * Factory method to connect to an existing media capture using a luna service
     * as the transport.
     * 
     * @param uri the location of existing capture
     */
    static boost::shared_ptr<MediaCaptureV3> connectLunaMediaCapture(const std::string& uri, LunaConnector* l);

    // THIS METHOD IS DEPRECATED!!
    static boost::shared_ptr<MediaCaptureV3> connectLunaMediaCapture(const std::string& uri, GMainLoop* l);


    /**
     * Factory method to connect to an existing clonk using a luna service as the
     * transport.
     *
     * @param uri the location of existing clonk
     */
    static boost::shared_ptr<Clonk> connectLunaMediaClonk(const std::string& uri, LunaConnector* l);


    /**
     * Factory method to create client-side ipc stubs for a MediaResourceManager using
     * the luna service as a transport.  
     */
    static boost::shared_ptr<MediaResourceManager> createLunaMediaResourceManager(GMainLoop* l);


    /**
     * Factory method to create client-side ipc stubs for a ManagedMediaResource using
     * the luna service as a transport,  using this function if LunaConnector is persistent,  e.g. related with webkit global gmainloop
     */ 
    static boost::shared_ptr<ManagedMediaResource> createLunaManagedMediaResource(const std::string& uri, LunaConnector* l);
    
    /**
     * Factory method to create client-side ipc stubs for a ManagedMediaResource using
     * the luna service as a transport,  the LunaConnector will be derefed,
     * Using this function if the LunaConnector needs to be deleted *after* the ManagedMediaResource is deleted
     */ 
    static boost::shared_ptr<ManagedMediaResource> createLunaManagedMediaResourceShared(const std::string& uri, boost::shared_ptr<LunaConnector> l);
};


}

#endif // media_MediaClient_h
