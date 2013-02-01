#include "Stdafx.h"
#include "AndroidUserItemSink.h"

//////////////////////////////////////////////////////////////////////////

//����ʱ��
#define TIME_LESS					3									//����ʱ��

//��Ϸʱ��
#define TIME_OUT_CARD				3									//����ʱ��
#define TIME_START_GAME				3									//��ʼʱ��
#define TIME_OPERATE_CARD			3									//����ʱ��
#define TIME_HEAR_STATUS			3									//����ʱ�䰴

//��Ϸʱ��
#define IDI_OUT_CARD				(IDI_ANDROID_ITEM_SINK+0)			//����ʱ��
#define IDI_START_GAME				(IDI_ANDROID_ITEM_SINK+1)			//��ʼʱ��
#define IDI_OPERATE_CARD			(IDI_ANDROID_ITEM_SINK+2)			//����ʱ��

//////////////////////////////////////////////////////////////////////////

//���캯��
CAndroidUserItemSink::CAndroidUserItemSink()
{
	//��Ϸ����
	m_wBankerUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;

	//״̬����
	m_bHearStatus=false;
	m_bWillHearStatus=false;
	m_bActionMask = WIK_NULL;
	m_cbActionCard=0;

	//������Ϣ
	m_cbOutCardData=0;
	m_wOutCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbDiscardCard,sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount,sizeof(m_cbDiscardCount));
	m_cbSendCardData = 0;

	//����˿�
	ZeroMemory(m_cbWeaveCount,sizeof(m_cbWeaveCount));
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));

	//�˿˱���
	m_cbLeftCardCount=0;
	ZeroMemory(m_cbCardIndex,sizeof(m_cbCardIndex));
	ZeroMemory(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));
	
	return;
}

//��������
CAndroidUserItemSink::~CAndroidUserItemSink()
{

}

//�ӿڲ�ѯ
void * __cdecl CAndroidUserItemSink::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IAndroidUserItemSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IAndroidUserItemSink,Guid,dwQueryVer);
	return NULL;
}

//��ʼ�ӿ�
bool __cdecl CAndroidUserItemSink::InitUserItemSink(IUnknownEx * pIUnknownEx)
{
	//��ѯ�ӿ�
	m_pIAndroidUserItem=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IAndroidUserItem);
	if (m_pIAndroidUserItem==NULL) return false;
	
	return true;
}

//���ýӿ�
bool __cdecl CAndroidUserItemSink::RepositUserItemSink()
{
	//��Ϸ����
	m_wBankerUser=INVALID_CHAIR;
	m_wCurrentUser=INVALID_CHAIR;

	//״̬����
	m_bHearStatus=false;
	m_bWillHearStatus=false;
	m_bActionMask = WIK_NULL;
	m_cbActionCard=0;

	//������Ϣ
	m_cbOutCardData=0;
	m_wOutCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbDiscardCard,sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount,sizeof(m_cbDiscardCount));
	m_cbSendCardData = 0;

	//����˿�
	ZeroMemory(m_cbWeaveCount,sizeof(m_cbWeaveCount));
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));

	//�˿˱���
	m_cbLeftCardCount=0;
	ZeroMemory(m_cbCardIndex,sizeof(m_cbCardIndex));
	ZeroMemory(m_cbRepertoryCard,sizeof(m_cbRepertoryCard));

	return true;
}

//ʱ����Ϣ
bool __cdecl CAndroidUserItemSink::OnEventTimer(UINT nTimerID)
{
	////_c//printf("android nTimerID: %d response\n",nTimerID);

	switch (nTimerID)
	{
	case IDI_START_GAME:		//��ʼ��Ϸ
		{
			//��ʼ�ж�
			m_pIAndroidUserItem->SendUserReady(NULL,0);
			return true;
		}
	case IDI_OPERATE_CARD:		//������ʱ��
		{

			////_c//printf(" android operate entry ........ m_bActionMask: %x \n",m_bActionMask);

			WORD wMeChair=m_pIAndroidUserItem->GetChairID();
		//	//_c//printf("android wMeChair: %d operate m_bActionMask: %x \n",wMeChair,m_bActionMask);
		//	//printf("android wMeChair: %d operate m_bActionMask: %x \n",wMeChair,m_bActionMask);

			if((m_bActionMask!=WIK_NULL)/*&&(m_wCurrentUser!=m_pIAndroidUserItem->GetChairID())*/)
			{
				
				if(m_bActionMask&WIK_CHI_HU)
				{
			//		//_c//printf("android operate WIK_CHI_HU ..........\n");//��������
			//		//printf("android operate WIK_CHI_HU ..........\n");//��������

					OnOperateCard(WIK_CHI_HU,0);
					return true;
				}
				

				if (m_bActionMask&WIK_TIE_PAI) // OMA  �������Ʋ�������������
				{
				//	//_c//printf("android operate WIK_TIE_PAI ..........\n"); // ����ֻ��һ��
				//	//printf("android operate WIK_TIE_PAI ..........\n"); // ����ֻ��һ��

					OnOperateCard(WIK_TIE_PAI,0);
					return true;
				}


				// �������� �ٸ� // for debug
				if (m_bActionMask&WIK_PENG) // OMA   �������Ʋ�������������
				{
				//	//_c//printf("android operate WIK_PENG ..........\n");
				//	//printf("android operate WIK_PENG ..........\n");


					OnOperateCard(WIK_PENG,0);
					return true;
				}

				
				if(m_bActionMask&WIK_GANG) // 
				{
				//	//_c//printf("android operate WIK_GANG ........m_wCurrentUser %d m_CurGangResult.cbCardCount: %d \n",m_wCurrentUser,m_CurGangResult.cbCardCount);
				//	  //printf("android operate WIK_GANG ........m_wCurrentUser %d m_CurGangResult.cbCardCount: %d \n",m_wCurrentUser,m_CurGangResult.cbCardCount);

					
					if (m_CurGangResult.cbCardCount>0&& m_wCurrentUser != INVALID_CHAIR)
					{
						if ( m_wCurrentUser == wMeChair)
						{
							for (BYTE k = 0;k<m_CurGangResult.cbCardCount;k++)
							{
								////_c//printf("%x ",m_CurGangResult.cbCardData[k]);
							}

								m_cbActionCard = m_CurGangResult.cbCardData[0]; // ѡ��һ��Ĭ�ϵĸ��ƣ�����ж������
						}
					
						////_c//printf("\n GANG operate m_wCurrentUser != INVALID_CHAIR Choose the first one..m_cbActionCard : %x \n",m_cbActionCard);
						////printf("\n GANG operate m_wCurrentUser != INVALID_CHAIR Choose the first one..m_cbActionCard : %x \n",m_cbActionCard);

						m_bGangStatus = true; // ���ø���״̬
						OnOperateCard(WIK_GANG,m_cbActionCard);
					}else
					{
						////_c//printf("WIK_GANG operate m_wCurrentUser == INVALID_CHAIR ........... \n");
						////printf("WIK_GANG operate m_wCurrentUser == INVALID_CHAIR ........... \n");

						OnOperateCard(WIK_GANG,m_cbActionCard); // ��������
					}

					return true;
				}

 				
				if (m_bActionMask&WIK_TI_PAI) // OMA  �������Ʋ���,��������
				{
 
					if (m_CurTIResult.cbCardCount>0)
					{
 						m_cbActionCard = m_CurTIResult.cbCardData[0]; // ѡ��һ��Ĭ�ϵ����ƣ�����ж������
 

						m_bTIStatus = true; // ��������״̬
						OnOperateCard(WIK_TI_PAI,m_cbActionCard);

					} 
					
					return true;
				}

			
				if (m_bActionMask&WIK_TIE_PAI) // OMA  �������Ʋ�������������
				{
 
					OnOperateCard(WIK_TIE_PAI,0);
					return true;
				}

 				// oma android ����˳���� �� �� �� �� �����ȼ�
 
	
				m_bActionMask &=~WIK_LISTEN;
				if((m_bActionMask!=WIK_NULL)&&(m_bHearStatus==false))
				{
					BYTE cbOperateCode=GetTheBestOperate(m_bActionMask,m_cbActionCard);
					ASSERT( m_cbActionCard!=0xFF);
					ASSERT(m_cbActionCard!=0);
					if(cbOperateCode==WIK_NULL)
						m_cbActionCard=0;
					OnOperateCard(cbOperateCode,m_cbActionCard);
				}

			}
 
			if(m_wCurrentUser==wMeChair)
			{
				if((m_bHearStatus==true)&&(m_cbSendCardData!=0))
				{
 

					BYTE cbCardData=m_cbSendCardData;
					//����Ч��
					if (VerdictOutCard(cbCardData)==false)
					{
						for (BYTE i=0;i<MAX_INDEX;i++)
						{
							//����Ч��
							if (m_cbCardIndex[wMeChair][i]==0) continue;
							if (VerdictOutCard(m_GameLogic.SwitchToCardData(i))==false)continue;

							//���ñ���
							cbCardData=m_GameLogic.SwitchToCardData(i);
						}
					}
					//���ƶ���
					OnOutCard(cbCardData);
					return true;

				}

 				//���ܳ���
				BYTE cbCardData=GetIsolatedCard();
#ifdef CONSOLE_OMA
				if((cbCardData!=0xFF))
#else
				if((cbCardData!=0xFF)&&(m_bHearStatus==false))
#endif 
				{
					////_c//printf("android: wMeChair %d operate GetIsolatedCard outcard cbCardData : %x \n",wMeChair,cbCardData);

					OnOutCard(cbCardData);
					return true;
				}
				
			//	//_c//printf("android GetIsolatedCard exception --- cbCardData: %x \n",cbCardData);
			//	//printf("android GetIsolatedCard exception --- cbCardData: %x \n",cbCardData);

				//�쳣����
				//for (INT i=MAX_INDEX-1;i>0;i--)
				for (INT i=0;i<MAX_INDEX;i++)
				{
					if((m_cbCardIndex[wMeChair][i]>0))
					{
						BYTE cbIndex=i;
						cbCardData=m_GameLogic.SwitchToCardData(i);
#ifdef CONSOLE_OMA
#else 
						if(m_bHearStatus==false)
#endif 
						{
						//	//_c//printf("android: wMeChair %d  exception outcard cbCardData: %x i == %d \n",wMeChair,cbCardData,i);
						//	//_c//printf("android: wMeChair %d  exception outcard cbCardData: %x i == %d \n",wMeChair,cbCardData,i);

							OnOutCard(cbCardData);
							return true;
						}
					}

				}

				//����Ч��
				if (VerdictOutCard(cbCardData)==false)
				{
					for (BYTE i=0;i<MAX_INDEX;i++)
					{
						//����Ч��
						if (m_cbCardIndex[wMeChair][i]==0) continue;
						if (VerdictOutCard(m_GameLogic.SwitchToCardData(i))==false)continue;

						//���ñ���
						cbCardData=m_GameLogic.SwitchToCardData(i);
					}
				}
			//	//_c//printf("android: wMeChair %d  last outcard cbCardData: %x \n",wMeChair,cbCardData);
			//	//printf("android: wMeChair %d  last outcard cbCardData: %x \n",wMeChair,cbCardData);


				//���ƶ���
				OnOutCard(cbCardData);
				return true;

				ASSERT(FALSE);

			}
			return true;
		}
	}

	return false;
}

