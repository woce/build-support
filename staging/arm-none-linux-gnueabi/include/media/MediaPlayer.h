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
 * Edit MediaPlayer in IDL file or code generation template instead.
 */
 
#ifndef media_MediaPlayer_h
#define media_MediaPlayer_h

#include <media//itypes.h>
#include <boost/shared_ptr.hpp>
#include <media/MediaObject.h>

namespace media { 

class MediaPlayerChangeListener;

struct HttpParameters;
struct VideoBounds;
typedef enum NetworkState {
    NETWORK_EMPTY,
    NETWORK_IDLE,
    NETWORK_LOADING,
    NETWORK_LOADED
} NetworkState;

typedef enum Error {
    NO_ERROR,
    INVALID_SOURCE_ERROR,
    NETWORK_ERROR,
    FORMAT_ERROR,
    DECODE_ERROR
} Error;

typedef enum VideoFitMode {
    VIDEO_FIT,
    VIDEO_FILL
} VideoFitMode;

typedef enum ReadyState {
    HAVE_NOTHING,
    HAVE_METADATA,
    HAVE_CURRENT_DATA,
    HAVE_FUTURE_DATA,
    HAVE_ENOUGH_DATA
} ReadyState;

struct HttpParameters {
    std::string cookies;
    std::string useragent;
    std::string extraheaders;
};

struct VideoBounds {
    float left;
    float top;
    float width;
    float height;
};






class MediaPlayer {
public:
    virtual ~MediaPlayer() { }
    
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
    virtual bool getVisible() = 0;
    virtual void setVisible(bool visible) = 0;
    virtual bool getSupportsFullscreen() = 0;

    virtual boost::shared_ptr<HttpParameters> getHttpparameters() = 0;
    virtual void setHttpparameters(boost::shared_ptr<HttpParameters> httpparameters) = 0;
    virtual bool getPausable() = 0;

    virtual long getVideoWidth() = 0;

    virtual long getVideoHeight() = 0;

    virtual bool getHasVideo() = 0;

    virtual bool getHasAudio() = 0;

    virtual bool getControls() = 0;
    virtual void setControls(bool controls) = 0;
    virtual bool getEos() = 0;

    virtual Error getError() = 0;

    virtual std::string getExtendedError() = 0;

    virtual std::string getSource() = 0;

    virtual AudioStreamClass getAudioClass() = 0;

    virtual std::string getVideoFrameCapture() = 0;

    virtual float getDuration() = 0;

    virtual float getCurrentTime() = 0;

    virtual bool getSeeking() = 0;

    virtual float getStartTime() = 0;

    virtual float getEndTime() = 0;
    virtual void setEndTime(float endTime) = 0;
    virtual float getRate() = 0;
    virtual void setRate(float rate) = 0;
    virtual bool getPreservesPitch() = 0;
    virtual void setPreservesPitch(bool preservesPitch) = 0;
    virtual bool getPaused() = 0;

    virtual std::string getPausedChangeReason() = 0;

    virtual float getVolume() = 0;
    virtual void setVolume(float volume) = 0;
    virtual NetworkState getNetworkState() = 0;

    virtual ReadyState getReadyState() = 0;

    virtual float getMaxTimeSeekable() = 0;

    virtual long getDataRate() = 0;

    virtual bool getTotalBytesKnown() = 0;

    virtual long getTotalBytes() = 0;

    virtual long getBytesLoaded() = 0;

    virtual VideoFitMode getFitMode() = 0;
    virtual void setFitMode(VideoFitMode fitMode) = 0;
    virtual boost::shared_ptr<VideoBounds> getVideoBounds() = 0;
    virtual void setVideoBounds(boost::shared_ptr<VideoBounds> videoBounds) = 0;
    virtual bool getAutobuffer() = 0;
    virtual void setAutobuffer(bool autobuffer) = 0;
    virtual std::string getVideoTitle() = 0;
    virtual void setVideoTitle(std::string videoTitle) = 0;
    virtual std::string getDescription() = 0;
    virtual void setDescription(std::string description) = 0;
    virtual long getNumThumbnails() = 0;
    virtual void setNumThumbnails(long numThumbnails) = 0;
    virtual std::string getLastThumbnail() = 0;

    virtual bool getThumbnailsGenerated() = 0;

    virtual bool getSaved() = 0;

    virtual std::string getLastSaved() = 0;

    virtual std::string getTrimVideoTitle() = 0;
    virtual void setTrimVideoTitle(std::string trimVideoTitle) = 0;
    virtual std::string getTrimVideoThumbnail() = 0;
    virtual void setTrimVideoThumbnail(std::string trimVideoThumbnail) = 0;
    
    // methods
    virtual void unload() = 0;
    virtual void cancelLoad() = 0;
    virtual void load(std::string uri,AudioStreamClass audioClass) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void suspend() = 0;
    virtual void seek(float time) = 0;
    virtual void generateThumbnails(long count,long width,long height,float startTime,float endTime,std::string filenameBase) = 0;
    virtual void trim(float start,float end,std::string filename) = 0;

    // change listener
    virtual void addMediaPlayerChangeListener(MediaPlayerChangeListener* l) = 0;
    virtual void removeMediaPlayerChangeListener(MediaPlayerChangeListener* l) = 0;
    
    // deprecated change listener - use pointers instead of smart pointers
    virtual void addMediaPlayerChangeListener(boost::shared_ptr<MediaPlayerChangeListener> l) = 0;
    virtual void removeMediaPlayerChangeListener(boost::shared_ptr<MediaPlayerChangeListener> l) = 0;};

class MediaPlayerChangeListener {
public:
    virtual ~MediaPlayerChangeListener() { }
    
	virtual void visibleChanged() { };
	virtual void supportsFullscreenChanged() { };
	virtual void httpparametersChanged() { };
	virtual void pausableChanged() { };
	virtual void videoWidthChanged() { };
	virtual void videoHeightChanged() { };
	virtual void hasVideoChanged() { };
	virtual void hasAudioChanged() { };
	virtual void controlsChanged() { };
	virtual void eosChanged() { };
	virtual void errorChanged() { };
	virtual void extendedErrorChanged() { };
	virtual void sourceChanged() { };
	virtual void audioClassChanged() { };
	virtual void videoFrameCaptureChanged() { };
	virtual void durationChanged() { };
	virtual void currentTimeChanged() { };
	virtual void seekingChanged() { };
	virtual void startTimeChanged() { };
	virtual void endTimeChanged() { };
	virtual void rateChanged() { };
	virtual void preservesPitchChanged() { };
	virtual void pausedChanged() { };
	virtual void pausedChangeReasonChanged() { };
	virtual void volumeChanged() { };
	virtual void networkStateChanged() { };
	virtual void readyStateChanged() { };
	virtual void maxTimeSeekableChanged() { };
	virtual void dataRateChanged() { };
	virtual void totalBytesKnownChanged() { };
	virtual void totalBytesChanged() { };
	virtual void bytesLoadedChanged() { };
	virtual void fitModeChanged() { };
	virtual void videoBoundsChanged() { };
	virtual void autobufferChanged() { };
	virtual void videoTitleChanged() { };
	virtual void descriptionChanged() { };
	virtual void numThumbnailsChanged() { };
	virtual void lastThumbnailChanged() { };
	virtual void thumbnailsGeneratedChanged() { };
	virtual void savedChanged() { };
	virtual void lastSavedChanged() { };
	virtual void trimVideoTitleChanged() { };
	virtual void trimVideoThumbnailChanged() { };
};

} /* namespace media */ 

#endif // media_MediaPlayer_h
