#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const WORD			CTableFrameSink::m_wPlayerCount=GAME_PLAYER;			//��Ϸ����
const enStartMode	CTableFrameSink::m_GameStartMode=enStartMode_FullReady;	//��ʼģʽ

//////////////////////////////////////////////////////////////////////////

//���캯��
CTableFrameSink::CTableFrameSink()
{
	//��Ϸ����
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

	//������Ϣ
	m_cbOutCardData=0;
	m_cbOutCardCount=0;
	m_wOutCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbDiscardCard,sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount,sizeof(m_cbDiscardCount));

	//������Ϣ
	m_wHeapHand = INVALID_CHAIR;
	m_wHeapTail = INVALID_CHAIR;
	ZeroMemory(m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));

	//������Ϣ
	m_cbSendCardData=0;
	m_cbSendCardCount=0;
	m_cbLeftCardCount=0;
	ZeroMemory(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));

	//���б���
	m_cbProvideCard=0;
	m_wResumeUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	m_wProvideUser=INVALID_CHAIR;

	//״̬����
	m_bSendStatus=false;
	m_bGangStatus = false;
	m_bGangOutStatus = false;
	ZeroMemory(m_bEnjoinChiHu,sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng,sizeof(m_bEnjoinChiPeng));

	//�û�״̬
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

	//����˿�
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));
	ZeroMemory(m_cbWeaveItemCount,sizeof(m_cbWeaveItemCount));

	//������Ϣ
	m_cbChiHuCard=0;
	ZeroMemory( m_dwChiHuKind,sizeof(m_dwChiHuKind) );
	memset( m_wProvider,INVALID_CHAIR,sizeof(m_wProvider) );

	//�������
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;

	//���ֱ�־
	m_bKaiJu = true;
#ifdef DEBUG
	 // ����̨���
	AllocConsole();
	 //�ļ����
	if((freopen("Majhonelog.txt", "w+", stdout)) == NULL)
			exit(-1);
#endif
	return;
}

//��������
CTableFrameSink::~CTableFrameSink(void)
{
#ifdef DEBUG
	// �رտ���̨
	FreeConsole();
	
#endif

}

//�ӿڲ�ѯ
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE(ITableUserAction,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ��
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL)
		return false;

	//��ȡ����
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	return true;
}

//��λ����
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	//��Ϸ����
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

	//������Ϣ
	m_cbOutCardData=0;
	m_cbOutCardCount=0;
	m_wOutCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbDiscardCard,sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount,sizeof(m_cbDiscardCount));

	//������Ϣ
	m_wHeapHand = INVALID_CHAIR;
	m_wHeapTail = INVALID_CHAIR;
	ZeroMemory(m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));

	//������Ϣ
	m_cbSendCardData=0;
	m_cbSendCardCount=0;
	m_cbLeftCardCount=0;
	ZeroMemory(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));

	//���б���
	m_cbProvideCard=0;
	m_wResumeUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;
	m_wProvideUser=INVALID_CHAIR;
	
	m_wBankerUser = (m_bKaiJu)?INVALID_CHAIR:m_wBankerUser;
	

	//״̬����
	m_bSendStatus=false;
	m_bGangStatus = false;
	m_bTIStatus = false;
	m_bGangOutStatus = false;

	ZeroMemory(m_bEnjoinChiHu,sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng,sizeof(m_bEnjoinChiPeng));

	//�û�״̬
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

	//����˿�
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));
	ZeroMemory(m_cbWeaveItemCount,sizeof(m_cbWeaveItemCount));

	//������Ϣ
	m_cbChiHuCard=0;
	ZeroMemory(m_dwChiHuKind,sizeof(m_dwChiHuKind));
	
	for( WORD i = 0; i < GAME_PLAYER; i++ )
		m_ChiHuRight[i].SetEmpty();

	return;
}

//��ʼģʽ
enStartMode __cdecl CTableFrameSink::GetGameStartMode()
{
	return m_GameStartMode;
}

//��Ϸ״̬
bool __cdecl CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	return true;
}

//��Ϸ��ʼ
bool __cdecl CTableFrameSink::OnEventGameStart()
{

	//����״̬
	m_pITableFrame->SetGameStatus(GS_MJ_PLAY);

	// ״̬��λ

	ZeroMemory(m_bOutMagicCard,sizeof(m_bOutMagicCard));
	ZeroMemory(m_bEnjoinChiHu,sizeof(m_bEnjoinChiHu));
	ZeroMemory(m_bEnjoinChiPeng,sizeof(m_bEnjoinChiPeng));
	ZeroMemory(m_bPlayleft,sizeof(m_bPlayleft));


	//�����˿�
	m_lSiceCount = MAKELONG(MAKEWORD(rand()%6+1,rand()%6+1),MAKEWORD(rand()%6+1,rand()%6+1));
	m_cbLeftCardCount=CountArray(m_cbRepertoryCard);
	m_GameLogic.RandCardData(m_cbRepertoryCard,CountArray(m_cbRepertoryCard));

  
	if (m_bKaiJu)
	{
		m_wBankerUser = ((BYTE)(m_lSiceCount>>24)+(BYTE)(m_lSiceCount>>16)-1)%GAME_PLAYER;
		m_bKaiJu = false; // ���ÿ��ֿ�ʼ  ��һ�������Ⱥ��Ƶ��û���ׯ 

	}


#ifdef DEBUG
	//test
	BYTE byTest[] = {
	
		0x17,0x12,0x22,0x16, //oma  ���4��
		0x06,0x29,0x08,0x25,0x04,0x29,0x09,0x13,0x07,						
		0x07,0x04,0x03,0x07,0x25,0x07,0x05,0x26,0x22,						
		0x08,0x04,0x29,0x06,0x06,0x05,0x17,0x19,0x05,						
		0x08,0x28,0x11,0x28,0x06,0x27,0x24,0x27,0x02,	
		0x22,0x14,0x05,0x12,0x04,0x24,0x11,0x03,0x16,						
		0x14,0x01,0x18,0x25,0x11
		,0x11 // oma �ƾ�
		,0x19, // oma ׯ�ҵ�14����


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

		
		//0x23,0x15,0x22,0x29, //oma  ���4��
		//0x26,0x23,0x26,0x15,0x04,0x26,0x11,0x27,0x08,						
		//0x22,0x04,0x03,0x24,0x15,0x15,0x05,0x21,0x21,						
		//0x23,0x06,0x07,0x19,0x09,0x05,0x27,0x14,0x07,						
		//0x16,0x16,0x14,0x13,0x17,0x27,0x21,0x27,0x08,	
		//0x21,0x07,0x08,0x11,0x13,0x24,0x11,0x04,0x23,						
		//0x22,0x29,0x29,0x19,0x19
		//,0x11 // oma �ƾ�
		//,0x28, // oma ׯ�ҵ�14����
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
	m_wBankerUser = 2;
#endif

	//�ַ��˿�
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

	//�����˿�
	m_cbSendCardCount++;
	m_cbSendCardData=m_cbRepertoryCard[--m_cbLeftCardCount];
	m_cbCardIndex[m_wBankerUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;


	//  ����������
	
	m_cbSendCardCount++;
	BYTE cbTingYong = 0,cbPaiJing = 0;
	cbPaiJing = m_cbRepertoryCard[--m_cbLeftCardCount];
	
	m_GameLogic.m_PaiJing.m_cbPaiJingCard = cbPaiJing;
	
	BYTE cbColor = cbPaiJing&MASK_COLOR;
	BYTE cbValue = cbPaiJing&MASK_VALUE;
	
	cbValue = cbValue%9+1;
	cbTingYong = (cbColor | cbValue);
	m_GameLogic.m_PaiJing.m_cbTingYongCard = cbTingYong;

	m_GameLogic.SetMagicIndex(m_GameLogic.SwitchToCardIndex(cbTingYong));


	//���ñ���
	m_cbProvideCard=0;
	m_wProvideUser=INVALID_CHAIR;
	m_wCurrentUser=m_wBankerUser;

	//������Ϣ
	WORD wSice = WORD(m_lSiceCount&0xffff);
	BYTE cbSiceTakeCount= HIBYTE(wSice)+LOBYTE(wSice);
	WORD wTakeChairID=(m_wBankerUser+cbSiceTakeCount-1)%GAME_PLAYER;
	BYTE cbTakeCount=MAX_REPERTORY-m_cbLeftCardCount;
	for (WORD i=0;i<GAME_PLAYER;i++)
	{
		//������Ŀ
		BYTE cbValidCount=HEAP_FULL_COUNT-m_cbHeapCardInfo[wTakeChairID][1]-((i==0)?(cbSiceTakeCount)*2:0);
		BYTE cbRemoveCount=__min(cbValidCount,cbTakeCount);

		//��ȡ�˿�
		cbTakeCount-=cbRemoveCount;
		m_cbHeapCardInfo[wTakeChairID][(i==0)?1:0]+=cbRemoveCount;

		//����ж�
		if (cbTakeCount==0)
		{
			m_wHeapHand=wTakeChairID;
			m_wHeapTail=(m_wBankerUser+cbSiceTakeCount-1)%GAME_PLAYER;
			//��ͷ����4��,�չ�108����
			m_cbHeapCardInfo[m_wHeapHand][0] -= 4;
			break;
		}
		//�л�����
		wTakeChairID=(wTakeChairID+1)%GAME_PLAYER;
	}

	//��������
	bool bAroseAction=false;
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		//ׯ���ж�
		if (i==m_wBankerUser)
		{
			//�����ж�
			tagGangCardResult GangCardResult;
			m_cbUserAction[i]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[i],NULL,0,GangCardResult);

			// ׯ�ҿ�ʼ�������������ƣ���˲���������

			//�����ж�
			CChiHuRight chr;
			m_cbCardIndex[i][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]--;
			m_cbUserAction[i]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i],NULL,0,m_cbSendCardData,chr);
			m_cbCardIndex[i][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;
		}
	}

	//��������
	CMD_S_GameStart GameStart;
	GameStart.lSiceCount=m_lSiceCount;
	GameStart.wBankerUser=m_wBankerUser;
	GameStart.wCurrentUser=m_wCurrentUser;
	GameStart.wHeapHand = m_wHeapHand;
	GameStart.wHeapTail = m_wHeapTail;
	GameStart.cbLeftCardCount = m_cbLeftCardCount;
	GameStart.bKaiJu = m_bKaiJu;

	CopyMemory(GameStart.cbHeapCardInfo,m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));

	//��������
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if( !m_bPlayStatus[i] ) continue;

		//���ñ���
		GameStart.cbUserAction=m_cbUserAction[i];
		m_GameLogic.SwitchToCardData(m_cbCardIndex[i],GameStart.cbCardData);

		//��������
		m_pITableFrame->SendTableData(i,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
		m_pITableFrame->SendLookonData(i,SUB_S_GAME_START,&GameStart,sizeof(GameStart));
	}

	// �����ƾ�
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_PAI_JING,&m_GameLogic.m_PaiJing,sizeof(m_GameLogic.m_PaiJing));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_PAI_JING,&m_GameLogic.m_PaiJing,sizeof(m_GameLogic.m_PaiJing));

	return true;
}

