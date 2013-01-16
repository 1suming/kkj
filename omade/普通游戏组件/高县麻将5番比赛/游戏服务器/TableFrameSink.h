#ifndef TABLE_FRAME_SINK_HEAD_FILE
#define TABLE_FRAME_SINK_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameLogic.h"

//////////////////////////////////////////////////////////////////////////
//枚举定义

//效验类型
enum enEstimatKind
{
	EstimatKind_OutCard,			//出牌效验
	EstimatKind_PengGangCard,		//杠牌效验
 
	EstimatKind_TICard,             //提牌校验
	EstimatKind_TIECard,            //贴牌校验
	EstimatKind_PENGCard,           //碰牌校验
};

//杠牌得分
struct tagGangScore
{
	BYTE		cbGangCount;							//杠个数
	LONG		lScore[MAX_WEAVE][GAME_PLAYER];			//每个杠得分
};


//////////////////////////////////////////////////////////////////////////

//游戏桌子类
class CTableFrameSink : public ITableFrameSink, public ITableUserAction
{
	//游戏变量
protected:
	LONG							m_lSiceCount;							//骰子点数
	WORD							m_wBankerUser;							//庄家用户
	LONG							m_lGameScore[GAME_PLAYER];				//游戏得分
	BYTE							m_cbCardIndex[GAME_PLAYER][MAX_INDEX];	//用户扑克
	bool							m_bTrustee[GAME_PLAYER];				//是否托管
	BYTE							m_cbGenCount[GAME_PLAYER];				//根数量
	bool							m_bPlayStatus[GAME_PLAYER];				//玩牌状态
	BYTE							m_cbWinCount;							//赢家数目
	WORD							m_wWinOrder[GAME_PLAYER];				//赢家排名
	LONG							m_lGameTax[GAME_PLAYER];				//抽税分数
	tagGangScore					m_GangScore[GAME_PLAYER];				//杠 分数

	WORD							m_wLostFanShu[GAME_PLAYER][GAME_PLAYER];//输分数目

	//出牌信息
protected:
	WORD							m_wOutCardUser;							//出牌用户
	BYTE							m_cbOutCardData;						//出牌扑克
	BYTE							m_cbOutCardCount;						//出牌数目
	BYTE							m_cbDiscardCount[GAME_PLAYER];			//丢弃数目
	BYTE							m_cbDiscardCard[GAME_PLAYER][55];		//丢弃记录

	//发牌信息
protected:
	BYTE							m_cbSendCardData;						//发牌扑克
	BYTE							m_cbSendCardCount;						//发牌数目
	BYTE							m_cbLeftCardCount;						//剩余数目
	BYTE							m_cbRepertoryCard[MAX_REPERTORY];		//库存扑克

	//堆立变量
protected:
	WORD							m_wHeapHand;							//堆立头部
	WORD							m_wHeapTail;							//堆立尾部
	BYTE							m_cbHeapCardInfo[4][2];					//堆牌信息

	//运行变量
protected:
	WORD							m_wResumeUser;							//还原用户
	WORD							m_wCurrentUser;							//当前用户
	WORD							m_wProvideUser;							//供应用户
	BYTE							m_cbProvideCard;						//供应扑克

	//状态变量
protected:
	bool							m_bSendStatus;							//发牌状态
	bool							m_bGangStatus;							//抢杆状态
	bool							m_bTIStatus;							//抢提状态
	bool							m_bGangOutStatus;						//杠上炮状态
	bool							m_bEnjoinChiHu[GAME_PLAYER];			//禁止吃胡
	bool							m_bEnjoinChiPeng[GAME_PLAYER];			//禁止吃碰

	//用户状态
public:
	bool							m_bResponse[GAME_PLAYER];				//响应标志
	BYTE							m_cbUserAction[GAME_PLAYER];			//用户动作
	BYTE							m_cbOperateCard[GAME_PLAYER];			//操作扑克
	BYTE							m_cbPerformAction[GAME_PLAYER];			//执行动作
	//组合扑克
protected:
	BYTE							m_cbWeaveItemCount[GAME_PLAYER];		//组合数目
	tagWeaveItem					m_WeaveItemArray[GAME_PLAYER][MAX_WEAVE];//组合扑克

