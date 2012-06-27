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
#ifndef PSOFTPATH_H
#define PSOFTPATH_H

#include "PRect.h"
#include "PMatrix3D.h"

/// \addtogroup SoftBackend
///  @{



#if !defined(DOXYGEN) || (defined(DOXYGEN) && (DOXYGEN==1))
#define PPATH_NEW       0
#define PPATH_CLOSED    1
#define PPATH_TYPE      2
#define PPATH_COUNT     4
#endif

struct PStack;



/**
 *  Software path data iterator
**/
struct PSoftPathIterator {
    friend struct PSoftPath;

    inline  bool        IsEnd       (void);                     ///< Returns true if we are at the end of the path
    inline  bool        IsNewSub    (void);                     ///< Returns true if we are creating a new subpath
    inline  bool        IsClosed    (void);                     ///< Returns true if the subpath needs to be closed
    inline  unsigned    GetPathType (void);                     ///< Returns the type of curve that follows
    inline  unsigned    GetPathCount(void);                     ///< Returns the count of elements that follows
    inline  PVertex2D  *GetPoints   (void);                     ///< Returns the pointer to the elements
    inline  void        Next        (void);                     ///< Move to the next element

    PSoftPathIterator &operator=(const PSoftPathIterator &Iter);///< Assignment operator

private:
    unsigned *Data;                                             ///< Pointer to the path's data chunk
};



/**
 *  Software path structure
**/
#if defined(DOXYGEN) && (DOXYGEN==1)
/**
 *  <center><table border=1 cellspacing=0 align=center class="main">
 *  <tr><th>Field</th><th>Bits</th><th>Description
 *
 *  <tr><td>New</td><td>1</td><td>Specifies if the subpath begins a new subpath (or extends the previous one)
 *  <tr><td>Closed</td><td>1</td><td>Specifies wether the path should close the current subpath
 *  <tr><td>Type</td><td>4</td><td>Specifies the type of element this subpath specifies
 *  <tr><td>Count</td><td>26</td><td>Total number of elements in this subpath
 *  <tr><td>Next</td><td>32</td><td>Pointer to the next path element
 *  <tr><td>Data</td><td>...</td><td>List of PVertex2D</td></tr></table>
 *  </center>
**/
#endif
struct PEXPORT PSoftPath {
    friend struct PStroker;
    friend struct PSoftContext2D;

    inline bool IsEmpty     (void) const;                                                           ///< Tells wether or not the path is empty
    inline bool MoveTo      (PVertex2D *const Pt);                                                  ///< Creates a new subpath starting with an absolute 2D point
    inline bool LineTo      (PVertex2D *const Pt, const unsigned Num = 1);                          ///< Creates an absolute set of lines from the current position
    bool        BezierTo    (const unsigned Order, PVertex2D *const Pts, const unsigned Num = 1);   ///< Creates an absolute set of bezier from the current position
    bool        ArcTo       (PVertex2D EndPt, PVertex2D Center, PVertex2D Radii, bool CCW = false); ///< Creates an elliptical arc from the current position
    bool        ArcTo       (PVertex2D Radii, PValue Rotation, PVertex2D EndPt, bool LargeArc = false, bool CCW = false);  ///< Creates an elliptical arc from the current position
    inline bool Close       (void);                                                                 ///< Close a subpath

    void        Reset       (void);                                                                 ///< Resets the path to empty.
    void        Finalize    (void);                                                                 ///< Completes the path
    bool        Transform   (PSoftPath* Path, const PMatrix3D *const Matrix) const;                 ///< Transforms the path and appends the result to the given path
    unsigned    Flatten     (PVertex2D **&Dst, const PMatrix3D *const Transform, PStack* const Stack = NULL) const;        ///< Flattens a path into a set of vertices
    void        GetBBox     (PRect &BBox) const;                                                    ///< Retrieves the bouding box of the given path

    inline void SetQuality  (const PValue Quality = PValue(0.5f));                                  ///< Sets the tesselator quality

    inline void SetIterator (PSoftPathIterator *Iter) const;                                        ///< Initialize the path iterator

    PSoftPath &operator=(const PSoftPath &Path);                                                    ///< Assignment operator

protected:
    inline PSoftPath(const PSoftPath &Path);                                                        ///< Copy constructor

     PSoftPath();                                                                                   ///< Constructor
    ~PSoftPath();                                                                                   ///< Destructor

private:
    unsigned        TotSub;                                                                         ///< Total number of subpaths
    unsigned       *Data;                                                                           ///< Pointer to subpath data
    unsigned       *First;                                                                          ///< Pointer to the fisrt element in the current subpath
    unsigned       *Last;                                                                           ///< Pointer to the last subpath in the path
    PVertex2D       StartPt;                                                                        ///< Starting point of the next subpath
    bool            NewSub;                                                                         ///< True if we should create a new subpath next

    PValue          Quality;                                                                        ///< Quality of the tesselation
};



#include "PSoftPath.inl"

/// @}
#endif
