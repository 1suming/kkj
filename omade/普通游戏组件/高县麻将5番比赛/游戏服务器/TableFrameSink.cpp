#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//静态变量
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;			//游戏人数
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_FullReady;	//开始模式

//////////////////////////////////////////////////////////////////////////

//构造函数
CTableFrameSink::CTableFrameSink()
{
	//游戏变量
	m_lSiceCount=0;
	m_wBankerUser=INVALID_CHAIR;
	ZeroMemory(m_cbCardIndex,sizeof(m_cbCardIndex));
	ZeroMemory(m_bTrustee,sizeof(m_bTrustee));
	ZeroMemory( m_GangScore,sizeof(m_GangScore) );
	ZeroMemory( m_cbGenCount,sizeof(m_cbGenCount) );
	ZeroMemory( m_bPlayStatus,sizeof(m_bPlayStatus) );
	ZeroMemory( m_lGameScore,sizeof(m_lGameScore) );
	m_cbWinCount = 0;
	memset( m_wWinOrder,INVALID_CHAIR,sizeof(m_wWinOrder) );
	ZeroMemory( m_lGameTax,sizeof(m_lGameTax) );
	ZeroMemory( m_wLostFanShu,sizeof(m_wLostFanShu) );
	ZeroMemory( m_bHuaZhu,sizeof(m_bHuaZhu) );
	ZeroMemory( m_bWuJiao,sizeof(m_bWuJiao) );

 
	//出牌信息
	m_cbOutCardData=0;
	m_cbOutCardCount=0;
	m_wOutCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbDiscardCard,sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount,sizeof(m_cbDiscardCount));

	//堆立信息
	m_wHeapHand = INVALID_CHAIR;
	m_wHeapTail = INVALID_CHAIR;
	ZeroMemory(m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));

	//发牌信息
	m_cbSendCardData=0;
	m_cbSendCardCount=0;
	m_cbLeftCardCount=0;
	ZeroMemory(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));

	//运行变量
	m_cbProvideCard=0;
	m_wResumeUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	m_wProvideUser=INVALID_CHAIR;

	//状态变量
	m_bSendStatus=false;
	m_bGangStatus = false;
	m_bGangOutStatus = false;
	ZeroMemory(m_bEnjoinChiHu,sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng,sizeof(m_bEnjoinChiPeng));

	//用户状态
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

	//组合扑克
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));
	ZeroMemory(m_cbWeaveItemCount,sizeof(m_cbWeaveItemCount));

	//结束信息
	m_cbChiHuCard=0;
	ZeroMemory( m_dwChiHuKind,sizeof(m_dwChiHuKind) );
	memset( m_wProvider,INVALID_CHAIR,sizeof(m_wProvider) );

	//组件变量
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;

	//开局标志
	m_bKaiJu = true;
 	return;
}

//析构函数
CTableFrameSink::~CTableFrameSink(void)
{
}

//接口查询
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//初始化
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//查询接口
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL)
		return false;

	//获取参数
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	//OMA 初始化游戏逻辑
	m_GameLogic.SetMaxScoreTimes(m_pGameServiceOption->lMaxScoreTimes);

	return true;
}

//复位桌子
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//游戏变量
	m_lSiceCount=0;
	ZeroMemory(m_cbCardIndex,sizeof(m_cbCardIndex));
	ZeroMemory(m_bTrustee,sizeof(m_bTrustee));
	ZeroMemory( m_GangScore,sizeof(m_GangScore) );
	ZeroMemory( m_cbGenCount,sizeof(m_cbGenCount) );
	ZeroMemory( m_lGameScore,sizeof(m_lGameScore) );
	ZeroMemory( m_bPlayStatus,sizeof(m_bPlayStatus) );
	m_cbWinCount = 0;
	memset( m_wWinOrder,INVALID_CHAIR,sizeof(m_wWinOrder) );
	ZeroMemory( m_lGameTax,sizeof(m_lGameTax) );
	ZeroMemory( m_wLostFanShu,sizeof(m_wLostFanShu) );

	ZeroMemory( m_bHuaZhu,sizeof(m_bHuaZhu) );
	ZeroMemory( m_bWuJiao,sizeof(m_bWuJiao) );

	//出牌信息
	m_cbOutCardData=0;
	m_cbOutCardCount=0;
	m_wOutCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbDiscardCard,sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount,sizeof(m_cbDiscardCount));

	//堆立信息
	m_wHeapHand = INVALID_CHAIR;
	m_wHeapTail = INVALID_CHAIR;
	ZeroMemory(m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));

	//发牌信息
	m_cbSendCardData=0;
	m_cbSendCardCount=0;
	m_cbLeftCardCount=0;
	ZeroMemory(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));

	//运行变量
	m_cbProvideCard=0;
	m_wResumeUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	m_wProvideUser=INVALID_CHAIR;
	m_wBankerUser = (m_bKaiJu)?INVALID_CHAIR:m_wBankerUser;

	//状态变量
	m_bSendStatus=false;
	m_bGangStatus = false;
	m_bTIStatus = false;
	m_bGangOutStatus = false;

	ZeroMemory(m_bEnjoinChiHu,sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng,sizeof(m_bEnjoinChiPeng));

	//用户状态
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

	//组合扑克
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));
	ZeroMemory(m_cbWeaveItemCount,sizeof(m_cbWeaveItemCount));

	//结束信息
	m_cbChiHuCard=0;
	ZeroMemory(m_dwChiHuKind,sizeof(m_dwChiHuKind));
	
	for( WORD i = 0; i < GAME_PLAYER; i++ )
		m_ChiHuRight[i].SetEmpty();

	return;
}

//开始模式
enStartMode __cdecl CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//游戏状态
bool __cdecl CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	return true;
}

//游戏开始
bool __cdecl CTableFrameSink::OnEventGameStart()
{

	//设置状态
	m_pITableFrame->SetGameStatus(GS_MJ_PLAY);

	// 状态复位

	ZeroMemory(m_bOutMagicCard,sizeof(m_bOutMagicCard));
	ZeroMemory(m_bEnjoinChiHu,sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng,sizeof(m_bEnjoinChiPeng));
	ZeroMemory(m_bPlayleft,sizeof(m_bPlayleft));


	//混乱扑克
	m_lSiceCount = MAKELONG(MAKEWORD(rand()%6+1,rand()%6+1),MAKEWORD(rand()%6+1,rand()%6+1));
	m_cbLeftCardCount=CountArray(m_cbRepertoryCard);
	m_GameLogic.RandCardData(m_cbRepertoryCard,CountArray(m_cbRepertoryCard));
  
	if (m_bKaiJu)
	{
		m_wBankerUser = ((BYTE)(m_lSiceCount>>24)+(BYTE)(m_lSiceCount>>16)-1)%GAME_PLAYER;
		m_bKaiJu = false; 
 	}


#ifdef DEBUG
	//test
	BYTE byTest[] = {
	
		0x17,0x12,0x22,0x16, //oma  最后4张
		0x06,0x29,0x08,0x25,0x04,0x29,0x09,0x13,0x07,						
		0x07,0x04,0x03,0x07,0x25,0x07,0x05,0x26,0x22,						
		0x08,0x04,0x29,0x06,0x06,0x05,0x17,0x19,0x05,						
		0x08,0x28,0x11,0x28,0x06,0x27,0x24,0x27,0x02,	
		0x22,0x14,0x05,0x12,0x04,0x24,0x11,0x03,0x16,						
		0x14,0x01,0x18,0x25,0x11
		,0x11 // oma 牌精
		,0x19, // oma 庄家第14张牌


		0x14,0x15,0x16,0x27,0x28,0x29,0x13,0x13,0x13,//oma  user 3 ,card data
		0x12,0x21,0x26,0x26,

		0x12,0x15,0x15,0x15,0x16,0x17,0x18,0x19,0x19, //oma  user 2 ,card data
		0x21,0x22,0x23,0x24,

		0x21,0x21,0x01,0x01,0x01,0x02,0x02,0x02,0x03,//oma  user 1 ,card data
		0x03,0x09,0x09,0x09,

		0x08,0x27,0x23,0x14,0x25,0x18,0x23,0x17,0x18, //oma  user 0 ,card data
		0x23,0x24,0x28,0x26,


//		0x14,0x14,0x29,0x29,0x29,0x26,0x13,0x13,0x13,//oma  user 3 ,card data
//		0x14,0x21,0x26,0x26,

//		0x16,0x15,0x15,0x01,0x13,0x23,0x19,0x06,0x19, //oma  user 2 ,card data
//		0x25,0x06,0x29,0x15,

//		0x21,0x01,0x01,0x02,0x02,0x02,0x03,0x03,0x21, //oma  user 1 ,card data
//		0x21,0x09,0x09,0x09,

//		0x08,0x27,0x23,0x14,0x25,0x18,0x23,0x17,0x18, //oma  user 0 ,card data
//		0x23,0x24,0x28,0x26,

		
		//0x23,0x15,0x22,0x29, //oma  最后4张
		//0x26,0x23,0x26,0x15,0x04,0x26,0x11,0x27,0x08,						
		//0x22,0x04,0x03,0x24,0x15,0x15,0x05,0x21,0x21,						
		//0x23,0x06,0x07,0x19,0x09,0x05,0x27,0x14,0x07,						
		//0x16,0x16,0x14,0x13,0x17,0x27,0x21,0x27,0x08,	
		//0x21,0x07,0x08,0x11,0x13,0x24,0x11,0x04,0x23,						
		//0x22,0x29,0x29,0x19,0x19
		//,0x11 // oma 牌精
		//,0x28, // oma 庄家第14张牌
		//

		//0x13,0x12,0x26,0x24,0x24,0x18,0x28,0x28,0x28,//oma  user 3 ,card data
		//0x06,0x01,0x04,0x06,

		//0x16,0x25,0x25,0x08,0x12,0x13,0x16,0x14,0x25, //oma  user 2 ,card data
		//0x25,0x05,0x06,0x07,

		//0x01,0x01,0x01,0x02,0x02,0x02,0x03,0x03,0x03, //oma  user 1 ,card data
		//0x09,0x12,0x09,0x09,

		//0x29,0x22,0x19,0x12,0x17,0x17,0x17,0x18,0x18, //oma  user 0 ,card data
		//0x08,0x14,0x18,0x23,

	};
	CopyMemory( m_cbRepertoryCard,byTest,sizeof(byTest) );
	m_wBankerUser = 2;//OMA MODIFY 设置庄家用户
#endif

	//分发扑克，发给没给用户手上13张
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if( m_pITableFrame->GetServerUserItem(i) != NULL )
		{
			m_bPlayStatus[i] = true;
			m_cbLeftCardCount-=(MAX_COUNT-1);
			m_GameLogic.SwitchToCardIndex(&m_cbRepertoryCard[m_cbLeftCardCount],MAX_COUNT-1,m_cbCardIndex[i]);
		}
		else
		{
			m_bPlayStatus[i] = false;
		}
	}

	//发送扑克,庄家多拿一张牌
	m_cbSendCardCount++;
	m_cbSendCardData=m_cbRepertoryCard[--m_cbLeftCardCount];
	m_cbCardIndex[m_wBankerUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;


	//OMA 产生牌精	
	m_cbSendCardCount++;
 	//OMA 设置牌精
	m_GameLogic.SetPaiJing(m_cbRepertoryCard[--m_cbLeftCardCount]);
	
 
	//设置变量
	m_cbProvideCard=0;
	m_wProvideUser=INVALID_CHAIR;
	m_wCurrentUser=m_wBankerUser;

	//堆立信息
	WORD wSice = WORD(m_lSiceCount&0xffff);
	BYTE cbSiceTakeCount= HIBYTE(wSice)+LOBYTE(wSice);
	WORD wTakeChairID=(m_wBankerUser+cbSiceTakeCount-1)%GAME_PLAYER;
	BYTE cbTakeCount=MAX_REPERTORY-m_cbLeftCardCount;
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//计算数目
		BYTE cbValidCount=HEAP_FULL_COUNT-m_cbHeapCardInfo[wTakeChairID][1]-((i==0)?(cbSiceTakeCount)*2:0);
		BYTE cbRemoveCount=__min(cbValidCount,cbTakeCount);

		//提取扑克
		cbTakeCount-=cbRemoveCount;
		m_cbHeapCardInfo[wTakeChairID][(i==0)?1:0]+=cbRemoveCount;

		//完成判断
		if (cbTakeCount==0)
		{
			m_wHeapHand=wTakeChairID;
			m_wHeapTail=(m_wBankerUser+cbSiceTakeCount-1)%GAME_PLAYER;
			//牌头加上4张,凑够108张牌
			m_cbHeapCardInfo[m_wHeapHand][0] -= 4;
			break;
		}
		//切换索引
		wTakeChairID=(wTakeChairID+1)%GAME_PLAYER;
	}

	//动作分析，发牌完成先判断庄家是否胡牌或者杠牌
	bool bAroseAction=false;
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		//庄家判断
		if (i==m_wBankerUser)
		{
			//杠牌判断
			tagGangCardResult GangCardResult;
			m_cbUserAction[i]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[i],NULL,0,GangCardResult);

			// 庄家开始，不会有贴的牌，因此不会有提牌

			//胡牌判断
			CChiHuRight chr;
			m_cbCardIndex[i][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]--;
			m_cbUserAction[i]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i],NULL,0,m_cbSendCardData,chr);
			m_cbCardIndex[i][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;
		}
	}

	//构造数据
	CMD_S_GameStart GameStart;
	GameStart.lSiceCount=m_lSiceCount;
	GameStart.wBankerUser=m_wBankerUser;
	GameStart.wCurrentUser=m_wCurrentUser;
	GameStart.wHeapHand = m_wHeapHand;
	GameStart.wHeapTail = m_wHeapTail;
	GameStart.cbLeftCardCount = m_cbLeftCardCount;
	GameStart.bKaiJu = m_bKaiJu;
	GameStart.cbPaiJing = m_GameLogic.GetPaiJing();// OMA 设置牌精

	CopyMemory(GameStart.cbHeapCardInfo,m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));

	//发送数据
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if( !m_bPlayStatus[i] ) continue;

		//设置变量
		GameStart.cbUserAction=m_cbUserAction[i];
		m_GameLogic.SwitchToCardData(m_cbCardIndex[i],GameStart.cbCardData);

		//发送数据
		m_pITableFrame->SendTableData(i,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
		m_pITableFrame->SendLookonData(i,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
	}

 
	return true;
}

