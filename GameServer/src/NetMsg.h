/******************************************************************************************
  Copyright 2013 Christian Roggia

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************************/

#ifndef NETMSG_H
#define NETMSG_H

#include "Global.h"
#include "MemPool.h"
#include "Utils.h"

#include <netinet/in.h>
#include <sys/socket.h>

/***********************************
TODO: CNetMsg::`vtbl'
************************************/

class CNetMsg;

class CNetMsg {
public:
    char MsgType;           // +0
    unsigned char *MsgData; // +4
    int  MsgPointer;        // +8
    int  MsgLength;         // +12
public:
    CNetMsg(void);
    CNetMsg(CNetMsg const &net_msg);
    CNetMsg(__tagMessageType);
    ~CNetMsg();

    void Init(void);
    void Init(CNetMsg const &);
    void Init(__tagMessageType);
    void Read(void *dest, int len);
    void Write(void *src, int len);
    void WriteRaw(void *write, int len);

    bool CanRead(long len)              { return this->MsgPointer <= this->MsgLength - len; }
    bool CanWrite(long len)             { return this->MsgPointer <= 1000 - len; }
    void MoveFirst(void)                { this->MsgPointer = 1; }
    void __rs(char *dest);
    void __ls(char const *src);

    /* FROM UTILS.CPP */

    void __as(CNetMsg const &net_msg)   { this->Init(net_msg); }

    void __rs(float &dest)              { this->Read(&dest, 4); }
    void __rs(double &dest)             { this->Read(&dest, 8); }
    void __rs(unsigned long long &dest) { this->Read(&dest, 8); } // dest = ntohll(dest);
    void __rs(long long &dest)          { this->Read(&dest, 8); } // dest = ntohll(dest);
    void __rs(unsigned long &dest)      { this->Read(&dest, 4); dest = ntohl(dest); }
    void __rs(long &dest)               { this->Read(&dest, 4); dest = ntohl(dest); }
    void __rs(unsigned int &dest)       { this->Read(&dest, 4); dest = ntohl(dest); }
    void __rs(int &dest)                { this->Read(&dest, 4); dest = ntohl(dest); }
    void __rs(unsigned short &dest)     { this->Read(&dest, 2); dest = ntohs(dest); }
    void __rs(short &dest)              { this->Read(&dest, 2); dest = ntohs(dest); }
    void __rs(unsigned char &dest)      { this->Read(&dest, 1); }
    void __rs(char &dest)               { this->Read(&dest, 1); }

    void __ls(float src)                { this->Write(&src, 4); }
    void __ls(double src)               { this->Write(&src, 8); }
    void __ls(unsigned long long src)   { this->Write(&src, 8); } // src = htonll(src);
    void __ls(long long src)            { this->Write(&src, 8); } // src = htonll(src);
    void __ls(unsigned long src)        { src = htonl(src); this->Write(&src, 4); }
    void __ls(long src)                 { src = htonl(src); this->Write(&src, 4); }
    void __ls(unsigned int src)         { src = htonl(src); this->Write(&src, 4); }
    void __ls(int src)                  { src = htonl(src); this->Write(&src, 4); }
    void __ls(unsigned short src)       { src = htons(src); this->Write(&src, 2); }
    void __ls(short src)                { src = htons(src); this->Write(&src, 2); }
    void __ls(unsigned char src)        { this->Write(&src, 1); }
    void __ls(char src)                 { this->Write(&src, 1); }
};

extern CMemPool<unsigned char, 1000> g_netmsgpool;

#endif