//��Ϸ����
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	switch (cbReason)
	{
	case GER_NORMAL:		//�������
		{
			//��������
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.wLeftUser = INVALID_CHAIR;

			//������Ϣ
			WORD wWinner = INVALID_CHAIR;
			BYTE cbLeftUserCount = 0;			//�ж��Ƿ�����
			bool bUserStatus[GAME_PLAYER];		//
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				GameEnd.cbCardCount[i]=m_GameLogic.SwitchToCardData(m_cbCardIndex[i],GameEnd.cbCardData[i]);
				m_ChiHuRight[i].GetRightData( &GameEnd.dwChiHuRight[i],MAX_RIGHT_COUNT );
				//���������
				if( m_ChiHuRight[i].IsEmpty() )
				{
					cbLeftUserCount++;
				}
				//��ǰ���״̬

				if( NULL != m_pITableFrame->GetServerUserItem(i) )
				{
					bUserStatus[i] = true;
				}
				else
				{
					bUserStatus[i] = false;
				}
			}
			
			LONG lHuaZhuScore[GAME_PLAYER];
			LONG lChaJiaoScore[GAME_PLAYER];
			LONG lGangScore[GAME_PLAYER];
			ZeroMemory( lGangScore,sizeof(lGangScore) );
			ZeroMemory( lHuaZhuScore,sizeof(lHuaZhuScore) );
			ZeroMemory( lChaJiaoScore,sizeof(lChaJiaoScore) );

			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
 				//if( cbLeftUserCount>1 && m_bPlayStatus[i] && m_ChiHuRight[i].IsEmpty() )
				//if( cbLeftUserCount>1 && m_bPlayStatus[i] && m_ChiHuRight[i].IsEmpty() )
 				//{

					TCHAR pMsg[128] = TEXT("");
					_snprintf(pMsg,sizeof(pMsg),TEXT("��ʼ���û�: %d �黨��"),i);
					CTraceService::TraceString( pMsg,TraceLevel_Debug);

					// ������(�Ѿ��⳥),�Ѿ������ߣ�����У����黨��
					if ( m_bPlayleft[i] || !m_bPlayStatus[i])
					{
						TCHAR pMsg[128] = TEXT("");
						_snprintf(pMsg,sizeof(pMsg),TEXT("�û�: %d ���黨�� �����"),i);

						CTraceService::TraceString( pMsg,TraceLevel_Debug);
						//bHuaZhu = true;  //�����߰��ջ�����
						continue;
					}

					//��� �黨��
					bool bHuaZhu = m_GameLogic.IsHuaZhu(m_cbCardIndex[i],m_WeaveItemArray[i],m_cbWeaveItemCount[i]);
 					if(m_bOutMagicCard[i])// ����������
					{
						bHuaZhu = false;//	���㻨��
						CTraceService::TraceString(TEXT("�黨�� ��������� ���㻨��"),TraceLevel_Debug);
					}
 
					if( bHuaZhu ) 
					{
 						TCHAR msg[128] = TEXT("");
						_snprintf(msg,sizeof(msg),TEXT("�û�: %d �ǻ���"),i);
						CTraceService::TraceString(msg,TraceLevel_Debug);
 
						//��������ǻ�������������
						for( WORD j = 0; j < GAME_PLAYER; j++ )
						{
#if 1						//���⳥(�Լ� �������ߡ��Ѿ�������) 
 							//if( j == i || m_bPlayleft[j] || !bUserStatus[j]) 
							if( j == i  || m_bPlayleft[j] )
 							{
  								TCHAR msg[256] = TEXT("");
								_snprintf_s(msg,sizeof(msg),TEXT("�黨�� ���⳥(�Լ� ��������)"));
								CTraceService::TraceString(msg,TraceLevel_Debug);
 								continue;
							}
 
							// �ǻ�����ҵõ��⳥
							if( !m_GameLogic.IsHuaZhu(m_cbCardIndex[j],m_WeaveItemArray[j],m_cbWeaveItemCount[j]) )
							{
								LONG maxScore = (LONG)pow(2.0,MAX_CHIHU_FANSU-1);
								lHuaZhuScore[i] -= m_pGameServiceOption->lCellScore*maxScore;
								lHuaZhuScore[j] += m_pGameServiceOption->lCellScore*maxScore;

								TCHAR msg[256] = TEXT("");
								_snprintf_s(msg,sizeof(msg),TEXT("�õ��⳥��ң�%d ��ֵ��%d"),j,lHuaZhuScore[j]);
								CTraceService::TraceString(msg,TraceLevel_Debug);

							}

 
#else
							if( j == i || !m_bPlayStatus[j] ) continue;
							if( !m_GameLogic.IsHuaZhu(m_cbCardIndex[j],m_WeaveItemArray[j],m_cbWeaveItemCount[j]) )
							{

								LONG maxScore = (LONG)pow(2.0,MAX_CHIHU_FANSU-1);
								lHuaZhuScore[i] -= m_pGameServiceOption->lCellScore*maxScore;
								lHuaZhuScore[j] += m_pGameServiceOption->lCellScore*maxScore;

							}

#endif 
						}
						CTraceService::TraceString(TEXT("�ǻ��� ����У������һ���û�"),TraceLevel_Debug);

						continue; //�ǻ��� �����
					}
 					// �黨�����

					CTraceService::TraceString(TEXT("���ǻ��� ��ʼ���"),TraceLevel_Debug);
			
					// ��ʼ���
					bool bChajiao;
					if (m_bOutMagicCard[i]) // ������������
					{
						bChajiao = false; // ����д���
						bHuaZhu = false;  
					}else
					{
						// δ������õ������
						 bChajiao = m_GameLogic.IsTingCard( m_cbCardIndex[i],m_WeaveItemArray[i],m_cbWeaveItemCount[i] );
					}
					

					//�޽� �� ���ǻ���

					if(!bChajiao && !bHuaZhu)//�޽�
					{
						//����
						//if( !bHuaZhu ) // 
						//{
							//û���Ƶ���ң������ã�������Ƶ�������Ŀ��ܷ���
							for( WORD j = 0; j < GAME_PLAYER; j++ )
							{
								// �����Լ����Ѿ����Ƶ��û����⣬������Ҳ���
 								if( j == i || !m_bPlayStatus[j] || m_bPlayleft[j] )
								{

									TCHAR msg[256] = TEXT("");
									_snprintf(msg,sizeof(msg),TEXT(" ���⳥ %d �û�"),j);
									CTraceService::TraceString( msg,TraceLevel_Debug);
						
									continue;
								}

								if( m_GameLogic.IsTingCard(m_cbCardIndex[j],m_WeaveItemArray[j],m_cbWeaveItemCount[j]) )
								{
									//���������
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
											//ȡ�����
											if( wFanShuTemp > wFanShu ) wFanShu = wFanShuTemp;
										}
									}

									//wFanShu = (wFanShu == 0)?1:wFanShu;

									LONG score = (LONG)pow(2.0,wFanShu-1);
																		
									// �Ѿ������û����ò�з�
									//�����Ǯ
									lChaJiaoScore[i] -= m_pGameServiceOption->lCellScore*score;
									lChaJiaoScore[j] += m_pGameServiceOption->lCellScore*score;

									TCHAR msg[256] = TEXT("");
									_snprintf(msg,sizeof(msg),TEXT("��� ���û� %d �⳥ %d (���� %d)"),j,m_pGameServiceOption->lCellScore*score,wFanShu);
									CTraceService::TraceString( msg,TraceLevel_Debug);


								}else
								{
									TCHAR msg[256] = TEXT("");
									_snprintf(msg,sizeof(msg),TEXT("��� �û� %d �޽�"),j);
									CTraceService::TraceString( msg,TraceLevel_Debug);

								}
							}
						//}
					}
					CTraceService::TraceString(TEXT(" ��н�������һ���û��黨�� ���"),TraceLevel_Debug);

					//// �������
				//}

			}

			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{

				//������ܷ�
				// �����ظ����������û�����
				if(	m_bPlayleft[i])
				{
					continue;
				} 			

				m_lGameScore[i] += lHuaZhuScore[i];
				m_lGameScore[i] += lChaJiaoScore[i];


				//��ֹ����
				IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(i);
				
				if( GAME_GENRE_SCORE == m_pGameServiceOption->wServerType 
					&&m_lGameScore[i] < 0L && 
					-m_lGameScore[i] > pUserItem->GetUserScore()->lScore )
				{
					// �������
					m_lGameScore[i] = -pUserItem->GetUserScore()->lScore;
				}



			}


			//ͳ�ƻ���
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				if( NULL == m_pITableFrame->GetServerUserItem(i) ) continue;

				//���û���
				if( GAME_GENRE_SCORE != m_pGameServiceOption->wServerType )
				{

#if 0
 // ���չ̶���Ŀ��˰
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
// ���չ̶�������˰
					if (m_lGameScore[i]>0L)
					{
						m_lGameTax[i] = (LONG)((LONGLONG)m_lGameScore[i]*m_pGameServiceOption->wRevenue/100L);
						m_lGameScore[i] -= m_lGameTax[i];
					}
#endif 	
				}
		
				enScoreKind ScoreKind;
				if( m_lGameScore[i] > 0L ) ScoreKind = enScoreKind_Win;
				else if( m_lGameScore[i] < 0L ) ScoreKind = enScoreKind_Lost;
				else ScoreKind = enScoreKind_Draw;

				//д�����
				m_pITableFrame->WriteUserScore(i,m_lGameScore[i],m_lGameTax[i],ScoreKind);
			}