//��Ϸ��Ϣ
bool __cdecl CAndroidUserItemSink::OnEventGameMessage(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	switch (wSubCmdID)
	{
	case SUB_S_GAME_START:		//��Ϸ��ʼ
		{
			return OnSubGameStart(pData,wDataSize);
		}
	case SUB_S_OUT_CARD:		//�û�����
		{
			return OnSubOutCard(pData,wDataSize);
		}
	case SUB_S_SEND_CARD:		//������Ϣ
		{
			return OnSubSendCard(pData,wDataSize);
		}
	case SUB_S_OPERATE_NOTIFY:	//������ʾ
		{
			return OnSubOperateNotify(pData,wDataSize);
		}
	case SUB_S_OPERATE_RESULT:	//�������
		{
			return OnSubOperateResult(pData,wDataSize);
		}
	case SUB_S_GAME_END:		//��Ϸ����
		{
			return OnSubGameEnd(pData,wDataSize);
		}
 
	}

	return true;
}

//��Ϸ��Ϣ
bool __cdecl CAndroidUserItemSink::OnEventFrameMessage(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	return true;
}

//������Ϣ
bool __cdecl CAndroidUserItemSink::OnEventGameScene(BYTE cbGameStatus, bool bLookonOther, void * pData, WORD wDataSize)
{
	switch (cbGameStatus)
	{
	case GS_MJ_FREE:	//����״̬
		{
			//Ч������
			if (wDataSize!=sizeof(CMD_S_StatusFree)) return false;
			CMD_S_StatusFree * pStatusFree=(CMD_S_StatusFree *)pData;
			IServerUserItem * pIServerUserItem=m_pIAndroidUserItem->GetMeUserItem();

			//��������
			m_wBankerUser=pStatusFree->wBankerUser;

			if( pIServerUserItem->GetUserStatus() != US_READY )
			{
				UINT nElapse = rand()%TIME_START_GAME+TIME_LESS;
				m_pIAndroidUserItem->SetGameTimer(IDI_START_GAME,nElapse);
			}
			return true;
		}
	case GS_MJ_PLAY:	//��Ϸ״̬
		{
			//Ч������
			if (wDataSize!=sizeof(CMD_S_StatusPlay)) return false;
			CMD_S_StatusPlay * pStatusPlay=(CMD_S_StatusPlay *)pData;

			//���ñ���
			m_wBankerUser=pStatusPlay->wBankerUser;
			m_wCurrentUser=pStatusPlay->wCurrentUser;
			m_cbLeftCardCount=pStatusPlay->cbLeftCardCount;

			//����״̬
			WORD wMeChairID=m_pIAndroidUserItem->GetChairID();
#ifdef CONSOLE_OMA			
#else 
			m_bHearStatus=(pStatusPlay->cbHearStatus[wMeChairID]==TRUE)?true:false;
#endif
			//��ʷ����
			m_wOutCardUser=pStatusPlay->wOutCardUser;
			m_cbOutCardData=pStatusPlay->cbOutCardData;
			CopyMemory(m_cbDiscardCard,pStatusPlay->cbDiscardCard,sizeof(m_cbDiscardCard));
			CopyMemory(m_cbDiscardCount,pStatusPlay->cbDiscardCount,sizeof(m_cbDiscardCount));

			//�˿˱���
			CopyMemory(m_cbWeaveCount,pStatusPlay->cbWeaveCount,sizeof(m_cbWeaveCount));
			CopyMemory(m_WeaveItemArray,pStatusPlay->WeaveItemArray,sizeof(m_WeaveItemArray));
			m_GameLogic.SwitchToCardIndex(pStatusPlay->cbCardData,pStatusPlay->cbCardCount,m_cbCardIndex[m_pIAndroidUserItem->GetChairID()]);

			//��������
			if ((pStatusPlay->cbActionMask!=WIK_NULL))
			{
				UINT nElapse = rand()%TIME_OPERATE_CARD+TIME_LESS;
				m_pIAndroidUserItem->SetGameTimer(IDI_OPERATE_CARD,nElapse);
			}
			if (m_wCurrentUser==m_pIAndroidUserItem->GetChairID()) 
			{
				{
					UINT nElapse = rand()%TIME_OPERATE_CARD+TIME_LESS;
					m_pIAndroidUserItem->SetGameTimer(IDI_OPERATE_CARD,nElapse);
				}

			}

			return true;
		}
	}

	return false;
}

//�û�����
void __cdecl CAndroidUserItemSink::OnEventUserEnter(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û��뿪
void __cdecl CAndroidUserItemSink::OnEventUserLeave(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û�����
void __cdecl CAndroidUserItemSink::OnEventUserScore(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û�״̬
void __cdecl CAndroidUserItemSink::OnEventUserStatus(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//�û���λ
void __cdecl CAndroidUserItemSink::OnEventUserSegment(IAndroidUserItem * pIAndroidUserItem, bool bLookonUser)
{
	return;
}

//ׯ����Ϣ
bool CAndroidUserItemSink::OnSubGameStart(void * pData, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GameStart));
	if (wDataSize!=sizeof(CMD_S_GameStart)) return false;

	//��������
	CMD_S_GameStart * pGameStart=(CMD_S_GameStart *)pData;

	//����״̬
	m_pIAndroidUserItem->SetGameStatus(GS_MJ_PLAY);

	//���ñ���
	m_bHearStatus=false;
	m_bWillHearStatus=false;
	m_wBankerUser=pGameStart->wBankerUser;
	m_wCurrentUser=pGameStart->wCurrentUser;
	m_cbLeftCardCount=MAX_REPERTORY-GAME_PLAYER*(MAX_COUNT-1)-1;
	m_bActionMask = WIK_NULL;
	m_cbActionCard = 0;

	//������Ϣ
	m_cbOutCardData=0;
	m_wOutCardUser=INVALID_CHAIR;
	ZeroMemory(m_cbDiscardCard,sizeof(m_cbDiscardCard));
	ZeroMemory(m_cbDiscardCount,sizeof(m_cbDiscardCount));
	//m_cbSendCardData = 0;

	//����˿�
	ZeroMemory(m_cbWeaveCount,sizeof(m_cbWeaveCount));
	ZeroMemory(m_WeaveItemArray,sizeof(m_WeaveItemArray));

	//�����˿�
	WORD wMeChairId = m_pIAndroidUserItem->GetChairID();
	BYTE cbCardCount = (wMeChairId==m_wBankerUser)?MAX_COUNT:(MAX_COUNT-1);
	m_GameLogic.SwitchToCardIndex(pGameStart->cbCardData,cbCardCount,m_cbCardIndex[wMeChairId]);

#ifdef CONSOLE_OMA
	ZeroMemory(&m_CurGangResult,sizeof(m_CurGangResult));
	m_GameLogic.AnalyseGangCard(m_cbCardIndex[wMeChairId],m_WeaveItemArray[wMeChairId],
		m_cbWeaveCount[wMeChairId],m_CurGangResult);

	////_c//printf("android OnSubGameStart GANG card count: %x\n ",m_CurGangResult.cbCardCount);
//	//printf("android OnSubGameStart GANG card data: %x\n ",m_CurGangResult.cbCardCount);

	for (BYTE j = 0;j<m_CurGangResult.cbCardCount;j++)
	{
	//	//_c//printf("android OnSubGameStart GANG card data: %x\n ",m_CurGangResult.cbCardData[j]);
	//	//printf("android OnSubGameStart GANG card data: %x\n ",m_CurGangResult.cbCardData[j]);

	}

#endif 

	
	//��������
	if ((pGameStart->cbUserAction!=WIK_NULL) || pGameStart->wCurrentUser==m_pIAndroidUserItem->GetChairID() )
	{
		m_bActionMask = pGameStart->cbUserAction;
		UINT nElapse = rand()%TIME_OPERATE_CARD+TIME_LESS;
		m_pIAndroidUserItem->SetGameTimer(IDI_OPERATE_CARD,3+nElapse);
	}

	return true;
}

//��Ϸ����
bool CAndroidUserItemSink::OnSubGameEnd(void * pData, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_GameEnd));
	if (wDataSize!=sizeof(CMD_S_GameEnd)) return false;

	//��Ϣ����
	CMD_S_GameEnd * pGameEnd=(CMD_S_GameEnd *)pData;

	//����״̬
	m_pIAndroidUserItem->SetGameStatus(GS_MJ_FREE);

	//ɾ����ʱ��
	m_pIAndroidUserItem->KillGameTimer(IDI_OPERATE_CARD);

	//����
	UINT nElapse = rand()%TIME_START_GAME+TIME_LESS;
	m_pIAndroidUserItem->SetGameTimer(IDI_START_GAME,nElapse);

	return true;
}