	//结束信息
protected:
	BYTE							m_cbChiHuCard;							//吃胡扑克
	DWORD							m_dwChiHuKind[GAME_PLAYER];				//吃胡结果
	CChiHuRight						m_ChiHuRight[GAME_PLAYER];				//
	WORD							m_wProvider[GAME_PLAYER];				//
 
	bool							m_bOutMagicCard[GAME_PLAYER];           // 打出听用标志
	bool							m_bKaiJu;                               // 开局标志 
	bool							m_bPlayleft[GAME_PLAYER];				// 逃跑玩家
 
//组件变量
protected:
	CGameLogic						m_GameLogic;							//游戏逻辑
	ITableFrame						* m_pITableFrame;						//框架接口
	const tagGameServiceOption		* m_pGameServiceOption;					//配置参数

	//属性变量
protected:
	static const WORD				m_wPlayerCount;							//游戏人数
	static const enStartMode		m_GameStartMode;						//开始模式

	//函数定义
public:
	//构造函数
	CTableFrameSink();
	//析构函数
	virtual ~CTableFrameSink();

	//基础接口
public:
	//释放对象
	virtual VOID __cdecl Release() { }
	//是否有效
	//virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CTableFrameSink))?true:false; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//管理接口
public:
	//初始化
	virtual bool __cdecl InitTableFrameSink(IUnknownEx * pIUnknownEx);
	//复位桌子
	virtual void __cdecl RepositTableFrameSink();

	//信息接口
public:
	//开始模式
	virtual enStartMode __cdecl GetGameStartMode();
	//游戏状态
	virtual bool __cdecl IsUserPlaying(WORD wChairID);

	//游戏事件
public:
	//游戏开始
	virtual bool __cdecl OnEventGameStart();
	//游戏结束
	virtual bool __cdecl OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason);
	//发送场景
	virtual bool __cdecl SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret);

	//事件接口
public:
	//定时器事件
	virtual bool __cdecl OnTimerMessage(WORD wTimerID, WPARAM wBindParam);
	//游戏消息处理
	virtual bool __cdecl OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);
	//框架消息处理
	virtual bool __cdecl OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem);

	//用户事件
public:
	//用户断线
	virtual bool __cdecl OnActionUserOffLine(WORD wChairID,IServerUserItem * pIServerUserItem) { return true; }
	//用户重入
	virtual bool __cdecl OnActionUserReConnect(WORD wChairID,IServerUserItem * pIServerUserItem) { return true; }
	//用户坐下
	virtual bool __cdecl OnActionUserSitDown(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户起立
	virtual bool __cdecl OnActionUserStandUp(WORD wChairID,IServerUserItem * pIServerUserItem, bool bLookonUser);
	//用户同意
	virtual bool __cdecl OnActionUserReady(WORD wChairID,IServerUserItem * pIServerUserItem, void * pData, WORD wDataSize) { return true; }


	//游戏事件
protected:
	//用户出牌
	bool OnUserOutCard(WORD wChairID, BYTE cbCardData);
	//用户操作
	bool OnUserOperateCard(WORD wChairID, BYTE cbOperateCode, BYTE cbOperateCard);

	//辅助函数
protected:
	//发送操作
	bool SendOperateNotify();
	//派发扑克
	bool DispatchCardData(WORD wCurrentUser,bool bTail=false);
	//响应判断
	bool EstimateUserRespond(WORD wCenterUser, BYTE cbCenterCard, enEstimatKind EstimatKind);
	// 提牌校验
	bool EstimateTICardRespond(WORD wCenterUser,BYTE cbCenterCard);//// cbCenterCard 提回的听用为当前牌
	// 贴牌校验
	bool EstimatePengTieCardRespond(WORD wCenterUser);

	// 处理吃胡用户
	void ProcessChiHuUser( WORD wChairId, bool bGiveUp );
	// 牌权过滤
	void FiltrateRight( WORD wChairId,CChiHuRight &chr );
 
};

//////////////////////////////////////////////////////////////////////////

#endif
