#ifndef CMD_SPARROW_HEAD_FILE
#define CMD_SPARROW_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//�����궨��

#define KIND_ID						3326								//��Ϸ I D // 5FAN SCORE MATCH

#define GAME_PLAYER					4									//��Ϸ����
#define GAME_NAME					TEXT("�����齫")					//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_SCORE|GAME_GENRE_MATCH|GAME_GENRE_GOLD|GAME_GENRE_LONGMATCH)	//��Ϸ����

//��Ϸ״̬
#define GS_MJ_FREE					GS_FREE								//����״̬
#define GS_MJ_PLAY					(GS_PLAYING+1)						//��Ϸ״̬

//��������
#define MAX_WEAVE					4									//������
#define MAX_INDEX					34									//�������
#define MAX_COUNT					14									//�����Ŀ
#define MAX_REPERTORY				108									//�����

// ������͵÷� 
// ���� N ��󷬵÷ֱ���Ϊ 2^(N-1);
// һ��                     2^(1-1) = 1;
// ���4�� �÷��� 8�������� 2^(4-1) = 8;
// ���5�� �÷��� 16�������� 2^(5-1) = 16;

// �����ƾ������   
// OMA ����Ϸ���������ò���
//#define MAX_CHIHU_FANSU				5									//�����Ʒ���


//�˿˶���
#define HEAP_FULL_COUNT				26									//����ȫ��

#define MAX_RIGHT_COUNT				1									//���ȨλDWORD����			
#define START_GRANT_SCORE_BASE      2000                               // ����2000�֣���ʼ�ͷ�
#define GRANT_SCORE_VALUE           2500								// ÿ����2500��

//////////////////////////////////////////////////////////////////////////

//�������
struct CMD_WeaveItem
{
	BYTE							cbWeaveKind;						//�������
	BYTE							cbCenterCard;						//�����˿�
	BYTE							cbPublicCard;						//������־
	WORD							wProvideUser;						//��Ӧ�û�

};

//////////////////////////////////////////////////////////////////////////
//����������ṹ

#define SUB_S_GAME_START			100									//��Ϸ��ʼ
#define SUB_S_OUT_CARD				101									//��������
#define SUB_S_SEND_CARD				102									//�����˿�
#define SUB_S_OPERATE_NOTIFY		104									//������ʾ
#define SUB_S_OPERATE_RESULT		105									//��������
#define SUB_S_GAME_END				106									//��Ϸ����
#define SUB_S_TRUSTEE				107									//�û��й�
#define SUB_S_CHI_HU				108									//�Ժ�
#define SUB_S_GANG_SCORE			110									//�ܷ�
#define SUB_S_USER_ESCAPE          111                                 //�û�����
#define SUB_S_GRANT_SCORE           112                                 //�ͷ�

//��Ϸ״̬
struct CMD_S_StatusFree
{
	LONG							lCellScore;							//��������
	LONG							lMaxScoreTimes;                     //�����
	WORD							wBankerUser;						//ׯ���û�
	bool							bTrustee[GAME_PLAYER];				//�Ƿ��й�
};

 
//��Ϸ״̬
struct CMD_S_StatusPlay
{
	//��Ϸ����
	LONG							lCellScore;									//��Ԫ����
	LONG							lMaxScoreTimes;								//�����
	WORD							wBankerUser;								//ׯ���û�
	WORD							wCurrentUser;								//��ǰ�û�

	//״̬����
	BYTE							cbActionCard;								//�����˿�
	BYTE							cbActionMask;								//��������
	BYTE							cbLeftCardCount;							//ʣ����Ŀ
	bool							bTrustee[GAME_PLAYER];						//�Ƿ��й�
	WORD							wWinOrder[GAME_PLAYER];						//

	//������Ϣ
	WORD							wOutCardUser;								//�����û�
	BYTE							cbOutCardData;								//�����˿�
	BYTE							cbDiscardCount[GAME_PLAYER];				//������Ŀ
	BYTE							cbDiscardCard[GAME_PLAYER][55];				//������¼

	//�˿�����
	BYTE							cbCardCount;								//�˿���Ŀ
	BYTE							cbCardData[MAX_COUNT];						//�˿��б�
	BYTE							cbSendCardData;								//�����˿�

	//����˿�
	BYTE							cbWeaveCount[GAME_PLAYER];					//�����Ŀ

	CMD_WeaveItem					WeaveItemArray[GAME_PLAYER][MAX_WEAVE];		//����˿�
	