// OMA 花猪处理
bool CTableFrameSink::HandleHuaZhu(int i,LONG lHuaZhuScore[GAME_PLAYER])
{

	//OMA 查花猪
	bool bHuaZhu = m_GameLogic.IsHuaZhu(m_cbCardIndex[i],m_WeaveItemArray[i],m_cbWeaveItemCount[i]);
	if( bHuaZhu ) 
	{
		m_bHuaZhu[i] = true;// 设置花猪

		//花猪赔给非花猪玩家最大番数。
		for( WORD j = 0; j < GAME_PLAYER; j++ )
		{
			IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(j);// pUserItem 可能为空
			LPCTSTR pUserName = (NULL!=pUserItem)?pUserItem->GetAccounts():TEXT("离开用户");

			//跳过自己 、逃跑者、已经胡牌者
			if( j == i  || m_bPlayStatus[j] )
			{
				TCHAR msg[256] = TEXT("");
				  _snprintf_s(msg,sizeof(msg),TEXT("查花猪跳过用户: %s"),pUserName);
				CTraceService::TraceString(msg,TraceLevel_Debug);
				continue;
			}

			// 花猪赔偿，对非花猪赔偿
			if( !m_GameLogic.IsHuaZhu(m_cbCardIndex[j],m_WeaveItemArray[j],m_cbWeaveItemCount[j]) )
			{
				//
				LONG maxScore = (LONG)pow(2.0,m_pGameServiceOption->lMaxScoreTimes-1);
				lHuaZhuScore[i] -= m_pGameServiceOption->lCellScore*maxScore;
				//lHuaZhuScore[j] += m_pGameServiceOption->lCellScore*maxScore; // 这里只检查不计算分数

				TCHAR msg[256] = TEXT("");
				  _snprintf_s(msg,sizeof(msg),TEXT("玩家: %s 得到赔偿分：%d"),pUserName,m_pGameServiceOption->lCellScore*maxScore);
				CTraceService::TraceString(msg,TraceLevel_Debug);
			}


		}

		CTraceService::TraceString(TEXT("当前用户查花猪结束"),TraceLevel_Debug);
		return true;

	}else
	{
		CTraceService::TraceString(TEXT("当前用户不是花猪"),TraceLevel_Debug);
		return false;
	}
}
// OMA 查叫处理
void CTableFrameSink::HandleChaJiao(int i,LONG lChaJiaoScore[GAME_PLAYER])
{

	if(!m_GameLogic.IsTingCard(m_cbCardIndex[i],m_WeaveItemArray[i],m_cbWeaveItemCount[i]))
	{
		m_bWuJiao[i] = true;
		for( WORD j = 0; j < GAME_PLAYER; j++ )
		{

			IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(j);// pUserItem 可能为空
			LPCTSTR pUserName = (NULL!=pUserItem)?pUserItem->GetAccounts():TEXT("离开用户");

			// 跳过自己和停止游戏的玩家
			if( j == i || !m_bPlayStatus[j] )
			{
				TCHAR msg[256] = TEXT("");
				  _snprintf_s(msg,sizeof(msg),TEXT("跳过停止游戏玩家: %s "),pUserName);
				CTraceService::TraceString( msg,TraceLevel_Debug);

				continue;
			}
			// 判断剩余玩家是否有叫
			if( m_GameLogic.IsTingCard(m_cbCardIndex[j],m_WeaveItemArray[j],m_cbWeaveItemCount[j]) )
			{
				//有叫
				//查找最大番数
				WORD wFanShu = 1;
				CChiHuRight chr;
				for( BYTE k = 0; k < MAX_INDEX-7; k++ )
				{
					BYTE cbCurrentCard = m_GameLogic.SwitchToCardData(k);
					if( WIK_CHI_HU == m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[j],m_WeaveItemArray[j],
						m_cbWeaveItemCount[j],cbCurrentCard,chr) )
					{
						FiltrateRight(j,chr);
						WORD wFanShuTemp = m_GameLogic.GetChiHuActionRank(chr);
						//取最大番数
						if( wFanShuTemp > wFanShu ) wFanShu = wFanShuTemp;
					}
				}

				LONG score = (LONG)pow(2.0,wFanShu-1);

				//查叫赔偿
				lChaJiaoScore[i] -= m_pGameServiceOption->lCellScore*score;// 扣分
				//lChaJiaoScore[j] += m_pGameServiceOption->lCellScore*score;// 这里只检查不计算分数

				TCHAR msg[256] = TEXT("");
				  _snprintf_s(msg,sizeof(msg),TEXT("查叫给用户 %s 赔偿 %d (番数 %d)"),pUserName,m_pGameServiceOption->lCellScore*score,wFanShu);
				CTraceService::TraceString( msg,TraceLevel_Debug);

			}else
			{
				TCHAR msg[256] = TEXT("");
				  _snprintf_s(msg,sizeof(msg),TEXT("用户 %s 有叫"),pUserName);
				CTraceService::TraceString( msg,TraceLevel_Debug);
			}
		}
	}


	
}

