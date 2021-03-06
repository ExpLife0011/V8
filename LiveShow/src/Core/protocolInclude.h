#pragma once

#include "protocol/Login.h"
#include "protocol/GetSelfInfo.h"
#include "protocol/SetSelfInfo.h"
#include "protocol/EnterRoom.h"
#include "protocol/userlist/GetUserList.h"
#include "protocol/userlist/GetWaittingList.h"
#include "protocol/SendGift.h"
#include "protocol/SendMessage.h"
#include "protocol/SendLoudSpeaker.h"
#include "protocol/LeaveRoom.h"
#include "protocol/show/RequestShow.h"
#include "protocol/show/ExitShow.h"
#include "protocol/show/OperateAV.h"
#include "protocol/show/PushOnShow.h"
#include "protocol/show/PullOffShow.h"
#include "protocol/show/OpenPrivate.h"
#include "protocol/show/ClosePrivate.h"
#include "protocol/show/RequestP2P.h"
#include "protocol/show/ResponseP2P.h"
#include "protocol/show/NotifyPrivateShow.h"
#include "protocol/show/PushOnShowAnswer.h"
#include "protocol/show/SetMicStatus.h"
#include "protocol/manage/KickUser.h"
#include "protocol/manage/LockIP.h"
#include "protocol/manage/ShutUp.h"
#include "protocol/manage/UnShutUp.h"
#include "protocol/manage/AddTitle.h"
#include "protocol/manage/RemoveTitle.h"
#include "protocol/manage/AddBlack.h"
#include "protocol/manage/NotifyRoomLocked.h"
#include "protocol/manage/OfficialNotice.h"
#include "protocol/ReportClientInfo.h"
#include "protocol/QueryClientInfo.h"
#include "protocol/SetRoomInfo.h"
#include "protocol/GetRoomInfo.h"
#include "protocol/SystemMessage.h"
#include "protocol/UserInfoUpdate.h"
#include "protocol/GiftOverTime.h"
#include "protocol/NotifyMoneyUpdate.h"
#include "protocol/NotifyPlutusAward.h"
#include "protocol/SendFlyWords.h"
#include "protocol/NotifyMediaServerReset.h"
#include "protocol/NotifyMyInfoUpdate.h"
#include "protocol/NotifyGiftStar.h"
#include "protocol/NotifyMyGoods.h"
#include "protocol/NotifyRichStar.h"
#include "protocol/ReportCollectInfo.h"
#include "protocol/Task.h"
#include "protocol/Fans.h"
#include "protocol/sofa/SofaList.h"
#include "protocol/sofa/BuySofa.h"
#include "protocol/song/UpdateSonglist.h"
#include "protocol/song/GetSonglist.h"
#include "protocol/song/OrderSong.h"
#include "protocol/song/ProcessOrder.h"
#include "protocol/song/GetOrderlist.h"
#include "protocol/box/boxkeyNotify.h"
#include "protocol/box/openBox.h"
#include "protocol/getOfflineActor.h"
#include "protocol/markSong.h"