#if 0
			// oma add 
			for (int k = 0;k<GAME_PLAYER;k++)
			{
				IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(k);
				// ���㵱�ֽ��������
				LONG totalScore  =  pUserItem->GetUserScore()->lScore;

				TCHAR printmsg[512] = TEXT("");
				_snprintf(printmsg,sizeof(printmsg),TEXT("������Ϸ�������û�������%d ,��ǰ�ͷִ�����%d ��Ϸ���ͣ�%d "),
					totalScore,pUserItem->GetUserScore()->lGrantCount,m_pGameServiceOption->wServerType);
				CTraceService::TraceString(printmsg,TraceLevel_Debug);

				if( GAME_GENRE_SCORE == m_pGameServiceOption->wServerType
					&& totalScore < m_pGameServiceOption->lLessScore 
					&& pUserItem->GetUserScore()->lGrantCount > 0 )
				{

					// �ͷ֣�ÿ���� GRANT_SCORE_VALUE ��

					TCHAR msg[512] = TEXT("");
					_snprintf(msg,sizeof(msg),TEXT("��ֻ�� %d ����Ŷ���ף�%d ���͸���Ŷ����,ʣ���ͷִ�����%d ������Ŷ"),
						totalScore,GRANT_SCORE_VALUE,--pUserItem->GetUserData()->UserScoreInfo.lGrantCount);
					CTraceService::TraceString(msg,TraceLevel_Debug);

					//totalScore+= GRANT_SCORE_VALUE;
					// ֪ͨ�ͻ����û�
					--pUserItem->GetUserData()->UserScoreInfo.lGrantCount;
					CMD_S_GrantScore GrantScore;
					
					_snprintf(GrantScore.messageContent,sizeof(GrantScore.messageContent),TEXT(" ��Ļ��ֲ��� %d ���ˣ����ǵ�%d����%d��(ÿ�� %d ��)"),
						m_pGameServiceOption->lLessScore ,GRANT_SCORE_COUNT-pUserItem->GetUserData()->UserScoreInfo.lGrantCount,GRANT_SCORE_VALUE,GRANT_SCORE_COUNT);
 
					m_pITableFrame->SendTableData(k,SUB_S_GRANT_SCORE,&GrantScore,sizeof(GrantScore));
					//д�����
					m_pITableFrame->WriteUserScore(k,GRANT_SCORE_VALUE,0,enScoreKind_Win);// ��˰0
				}

			}
			// oma add end 
#endif 
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

			//���ͽ�����Ϣ
			m_pITableFrame->SendTableData( INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd) );
			m_pITableFrame->SendLookonData( INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd) );

			//������Ϸ
			m_pITableFrame->ConcludeGame();
			return true;
		}
	case GER_DISMISS:		//��Ϸ��ɢ
		{
			//��������
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.wLeftUser = INVALID_CHAIR;

			//���ñ���
			memset( GameEnd.wProvideUser,INVALID_CHAIR,sizeof(GameEnd.wProvideUser) );

			//�����˿�
			for (WORD i=0;i<GAME_PLAYER;i++)
			{
				GameEnd.cbCardCount[i]=m_GameLogic.SwitchToCardData(m_cbCardIndex[i],GameEnd.cbCardData[i]);
			}

			//������Ϣ
			m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));
			m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_GAME_END,&GameEnd,sizeof(GameEnd));

			//������Ϸ
			m_pITableFrame->ConcludeGame();

			return true;
		}
	case GER_USER_LEFT:		//�û�ǿ��
		{
			//��������
			CMD_S_GameEnd GameEnd;
			ZeroMemory(&GameEnd,sizeof(GameEnd));
			GameEnd.wLeftUser = wChairID;

//       ��¼�������û�
			m_bPlayleft[wChairID] = true; 
		
			if(m_wCurrentUser == wChairID )
			{
				m_wResumeUser = wChairID;
				m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
				while( !m_bPlayStatus[m_wResumeUser] ) m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
				DispatchCardData(m_wResumeUser,false);
			}
// ���ܿ� ��󷬷���

			m_bPlayStatus[wChairID] = false;
			LONG maxScore = (LONG)pow(2.0,MAX_CHIHU_FANSU-1);
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
				if( !m_bPlayleft[i] ) // ��������Ҿ��ɻ���⳥
				{
					m_lGameScore[i] += maxScore*m_pGameServiceOption->lCellScore;
					m_lGameScore[wChairID] -= maxScore*m_pGameServiceOption->lCellScore;
				}
			}

				m_pITableFrame->GetServerUserItem(wChairID);
				
				//���û���
				LONG lGameTax = 0L;
				if( GAME_GENRE_SCORE == m_pGameServiceOption->wServerType )
				{
					if (m_lGameScore[wChairID]>0L)
					{
						lGameTax = (LONG)((LONGLONG)m_lGameScore[wChairID]*m_pGameServiceOption->wRevenue/1000L);
						m_lGameScore[wChairID] -= lGameTax;
					}
					else
					{
						//��ֹ����
						IServerUserItem *pUserItem = m_pITableFrame->GetServerUserItem(wChairID);
						if( GAME_GENRE_SCORE==m_pGameServiceOption->wServerType && -m_lGameScore[wChairID] > pUserItem->GetUserScore()->lScore )
							m_lGameScore[wChairID] = -pUserItem->GetUserScore()->lScore;
					}
				}

				enScoreKind ScoreKind = enScoreKind_Flee;;

				//д�����
				m_pITableFrame->WriteUserScore(wChairID,m_lGameScore[wChairID],lGameTax,ScoreKind);
			return true;
		}
	}

	//�������
	ASSERT(FALSE);
	return false;
}

