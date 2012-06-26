// Copyright (c) 2006-2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.

#ifndef PIPCMESSAGEUTILS_H_
#define PIPCMESSAGEUTILS_H_

#include <string>

#include "PIpcMessage.h"
#include "tuple.h"

// Used by IPC_BEGIN_MESSAGES so that each message class starts from a unique
// base.  PIpcMessages have unique IDs across channels in order for the IPC logging
// code to figure out the message class from its ID.
enum IPCMessageStart {
  // By using a start value of 0 for automation messages, we keep backward
  // compatibility with old builds.
  AutomationMsgStart = 0,
  TestMsgStart,
  ViewMsgStart,
  ViewHostMsgStart,
  SysMgrMsgStart,
  RemoteMsgStart,
  // NOTE: this enum is used by IPC_MESSAGE_MACRO to generate a unique message
  // id.  Only 4 bits are used for the message type, so if this enum needs more
  // than 16 entries, that code needs to be updated.
  LastMsgIndex
};

COMPILE_ASSERT(LastMsgIndex <= 16, need_to_update_IPC_MESSAGE_MACRO);

//-----------------------------------------------------------------------------
// ParamTraits specializations, etc.

template <class P> struct ParamTraits {};

template <class P>
static inline void WriteParam(PIpcMessage* m, const P& p) {
  ParamTraits<P>::Write(m, p);
}

template <class P>
static inline bool ReadParam(const PIpcMessage* m, P* p) {
  return ParamTraits<P>::Read(m, p);
}

template <class P>
static inline uint32_t ParamLength(const P& p) {
  return ParamTraits<P>::Length(p);
}

