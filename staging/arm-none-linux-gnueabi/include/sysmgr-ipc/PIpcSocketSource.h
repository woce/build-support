/**
 *  Copyright (c) 2009-2012 Hewlett-Packard Development Company, L.P.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


#ifndef PIPCSOCKETSOURCE_H
#define PIPCSOCKETSOURCE_H

#include <glib.h>

struct PIpcSocketSource;
typedef gboolean (*PIpcSocketSourceCallback)(PIpcSocketSource* src,
											 GIOCondition condition,
											 gpointer userData);

PIpcSocketSource* PIpcSocketSourceCreate(int socketFd, GIOCondition condition,
										 PIpcSocketSourceCallback callback,
										 gpointer userData);

void PIpcSocketSourceSetCondition(PIpcSocketSource* src, GIOCondition condition);

#endif /* PIPCSOCKETSOURCE_H */