void CTableFrameSink::PayPunishScore(int i,LONG lHuaZhuScore[GAME_PLAYER],LONG lChaJiaoScore[GAME_PLAYER])
{

	// 检查用户状态
	if(!m_bPlayStatus[i] || !m_bWuJiao[i] ) 
	{
		// 跳过不在局中的玩家、有叫玩家
		return;
	}
 
	IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(i);// 花猪用户项
	LPCTSTR pUserName = (NULL!=pUserItem)?pUserItem->GetAccounts():TEXT("错误用户");//花猪用户名称
	LONG lScore = 0 ;
	if (m_pGameServiceOption->wServerType == GAME_GENRE_SCORE)
	{
		lScore = pUserItem->GetUserScore()->lScore;
	}else if (m_pGameServiceOption->wServerType == GAME_GENRE_GOLD)
	{
		lScore = pUserItem->GetUserScore()->lGameGold;
	}
 
	if (m_bHuaZhu[i])//是花猪用户
	{
 		// 统计局中非花猪玩家数量
		WORD wNotHuaZhuCount = 0;
		for( WORD k = 0; k < GAME_PLAYER; k++ )
		{
			if (!m_bHuaZhu[k] && m_bPlayStatus[k])
			{
				wNotHuaZhuCount++;
			}
		}


		// 花猪负分处理
		if (lScore<lHuaZhuScore[i])
		{
			m_lGameScore[i] = 0;
		}

 		// 赔偿非花猪玩家
		for( WORD j = 0; j < GAME_PLAYER; j++ )
		{
 			if(i == j || m_bHuaZhu[j] || !m_bPlayStatus[j])
			{
				// 跳过自己、跳过其他花猪玩家，跳过不在局中玩家
				continue;
			}
 			// 赔偿分数，按照平均分配
 			LONG lPayPunishScore = (-lHuaZhuScore[i] > lScore)?lScore/wNotHuaZhuCount:-lHuaZhuScore[i]/wNotHuaZhuCount;
			m_lGameScore[j] += lPayPunishScore;

			IServerUserItem *pUserItem2 = m_pITableFrame->GetServerUserItem(j);// pUserItem 可能为空
			LPCTSTR pUserName2 = (NULL!=pUserItem)?pUserItem->GetAccounts():TEXT("错误用户");
			TCHAR msg[256] = TEXT("");
			  _snprintf_s(msg,sizeof(msg),TEXT("花猪玩家: %s 赔偿给非花猪玩家:%s分数：%d "),pUserName,pUserName2,lPayPunishScore);
			CTraceService::TraceString( msg,TraceLevel_Debug);
			//TODO: 通知客户端


  		}
 	}else if (m_bWuJiao[i])// 是无叫用户
	{
		// 统计局中有叫玩家数量
		WORD wHaveJiaoCount = 0;
		for( WORD k = 0; k < GAME_PLAYER; k++ )
		{
			if (!m_bHuaZhu[k] && m_bPlayStatus[k])
			{
				wHaveJiaoCount++;
			}
		}

		// 查叫负分处理
		if (lScore<lChaJiaoScore[i])
		{
			m_lGameScore[i] = 0;
		}

		// 赔偿有叫玩家
		for( WORD j = 0; j < GAME_PLAYER; j++ )
		{
 			// 赔偿有叫玩家
			if(i != j && !m_bWuJiao[j]&& m_bPlayStatus[j])
			{
 				// 分配分数
				LONG lPayPunishScore = (-lChaJiaoScore[i] > lScore)?lScore/wHaveJiaoCount:-lChaJiaoScore[i]/wHaveJiaoCount;
				m_lGameScore[j] += lPayPunishScore;

				IServerUserItem *pUserItem2 = m_pITableFrame->GetServerUserItem(j);// pUserItem 可能为空
				LPCTSTR pUserName2 = (NULL!=pUserItem)?pUserItem->GetAccounts():TEXT("错误用户");
				TCHAR msg[256] = TEXT("");
				  _snprintf_s(msg,sizeof(msg),TEXT("无叫玩家: %s 赔偿给有叫玩家:%s分数：%d "),pUserName,pUserName2,lPayPunishScore);
				CTraceService::TraceString( msg,TraceLevel_Debug);

				//TODO: 发送客户端
			}
 		}
	}
 }

//游戏结束
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_NORMAL:		//常规结束
		{
			//变量定义
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.wLeftUser = INVALID_CHAIR;

			//结束信息
			WORD wWinner = INVALID_CHAIR;
			BYTE cbLeftUserCount = 0;			//判断是否流局O
			//bool bUserStatus[GAME_PLAYER];		//

			// OMA 流局判断的作用？// cbLeftUserCount>1说明有流局产生，但不管是不是流局都要查叫查花猪
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				GameEnd.cbCardCount[i]=m_GameLogic.SwitchToCardData(m_cbCardIndex[i],GameEnd.cbCardData[i]);
				m_ChiHuRight[i].GetRightData( &GameEnd.dwChiHuRight[i],MAX_RIGHT_COUNT );
				//流局玩家数
				if( m_ChiHuRight[i].IsEmpty())
				{
					cbLeftUserCount++;
				}
				//当前玩家状态 // OMA 有什么用？
				//bUserStatus[i] = ( NULL != m_pITableFrame->GetServerUserItem(i))?true:false;
				
			}
			
			LONG lHuaZhuScore[GAME_PLAYER];		//花烛分
			LONG lChaJiaoScore[GAME_PLAYER];	//查叫分
			LONG lGangScore[GAME_PLAYER];		//杠分不加分，因此没有用到	
			ZeroMemory( lGangScore,sizeof(lGangScore));
			ZeroMemory( lHuaZhuScore,sizeof(lHuaZhuScore));
			ZeroMemory( lChaJiaoScore,sizeof(lChaJiaoScore));

			//OMA 查牌
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
 				
				IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(i);// pUserItem 可能为空
				LPCTSTR pUserName = (NULL!=pUserItem)?pUserItem->GetAccounts():TEXT("离开用户");
				
				TCHAR pMsg[128] = TEXT("");
				  _snprintf_s(pMsg,sizeof(pMsg),TEXT("开始对用户: %s 进行判断"),pUserName);
				CTraceService::TraceString( pMsg,TraceLevel_Debug);

				// OMA 跳过停止玩牌玩家
				if (!m_bPlayStatus[i])// 逃跑者,已经设置m_bPlayStatus为false
				{
						TCHAR pMsg[128] = TEXT("");
						if ( m_bPlayleft[i])
						{
							  _snprintf_s(pMsg,sizeof(pMsg),TEXT("用户: %s 是逃跑用户"),pUserName);
						}else
						{
							  _snprintf_s(pMsg,sizeof(pMsg),TEXT("用户: %s 是胡牌用户"),pUserName);
						}
						
						CTraceService::TraceString( pMsg,TraceLevel_Debug);
						continue;
				}
//////////////////////////////////////////////////////////////////////////
				// OMA 逻辑框架
				
				// OMA 是否打出听用
				if(m_bOutMagicCard[i])
				{
					// 查叫，检查当前用户与其他三家用户的关系
					HandleChaJiao(i,lChaJiaoScore);

				}else
				{
					if(HandleHuaZhu(i,lHuaZhuScore))// 花猪处理
					{
						continue;
					}else
					{
						// 查叫
						HandleChaJiao(i,lChaJiaoScore);
					}
				}
			}

			//查牌结束

//////////////////////////////////////////////////////////////////////////
			// 处理罚分计算
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
				// 循环每一个用户
				PayPunishScore(i,lHuaZhuScore,lChaJiaoScore);
			}
   

			//积分扣税
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				if( NULL == m_pITableFrame->GetServerUserItem(i) )
				{
					continue;
				}

				//扣税类型
				if( GAME_GENRE_SCORE == m_pGameServiceOption->wServerType ||
					 GAME_GENRE_GOLD == m_pGameServiceOption->wServerType||
					 GAME_GENRE_LONGMATCH == m_pGameServiceOption->wServerType)
				{

#if 0
 // 按照固定数目抽税
					if (m_pGameServiceOption->lCellScore>0 && m_pGameServiceOption->wRevenue>0 )
					{
						LONG wRevenue = m_pGameServiceOption->wRevenue;
						LONG lCellScore = m_pGameServiceOption->lCellScore;
						float rate = wRevenue*1.0/lCellScore;
						if (rate>=0 && rate<= 1)
						{
							m_lGameTax[i] = m_pGameServiceOption->wRevenue;
							m_lGameScore[i] -= m_lGameTax[i];
						}

					}


#else
// 按照固定比例抽税
					if (m_lGameScore[i]>0L)
					{
						m_lGameTax[i] = (LONG)((LONGLONG)m_lGameScore[i]*m_pGameServiceOption->wRevenue/1000L);
						m_lGameScore[i] -= m_lGameTax[i];
					}
#endif 	
				}
		
				enScoreKind ScoreKind;
				if( m_lGameScore[i] > 0L ) ScoreKind = enScoreKind_Win;
				else if( m_lGameScore[i] < 0L ) ScoreKind = enScoreKind_Lost;
				else ScoreKind = enScoreKind_Draw;

				//写入积分
				m_pITableFrame->WriteUserScore(i,m_lGameScore[i],m_lGameTax[i],ScoreKind);
			}

			CopyMemory( GameEnd.lHuaZhuScore,lHuaZhuScore,sizeof(lHuaZhuScore) );
			CopyMemory( GameEnd.lChaJiaoScore,lChaJiaoScore,sizeof(lChaJiaoScore) );
			CopyMemory( GameEnd.bPlayleft,m_bPlayleft,sizeof(m_bPlayleft));

			CopyMemory( GameEnd.lGameScore,m_lGameScore,sizeof(m_lGameScore) );
			CopyMemory( GameEnd.lGangScore,lGangScore,sizeof(lGangScore) );
			CopyMemory( GameEnd.wWinOrder,m_wWinOrder,sizeof(m_wWinOrder) );
			CopyMemory( GameEnd.wProvideUser,m_wProvider,sizeof(m_wProvider) );
			CopyMemory( GameEnd.lGameTax,m_lGameTax,sizeof(m_lGameTax) );
			CopyMemory( GameEnd.wLostFanShu,m_wLostFanShu,sizeof(m_wLostFanShu) );


			if (m_wWinOrder[0] != INVALID_CHAIR)
			{
				m_wBankerUser = m_wWinOrder[0];
			}
			if ((m_wWinOrder[0]!=INVALID_CHAIR)&& (m_wWinOrder[1]!=INVALID_CHAIR))
			{
				if (m_wProvider[m_wWinOrder[0]] == m_wProvider[m_wWinOrder[1]])
				{
					m_wBankerUser = m_wProvider[m_wWinOrder[0]];
				}
			}

			//发送结束信息
			m_pITableFrame->SendTableData( INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd) );
			m_pITableFrame->SendLookonData( INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd) );

			//结束游戏
			m_pITableFrame->ConcludeGame();
			return true;
		}
	case GER_DISMISS:		//游戏解散
		{
			//变量定义
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.wLeftUser = INVALID_CHAIR;

			//设置变量
			memset( GameEnd.wProvideUser,INVALID_CHAIR,sizeof(GameEnd.wProvideUser) );

			//拷贝扑克
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				GameEnd.cbCardCount[i]=m_GameLogic.SwitchToCardData(m_cbCardIndex[i],GameEnd.cbCardData[i]);
			}

			//发送信息
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//结束游戏
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_USER_LEFT:		//用户强退
		{
			//变量定义
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.wLeftUser = wChairID;

			//记录逃跑用户状态
			m_bPlayleft[wChairID] = true; 
			m_bPlayStatus[wChairID] = false; // 设置玩牌状态为false
	
			//OMA 逃跑扣最大番分数
			LONG maxScore = (LONG)pow(2.0,m_pGameServiceOption->lMaxScoreTimes-1);
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
				if( !m_bPlayleft[i] ) // 非逃跑玩家均可获得赔偿
				{
					m_lGameScore[i] += maxScore*m_pGameServiceOption->lCellScore; //OMA 加分
					m_lGameScore[wChairID] -= maxScore*m_pGameServiceOption->lCellScore;// OMA 扣分
				}
			}
				
			//设置积分
			LONG lGameTax = 0L;
 			if (m_lGameScore[wChairID]>0L)// OMA 赔偿后分数情况
			{
				lGameTax = (LONG)((LONGLONG)m_lGameScore[wChairID]*m_pGameServiceOption->wRevenue/1000L);
				m_lGameScore[wChairID] -= lGameTax;// OMA 扣税
			}
			else
			{
 				m_lGameScore[wChairID] = 0;// 负分数设置为0分，开局要求至少能赔偿三个满分
				//防止负分 //TODO: 负 分处理
				//IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(wChairID);
				//if( GAME_GENRE_SCORE==m_pGameServiceOption->wServerType && -m_lGameScore[wChairID] > pUserItem->GetUserScore()->lScore )
				//	m_lGameScore[wChairID] = -pUserItem->GetUserScore()->lScore;
			}
			//OMA 通知其他用户该用户逃跑
			IServerUserItem *pLeftUser =  m_pITableFrame->GetServerUserItem(wChairID);
			LPCTSTR pUserName = (NULL!=pLeftUser)?pLeftUser->GetAccounts():TEXT("错误用户");
			TCHAR szDescribe[128]=TEXT("");

			  _snprintf_s(szDescribe,sizeof(szDescribe),TEXT("[ %s ] 逃跑，对非逃跑玩家赔偿最大番分数！本局结束后计算分数"),pUserName);
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				IServerUserItem *pIServerUserItem2 = NULL;
				if((pIServerUserItem2 = m_pITableFrame->GetServerUserItem(i))!= NULL)
				{
 					m_pITableFrame->SendGameMessage(pIServerUserItem2,szDescribe,SMT_INFO|SMT_EJECT);
				}
			} 
 
			//写入积分
			m_pITableFrame->WriteUserScore(wChairID,m_lGameScore[wChairID],lGameTax,enScoreKind_Flee);
		
			// 继续游戏 OMA
			if(m_wCurrentUser == wChairID )// OMA 发牌给下一个用户
			{
				m_wResumeUser = wChairID;
				m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
				while( !m_bPlayStatus[m_wResumeUser] ) m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
				DispatchCardData(m_wResumeUser,false);
			}
			return true;
		}
	}

	//错误断言
	ASSERT(FALSE);
	return false;
}

