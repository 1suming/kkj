#include "StdAfx.h"
#include "GameLogic.h"
#include "math.h"


//////////////////////////////////////////////////////////////////////////

//��̬����
bool		CChiHuRight::m_bInit = false;
DWORD		CChiHuRight::m_dwRightMask[MAX_RIGHT_COUNT];

//���캯��
CChiHuRight::CChiHuRight()
{
	ZeroMemory( m_dwRight,sizeof(m_dwRight) );

	if( !m_bInit )
	{
		m_bInit = true;
		for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
		{
			if( 0 == i )
				m_dwRightMask[i] = 0;
			else
				m_dwRightMask[i] = (DWORD(pow(2.0,i-1)))<<28;
		}
	}
}

//��ֵ������
CChiHuRight & CChiHuRight::operator = ( DWORD dwRight )
{
	DWORD dwOtherRight = 0;
	//��֤Ȩλ
	if( !IsValidRight( dwRight ) )
	{
		//��֤ȡ��Ȩλ
		ASSERT( IsValidRight( ~dwRight ) );
		if( !IsValidRight( ~dwRight ) ) return *this;
		dwRight = ~dwRight;
		dwOtherRight = MASK_CHI_HU_RIGHT;
	}

	for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
	{
		if( (dwRight&m_dwRightMask[i]) || (i==0&&dwRight<0x10000000) )
			m_dwRight[i] = dwRight&MASK_CHI_HU_RIGHT;
		else m_dwRight[i] = dwOtherRight;
	}

	return *this;
}

//�����
CChiHuRight & CChiHuRight::operator &= ( DWORD dwRight )
{
	bool bNavigate = false;
	//��֤Ȩλ
	if( !IsValidRight( dwRight ) )
	{
		//��֤ȡ��Ȩλ
		ASSERT( IsValidRight( ~dwRight ) );
		if( !IsValidRight( ~dwRight ) ) return *this;
		//����Ȩλ
		DWORD dwHeadRight = (~dwRight)&0xF0000000;
		DWORD dwTailRight = dwRight&MASK_CHI_HU_RIGHT;
		dwRight = dwHeadRight|dwTailRight;
		bNavigate = true;
	}

	for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
	{
		if( (dwRight&m_dwRightMask[i]) || (i==0&&dwRight<0x10000000) )
		{
			m_dwRight[i] &= (dwRight&MASK_CHI_HU_RIGHT);
		}
		else if( !bNavigate )
			m_dwRight[i] = 0;
	}

	return *this;
}

//�����
CChiHuRight & CChiHuRight::operator |= ( DWORD dwRight )
{
	//��֤Ȩλ
	if( !IsValidRight( dwRight ) ) return *this;

	for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
	{
		if( (dwRight&m_dwRightMask[i]) || (i==0&&dwRight<0x10000000) )
			m_dwRight[i] |= (dwRight&MASK_CHI_HU_RIGHT);
	}

	return *this;
}

//��
CChiHuRight CChiHuRight::operator & ( DWORD dwRight )
{
	CChiHuRight chr = *this;
	return (chr &= dwRight);
}

//��
CChiHuRight CChiHuRight::operator & ( DWORD dwRight ) const
{
	CChiHuRight chr = *this;
	return (chr &= dwRight);
}

//��
CChiHuRight CChiHuRight::operator | ( DWORD dwRight )
{
	CChiHuRight chr = *this;
	return chr |= dwRight;
}

//��
CChiHuRight CChiHuRight::operator | ( DWORD dwRight ) const
{
	CChiHuRight chr = *this;
	return chr |= dwRight;
}

//�Ƿ�ȨλΪ��
bool CChiHuRight::IsEmpty()
{
	for( BYTE i = 0; i < CountArray(m_dwRight); i++ )
		if( m_dwRight[i] ) return false;
	return true;
}

//����ȨλΪ��
void CChiHuRight::SetEmpty()
{
	ZeroMemory( m_dwRight,sizeof(m_dwRight) );
	return;
}

//��ȡȨλ��ֵ
BYTE CChiHuRight::GetRightData( DWORD dwRight[], BYTE cbMaxCount )
{
	ASSERT( cbMaxCount >= CountArray(m_dwRight) );
	if( cbMaxCount < CountArray(m_dwRight) ) return 0;

	CopyMemory( dwRight,m_dwRight,sizeof(DWORD)*CountArray(m_dwRight) );
	return CountArray(m_dwRight);
}

//����Ȩλ��ֵ
bool CChiHuRight::SetRightData( const DWORD dwRight[], BYTE cbRightCount )
{
	ASSERT( cbRightCount <= CountArray(m_dwRight) );
	if( cbRightCount > CountArray(m_dwRight) ) return false;

	ZeroMemory( m_dwRight,sizeof(m_dwRight) );
	CopyMemory( m_dwRight,dwRight,sizeof(DWORD)*cbRightCount );
	
	return true;
}

