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

/*
 * GENERATED FILE - DO NOT EDIT DIRECTLY!
 * Edit MediaObject in IDL file or code generation template instead.
 */
 
#ifndef media_MediaObject_h
#define media_MediaObject_h

#include <media//itypes.h>
#include <boost/shared_ptr.hpp>


namespace media { 

class MediaObjectChangeListener;

typedef enum AudioStreamClass {
    kAudioStreamRingtone,
    kAudioStreamAlert,
    kAudioStreamMedia,
    kAudioStreamNotification,
    kAudioStreamFeedback,
    kAudioStreamFlash,
    kAudioStreamNavigation,
    kAudioStreamVoicedial,
    kAudioStreamVoip,
    kAudioStreamCalendar,
    kAudioStreamAlarm,
    kAudioStreamDefaultapp,
    kAudioStreamVvm,
    kAudioStreamAlsa,
    kAudioStreamFake,
    kAudioStreamNone
} AudioStreamClass;


class MediaObject {
public:
    virtual ~MediaObject() { }
    
    /**
     * Is the interface currently in an error state?
     */
    virtual boolean _isInErrorState() = 0;
    
    /**
     * Description of the error state.  
     */
    virtual string _getErrorDescription() = 0;
    
    /**
     * Fetch the URI that represents this object
     */
    virtual std::string _getObjectUri() = 0;

	// attributes
    
    // methods

};



} /* namespace media */ 

#endif // media_MediaObject_h