template <>
struct ParamTraits<bool> {
  typedef bool param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeBool(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readBool(r);
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<char> {
  typedef char param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeChar(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readChar(r);
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<int16_t> {
  typedef int16_t param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeInt16(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readInt16(r);
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<int32_t> {
  typedef int32_t param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeInt32(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readInt32(r);
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<int64_t> {
  typedef int64_t param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeInt64(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readInt64(r);
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<unsigned char> {
  typedef unsigned char param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeChar(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readChar(reinterpret_cast<char*>(r));
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<uint16_t> {
  typedef uint16_t param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeInt16(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readInt16(reinterpret_cast<int16_t*>(r));
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<uint32_t> {
  typedef uint32_t param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeInt32(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readInt32(reinterpret_cast<int32_t*>(r));
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<uint64_t> {
  typedef uint64_t param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeInt64(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readInt64(reinterpret_cast<int64_t*>(r));
  }
  static uint32_t Length(const param_type& p) {
	  return PIpcMessage::lengthOf(static_cast<int64_t>(p));
  }
};

template <>
struct ParamTraits<double> {
  typedef double param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeDouble(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readDouble(r);
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <>
struct ParamTraits<std::string> {
  typedef std::string param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    m->writeString(p);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return m->readString(r);
  }
  static uint32_t Length(const param_type& p) {
    return PIpcMessage::lengthOf(p);
  }
};

template <class A, class B>
struct ParamTraits<std::pair<A, B> > {
  typedef std::pair<A, B> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.first);
    WriteParam(m, p.second);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
	return ReadParam(m, &r->first) && ReadParam(m, &r->second);
  }
  static uint32_t Length(const param_type& p) {
    return ParamLength(p.first) + ParamLength(p.second);
  }
};



template <>
struct ParamTraits<Tuple0> {
  typedef Tuple0 param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return true;
  }
  static uint32_t Length(const param_type& p) {
    return 0;
  }
};

template <class A>
struct ParamTraits< Tuple1<A> > {
  typedef Tuple1<A> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return ReadParam(m, &r->a);
  }
  static uint32_t Length(const param_type& p) {
    return ParamLength(p.a);
  }
};

template <class A, class B>
struct ParamTraits< Tuple2<A, B> > {
  typedef Tuple2<A, B> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
    WriteParam(m, p.b);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return (ReadParam(m, &r->a) &&
            ReadParam(m, &r->b));
  }
  static uint32_t Length(const param_type& p) {
    return (ParamLength(p.a) +
            ParamLength(p.b));
  }
};

template <class A, class B, class C>
struct ParamTraits< Tuple3<A, B, C> > {
  typedef Tuple3<A, B, C> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
    WriteParam(m, p.b);
    WriteParam(m, p.c);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return (ReadParam(m, &r->a) &&
            ReadParam(m, &r->b) &&
            ReadParam(m, &r->c));
  }
  static uint32_t Length(const param_type& p) {
    return (ParamLength(p.a) +
            ParamLength(p.b) +
            ParamLength(p.c));
  }
};

template <class A, class B, class C, class D>
struct ParamTraits< Tuple4<A, B, C, D> > {
  typedef Tuple4<A, B, C, D> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
    WriteParam(m, p.b);
    WriteParam(m, p.c);
    WriteParam(m, p.d);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return (ReadParam(m, &r->a) &&
            ReadParam(m, &r->b) &&
            ReadParam(m, &r->c) &&
            ReadParam(m, &r->d));
  }
  static uint32_t Length(const param_type& p) {
    return (ParamLength(p.a) +
            ParamLength(p.b) +
            ParamLength(p.c) +
            ParamLength(p.d));
  }
};

template <class A, class B, class C, class D, class E>
struct ParamTraits< Tuple5<A, B, C, D, E> > {
  typedef Tuple5<A, B, C, D, E> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
    WriteParam(m, p.b);
    WriteParam(m, p.c);
    WriteParam(m, p.d);
    WriteParam(m, p.e);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return (ReadParam(m, &r->a) &&
            ReadParam(m, &r->b) &&
            ReadParam(m, &r->c) &&
            ReadParam(m, &r->d) &&
            ReadParam(m, &r->e));
  }
  static uint32_t Length(const param_type& p) {
    return (ParamLength(p.a) +
            ParamLength(p.b) +
            ParamLength(p.c) +
            ParamLength(p.d) +
            ParamLength(p.e));
  }
};

template <class A, class B, class C, class D, class E, class F>
struct ParamTraits< Tuple6<A, B, C, D, E, F> > {
  typedef Tuple6<A, B, C, D, E, F> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
    WriteParam(m, p.b);
    WriteParam(m, p.c);
    WriteParam(m, p.d);
    WriteParam(m, p.e);
    WriteParam(m, p.f);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return (ReadParam(m, &r->a) &&
            ReadParam(m, &r->b) &&
            ReadParam(m, &r->c) &&
            ReadParam(m, &r->d) &&
            ReadParam(m, &r->e) &&
            ReadParam(m, &r->f));
  }
  static uint32_t Length(const param_type& p) {
    return (ParamLength(p.a) +
            ParamLength(p.b) +
            ParamLength(p.c) +
            ParamLength(p.d) +
            ParamLength(p.e) +
            ParamLength(p.f));
  }
};

template <class A, class B, class C, class D, class E, class F, class G>
struct ParamTraits< Tuple7<A, B, C, D, E, F, G> > {
  typedef Tuple7<A, B, C, D, E, F, G> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
    WriteParam(m, p.b);
    WriteParam(m, p.c);
    WriteParam(m, p.d);
    WriteParam(m, p.e);
    WriteParam(m, p.f);
    WriteParam(m, p.g);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return (ReadParam(m, &r->a) &&
            ReadParam(m, &r->b) &&
            ReadParam(m, &r->c) &&
            ReadParam(m, &r->d) &&
            ReadParam(m, &r->e) &&
            ReadParam(m, &r->f) &&
            ReadParam(m, &r->g));
  }
  static uint32_t Length(const param_type& p) {
    return (ParamLength(p.a) +
            ParamLength(p.b) +
            ParamLength(p.c) +
            ParamLength(p.d) +
            ParamLength(p.e) +
            ParamLength(p.f) +
            ParamLength(p.g));
  }
};

template <class A, class B, class C, class D, class E, class F, class G, class H>
struct ParamTraits< Tuple8<A, B, C, D, E, F, G, H> > {
  typedef Tuple8<A, B, C, D, E, F, G, H> param_type;
  static void Write(PIpcMessage* m, const param_type& p) {
    WriteParam(m, p.a);
    WriteParam(m, p.b);
    WriteParam(m, p.c);
    WriteParam(m, p.d);
    WriteParam(m, p.e);
    WriteParam(m, p.f);
    WriteParam(m, p.g);
    WriteParam(m, p.h);
  }
  static bool Read(const PIpcMessage* m, param_type* r) {
    return (ReadParam(m, &r->a) &&
            ReadParam(m, &r->b) &&
            ReadParam(m, &r->c) &&
            ReadParam(m, &r->d) &&
            ReadParam(m, &r->e) &&
            ReadParam(m, &r->f) &&
            ReadParam(m, &r->h) &&
            ReadParam(m, &r->g));
  }
  static uint32_t Length(const param_type& p) {
    return (ParamLength(p.a) +
            ParamLength(p.b) +
            ParamLength(p.c) +
            ParamLength(p.d) +
            ParamLength(p.e) +
            ParamLength(p.f) +
            ParamLength(p.g) +
             ParamLength(p.h));
  }
};


//-----------------------------------------------------------------------------
// Generic message subclasses

// Used for asynchronous messages.
template <class ParamType>
class PIpcMessageWithTuple : public PIpcMessage {
 public:
  typedef ParamType Param;
  typedef typename ParamType::ParamTuple RefParam;

  PIpcMessageWithTuple(int32_t routing_id, uint16_t type, const RefParam& p)
      : PIpcMessage(routing_id, type, ParamLength(p)) {
    WriteParam(this, p);
  }

  static bool Read(const PIpcMessage* msg, Param* p) {
    if (ReadParam(msg, p))
      return true;
    return false;
  }

  // Generic dispatcher.  Should cover most cases.
  template<class T, class Method>
  static bool Dispatch(const PIpcMessage* msg, T* obj, Method func) {
    Param p;
    if (Read(msg, &p)) {
      DispatchToMethod(obj, func, p);
      return true;
    }
    return false;
  }

  // The following dispatchers exist for the case where the callback function
  // needs the message as well.  They assume that "Param" is a type of Tuple
  // (except the one arg case, as there is no Tuple1).
  template<class T, typename TA>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&, TA)) {
    Param p;
    if (Read(msg, &p)) {
      (obj->*func)(*msg, p.a);
      return true;
    }
    return false;
  }

  template<class T, typename TA, typename TB>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&, TA, TB)) {
    Param p;
    if (Read(msg, &p)) {
      (obj->*func)(*msg, p.a, p.b);
      return true;
    }
    return false;
  }

  template<class T, typename TA, typename TB, typename TC>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&, TA, TB, TC)) {
    Param p;
    if (Read(msg, &p)) {
      (obj->*func)(*msg, p.a, p.b, p.c);
      return true;
    }
    return false;
  }

  template<class T, typename TA, typename TB, typename TC, typename TD>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&, TA, TB, TC, TD)) {
    Param p;
    if (Read(msg, &p)) {
      (obj->*func)(*msg, p.a, p.b, p.c, p.d);
      return true;
    }
    return false;
  }

  template<class T, typename TA, typename TB, typename TC, typename TD,
           typename TE>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&, TA, TB, TC, TD, TE)) {
    Param p;
    if (Read(msg, &p)) {
      (obj->*func)(*msg, p.a, p.b, p.c, p.d, p.e);
      return true;
    }
    return false;
  }

  template<class T, typename TA, typename TB, typename TC, typename TD,
           typename TE, typename TF>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&, TA, TB, TC, TD, TE, TF)) {
    Param p;
    if (Read(msg, &p)) {
      (obj->*func)(*msg, p.a, p.b, p.c, p.d, p.e, p.f);
      return true;
    }
    return false;
  }

  template<class T, typename TA, typename TB, typename TC, typename TD,
           typename TE, typename TF, typename TG>
  static bool Dispatch(const PIpcMessage* msg, T* obj,
                       void (T::*func)(const PIpcMessage&, TA, TB, TC, TD, TE, TF, TG)) {
    Param p;
    if (Read(msg, &p)) {
      (obj->*func)(*msg, p.a, p.b, p.c, p.d, p.e, p.f, p.g);
      return true;
    }
    return false;
  }
};