//������ʾ
bool CAndroidUserItemSink::OnSubOperateNotify( const void *pBuffer,WORD wDataSize )
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_OperateNotify));
	if (wDataSize!=sizeof(CMD_S_OperateNotify)) return false;

	// OnSubOperateNotify���ڣ� �������û����ƣ�֪ͨ������Ӧ���û� 
	//��������
	CMD_S_OperateNotify * pOperateNotify=(CMD_S_OperateNotify *)pBuffer;
	


 // //_c//printf("android  OnSubOperateNotify --- wMeChairID: %d m_bActionMask: %x cbActionCard: %x \n",m_pIAndroidUserItem->GetChairID(),pOperateNotify->cbActionMask,pOperateNotify->cbActionCard);
 // //printf("android  OnSubOperateNotify --- wMeChairID: %d m_bActionMask: %x cbActionCard: %x \n",m_pIAndroidUserItem->GetChairID(),pOperateNotify->cbActionMask,pOperateNotify->cbActionCard);


	//�û�����
	if ((pOperateNotify->cbActionMask!=WIK_NULL))
	{
		//��ȡ����
		WORD wMeChairID=m_pIAndroidUserItem->GetChairID();
		m_bActionMask = pOperateNotify->cbActionMask;
		m_cbActionCard=pOperateNotify->cbActionCard;
		

	//	//_c//printf("android  OnSubOperateNotify : wMeChairID: %d  m_bActionMask: %x m_cbActionCard: %x \n",wMeChairID,m_bActionMask,m_cbActionCard);
	//	//printf("android  OnSubOperateNotify : wMeChairID: %d  m_bActionMask: %x m_cbActionCard: %x \n",wMeChairID,m_bActionMask,m_cbActionCard);

#ifdef CONSOLE_OMA
		// ���� �� ����
		if(pOperateNotify->cbActionMask&WIK_GANG)
		{
		//	//_c//printf("android  OnSubOperateNotify  WIK_GANG before \n");
		//	//printf("android  OnSubOperateNotify  WIK_GANG before \n");

			for (BYTE kk = 0;kk<MAX_INDEX;kk++)
			{
				if (kk%9 ==0)
				{
				//	//_c//printf(" \n");
				//	//printf(" \n");

				}
				////_c//printf("%d ",m_cbCardIndex[wMeChairID][kk]);
			//	//printf("%d ",m_cbCardIndex[wMeChairID][kk]);

			}

		//	//_c//printf(" \n");
		//	//printf(" \n");

			ZeroMemory(&m_CurGangResult,sizeof(m_CurGangResult));
			m_GameLogic.AnalyseGangCard(m_cbCardIndex[wMeChairID],m_WeaveItemArray[wMeChairID],
				m_cbWeaveCount[wMeChairID],m_CurGangResult);
			
			for (BYTE j = 0;j<m_CurGangResult.cbCardCount;j++)
			{
				////_c//printf("android GANG card data: %x\n ",m_CurGangResult.cbCardData[j]);
			//	//printf("android GANG card data: %x\n ",m_CurGangResult.cbCardData[j]);

			}
		}
#if 1	
		if (pOperateNotify->cbActionMask&WIK_TI_PAI)
		{
		//	//_c//printf("android  OnSubOperateNotify  WIK_TI_PAI before \n");
		//	//printf("android  OnSubOperateNotify  WIK_TI_PAI before \n");

			
			for (BYTE kk = 0;kk<MAX_INDEX;kk++)
			{
				if (kk%9 ==0)
				{
				//	//_c//printf(" \n");
				//	//printf(" \n");

				}
				////_c//printf("%d ",m_cbCardIndex[m_wCurrentUser][kk]);
				////printf("%d ",m_cbCardIndex[m_wCurrentUser][kk]);

			}

			////_c//printf(" \n");
			////printf(" \n");



			ZeroMemory(&m_CurTIResult,sizeof(m_CurTIResult));

			//m_CurTIResult.cbCardCount = 1;
			//m_CurTIResult.cbCardData[0] = m_cbActionCard;

			m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wMeChairID],m_WeaveItemArray[wMeChairID],
				m_cbWeaveCount[wMeChairID],m_CurTIResult);

		//	//_c//printf("android TI card cbCardCount: %x\n ",m_CurTIResult.cbCardCount);
		//	//printf("android TI card cbCardCount: %x\n ",m_CurTIResult.cbCardCount);


			for (BYTE j = 0;j<m_CurTIResult.cbCardCount;j++)
			{
		//		//_c//printf("android TI card data: %x\n ",m_CurTIResult.cbCardData[j]);
		//		//printf("android TI card data: %x\n ",m_CurTIResult.cbCardData[j]);

			}



		}
#endif 


	//	//_c//printf("android wMeChairID:%d OnSubOperateNotify CARD DATA \n",wMeChairID);
	//	//printf("android  wMeChairID%d OnSubOperateNotify  CARD  DATA \n",wMeChairID);


		for (BYTE kk = 0;kk<MAX_INDEX;kk++)
		{
			if (kk%9 ==0)
			{
		//		//_c//printf(" \n");
		//		//printf(" \n");

			}
		//	//_c//printf("%d ",m_cbCardIndex[wMeChairID][kk]);
		//	//printf("%d ",m_cbCardIndex[wMeChairID][kk]);

		}

	//	//_c//printf(" \n");
	//	//printf(" \n");


		//����ʱ��
	//	UINT nElapse = rand()%TIME_OPERATE_CARD+TIME_LESS;
		//UINT nElapse = 0;
		//if (wMeChairID == 0)
		//{
		//	nElapse = 2;
		//}else if (wMeChairID == 1)
		//{
		//	nElapse = 2;
		//}else if (wMeChairID == 2)
		//{
		//	nElapse = 2;
		//}else if (wMeChairID == 3)
		//{
		//	nElapse = 2;
		//}

	// //_c//printf("android OnSubOperateNotify wMeChairID: %d nElapse: %d m_bActionMask: %x \n",wMeChairID,nElapse,m_bActionMask);

	//	UINT nElapse = TIME_OPERATE_CARD+TIME_LESS;
		UINT nElapse = 2;

	//	//_c//printf(" android wMeChairID: %d  start timer ..............nElapse: %d \n",wMeChairID,nElapse);
	//	//printf(" android wMeChairID: %d start timer ..............nElapse %d \n",wMeChairID,nElapse);

		//OnEventTimer(IDI_OPERATE_CARD);

		m_pIAndroidUserItem->SetGameTimer(IDI_OPERATE_CARD,nElapse);
	}
#endif 
	return true;
}