//���ͳ���
bool __cdecl CTableFrameSink::SendGameScene(WORD wChiarID, IServerUserItem * pIServerUserItem, BYTE cbGameStatus, bool bSendSecret)
{
	switch (cbGameStatus)
	{
	case GS_MJ_FREE:	//����״̬
		{
			//��������
			CMD_S_StatusFree StatusFree;
			memset(&StatusFree,0,sizeof(StatusFree));

			//��������
			StatusFree.wBankerUser=m_wBankerUser;
			StatusFree.lCellScore=m_pGameServiceOption->lCellScore;
			CopyMemory(StatusFree.bTrustee,m_bTrustee,sizeof(m_bTrustee));

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusFree,sizeof(StatusFree));
		}
	case GS_MJ_PLAY:	//��Ϸ״̬
		{
			//��������
			CMD_S_StatusPlay StatusPlay;
			memset(&StatusPlay,0,sizeof(StatusPlay));

			//��Ϸ����
			StatusPlay.wBankerUser=m_wBankerUser;
			StatusPlay.wCurrentUser=m_wCurrentUser;
			StatusPlay.lCellScore=m_pGameServiceOption->lCellScore;
			CopyMemory(StatusPlay.bTrustee,m_bTrustee,sizeof(m_bTrustee));
			CopyMemory(StatusPlay.wWinOrder,m_wWinOrder,sizeof(m_wWinOrder));

			//״̬����
			StatusPlay.cbActionCard=m_cbProvideCard;
			StatusPlay.cbLeftCardCount=m_cbLeftCardCount;
			StatusPlay.cbActionMask=(m_bResponse[wChiarID]==false)?m_cbUserAction[wChiarID]:WIK_NULL;

			//��ʷ��¼
			StatusPlay.wOutCardUser=m_wOutCardUser;
			StatusPlay.cbOutCardData=m_cbOutCardData;
			CopyMemory(StatusPlay.cbDiscardCard,m_cbDiscardCard,sizeof(StatusPlay.cbDiscardCard));
			CopyMemory(StatusPlay.cbDiscardCount,m_cbDiscardCount,sizeof(StatusPlay.cbDiscardCount));

			//����˿�
			CopyMemory(StatusPlay.WeaveItemArray,m_WeaveItemArray,sizeof(m_WeaveItemArray));
			CopyMemory(StatusPlay.cbWeaveCount,m_cbWeaveItemCount,sizeof(m_cbWeaveItemCount));

			//������Ϣ
			StatusPlay.wHeapHand = m_wHeapHand;
			StatusPlay.wHeapTail = m_wHeapTail;
			CopyMemory(StatusPlay.cbHeapCardInfo,m_cbHeapCardInfo,sizeof(m_cbHeapCardInfo));
			CopyMemory(&StatusPlay.PaiJin,&m_GameLogic.m_PaiJing,sizeof(m_GameLogic.m_PaiJing));

			//�˿�����
			StatusPlay.cbCardCount=m_GameLogic.SwitchToCardData(m_cbCardIndex[wChiarID],StatusPlay.cbCardData);
			StatusPlay.cbSendCardData=((m_cbSendCardData!=0)&&(m_wProvideUser==wChiarID))?m_cbSendCardData:0x00;

			//���ͳ���
			return m_pITableFrame->SendGameScene(pIServerUserItem,&StatusPlay,sizeof(StatusPlay));
		}
	}

	return false;
}

//��ʱ���¼�
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	return false;
}

//��Ϸ��Ϣ����
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_C_OUT_CARD:		//������Ϣ
		{
			//Ч����Ϣ
			ASSERT(wDataSize==sizeof(CMD_C_OutCard));
			if (wDataSize!=sizeof(CMD_C_OutCard)) return false;

			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//��Ϣ����
			CMD_C_OutCard * pOutCard=(CMD_C_OutCard *)pDataBuffer;
			return OnUserOutCard(pUserData->wChairID,pOutCard->cbCardData);
		}
	case SUB_C_OPERATE_CARD:	//������Ϣ
		{
			//Ч����Ϣ
			ASSERT(wDataSize==sizeof(CMD_C_OperateCard));
			if (wDataSize!=sizeof(CMD_C_OperateCard)) return false;

			//�û�Ч��
			tagServerUserData * pUserData=pIServerUserItem->GetUserData();
			if (pUserData->cbUserStatus!=US_PLAY) return true;

			//��Ϣ����
			CMD_C_OperateCard * pOperateCard=(CMD_C_OperateCard *)pDataBuffer;
			return OnUserOperateCard(pUserData->wChairID,pOperateCard->cbOperateCode,pOperateCard->cbOperateCard);
		}
	case SUB_C_TRUSTEE:
		{
			CMD_C_Trustee *pTrustee =(CMD_C_Trustee *)pDataBuffer;
			if(wDataSize != sizeof(CMD_C_Trustee)) return false;

			//�û�Ч��
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

//�����Ϣ����
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserSitDown(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	return true;
}
//�û�ͬ��
bool __cdecl CTableFrameSink::OnActionUserReady(WORD wChairID,IServerUserItem * pIServerUserItem, void * pData, WORD wDataSize)
{
	//OMA START �Է����ͷֵ��û������ͷֲ���
	tagUserScore  &pUserScore = pIServerUserItem->GetUserData()->UserScoreInfo;
	if(pUserScore.lScore<m_pGameServiceOption->lLessScore
		&& pUserScore.lGrantCount>0)
	{
		// ��ִ�е������ʾ�������������ǻ����ͷִ���
		// �ͷ�
		m_pITableFrame->WriteUserScore(pIServerUserItem,m_pGameServiceOption->lLessScore,0,enScoreKind_Present,0);

		// ������Ϣ
		TCHAR szMessage[512]=TEXT("");
 		_snprintf(szMessage,sizeof(szMessage),TEXT("���ǵ�%d����%d�֣�ʣ���ͷִ���Ϊ%d ",GRANT_SCORE_COUNT-pUserScore.lGrantCount,m_pGameServiceOption->lLessScore,pUserScore.lGrantCount));
		for (WORD i=0;i<m_wPlayerCount;i++)
		{
			IServerUserItem *pIServerUserItem2 = NULL;
			if( pIServerUserItem2 = m_pITableFrame->GetServerUserItem(i) != NULL )
			{
				WORD wTYPE = SMT_INFO;
				if (pIServerUserItem == pIServerUserItem2)
				{
					//��ǰ�û���������Ϣ
					wTYPE |= SMT_EJECT;
				}
				m_pITableFrame->SendGameMessage(pIServerUserItem2,szMessage,wTYPE);
			}
		} 
	}
	// OMA END
	return true;
}

//�û�����
bool __cdecl CTableFrameSink::OnActionUserStandUp(WORD wChairID, IServerUserItem * pIServerUserItem, bool bLookonUser)
{
	//ׯ������
	if (bLookonUser==false)
	{
		m_bKaiJu = true;
		m_bTrustee[wChairID]=false;
		CMD_S_Trustee Trustee;
		Trustee.bTrustee=false;
		Trustee.wChairID = wChairID;
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_TRUSTEE,&Trustee,sizeof(Trustee));
	}

	return true;
}

//�û�����
bool CTableFrameSink::OnUserOutCard(WORD wChairID, BYTE cbCardData)
{

	//Ч��״̬
	ASSERT(m_pITableFrame->GetGameStatus()==GS_MJ_PLAY);
	if (m_pITableFrame->GetGameStatus()!=GS_MJ_PLAY) return true;

	//�������
	ASSERT(wChairID==m_wCurrentUser);
	ASSERT(m_GameLogic.IsValidCard(cbCardData)==true);

	//Ч�����
	if (wChairID!=m_wCurrentUser) return false;
	if (m_GameLogic.IsValidCard(cbCardData)==false) return false;

	//ɾ���˿�
	if (m_GameLogic.RemoveCard(m_cbCardIndex[wChairID],cbCardData)==false)
	{
		ASSERT(FALSE);
		return false;
	}

	//���ñ���
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

	//���Ƽ�¼
	m_cbOutCardCount++;
	m_wOutCardUser=wChairID;
	m_cbOutCardData=cbCardData;


	//��������
	CMD_S_OutCard OutCard;
	OutCard.wOutCardUser=wChairID;
	OutCard.cbOutCardData=cbCardData;

	//������Ϣ
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OUT_CARD,&OutCard,sizeof(OutCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OUT_CARD,&OutCard,sizeof(OutCard));

	m_wProvideUser=wChairID;
	m_cbProvideCard=cbCardData;

	if (m_GameLogic.IsMagicCard(cbCardData)) // �������
	{
		m_bOutMagicCard[wChairID] = true;
		// ������������ƣ���ֹ�Ժ��������й�ģʽ
		m_bEnjoinChiHu[wChairID] = true;			//��ֹ�Ժ�
		m_bEnjoinChiPeng[wChairID] = true;			//��ֹ����
	}




	//�û��л�
	m_wCurrentUser=(wChairID+m_wPlayerCount-1)%m_wPlayerCount;
	while( !m_bPlayStatus[m_wCurrentUser] ) 
		m_wCurrentUser=(m_wCurrentUser+m_wPlayerCount-1)%m_wPlayerCount;


	//��Ӧ�ж�
	bool bAroseAction=EstimateUserRespond(wChairID,cbCardData,EstimatKind_OutCard);

	//�ɷ��˿�
	if (bAroseAction==false) DispatchCardData(m_wCurrentUser);

	return true;
}

