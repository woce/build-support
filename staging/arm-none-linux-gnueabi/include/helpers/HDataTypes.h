//  @@@LICENSE
//
//      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  LICENSE@@@

#ifndef __HDATATYPES__
#define __HDATATYPES__

// this file is used by HDataWriter and HDataReader
#define HDATA_IDENT "Hdata"
const int HDATA_TYPE_BASE = 100000;
const int HDATA_TYPE_INT = HDATA_TYPE_BASE + 1;
const int HDATA_TYPE_CHAR = HDATA_TYPE_BASE + 2;
const int HDATA_TYPE_BOOL = HDATA_TYPE_BASE + 3;
const int HDATA_TYPE_DOUBLE = HDATA_TYPE_BASE + 4;
const int HDATA_TYPE_STR = HDATA_TYPE_BASE + 5;
const int HDATA_TYPE_DATA = HDATA_TYPE_BASE + 6;
const int HDATA_TYPE_ENDCAP = HDATA_TYPE_BASE + 7;

#endif