//
bool CAndroidUserItemSink::OnSubOperateResult( const void *pBuffer,WORD wDataSize )
{
	//Ч����Ϣ
	ASSERT(wDataSize==sizeof(CMD_S_OperateResult));
	if (wDataSize!=sizeof(CMD_S_OperateResult)) return false;

	//��Ϣ����
	CMD_S_OperateResult * pOperateResult=(CMD_S_OperateResult *)pBuffer;

	//��������
	BYTE cbPublicCard=TRUE;
	WORD wOperateUser=pOperateResult->wOperateUser;
	BYTE cbOperateCard=pOperateResult->cbOperateCard;

	//���Ʊ���
	if (pOperateResult->cbOperateCode!=WIK_NULL)
	{
		m_cbOutCardData=0;
		m_wOutCardUser=INVALID_CHAIR; // ���û���������û���û�����
	}

	//��������

	m_bActionMask = WIK_NULL;
	m_cbActionCard =0;
	m_pIAndroidUserItem->KillGameTimer(IDI_OPERATE_CARD);  // ����������


	//�������
	if ((pOperateResult->cbOperateCode&WIK_GANG)!=0)
	{
		//���ñ���
		m_wCurrentUser=INVALID_CHAIR; // û�е�ǰ�û������ƺ󣬲�֪����û��������

		//����˿�
		BYTE cbWeaveIndex=0xFF;
		for (BYTE i=0;i<m_cbWeaveCount[wOperateUser];i++) // �ж��Ƿ�����
		{
			BYTE cbWeaveKind=m_WeaveItemArray[wOperateUser][i].cbWeaveKind;
			BYTE cbCenterCard=m_WeaveItemArray[wOperateUser][i].cbCenterCard;
			if ((cbCenterCard==cbOperateCard)&&(cbWeaveKind==WIK_PENG)) // Ѱ���������
			{
				cbWeaveIndex=i;
				m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbPublicCard=TRUE;
				m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbWeaveKind=pOperateResult->cbOperateCode;
				m_WeaveItemArray[wOperateUser][cbWeaveIndex].wProvideUser=pOperateResult->wProvideUser;
				break;
			}
		}

		//����˿�
		if (cbWeaveIndex==0xFF)// ���û���ҵ����ܣ��������Ұ�������
		{
			//�����ж�
#ifdef CONSOLE_OMA
			cbPublicCard = TRUE; // OMA ���ø��ƿ���ʾ
#else
			cbPublicCard=(pOperateResult->wProvideUser==wOperateUser)?FALSE:TRUE;
#endif 
			//�����˿�
			cbWeaveIndex=m_cbWeaveCount[wOperateUser]++;
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbPublicCard=cbPublicCard;
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbCenterCard=cbOperateCard;
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbWeaveKind=pOperateResult->cbOperateCode;
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].wProvideUser=pOperateResult->wProvideUser;
		}

		//�˿�����
		if(wOperateUser==m_pIAndroidUserItem->GetChairID())
			m_cbCardIndex[wOperateUser][m_GameLogic.SwitchToCardIndex(pOperateResult->cbOperateCard)]=0;

	}
	else if (pOperateResult->cbOperateCode!=WIK_NULL&&pOperateResult->cbOperateCode!=WIK_CHI_HU)
	{
		// ���� �ܺ�֮��Ĳ�����������������ᣨ�����齫�� �����ԣ�
		//���ñ���
		m_wCurrentUser=pOperateResult->wOperateUser;
		
		BYTE cbWeaveIndex=0;

		if ((pOperateResult->cbOperateCode&WIK_TI_PAI)!=0) // ����,��������䣬���͸ı�
		{
			////_c//printf("OnSubOperateResult WIK_TI_PAI  \n");
			////printf("OnSubOperateResult WIK_TI_PAI  \n");


			for (BYTE kk = 0; kk< m_cbWeaveCount[wOperateUser];kk++)
			{
				if(m_WeaveItemArray[wOperateUser][kk].cbWeaveKind == WIK_TIE_PAI 
					&& m_WeaveItemArray[wOperateUser][kk].cbCenterCard == cbOperateCard) // ����
				{
					cbWeaveIndex = kk;
					m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbPublicCard=TRUE;
					m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbCenterCard=cbOperateCard;
					m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbWeaveKind=WIK_PENG; // ���ƺ��Ϊ������
					//m_WeaveItemArray[wOperateUser][cbWeaveIndex].wProvideUser=GetMeChairID();
					break;

				}
			}

			if(wOperateUser==m_pIAndroidUserItem->GetChairID())
			{
				////_c//printf("OnSubOperateResult WIK_TI_PAI card change before \n");
				////printf("OnSubOperateResult WIK_TI_PAI card change before \n");


				for (BYTE kk = 0;kk<MAX_INDEX;kk++)
				{
					if (kk%9 ==0)
					{
					//	//_c//printf(" \n");
					//	//printf(" \n");

					}
					////_c//printf("%d ",m_cbCardIndex[wOperateUser][kk]);
					////printf("%d ",m_cbCardIndex[wOperateUser][kk]);

				}

			//	//_c//printf(" \n");
			//	//printf(" \n");

				m_GameLogic.RemoveCard(m_cbCardIndex[wOperateUser],
					m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbCenterCard); // ɾ������
				m_cbCardIndex[wOperateUser][m_GameLogic.GetMagicIndex()]++;// ����ħ����
				
			//	//_c//printf("OnSubOperateResult WIK_TI_PAI card change after \n");
			//	//printf("OnSubOperateResult WIK_TI_PAI card change after \n");

				for (BYTE kk = 0;kk<MAX_INDEX;kk++)
				{
					if (kk%9 ==0)
					{
				//		//_c//printf(" \n");
				//		//printf(" \n");

					}
				//	//_c//printf("%d ",m_cbCardIndex[wOperateUser][kk]);
				//	//printf("%d ",m_cbCardIndex[wOperateUser][kk]);

				}

			//	//_c//printf(" \n");
			//	//printf(" \n");

			}
			////_c//printf("OnSubOperateResult WIK_TI_PAI ok \n");
			////printf("OnSubOperateResult WIK_TI_PAI ok \n");


		}else if((pOperateResult->cbOperateCode&WIK_TIE_PAI)!=0 || (pOperateResult->cbOperateCode&WIK_PENG)!=0) 
			// ���� һ����
		{
			// ����
			cbWeaveIndex=m_cbWeaveCount[wOperateUser]++;
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbPublicCard=TRUE;
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbCenterCard=cbOperateCard;
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].cbWeaveKind= pOperateResult->cbOperateCode; // ��ǰ����������
			m_WeaveItemArray[wOperateUser][cbWeaveIndex].wProvideUser=pOperateResult->wProvideUser;
		
			////_c//printf(" android WWWWWWWWWWWW OnSubOperateResult wOperateUser: %d cbOperateCard: %x  \n",wOperateUser,cbOperateCard);
			////printf(" android OOOOOOOOOOOOO OnSubOperateResult wOperateUser: %d cbOperateCard: %x  \n",wOperateUser,cbOperateCard);




			//��Ͻ���
			BYTE cbWeaveCard[4]={0,0,0,0},cbWeaveKind=pOperateResult->cbOperateCode;
			BYTE cbWeaveCardCount=m_GameLogic.GetWeaveCard(cbWeaveKind,cbOperateCard,cbWeaveCard);


			//ɾ���˿�
			if(wOperateUser==m_pIAndroidUserItem->GetChairID())
			{


				////_c//printf(" android WWWWWWWWWWWW OnSubOperateResult BEFORE Weave Card:  \n");
				////printf(" android WWWWWWWWWWWW OnSubOperateResult BEFORE Weave Card:  \n");

				for (BYTE j = 0;j<m_cbWeaveCount[wOperateUser];j++)
				{
					m_GameLogic.GetWeaveCard(m_WeaveItemArray[wOperateUser][j].cbWeaveKind,
						m_WeaveItemArray[wOperateUser][j].cbCenterCard,cbWeaveCard);
				//	//_c//printf(" %x  %x  %x  %x \n",cbWeaveCard[0],cbWeaveCard[1],cbWeaveCard[2],cbWeaveCard[3]);
				//	//printf(" %x  %x  %x  %x \n",cbWeaveCard[0],cbWeaveCard[1],cbWeaveCard[2],cbWeaveCard[3]);

				}


			//	//_c//printf("android OnSubOperateResult  pOperateResult->cbOperateCode: %x change before \n",pOperateResult->cbOperateCode);
			//	//printf("android OnSubOperateResult  pOperateResult->cbOperateCode: %x change before \n",pOperateResult->cbOperateCode);

				for (BYTE kk = 0;kk<MAX_INDEX;kk++)
				{
					if (kk%9 ==0)
					{
				//		//_c//printf(" \n");
				//		//printf(" \n");
					}
				//	//_c//printf("%d ",m_cbCardIndex[wOperateUser][kk]);
				//	//printf("%d ",m_cbCardIndex[wOperateUser][kk]);
				}

				////_c//printf(" \n");
				////printf(" \n");




				m_GameLogic.RemoveCard(cbWeaveCard,cbWeaveCardCount,&cbOperateCard,1); // cbWeaveCard ɾ��һ��Ҫ��������
				m_GameLogic.RemoveCard(m_cbCardIndex[wOperateUser],cbWeaveCard,cbWeaveCardCount-1);// ɾ��cbWeaveCard ʣ�µ���
				
				////_c//printf("android OnSubOperateResult  pOperateResult->cbOperateCode: %x change after \n",pOperateResult->cbOperateCode);
				////printf("android OnSubOperateResult  pOperateResult->cbOperateCode: %x change after \n",pOperateResult->cbOperateCode);

				for (BYTE kk = 0;kk<MAX_INDEX;kk++)
				{
					if (kk%9 ==0)
					{
					//	//_c//printf(" \n");
					//	//printf(" \n");

					}
				//	//_c//printf("%d ",m_cbCardIndex[wOperateUser][kk]);
				//	//printf("%d ",m_cbCardIndex[wOperateUser][kk]);

				}

			//	//_c//printf(" \n");
			//	//printf(" \n");


			//	//_c//printf(" android WWWWWWWWWWWW OnSubOperateResult after Weave Card:  \n");
			//	//printf(" android WWWWWWWWWWWW OnSubOperateResult after Weave Card:  \n");

				for (BYTE j = 0;j<m_cbWeaveCount[wOperateUser];j++)
				{
					m_GameLogic.GetWeaveCard(m_WeaveItemArray[wOperateUser][j].cbWeaveKind,
						m_WeaveItemArray[wOperateUser][j].cbCenterCard,cbWeaveCard);
				//	//_c//printf(" %x  %x  %x  %x \n",cbWeaveCard[0],cbWeaveCard[1],cbWeaveCard[2],cbWeaveCard[3]);
				//	//printf(" %x  %x  %x  %x \n",cbWeaveCard[0],cbWeaveCard[1],cbWeaveCard[2],cbWeaveCard[3]);

				}


			}



		}

	}

	//����ʱ��
	if (wOperateUser==m_pIAndroidUserItem->GetChairID())
	{
		
#ifdef CONSOLE_OMA
#else
		BYTE cbChiHuRight=0;
		BYTE cbActionMask=m_GameLogic.AnalyseTingCard(m_cbCardIndex[m_pIAndroidUserItem->GetChairID()],m_WeaveItemArray[m_pIAndroidUserItem->GetChairID()],m_cbWeaveCount[m_pIAndroidUserItem->GetChairID()],cbChiHuRight);
		if((cbActionMask==WIK_LISTEN)&&(m_bHearStatus==false))
		{
			if( !m_pIAndroidUserItem->SendSocketData(SUB_C_LISTEN_CARD))
			{
				ASSERT( FALSE );
				return false;
			}

			m_bHearStatus=true;

		}
#endif 
		//����ʱ��
		UINT nElapse=rand()%TIME_OPERATE_CARD+TIME_LESS;
		//if ((m_bHearStatus==true)) 
		//	nElapse=rand()%TIME_HEAR_STATUS+TIME_LESS;
		//ASSERT(FALSE);

	//	//_c//printf("android OnSubOperateResult SetGameTimer wOperateUser: %d nElapse : %d \n",wOperateUser,nElapse);
	//	//_c//printf("android OnSubOperateResult SetGameTimer wOperateUser: %d nElapse : %d \n",wOperateUser,nElapse);

		//nElapse = 5;
		//����ʱ��
		m_pIAndroidUserItem->SetGameTimer(IDI_OPERATE_CARD,nElapse);
	}

	return true;
}

//
bool CAndroidUserItemSink::OnSubOutCard( const void *pBuffer,WORD wDataSize )
{
	//Ч����Ϣ
	ASSERT(wDataSize==sizeof(CMD_S_OutCard));
	if (wDataSize!=sizeof(CMD_S_OutCard)) return false;

	//��Ϣ����
	CMD_S_OutCard * pOutCard=(CMD_S_OutCard *)pBuffer;

	//��������
	WORD wMeChairID=m_pIAndroidUserItem->GetChairID();


	//���ñ���
	m_wCurrentUser=INVALID_CHAIR;
	m_wOutCardUser=pOutCard->wOutCardUser;
	ASSERT( pOutCard->cbOutCardData != 0 );
	m_cbOutCardData=pOutCard->cbOutCardData;

	return true;
}