	//������Ϣ
	WORD							wHeapHand;									//����ͷ��
	WORD							wHeapTail;									//����β��
	BYTE							cbHeapCardInfo[GAME_PLAYER][2];				//������Ϣ
	BYTE							cbPaiJing;                                  // �ƾ� 
 
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	LONG							lSiceCount;									//���ӵ���
	WORD							wBankerUser;								//ׯ���û�
	WORD							wCurrentUser;								//��ǰ�û�
	BYTE							cbUserAction;								//�û�����
	BYTE							cbCardData[MAX_COUNT];						//�˿��б�
	WORD							wHeapHand;									//������ͷ
	WORD							wHeapTail;									//������β
	BYTE							cbHeapCardInfo[GAME_PLAYER][2];				//������Ϣ
	BYTE							cbLeftCardCount;							//
	BYTE							cbPaiJing;									// �ƾ� //OMA
	bool 							bKaiJu;										// �¿��ֱ�־

};

//��������
struct CMD_S_OutCard
{
	WORD							wOutCardUser;						//�����û�
	BYTE							cbOutCardData;						//�����˿�
};


//���ƽ��
struct tagTICardResult
{
	BYTE							cbCardCount;						//�˿���Ŀ
	BYTE							cbCardData[4];						//�˿�����
};



//���ƽ��
struct tagGangCardResult
{
	BYTE							cbCardCount;						//�˿���Ŀ
	BYTE							cbCardData[4];						//�˿�����
};


//�����˿�
struct CMD_S_SendCard
{
	bool							bTail;								//ĩβ����
	WORD							wCurrentUser;						//��ǰ�û�
	BYTE							cbCardData;							//�˿�����
 	BYTE							cbActionMask;						//��������
};


//������ʾ
struct CMD_S_OperateNotify
{
	WORD							wResumeUser;						//��ԭ�û�
	BYTE							cbActionMask;						//��������
	BYTE							cbActionCard;						//�����˿�
};

//��������
struct CMD_S_OperateResult
{
	WORD							wOperateUser;						//�����û�
	WORD							wProvideUser;						//��Ӧ�û�
	BYTE							cbOperateCode;						//��������
	BYTE							cbOperateCard;						//�����˿�
};

//��Ϸ����
struct CMD_S_GameEnd
{
	BYTE							cbCardCount[GAME_PLAYER];			//
	BYTE							cbCardData[GAME_PLAYER][MAX_COUNT];	//
	//������Ϣ
	WORD							wProvideUser[GAME_PLAYER];			//��Ӧ�û�
	DWORD							dwChiHuRight[GAME_PLAYER];			//��������

	//������Ϣ
	LONG							lGameScore[GAME_PLAYER];			//��Ϸ����
	LONG							lGameTax[GAME_PLAYER];				//
	WORD							wWinOrder[GAME_PLAYER];				//��������
	LONG							lGangScore[GAME_PLAYER];			//��ϸ�÷�
	WORD							wLostFanShu[GAME_PLAYER][GAME_PLAYER];
	WORD							wLeftUser;							//�����û�//OMAѪս�����ж���������

	LONG							lHuaZhuScore[GAME_PLAYER];			//�����
	LONG							lChaJiaoScore[GAME_PLAYER];			//��з�
	bool							bPlayleft[GAME_PLAYER];				//�����û�// OMA ��¼�������


};

//�û��й�
struct CMD_S_Trustee
{
	bool							bTrustee;							//�Ƿ��й�
	WORD							wChairID;							//�й��û�
};
  
//  �Ժ����
struct CMD_S_ChiHu
{
	WORD							wChiHuUser;							// �Ժ��û�
	WORD							wProviderUser;						// ��Ӧ�û�
	BYTE							cbChiHuCard;						// �Ժ���
	BYTE							cbCardCount;						// ����ʱ����������
	LONG							lGameScore;							// ���Ƶ÷�
	BYTE							cbWinOrder;							// ��������

	bool							bGangStatus;                        // ���ܱ�־
	bool							bTIStatus ;							// ����״̬


};

//
struct CMD_S_GangScore
{
	WORD							wChairId;							//
	BYTE							cbXiaYu;							//
	LONG							lGangScore[GAME_PLAYER];			//
};


//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_OUT_CARD				1									//��������
#define SUB_C_OPERATE_CARD			3									//�����˿�
#define SUB_C_TRUSTEE				4									//�û��й�

//��������
struct CMD_C_OutCard
{
	BYTE							cbCardData;							//�˿�����
};

//��������
struct CMD_C_OperateCard
{
	BYTE							cbOperateCode;						//��������
	BYTE							cbOperateCard;						//�����˿�
};

//�û��й�
struct CMD_C_Trustee
{
	bool							bTrustee;							//�Ƿ��й�	
};
//////////////////////////////////////////////////////////////////////////

#endif