//����λ�Ƿ���ȷ
bool CChiHuRight::IsValidRight( DWORD dwRight )
{
	DWORD dwRightHead = dwRight & 0xF0000000;
	for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
		if( m_dwRightMask[i] == dwRightHead ) return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//��̬����

//�˿�����
const BYTE CGameLogic::m_cbCardDataArray[MAX_REPERTORY]=
{
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
	0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
	0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
};

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameLogic::CGameLogic()
{
	m_cbMagicIndex = MAX_INDEX;
	m_cbGenCount = 0;
	m_bSingleMagic = true;
}

//��������
CGameLogic::~CGameLogic()
{
}

//�����˿�
void CGameLogic::RandCardData(BYTE cbCardData[], BYTE cbMaxCount)
{
	//����׼��
	BYTE cbCardDataTemp[CountArray(m_cbCardDataArray)];
	CopyMemory(cbCardDataTemp,m_cbCardDataArray,sizeof(m_cbCardDataArray));

	//�����˿�
	BYTE cbRandCount=0,cbPosition=0;
	do
	{
		cbPosition=rand()%(cbMaxCount-cbRandCount);
		cbCardData[cbRandCount++]=cbCardDataTemp[cbPosition];
		cbCardDataTemp[cbPosition]=cbCardDataTemp[cbMaxCount-cbRandCount];
	} while (cbRandCount<cbMaxCount);

	return;
}

//ɾ���˿�
bool CGameLogic::RemoveCard(BYTE cbCardIndex[MAX_INDEX], BYTE cbRemoveCard)
{
	//Ч���˿�
	ASSERT(IsValidCard(cbRemoveCard));
	ASSERT(cbCardIndex[SwitchToCardIndex(cbRemoveCard)]>0);

	//ɾ���˿�
	BYTE cbRemoveIndex=SwitchToCardIndex(cbRemoveCard);
	if (cbCardIndex[cbRemoveIndex]>0)
	{
		cbCardIndex[cbRemoveIndex]--;
		return true;
	}

	//ʧ��Ч��
	ASSERT(FALSE);

	return false;
}

//ɾ���˿�
bool CGameLogic::RemoveCard(BYTE cbCardIndex[MAX_INDEX], const BYTE cbRemoveCard[], BYTE cbRemoveCount)
{
	//ɾ���˿�
	for (BYTE i=0;i<cbRemoveCount;i++)
	{
		//Ч���˿�
		ASSERT(IsValidCard(cbRemoveCard[i]));
		ASSERT(cbCardIndex[SwitchToCardIndex(cbRemoveCard[i])]>0);

		//ɾ���˿�
		BYTE cbRemoveIndex=SwitchToCardIndex(cbRemoveCard[i]);
		if (cbCardIndex[cbRemoveIndex]==0)
		{
			//�������
			ASSERT(FALSE);

			//��ԭɾ��
			for (BYTE j=0;j<i;j++) 
			{
				ASSERT(IsValidCard(cbRemoveCard[j]));
				cbCardIndex[SwitchToCardIndex(cbRemoveCard[j])]++;
			}

			return false;
		}
		else 
		{
			//ɾ���˿�
			--cbCardIndex[cbRemoveIndex];
		}
	}

	return true;
}
 
// �ж�����������
bool CGameLogic::HaveMagicCard(const BYTE cbCardIndex[MAX_INDEX],const tagWeaveItem WeaveItem[], BYTE cbWeaveCount)
{
		for (BYTE i = 0;i<MAX_INDEX;i++)
		{

			if (cbCardIndex[i]>0 && IsMagicCard(SwitchToCardData(i)))
			{
				return true;
			}
		}

		for (BYTE i = 0;i<cbWeaveCount;i++)
		{
			if (WeaveItem[i].cbWeaveKind&WIK_TIE_PAI)
			{
				return true;
			}
		}

		return false;

}
// �ж��Ƿ���3���ƾ�
bool CGameLogic::HaveThreePaiJin(const BYTE cbCardIndex[MAX_INDEX],const tagWeaveItem WeaveItem[], BYTE cbWeaveCount)
{
	BYTE cbPaiJinCount = 0;
	for (BYTE k =0;k<cbWeaveCount;k++)
	{
		if(WeaveItem[k].cbCenterCard != m_PaiJing)
			continue;
		if (WeaveItem[k].cbWeaveKind&WIK_PENG || WeaveItem[k].cbWeaveKind&WIK_TIE_PAI)
		{
			cbPaiJinCount = 3;
			break;
		}
	}
	
	BYTE cbPaiJingIndex = SwitchToCardIndex(m_PaiJing);// �ƾ�����
	cbPaiJinCount+=cbCardIndex[cbPaiJingIndex];

	return cbPaiJinCount >= 3;
	
}

void CGameLogic::SetPaiJing(BYTE cbCardData)
{

	if(!IsValidCard(cbCardData)) return;

	// �����ƾ�
	m_PaiJing = cbCardData; 
	BYTE cbColor = m_PaiJing&MASK_COLOR;
	BYTE cbValue = m_PaiJing&MASK_VALUE;
	cbValue = cbValue%9+1;
	BYTE cbTingYong = (cbColor | cbValue);

	// ������������
	if (m_bSingleMagic)
	{
		m_cbMagicIndex = SwitchToCardIndex(cbTingYong);	
 	}else
	{
		//TODO: ʵ��˫���ж�
	}

 }


 
//ɾ���˿�
bool CGameLogic::RemoveCard(BYTE cbCardData[], BYTE cbCardCount, const BYTE cbRemoveCard[], BYTE cbRemoveCount)
{
	//��������
	ASSERT(cbCardCount<=14);
	ASSERT(cbRemoveCount<=cbCardCount);

	//�������
	BYTE cbDeleteCount=0,cbTempCardData[14];
	if (cbCardCount>CountArray(cbTempCardData))
		return false;
	CopyMemory(cbTempCardData,cbCardData,cbCardCount*sizeof(cbCardData[0]));

	//�����˿�
	for (BYTE i=0;i<cbRemoveCount;i++)
	{
		for (BYTE j=0;j<cbCardCount;j++)
		{
			if (cbRemoveCard[i]==cbTempCardData[j])
			{
				cbDeleteCount++;
				cbTempCardData[j]=0;
				break;
			}
		}
	}

	//�ɹ��ж�
	if (cbDeleteCount!=cbRemoveCount) 
	{
		ASSERT(FALSE);
		return false;
	}

	//�����˿�
	BYTE cbCardPos=0;
	for (BYTE i=0;i<cbCardCount;i++)
	{
		if (cbTempCardData[i]!=0) 
			cbCardData[cbCardPos++]=cbTempCardData[i];
	}

	return true;
}

//��Ч�ж�
bool CGameLogic::IsValidCard(BYTE cbCardData)
{
	BYTE cbValue=(cbCardData&MASK_VALUE);
	BYTE cbColor=(cbCardData&MASK_COLOR)>>4;
	return (((cbValue>=1)&&(cbValue<=9)&&(cbColor<=2))||((cbValue>=1)&&(cbValue<=7)&&(cbColor==3)));
}

//�˿���Ŀ
BYTE CGameLogic::GetCardCount(const BYTE cbCardIndex[MAX_INDEX])
{
	//��Ŀͳ��
	BYTE cbCardCount=0;
	for (BYTE i=0;i<MAX_INDEX;i++) 
		cbCardCount+=cbCardIndex[i];

	return cbCardCount;
}

//��ȡ���
BYTE CGameLogic::GetWeaveCard(BYTE cbWeaveKind, BYTE cbCenterCard, BYTE cbCardBuffer[4])
{
	//����˿�
	switch (cbWeaveKind)
	{

	case WIK_TI_PAI:		//���Ʋ���
	    {
		    //���ñ���
			cbCardBuffer[0]=cbCenterCard;
			cbCardBuffer[1]=cbCenterCard;
			cbCardBuffer[2]=cbCenterCard;
			return 3;
	    }

	case WIK_TIE_PAI:		//���Ʋ���
		{
			//���ñ���
			cbCardBuffer[0]=cbCenterCard;
			cbCardBuffer[1]=cbCenterCard;
			cbCardBuffer[2]=SwitchToCardData(m_cbMagicIndex); // ħ����
			return 3;
		}
 
	case WIK_PENG:		//���Ʋ���
		{
			//���ñ���
			cbCardBuffer[0]=cbCenterCard;
			cbCardBuffer[1]=cbCenterCard;
			cbCardBuffer[2]=cbCenterCard;

			return 3;
		}
	case WIK_GANG:		//���Ʋ���
		{
			//���ñ���
			cbCardBuffer[0]=cbCenterCard;
			cbCardBuffer[1]=cbCenterCard;
			cbCardBuffer[2]=cbCenterCard;
			cbCardBuffer[3]=cbCenterCard;

			return 4;
		}
	default:
		{
			ASSERT(FALSE);
		}
	}

	return 0;
}


//�����ȼ�
BYTE CGameLogic::GetUserActionRank(BYTE cbUserAction)
{
	//���Ƶȼ�
	if (cbUserAction&WIK_CHI_HU) { return 4+3; }
	//���Ƶȼ�
	if (cbUserAction&WIK_GANG) { return 4+2; }
	//���Ƶȼ�
	if (cbUserAction&WIK_PENG) { return 4+1; }
	//���Ƶȼ�
	if (cbUserAction&WIK_TIE_PAI){	return 4; }
	
	return 0;
}

//���Ƶȼ�
WORD CGameLogic::GetChiHuActionRank(const CChiHuRight & ChiHuRight)
{
	WORD wFanShu = 1; // �ط��� һ�� 

	if( !(ChiHuRight&CHR_TIAN_HU).IsEmpty() || !(ChiHuRight&CHR_DI_HU).IsEmpty() ) // ������ߵغ� ��߷�
	{
		return (WORD)m_lMaxScoreTimes;
	}

	//////////////////////////////////////////////////////////////////////////
	// ����������

	if( !(ChiHuRight&CHR_QING_YI_SE).IsEmpty() ) // ��һɫ 3��
	{
		wFanShu += 2;// һ����3��
	}

	// ����� ���� ��С�� 
	if( !(ChiHuRight&CHR_DA_DUI_ZI).IsEmpty() ||  !(ChiHuRight&CHR_QI_XIAO_DUI).IsEmpty() ) // ����� 3��
	{
		wFanShu += 2;// һ����3��
	}
	
   //////////////////////////////////////////////////////////////////////////
	// ��һ������
	if( !(ChiHuRight&CHR_WITHOUT_TING_YONG).IsEmpty() ) //ȱ���ü� 1��
	{
		wFanShu+=1;
	}

	if( !(ChiHuRight&CHR_WITH_THREE_PAI_JIN).IsEmpty() ) //3���ƾ� ��1��
	{
		wFanShu +=1;
	}

	// �󵥵��͵����ڲ���ͬʱ����
	if( !(ChiHuRight&CHR_DA_DAN_DIAO).IsEmpty() ||!(ChiHuRight&CHR_DA_DAN_DIAO_PAO).IsEmpty()) //�󵥵� 1��
	{
		wFanShu += 1;
	}
	

	// ���ܺ͸����ڣ����ϻ� ����ͬʱ����
	if( !(ChiHuRight&CHR_GANG_SHANG_PAO).IsEmpty()|| 
		!(ChiHuRight&CHR_QIANG_GANG).IsEmpty() ||
		!(ChiHuRight&CHR_GANG_KAI).IsEmpty()) 
	{
		wFanShu += 1;
	}
	

	
	// �и��ͼӷ�,�м����ͼӼ���
	if (!(ChiHuRight&CHR_GENG_COUNT_ONE).IsEmpty() )
	{
		wFanShu += 1;

	}else if (!(ChiHuRight&CHR_GENG_COUNT_TWO).IsEmpty() )
	{
		wFanShu += 2;

	}else if (!(ChiHuRight&CHR_GENG_COUNT_THREE).IsEmpty() )
	{
		wFanShu += 3;
		
	}else if (!(ChiHuRight&CHR_GENG_COUNT_FOUR).IsEmpty() )
	{
		wFanShu += 4;
		
	}
	

	if (!(ChiHuRight&CHR_SHU_FAN).IsEmpty() ) // �ط�
	{
		wFanShu = 1;
	}

	
	if (wFanShu>m_lMaxScoreTimes)
	{
		wFanShu = (WORD)m_lMaxScoreTimes;
	}


	return wFanShu;
}

//�����ж�
BYTE CGameLogic::EstimateEatCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard)
{
	//����Ч��
	ASSERT(IsValidCard(cbCurrentCard));

	//�����ж�
	if ( cbCurrentCard>=0x31 || IsMagicCard(cbCurrentCard) ) 
		return WIK_NULL;

	//��������
	BYTE cbExcursion[3]={0,1,2};
	BYTE cbItemKind[3]={WIK_LEFT,WIK_CENTER,WIK_RIGHT};

	//�����ж�
	BYTE cbEatKind=0,cbFirstIndex=0;
	BYTE cbCurrentIndex=SwitchToCardIndex(cbCurrentCard);
	for (BYTE i=0;i<CountArray(cbItemKind);i++)
	{
		BYTE cbValueIndex=cbCurrentIndex%9;
		if ((cbValueIndex>=cbExcursion[i])&&((cbValueIndex-cbExcursion[i])<=6))
		{
			//�����ж�
			cbFirstIndex=cbCurrentIndex-cbExcursion[i];

			//���Ʋ��ܰ���������
			if( m_cbMagicIndex != MAX_INDEX &&
				m_cbMagicIndex >= cbFirstIndex && m_cbMagicIndex <= cbFirstIndex+2 ) continue;

			if ((cbCurrentIndex!=cbFirstIndex)&&(cbCardIndex[cbFirstIndex]==0))
				continue;
			if ((cbCurrentIndex!=(cbFirstIndex+1))&&(cbCardIndex[cbFirstIndex+1]==0))
				continue;
			if ((cbCurrentIndex!=(cbFirstIndex+2))&&(cbCardIndex[cbFirstIndex+2]==0))
				continue;

			//��������
			cbEatKind|=cbItemKind[i];
		}
	}

	return cbEatKind;
}