//发送场景
bool __cdecl CTableFrameSink::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GS_MJ_FREE:	//空闲状态
		{
			//变量定义
			CMD_S_StatusFree StatusFree;
			memset(&StatusFree,0,sizeof(StatusFree));

			//构造数据
			StatusFree.wBankerUser=m_wBankerUser;
			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			StatusFree.lMaxScoreTimes=m_pGameServiceOption->lMaxScoreTimes;//OMA
		
			CopyMemory(StatusFree.bTrustee,m_bTrustee,sizeof(m_bTrustee));

			//发送场景
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
		}
	case GS_MJ_PLAY:	//游戏状态
		{
			//变量定义
			CMD_S_StatusPlay StatusPlay;
			memset(&StatusPlay,0,sizeof(StatusPlay));

			//游戏变量
			StatusPlay.wBankerUser=m_wBankerUser;
			StatusPlay.wCurrentUser=m_wCurrentUser;
			StatusPlay.lCellScore=m_pGameServiceOption->lCellScore;
			StatusPlay.lMaxScoreTimes=m_pGameServiceOption->lMaxScoreTimes;//OMA

			CopyMemory(StatusPlay.bTrustee,m_bTrustee,sizeof(m_bTrustee));
			CopyMemory(StatusPlay.wWinOrder,m_wWinOrder,sizeof(m_wWinOrder));

			//状态变量
			StatusPlay.cbActionCard=m_cbProvideCard;
			StatusPlay.cbLeftCardCount=m_cbLeftCardCount;
			StatusPlay.cbActionMask=(m_bResponse[wChiarID]==false)?m_cbUserAction[wChiarID]:WIK_NULL;

			//历史记录
			StatusPlay.wOutCardUser=m_wOutCardUser;
			StatusPlay.cbOutCardData=m_cbOutCardData;
			CopyMemory(StatusPlay.cbDiscardCard,m_cbDiscardCard,sizeof(StatusPlay.cbDiscardCard));
			CopyMemory(StatusPlay.cbDiscardCount,m_cbDiscardCount,sizeof(StatusPlay.cbDiscardCount));

			//组合扑克
			CopyMemory(StatusPlay.WeaveItemArray,m_WeaveItemArray,sizeof(m_WeaveItemArray));
			CopyMemory(StatusPlay.cbWeaveCount,m_cbWeaveItemCount,sizeof(m_cbWeaveItemCount));

			//堆立信息
			StatusPlay.wHeapHand = m_wHeapHand;
			StatusPlay.wHeapTail = m_wHeapTail;
			CopyMemory(StatusPlay.cbHeapCardInfo,m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));
			//OMA设置牌精
			StatusPlay.cbPaiJing = m_GameLogic.GetPaiJing();

			//扑克数据
			StatusPlay.cbCardCount=m_GameLogic.SwitchToCardData(m_cbCardIndex[wChiarID],StatusPlay.cbCardData);
			StatusPlay.cbSendCardData=((m_cbSendCardData!=0)&&(m_wProvideUser==wChiarID))?m_cbSendCardData:0x00;

			//发送场景
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}
	}

	return false;
}

//定时器事件
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	return false;
}

//游戏消息处理
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_C_OUT_CARD:		//出牌消息
		{
			//效验消息
			ASSERT(wDataSize==sizeof(CMD_C_OutCard));
			if (wDataSize!=sizeof(CMD_C_OutCard)) return false;

			//用户效验
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//消息处理
			CMD_C_OutCard * pOutCard=(CMD_C_OutCard *)pDataBuffer;
			return OnUserOutCard(pUserData->wChairID,pOutCard->cbCardData);
		}
	case SUB_C_OPERATE_CARD:	//操作消息
		{
			//效验消息
			ASSERT(wDataSize==sizeof(CMD_C_OperateCard));
			if (wDataSize!=sizeof(CMD_C_OperateCard)) return false;

			//用户效验
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//消息处理
			CMD_C_OperateCard * pOperateCard=(CMD_C_OperateCard *)pDataBuffer;
			return OnUserOperateCard(pUserData->wChairID,pOperateCard->cbOperateCode,pOperateCard->cbOperateCard);
		}
	case SUB_C_TRUSTEE:		// 托管消息
		{
			CMD_C_Trustee *pTrustee =(CMD_C_Trustee *)pDataBuffer;
			if(wDataSize != sizeof(CMD_C_Trustee)) return false;

			//用户效验
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();

			m_bTrustee[pUserData->wChairID]=pTrustee->bTrustee;
			CMD_S_Trustee Trustee;
			Trustee.bTrustee=pTrustee->bTrustee;
			Trustee.wChairID = pUserData->wChairID;
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));

			return true;
		}
	}

	return false;
}

//框架消息处理
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

//用户坐下
bool __cdecl CTableFrameSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	return true;
}
//用户同意
bool __cdecl CTableFrameSink::OnActionUserReady(WORD wChairID,IServerUserItem * pIServerUserItem, void * pData, WORD wDataSize)
{
	//OMA START 对符合送分的用户进行送分操作,仅仅是积分类型才送分
	tagUserScore  &pUserScore = pIServerUserItem->GetUserData()->UserScoreInfo;
	if(pUserScore.lScore<m_pGameServiceOption->lLessScore
		&& pUserScore.lGrantCount>0 
		&& m_pGameServiceOption->wServerType == GAME_GENRE_SCORE)
	{
		// 能执行到这里，表示分数不够，但是还有送分次数
		// 送分
		m_pITableFrame->WriteUserScore(pIServerUserItem,m_pGameServiceOption->lLessScore,0,enScoreKind_Present,0);

		// 发送消息
		TCHAR szMessage[512]=TEXT("");
 		  _snprintf_s(szMessage,sizeof(szMessage),TEXT("这是第%d次送%d分，剩余送分次数为%d ",GRANT_SCORE_COUNT-pUserScore.lGrantCount,m_pGameServiceOption->lLessScore,pUserScore.lGrantCount));
		for (WORD i=0;i<m_wPlayerCount;i++)
		{
			IServerUserItem *pIServerUserItem2 = NULL;
			if((pIServerUserItem2 = m_pITableFrame->GetServerUserItem(i))!= NULL)
			{
				WORD wTYPE = SMT_INFO;
				if (pIServerUserItem == pIServerUserItem2)
				{
					//当前用户，弹出信息
					wTYPE |= SMT_EJECT;
				}
				m_pITableFrame->SendGameMessage(pIServerUserItem2,szMessage,wTYPE);
			}
		} 
	}
	// OMA END
	return true;
}

