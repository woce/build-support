/**
 *  Copyright (c) 2009 - 2012 Hewlett-Packard Development Company, L.P.
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


#ifndef SYSMGRDEFS_H
#define SYSMGRDEFS_H

enum SysMgrOverlayNotificationPosition {
	SysMgrOverlayNotificationBottom = 0,
	SysMgrOverlayNotificationTop,
	SysMgrOverlayNotificationLeft,
	SysMgrOverlayNotificationRight,
	SysMgrOverlayNotificationLast = 0xFFFFFFFF
};

// The magic 0x0100 number is set to match Qt::CustomGesture
enum SysMgrGesture {
	SysMgrGestureFlick = 0x0100 + 1, // this is also defined in qnamespace.h since QTapGestureRecognizer needs to know about it.
	SysMgrGestureSingleClick,
	SysMgrGestureScreenEdgeFlick,
	SysMgrGestureLast = 0xFFFFFFFF
};

#endif /* SYSMGRDEFS_H */