//�����ж�
BYTE CGameLogic::AnalyseTIPaiCard(const BYTE cbCardIndex[MAX_INDEX],const tagWeaveItem WeaveItem[], BYTE cbWeaveCount,tagTICardResult& TICardResult)
{
	BYTE ret = WIK_NULL;
		
	if (m_cbMagicIndex!=MAX_INDEX)
	{
		for (BYTE j = 0; j<cbWeaveCount;j++)
		{
			BYTE cbCenterCard = WeaveItem[j].cbCenterCard;
			BYTE cbWeaveKind =  WeaveItem[j].cbWeaveKind;
			
			if((WeaveItem[j].cbWeaveKind&WIK_TIE_PAI)!=0 && cbCardIndex[SwitchToCardIndex(cbCenterCard)]>=1)
			{
				// ������������� �� ����������һ�����Ǹ�����ͬ��ɫ
				ret |=  WIK_TI_PAI;
				TICardResult.cbCardData[TICardResult.cbCardCount++]= cbCenterCard;
			}
		}
	}


	return ret;

}

//�����ж�
BYTE CGameLogic::EstimateTiePaiCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard)
{

	// ��ֹ��������

	//����Ч��
	ASSERT(IsValidCard(cbCurrentCard));
	//�����ж�
	if ( IsMagicCard(cbCurrentCard) ) 
		return WIK_NULL;

	
	BYTE ret = WIK_NULL;
	
	if(cbCardIndex[SwitchToCardIndex(cbCurrentCard)]>=1 && m_cbMagicIndex !=MAX_INDEX &&cbCardIndex[m_cbMagicIndex]>=1)
	{
		// ������һ�Ŵ�����ƣ�ͬʱ������һ��������
		ret |= WIK_TIE_PAI;
	}
	return ret;
	
}