//用户起来
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//庄家设置
	if (bLookonUser==false)
	{
		m_bKaiJu = true;// 用户离开，复位开局标志 OMA
		m_bTrustee[wChairID]=false;
		CMD_S_Trustee Trustee;
		Trustee.bTrustee=false;
		Trustee.wChairID = wChairID;
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));
	}

	return true;
}

//用户出牌
bool CTableFrameSink::OnUserOutCard(WORD wChairID, BYTE cbCardData)
{

	//效验状态
	ASSERT(m_pITableFrame->GetGameStatus()==GS_MJ_PLAY);
	if (m_pITableFrame->GetGameStatus()!=GS_MJ_PLAY) return true;

	//错误断言
	ASSERT(wChairID==m_wCurrentUser);
	ASSERT(m_GameLogic.IsValidCard(cbCardData)==true);

	//效验参数
	if (wChairID!=m_wCurrentUser) return false;
	if (m_GameLogic.IsValidCard(cbCardData)==false) return false;

	//删除扑克
	if (m_GameLogic.RemoveCard(m_cbCardIndex[wChairID],cbCardData)==false)
	{
		ASSERT(FALSE);
		return false;
	}

	//设置变量
	m_bSendStatus=true;
	if( m_bGangStatus )
	{
		m_bGangStatus = false;
		m_bGangOutStatus = true;
	}

	if(m_cbUserAction[wChairID] == WIK_CHI_HU)
	{
		m_bEnjoinChiHu[wChairID] = true;
	}

	m_cbUserAction[wChairID]=WIK_NULL;
	m_cbPerformAction[wChairID]=WIK_NULL;

	//出牌记录
	m_cbOutCardCount++;
	m_wOutCardUser=wChairID;
	m_cbOutCardData=cbCardData;


	//构造数据
	CMD_S_OutCard OutCard;
	OutCard.wOutCardUser=wChairID;
	OutCard.cbOutCardData=cbCardData;

	//发送消息
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OUT_CARD,&OutCard,sizeof(OutCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OUT_CARD,&OutCard,sizeof(OutCard));

	m_wProvideUser=wChairID;
	m_cbProvideCard=cbCardData;

	if (m_GameLogic.IsMagicCard(cbCardData)) // 打出听用
	{
		m_bOutMagicCard[wChairID] = true;			//设置打出听用
		m_bEnjoinChiHu[wChairID] = true;			//设置禁止吃胡
		m_bEnjoinChiPeng[wChairID] = true;			//设置禁止吃碰
	}

	//用户切换
	m_wCurrentUser=(wChairID+m_wPlayerCount-1)%m_wPlayerCount;
	while( !m_bPlayStatus[m_wCurrentUser] ) 
		m_wCurrentUser=(m_wCurrentUser+m_wPlayerCount-1)%m_wPlayerCount;


	//响应判断
	bool bAroseAction=EstimateUserRespond(wChairID,cbCardData,EstimatKind_OutCard);

	//派发扑克
	if (bAroseAction==false) DispatchCardData(m_wCurrentUser);

	return true;
}

