// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.

#ifndef BASE_PICKLE_H__
#define BASE_PICKLE_H__

#include <string>
#include <stdint.h>

#include "basictypes.h"

// This class provides facilities for basic binary value packing and unpacking.
//
// The Pickle class supports appending primitive values (ints, strings, etc.)
// to a pickle instance.  The internal memory buffer is exposed as the "data" 
// of the Pickle.
//
// When reading from a Pickle object, it is important for the consumer to know
// what value types to read and in what order to read them as the Pickle does
// not keep track of the type of data written to it.
//
// The Pickle's data has a header which contains the size of the Pickle's
// payload.  It can optionally support additional space in the header.  That
// space is controlled by the header_size parameter passed to the Pickle
// constructor.
//
class PIPC_API Pickle {
 public:
  virtual ~Pickle();

  // Initialize a Pickle object with the specified header size in bytes, which
  // must be greater-than-or-equal-to sizeof(Pickle::Header).  The header size
  // will be rounded up to ensure that the header size is 32bit-aligned.
  // Used for marshalling.
  explicit Pickle(size_t capacity);

  // Returns the size of the Pickle's data.
  int32_t size() const { return capacity_; }

  // Returns the data for this Pickle.
  char* payload() const { return payload_; }

  // Methods for reading the payload of the Pickle. If successful, these 
  // methods return true.  Otherwise, false is returned to indicate that 
  // the result could not be extracted.
  bool readBool(bool* result) const;
  bool readChar(char* result) const;
  bool readInt16(int16_t* result) const;
  bool readInt32(int32_t* result) const;
  bool readSize(size_t* result) const;
  bool readInt64(int64_t* result) const;
  bool readDouble(double* result) const;
  bool readString(std::string* result) const;
  bool readData(const char** data, int* length) const;
  bool readBytes(const char** data, int length) const;

  // Safer version of readInt32() checks for the result not being negative.
  // Use it for reading the object sizes.
  bool readLength(int32_t* result) const;

  // Methods for adding to the payload of the Pickle.  These values are
  // appended to the end of the Pickle's payload.  When reading values from a
  // Pickle, it is important to read them in the order in which they were added
  // to the Pickle.
  bool writeBool(bool value) {
    return writeInt32(value ? 1 : 0);
  }
  bool writeChar(char value) {
    return writeBytes(&value, sizeof(value));
  }
  bool writeInt16(int16_t value) {
    return writeBytes(&value, sizeof(value));
  }
  bool writeInt32(int32_t value) {
    return writeBytes(&value, sizeof(value));
  }
  bool writeSize(size_t value) {
    return writeBytes(&value, sizeof(value));
  }
  bool writeInt64(int64_t value) {
    return writeBytes(&value, sizeof(value));
  }
  bool writeDouble(double value) {
    return writeBytes(&value, sizeof(value));
  }
  bool writeString(const std::string& value);
  bool writeData(const char* data, int length);
  bool writeBytes(const void* data, int32_t data_len);

  // Methods for checking how much space is needed in order to store
  // the passed unit.
  static uint32_t lengthOf(const bool& value) {
    return sizeof(uint32_t);
  }
  static uint32_t lengthOf(const char& value) {
    return sizeof(uint32_t);
  }
  static uint32_t lengthOf(const int16_t& value) {
    return sizeof(uint32_t);
  }
  static uint32_t lengthOf(const int32_t& value) {
    return sizeof(uint32_t);
  }
  static uint32_t lengthOf(const uint32_t& value) {
    return sizeof(uint32_t);
  }
  static uint32_t lengthOf(const int64_t& value) {
    return alignInt(sizeof(value), sizeof(uint64_t));
  }
  static uint32_t lengthOf(const double& value) {
    return alignInt(sizeof(value), sizeof(uint32_t));
  }
  static uint32_t lengthOf(const std::string& value) {
    return lengthOf(value.c_str(), value.size());
  }
  static uint32_t lengthOf(const char* value, int len) {
    return lengthOf(len) + alignInt(len, sizeof(uint32_t));
  }

  // If there is no room for the given data before the end of the
  // payload, returns false.
  bool hasRoomFor(int len) const {
    if (len < 0)
      return false;
    return position_ + alignInt(len, sizeof(uint32_t)) <= capacity_;
  }

 protected:

  // Reset the position to the beginning of the payload.
  virtual void reset() { position_ = 0; }

  // Aligns 'i' by rounding it up to the next multiple of 'alignment'
  static size_t alignInt(size_t i, int alignment) {
    return i + (alignment - (i % alignment)) % alignment;
  }

  // Moves the iterator by the given number of bytes, making sure it is aligned.
  // Pointer (iterator) is NOT aligned, but the change in the pointer
  // is guaranteed to be a multiple of sizeof(uint32).
  void updateIter(int bytes) const {
    position_ += alignInt(bytes, sizeof(uint32_t));
  }

  // Allow unit test to peek inside
  friend class PickleTest;

 private:
  
  char* payload_;
  mutable uint32_t position_;
  size_t capacity_;

  DISALLOW_COPY_AND_ASSIGN(Pickle);
};

#endif  // BASE_PICKLE_H__