//�����ж�
BYTE CGameLogic::EstimatePengCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard)
{
	//����Ч��
	ASSERT(IsValidCard(cbCurrentCard));
	//�����ж�
	if ( IsMagicCard(cbCurrentCard) ) 
		return WIK_NULL;

	//�����ж�
	return (cbCardIndex[SwitchToCardIndex(cbCurrentCard)]>=2)?WIK_PENG:WIK_NULL;
}

//�����ж�
BYTE CGameLogic::EstimateGangCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard)
{
	//����Ч��
	ASSERT(IsValidCard(cbCurrentCard));
#if 1

	//�����ж�
	return (cbCardIndex[SwitchToCardIndex(cbCurrentCard)]==3)?WIK_GANG:WIK_NULL;

#else
	//�����ж�
	if ( IsMagicCard(cbCurrentCard) ) // ��ǰ����ħ����
		return WIK_NULL;

	//�����ж�
	return (cbCardIndex[SwitchToCardIndex(cbCurrentCard)]==3)?WIK_GANG:WIK_NULL;
#endif 
}

//���Ʒ���
BYTE CGameLogic::AnalyseGangCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, tagGangCardResult & GangCardResult)
{
	//���ñ���
	BYTE cbActionMask=WIK_NULL;
	ZeroMemory(&GangCardResult,sizeof(GangCardResult));

	//���ϸ���
	for (BYTE i=0;i<MAX_INDEX;i++)
	{

		if( i == m_cbMagicIndex ) continue; 

		if (cbCardIndex[i]==4)
		{
			cbActionMask|=WIK_GANG;
			GangCardResult.cbCardData[GangCardResult.cbCardCount++]=SwitchToCardData(i);
		}
	}

	//��ϸ���
	for (BYTE i=0;i<cbWeaveCount;i++)
	{
		if (WeaveItem[i].cbWeaveKind==WIK_PENG)
		{
			if (cbCardIndex[SwitchToCardIndex(WeaveItem[i].cbCenterCard)]==1)
			{
				cbActionMask|=WIK_GANG;
				GangCardResult.cbCardData[GangCardResult.cbCardCount++]=WeaveItem[i].cbCenterCard;
			}
		}
	}

	return cbActionMask;
}

//�Ժ�����
BYTE CGameLogic::AnalyseChiHuCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight)
{

	//��������
	BYTE cbChiHuKind=WIK_NULL;
	CAnalyseItemArray AnalyseItemArray;

	//���ñ���
	AnalyseItemArray.RemoveAll();
	ChiHuRight.SetEmpty();

	//�����˿�
	BYTE cbCardIndexTemp[MAX_INDEX];
	CopyMemory(cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp));


	//�����˿�
	BYTE cbCardIndexTemp2[MAX_INDEX];
	ZeroMemory(cbCardIndexTemp2,sizeof(cbCardIndexTemp2));
	m_cbGenCount = 0;
	BYTE cbFanShu = 0;
	CChiHuRight tmpChiHuRight;
	

	//cbCurrentCardһ����Ϊ0			!!!!!!!!!
	ASSERT( cbCurrentCard != 0 );
	if( cbCurrentCard == 0 ) return WIK_NULL;

	/*
	//	���ⷬ��
	*/

	//��С����
	if( IsQiXiaoDui(cbCardIndex,WeaveItem,cbWeaveCount,cbCurrentCard) ) 
	{
		ChiHuRight |= CHR_QI_XIAO_DUI;
	}

	if( !ChiHuRight.IsEmpty() )
		cbChiHuKind = WIK_CHI_HU;

	//�����˿�
	if (cbCurrentCard!=0)
		cbCardIndexTemp[SwitchToCardIndex(cbCurrentCard)]++;

	//����ȱһ��
	if( IsHuaZhu(cbCardIndexTemp,WeaveItem,cbWeaveCount) )
	{
		return WIK_NULL;
	}



	//���Ʒ���
 if((ChiHuRight&CHR_QI_XIAO_DUI).IsEmpty())
 {
		//�����˿�
	AnalyseCard(cbCardIndexTemp,WeaveItem,cbWeaveCount,AnalyseItemArray);
	if (AnalyseItemArray.GetCount()>0)
	{
		cbChiHuKind = WIK_CHI_HU;
	
		//���ͷ���
		for (INT_PTR i=0;i<AnalyseItemArray.GetCount();i++)
		{
			//��������
			tagAnalyseItem * pAnalyseItem=&AnalyseItemArray[i];


			ZeroMemory(cbCardIndexTemp2,sizeof(cbCardIndexTemp2));
			cbCardIndexTemp2[SwitchToCardIndex(pAnalyseItem->cbCardEye)] = 2;
			BYTE cbTmpFanShu = 0;
			tmpChiHuRight.SetEmpty();
			for (BYTE k =0;k<4;k++)
			{

				if (pAnalyseItem->cbWeaveKind[k] == WIK_LEFT)
				{
					BYTE cbTmpIndex =  SwitchToCardIndex(pAnalyseItem->cbCenterCard[k]);
					for (BYTE t = 0;t < 3;t ++)
					{
						cbCardIndexTemp2[cbTmpIndex]++;
						cbTmpIndex++;
					}
					
				}else if (pAnalyseItem->cbWeaveKind[k] == WIK_PENG || pAnalyseItem->cbWeaveKind[k] == WIK_TIE_PAI)
				{
					BYTE cbTmpIndex =  SwitchToCardIndex(pAnalyseItem->cbCenterCard[k]);
					for (BYTE t = 0;t < 3;t ++)
					{
						cbCardIndexTemp2[cbTmpIndex]++; 
					}
				}else if (pAnalyseItem->cbWeaveKind[k] == WIK_GANG)
				{
					BYTE cbTmpIndex =  SwitchToCardIndex(pAnalyseItem->cbCenterCard[k]);
					for (BYTE t = 0;t < 4;t ++)
					{
						cbCardIndexTemp2[cbTmpIndex]++; 
					}

				}

			}


	//  ������
		BYTE tmpCount = 0;
		for (BYTE k = 0;k<MAX_INDEX;k++)
		{
			// ���������ƣ����������в����Ƿ��и�
			if (cbCardIndexTemp2[k] == 4)
			{
				tmpCount++;
				cbTmpFanShu++;
			}
	
		}
	
		// �ж��Ƿ���3���ƾ�
		if (HaveThreePaiJin(cbCardIndexTemp2,WeaveItem,cbWeaveCount))
		{
			tmpChiHuRight |= CHR_WITH_THREE_PAI_JIN;
			cbTmpFanShu = (cbTmpFanShu == 0)?2:(cbTmpFanShu+=1);
			
		}


			/*
			//	�жϷ���
			*/
			//������
			if( IsPengPeng(pAnalyseItem) ) 
			{
				tmpChiHuRight |= CHR_DA_DUI_ZI;
				cbTmpFanShu+=3;
			}



			if(cbTmpFanShu>cbFanShu)
			{
				cbFanShu = cbTmpFanShu;
				DWORD wRightData =0;
				tmpChiHuRight.GetRightData(&wRightData, MAX_RIGHT_COUNT);
				ChiHuRight.SetRightData(&wRightData, MAX_RIGHT_COUNT);
				m_cbGenCount = tmpCount;

			}
	
#if 0

			//����
			if( IsDaiYao(pAnalyseItem) )
				ChiHuRight |= CHR_DAI_YAO;
			//����
			if( IsJiangDui(pAnalyseItem) )
				ChiHuRight |= CHR_JIANG_DUI;
#endif 
		}
	}
 }
	


	if(!(ChiHuRight&CHR_QI_XIAO_DUI).IsEmpty())
	{
		BYTE cbTingYongCardCount = cbCardIndexTemp[m_cbMagicIndex];
		BYTE cbOneCount = 0,cbThreeCount = 0;

		ChiHuRight &=~CHR_DA_DUI_ZI;
		for(BYTE k = 0;k<MAX_INDEX-7;k++)
		{

			if( k == m_cbMagicIndex ) continue;

			if(cbCardIndexTemp[k] == 4)
			{
				m_cbGenCount++;
			}

			BYTE cbCardCount=cbCardIndexTemp[k];
			if(cbCardCount == 1)
			{
				cbOneCount++; 
			}else if(cbCardCount == 3)
			{
				cbThreeCount++; 
			}


		}


		switch (cbTingYongCardCount)
		{
		case 1:
			if (cbThreeCount == 1)
				m_cbGenCount++;
			break;
		case 2:
			if (cbThreeCount == 2 && cbOneCount == 0)
				m_cbGenCount+=2;
			else if (cbThreeCount == 1 && cbOneCount == 1)
				m_cbGenCount++;

			break;
		case 3:
			if (cbThreeCount == 1 && cbOneCount == 0)
				m_cbGenCount+=2;
			else if (cbThreeCount == 3 && cbOneCount == 0)
				m_cbGenCount+=cbThreeCount;
			else if ( cbThreeCount == 2 && cbOneCount == 1)
				m_cbGenCount+=cbThreeCount;
			else if (cbThreeCount == 1 && cbOneCount == 2)
				m_cbGenCount+=cbThreeCount;

			break;
		case 4:
			if (cbThreeCount == 2 && cbOneCount == 0)
 				m_cbGenCount+=3;
			else if (cbThreeCount == 1 && cbOneCount == 1)
				m_cbGenCount+=2;
			else if ( cbThreeCount == 2 && cbOneCount == 2)
				m_cbGenCount+=cbThreeCount;
			else if (cbThreeCount == 1 && cbOneCount == 3)
				m_cbGenCount+=cbThreeCount;

			break;
		default:
			break;
		}

	}
	

	if( cbChiHuKind == WIK_CHI_HU )
	{
		//��һɫ��
		if( IsQingYiSe(cbCardIndex,WeaveItem,cbWeaveCount,cbCurrentCard) )
		{
			ChiHuRight |= CHR_QING_YI_SE;
		}

		if (!HaveMagicCard(cbCardIndex,WeaveItem,cbWeaveCount) && IsMagicCard(cbCurrentCard)==false) // ȱ����
		{
			ChiHuRight |= CHR_WITHOUT_TING_YONG;

		}

		if (IsDaDanDiao(cbCardIndex,cbWeaveCount)) // �󵥵�
  	    {
			ChiHuRight |= CHR_DA_DAN_DIAO;
		}



		switch(m_cbGenCount)
		{
			case 1:
				ChiHuRight|= CHR_GENG_COUNT_ONE;
				break;
			case 2:
				ChiHuRight|= CHR_GENG_COUNT_TWO;
				break;
			case 3:
				ChiHuRight|= CHR_GENG_COUNT_THREE;
				break;
			case 4:
				ChiHuRight|= CHR_GENG_COUNT_FOUR;
				break;
						
		}

		//�ط�
		if( cbChiHuKind == WIK_CHI_HU && ChiHuRight.IsEmpty() )
			ChiHuRight |= CHR_SHU_FAN;

	}

	return cbChiHuKind;
}

