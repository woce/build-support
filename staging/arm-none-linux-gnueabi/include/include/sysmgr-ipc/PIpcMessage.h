// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.

#ifndef IPC_IPC_MESSAGE_H__
#define IPC_IPC_MESSAGE_H__

#include <stdint.h>
#include <string>

#include "pickle.h"

//------------------------------------------------------------------------------


class PIPC_API PIpcMessage : public Pickle {
 public:

  virtual ~PIpcMessage();

  // Create a message in preparation for reading via payload().
  PIpcMessage(uint32_t capacity);

  // Initialize a message with a user-defined type, and
  // destination WebView ID.
  PIpcMessage(int32_t routing_id, uint16_t type, uint32_t payload_size);

  bool is_valid() const { 
    return header_ != 0;
  }

  // True if this is a synchronous message.
  bool is_sync() const {
    return is_valid() ? (header_->flags & SYNC_BIT) != 0 : false;
  }

  void set_sync() {
    if (is_valid()) header_->flags |= SYNC_BIT;
  }
	
  // Set this on a reply to a synchronous message.
  void set_reply() {
    if (is_valid()) header_->flags |= REPLY_BIT;
  }

  bool is_reply() const {
    return is_valid() ? (header_->flags & REPLY_BIT) != 0 : false;
  }

  // Set this on a reply to a synchronous message to indicate that no receiver
  // was found.
  void set_reply_error() {
    if (is_valid()) header_->flags |= REPLY_ERROR_BIT;
  }

  bool is_reply_error() const {
    return is_valid() ? (header_->flags & REPLY_ERROR_BIT) != 0 : true;
  }

  // Normally when a receiver gets a message and they're blocked on a
  // synchronous message Send, they buffer a message.  Setting this flag causes
  // the receiver to be unblocked and the message to be dispatched immediately.
  void set_unblock(bool unblock) {
	if (!is_valid())
		return;
    if (unblock) {
      header_->flags |= UNBLOCK_BIT;
    } else {
      header_->flags &= ~UNBLOCK_BIT;
    }
  }

  bool should_unblock() const {
    return is_valid() ? (header_->flags & UNBLOCK_BIT) != 0 : false;
  }

  void set_disconnect() {
      if (is_valid()) header_->flags |= DISCONNECT_BIT;
  }

  bool is_disconnect() const {
      return (is_valid()) ? ((header_->flags & DISCONNECT_BIT) != 0) : false;
  }

  void set_suspend() {
      if (is_valid()) header_->flags |= SUSPEND_BIT;
  }

  bool is_suspend() const {
      return (is_valid()) ? ((header_->flags & SUSPEND_BIT) != 0) : false;
  }

  uint16_t type() const {
    return is_valid() ? header_->type : 0;
  }

  int32_t routing_id() const {
    return is_valid() ? header_->routing : 0;
  }

  void set_routing_id(int32_t new_id) {
    if (is_valid()) header_->routing = new_id;
  }

  uint32_t message_id() const {
	 return is_valid() ? header_->id : 0;
  }

  void set_message_id(uint32_t id) {
     if (is_valid()) header_->id = id;
  }

  template<class T>
  static bool Dispatch(const PIpcMessage* msg, T* obj, void (T::*func)()) {
    (obj->*func)();
    return true;
  }

  template<class T>
  static bool Dispatch(const PIpcMessage* msg, T* obj, void (T::*func)() const) {
    (obj->*func)();
    return true;
  }

  template<class T>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&)) {
    (obj->*func)(*msg);
    return true;
  }

  template<class T>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&) const) {
    (obj->*func)(*msg);
    return true;
  }

 protected:

  virtual void reset() { 
    if (is_valid()) {
      Pickle::reset();
      updateIter(sizeof(Header));
    }
  }

  // flags
  enum {
    SYNC_BIT        = 0x0004,
    REPLY_BIT       = 0x0008,
    REPLY_ERROR_BIT = 0x0010,
    UNBLOCK_BIT     = 0x0020,
    DISCONNECT_BIT  = 0x0040,
    SUSPEND_BIT     = 0x0080 // only valid for Synchronous messages, used to suspend the client process
  };

  struct Header {
    int32_t routing;  // ID of the view that this message is destined for
    uint16_t type;    // specifies the user-defined message type
    uint16_t flags;   // specifies control flags for the message
    uint32_t id;      // Id of this message
  };
  Header* header_;

  // Allow unit test to peek inside
  friend class PIpcMessageTest;

private:
  DISALLOW_COPY_AND_ASSIGN(PIpcMessage);
};

//------------------------------------------------------------------------------

enum SpecialRoutingIDs {
  // indicates that we don't have a routing ID yet.
  MSG_ROUTING_NONE = -2,

  // indicates a general message not sent to a particular tab.
  MSG_ROUTING_CONTROL = 0x7FFFFFFF
};

#define IPC_REPLY_ID 0xFFF0  // Special message type for replies

#endif  // PIPCMESSAGE_H__
