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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <unistd.h>

#include "HCommon.h"

struct HEXPORT HSocket
{
	int Fd;

	HSocket(int _Fd = -1)
		: Fd(_Fd)
	{
	}

	~HSocket()
	{
		Destroy();
	}

	void Destroy()
	{
		if (Fd != -1) {
			close(Fd);
		}
		Fd = -1;
	}

	void Shutdown()
	{
		if (Fd != -1) {
			if (shutdown(Fd, SHUT_RDWR) != 0) {
				HTRACE( "shutdown failed: %s\n", strerror(errno));
			}
		}
	}

	void Set(int Fd)
	{
		Destroy();
		this->Fd = Fd;
	}

	HSocket& operator=(const HSocket& Socket)
	{
		if (Fd != Socket.Fd) {
			Set(Socket.Fd);
		}
		return *this;
	}

	int GetFd()
	{
		return Fd;
	}

	bool Create()
	{
		if ((Fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
			HTRACE("socket failed: %s\n", strerror(errno));
			return false;
		}
		return true;
	}

	bool HasData(int WaitMs = 0)
	{
		fd_set FdSet;

		FD_ZERO(&FdSet);
		FD_SET(Fd, &FdSet);
		struct timeval tv;
		tv.tv_sec = WaitMs / 1000;
		tv.tv_usec = (WaitMs - tv.tv_sec * 1000) * 1000;

		// On Linux I believe the timeout will be updated on EINTR
		int rc;
		while ((rc = select(Fd+1, &FdSet, NULL, NULL, &tv)) == -1 && errno == EINTR)
			;

		HTRACE( "select returned %d\n", rc);
		return (rc > 0 && FD_ISSET(Fd, &FdSet));
	}

	bool Bind(const char* Path)
	{
		sockaddr_un local;
		int len;

		local.sun_family = AF_UNIX;
		strncpy(local.sun_path, Path, sizeof(local.sun_path) - 1);
		local.sun_path[sizeof(local.sun_path) - 1] = '0';
		unlink(local.sun_path);

		len = strlen(local.sun_path) + sizeof(local.sun_family);
		if (bind(Fd, (sockaddr*) &local, len) == -1) {
		    HTRACE("bind failed: %s\n", strerror(errno));
			return false;
		}
		return true;
	}

	bool Listen(int BackLog = 0)
	{
		if (listen(Fd, BackLog) == -1) {
		    HTRACE("listen failed: %s\n", strerror(errno));
			return false;
		}
		return true;
	}

	bool Accept(HSocket* Incoming)
	{
		int s;
		sockaddr_un remote;
		socklen_t t = sizeof(remote);

		if ((s = accept(Fd, (sockaddr*) &remote, &t)) == -1) {
		    HTRACE("accept failed: %s\n", strerror(errno));
			return false;
		}

		Incoming->Set(s);
		return true;
	}

	bool Connect(const char* Path)
	{
		sockaddr_un remote;
		int len;

		remote.sun_family = AF_UNIX;
		strncpy(remote.sun_path, Path, sizeof(remote.sun_path) - 1);
		remote.sun_path[sizeof(remote.sun_path) - 1] = '0';

		len = strlen(remote.sun_path) + sizeof(remote.sun_family);
		if (connect(Fd, (sockaddr*) &remote, len) == -1) {
		    HTRACE("connect failed: %s\n", strerror(errno));
			return false;
		}
		return true;
	}

	int SendMsg(msghdr* MsgHdr, int Flags = 0)
	{
		ssize_t size = sendmsg (Fd, MsgHdr, Flags);
		if (size < 0) {
		    HTRACE("sendmsg failed: %s\n", strerror(errno));
		}
		return size;
	}

	int Send(void* Buffer, int Length, int Flags = 0)
	{
		ssize_t size = send(Fd, Buffer, Length, Flags);
		if (size < 0) {
		    HTRACE("send failed: %s\n", strerror(errno));
		}
		return size;
	}

	int RecvMsg(msghdr* MsgHdr, int Flags = 0)
	{
		ssize_t size = recvmsg(Fd, MsgHdr, Flags);
		if (size < 0) {
		    HTRACE("recvmsg failed: %s\n", strerror(errno));
		}
		return size;
	}

	int Recv(void* Buffer, int Length, int Flags = 0)
	{
		ssize_t size = recv(Fd, Buffer, Length, Flags);
		if (size < 0) {
		    HTRACE("recv failed: %s\n", strerror(errno));
		}
		return size;
	}

protected:

};