//�Ƿ�����
bool CGameLogic::IsTingCard( const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount )
{
	//��������
	BYTE cbCardIndexTemp[MAX_INDEX];
	CopyMemory( cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp) );

	CChiHuRight chr;
	for( BYTE i = 0; i < MAX_INDEX-7; i++ )
	{
		BYTE cbCurrentCard = SwitchToCardData( i );
		if( WIK_CHI_HU == AnalyseChiHuCard( cbCardIndexTemp,WeaveItem,cbWeaveCount,cbCurrentCard,chr ) )
			return true;
	}
	return false;
}

//�˿�ת��
BYTE CGameLogic::SwitchToCardData(BYTE cbCardIndex)
{
	ASSERT(cbCardIndex<34);
	return ((cbCardIndex/9)<<4)|(cbCardIndex%9+1);
}

//�˿�ת��
BYTE CGameLogic::SwitchToCardIndex(BYTE cbCardData)
{
	ASSERT(IsValidCard(cbCardData));
	return ((cbCardData&MASK_COLOR)>>4)*9+(cbCardData&MASK_VALUE)-1;
}

//�˿�ת��
BYTE CGameLogic::SwitchToCardData(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCardData[MAX_COUNT])
{
	//ת���˿�
	BYTE cbPosition=0;
	//����
	if( m_cbMagicIndex != MAX_INDEX )
	{
		for( BYTE i = 0; i < cbCardIndex[m_cbMagicIndex]; i++ )
			cbCardData[cbPosition++] = SwitchToCardData(m_cbMagicIndex);
	}
	for (BYTE i=0;i<MAX_INDEX;i++)
	{
		if( i == m_cbMagicIndex ) continue; //������ת����ת��ʣ���ƣ���������
		if (cbCardIndex[i]!=0)
		{
			for (BYTE j=0;j<cbCardIndex[i];j++)
			{
				ASSERT(cbPosition<MAX_COUNT);
				cbCardData[cbPosition++]=SwitchToCardData(i);
			}
		}
	}

	return cbPosition;
}

//�˿�ת��
BYTE CGameLogic::SwitchToCardIndex(const BYTE cbCardData[], BYTE cbCardCount, BYTE cbCardIndex[MAX_INDEX])
{
	//���ñ���
	ZeroMemory(cbCardIndex,sizeof(BYTE)*MAX_INDEX);

	//ת���˿�
	for (BYTE i=0;i<cbCardCount;i++)
	{
		ASSERT(IsValidCard(cbCardData[i]));
		if (!IsValidCard(cbCardData[i])) continue;
		cbCardIndex[SwitchToCardIndex(cbCardData[i])]++;
	}

	return cbCardCount;
}