//�û�����
bool CTableFrameSink::OnUserOperateCard(WORD wChairID, BYTE cbOperateCode, BYTE cbOperateCard)
{
	//Ч��״̬
	ASSERT(m_pITableFrame->GetGameStatus()==GS_MJ_PLAY);
	if (m_pITableFrame->GetGameStatus()!=GS_MJ_PLAY)
		return true;

	//Ч���û�
	ASSERT((wChairID==m_wCurrentUser)||(m_wCurrentUser==INVALID_CHAIR));
	if ((wChairID!=m_wCurrentUser)&&(m_wCurrentUser!=INVALID_CHAIR)) 
		return false;


	//��������
	if (m_wCurrentUser==INVALID_CHAIR)
	{
		//Ч��״̬
		ASSERT(m_bResponse[wChairID]==false); // �û�wChairID ֻ����Ӧһ��
		ASSERT((cbOperateCode==WIK_NULL)||((m_cbUserAction[wChairID]&cbOperateCode)!=0));// ����ֻ���Ƿ��� �����ǿ�ִ�ж����е�һ��

		//Ч��״̬
		if (m_bResponse[wChairID]==true) // �û�wChairID ֻ����Ӧһ��
			return false;
		if ((cbOperateCode!=WIK_NULL)&&((m_cbUserAction[wChairID]&cbOperateCode)==0))// ����ֻ���Ƿ��� �����ǿ�ִ�ж����е�һ��
			return false;
		//��������
		WORD wTargetUser=wChairID; // wTargetUser ִ�ж������û�
		BYTE cbTargetAction=cbOperateCode;// �û�ִ�еĶ���

		//���ñ���
		m_bResponse[wChairID]=true; // ����ID Ϊ wChairID ���û����Ѿ�ִ�й�������
		m_cbPerformAction[wChairID]=cbOperateCode; // ִ�еĶ�����
		m_cbOperateCard[wChairID]=(cbOperateCard==0)?m_cbProvideCard:cbOperateCard;// �붯��������ص���

		//���Լ�δ����һ���Ƶ�һȦ��,��������һ�Ҷ�����һ��
		if( cbTargetAction == WIK_NULL && (WIK_CHI_HU&m_cbUserAction[wTargetUser]) &&
			m_wProvideUser != wTargetUser )
			m_bEnjoinChiHu[wTargetUser] = true;


		//ִ���ж�
		for (WORD i=0;i<m_wPlayerCount;i++) // ��������û�
		{
			//��ȡ����
			BYTE cbUserAction=(m_bResponse[i]==false)?m_cbUserAction[i]:m_cbPerformAction[i];
			// cbUserAction ����Ϊ ����i���û�û��Ӧ��������Ϊ��ִ�ж���������Ϊʵ��ִ�еĶ���
			
			//���ȼ���
			BYTE cbUserActionRank=m_GameLogic.GetUserActionRank(cbUserAction); // ��i���û��� ִ�ж����� ��ִ�ж��� �����ȼ�
			BYTE cbTargetActionRank=m_GameLogic.GetUserActionRank(cbTargetAction);// cbTargetActionRank ��ǰ�û�ִ�еĶ������ȼ�

			if((cbUserAction & WIK_TIE_PAI)!=0&& (cbTargetAction & WIK_TIE_PAI)!=0)
			{
				cbTargetActionRank = 0;
				WORD wTmpID = m_wProvideUser;
				if(i == (--wTmpID)%4>=0?wTmpID: 3)
				{
					cbUserActionRank = 4;
				}else if(i == ((wTmpID-=2)%4>=0?wTmpID:3))
				{
				   cbUserActionRank = 3;
				}else if(i == ((wTmpID-=3)%4>=0?wTmpID:3))
				{
					cbUserActionRank = 2;
				}
			}


			//�����ж�
			if (cbUserActionRank>cbTargetActionRank) 
			{
				// �����ǰ�û���ִ�ж������ȼ����ڵ�I���û��Ŀ�ִ�ж������ȼ�
				// wTargetUser Ŀ���û�����Ϊ ��i���û���Ŀ�궯��Ϊ��i���û��� ��ִ�ж����� ִ�ж���
				wTargetUser=i;
				cbTargetAction=cbUserAction;
			}
		}
		if (m_bResponse[wTargetUser]==false) // ���Ŀ���û������ȼ��ߵ��û���û��ִ�ж��������ز��������´���
			return true;

		//�Ժ��ȴ�
		if (cbTargetAction==WIK_CHI_HU)
		{
			// Ŀ���û������Ǻ��ƣ��������κ�һ�������û���ִ�ж���Ϊ���ƣ�������
			for (WORD i=0;i<m_wPlayerCount;i++)
			{
				if ((m_bResponse[i]==false)&&(m_cbUserAction[i]&WIK_CHI_HU))
					return true;
			}
		}
 
		//��������
		if (cbTargetAction==WIK_NULL)
		{
			//�û�״̬
			ZeroMemory(m_bResponse,sizeof(m_bResponse));
			ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
			ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
			ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

			//�����˿�
			DispatchCardData(m_wResumeUser);
			return true;
		}
		//��������
		BYTE cbTargetCard=m_cbOperateCard[wTargetUser];

		//���Ʊ���
		m_cbOutCardData=0;
		m_bSendStatus=true;
		m_wOutCardUser=INVALID_CHAIR;

		//���Ʋ���
		if (cbTargetAction==WIK_CHI_HU) // ����
		{
			//������Ϣ
			m_cbChiHuCard=cbTargetCard;

			for (WORD i=(m_wProvideUser+m_wPlayerCount-1)%GAME_PLAYER;i!=m_wProvideUser;i = (i+m_wPlayerCount-1)%GAME_PLAYER)
			{
				//�����ж�
				if ((m_cbPerformAction[i]&WIK_CHI_HU)==0)
					continue;


				//�����ж�
				BYTE cbWeaveItemCount=m_cbWeaveItemCount[i];
				tagWeaveItem * pWeaveItem=m_WeaveItemArray[i];
				m_dwChiHuKind[i] = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i],pWeaveItem,cbWeaveItemCount,m_cbChiHuCard,m_ChiHuRight[i]);

				if (m_GameLogic.IsDaDanDiao(m_cbCardIndex[m_wProvideUser],m_cbWeaveItemCount[m_wProvideUser]))
				{
					// �����û�Ϊ�󵥵����ͣ����Ƽӷ�
					m_ChiHuRight[i] |= CHR_DA_DAN_DIAO_PAO; 
				}

				//�����˿�
				if (m_dwChiHuKind[i]!=WIK_NULL) 
				{
					m_cbCardIndex[i][m_GameLogic.SwitchToCardIndex(m_cbChiHuCard)]++;
					ProcessChiHuUser( i,false );
				}
			}

			//�жϽ���
			BYTE cbPlayCount = 0;
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
				if( m_bPlayStatus[i] ) cbPlayCount++;
			}

			if( cbPlayCount < 2 ) 
				OnEventGameEnd( INVALID_CHAIR,NULL,GER_NORMAL );
			else
			{
				//�û�״̬
				ZeroMemory(m_bResponse,sizeof(m_bResponse));
				ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
				ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
				ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

				if(m_bGangStatus == true && m_wProvideUser != wTargetUser) 
				{
					//// �ı乩Ӧ�û����и�����Ϊ������
					for (BYTE k =0;k<m_cbWeaveItemCount[m_wProvideUser];k++) 
					{
						BYTE cbCenterCard = m_WeaveItemArray[m_wProvideUser][k].cbCenterCard;
						if (m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind == WIK_GANG && cbCenterCard == m_cbChiHuCard)
						{
							m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind = WIK_PENG; // ����Ϊ������
							m_bGangStatus = false; // ���ø�״̬
							break;
						}
						

					}

				}
				if((m_bTIStatus == true) && m_wProvideUser != wTargetUser) 
				{

					// �ı乩Ӧ�û�����������Ϊ������
					for (BYTE k =0;k<m_cbWeaveItemCount[m_wProvideUser];k++) // �ı乩Ӧ�û����и�����Ϊ������
					{
						BYTE cbCenterCard = m_WeaveItemArray[m_wProvideUser][k].cbCenterCard;
						if (m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind == WIK_PENG && cbCenterCard == m_cbChiHuCard)
						{
							m_WeaveItemArray[m_wProvideUser][k].cbWeaveKind = WIK_TIE_PAI; // ����Ϊ������
							// ɾ������ص�����
							m_GameLogic.RemoveCard(m_cbCardIndex[m_wProvideUser],
								m_GameLogic.SwitchToCardData(m_GameLogic.GetMagicIndex()));
							m_bTIStatus = false;// ��������״̬
							break;
						}

					}

				}
				
				m_bGangOutStatus = false;
				m_wResumeUser = wTargetUser;

				//�����˿�
				m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
				while( !m_bPlayStatus[m_wResumeUser] ) m_wResumeUser = (m_wResumeUser+GAME_PLAYER-1)%GAME_PLAYER;
			
				DispatchCardData(m_wResumeUser,false);
			}

			return true;
		}

		//�û�״̬
		ZeroMemory(m_bResponse,sizeof(m_bResponse));
		ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
		ZeroMemory(m_cbOperateCard,sizeof(m_cbOperateCard));
		ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

		//����˿�
		ASSERT(m_cbWeaveItemCount[wTargetUser]<4);
		WORD wIndex=m_cbWeaveItemCount[wTargetUser]++;
		m_WeaveItemArray[wTargetUser][wIndex].cbPublicCard=TRUE;
		m_WeaveItemArray[wTargetUser][wIndex].cbCenterCard=cbTargetCard;
		m_WeaveItemArray[wTargetUser][wIndex].cbWeaveKind=cbTargetAction;
		m_WeaveItemArray[wTargetUser][wIndex].wProvideUser=(m_wProvideUser==INVALID_CHAIR)?wTargetUser:m_wProvideUser;

		//ɾ���˿�
		switch (cbTargetAction)
		{
		case WIK_LEFT:		//���Ʋ���
			{
				//ɾ���˿�
				BYTE cbRemoveCard[3];
				m_GameLogic.GetWeaveCard(WIK_LEFT,cbTargetCard,cbRemoveCard);
				VERIFY( m_GameLogic.RemoveCard(cbRemoveCard,3,&cbTargetCard,1) );
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );

				break;
			}

		case WIK_RIGHT:		//���Ʋ���
			{
				//ɾ���˿�
				BYTE cbRemoveCard[3];
				m_GameLogic.GetWeaveCard(WIK_RIGHT,cbTargetCard,cbRemoveCard);
				VERIFY( m_GameLogic.RemoveCard(cbRemoveCard,3,&cbTargetCard,1) );
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );

				break;
			}
		case WIK_TIE_PAI:		//���Ʋ���
			{
				//ɾ���˿�

				BYTE cbRemoveCard[3];
				m_GameLogic.GetWeaveCard(WIK_TIE_PAI,cbTargetCard,cbRemoveCard);
				VERIFY( m_GameLogic.RemoveCard(cbRemoveCard,3,&cbTargetCard,1) );
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );

				break;
			}

		case WIK_PENG:		//���Ʋ���
			{
				//ɾ���˿�
				BYTE cbRemoveCard[]={cbTargetCard,cbTargetCard};
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,2) );
				break;
			}
		case WIK_GANG:		//���Ʋ���
			{
				//ɾ���˿�,������
				BYTE cbRemoveCard[]={cbTargetCard,cbTargetCard,cbTargetCard};
				VERIFY( m_GameLogic.RemoveCard(m_cbCardIndex[wTargetUser],cbRemoveCard,CountArray(cbRemoveCard)) );
			
				break;
			}
		default:
			ASSERT( FALSE );
			return false;
		}

		//������
		CMD_S_OperateResult OperateResult;
		OperateResult.wOperateUser=wTargetUser;
		OperateResult.cbOperateCard=cbTargetCard;
		OperateResult.cbOperateCode=cbTargetAction;
		OperateResult.wProvideUser=(m_wProvideUser==INVALID_CHAIR)?wTargetUser:m_wProvideUser;
	    m_bEnjoinChiHu[wTargetUser]=false; // ȡ���Ժ�����
		//������Ϣ
		m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));
		m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));

		//�����û�
		m_wCurrentUser=wTargetUser;

		//���ƴ���
		if (cbTargetAction==WIK_GANG)
		{
			m_bGangStatus = true;
			DispatchCardData(wTargetUser,false); // ���Ƹ������û������Ƶ�ǰ�û�����
		}
		else 
		{
			// ����֮�󣬹����Լ���������û�� �ᡢ �ܡ� ����
			// �������֮��,ֻ�����Լ�������
			EstimatePengTieCardRespond(m_wCurrentUser);


		}
		return true;
	}

	//��������
	if (m_wCurrentUser==wChairID)
	{
		//Ч�����
		ASSERT((cbOperateCode!=WIK_NULL)&&((m_cbUserAction[wChairID]&cbOperateCode)!=0));
		if ((cbOperateCode==WIK_NULL)||((m_cbUserAction[wChairID]&cbOperateCode)==0))// ����ֻ���Ƿ��� �����ǿ�ִ�ж����е�һ��
			return false;

		//�˿�Ч��
		ASSERT((cbOperateCode==WIK_NULL)||(cbOperateCode==WIK_CHI_HU)||(m_GameLogic.IsValidCard(cbOperateCard)==true));
		if ((cbOperateCode!=WIK_NULL)&&(cbOperateCode!=WIK_CHI_HU)&&(m_GameLogic.IsValidCard(cbOperateCard)==false)) 
			return false;

		//���ñ���
		m_bSendStatus=true;
		m_bEnjoinChiHu[m_wCurrentUser]=false;
		m_cbUserAction[m_wCurrentUser]=WIK_NULL;
		m_cbPerformAction[m_wCurrentUser]=WIK_NULL;

		bool bPublic=false;
		// ���� ���� ���������ܣ�����
		// ���û�����ܣ����ᣬ��˳��ִ��
		// ���� �ȴ����������û�ִ�н��

		//ִ�ж���
		switch (cbOperateCode)
		{
		case WIK_TI_PAI:			//���Ʋ���
			{
				//��������
				BYTE cbWeaveIndex=0xFF;
				BYTE cbCardIndex=m_GameLogic.SwitchToCardIndex(cbOperateCard);

				//���ƴ���
				if (m_cbCardIndex[wChairID][cbCardIndex]>=1) // ����Ҫ��һ�ſ��滻����
				{
					//Ѱ�����
					for (BYTE i=0;i<m_cbWeaveItemCount[wChairID];i++)
					{
						BYTE cbWeaveKind=m_WeaveItemArray[wChairID][i].cbWeaveKind;
						BYTE cbCenterCard=m_WeaveItemArray[wChairID][i].cbCenterCard;
						if ((cbCenterCard==cbOperateCard)&&(cbWeaveKind==WIK_TIE_PAI))
						{
							// �ҵ������������
							bPublic=true;
							cbWeaveIndex=i;
							break;
						}
					}

					//Ч�鶯��
					ASSERT(cbWeaveIndex!=0xFF);
					if (cbWeaveIndex==0xFF) return false;
					
					// ɾ���滻�˿�
					m_GameLogic.RemoveCard(m_cbCardIndex[wChairID],cbOperateCard);
					m_bTIStatus = true;// ��������״̬

					//����˿�
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbPublicCard=TRUE;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbWeaveKind=WIK_PENG;
				}


				//������
				CMD_S_OperateResult OperateResult;
				OperateResult.wOperateUser=wChairID;
				OperateResult.wProvideUser=wChairID;
				OperateResult.cbOperateCode=cbOperateCode;
				OperateResult.cbOperateCard=cbOperateCard;

				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));

				// ��ͷ�Ѿ����ƹ�������Ӧ�����ﲻӦ���ٹ���
				//Ч�鶯��
				bool bAroseAction=false;
				if (bPublic==true)
				{
					bAroseAction = EstimateUserRespond(wChairID,cbOperateCard,EstimatKind_TICard);
				}

				if (bAroseAction==false)
				{

					m_bTIStatus = false; // û�������ᣬ�Լ����Ʋ������ᣬ�����־��λ
					EstimateTICardRespond(wChairID,m_GameLogic.SwitchToCardData(m_GameLogic.GetMagicIndex()));
					m_cbCardIndex[wChairID][m_GameLogic.GetMagicIndex()]++;// ��������˿�
				}
				return true;
			}

		case WIK_GANG:			//���Ʋ���
			{
				//��������
				BYTE cbWeaveIndex=0xFF;
				BYTE cbCardIndex=m_GameLogic.SwitchToCardIndex(cbOperateCard);
				//���ƴ���
				if (m_cbCardIndex[wChairID][cbCardIndex]==1)
				{
					//Ѱ����� // 
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

					//Ч�鶯��
					ASSERT(cbWeaveIndex!=0xFF);
					if (cbWeaveIndex==0xFF)
					{
						return false;
					}

					//����˿�
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbPublicCard=TRUE;
					m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser=wChairID;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbWeaveKind=cbOperateCode;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard=cbOperateCard;
				}
				else
				{
					//�˿�Ч��
					ASSERT(m_cbCardIndex[wChairID][cbCardIndex]==4);
					if (m_cbCardIndex[wChairID][cbCardIndex]!=4) 
						return false;

					//���ñ���
					bPublic=false; // ����Ϊ��������
					cbWeaveIndex=m_cbWeaveItemCount[wChairID]++;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbPublicCard=TRUE; // ��������Ϊ�ɼ�

					m_WeaveItemArray[wChairID][cbWeaveIndex].wProvideUser=wChairID;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbWeaveKind=cbOperateCode;
					m_WeaveItemArray[wChairID][cbWeaveIndex].cbCenterCard=cbOperateCard;
				}

				//ɾ���˿�
				m_cbCardIndex[wChairID][cbCardIndex]=0;
				m_bGangStatus = true;

				//������
				CMD_S_OperateResult OperateResult;
				OperateResult.wOperateUser=wChairID;
				OperateResult.wProvideUser=wChairID;
				OperateResult.cbOperateCode=cbOperateCode;
				OperateResult.cbOperateCard=cbOperateCard;

				//������Ϣ
				m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));
				m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_OPERATE_RESULT,&OperateResult,sizeof(OperateResult));

				//Ч�鶯��
				bool bAroseAction=false;
				if (bPublic==true) 
				{
					bAroseAction=EstimateUserRespond(wChairID,cbOperateCard,EstimatKind_PengGangCard);
				}
			
				//�����˿�
				if (bAroseAction==false)
 
				{
					DispatchCardData(wChairID,false); //˳�η���
				}
				return true;
			}
		case WIK_CHI_HU:		//�Ժ�����
			{
				//����Ȩλ
				if (m_cbOutCardCount==0)
				{
					m_wProvideUser = m_wCurrentUser;
					m_cbProvideCard = m_cbSendCardData;
				}

				//��ͨ����
				BYTE cbWeaveItemCount=m_cbWeaveItemCount[wChairID];
				tagWeaveItem * pWeaveItem=m_WeaveItemArray[wChairID];
				m_GameLogic.RemoveCard(m_cbCardIndex[wChairID],&m_cbProvideCard,1);
				m_dwChiHuKind[wChairID] = m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wChairID],pWeaveItem,cbWeaveItemCount,m_cbProvideCard,
					m_ChiHuRight[wChairID]);
				m_cbCardIndex[wChairID][m_GameLogic.SwitchToCardIndex(m_cbProvideCard)]++;

				//������Ϣ
				m_cbChiHuCard=m_cbProvideCard;

				ProcessChiHuUser( wChairID,false );

				//�жϽ���
				BYTE cbPlayCount = 0;
				for( WORD i = 0; i < GAME_PLAYER; i++ )
				{
					if( m_bPlayStatus[i] ) cbPlayCount++;
				}

				if( cbPlayCount < 2 ) 
					OnEventGameEnd( INVALID_CHAIR,NULL,GER_NORMAL );
				else
				{
					//����
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

//���Ͳ���
bool CTableFrameSink::SendOperateNotify()
{
	//������ʾ
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		if (m_cbUserAction[i]!=WIK_NULL)
		{
			//��������
			CMD_S_OperateNotify OperateNotify;
			OperateNotify.wResumeUser=m_wResumeUser;
			OperateNotify.cbActionCard=m_cbProvideCard;
			OperateNotify.cbActionMask=m_cbUserAction[i];

			//��������
			m_pITableFrame->SendTableData(i,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
			m_pITableFrame->SendLookonData(i,SUB_S_OPERATE_NOTIFY,&OperateNotify,sizeof(OperateNotify));
		}
	}

	return true;
}

//�ɷ��˿� // btail - �Ƿ�������
bool CTableFrameSink::DispatchCardData(WORD wCurrentUser,bool bTail)
{
	//״̬Ч��
	ASSERT(wCurrentUser!=INVALID_CHAIR);
	if (wCurrentUser==INVALID_CHAIR)
		return false;

	//�����˿�
	if ((m_wOutCardUser!=INVALID_CHAIR)&&(m_cbOutCardData!=0))
	{
		m_cbDiscardCount[m_wOutCardUser]++;
		m_cbDiscardCard[m_wOutCardUser][m_cbDiscardCount[m_wOutCardUser]-1]=m_cbOutCardData;
	}

	//��ׯ����
	if (m_cbLeftCardCount==0)
	{
		m_cbChiHuCard=0;
		m_wProvideUser=INVALID_CHAIR;
		OnEventGameEnd(m_wProvideUser,NULL,GER_NORMAL);

		return true;
	}

	//���ñ���
	m_cbOutCardData=0;
	m_wCurrentUser=wCurrentUser;
	m_wOutCardUser=INVALID_CHAIR;
	m_bEnjoinChiHu[wCurrentUser]=false;

	//�ܺ���
	if( m_bGangOutStatus )
	{
		m_bGangOutStatus = false;
	}
	//���ƴ���
	if (m_bSendStatus==true)
	{
		//�����˿�
		m_cbSendCardCount++;
		m_cbSendCardData=m_cbRepertoryCard[--m_cbLeftCardCount];


		m_cbUserAction[wCurrentUser] = WIK_NULL; // OMA ����֮ǰ�û�����

		//�Ժ�����
		if(m_bOutMagicCard[wCurrentUser] == false)
		{
			//�Ժ�����
			CChiHuRight ChiHuRight;
			ZeroMemory(&ChiHuRight,sizeof(ChiHuRight));
			m_cbUserAction[wCurrentUser]|= m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wCurrentUser],
				m_WeaveItemArray[wCurrentUser], m_cbWeaveItemCount[wCurrentUser],m_cbSendCardData,ChiHuRight);
		}

		//����
		m_cbCardIndex[wCurrentUser][m_GameLogic.SwitchToCardIndex(m_cbSendCardData)]++;

		//���ñ���
		m_wProvideUser=wCurrentUser;
		m_cbProvideCard=m_cbSendCardData;

		

		//�����ж�
		if ((m_bEnjoinChiPeng[wCurrentUser]==false)&&(m_cbLeftCardCount>0))
		{
			tagGangCardResult GangCardResult; 
			// �ڿͻ��˾����������Щ�ܣ�����ֻ��Ҫ֪���ɸ��������
			ZeroMemory(&GangCardResult,sizeof(GangCardResult));
			m_cbUserAction[wCurrentUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCurrentUser],
				m_WeaveItemArray[wCurrentUser],m_cbWeaveItemCount[wCurrentUser],GangCardResult);
		}
		tagTICardResult TICardResult; 
		ZeroMemory(&TICardResult,sizeof(TICardResult));

		// ���Ʒ���
		m_cbUserAction[wCurrentUser]|= m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCurrentUser],
				m_WeaveItemArray[wCurrentUser], m_cbWeaveItemCount[wCurrentUser],TICardResult);
	}

	//������Ϣ
	ASSERT( m_wHeapHand != INVALID_CHAIR && m_wHeapTail != INVALID_CHAIR );
	if( !bTail )
	{
		//�л�����
		BYTE cbHeapCount=m_cbHeapCardInfo[m_wHeapHand][0]+m_cbHeapCardInfo[m_wHeapHand][1];
		if (cbHeapCount==HEAP_FULL_COUNT) 
			m_wHeapHand=(m_wHeapHand+1)%CountArray(m_cbHeapCardInfo);
		m_cbHeapCardInfo[m_wHeapHand][0]++;
	}
	else
	{
		//�л�����
		BYTE cbHeapCount=m_cbHeapCardInfo[m_wHeapTail][0]+m_cbHeapCardInfo[m_wHeapTail][1];
		if (cbHeapCount==HEAP_FULL_COUNT) 
			m_wHeapTail=(m_wHeapTail+3)%CountArray(m_cbHeapCardInfo);
		m_cbHeapCardInfo[m_wHeapTail][1]++;
	}
	
	//��������
	CMD_S_SendCard SendCard;
	ZeroMemory(&SendCard,sizeof(SendCard));
	SendCard.wCurrentUser=wCurrentUser;
	SendCard.bTail = bTail;
	SendCard.cbActionMask=m_cbUserAction[wCurrentUser];
	SendCard.cbCardData=(m_bSendStatus==true)?m_cbSendCardData:0x00;


	//��������
	m_pITableFrame->SendTableData(INVALID_CHAIR,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));
	m_pITableFrame->SendLookonData(INVALID_CHAIR,SUB_S_SEND_CARD,&SendCard,sizeof(SendCard));

	return true;
}

