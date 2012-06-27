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
#ifndef PARRAY_H_
#define PARRAY_H_


template<class T>
struct PArray
{
    PArray() :
        NumElem(0),
        Elem(NULL)
    {
    }

    PArray(T* Elem, unsigned int NumElem) :
        NumElem(0),
        Elem(NULL)
    {
        Set(Elem, NumElem);
    }

    ~PArray()
    {
        Dealloc();
    }

    void Dealloc()
    {
        if (Elem) {
            PDELETEA(Elem);
        }
        this->NumElem = 0;
    }

    unsigned int Length() const
    {
        return NumElem;
    }

    void Set(T* Elem, unsigned int NumElem)
    {
        Dealloc();

        this->NumElem = NumElem;
        if (this->NumElem > 0) {
            this->Elem = new T[NumElem];
        }

        for(unsigned int i = 0; i < NumElem; i++) {
            this->Elem[i] = Elem[i];
        }
    }

    PArray<T>& operator=(const PArray<T>& Array)
    {
        if (&Array != this) {
            Set(Array.Elem, Array.NumElem);
        }
        return *this;
    }

    bool operator==(const PArray<T>& Array) const
    {
        if (NumElem == Array.NumElem) {
            for (unsigned int i = 0; i < NumElem; i++) {
                if (!(Elem[i] == Array.Elem[i])) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    T& operator[](unsigned int Index)
    {
        PASSERT(Index < NumElem, "Bad array index %d (NumElem %d)", Index, NumElem);
        PASSERT(Elem != NULL, "NULL array dereference (index %d)\n", Index);
        return Elem[Index];
    }

    const T& operator[](unsigned int Index) const
    {
        PASSERT(Index < NumElem, "Bad array index %d (NumElem %d)", Index, NumElem);
        PASSERT(Elem != NULL, "NULL array dereference (index %d)\n", Index);
        return Elem[Index];
    }

protected:
    PArray(const PArray&);

protected:
    unsigned int NumElem;
    T*  Elem;
};

#endif /*PARRAY_H_*/
