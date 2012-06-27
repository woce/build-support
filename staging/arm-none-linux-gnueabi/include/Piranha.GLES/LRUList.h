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

//#public
#ifndef LRULIST_H
#define LRULIST_H

#include "PCommon.h"



template<typename DataType> struct LRUList {
    struct Node {
        DataType   *Data;
        Node       *Prev;
        Node       *Next;
    } *Head, *Tail;



    LRUList() : Head(NULL), Tail(NULL)
    {
    }



    ~LRUList()
    {
        // Delete the nodes and the data content
        while (Head) {
            DataType *At = Remove();

            delete At;
        }
    }



    inline void Push(DataType *Data)
    {
        Node *N = new(Node);

        N->Data = Data;
        N->Prev = NULL;
        N->Next = Head;

        if (Head)
            Head->Prev = N;
        else
            Tail = N;

        Head = N;
    }



    inline DataType *Remove(void)
    {
        PASSERT(Tail, "Atempting to remove data when no more exists");

        DataType *Data  = Tail->Data;
        Node *Die       = Tail;

        if (Tail->Prev)
            Tail->Prev->Next = NULL;
        else
            Head = NULL;

        Tail = Tail->Prev;

        delete Die;

        return Data;
    }



    inline void Promote(Node *At)
    {
        if (At != Head) {
            At->Prev->Next  = At->Next;

            if (At->Next)
                At->Next->Prev = At->Prev;
            else
                Tail = At->Prev;

            At->Prev        = NULL;
            At->Next        = Head;
            Head->Prev      = At;
            Head            = At;
        }
    }
};

#endif /* LRULIST_H */