//�����˿�
bool CGameLogic::AnalyseCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, CAnalyseItemArray & AnalyseItemArray)
{
	//������Ŀ
	BYTE cbCardCount=GetCardCount(cbCardIndex);

	//Ч����Ŀ
	ASSERT((cbCardCount>=2)&&(cbCardCount<=MAX_COUNT)&&((cbCardCount-2)%3==0));
	if ((cbCardCount<2)||(cbCardCount>MAX_COUNT)||((cbCardCount-2)%3!=0))
	{
		return false;
	}
	//��������
	BYTE cbKindItemCount=0;
#if 1 
	tagKindItem KindItem[220]; //  ������12ѡ3 = 12!/(9!*3!) = 220
#else
	tagKindItem KindItem[27*2+7+14];
#endif 
	ZeroMemory(KindItem,sizeof(KindItem));

	//�����ж�
	BYTE cbLessKindItem=(cbCardCount-2)/3;
	ASSERT((cbLessKindItem+cbWeaveCount)==4);
	
	//�����ж�
	if (cbLessKindItem==0)
	{
		//Ч�����
		ASSERT((cbCardCount==2)&&(cbWeaveCount==4));

		//�����ж�
		for (BYTE i=0;i<MAX_INDEX;i++)
		{
			if (cbCardIndex[i]==2 || 
				( m_cbMagicIndex != MAX_INDEX && i != m_cbMagicIndex && cbCardIndex[m_cbMagicIndex]+cbCardIndex[i]==2 ) )
			{
				//��������
				tagAnalyseItem AnalyseItem;
				ZeroMemory(&AnalyseItem,sizeof(AnalyseItem));

				//���ý��
				for (BYTE j=0;j<cbWeaveCount;j++)
				{
					AnalyseItem.cbWeaveKind[j]=WeaveItem[j].cbWeaveKind;
					AnalyseItem.cbCenterCard[j]=WeaveItem[j].cbCenterCard;
					GetWeaveCard( WeaveItem[j].cbWeaveKind,WeaveItem[j].cbCenterCard,AnalyseItem.cbCardData[j] );
				}
				AnalyseItem.cbCardEye=SwitchToCardData(i);
				if( cbCardIndex[i] < 2 || i == m_cbMagicIndex )
					AnalyseItem.bMagicEye = true;
				else AnalyseItem.bMagicEye = false;

				//������
				AnalyseItemArray.Add(AnalyseItem);

				return true;
			}
		}

		return false;
	}

	//��ַ���
	BYTE cbMagicCardIndex[MAX_INDEX];
	CopyMemory(cbMagicCardIndex,cbCardIndex,sizeof(cbMagicCardIndex));
	BYTE cbMagicCardCount = 0;
	if( m_cbMagicIndex != MAX_INDEX )
	{
		cbMagicCardCount = cbCardIndex[m_cbMagicIndex];
		if( cbMagicCardIndex[m_cbMagicIndex] ) cbMagicCardIndex[m_cbMagicIndex] = 1;		//��С�������
	}
	if (cbCardCount>=3)
	{
		for (BYTE i=0;i<MAX_INDEX;i++)
		{
			//ͬ���ж�
			if (cbMagicCardIndex[i]+cbMagicCardCount>=3)
			{
				ASSERT( cbKindItemCount < CountArray(KindItem) );
				KindItem[cbKindItemCount].cbCardIndex[0]=i;
				KindItem[cbKindItemCount].cbCardIndex[1]=i;
				KindItem[cbKindItemCount].cbCardIndex[2]=i;
				KindItem[cbKindItemCount].cbWeaveKind=WIK_PENG;
				KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
				KindItem[cbKindItemCount].cbValidIndex[0] = cbMagicCardIndex[i]>0?i:m_cbMagicIndex;
				KindItem[cbKindItemCount].cbValidIndex[1] = cbMagicCardIndex[i]>1?i:m_cbMagicIndex;
				KindItem[cbKindItemCount].cbValidIndex[2] = cbMagicCardIndex[i]>2?i:m_cbMagicIndex;
				cbKindItemCount++;
				if(cbMagicCardIndex[i]+cbMagicCardCount>=6) // ������Է���Ϊ2������
				{
					ASSERT( cbKindItemCount < CountArray(KindItem) ); // ��2��
					KindItem[cbKindItemCount].cbCardIndex[0]=i;
					KindItem[cbKindItemCount].cbCardIndex[1]=i;
					KindItem[cbKindItemCount].cbCardIndex[2]=i;
					KindItem[cbKindItemCount].cbWeaveKind=WIK_PENG;
					KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
					KindItem[cbKindItemCount].cbValidIndex[0] = cbMagicCardIndex[i]>3?i:m_cbMagicIndex;
					KindItem[cbKindItemCount].cbValidIndex[1] = m_cbMagicIndex;
					KindItem[cbKindItemCount].cbValidIndex[2] = m_cbMagicIndex;
					cbKindItemCount++;
				}
			}

			//�����ж�
			if ((i<(MAX_INDEX-9))&&((i%9)<7))
			{
				//ֻҪ������������3��˳���������������ڵ���3,��������
				if( cbMagicCardCount+cbMagicCardIndex[i]+cbMagicCardIndex[i+1]+cbMagicCardIndex[i+2] >= 3 )
				{
					BYTE cbIndex[3] = { i==m_cbMagicIndex?0:cbMagicCardIndex[i],(i+1)==m_cbMagicIndex?0:cbMagicCardIndex[i+1],
						(i+2)==m_cbMagicIndex?0:cbMagicCardIndex[i+2] };
					int nMagicCountTemp = cbMagicCardCount;
					BYTE cbValidIndex[3];
					while( nMagicCountTemp+cbIndex[0]+cbIndex[1]+cbIndex[2] >= 3 )
					{
						for( BYTE j = 0; j < CountArray(cbIndex); j++ )
						{
							if( cbIndex[j] > 0 ) 
							{
								cbIndex[j]--;
								cbValidIndex[j] = i+j;
							}
							else 
							{
								nMagicCountTemp--;
								cbValidIndex[j] = m_cbMagicIndex;
							}
						}
					
						if( nMagicCountTemp >= 0 )
						{
							ASSERT( cbKindItemCount < CountArray(KindItem) );
							KindItem[cbKindItemCount].cbCardIndex[0]=i;
							KindItem[cbKindItemCount].cbCardIndex[1]=i+1;
							KindItem[cbKindItemCount].cbCardIndex[2]=i+2;
							KindItem[cbKindItemCount].cbWeaveKind=WIK_LEFT;
							KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
							CopyMemory( KindItem[cbKindItemCount].cbValidIndex,cbValidIndex,sizeof(cbValidIndex) );
							cbKindItemCount++;
						}
						else break;
					}

					if (cbMagicCardIndex[i]>=1 && cbMagicCardIndex[i+1]>=1&&cbMagicCardCount>0)
					{

						cbValidIndex[0] = i;cbValidIndex[1] = i+1;cbValidIndex[2] = m_cbMagicIndex;
						ASSERT( cbKindItemCount < CountArray(KindItem) );
						KindItem[cbKindItemCount].cbCardIndex[0]=i;
						KindItem[cbKindItemCount].cbCardIndex[1]=i+1;
						KindItem[cbKindItemCount].cbCardIndex[2]=i+2;
						KindItem[cbKindItemCount].cbWeaveKind=WIK_LEFT;
						KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
						CopyMemory( KindItem[cbKindItemCount].cbValidIndex,cbValidIndex,sizeof(cbValidIndex) );
						cbKindItemCount++;

					}
					if (cbMagicCardIndex[i+1]>=1 && cbMagicCardIndex[i+2]>=1&&cbMagicCardCount>0)
					{
						cbValidIndex[0] = m_cbMagicIndex;cbValidIndex[1] = i+1;cbValidIndex[2] = i+2;
						ASSERT( cbKindItemCount < CountArray(KindItem) );
						KindItem[cbKindItemCount].cbCardIndex[0]=i;
						KindItem[cbKindItemCount].cbCardIndex[1]=i+1;
						KindItem[cbKindItemCount].cbCardIndex[2]=i+2;
						KindItem[cbKindItemCount].cbWeaveKind=WIK_LEFT;
						KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
						CopyMemory( KindItem[cbKindItemCount].cbValidIndex,cbValidIndex,sizeof(cbValidIndex) );
						cbKindItemCount++;

					}
					if (cbMagicCardIndex[i]>=1 && cbMagicCardIndex[i+2]>=1&&cbMagicCardCount>0)
					{
						cbValidIndex[0] = i;cbValidIndex[1] = m_cbMagicIndex;cbValidIndex[2] = i+2;
						ASSERT( cbKindItemCount < CountArray(KindItem) );
						KindItem[cbKindItemCount].cbCardIndex[0]=i;
						KindItem[cbKindItemCount].cbCardIndex[1]=i+1;
						KindItem[cbKindItemCount].cbCardIndex[2]=i+2;
						KindItem[cbKindItemCount].cbWeaveKind=WIK_LEFT;
						KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
						CopyMemory( KindItem[cbKindItemCount].cbValidIndex,cbValidIndex,sizeof(cbValidIndex) );
						cbKindItemCount++;

					}

				}
			}
		}
	}


	//��Ϸ���
	if (cbKindItemCount>=cbLessKindItem)
	{
		//��������
		BYTE cbCardIndexTemp[MAX_INDEX];
		ZeroMemory(cbCardIndexTemp,sizeof(cbCardIndexTemp));

		//��������
		BYTE cbIndex[4]={0,1,2,3};
		tagKindItem * pKindItem[4];
		ZeroMemory(&pKindItem,sizeof(pKindItem));

		//��ʼ���
		do
		{
			//���ñ���
			CopyMemory(cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp));
			for (BYTE i=0;i<cbLessKindItem;i++)
				pKindItem[i]=&KindItem[cbIndex[i]];

			//�����ж�
			bool bEnoughCard=true;
			for (BYTE i=0;i<cbLessKindItem*3;i++)
			{
				//�����ж�
				BYTE cbCardIndex=pKindItem[i/3]->cbValidIndex[i%3]; 
				if (cbCardIndexTemp[cbCardIndex]==0)
				{
					bEnoughCard=false;
					break;
				}
				else 
					cbCardIndexTemp[cbCardIndex]--;
			}

			//�����ж�
			if (bEnoughCard==true)
			{
				//�����ж�
				BYTE cbCardEye=0;
				bool bMagicEye = false;
				for (BYTE i=0;i<MAX_INDEX;i++)
				{
					if (cbCardIndexTemp[i]==2)
					{
						cbCardEye=SwitchToCardData(i);
						if( i == m_cbMagicIndex ) bMagicEye = true;
						break;
					}
					else if( i!=m_cbMagicIndex && 
						m_cbMagicIndex != MAX_INDEX && cbCardIndexTemp[i]+cbCardIndexTemp[m_cbMagicIndex]==2 )
					{
						cbCardEye = SwitchToCardData(i);
						bMagicEye = true;
					}
				}

				//�������
				if (cbCardEye!=0)
				{
					//��������
					tagAnalyseItem AnalyseItem;
					ZeroMemory(&AnalyseItem,sizeof(AnalyseItem));

					//�������
					for (BYTE i=0;i<cbWeaveCount;i++)
					{
						AnalyseItem.cbWeaveKind[i]=WeaveItem[i].cbWeaveKind;
						AnalyseItem.cbCenterCard[i]=WeaveItem[i].cbCenterCard;
						GetWeaveCard( WeaveItem[i].cbWeaveKind,WeaveItem[i].cbCenterCard,
							AnalyseItem.cbCardData[i] );
					}

					//��������
					for (BYTE i=0;i<cbLessKindItem;i++) 
					{
						AnalyseItem.cbWeaveKind[i+cbWeaveCount]=pKindItem[i]->cbWeaveKind;
						AnalyseItem.cbCenterCard[i+cbWeaveCount]=pKindItem[i]->cbCenterCard;
						AnalyseItem.cbCardData[cbWeaveCount+i][0] = SwitchToCardData(pKindItem[i]->cbValidIndex[0]);
						AnalyseItem.cbCardData[cbWeaveCount+i][1] = SwitchToCardData(pKindItem[i]->cbValidIndex[1]);
						AnalyseItem.cbCardData[cbWeaveCount+i][2] = SwitchToCardData(pKindItem[i]->cbValidIndex[2]);
					}

					//��������
					AnalyseItem.cbCardEye=cbCardEye;
					AnalyseItem.bMagicEye = bMagicEye;

					//������
					AnalyseItemArray.Add(AnalyseItem);
				}
			}

			//��������
			if (cbIndex[cbLessKindItem-1]==(cbKindItemCount-1))
			{
				BYTE i = 0;
				for (i=cbLessKindItem-1;i>0;i--)
				{
					if ((cbIndex[i-1]+1)!=cbIndex[i])
					{
						BYTE cbNewIndex=cbIndex[i-1];
						for (BYTE j=(i-1);j<cbLessKindItem;j++) 
							cbIndex[j]=cbNewIndex+j-i+2;
						break;
					}
				}
				if (i==0)
					break;
			}
			else
				cbIndex[cbLessKindItem-1]++;
		} while (true);

	}

	return (AnalyseItemArray.GetCount()>0);
}