bool CTableFrameSink::EstimatePengTieCardRespond(WORD wCenterUser)
{
	bool bAroseAction=false;

	//�û�״̬
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

	////�����ж�
	// �����Լ��������Ƿ������
	tagTICardResult TICardResult;
	ZeroMemory(&TICardResult,sizeof(TICardResult));
	m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
		m_cbWeaveItemCount[wCenterUser],TICardResult);

	//�����ж�
	if (m_cbLeftCardCount>0) 
	{
		// �����Լ��������Ƿ���Ը�
		tagGangCardResult GangCardResult;
		ZeroMemory(&GangCardResult,sizeof(GangCardResult));
		m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
			m_cbWeaveItemCount[wCenterUser],GangCardResult);

	}


	//����ж�
	if (m_cbUserAction[wCenterUser]!=WIK_NULL) 
		bAroseAction=true;


	//�������
	if (bAroseAction==true) 
	{
		//���ñ���
		m_wProvideUser=wCenterUser;
		m_wResumeUser=m_wCurrentUser;
		//������ʾ
		SendOperateNotify();
	}

	return true;
}


bool CTableFrameSink::EstimateTICardRespond(WORD wCenterUser,BYTE cbCenterCard)// cbCenterCard ��ص�����Ϊ��ǰ��
{

	bool bAroseAction=false;
	
	//�û�״̬
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));
	
	////�����ж�
	// �����Լ��������Ƿ������
	tagTICardResult TICardResult;
	m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
		m_cbWeaveItemCount[wCenterUser],TICardResult);

	//�����ж�
	if (m_cbLeftCardCount>0) 
	{
		// �����Լ��������Ƿ���Ը�
		tagGangCardResult GangCardResult;
		m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
			m_cbWeaveItemCount[wCenterUser],GangCardResult);

	}

	//�����ж�
	if (m_bEnjoinChiHu[wCenterUser]==false && m_bPlayStatus[wCenterUser])// �������������ƣ�ȡ��������Ӧ
	{
		//�Ժ��ж�
		CChiHuRight chr;
		BYTE cbWeaveCount=m_cbWeaveItemCount[wCenterUser];
		m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],cbWeaveCount,cbCenterCard,chr);

	}

	//����ж�
	if (m_cbUserAction[wCenterUser]!=WIK_NULL) 
		bAroseAction=true;

	//�������
	if (bAroseAction==true) 
	{

		//���ñ���
		m_wProvideUser=wCenterUser;
		m_cbProvideCard=cbCenterCard;
		m_wResumeUser=m_wCurrentUser;
		//������ʾ
		SendOperateNotify();

	}

	return true;

}