//用户操作
bool CTableFrameSink::OnUserOperateCard(WORD wChairID, BYTE cbOperateCode, BYTE cbOperateCard)
{
	//效验状态
	ASSERT(m_pITableFrame->GetGameStatus()==GS_MJ_PLAY);
	if (m_pITableFrame->GetGameStatus()!=GS_MJ_PLAY)
		return true;

	//效验用户
	ASSERT((wChairID==m_wCurrentUser)||(m_wCurrentUser==INVALID_CHAIR));
	if ((wChairID!=m_wCurrentUser)&&(m_wCurrentUser!=INVALID_CHAIR)) 
		return false;


	//被动动作
	if (m_wCurrentUser==INVALID_CHAIR)
	{
		//效验状态
		ASSERT(m_bResponse[wChairID]==false); // 用户wChairID 只能响应一次
		ASSERT((cbOperateCode==WIK_NULL)||((m_cbUserAction[wChairID]&cbOperateCode)!=0));// 动作只能是放弃 或者是可执行动作中的一个

		//效验状态
		if (m_bResponse[wChairID]==true) // 用户wChairID 只能响应一次
			return false;
		if ((cbOperateCode!=WIK_NULL)&&((m_cbUserAction[wChairID]&cbOperateCode)==0))// 动作只能是放弃 或者是可执行动作中的一个
			return false;
		//变量定义
		WORD wTargetUser=wChairID; // wTargetUser 执行动作的用户
		BYTE cbTargetAction=cbOperateCode;// 用户执行的动作

		//设置变量
		m_bResponse[wChairID]=true; // 设置ID 为 wChairID 的用户，已经执行过动作了
		m_cbPerformAction[wChairID]=cbOperateCode; // 将要执行的操作码
		m_cbOperateCard[wChairID]=(cbOperateCard==0)?m_cbProvideCard:cbOperateCard;// 与动作操作相关的牌

		//在自己未摸下一张牌的一圈内,不能弃上一家而胡下一家
		if( cbTargetAction == WIK_NULL && (WIK_CHI_HU&m_cbUserAction[wTargetUser]) &&
			m_wProvideUser != wTargetUser )
			m_bEnjoinChiHu[wTargetUser] = true;


		//执行判断
		for (WORD i=0;i<m_wPlayerCount;i++) // 检查所有用户
		{
			//获取动作
			BYTE cbUserAction=(m_bResponse[i]==false)?m_cbUserAction[i]:m_cbPerformAction[i];
			// cbUserAction 设置为 ，第i个用户没响应过，动作为可执行动作，否则为实际执行的动作
			
			//优先级别
			BYTE cbUserActionRank=m_GameLogic.GetUserActionRank(cbUserAction); // 第i个用户的 执行动作或 可执行动作 的优先级
			BYTE cbTargetActionRank=m_GameLogic.GetUserActionRank(cbTargetAction);// cbTargetActionRank 当前用户执行的动作优先级

			// 两个用户同时贴牌
			if((cbTargetAction & WIK_TIE_PAI) != 0 &&
				(cbUserAction & WIK_TIE_PAI) !=0)
			{
				cbTargetActionRank = 0;
				WORD wTmpID = m_wProvideUser;
				if(i == (--wTmpID)%4>=0?wTmpID: 3) // 按照出牌用户开始，依次计算相同操作码下面的用户等级
				{
					cbUserActionRank = OPE_RANK2_LEVEL1;
				}else if(i == ((wTmpID-=2)%4>=0?wTmpID:3))
				{
				   cbUserActionRank = OPE_RANK2_LEVEL2;
				}else if(i == ((wTmpID-=3)%4>=0?wTmpID:3))
				{
					cbUserActionRank = OPE_RANK2_LEVEL2;
				}
			}
			//TODO: 2个或者三个用户同时吃胡


			//动作判断,优先级判断
			if (cbUserActionRank>cbTargetActionRank) 
			{
				wTargetUser=i;
				cbTargetAction=cbUserAction;
			}
		}

		if (m_bResponse[wTargetUser]==false) // 如果目标用户没有执行动作，返回不继续往下处理
			return true;

		//OMA 到这里目标用户已经产生,执行目标用户的动作

		//吃胡等待,处理双响三响
		if (cbTargetAction==WIK_CHI_HU)
		{
			
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				// 等待其他可胡牌的用户响应
				if ((m_bResponse[i]==false)&&(m_cbUserAction[i]&WIK_CHI_HU))
					return true;
			}
		}
 
		//放弃操作, 如果有2个同时吃胡，产生两个目标用户,其中一个放弃?OMA
		if (cbTargetAction==WIK_NULL)
		{
			//用户状态
			ZeroMemory(m_bResponse,sizeof(m_bResponse));
			ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
			ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
			ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

			//发送扑克
			DispatchCardData(m_wResumeUser);
			return true;
		}
		//变量定义
		BYTE cbTargetCard=m_cbOperateCard[wTargetUser];

		//出牌变量
		m_cbOutCardData=0;
		m_bSendStatus=true;
		m_wOutCardUser=INVALID_CHAIR;

		//胡牌操作
		if (cbTargetAction==WIK_CHI_HU) // 点炮
		{
			//结束信息
			m_cbChiHuCard=cbTargetCard;

			// 从出牌用户的下一个用户开始循环计算
			for (WORD i=(m_wProvideUser+m_wPlayerCount-1)%GAME_PLAYER;i!=m_wProvideUser;i = (i+m_wPlayerCount-1)%GAME_PLAYER)
			{
				//过虑判断
				if ((m_cbPerformAction[i]&WIK_CHI_HU)==0)
					continue;


				//胡牌判断
				BYTE cbWeaveItemCount=m_cbWeaveItemCount[i];
				tagWeaveItem * pWeaveItem=m_WeaveItemArray[i];
				m_dwChiHuKind[i] = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i],pWeaveItem,cbWeaveItemCount,m_cbChiHuCard,m_ChiHuRight[i]);

				if (m_GameLogic.IsDaDanDiao(m_cbCardIndex[m_wProvideUser],m_cbWeaveItemCount[m_wProvideUser]))
				{
					// 放炮用户为大单吊牌型，胡牌加番
					m_ChiHuRight[i] |= CHR_DA_DAN_DIAO_PAO; 
				}

				//插入扑克
				if (m_dwChiHuKind[i]!=WIK_NULL) 
				{
					m_cbCardIndex[i][m_GameLogic.SwitchToCardIndex(m_cbChiHuCard)]++;
					ProcessChiHuUser( i,false );
				}
			}

			//判断结束
			BYTE cbPlayCount = 0;
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
				if( m_bPlayStatus[i] ) cbPlayCount++;
			}

			if( cbPlayCount < 2 ) 
				OnEventGameEnd( INVALID_CHAIR,NULL,GER_NORMAL );
			else
			{
				//用户状态
				ZeroMemory(m_bResponse,sizeof(m_bResponse));
				ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
				ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
				ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

				if(m_bGangStatus == true && m_wProvideUser != wTargetUser) 
				{
					// 抢杠失败后，恢复原样OMA,有问题？杠失败的可能情形是什么？
					//// 改变供应用户手中杠类型为碰类型
					for (BYTE k =0;k<m_cbWeaveItemCount[m_wProvideUser];k++) 
					{
						BYTE cbCenterCard = m_WeaveItemArray[m_wProvideUser][k].cbCenterCard;
						if (m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind == WIK_GANG && cbCenterCard == m_cbChiHuCard)
						{
							m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind = WIK_PENG; // 更改为碰类型
							m_bGangStatus = false; // 重置杠状态
							break;
						}
						

					}

				}
				if((m_bTIStatus == true) && m_wProvideUser != wTargetUser) 
				{
					// 处理抢提失败OMA,抢提失败的可能原因是什么？
					// 改变供应用户手中碰类型为贴类型
					for (BYTE k =0;k<m_cbWeaveItemCount[m_wProvideUser];k++) // 改变供应用户手中杠类型为碰类型
					{
						BYTE cbCenterCard = m_WeaveItemArray[m_wProvideUser][k].cbCenterCard;
						if (m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind == WIK_PENG && cbCenterCard == m_cbChiHuCard)
						{
							m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind = WIK_TIE_PAI; // 更改为碰类型
							// 删除被提回的听用
							m_GameLogic.RemoveCard(m_cbCardIndex[m_wProvideUser],
								m_GameLogic.SwitchToCardData(m_GameLogic.GetMagicIndex()));
							m_bTIStatus = false;// 重置提牌状态
							break;
						}

					}

				}
				
				m_bGangOutStatus = false;
				m_wResumeUser = wTargetUser;

				//发送扑克
				m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
				while( !m_bPlayStatus[m_wResumeUser] ) m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
			
				DispatchCardData(m_wResumeUser,false);
			}

			return true;
		}

		//用户状态
		ZeroMemory(m_bResponse,sizeof(m_bResponse));
		ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
		ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
		ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

		//组合扑克
		ASSERT(m_cbWeaveItemCount[wTargetUser]<4);
		WORD wIndex=m_cbWeaveItemCount[wTargetUser]++;
		m_WeaveItemArray[wTargetUser][wIndex].cbPublicCard=TRUE;
		m_WeaveItemArray[wTargetUser][wIndex].cbCenterCard=cbTargetCard;
		m_WeaveItemArray[wTargetUser][wIndex].cbWeaveKind=cbTargetAction;
		m_WeaveItemArray[wTargetUser][wIndex].wProvideUser=(m_wProvideUser==INVALID_CHAIR)?wTargetUser:m_wProvideUser;

		//删除扑克
		switch (cbTargetAction)
		{
		case WIK_LEFT:		//上牌操作
			{
				//删除扑克
				BYTE cbRemoveCard[3];
				m_GameLogic.GetWeaveCard(WIK_LEFT,cbTargetCard,cbRemoveCard);
				VERIFY( m_GameLogic.RemoveCard(cbRemoveCard,3,&cbTargetCard,1) );
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );

				break;
			}

		case WIK_RIGHT:		//上牌操作
			{
				//删除扑克
				BYTE cbRemoveCard[3];
				m_GameLogic.GetWeaveCard(WIK_RIGHT,cbTargetCard,cbRemoveCard);
				VERIFY( m_GameLogic.RemoveCard(cbRemoveCard,3,&cbTargetCard,1) );
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );

				break;
			}
		case WIK_TIE_PAI:		//贴牌操作
			{
				//删除扑克

				BYTE cbRemoveCard[3];
				m_GameLogic.GetWeaveCard(WIK_TIE_PAI,cbTargetCard,cbRemoveCard);
				VERIFY( m_GameLogic.RemoveCard(cbRemoveCard,3,&cbTargetCard,1) );
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );
				
				// 贴牌后，估计是否可以有其他操作
				EstimateUserRespond(m_wCurrentUser,0,EstimatKind_TIECard);
				break;
			}

		case WIK_PENG:		//碰牌操作
			{
				//删除扑克
				BYTE cbRemoveCard[]={cbTargetCard,cbTargetCard};
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );
				// 碰牌后，估计是否可以有其他操作
				EstimateUserRespond(m_wCurrentUser,0,EstimatKind_PENGCard);

				break;
			}
		case WIK_GANG:		//杠牌操作
			{
				//删除扑克,被动杠
				BYTE cbRemoveCard[]={cbTargetCard,cbTargetCard,cbTargetCard};
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,CountArray(cbRemoveCard)) );
				m_bGangStatus = true;
				DispatchCardData(wTargetUser,false); // 发牌给杠牌用户，估计当前用户动作

				break;
			}
		default:
			ASSERT( FALSE );
			return false;
		}

		//构造结果
		CMD_S_OperateResult OperateResult;
		OperateResult.wOperateUser=wTargetUser;
		OperateResult.cbOperateCard=cbTargetCard;
		OperateResult.cbOperateCode=cbTargetAction;
		OperateResult.wProvideUser=(m_wProvideUser==INVALID_CHAIR)?wTargetUser:m_wProvideUser;
	    m_bEnjoinChiHu[wTargetUser]=false; // 取消吃胡限制
		//发送消息
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));

		//设置用户
		m_wCurrentUser=wTargetUser;

		//杠牌处理
		if (cbTargetAction==WIK_GANG)
		{
			m_bGangStatus = true;
			DispatchCardData(wTargetUser,false); // 发牌给杠牌用户，估计当前用户动作
		}
		//else 
		//{
		//	// 碰贴之后，估计自己手上牌有没有 提、 杠、 胡。
		//	// 动作完成之后,只估计自己手上牌
		//	EstimatePengTieCardRespond(m_wCurrentUser);

		//	EstimateUserRespond(m_wCurrentUser,0,EstimatKind_TICard);
		//}
		return true;
	}

	//主动动作
	if (m_wCurrentUser==wChairID)
	{
		//效验操作
		ASSERT((cbOperateCode!=WIK_NULL)&&((m_cbUserAction[wChairID]&cbOperateCode)!=0));
		if ((cbOperateCode==WIK_NULL)||((m_cbUserAction[wChairID]&cbOperateCode)==0))// 动作只能是放弃 或者是可执行动作中的一个
			return false;

		//扑克效验
		ASSERT((cbOperateCode==WIK_NULL)||(cbOperateCode==WIK_CHI_HU)||(m_GameLogic.IsValidCard(cbOperateCard)==true));
		if ((cbOperateCode!=WIK_NULL)&&(cbOperateCode!=WIK_CHI_HU)&&(m_GameLogic.IsValidCard(cbOperateCard)==false)) 
			return false;

		//设置变量
		m_bSendStatus=true;
		m_bEnjoinChiHu[m_wCurrentUser]=false;
		m_cbUserAction[m_wCurrentUser]=WIK_NULL;
		m_cbPerformAction[m_wCurrentUser]=WIK_NULL;

		bool bPublic=false;
		// 杠牌 提牌 ，估计抢杠，抢提
		// 如果没有抢杠，抢提，按顺序执行
		// 否则 等待抢杠抢体用户执行结果

		//执行动作
		switch (cbOperateCode)
		{
		case WIK_TI_PAI:			//提牌操作
			{
				//变量定义
				BYTE cbWeaveIndex=0xFF;
				BYTE cbCardIndex=m_GameLogic.SwitchToCardIndex(cbOperateCard);

				//提牌处理
				if (m_cbCardIndex[wChairID][cbCardIndex]>=1) // 至少要有一张可替换的牌
				{
					//寻找组合
					for (BYTE i=0;i<m_cbWeaveItemCount[wChairID];i++)
					{
						BYTE cbWeaveKind=m_WeaveItemArray[wChairID][i].cbWeaveKind;
						BYTE cbCenterCard=m_WeaveItemArray[wChairID][i].cbCenterCard;
						if ((cbCenterCard==cbOperateCard)&&(cbWeaveKind==WIK_TIE_PAI))
						{
							// 找到贴牌组合类型
							bPublic=true;
							cbWeaveIndex=i;
							break;
						}
					}

					//效验动作
					ASSERT(cbWeaveIndex!=0xFF);
					if (cbWeaveIndex==0xFF) return false;
					
					// 删除替换扑克
					m_GameLogic.RemoveCard(m_cbCardIndex[wChairID],cbOperateCard);
					m_bTIStatus = true;// 设置提牌状态

					//组合扑克
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbPublicCard=TRUE;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbWeaveKind=WIK_PENG;
				}


				//构造结果
				CMD_S_OperateResult OperateResult;
				OperateResult.wOperateUser=wChairID;
				OperateResult.wProvideUser=wChairID;
				OperateResult.cbOperateCode=cbOperateCode;
				OperateResult.cbOperateCard=cbOperateCard;

				//发送消息
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));

				// 开头已经估计过动作响应，这里不应该再估计
				//效验动作
				bool bAroseAction=false;
				if (bPublic==true)
				{
					bAroseAction = EstimateUserRespond(wChairID,cbOperateCard,EstimatKind_TICard);
				}

				if (bAroseAction==false)
				{

					m_bTIStatus = false; // 没有人抢提，自己胡牌不算抢提，抢提标志复位

					 EstimateUserRespond(wChairID,m_GameLogic.SwitchToCardData(m_GameLogic.GetMagicIndex()),
										EstimatKind_TICard);
 					//EstimateTICardRespond(wChairID,m_GameLogic.SwitchToCardData(m_GameLogic.GetMagicIndex()));
					m_cbCardIndex[wChairID][m_GameLogic.GetMagicIndex()]++;// 提回听用扑克
				}
				return true;
			}

		case WIK_GANG:			//杠牌操作
			{
				//变量定义
				BYTE cbWeaveIndex=0xFF;
				BYTE cbCardIndex=m_GameLogic.SwitchToCardIndex(cbOperateCard);
				//杠牌处理
				if (m_cbCardIndex[wChairID][cbCardIndex]==1)
				{
					//寻找组合 // 
					for (BYTE i=0;i<m_cbWeaveItemCount[wChairID];i++)
					{
						BYTE cbWeaveKind=m_WeaveItemArray[wChairID][i].cbWeaveKind;
						BYTE cbCenterCard=m_WeaveItemArray[wChairID][i].cbCenterCard;
						if ((cbCenterCard==cbOperateCard)&&(cbWeaveKind==WIK_PENG))
						{
							bPublic=true;
							cbWeaveIndex=i;
							break;
						}
					}

					//效验动作
					ASSERT(cbWeaveIndex!=0xFF);
					if (cbWeaveIndex==0xFF)
					{
						return false;
					}

					//组合扑克
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbPublicCard=TRUE;
					m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser=wChairID;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbWeaveKind=cbOperateCode;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard=cbOperateCard;
				}
				else
				{
					//扑克效验
					ASSERT(m_cbCardIndex[wChairID][cbCardIndex]==4);
					if (m_cbCardIndex[wChairID][cbCardIndex]!=4) 
						return false;

					//设置变量
					bPublic=false; // 设置为不能抢杠
					cbWeaveIndex=m_cbWeaveItemCount[wChairID]++;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbPublicCard=TRUE; // 暗杠设置为可见

					m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser=wChairID;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbWeaveKind=cbOperateCode;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard=cbOperateCard;
				}

				//删除扑克
				m_cbCardIndex[wChairID][cbCardIndex]=0;
				m_bGangStatus = true;

				//构造结果
				CMD_S_OperateResult OperateResult;
				OperateResult.wOperateUser=wChairID;
				OperateResult.wProvideUser=wChairID;
				OperateResult.cbOperateCode=cbOperateCode;
				OperateResult.cbOperateCard=cbOperateCard;

				//发送消息
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));

				//效验动作
				bool bAroseAction=false;
				if (bPublic==true) 
				{
					bAroseAction=EstimateUserRespond(wChairID,cbOperateCard,EstimatKind_PengGangCard);
				}
			
				//发送扑克
				if (bAroseAction==false)
 
				{
					DispatchCardData(wChairID,false); //顺次发牌
				}
				return true;
			}
		case WIK_CHI_HU:		//吃胡操作
			{
				//吃牌权位
				if (m_cbOutCardCount==0)
				{
					m_wProvideUser = m_wCurrentUser;
					m_cbProvideCard = m_cbSendCardData;
				}

				//普通胡牌
				BYTE cbWeaveItemCount=m_cbWeaveItemCount[wChairID];
				tagWeaveItem * pWeaveItem=m_WeaveItemArray[wChairID];
				m_GameLogic.RemoveCard(m_cbCardIndex[wChairID],&m_cbProvideCard,1);
				m_dwChiHuKind[wChairID] = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wChairID],pWeaveItem,cbWeaveItemCount,m_cbProvideCard,
					m_ChiHuRight[wChairID]);
				m_cbCardIndex[wChairID][m_GameLogic.SwitchToCardIndex(m_cbProvideCard)]++;

				//结束信息
				m_cbChiHuCard=m_cbProvideCard;

				ProcessChiHuUser( wChairID,false );

				//判断结束
				BYTE cbPlayCount = 0;
				for( WORD i = 0; i < GAME_PLAYER; i++ )
				{
					if( m_bPlayStatus[i] ) cbPlayCount++;
				}

				if( cbPlayCount < 2 ) 
					OnEventGameEnd( INVALID_CHAIR,NULL,GER_NORMAL );
				else
				{
					//发牌
					m_wCurrentUser = (m_wCurrentUser+GAME_PLAYER-1)%GAME_PLAYER;
					while( !m_bPlayStatus[m_wCurrentUser] )
						m_wCurrentUser = (m_wCurrentUser+GAME_PLAYER-1)%GAME_PLAYER;
					DispatchCardData( m_wCurrentUser,false );
				}

				return true;
			}
		}

		return true;
	}

	return false;
}