// Used for synchronous messages.
template <class SendParamType, class ReplyParamType>
class PIpcMessageWithReply : public PIpcMessage {
 public:
  typedef SendParamType SendParam;
  typedef typename SendParam::ParamTuple RefSendParam;
  typedef ReplyParamType ReplyParam;

  ReplyParam reply_;

  PIpcMessageWithReply(int32_t routing_id, uint16_t type,
					   const RefSendParam& send, const ReplyParam& reply)
      : PIpcMessage(routing_id, type, ParamLength(send))
      , reply_(reply) {
    set_sync();
    WriteParam(this, send);
  }

  template<class T, class Method>
  static bool Dispatch(const PIpcMessage* msg, T* obj, Method func) {
    SendParam send_params;
    typename ReplyParam::ValueTuple reply_params;
    PIpcMessage* reply = 0;
    bool error;
    if (ReadParam(msg, &send_params)) {
      DispatchToMethod(obj, func, send_params, &reply_params);
      reply = new PIpcMessage(msg->routing_id(), IPC_REPLY_ID, 
                              ParamLength(reply_params));
      reply->set_reply();
      WriteParam(reply, reply_params);
      error = false;
    } else {
      reply = new PIpcMessage(msg->routing_id(), IPC_REPLY_ID, 
                              ParamLength(reply_params));
      reply->set_reply_error();
      error = true;
    }

    obj->channel()->sendReply(reply);
    return !error;
  }

  template<typename TA>
  static void WriteReplyParams(PIpcMessage* reply, TA a) {
    ReplyParam p(a);
    WriteParam(reply, p);
  }

  template<typename TA, typename TB>
  static void WriteReplyParams(PIpcMessage* reply, TA a, TB b) {
    ReplyParam p(a, b);
    WriteParam(reply, p);
  }

  template<typename TA, typename TB, typename TC>
  static void WriteReplyParams(PIpcMessage* reply, TA a, TB b, TC c) {
    ReplyParam p(a, b, c);
    WriteParam(reply, p);
  }

  template<typename TA, typename TB, typename TC, typename TD>
  static void WriteReplyParams(PIpcMessage* reply, TA a, TB b, TC c, TD d) {
    ReplyParam p(a, b, c, d);
    WriteParam(reply, p);
  }

  template<typename TA, typename TB, typename TC, typename TD, typename TE>
  static void WriteReplyParams(PIpcMessage* reply, TA a, TB b, TC c, TD d, TE e) {
    ReplyParam p(a, b, c, d, e);
    WriteParam(reply, p);
  }
};

#endif  // PIPCMESSAGEUTILS_H_