//��Ӧ�ж� // �ǹ���EstimatKind �����������û���Ӧ
bool CTableFrameSink::EstimateUserRespond(WORD wCenterUser, BYTE cbCenterCard, enEstimatKind EstimatKind)
{
	//��������
	bool bAroseAction=false;
 
	//�û�״̬
	ZeroMemory(m_bResponse,sizeof(m_bResponse));
	ZeroMemory(m_cbUserAction,sizeof(m_cbUserAction));
	ZeroMemory(m_cbPerformAction,sizeof(m_cbPerformAction));

	// ���ƣ����ƣ�ֻ���Ƶ�ǰ�����û�
	if(EstimatKind_TIECard == EstimatKind || EstimatKind_PENGCard == EstimatKind)
	{
		//�����ж�	// �����Լ��������Ƿ������
		tagTICardResult TICardResult;
		m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
			m_cbWeaveItemCount[wCenterUser],TICardResult);

		//�����ж�
		if (m_cbLeftCardCount>0) 
		{
			// �����Լ��������Ƿ���Ը�
			tagGangCardResult GangCardResult;
			m_cbUserAction[wCenterUser]|=m_GameLogic.AnalyseGangCard(m_cbCardIndex[wCenterUser],m_WeaveItemArray[wCenterUser],
			m_cbWeaveItemCount[wCenterUser],GangCardResult);
		}

		// ������������Ҫ�����������Ƿ���Ժ���

		m_cbProvideCard = 0;
		if (m_cbUserAction[wCenterUser]!=WIK_NULL) 
			bAroseAction=true;

	}else
	
	//�����ж�
	for (WORD i=0;i<m_wPlayerCount;i++)
	{
		//��������
		if (EstimatKind==EstimatKind_OutCard)
		{

			//�û�����  // �����жϣ������Լ�
			if (wCenterUser==i||!m_bPlayStatus[i]) continue;
			//�û�����  // �����жϣ���������������û�
			if (m_bOutMagicCard[i] == true) continue;

			//�����ж�
			if (m_bEnjoinChiPeng[i]==false)
			{
				//�����ж�
				m_cbUserAction[i]|=m_GameLogic.EstimatePengCard(m_cbCardIndex[i],cbCenterCard);
				//�����ж�
				m_cbUserAction[i]|=m_GameLogic.EstimateTiePaiCard(m_cbCardIndex[i],cbCenterCard);
				//�����ж�
				if (m_cbLeftCardCount>0) 
				{
					// EstimateGangCard ֻ���������û������ǣ��Ƿ���Ը���
					m_cbUserAction[i]|=m_GameLogic.EstimateGangCard(m_cbCardIndex[i],cbCenterCard);
				}
			}
		}else if (EstimatKind==EstimatKind_TICard) // ���ƶ������֮�� ��ǰ�û���������
		{

		}

		//�����ж�
		if (m_bEnjoinChiHu[i]==false && !m_GameLogic.IsMagicCard(cbCenterCard)&&m_bPlayStatus[i])// �������������ƣ�ȡ��������Ӧ
		{
			//�Ժ��ж�
			CChiHuRight chr;
			BYTE cbWeaveCount=m_cbWeaveItemCount[i];
			m_cbUserAction[i]|=m_GameLogic.AnalyseChiHuCard(m_cbCardIndex[i],m_WeaveItemArray[i],cbWeaveCount,cbCenterCard,chr);
		}
	
		//����ж�
		if (m_cbUserAction[i]!=WIK_NULL) 
			bAroseAction=true;

	}


	//�������
	if (bAroseAction==true) 
	{

		//���ñ���
		m_wProvideUser=wCenterUser;
		m_cbProvideCard=cbCenterCard;
		m_wResumeUser=m_wCurrentUser;
		m_wCurrentUser=INVALID_CHAIR;
	
		//������ʾ
		SendOperateNotify();

		return true;
	}

	return false;
}