//发送操作
bool CTableFrameSink::SendOperateNotify()
{
	//发送提示
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if (m_cbUserAction[i]!=WIK_NULL)
		{
			//构造数据
			CMD_S_OperateNotify OperateNotify;
			OperateNotify.wResumeUser=m_wResumeUser;
			OperateNotify.cbActionCard=m_cbProvideCard;
			OperateNotify.cbActionMask=m_cbUserAction[i];

			//发送数据
			m_pITableFrame->SendTableData(i,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
			m_pITableFrame->SendLookonData(i,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
		}
	}

	return true;
}

//派发扑克 // btail - 是否从最后发牌
bool CTableFrameSink::DispatchCardData(WORD wCurrentUser,bool bTail)
{
	//状态效验
	ASSERT(wCurrentUser!=INVALID_CHAIR);
	if (wCurrentUser==INVALID_CHAIR)
		return false;

	//丢弃扑克
	if ((m_wOutCardUser!=INVALID_CHAIR)&&(m_cbOutCardData!=0))
	{
		m_cbDiscardCount[m_wOutCardUser]++;
		m_cbDiscardCard[m_wOutCardUser][m_cbDiscardCount[m_wOutCardUser]-1]=m_cbOutCardData;
	}

	//荒庄结束
	if (m_cbLeftCardCount==0)
	{
		m_cbChiHuCard=0;
		m_wProvideUser=INVALID_CHAIR;
		OnEventGameEnd(m_wProvideUser,NULL,GER_NORMAL);

		return true;
	}

	//设置变量
	m_cbOutCardData=0;
	m_wCurrentUser=wCurrentUser;
	m_wOutCardUser=INVALID_CHAIR;
	m_bEnjoinChiHu[wCurrentUser]=false;

	//杠后炮
	if( m_bGangOutStatus )
	{
		m_bGangOutStatus = false;
	}
	//发牌处理
	if (m_bSendStatus==true)
	{
		//发送扑克
		m_cbSendCardCount++;
		m_cbSendCardData=m_cbRepertoryCard[--m_cbLeftCardCount];
		//加牌
		m_cbCardIndex[wCurrentUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;
		//设置变量
		m_wProvideUser=wCurrentUser;
		m_cbProvideCard=m_cbSendCardData;
	}

	//堆立信息
	ASSERT( m_wHeapHand != INVALID_CHAIR && m_wHeapTail != INVALID_CHAIR );
	if( !bTail )
	{
		//切换索引
		BYTE cbHeapCount=m_cbHeapCardInfo[m_wHeapHand][0]+m_cbHeapCardInfo[m_wHeapHand][1];
		if (cbHeapCount==HEAP_FULL_COUNT) 
			m_wHeapHand=(m_wHeapHand+1)%CountArray(m_cbHeapCardInfo);
		m_cbHeapCardInfo[m_wHeapHand][0]++;
	}
	else
	{
		//切换索引
		BYTE cbHeapCount=m_cbHeapCardInfo[m_wHeapTail][0]+m_cbHeapCardInfo[m_wHeapTail][1];
		if (cbHeapCount==HEAP_FULL_COUNT) 
			m_wHeapTail=(m_wHeapTail+3)%CountArray(m_cbHeapCardInfo);
		m_cbHeapCardInfo[m_wHeapTail][1]++;
	}
	
	//构造数据
	CMD_S_SendCard SendCard;
	ZeroMemory(&SendCard,sizeof(SendCard));
	SendCard.wCurrentUser=wCurrentUser;
	SendCard.bTail = bTail;
	SendCard.cbActionMask=m_cbUserAction[wCurrentUser];
	SendCard.cbCardData=(m_bSendStatus==true)?m_cbSendCardData:0x00;


	//发送数据
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));

	//发牌后估计OMA
	EstimateUserRespond(wCurrentUser,m_cbSendCardData,EstimatKind_SendCard);


	return true;
}

//bool CTableFrameSink::EstimatePengTieCardRespond(WORD wCenterUser)
//{
//	bool bAroseAction=false;
//
//	//用户状态
//	ZeroMemory(m_bResponse,sizeof(m_bResponse));
//	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
//	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));
//
//	////提牌判断
//	// 估计自己手上牌是否可以提
//	tagTICardResult TICardResult;
//	ZeroMemory(&TICardResult,sizeof(TICardResult));
//	m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
//		m_cbWeaveItemCount[wCenterUser],TICardResult);
//
//	//杠牌判断
//	if (m_cbLeftCardCount>0) 
//	{
//		// 估计自己手上牌是否可以杠
//		tagGangCardResult GangCardResult;
//		ZeroMemory(&GangCardResult,sizeof(GangCardResult));
//		m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
//			m_cbWeaveItemCount[wCenterUser],GangCardResult);
//
//	}
//
//
//	//结果判断
//	if (m_cbUserAction[wCenterUser]!=WIK_NULL) 
//		bAroseAction=true;
//
//
//	//结果处理
//	if (bAroseAction==true) 
//	{
//		//设置变量
//		m_wProvideUser=wCenterUser;
//		m_wResumeUser=m_wCurrentUser;
//		//发送提示
//		SendOperateNotify();
//	}
//
//	return true;
//}


//bool CTableFrameSink::EstimateTICardRespond(WORD wCenterUser,BYTE cbCenterCard)// cbCenterCard 提回的听用为当前牌
//{
//
//	bool bAroseAction=false;
//	
//	//用户状态
//	ZeroMemory(m_bResponse,sizeof(m_bResponse));
//	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
//	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));
//	
//	////提牌判断
//	tagTICardResult TICardResult;
//	m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
//		m_cbWeaveItemCount[wCenterUser],TICardResult);
//
//	//杠牌判断
//	if (m_cbLeftCardCount>0) 
//	{
//		// 估计自己手上牌是否可以杠
//		tagGangCardResult GangCardResult;
//		m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
//			m_cbWeaveItemCount[wCenterUser],GangCardResult);
//
//	}
//
//	//胡牌判断
//	if (m_bEnjoinChiHu[wCenterUser]==false && m_bPlayStatus[wCenterUser])// 如果打出的是钻牌，禁止胡牌
//	{
//		//吃胡判断
//		CChiHuRight chr;
//		BYTE cbWeaveCount=m_cbWeaveItemCount[wCenterUser];
//		m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],cbWeaveCount,cbCenterCard,chr);
//
//	}
//
//	//结果判断
//	if (m_cbUserAction[wCenterUser]!=WIK_NULL) 
//		bAroseAction=true;
//
//	//结果处理
//	if (bAroseAction==true) 
//	{
//
//		//设置变量
//		m_wProvideUser=wCenterUser;
//		m_cbProvideCard=cbCenterCard;
//		m_wResumeUser=m_wCurrentUser;
//		//发送提示
//		SendOperateNotify();
//
//	}
//
//	return true;
//
//}