//
bool CAndroidUserItemSink::OnSubSendCard( const void *pBuffer,WORD wDataSize )
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_SendCard));
	if (wDataSize!=sizeof(CMD_S_SendCard)) return false;

	//��������
	CMD_S_SendCard * pSendCard=(CMD_S_SendCard *)pBuffer;

	//���ñ���
	WORD wMeChairID=m_pIAndroidUserItem->GetChairID();
	m_wCurrentUser = pSendCard->wCurrentUser;
	//
	////_c//printf("android OnSubSendCard --- pSendCard->wCurrentUser: %d pSendCard->cbCardData: %x pSendCard->cbActionMask :%x \n",
	//	pSendCard->wCurrentUser,pSendCard->cbCardData,pSendCard->cbActionMask);

	////_c//printf("android OnSubSendCard wMeChairID: %d m_wCurrentUser: %d cbCardData: %x \n",wMeChairID,m_wCurrentUser,pSendCard->cbCardData);
	////_c//printf("android OnSubSendCard m_wOutCardUser: %d ActionMask: %x \n",m_wOutCardUser,pSendCard->cbActionMask);

	////printf("android OnSubSendCard wMeChairID: %d m_wCurrentUser: %d cbCardData: %x \n",wMeChairID,m_wCurrentUser,pSendCard->cbCardData);
	////printf("android OnSubSendCard m_wOutCardUser: %d ActionMask: %x pSendCard->wCurrentUser : %d \n",m_wOutCardUser,pSendCard->cbActionMask,pSendCard->wCurrentUser);

	//�����˿�
	if ((m_wOutCardUser!=INVALID_CHAIR)&&(m_cbOutCardData!=0))
	{
		//�����˿�
		m_cbDiscardCard[m_wOutCardUser][m_cbDiscardCount[m_wOutCardUser]++] = m_cbOutCardData;
		//���ñ���
		m_cbOutCardData=0;
		m_wOutCardUser=INVALID_CHAIR;
	}

	//���ƴ���
	if ((pSendCard->cbCardData!=0)&&((m_wCurrentUser==wMeChairID)))
	{
		m_cbCardIndex[m_wCurrentUser][m_GameLogic.SwitchToCardIndex(pSendCard->cbCardData)]++;	
		//�۳��˿�
		m_cbLeftCardCount--;
	}

	//��ǰ�û�
	if ((m_wCurrentUser==wMeChairID))
	{

		
#ifdef CONSOLE_OMA
		m_cbSendCardData = pSendCard->cbCardData;
		ZeroMemory(&m_CurGangResult,sizeof(m_CurGangResult));
		ZeroMemory(&m_CurTIResult,sizeof(m_CurTIResult));
#else
		m_cbSendCardData = pSendCard->cbCardData;

		//�����ж�
		if (m_bHearStatus==false)
		{
			BYTE cbChiHuRight=0;
			BYTE cbWeaveCount=m_cbWeaveCount[wMeChairID];
			if( WIK_LISTEN==m_GameLogic.AnalyseTingCard(m_cbCardIndex[wMeChairID],m_WeaveItemArray[wMeChairID],cbWeaveCount,cbChiHuRight) )
			{
				m_bWillHearStatus = true;
			}
			else 
				m_bWillHearStatus = false;
		}
#endif
	}

	//����ʱ��
	if( wMeChairID == m_wCurrentUser )
	{
		m_bActionMask = pSendCard->cbActionMask;
		
		
		if (m_bActionMask&WIK_TI_PAI)
		{

			//printf("android   OnSubSendCard BEFORE card DATA: \n");
			for (BYTE kk = 0;kk<MAX_INDEX;kk++)
			{
				if (kk%9 ==0)
				{
			//		//_c//printf(" \n");
			//		//printf(" \n");
				}
			//	//_c//printf("%d ",m_cbCardIndex[m_wCurrentUser][kk]);
			//	//printf("%d ",m_cbCardIndex[m_wCurrentUser][kk]);
			}

			////_c//printf(" \n");
			////printf(" \n");



			BYTE cbWeaveCount=m_cbWeaveCount[wMeChairID];
		//	//_c//printf("android TI PAI Weave card data: \n");
			for (BYTE j = 0;j<cbWeaveCount;j++)
			{
				BYTE cbWeaveCard[4] ={0,0,0,0};
				m_GameLogic.GetWeaveCard(m_WeaveItemArray[wMeChairID][j].cbWeaveKind,m_WeaveItemArray[wMeChairID][j].cbCenterCard,cbWeaveCard);
			//	//_c//printf(" %x  %x  %x  %x\n",cbWeaveCard[0],cbWeaveCard[1],cbWeaveCard[2],cbWeaveCard[3]);
			}
		
			
			m_GameLogic.AnalyseTIPaiCard(m_cbCardIndex[wMeChairID],m_WeaveItemArray[wMeChairID],cbWeaveCount,m_CurTIResult);

		//	//_c//printf("m_CurTIResult wMeChairID: %d count %d \n",wMeChairID,m_CurTIResult.cbCardCount);
		//	//printf("m_CurTIResult wMeChairID: %d count %d \n",wMeChairID,m_CurTIResult.cbCardCount);

			for (BYTE j = 0;j<m_CurTIResult.cbCardCount;j++)
			{
		//		//_c//printf("TI PAI Option  [%d]......cbCardData: %x \n",j,m_CurTIResult.cbCardData[j]);
		//		//printf("TI PAI Option  [%d]......cbCardData: %x \n",j,m_CurTIResult.cbCardData[j]);

			}
		}
		
		if (m_bActionMask&WIK_GANG)
		{
			BYTE cbWeaveCount=m_cbWeaveCount[wMeChairID];
			m_GameLogic.AnalyseGangCard(m_cbCardIndex[wMeChairID],m_WeaveItemArray[wMeChairID],cbWeaveCount,m_CurGangResult);
			for (BYTE j = 0;j<m_CurGangResult.cbCardCount;j++)
			{
			//	//_c//printf("GANG PAI Option [%d]......cbCardData: %x \n",j,m_CurGangResult.cbCardData[j]);
			//	//printf("GANG PAI Option [%d]......cbCardData: %x \n",j,m_CurGangResult.cbCardData[j]);

			}

		}
		
		//m_cbActionCard = m_cbSendCardData;
	//	//_c//printf("android OnSubSendCard (m_wCurrentUser==wMeChairID) m_bActionMask: %x m_cbActionCard: %x \n",m_bActionMask,m_cbActionCard);

#ifdef CONSOLE_OMA
		// oma no WIK_LISTEN need.
#else
		if( (m_bWillHearStatus == true)&&(m_bHearStatus==false) )
			m_bActionMask |= WIK_LISTEN;

		if((m_bActionMask&WIK_LISTEN)&&(m_bHearStatus==false))
		{
			if( !m_pIAndroidUserItem->SendSocketData(SUB_C_LISTEN_CARD))
			{
				ASSERT( FALSE );
				return false;
			}

			m_bHearStatus=true;

		}
		//����ʱ��
		UINT nElapse=rand()%TIME_OPERATE_CARD+TIME_LESS;
		if ((m_bHearStatus==true)&&(m_wCurrentUser==wMeChairID)) 
			nElapse=rand()%TIME_HEAR_STATUS+TIME_LESS;

#endif
		////����ʱ��
		//UINT nElapse=rand()%TIME_OPERATE_CARD+TIME_LESS;
		//if ((m_bHearStatus==true)&&(m_wCurrentUser==wMeChairID)) 
		//	nElapse=rand()%TIME_HEAR_STATUS+TIME_LESS;

		UINT nElapse = 2;
		m_pIAndroidUserItem->SetGameTimer(IDI_OPERATE_CARD,nElapse);
	}

	return true;
}

#ifdef CONSOLE_OMA
#else 
//�û�����
bool CAndroidUserItemSink::OnSubListenCard(const void * pBuffer, WORD wDataSize)
{
	//Ч������
	ASSERT(wDataSize==sizeof(CMD_S_ListenCard));
	if (wDataSize!=sizeof(CMD_S_ListenCard))
		return false;

	//��������
	CMD_S_ListenCard * pListenCard=(CMD_S_ListenCard *)pBuffer;
	if(pListenCard->wListenUser==m_pIAndroidUserItem->GetChairID())
	{
		m_bHearStatus=true;
	}
	return true;

}
#endif 

//�û�����
void CAndroidUserItemSink::OnOutCard( BYTE cbOutCard )
{
	//��������
	if (m_bWillHearStatus==true)
	{
		m_bHearStatus=true;
		m_bWillHearStatus=false;
	}

	//���ñ���
	m_wCurrentUser=INVALID_CHAIR;
	WORD wMeChairId = m_pIAndroidUserItem->GetChairID();
	m_GameLogic.RemoveCard(m_cbCardIndex[wMeChairId],cbOutCard);

	//���ý���
	m_pIAndroidUserItem->KillGameTimer(IDI_OPERATE_CARD);
	m_cbSendCardData=0;

	//��������
	CMD_C_OutCard OutCard;
	OutCard.cbCardData=cbOutCard;
	if( !m_pIAndroidUserItem->SendSocketData(SUB_C_OUT_CARD,&OutCard,sizeof(OutCard)) )
	{
		ASSERT( FALSE );
		return ;
	}

	//���ñ���
	m_bActionMask = WIK_NULL;
	
	return ;
}