//
void CTableFrameSink::ProcessChiHuUser( WORD wChairId, bool bGiveUp )
{
	if( !bGiveUp )
	{
		//����Ȩλs
		CChiHuRight &chr = m_ChiHuRight[wChairId];
	
		DWORD Right;
		chr.GetRightData(&Right,1);
		FiltrateRight( wChairId,chr );
		WORD wFanShu = m_GameLogic.GetChiHuActionRank( chr );
		LONG score = (LONG)pow(2.0,wFanShu-1);
	

		// ������ܷ�
		LONG lChiHuScore = score*m_pGameServiceOption->lCellScore;
		if( m_wProvideUser != wChairId ) // ���ڻ�������
		{
			m_wLostFanShu[m_wProvideUser][wChairId] = lChiHuScore; // �����û��۷�
		}
		else
		{
			for( WORD i = 0; i < GAME_PLAYER; i++ ) // ������δ�����ŷ���
			{
				if( !m_bPlayStatus[i] || i == wChairId ) continue;

				m_wLostFanShu[i][wChairId] = lChiHuScore;
			}
		}

	//////////////////////////////////////////////////////////////////////////
		//  �÷�
		if( m_wProvideUser == wChairId ) // ����
		{
			for( WORD i = 0; i < GAME_PLAYER; i++ )
			{
				if( !m_bPlayStatus[i] || i == wChairId ) continue;

				// �����û����ٿ۷�
				if(m_bPlayleft[i] == true) continue;
				//���Ʒ�
				m_lGameScore[i] -= lChiHuScore;
				m_lGameScore[wChairId] += lChiHuScore;
			}
		}
		//����
		else
		{
			m_lGameScore[m_wProvideUser] -= lChiHuScore;
			m_lGameScore[wChairId] += lChiHuScore;
		}

		//���ñ���
		m_wProvider[wChairId] = m_wProvideUser;
		m_wWinOrder[m_cbWinCount++] = wChairId;
		//������Ϣ
		CMD_S_ChiHu ChiHu;
		ChiHu.wChiHuUser = wChairId;
		ChiHu.wProviderUser = m_wProvideUser;
		ChiHu.bGangStatus = m_bGangStatus;
		ChiHu.bTIStatus = m_bTIStatus ;// ��������״̬
		ChiHu.lGameScore = m_lGameScore[wChairId];
		ChiHu.cbCardCount = m_GameLogic.GetCardCount( m_cbCardIndex[wChairId] );
		ChiHu.cbChiHuCard = m_cbProvideCard;
		ChiHu.cbWinOrder = m_cbWinCount;
		m_pITableFrame->SendTableData( INVALID_CHAIR,SUB_S_CHI_HU,&ChiHu,sizeof(ChiHu) );
		m_pITableFrame->SendLookonData( INVALID_CHAIR,SUB_S_CHI_HU,&ChiHu,sizeof(ChiHu) );

		//���ñ���
		m_bPlayStatus[wChairId] = false;

	}

	return;
}

//
void CTableFrameSink::FiltrateRight( WORD wChairId,CChiHuRight &chr )
{

	//Ȩλ����
	//����
	if( m_wCurrentUser == INVALID_CHAIR && m_bGangStatus )
	{
		chr |= CHR_QIANG_GANG;
	}
	//���
	if( m_cbSendCardCount == 2 && m_cbOutCardCount == 0 ) // ���㷭��һ��
	{
		chr.SetEmpty();
		chr |= CHR_TIAN_HU;
	}
	//�غ�
	else if( m_cbSendCardCount == 2 && m_cbOutCardCount == 1 )
	{
		chr.SetEmpty();
		chr |= CHR_DI_HU;
	}

	//����Ȩλ
	//���ϻ�
	if( m_wCurrentUser==wChairId && m_bGangStatus )
	{
		chr |= CHR_GANG_KAI;
	}
	//������
	if( m_bGangOutStatus && !m_bGangStatus )
	{
		chr |= CHR_GANG_SHANG_PAO;
	}
 
	//���ӷ�
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