//����
bool CGameLogic::IsMagicCard( BYTE cbCardData )
{
	if(IsValidCard(cbCardData))
	{
		BYTE cbColor = m_PaiJing&MASK_COLOR;
		BYTE cbValue = m_PaiJing&MASK_VALUE;

		if (m_bSingleMagic)
		{
			cbValue = cbValue%9+1;
			BYTE cbTingYong = (cbColor | cbValue);

			return cbCardData == cbTingYong ? true:false;
		}else
		{
			//TODO: ʵ��˫���ж�
		
		}
	}

	return false;
}

//����,������ֵ����
bool CGameLogic::SortCardList( BYTE cbCardData[MAX_COUNT], BYTE cbCardCount )
{
	//��Ŀ����
	if (cbCardCount==0||cbCardCount>MAX_COUNT) return false;

	//�������
	bool bSorted=true;
	BYTE cbSwitchData=0,cbLast=cbCardCount-1;
	do
	{
		bSorted=true;
		for (BYTE i=0;i<cbLast;i++)
		{
			if (cbCardData[i]>cbCardData[i+1])
			{
				//���ñ�־
				bSorted=false;

				//�˿�����
				cbSwitchData=cbCardData[i];
				cbCardData[i]=cbCardData[i+1];
				cbCardData[i+1]=cbSwitchData;
			}	
		}
		cbLast--;
	} while(bSorted==false);

	return true;
}

