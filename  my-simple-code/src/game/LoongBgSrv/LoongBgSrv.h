
#ifndef GAME_LOONGBGSRV_H_
#define GAME_LOONGBGSRV_H_

#include <mysdk/base/Common.h>
#include <mysdk/base/Timestamp.h>
#include <mysdk/base/Thread.h>
#include <mysdk/base/BlockingQueue.h>

#include <mysdk/net/EventLoop.h>
#include <mysdk/net/InetAddress.h>
#include <mysdk/net/TcpServer.h>
#include <mysdk/net/TcpConnection.h>

#include <mysdk/protocol/kabu/codec/KaBuCodec.h>

#include <game/LoongBgSrv/BattlegroundMgr.h>

#include <map>

using namespace mysdk;
using namespace mysdk::net;

struct ThreadParam
{
	int32 bgId;
};

// 龙族对抗战场服务器
class BgPlayer;
class LoongBgSrv
{
public:
	typedef std::map<int32, BgPlayer*> BgPlayerMapT;
public:
	LoongBgSrv(EventLoop* loop, InetAddress& serverAddr);
	~LoongBgSrv();

public:
	void start();
	void stop();

	void onConnectionCallback(mysdk::net::TcpConnection* pCon);
	void onKaBuMessage(mysdk::net::TcpConnection* pCon, PacketBase& pb, Timestamp timestamp);

	void send(mysdk::net::TcpConnection* pCon, PacketBase& pb);

	BattlegroundMgr& getBgMgr()
	{
		return battlegroundMgr_;
	}
private:
	bool login(mysdk::net::TcpConnection* pCon, PacketBase& pb, Timestamp timestamp);
	void tickMe();
	bool hasBgPlayer(int32 playerId);
	void phpThreadHandler();
private:
	KaBuCodec codec_;
	BgPlayerMapT bgPlayerMap_;
	Thread phpThread_;
	BattlegroundMgr battlegroundMgr_;

	EventLoop* loop_;
	TcpServer server_;
public:
	BlockingQueue<ThreadParam> queue_;
private:
	DISALLOW_COPY_AND_ASSIGN(LoongBgSrv);
};

#endif /* LOONGBGSRV_H_ */
