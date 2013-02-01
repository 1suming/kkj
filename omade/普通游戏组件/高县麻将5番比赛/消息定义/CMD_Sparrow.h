#ifndef CMD_SPARROW_HEAD_FILE
#define CMD_SPARROW_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//公共宏定义

#define KIND_ID						3326								//游戏 I D // 5FAN SCORE MATCH

#define GAME_PLAYER					4									//游戏人数
#define GAME_NAME					TEXT("高县麻将")					//游戏名字
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD|GAME_GENRE_LONGMATCH)	//游戏类型

//游戏状态
#define GS_MJ_FREE					GS_FREE								//空闲状态
#define GS_MJ_PLAY					(GS_PLAYING+1)						//游戏状态

//常量定义
#define MAX_WEAVE					4									//最大组合
#define MAX_INDEX					34									//最大索引
#define MAX_COUNT					14									//最大数目
#define MAX_REPERTORY				108									//最大库存

// 最大番数和得分 
// 番数 N 最大番得分倍数为 2^(N-1);
// 一番                     2^(1-1) = 1;
// 最大4番 得分是 8倍基数分 2^(4-1) = 8;
// 最大5番 得分是 16倍基数分 2^(5-1) = 16;

// 设置牌局最大番数   
// OMA 在游戏房间中设置参数
//#define MAX_CHIHU_FANSU				5									//最大胡牌番数


//扑克定义
#define HEAP_FULL_COUNT				26									//堆立全牌

#define MAX_RIGHT_COUNT				1									//最大权位DWORD个数			
#define START_GRANT_SCORE_BASE      2000                               // 低于2000分，开始送分
#define GRANT_SCORE_VALUE           2500								// 每次送2500分

//////////////////////////////////////////////////////////////////////////

//组合子项
struct CMD_WeaveItem
{
	BYTE							cbWeaveKind;						//组合类型
	BYTE							cbCenterCard;						//中心扑克
	BYTE							cbPublicCard;						//公开标志
	WORD							wProvideUser;						//供应用户

};

//////////////////////////////////////////////////////////////////////////
//服务器命令结构

#define SUB_S_GAME_START			100									//游戏开始
#define SUB_S_OUT_CARD				101									//出牌命令
#define SUB_S_SEND_CARD				102									//发送扑克
#define SUB_S_OPERATE_NOTIFY		104									//操作提示
#define SUB_S_OPERATE_RESULT		105									//操作命令
#define SUB_S_GAME_END				106									//游戏结束
#define SUB_S_TRUSTEE				107									//用户托管
#define SUB_S_CHI_HU				108									//吃胡
#define SUB_S_GANG_SCORE			110									//杠分
#define SUB_S_USER_ESCAPE          111                                 //用户逃跑
#define SUB_S_GRANT_SCORE           112                                 //送分

//游戏状态
struct CMD_S_StatusFree
{
	LONG							lCellScore;							//基础分数
	LONG							lMaxScoreTimes;                     //最大倍数
	WORD							wBankerUser;						//庄家用户
	bool							bTrustee[GAME_PLAYER];				//是否托管
};

 
//游戏状态
struct CMD_S_StatusPlay
{
	//游戏变量
	LONG							lCellScore;									//单元积分
	LONG							lMaxScoreTimes;								//最大倍数
	WORD							wBankerUser;								//庄家用户
	WORD							wCurrentUser;								//当前用户

	//状态变量
	BYTE							cbActionCard;								//动作扑克
	BYTE							cbActionMask;								//动作掩码
	BYTE							cbLeftCardCount;							//剩余数目
	bool							bTrustee[GAME_PLAYER];						//是否托管
	WORD							wWinOrder[GAME_PLAYER];						//

	//出牌信息
	WORD							wOutCardUser;								//出牌用户
	BYTE							cbOutCardData;								//出牌扑克
	BYTE							cbDiscardCount[GAME_PLAYER];				//丢弃数目
	BYTE							cbDiscardCard[GAME_PLAYER][55];				//丢弃记录

	//扑克数据
	BYTE							cbCardCount;								//扑克数目
	BYTE							cbCardData[MAX_COUNT];						//扑克列表
	BYTE							cbSendCardData;								//发送扑克

	//组合扑克
	BYTE							cbWeaveCount[GAME_PLAYER];					//组合数目

	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//组合扑克
	

	//堆立信息
	WORD							wHeapHand;									//堆立头部
	WORD							wHeapTail;									//堆立尾部
	BYTE							cbHeapCardInfo[GAME_PLAYER][2];				//堆牌信息
	BYTE							cbPaiJing;                                  // 牌精 
 
};