/*
// ������������
*/

//�����
bool CGameLogic::IsPengPeng( const tagAnalyseItem *pAnalyseItem )
{
	for( BYTE i = 0; i < CountArray(pAnalyseItem->cbWeaveKind); i++ )
	{
		if( (pAnalyseItem->cbWeaveKind[i]&WIK_LEFT)!=0)
			return false;
	}
	return true;
}

//��һɫ��
bool CGameLogic::IsQingYiSe(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], const BYTE cbItemCount,const BYTE cbCurrentCard)
{
	//�����ж�
	BYTE cbCardColor=0xFF;

	for (BYTE i=0;i<MAX_INDEX;i++)
	{
		if(i==m_cbMagicIndex) continue;
		if (cbCardIndex[i]!=0)
		{
			//��ɫ�ж�
			if (cbCardColor!=0xFF)
				return false;

			//���û�ɫ
			cbCardColor=(SwitchToCardData(i)&MASK_COLOR);

			//��������
			i=(i/9+1)*9-1;
		}
	}

	//�������ֻ������
	if( cbCardColor == 0xFF )
	{
		ASSERT( m_cbMagicIndex != MAX_INDEX && cbCardIndex[m_cbMagicIndex] > 0 );
		//������
		ASSERT( cbItemCount > 0 );
		cbCardColor = WeaveItem[0].cbCenterCard&MASK_COLOR;
	}

	if((cbCurrentCard&MASK_COLOR)!=cbCardColor && !IsMagicCard(cbCurrentCard) ) return false;

	//����ж�
	for (BYTE i=0;i<cbItemCount;i++)
	{
		BYTE cbCenterCard=WeaveItem[i].cbCenterCard;
		if ((cbCenterCard&MASK_COLOR)!=cbCardColor)	return false;
	}

	return true;
}

//��С����
bool CGameLogic::IsQiXiaoDui(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], const BYTE cbWeaveCount,const BYTE cbCurrentCard)
{
	//����ж�
	if (cbWeaveCount!=0) return false;

	//������Ŀ
	BYTE cbReplaceCount = 0;

	//��ʱ����
	BYTE cbCardIndexTemp[MAX_INDEX];
	CopyMemory(cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp));

	//��������
	BYTE cbCurrentIndex = SwitchToCardIndex(cbCurrentCard);
	cbCardIndexTemp[cbCurrentIndex]++;

	//���㵥��
	for (BYTE i=0;i<MAX_INDEX;i++)
	{
		BYTE cbCardCount=cbCardIndexTemp[i];

		//���ƹ���
		if( i == m_cbMagicIndex ) continue;

		//����ͳ��
		if( cbCardCount == 1 || cbCardCount == 3 ) 	cbReplaceCount++;
	}

	//���Ʋ���
	if( m_cbMagicIndex != MAX_INDEX && cbReplaceCount > cbCardIndexTemp[m_cbMagicIndex] ||
		m_cbMagicIndex == MAX_INDEX && cbReplaceCount > 0 )
		return false;

	return true;

}

//����
bool CGameLogic::IsDaiYao( const tagAnalyseItem *pAnalyseItem )
{
	//�������
	BYTE cbCardValue = pAnalyseItem->cbCardEye&MASK_VALUE;
	if( cbCardValue != 1 && cbCardValue != 9 ) return false;

	for( BYTE i = 0; i < CountArray(pAnalyseItem->cbWeaveKind); i++ )
	{
		if( pAnalyseItem->cbWeaveKind[i]&(WIK_LEFT|WIK_CENTER|WIK_RIGHT) )
		{
			BYTE j = 0;
			for(j = 0; j < 3; j++ )
			{
				cbCardValue = pAnalyseItem->cbCardData[i][j]&MASK_VALUE;
				if( cbCardValue == 1 || cbCardValue == 9 ) break;
			}
			if( j == 3 ) return false;
		}
		else
		{
			cbCardValue = pAnalyseItem->cbCenterCard[i]&MASK_VALUE;
			if( cbCardValue != 1 && cbCardValue != 9 ) return false;
		}
	}
	return true;
}

//���� //���� ������ �� ������ �����Ƕ����壬�˵��ƾͽн���
bool CGameLogic::IsJiangDui( const tagAnalyseItem *pAnalyseItem )
{
	//�Ƿ�����
	if( !IsPengPeng(pAnalyseItem) ) return false;

	//�������
	BYTE cbCardValue = pAnalyseItem->cbCardEye&MASK_VALUE;
	if( cbCardValue != 2 && cbCardValue != 5 && cbCardValue != 8 ) return false;

	for( BYTE i = 0; i < CountArray(pAnalyseItem->cbWeaveKind); i++ )
	{
		if( pAnalyseItem->cbWeaveKind[i]&(WIK_LEFT|WIK_CENTER|WIK_RIGHT) )
		{
			BYTE j = 0;
			for( j = 0; j < 3; j++ )
			{
				cbCardValue = pAnalyseItem->cbCardData[i][j]&MASK_VALUE;
				if( cbCardValue == 2 || cbCardValue == 5 || cbCardValue == 8 ) break;
			}
			if( j == 3 ) return false;
		}
		else
		{
			cbCardValue = pAnalyseItem->cbCenterCard[i]&MASK_VALUE;
			if( cbCardValue != 2 && cbCardValue != 5 && cbCardValue != 8 ) return false;
		}
	}
	return true;
}

//�Ƿ���
bool CGameLogic::IsHuaZhu( const BYTE cbCardIndex[], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount )
{
	BYTE cbColor[3] = { 0,0,0 };
	for( BYTE i = 0; i < MAX_INDEX; i++ )
	{

		if (m_cbMagicIndex == i)
		{
			continue; // oma ��������
		}
 
		if( cbCardIndex[i] > 0 )
		{
			BYTE cbCardColor = SwitchToCardData(i)&MASK_COLOR;
			cbColor[cbCardColor>>4]++;

			i = (i/9+1)*9-1;
		}
	}
	for( BYTE i = 0; i < cbWeaveCount; i++ )
	{
		BYTE cbCardColor = WeaveItem[i].cbCenterCard&MASK_COLOR;
		cbColor[cbCardColor>>4]++;
	}
	//ȱһ�žͲ��ǻ���
	for( BYTE i = 0; i < CountArray(cbColor); i++ )
		if( cbColor[i] == 0 ) return false;

	return true;
}

 
bool CGameLogic::IsDaDanDiao(const BYTE cbCardIndex[MAX_INDEX],const BYTE cbWeaveCount)
{
	return (GetCardCount(cbCardIndex) == 1 && cbWeaveCount == 4);
}
 


 //////////////////////////////////////////////////////////////////////////
