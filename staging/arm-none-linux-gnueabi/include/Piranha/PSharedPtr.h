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
#ifndef PSHAREDPTR_H_
#define PSHAREDPTR_H_

#include <string.h>
#include "PCommon.h"

template<typename T>
struct PSPDefaultManager
{
    struct Item
    {
        int RefCount;
        T   Data;

        Item(const T& _Data) :
            RefCount(1),
            Data(_Data)
            {}

        Item() :
            RefCount(1)
            {}
    };

    inline static void* Alloc(const T* const Data = NULL)
    {
        if (Data) {
            return new Item(*Data);
        }
        else {
            return new Item;
        }
    }

    inline static void IncRef(void* Ptr)
    {
        ((Item*)Ptr)->RefCount++;
    }
    inline static void DecRef(void* Ptr)
    {
        Item* ItemPtr = (Item*)Ptr;
        PASSERT(ItemPtr->RefCount > 0, "Bad ref count: %d\n", ItemPtr->RefCount);

        if (0 == --ItemPtr->RefCount) {
            delete ItemPtr;
        }
    }
    inline static T* GetTypedPtr(void* Ptr)
    {
        return &((Item*)Ptr)->Data;
    }
    inline static int Count(void* Ptr)
    {
        return ((Item*)Ptr)->RefCount;
    }
};

struct PSPStringManager
{
    inline static void* Alloc(const char* String)
    {
        int size = sizeof(int) + strlen(String) + 1;
        size = PALIGN(size, 4);

        void* Ptr = malloc(size);

        // Initialize reference count
        *(int*)Ptr = 1;

        // Copy string data
        strcpy(GetTypedPtr(Ptr), String);

        return Ptr;
    }
    inline static void IncRef(void* Ptr)
    {
        int* Count = (int*)Ptr;
        (*Count)++;
    }
    inline static void DecRef(void* Ptr)
    {
        int* Count = (int*)Ptr;
        (*Count)--;

        if (*Count == 0) {
            PTRACE( "PSPStringManager freeing '%s'\n", GetTypedPtr(Ptr));
            free(Ptr);
        }
    }
    inline static char* GetTypedPtr(void* Ptr)
    {
        return (char*)Ptr + sizeof(int);
    }
    inline static int Count(void* Ptr)
    {
        return *(int*)Ptr;
    }
};

template<typename T, typename TManager = PSPDefaultManager<T> >
struct PSharedPtr
{
    inline PSharedPtr() :
        Ptr(NULL)
    {
        // We must be exactly the size of a void* to allow for "hiding" of this type
        PCOMPILE_TIME_ASSERT(sizeof(*this)==sizeof(void*));
    }

    inline PSharedPtr(const T& Data)
    {
        Ptr = TManager::Alloc(Data);
    }

    inline PSharedPtr(const T* const Data)
    {
        Ptr = TManager::Alloc(Data);
    }

    inline void Copy(const T* const Data)
    {
        Release();
        Ptr = TManager::Alloc(Data);
    }

    inline void Copy(const T& Data)
    {
        Release();
        Ptr = TManager::Alloc(&Data);
    }

    inline void Create()
    {
        Ptr = TManager::Alloc();
    }

    inline ~PSharedPtr()
    {
        Release();
    }

    inline PSharedPtr& operator=(const PSharedPtr<T, TManager>& P)
    {
        Release();
        Ptr = P.Ptr;
        Attach();
        return *this;
    }

    inline PSharedPtr(const PSharedPtr<T, TManager>& P) :
        Ptr(P.Ptr)
    {
        Attach();
    }

    inline operator T* ()
    {
        return TManager::GetTypedPtr(Ptr);
    }

    inline bool operator==(const PSharedPtr<T, TManager>& P)
    {
        return Ptr == P.Ptr;
    }

    inline bool IsNull()
    {
        return Ptr == NULL;
    }

    inline int Count()
    {
        return TManager::Count(Ptr);
    }

    inline void Release()
    {
        if (Ptr != NULL) {
            TManager::DecRef(Ptr);
            Ptr = NULL;
        }
    }
protected:
    void* Ptr;

    inline void Attach()
    {
        if (Ptr != NULL) {
            TManager::IncRef(Ptr);
        }
    }
};

typedef PSharedPtr<char, PSPStringManager> PSharedString;

#endif /*PSHAREDPTR_H_*/