//响应判断 
bool CTableFrameSink::EstimateUserRespond(WORD wCenterUser, BYTE cbCenterCard, enEstimatKind EstimatKind)
{
	//变量定义
	bool bAroseAction=false;
 
	//用户状态
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));
	//////////////////////////////////////////////////////////////////////////

	//OMA 重构后的代码

	switch (EstimatKind)
	{
		
		case EstimatKind_SendCard:
		{
			// 发牌后，估计胡牌，提牌，杠牌
			//胡牌判断
			if (m_bEnjoinChiHu[wCenterUser]==false &&m_bPlayStatus[wCenterUser] && !m_GameLogic.IsMagicCard(cbCenterCard))// 如果打出的是钻牌不能吃胡
			{
 				CChiHuRight chr;
				BYTE cbWeaveCount=m_cbWeaveItemCount[wCenterUser];
				m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],cbWeaveCount,cbCenterCard,chr);
			}

			//杠牌判断
			if (m_cbLeftCardCount>0) 
			{
				// 估计自己手上牌是否可以杠
				tagGangCardResult GangCardResult;
				ZeroMemory(&GangCardResult,sizeof(GangCardResult));
				m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
					m_cbWeaveItemCount[wCenterUser],GangCardResult);
			}
			 
			// 提牌分析
			tagTICardResult TICardResult; 
			ZeroMemory(&TICardResult,sizeof(TICardResult));
			m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],
				m_WeaveItemArray[wCenterUser],m_cbWeaveItemCount[wCenterUser],
				TICardResult);

			break;
		}
		case EstimatKind_OutCard:
		{
			//动作判断
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				//用户过滤,跳过自己,跳过不在游戏中的用户,跳过打出听用的用户
				if (wCenterUser==i||!m_bPlayStatus[i] || m_bOutMagicCard[i]) continue;

				//碰贴杠判断
				if (m_bEnjoinChiPeng[i]==false)
				{
					//碰牌判断
					m_cbUserAction[i]|=m_GameLogic.EstimatePengCard(m_cbCardIndex[i],cbCenterCard);
					//贴牌判断
					m_cbUserAction[i]|=m_GameLogic.EstimateTiePaiCard(m_cbCardIndex[i],cbCenterCard);
					//杠牌判断
					if (m_cbLeftCardCount>0) 
					{
						m_cbUserAction[i]|=m_GameLogic.EstimateGangCard(m_cbCardIndex[i],cbCenterCard);
					}
				}

				//胡牌判断
				if (m_bEnjoinChiHu[i]==false &&m_bPlayStatus[i] && !m_GameLogic.IsMagicCard(cbCenterCard))// 如果打出的是钻牌不能吃胡
				{
					//吃胡判断
					CChiHuRight chr;
					BYTE cbWeaveCount=m_cbWeaveItemCount[i];
					m_cbUserAction[i]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i],m_WeaveItemArray[i],cbWeaveCount,cbCenterCard,chr);
				}

				//结果汇总
				if (m_cbUserAction[i]!=WIK_NULL) 
					bAroseAction=true;
			}
			
			break;
		}
		case EstimatKind_TICard:
		{
			//杠牌判断
			if (m_cbLeftCardCount>0) 
			{
				// 估计自己手上牌是否可以杠
				tagGangCardResult GangCardResult;
				m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
					m_cbWeaveItemCount[wCenterUser],GangCardResult);
			}

			//胡牌判断
			if (m_bEnjoinChiHu[wCenterUser]==false &&m_bPlayStatus[wCenterUser] && !m_GameLogic.IsMagicCard(cbCenterCard))// 如果打出的是钻牌不能吃胡
			{
				//吃胡判断
				CChiHuRight chr;
				BYTE cbWeaveCount=m_cbWeaveItemCount[wCenterUser];
				m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],cbWeaveCount,cbCenterCard,chr);
			}

			break;
		}
		case EstimatKind_TIECard:
		case EstimatKind_PENGCard:
		{
			// 贴牌或者碰牌后，估计是否可以提牌、杠牌

			//提牌判断
			tagTICardResult TICardResult;
			m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],
														m_WeaveItemArray[wCenterUser],m_cbWeaveItemCount[wCenterUser],
														TICardResult);
			//杠牌判断
			if (m_cbLeftCardCount>0) 
			{
				// 估计自己手上牌是否可以杠
				tagGangCardResult GangCardResult;
				m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
					m_cbWeaveItemCount[wCenterUser],GangCardResult);
			}

			//结果汇总
 			if (m_cbUserAction[wCenterUser]!=WIK_NULL) 
				bAroseAction=true;

			break;
		}
		case EstimatKind_PengGangCard:
		{
			// 杠牌后判断

			//提牌判断
			tagTICardResult TICardResult;
			m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],
				m_WeaveItemArray[wCenterUser],m_cbWeaveItemCount[wCenterUser],
				TICardResult);

			//胡牌判断
			if (m_bEnjoinChiHu[wCenterUser]==false &&m_bPlayStatus[wCenterUser] && !m_GameLogic.IsMagicCard(cbCenterCard))// 如果打出的是钻牌不能吃胡
			{
				//吃胡判断
				CChiHuRight chr;
				BYTE cbWeaveCount=m_cbWeaveItemCount[wCenterUser];
				m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],cbWeaveCount,cbCenterCard,chr);
			}

			//结果汇总
 			if (m_cbUserAction[wCenterUser]!=WIK_NULL) 
				bAroseAction=true;


			break;
		}

	}
	//结果处理
	if (bAroseAction==true) 
	{
 		//设置变量
		m_wProvideUser=wCenterUser;
		m_cbProvideCard=cbCenterCard;
		m_wResumeUser=m_wCurrentUser;
		m_wCurrentUser=INVALID_CHAIR;

		//发送提示
		SendOperateNotify();

		return true;
	}

	return false;

	//OMA 重构结束
	//////////////////////////////////////////////////////////////////////////
}

//
void CTableFrameSink::ProcessChiHuUser( WORD wChairId, bool bGiveUp )
{
	if( !bGiveUp )
	{
		//引用权位s
		CChiHuRight &chr = m_ChiHuRight[wChairId];
	
		DWORD Right;
		chr.GetRightData(&Right,1);
		FiltrateRight( wChairId,chr );
		WORD wFanShu = m_GameLogic.GetChiHuActionRank( chr );
		LONG score = (LONG)pow(2.0,wFanShu-1);
	

		// 不处理杠分
		LONG lChiHuScore = score*m_pGameServiceOption->lCellScore;
		if( m_wProvideUser != wChairId ) // 点炮或者引杠
		{
			m_wLostFanShu[m_wProvideUser][wChairId] = lChiHuScore; // 点炮用户扣分
		}
		else
		{
			for( WORD i = 0; i < GAME_PLAYER; i++ ) // 自摸扣未胡牌着分数
			{
				if( !m_bPlayStatus[i] || i == wChairId ) continue;

				m_wLostFanShu[i][wChairId] = lChiHuScore;
			}
		}

	//////////////////////////////////////////////////////////////////////////
		//  得分
		if( m_wProvideUser == wChairId ) // 自摸
		{
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
				if( !m_bPlayStatus[i] || i == wChairId ) continue;

				// 逃跑用户不再扣分
				if(m_bPlayleft[i] == true) continue;
				//胡牌分
				m_lGameScore[i] -= lChiHuScore;
				m_lGameScore[wChairId] += lChiHuScore;
			}
		}
		//点炮
		else
		{
			m_lGameScore[m_wProvideUser] -= lChiHuScore;
			m_lGameScore[wChairId] += lChiHuScore;
		}

		//设置变量
		m_wProvider[wChairId] = m_wProvideUser;
		m_wWinOrder[m_cbWinCount++] = wChairId;
		//发送消息
		CMD_S_ChiHu ChiHu;
		ChiHu.wChiHuUser = wChairId;
		ChiHu.wProviderUser = m_wProvideUser;
		ChiHu.bGangStatus = m_bGangStatus;
		ChiHu.bTIStatus = m_bTIStatus ;// 设置提牌状态
		ChiHu.lGameScore = m_lGameScore[wChairId];
		ChiHu.cbCardCount = m_GameLogic.GetCardCount( m_cbCardIndex[wChairId] );
		ChiHu.cbChiHuCard = m_cbProvideCard;
		ChiHu.cbWinOrder = m_cbWinCount;
		m_pITableFrame->SendTableData( INVALID_CHAIR,SUB_S_CHI_HU,&ChiHu,sizeof(ChiHu) );
		m_pITableFrame->SendLookonData( INVALID_CHAIR,SUB_S_CHI_HU,&ChiHu,sizeof(ChiHu) );

		//设置变量
		m_bPlayStatus[wChairId] = false;

	}

	return;
}

//
void CTableFrameSink::FiltrateRight( WORD wChairId,CChiHuRight &chr )
{

	//权位增加
	//抢杠
	if( m_wCurrentUser == INVALID_CHAIR && m_bGangStatus )
	{
		chr |= CHR_QIANG_GANG;
	}
	//天胡
	if( m_cbSendCardCount == 2 && m_cbOutCardCount == 0 ) // 多发了一张作为牌精
	{
		chr.SetEmpty();
		chr |= CHR_TIAN_HU;
	}
	//地胡
	else if( m_cbSendCardCount == 2 && m_cbOutCardCount == 1 )
	{
		chr.SetEmpty();
		chr |= CHR_DI_HU;
	}

	//附加权位
	//杠上花
	if( m_wCurrentUser==wChairId && m_bGangStatus )
	{
		chr |= CHR_GANG_KAI;
	}
	//杠上炮
	if( m_bGangOutStatus && !m_bGangStatus )
	{
		chr |= CHR_GANG_SHANG_PAO;
	}
 
	//根加番
	switch (m_cbGenCount[wChairId])
	{
	case 1:
		chr |= CHR_GENG_COUNT_ONE;
			break;
	case 2:
		chr |= CHR_GENG_COUNT_TWO;
		break;
	case 3:
		chr |= CHR_GENG_COUNT_THREE;
		break;
	case 4:
		chr |= CHR_GENG_COUNT_FOUR;
		break;
	}

}
 

//////////////////////////////////////////////////////////////////////////