//
void CAndroidUserItemSink::OnOperateCard( BYTE cbOperateCode,BYTE cbOperateCard )
{
	//ɾ��ʱ��
	m_pIAndroidUserItem->KillGameTimer(IDI_OPERATE_CARD);


#ifdef CONSOLE_OMA

#else
	//��������
	tagGangCardResult GangCardResult;
	ZeroMemory(&GangCardResult,sizeof(GangCardResult));

	//��ȡ����
	if (m_wCurrentUser==m_pIAndroidUserItem->GetChairID())
	{
		WORD wMeChairID=m_pIAndroidUserItem->GetChairID();
		BYTE cbWeaveCount=m_cbWeaveCount[wMeChairID];
		m_GameLogic.AnalyseGangCard(m_cbCardIndex[wMeChairID],m_WeaveItemArray[wMeChairID],cbWeaveCount,GangCardResult);
	}
	else
	{
		GangCardResult.cbCardCount=1;
		GangCardResult.cbCardData[0]=m_cbActionCard;

	}
#endif 

	//��������
	CMD_C_OperateCard OperateCard;
	OperateCard.cbOperateCode=cbOperateCode;
#ifdef CONSOLE_OMA
	if (((cbOperateCard==0)&&(cbOperateCode&WIK_GANG)))
	{
		OperateCard.cbOperateCard = m_CurGangResult.cbCardData[0];
	}else if (((cbOperateCard==0)&&(cbOperateCode&WIK_TI_PAI)))
	{
		OperateCard.cbOperateCard = m_CurTIResult.cbCardData[0];
	}else
	{
		OperateCard.cbOperateCard  = cbOperateCard;
	}

//	OperateCard.cbOperateCard=(((cbOperateCard==0)&&(cbOperateCode&WIK_GANG)))?GangCardResult.cbCardData[0]:cbOperateCard;
#else
	OperateCard.cbOperateCard=(((cbOperateCard==0)&&(cbOperateCode&WIK_GANG)))?GangCardResult.cbCardData[0]:cbOperateCard;
#endif 
	if( !m_pIAndroidUserItem->SendSocketData(SUB_C_OPERATE_CARD,&OperateCard,sizeof(OperateCard)) )
	{
		ASSERT( FALSE );
		return ;
	}

	//��������
	m_bActionMask = WIK_NULL;

	////_c//printf("OnOperateCard cbOperateCode: %x  ok\n",cbOperateCode);
	////printf("OnOperateCard cbOperateCode: %x  ok\n",cbOperateCode);

	return ;
}
//���ܴ���
BYTE CAndroidUserItemSink::GetIsolatedCard()
{

	//�������
	WORD wMeChairID=m_pIAndroidUserItem->GetChairID();
	int i=0;
#ifdef CONSOLE_OMA
	int colorNum[3] = {0,0,0};
	BYTE cbCard = 0xFF;

	for(int k = 0;k<m_cbWeaveCount[wMeChairID];k++)
	{
		tagWeaveItem item = m_WeaveItemArray[wMeChairID][k];
		cbCard = item.cbCenterCard;
		int number = 0;
		if(item.cbWeaveKind == WIK_PENG || item.cbWeaveKind ==WIK_TIE_PAI)
			number = 3;
		else if(item.cbWeaveKind == WIK_GANG)
			number = 4;
		
		if((cbCard&0xF0)>>4==0)
		{
				colorNum[0]+=number;
		}else if((cbCard&0xF0)>>4==1)
		{
				colorNum[1]+=number;
		}else if((cbCard&0xF0)>>4==2)
		{
				colorNum[2]+=number;
		}
	}

	for( i=0; i<27; i++)
	{

		if(m_GameLogic.GetMagicIndex() == i)
		{
			continue;
		}

		

		if(m_cbCardIndex[wMeChairID][i]>0)
 		{
	 		cbCard = m_GameLogic.SwitchToCardData(i);
		
			if((cbCard&0xF0)>>4==0)
			{
				colorNum[0]++;
			}else if((cbCard&0xF0)>>4==1)
			{
				colorNum[1]++;
			}else if((cbCard&0xF0)>>4==2)
			{
				colorNum[2]++;
			}
		}

	}

	

// ��ȱ
	int minIndex = 0;
		if(colorNum[0] < colorNum[1])
			minIndex = 0;			
		else minIndex = 1;	
		if(colorNum[minIndex] > colorNum[2])
			minIndex = 2;			

		if(colorNum[minIndex] > 0) // ��δ��ȱ
		{
			for(int i = minIndex*9;i<=minIndex*9+8;i++)
			{
				if(m_cbCardIndex[wMeChairID][i]>0)
				return m_GameLogic.SwitchToCardData(i);
			}

		}

#else
	//�з���
	for( i=27; i<27+7; i++)
	{
		
		if(m_cbCardIndex[wMeChairID][i]==1)
		{
			return m_GameLogic.SwitchToCardData(i);
		}
	}
#endif

	//�й��ƴ����
	//��1,9����
	for(i=0; i<3; i++)
	{


	
		if(m_cbCardIndex[wMeChairID][i*9]==1) // ����
		{
			if((m_cbCardIndex[wMeChairID][i*9+1]==0)&&(m_cbCardIndex[wMeChairID][i*9+2]==0))//�ж�û�� 23
			{
#ifdef CONSOLE_OMA
				if(m_GameLogic.GetMagicIndex() == i*9)
				{
					continue;
				}else
#endif 
				return m_GameLogic.SwitchToCardData(i*9);
			}
		}
		if(m_cbCardIndex[wMeChairID][i*9+8]==1) // ���
		{
			if((m_cbCardIndex[wMeChairID][i*9+7]==0)&&(m_cbCardIndex[wMeChairID][i*9+6]==0)) // �ж�û�� 78
			{
			//	//_c//printf("GetIsolatedCard 22222222 : %x \n",m_GameLogic.SwitchToCardData(i*9+8));
			//	//printf("GetIsolatedCard 22222222 : %x \n",m_GameLogic.SwitchToCardData(i*9+8));


				if(m_GameLogic.GetMagicIndex() == i*9+8)
				{
					continue;
				}else
				return m_GameLogic.SwitchToCardData(i*9+8);
			}
		}
	}
	//����ͨ����
	for( i=0; i<27; i++)
	{
		if(m_cbCardIndex[wMeChairID][i]==1)
		{

#ifdef CONSOLE_OMA
			if(m_GameLogic.GetMagicIndex() == i)
				continue;
#endif 
			BYTE cbTmp = i%9;
			switch(cbTmp)
			{
			case 0:
				if((m_cbCardIndex[wMeChairID][i+1]==0)
					&& (m_cbCardIndex[wMeChairID][i+2]==0))
				{
					////_c//printf("GetIsolatedCard 33333333 : %x \n",m_GameLogic.SwitchToCardData(i));
					////printf("GetIsolatedCard 33333333 : %x \n",m_GameLogic.SwitchToCardData(i));
					return m_GameLogic.SwitchToCardData(i);
				}
				break;
			case 1:
				if((m_cbCardIndex[wMeChairID][i+1]==0)
					&&(m_cbCardIndex[wMeChairID][i+2]==0)
					&&(m_cbCardIndex[wMeChairID][i-1]==0))
				{
				//	//_c//printf("GetIsolatedCard 44444444 : %x \n",m_GameLogic.SwitchToCardData(i));
				//	//printf("GetIsolatedCard 44444444 : %x \n",m_GameLogic.SwitchToCardData(i));

					return m_GameLogic.SwitchToCardData(i);
				}
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				if((m_cbCardIndex[wMeChairID][i+1]==0)
					&&(m_cbCardIndex[wMeChairID][i+2]==0)
					&&(m_cbCardIndex[wMeChairID][i-1]==0)
					&& (m_cbCardIndex[wMeChairID][i-2]==0))
				{
					////_c//printf("GetIsolatedCard 55555 : %x \n",m_GameLogic.SwitchToCardData(i));
					////printf("GetIsolatedCard 55555 : %x \n",m_GameLogic.SwitchToCardData(i));

					return m_GameLogic.SwitchToCardData(i);
				}
				break;
			case 7:
				if((m_cbCardIndex[wMeChairID][i-1]==0)
					&&(m_cbCardIndex[m_pIAndroidUserItem->GetChairID()][i-2]==0)
					&&(m_cbCardIndex[m_pIAndroidUserItem->GetChairID()][i+1]==0))
				{
				//	//_c//printf("GetIsolatedCard 6666666 : %x \n",m_GameLogic.SwitchToCardData(i));
				//	//printf("GetIsolatedCard 6666666 : %x \n",m_GameLogic.SwitchToCardData(i));

					return m_GameLogic.SwitchToCardData(i);
				}
				break;
			case 8:
				if((m_cbCardIndex[wMeChairID][i-1]==0)
					&&(m_cbCardIndex[m_pIAndroidUserItem->GetChairID()][i-2]==0))
				{
				//	//_c//printf("GetIsolatedCard 777777777 : %x \n",m_GameLogic.SwitchToCardData(i));
				//	//printf("GetIsolatedCard 777777777 : %x \n",m_GameLogic.SwitchToCardData(i));

					return m_GameLogic.SwitchToCardData(i);
				}
				break;
			}
			if(cbTmp < 3)
			{
				i += 5;
			}
			else
			{
				i = (i/9+1)*9 - 1;
			}
		}	
	}

	//����
	//��19����
	for(i=0; i<3; i++)
	{
		if(m_cbCardIndex[wMeChairID][i*9] == 1)
		{
			if(m_cbCardIndex[wMeChairID][i*9+1] == 0
				|| m_cbCardIndex[wMeChairID][i*9+2] == 0)
			{
				////_c//printf("GetIsolatedCard 888888 : %x \n",m_GameLogic.SwitchToCardData(i*9));
				////printf("GetIsolatedCard 888888 : %x \n",m_GameLogic.SwitchToCardData(i*9));

#ifdef CONSOLE_OMA
				if(m_GameLogic.GetMagicIndex() == i*9)
				{
					continue;
				}else
#endif 


				return m_GameLogic.SwitchToCardData(i*9);
			}
		}
		if(m_cbCardIndex[wMeChairID][i*9+8] == 1)
		{
			if(m_cbCardIndex[wMeChairID][i*9+7] == 0
				|| m_cbCardIndex[wMeChairID][i*9+6] == 0)
			{
				////_c//printf("GetIsolatedCard 999999999 : %x \n",m_GameLogic.SwitchToCardData(i*9+8));
				////printf("GetIsolatedCard 999999999 : %x \n",m_GameLogic.SwitchToCardData(i*9+8));
#ifdef CONSOLE_OMA
				if(m_GameLogic.GetMagicIndex() == i*9+8)
				{
					continue;
				}else
#endif 

				return m_GameLogic.SwitchToCardData(i*9+8);
			}
		}
	}

	//����ͨ����
	for(i=0; i<27; i++)
	{

#ifdef CONSOLE_OMA
				if(m_GameLogic.GetMagicIndex() == i)
				{
					continue;
				}
#endif 

		if(m_cbCardIndex[wMeChairID][i] == 1)
		{
			if((i%9) == 0)
			{
				i += 3;
				continue;
			}
			if((i+1)%9 == 0)
			{
				continue;
			}
			if(m_cbCardIndex[wMeChairID][i+1] == 0
				&& m_cbCardIndex[wMeChairID][i-1] == 0)
			{
			//	//_c//printf("GetIsolatedCard 999999999000000 : %x \n",m_GameLogic.SwitchToCardData(i));
			//	//printf("GetIsolatedCard 999999999000000 : %x \n",m_GameLogic.SwitchToCardData(i));

				return m_GameLogic.SwitchToCardData(i);
			}
			i += 1;
		}	
	}


	return  0XFF;
}
//������Ŀ
BYTE CAndroidUserItemSink::GetIsolatedCardCount(BYTE cbCardIndex[MAX_INDEX])
{
	//��ʱ����
	BYTE cbTempCardIndex[MAX_INDEX];
	CopyMemory(cbTempCardIndex,cbCardIndex,sizeof(cbTempCardIndex));

	//�������
	WORD wMeChairID=m_pIAndroidUserItem->GetChairID();
	int i=0;
	int iIsolateCardCount=0;

#ifdef CONSOLE_OMA
#else
	//�з���
	for( i=27; i<27+7; i++)
	{
		if(cbTempCardIndex[i]==1)
		{
			iIsolateCardCount++;
		}
	}
#endif

	//�й��ƴ����
	//��19����
	for(i=0; i<3; i++)
	{

		if(cbTempCardIndex[i*9]==1)
		{
			if((cbTempCardIndex[i*9+1]==0)
				&&(cbTempCardIndex[i*9+2]==0))
			{
#ifdef CONSOLE_OMA
		if(m_GameLogic.GetMagicIndex() == i*9)
		{
			continue;
		}
#endif 

				iIsolateCardCount++;
			}
		}
		if(cbTempCardIndex[i*9+8]==1)
		{
			if((cbTempCardIndex[i*9+7]==0)
				&&(cbTempCardIndex[i*9+6]==0))
			{

#ifdef CONSOLE_OMA
		if(m_GameLogic.GetMagicIndex() == i*9+8)
		{
			continue;
		}
#endif 

				iIsolateCardCount++;
			}
		}
	}
	//����ͨ����
	for( i=0; i<27; i++)
	{
#ifdef CONSOLE_OMA
		if(m_GameLogic.GetMagicIndex() == i)
		{
			continue;
		}
#endif 

	
		if(cbTempCardIndex[i]==1)
		{
			BYTE cbTmp = i%9;
			switch(cbTmp)
			{
			case 0:
				if((cbTempCardIndex[i+1]==0)
					&& (cbTempCardIndex[i+2]==0))
				{
					iIsolateCardCount++;
				}
				break;
			case 1:
				if((cbTempCardIndex[i+1]==0)
					&&(cbTempCardIndex[i+2]==0)
					&&(cbTempCardIndex[i-1]==0))
				{
					iIsolateCardCount++;
				}
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				if((cbTempCardIndex[i+1]==0)
					&&(cbTempCardIndex[i+2]==0)
					&&(cbTempCardIndex[i-1]==0)
					&& (cbTempCardIndex[i-2]==0))
				{
					iIsolateCardCount++;
				}
				break;
			case 7:
				if((cbTempCardIndex[i-1]==0)
					&&(cbTempCardIndex[i-2]==0)
					&&(cbTempCardIndex[i+1]==0))
				{
					iIsolateCardCount++;
				}
				break;
			case 8:
				if((cbTempCardIndex[i-1]==0)
					&&(cbTempCardIndex[i-2]==0))
				{
					iIsolateCardCount++;
				}
				break;
			}
			if(cbTmp < 3)
			{
				i += 5;
			}
			else
			{
				i = (i/9+1)*9 - 1;
			}
		}	
	}

	//����
	//��19����
	for(i=0; i<3; i++)
	{

		if(cbTempCardIndex[i*9] == 1)
		{
			if(cbTempCardIndex[i*9+1] == 0
				|| cbTempCardIndex[i*9+2] == 0)
			{
#ifdef CONSOLE_OMA
		if(m_GameLogic.GetMagicIndex() == i*9)
		{
			continue;
		}
#endif 

				iIsolateCardCount++;
				
			}
		}
		if(cbTempCardIndex[i*9+8] == 1)
		{
			if(cbTempCardIndex[i*9+7] == 0
				|| cbTempCardIndex[i*9+6] == 0)
			{

#ifdef CONSOLE_OMA
		if(m_GameLogic.GetMagicIndex() == i*9)
		{
			continue;
		}
#endif 

				iIsolateCardCount++;
			}
		}
	}

	//����ͨ����
	for(i=0; i<27; i++)
	{
#ifdef CONSOLE_OMA
		if(m_GameLogic.GetMagicIndex() == i)
		{
			continue;
		}
#endif 

		if(cbTempCardIndex[i] == 1)
		{
			if((i%9) == 0)
			{
				i += 3;
				continue;
			}
			if((i+1)%9 == 0)
			{
				continue;
			}
			if(cbTempCardIndex[i+1] == 0
				&& cbTempCardIndex[i-1] == 0)
			{
				iIsolateCardCount++;
			}
			i += 1;
		}	
	}

	return  iIsolateCardCount;

}
BYTE CAndroidUserItemSink::GetTheBestOperate(BYTE cbOperateCode,BYTE cbOperateCard)
{
	//�������
	BYTE cbPreIsolateCardCount=GetIsolatedCardCount(m_cbCardIndex[m_pIAndroidUserItem->GetChairID()]);
	BYTE cbPengIsolateCardCount=0XFF;
	BYTE cbLeftIsolateCardCount=0XFF;
	BYTE cbCenterIsolateCradCount=0XFF;
	BYTE cbRightIsolateCardCount=0XFF;
#ifdef CONSOLE_OMA
	BYTE cbTiePaiIsolateCardCount=0XFF;
	//���Ʋ���
	if(cbOperateCode&WIK_TIE_PAI)
	{
		BYTE cbTempCardIndex[MAX_INDEX];
		CopyMemory(cbTempCardIndex,m_cbCardIndex[m_pIAndroidUserItem->GetChairID()],sizeof(cbTempCardIndex));

		//��Ͻ���
		BYTE cbWeaveCard[4]={0,0,0,0},cbWeaveKind=WIK_TIE_PAI;
		BYTE cbWeaveCardCount=m_GameLogic.GetWeaveCard(cbWeaveKind,cbOperateCard,cbWeaveCard);
		m_GameLogic.RemoveCard(cbWeaveCard,cbWeaveCardCount,&cbOperateCard,1);
		m_GameLogic.RemoveCard(cbTempCardIndex,cbWeaveCard,cbWeaveCardCount-1);
		cbTiePaiIsolateCardCount=GetIsolatedCardCount(cbTempCardIndex);
	}

#endif 




	//���Ʋ���
	if(cbOperateCode&WIK_PENG)
	{
		BYTE cbTempCardIndex[MAX_INDEX];
		CopyMemory(cbTempCardIndex,m_cbCardIndex[m_pIAndroidUserItem->GetChairID()],sizeof(cbTempCardIndex));

		//��Ͻ���
		BYTE cbWeaveCard[4]={0,0,0,0},cbWeaveKind=WIK_PENG;
		BYTE cbWeaveCardCount=m_GameLogic.GetWeaveCard(cbWeaveKind,cbOperateCard,cbWeaveCard);
		m_GameLogic.RemoveCard(cbWeaveCard,cbWeaveCardCount,&cbOperateCard,1);
		m_GameLogic.RemoveCard(cbTempCardIndex,cbWeaveCard,cbWeaveCardCount-1);
		cbPengIsolateCardCount=GetIsolatedCardCount(cbTempCardIndex);
	}
	//��Բ���
	if(cbOperateCode&WIK_LEFT)
	{
		BYTE cbTempCardIndex[MAX_INDEX];
		CopyMemory(cbTempCardIndex,m_cbCardIndex[m_pIAndroidUserItem->GetChairID()],sizeof(cbTempCardIndex));

		//��Ͻ���
		BYTE cbWeaveCard[4]={0,0,0,0},cbWeaveKind=WIK_LEFT;
		BYTE cbWeaveCardCount=m_GameLogic.GetWeaveCard(cbWeaveKind,cbOperateCard,cbWeaveCard);
		m_GameLogic.RemoveCard(cbWeaveCard,cbWeaveCardCount,&cbOperateCard,1);
		m_GameLogic.RemoveCard(cbTempCardIndex,cbWeaveCard,cbWeaveCardCount-1);
		cbLeftIsolateCardCount=GetIsolatedCardCount(cbTempCardIndex);
	}
	//�гԲ���
	if(cbOperateCode&WIK_CENTER)
	{
		BYTE cbTempCardIndex[MAX_INDEX];
		CopyMemory(cbTempCardIndex,m_cbCardIndex[m_pIAndroidUserItem->GetChairID()],sizeof(cbTempCardIndex));

		//��Ͻ���
		BYTE cbWeaveCard[4]={0,0,0,0},cbWeaveKind=WIK_CENTER;
		BYTE cbWeaveCardCount=m_GameLogic.GetWeaveCard(cbWeaveKind,cbOperateCard,cbWeaveCard);
		m_GameLogic.RemoveCard(cbWeaveCard,cbWeaveCardCount,&cbOperateCard,1);
		m_GameLogic.RemoveCard(cbTempCardIndex,cbWeaveCard,cbWeaveCardCount-1);
		cbCenterIsolateCradCount=GetIsolatedCardCount(cbTempCardIndex);
	}
	//�ҳԲ���
	if(cbOperateCode&WIK_RIGHT)
	{
		BYTE cbTempCardIndex[MAX_INDEX];
		CopyMemory(cbTempCardIndex,m_cbCardIndex[m_pIAndroidUserItem->GetChairID()],sizeof(cbTempCardIndex));

		//��Ͻ���
		BYTE cbWeaveCard[4]={0,0,0,0},cbWeaveKind=WIK_RIGHT;
		BYTE cbWeaveCardCount=m_GameLogic.GetWeaveCard(cbWeaveKind,cbOperateCard,cbWeaveCard);
		m_GameLogic.RemoveCard(cbWeaveCard,cbWeaveCardCount,&cbOperateCard,1);
		m_GameLogic.RemoveCard(cbTempCardIndex,cbWeaveCard,cbWeaveCardCount-1);
		cbRightIsolateCardCount=GetIsolatedCardCount(cbTempCardIndex);
	}

	
	//��������
	if(cbPengIsolateCardCount==0)
		return WIK_PENG;
#ifdef CONSOLE_OMA
	if(cbTiePaiIsolateCardCount==0)
		return WIK_TIE_PAI;
#endif 


	if(cbLeftIsolateCardCount==0)
		return WIK_LEFT;
	if(cbCenterIsolateCradCount==0)
		return WIK_CENTER;
	if(cbRightIsolateCardCount==0)
		return WIK_RIGHT;
	
	//����Ȩλ
	BYTE cbMin=0xFF;
	if(cbMin>cbPengIsolateCardCount)
		cbMin=cbPengIsolateCardCount;
#ifdef CONSOLE_OMA
	if(cbMin>cbTiePaiIsolateCardCount)
		cbMin=cbTiePaiIsolateCardCount;
#endif 

	if(cbMin>cbLeftIsolateCardCount)
		cbMin=cbLeftIsolateCardCount;
	if(cbMin>cbCenterIsolateCradCount)
		cbMin=cbCenterIsolateCradCount;
	if(cbMin>cbRightIsolateCardCount)
		cbMin=cbRightIsolateCardCount;
	ASSERT(cbMin!=0xFF);
	if(cbMin>cbPreIsolateCardCount)
		return WIK_NULL;
	if(cbMin==cbPengIsolateCardCount)
		return WIK_PENG;
	if(cbMin==cbLeftIsolateCardCount)
		return WIK_LEFT;
	if(cbMin==cbCenterIsolateCradCount)
		return WIK_CENTER;
	if(cbMin==cbRightIsolateCardCount)
		return WIK_RIGHT;
#ifdef CONSOLE_OMA
	if(cbMin==cbTiePaiIsolateCardCount)
		return WIK_TIE_PAI;
		//����Ȩλ
	if((cbOperateCode&WIK_TIE_PAI)&&(cbPreIsolateCardCount-1==cbTiePaiIsolateCardCount))
		return WIK_PENG;
#endif 

	//����Ȩλ
	if((cbOperateCode&WIK_PENG)&&(cbPreIsolateCardCount-1==cbPengIsolateCardCount))
		return WIK_PENG;
	if((cbOperateCode&WIK_LEFT)&&(cbPreIsolateCardCount-1==cbLeftIsolateCardCount))
		return WIK_LEFT;
	if((cbOperateCode&WIK_CENTER)&&(cbPreIsolateCardCount-1==cbCenterIsolateCradCount))
		return WIK_CENTER;
	if((cbOperateCode&WIK_RIGHT)&&(cbPreIsolateCardCount-1==cbRightIsolateCardCount))
		return WIK_RIGHT;
	return WIK_NULL;
}
//�����ж�
bool CAndroidUserItemSink::VerdictOutCard(BYTE cbCardData)
{
	//�����ж�
	if ((m_bHearStatus==true))
	{
		//��������
#ifdef CONSOLE_OMA
		CChiHuRight ChiHuResult;
#else 
		tagChiHuResult ChiHuResult;
#endif 	
		WORD wMeChairID=m_pIAndroidUserItem->GetChairID();
		BYTE cbWeaveCount=m_cbWeaveCount[wMeChairID];

		//�����˿�
		BYTE cbCardIndexTemp[MAX_INDEX];
		CopyMemory(cbCardIndexTemp,m_cbCardIndex[wMeChairID],sizeof(cbCardIndexTemp));

		//ɾ���˿�
		m_GameLogic.RemoveCard(cbCardIndexTemp,cbCardData);

		//�����ж�
		BYTE i=0;// oma
		for (i=0;i<MAX_INDEX;i++) // oma
		{
			//���Ʒ���
			
			
#ifdef CONSOLE_OMA
			BYTE cbCurrentCard=m_GameLogic.SwitchToCardData(i);
			BYTE cbHuCardKind=m_GameLogic.AnalyseChiHuCard(cbCardIndexTemp,m_WeaveItemArray[wMeChairID],cbWeaveCount,cbCurrentCard,ChiHuResult);
#else 
			BYTE wChiHuRight=0;	
			BYTE cbCurrentCard=m_GameLogic.SwitchToCardData(i);
			BYTE cbHuCardKind=m_GameLogic.AnalyseChiHuCard(cbCardIndexTemp,m_WeaveItemArray[wMeChairID],cbWeaveCount,cbCurrentCard,wChiHuRight,ChiHuResult);
#endif 
			//����ж�
			if (cbHuCardKind!=CHK_NULL) 
				break;
		}

		//�����ж�
		return (i!=MAX_INDEX);
	}

	return true;
}
#ifdef CONSOLE_OMA
//bool CAndroidUserItemSink::OnSubCardPaiJin( const void *pBuffer, WORD wDataSize )
//{
//
//	ASSERT(wDataSize==sizeof(CMD_S_PaiJing));
//	if (wDataSize!=sizeof(CMD_S_PaiJing)) return false;
//
//	ZeroMemory(&m_GameLogic.m_PaiJing,sizeof(m_GameLogic.m_PaiJing));
//	//��Ϣ����
//	CMD_S_PaiJing * pPaiJing=(CMD_S_PaiJing *)pBuffer;
//
//	m_GameLogic.SetMagicIndex(m_GameLogic.SwitchToCardIndex(pPaiJing->m_cbTingYongCard));
//
//	m_GameLogic.m_PaiJing.m_cbPaiJingCard = pPaiJing->m_cbPaiJingCard;
//	m_GameLogic.m_PaiJing.m_cbTingYongCard = pPaiJing->m_cbTingYongCard;
//
//	return true;
//
//}
bool CAndroidUserItemSink::OnSubUserChiHu( const void *pBuffer,WORD wDataSize )
{
	//Ч����Ϣ
	ASSERT(wDataSize==sizeof(CMD_S_ChiHu));
	if (wDataSize!=sizeof(CMD_S_ChiHu)) return false;

	//��Ϣ����
	CMD_S_ChiHu * pChiHu=(CMD_S_ChiHu *)pBuffer;
#ifdef CONSOLE_OMA
	bool bQiangGang = pChiHu->bGangStatus; // ��״̬
	bool bQiangTi = pChiHu->bTIStatus;     // ��״̬
	BYTE cbChiHuCard = pChiHu->cbChiHuCard; // �Ժ���
#endif 
	//��ȡ����
	WORD wMeChairID=m_pIAndroidUserItem->GetChairID();

	//ɾ����ʱ��
	m_pIAndroidUserItem->KillGameTimer(IDI_OPERATE_CARD);

#ifdef CONSOLE_OMA

	////_c//printf("android  wMeChairID:%d OnSubUserChiHu m_cbWeaveCount : %d pChiHu->bGangStatus: %d pChiHu->bTIStatus: %d \n",wMeChairID,m_cbWeaveCount[wMeChairID],pChiHu->bGangStatus,pChiHu->bTIStatus);
	////printf("android  wMeChairID:%d OnSubUserChiHu m_cbWeaveCount : %d pChiHu->bGangStatus: %d pChiHu->bTIStatus: %d \n",wMeChairID,m_cbWeaveCount[wMeChairID],pChiHu->bGangStatus,pChiHu->bTIStatus);

	// �ı������Ϊ������
	for (BYTE j = 0;j<m_cbWeaveCount[wMeChairID];j++)
	{
		BYTE cbCenterCard = m_WeaveItemArray[wMeChairID][j].cbCenterCard;
		BYTE cbWeaveKind = m_WeaveItemArray[wMeChairID][j].cbWeaveKind;
	//	//_c//printf("android  wMeChairID:%d OnSubUserChiHu before m_WeaveItem---- cbWeaveKind:%x cbCenterCard:%x \n",wMeChairID,cbWeaveKind,cbCenterCard);
	//	//printf("android wMeChairID:%d OnSubUserChiHu before m_WeaveItem---- cbWeaveKind:%x cbCenterCard:%x \n",wMeChairID,cbWeaveKind,cbCenterCard);

	}

	if (pChiHu->bGangStatus || pChiHu->bTIStatus)
	{
		//ɾ���˿�

			if (((pChiHu->wProviderUser==wMeChairID)))
			{
				if (pChiHu->bGangStatus == true)
				{
					// �ı������Ϊ������
					for (BYTE j = 0;j<m_cbWeaveCount[wMeChairID];j++)
					{
						BYTE cbCenterCard = m_WeaveItemArray[wMeChairID][j].cbCenterCard;
						if (m_WeaveItemArray[wMeChairID][j].cbWeaveKind == WIK_GANG && cbCenterCard == cbChiHuCard)
						{
							m_WeaveItemArray[wMeChairID][j].cbWeaveKind = WIK_PENG;// �����Ʋ���
							
							////_c//printf("android change wang to peng \n"); 
							////printf("android change wang to peng \n ");

							
							break;
						}
					}

				}else if (pChiHu->bTIStatus == true)
				{
					// �ı������Ϊ������
					for (BYTE j = 0;j<m_cbWeaveCount[wMeChairID];j++)
					{
						BYTE cbCenterCard = m_WeaveItemArray[wMeChairID][j].cbCenterCard;
						if (m_WeaveItemArray[wMeChairID][j].cbWeaveKind == WIK_PENG && cbCenterCard == cbChiHuCard)
						{
							m_WeaveItemArray[wMeChairID][j].cbWeaveKind = WIK_TIE_PAI;
							m_cbCardIndex[wMeChairID][m_GameLogic.GetMagicIndex()]--; // �����������
							
						//	//_c//printf("android change peng to tie \n"); 
						//	//printf("android change peng to tie \n ");

							break;
						}
					}

				}

			}

	}
#endif 
	m_bActionMask = WIK_NULL;							//��������
	m_cbActionCard = 0;							//�����˿�	

#ifdef CONSOLE_OMA
	
	// �ı������Ϊ������
	for (BYTE j = 0;j<m_cbWeaveCount[wMeChairID];j++)
	{
		BYTE cbCenterCard = m_WeaveItemArray[wMeChairID][j].cbCenterCard;
		BYTE cbWeaveKind = m_WeaveItemArray[wMeChairID][j].cbWeaveKind;
		////_c//printf("android  wMeChairID:%d OnSubUserChiHu after m_WeaveItem---- cbWeaveKind:%x cbCenterCard:%x \n",wMeChairID,cbWeaveKind,cbCenterCard);
		// //printf("android wMeChairID:%d OnSubUserChiHu after m_WeaveItem---- cbWeaveKind:%x cbCenterCard:%x \n",wMeChairID,cbWeaveKind,cbCenterCard);

	}

#endif 




	return true;
}

#endif 

//////////////////////////////////////////////////////////////////////////
