#pragma once
#include "..\..\CommonLibrary\include\net\packet.h"
#include "ProtocolBase.h"
#include "ProtocolDefine.h"
#include "coredefine.h"

class UserInfoUpdatePacket : public ServerPacket
{
public:
	UserInfoUpdatePacket(ByteBuf & buf, core::NotifyUserInfoUpdateEvent& _event)
		:ServerPacket(buf), stEvent(_event){}

	void Unpack();

private:
	core::NotifyUserInfoUpdateEvent& stEvent;
};