//游戏开始
struct CMD_S_GameStart
{
	LONG							lSiceCount;									//骰子点数
	WORD							wBankerUser;								//庄家用户
	WORD							wCurrentUser;								//当前用户
	BYTE							cbUserAction;								//用户动作
	BYTE							cbCardData[MAX_COUNT];						//扑克列表
	WORD							wHeapHand;									//堆立牌头
	WORD							wHeapTail;									//堆立牌尾
	BYTE							cbHeapCardInfo[GAME_PLAYER][2];				//堆立信息
	BYTE							cbLeftCardCount;							//
	BYTE							cbPaiJing;									// 牌精 //OMA
	bool 							bKaiJu;										// 新开局标志

};

//出牌命令
struct CMD_S_OutCard
{
	WORD							wOutCardUser;						//出牌用户
	BYTE							cbOutCardData;						//出牌扑克
};


//提牌结果
struct tagTICardResult
{
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[4];						//扑克数据
};



//杠牌结果
struct tagGangCardResult
{
	BYTE							cbCardCount;						//扑克数目
	BYTE							cbCardData[4];						//扑克数据
};


//发送扑克
struct CMD_S_SendCard
{
	bool							bTail;								//末尾发牌
	WORD							wCurrentUser;						//当前用户
	BYTE							cbCardData;							//扑克数据
 	BYTE							cbActionMask;						//动作掩码
};


//操作提示
struct CMD_S_OperateNotify
{
	WORD							wResumeUser;						//还原用户
	BYTE							cbActionMask;						//动作掩码
	BYTE							cbActionCard;						//动作扑克
};

//操作命令
struct CMD_S_OperateResult
{
	WORD							wOperateUser;						//操作用户
	WORD							wProvideUser;						//供应用户
	BYTE							cbOperateCode;						//操作代码
	BYTE							cbOperateCard;						//操作扑克
};

//游戏结束
struct CMD_S_GameEnd
{
	BYTE							cbCardCount[GAME_PLAYER];			//
	BYTE							cbCardData[GAME_PLAYER][MAX_COUNT];	//
	//结束信息
	WORD							wProvideUser[GAME_PLAYER];			//供应用户
	DWORD							dwChiHuRight[GAME_PLAYER];			//胡牌类型

	//积分信息
	LONG							lGameScore[GAME_PLAYER];			//游戏积分
	LONG							lGameTax[GAME_PLAYER];				//
	WORD							wWinOrder[GAME_PLAYER];				//胡牌排名
	LONG							lGangScore[GAME_PLAYER];			//详细得分
	WORD							wLostFanShu[GAME_PLAYER][GAME_PLAYER];
	WORD							wLeftUser;							//逃跑用户//OMA血战可以有多个逃跑玩家

	LONG							lHuaZhuScore[GAME_PLAYER];			//花猪分
	LONG							lChaJiaoScore[GAME_PLAYER];			//查叫分
	bool							bPlayleft[GAME_PLAYER];				//逃跑用户// OMA 记录逃跑玩家


};

//用户托管
struct CMD_S_Trustee
{
	bool							bTrustee;							//是否托管
	WORD							wChairID;							//托管用户
};
  
//  吃胡结果
struct CMD_S_ChiHu
{
	WORD							wChiHuUser;							// 吃胡用户
	WORD							wProviderUser;						// 供应用户
	BYTE							cbChiHuCard;						// 吃胡牌
	BYTE							cbCardCount;						// 胡牌时手上牌数量
	LONG							lGameScore;							// 胡牌得分
	BYTE							cbWinOrder;							// 胡牌排名

	bool							bGangStatus;                        // 抢杠标志
	bool							bTIStatus ;							// 提牌状态


};

//
struct CMD_S_GangScore
{
	WORD							wChairId;							//
	BYTE							cbXiaYu;							//
	LONG							lGangScore[GAME_PLAYER];			//
};


//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_OUT_CARD				1									//出牌命令
#define SUB_C_OPERATE_CARD			3									//操作扑克
#define SUB_C_TRUSTEE				4									//用户托管

//出牌命令
struct CMD_C_OutCard
{
	BYTE							cbCardData;							//扑克数据
};

//操作命令
struct CMD_C_OperateCard
{
	BYTE							cbOperateCode;						//操作代码
	BYTE							cbOperateCard;						//操作扑克
};

//用户托管
struct CMD_C_Trustee
{
	bool							bTrustee;							//是否托管	
};
//////////////////////////////////////////////////////////////////////////

#endif
