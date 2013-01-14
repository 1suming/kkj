#include "StdAfx.h"
#include "ScoreControl.h"

//////////////////////////////////////////////////////////////////////////


//���캯��
CScoreControl::CScoreControl()
{
	//���ñ���
	ZeroMemory(&m_ScoreInfo,sizeof(m_ScoreInfo));
	m_ChiHuRight.SetEmpty();
	m_ptBenchmark.SetPoint(0,0);
	m_bShow = false;

	//������Դ
	HINSTANCE hResInstance=AfxGetInstanceHandle();
	m_ImageGameLost.LoadImage( hResInstance,TEXT("GAME_LOST") );
	m_ImageGameWin.LoadImage( hResInstance,TEXT("GAME_WIN") );
	m_PngNum.LoadImage( hResInstance,TEXT("NUM_ORDER") );

	return;
}

//��������
CScoreControl::~CScoreControl()
{
}

//��λ����
void CScoreControl::RestorationData()
{
	//���ñ���
	ZeroMemory(&m_ScoreInfo,sizeof(m_ScoreInfo));
	m_ChiHuRight.SetEmpty();
	m_bShow = false;

	return;
}

//���û���
void CScoreControl::SetScoreInfo(const tagScoreInfo & ScoreInfo)
{
 	//���ñ���
	m_ScoreInfo=ScoreInfo;
	m_ChiHuRight.SetRightData( ScoreInfo.dwChiHuRight,MAX_RIGHT_COUNT );

	//��ʾ����
	m_bShow = true;

	return;
}

//�ػ�����
void CScoreControl::DrawScoreControl( CDC *pDC )
{
 	if( !m_bShow ) return;

	pDC->SetBkMode(TRANSPARENT);

	int nXPos = m_ptBenchmark.x;
	int nYPos = m_ptBenchmark.y;

	//�滭����
	if( m_ScoreInfo.lGameScore > 0 )
	{
 		Image *m_pImage = m_ImageGameWin.GetImage();
		
		ColorMatrix cm={{
			{1.0,0,0,0,0},
			{0,1.0,0,0,0},
			{0,0,1.0,0,0},
			{0,0,0,0.5,0},
			{0,0,0,0,1.0}
		}};
		ImageAttributes ImgAttr;
		ImgAttr.SetColorMatrix(&cm);
		
			//�����ж�
		ASSERT(m_pImage!=NULL);
		if (m_pImage==NULL) return ;

		//������Ļ
		ASSERT(pDC!=NULL);
		Graphics graphics(pDC->GetSafeHdc());

		//��ȡ����
		INT nImageWidth=m_pImage->GetWidth();
		INT nImageHeight=m_pImage->GetHeight();

		//����λ��
		RectF rcDrawRect;
		rcDrawRect.X=(REAL)nXPos;
		rcDrawRect.Y=(REAL)nYPos;
		rcDrawRect.Width=(REAL)nImageWidth;
		rcDrawRect.Height=(REAL)nImageHeight;

		//�滭ͼ��
		graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel,&ImgAttr);
		//m_ImageGameWin.DrawImage( pDC,nXPos,nYPos );
 	}
	else 
	{
 		Image *m_pImage = m_ImageGameLost.GetImage();

		ColorMatrix cm={{
			{1.0,0,0,0,0},
			{0,1.0,0,0,0},
			{0,0,1.0,0,0},
			{0,0,0,0.5,0},
			{0,0,0,0,1.0}
		}};
		ImageAttributes ImgAttr;
		ImgAttr.SetColorMatrix(&cm);

		//�����ж�
		ASSERT(m_pImage!=NULL);
		if (m_pImage==NULL) return ;

		//������Ļ
		ASSERT(pDC!=NULL);
		Graphics graphics(pDC->GetSafeHdc());

		//��ȡ����
		INT nImageWidth=m_pImage->GetWidth();
		INT nImageHeight=m_pImage->GetHeight();

		//����λ��
		RectF rcDrawRect;
		rcDrawRect.X=(REAL)nXPos;
		rcDrawRect.Y=(REAL)nYPos;
		rcDrawRect.Width=(REAL)nImageWidth;
		rcDrawRect.Height=(REAL)nImageHeight;

		//�滭ͼ��
		graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel,&ImgAttr);
  	}

 	////�滭����
	//if( m_ScoreInfo.lGameScore > 0 )
	//	m_ImageGameWin.DrawImage( pDC,nXPos,nYPos );
	//else 
	//	m_ImageGameLost.DrawImage( pDC,nXPos,nYPos );

	if( m_ScoreInfo.lGameScore > 0 )
	{
		nXPos += 84;
		nYPos += 17;
	}
	else
	{
		nXPos += 46;
		nYPos += 14;
	}

	//��������
	if( m_ScoreInfo.cbWinOrder > 0 )
	{
		if( m_ScoreInfo.lGameScore > 0 )
			DrawNumberString( pDC,m_PngNum,m_ptBenchmark.x+58,m_ptBenchmark.y+30,m_ScoreInfo.cbWinOrder,true );
		else
			DrawNumberString( pDC,m_PngNum,m_ptBenchmark.x+20,m_ptBenchmark.y+27,m_ScoreInfo.cbWinOrder,true );
	}
 
	WORD wMeChairId = m_ScoreInfo.wMeChairId;

	//������Ϣ
	TCHAR szBuffer[256] = TEXT("");
	if( !m_ChiHuRight.IsEmpty() )
	{
		if( m_ScoreInfo.wMeChairId == m_ScoreInfo.wProvideUser )
		{
			lstrcpy( szBuffer,TEXT("����") );
			DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
			nYPos += 19;

		}
		else 
		{
			lstrcpy( szBuffer,TEXT("Ӯ��") );
			TCHAR szName[64] = TEXT("");


			lstrcpyn( szName,m_ScoreInfo.szUserName[m_ScoreInfo.wProvideUser],sizeof(szName)/sizeof(TCHAR));
			lstrcat( szBuffer,szName );
	
			lstrcat( szBuffer,TEXT(" ����") );
			DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
			nYPos += 19;

		}

 		DWORD dwRight[] = {
			CHR_SHU_FAN,CHR_TIAN_HU,CHR_DI_HU,
			CHR_DA_DUI_ZI,CHR_QING_YI_SE,CHR_QI_XIAO_DUI,
			CHR_GANG_SHANG_PAO,CHR_GANG_KAI,CHR_QIANG_GANG,
			CHR_WITHOUT_TING_YONG,CHR_WITH_THREE_PAI_JIN,CHR_DA_DAN_DIAO,CHR_DA_DAN_DIAO_PAO,
			CHR_GENG_COUNT_ONE,CHR_GENG_COUNT_TWO,CHR_GENG_COUNT_THREE,CHR_GENG_COUNT_FOUR
		};
		LPCTSTR pszRight[] = {
			TEXT("�ط�"),TEXT("��� 5�� "),TEXT("�غ� 5�� "),
			TEXT("����� 3�� "),TEXT("��һɫ 3�� "),TEXT("��С�� 3�� "),
			TEXT("������ 1�� "),TEXT("���ϻ� 1�� "),TEXT("���� 1�� "),
			TEXT("������ 1�� "),TEXT("���ƾ� 1�� "),TEXT("���� 1�� "),TEXT("������ 1�� "),
			TEXT("һ�� 1�� "),TEXT("���� 2�� "),TEXT("���� 3�� "),TEXT("�ĸ� 4�� "),
		};

 		ZeroMemory(szBuffer,sizeof(szBuffer));
		for( BYTE j = 0; j < CountArray(pszRight); j++ )
		{
			if( !(m_ChiHuRight&dwRight[j]).IsEmpty() )
				lstrcat( szBuffer,pszRight[j] );
		}

 		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
		nYPos += 19;


	}
 
	if(m_ScoreInfo.lHuaZhuScore[m_ScoreInfo.wMeChairId]>0)
	{

 		ZeroMemory(szBuffer,sizeof(szBuffer));
		TCHAR szGen[64];
		_snprintf( szGen,CountArray(szGen),TEXT("�û���� %d"),m_ScoreInfo.lHuaZhuScore[m_ScoreInfo.wMeChairId] );
		lstrcat( szBuffer,szGen );
		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
		nYPos += 19;

	}

	if(m_ScoreInfo.lChaJiaoScore[m_ScoreInfo.wMeChairId]>0)
	{
 
		ZeroMemory(szBuffer,sizeof(szBuffer));
		TCHAR szGen[64];
		_snprintf( szGen,CountArray(szGen),TEXT("�ò�з� %d"),m_ScoreInfo.lChaJiaoScore[m_ScoreInfo.wMeChairId] );
		lstrcat( szBuffer,szGen );
		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
		nYPos += 19;
	}


 
	//������
	bool blose = false,bleft = false;

	for( WORD i = 0; i < GAME_PLAYER; i++ )
	{
		if( i == m_ScoreInfo.wMeChairId ) continue;

		if (m_ScoreInfo.bPlayleft[i] == true)
		{
			lstrcpy( szBuffer,TEXT("����") );
			bleft = true;
		}else if( m_ScoreInfo.wLostFanShu[i] > 0 )
		{
			lstrcpy( szBuffer,TEXT("��� ") );
			blose = true;
		}
	}

	if(blose == true || bleft == true)
	{
		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
		nYPos += 19;
	}

	for( WORD i = 0; i < GAME_PLAYER; i++ )
	{
		if( i == m_ScoreInfo.wMeChairId )
		{
			continue;
		}

		if(m_ScoreInfo.wLostFanShu[i]>0)
		{
			ZeroMemory(szBuffer,sizeof(szBuffer));
			
			TCHAR szName[NAME_LEN] = TEXT("");
			lstrcpyn( szName,m_ScoreInfo.szUserName[i],NAME_LEN*sizeof(TCHAR));
		
			_snprintf( szBuffer,CountArray(szBuffer),TEXT(" %s %d "),szName,m_ScoreInfo.wLostFanShu[i] );

			DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
			nYPos += 19;

		}
	}
 	// ����
	if(m_ScoreInfo.lHuaZhuScore[wMeChairId]<0)
	{

		ZeroMemory(szBuffer,sizeof(szBuffer));
		_snprintf( szBuffer,CountArray(szBuffer),TEXT("����"),szBuffer,0-m_ScoreInfo.lHuaZhuScore[wMeChairId]);
		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
		nYPos += 19;

	}else if(m_ScoreInfo.lChaJiaoScore[wMeChairId]<0) // ���
	{
		ZeroMemory(szBuffer,sizeof(szBuffer));
		_snprintf( szBuffer,CountArray(szBuffer),TEXT("�޽�"),szBuffer);
		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),nXPos,nYPos,false );
		nYPos += 19;

	}
 
	//�ܼ�
	_snprintf( szBuffer,CountArray(szBuffer),TEXT("%ld"),m_ScoreInfo.lGameScore );
	if( m_ScoreInfo.lGameScore > 0 )
		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),m_ptBenchmark.x+151,m_ptBenchmark.y+117,false );
	else
		DrawTextString( pDC,szBuffer,RGB(255,255,255),RGB(0,0,0),m_ptBenchmark.x+115,m_ptBenchmark.y+114,false );


	UINT winWidth = m_ImageGameWin->GetWidth();
	UINT winHeight = m_ImageGameWin->GetWidth();

	CDC memdc;  
	HBITMAP hBitmap; 
	CBitmap bmp;
	HGDIOBJ pOldBitmap,wingidobj;  
	memdc.CreateCompatibleDC(pDC);  
	bmp.CreateCompatibleBitmap(pDC,winWidth,winHeight); 
	memdc.SelectObject(&bmp);  

	memdc.SetTextColor(RGB(0,255,0));
	memdc.TextOut(0,0,TEXT("asdf"),4);

	//wingidobj = m_ImageGameWin.GetImage();
	//pOldBitmap = memdc.SelectObject(wingidobj);  

	//pDC->BitBlt(nXPos,nYPos,winWidth,winHeight,&memdc,winWidth,winHeight,0);

	BLENDFUNCTION bf;  
	bf.BlendOp = AC_SRC_OVER;  
	bf.BlendFlags = 0;  
	bf.SourceConstantAlpha = 100;  
	bf.AlphaFormat = 1;  
	pDC->AlphaBlend(nXPos,nYPos,winWidth,winHeight,&memdc,0,0,winWidth,winHeight,bf);  
	memdc.SelectObject(pOldBitmap);   
 
	return;

 }


//��������
void CScoreControl::DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos, bool bDrawCenter)
{
	//��������
	int nStringLength=lstrlen(pszString);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	if( bDrawCenter )
	{
		TEXTMETRIC tm;
		ZeroMemory( &tm,sizeof(tm) );
		GetTextMetrics(pDC->m_hDC,&tm );
		nXPos -= tm.tmAveCharWidth*nStringLength/2;
		nYPos -= tm.tmHeight/2;
	}

	//�滭�߿�
	pDC->SetTextColor(crFrame);
	for (int i=0;i<CountArray(nXExcursion);i++)
	{
		pDC->TextOut(nXPos+nXExcursion[i],nYPos+nYExcursion[i],pszString,nStringLength);
	}

	//�滭����
	pDC->SetTextColor(crText);
	pDC->TextOut(nXPos,nYPos,pszString,nStringLength);

	return;
}

//�滭����
void CScoreControl::DrawNumberString( CDC *pDC, CPngImage &PngNumber, int nXPos, int nYPos, LONG lNumber, bool bDrawCenter)
{
	int nWidthNumber = PngNumber.GetWidth()/10;
	int nHeightNumber = PngNumber.GetHeight();

	int nXDrawPos = nXPos, nYDrawPos = nYPos;
	nYDrawPos -= nHeightNumber/2;

	CHAR szNum[256] = {0};
	_snprintf(szNum,CountArray(szNum),"%+ld",lNumber);

	if( bDrawCenter )
	{
		nXDrawPos -= (lstrlen(szNum)-1)*nWidthNumber/2;
	}

	for( int i = 1; i < lstrlen(szNum); i++ )
	{
		if( ::isdigit(szNum[i]) )
		{
			PngNumber.DrawImage( pDC,nXDrawPos,nYDrawPos,nWidthNumber,nHeightNumber,(((int)szNum[i]-48))*nWidthNumber,
				0,nWidthNumber,nHeightNumber );
		}
		else
		{
			break;
		}
		nXDrawPos += nWidthNumber;
	}
}

//
void CScoreControl::SetBenchmarkPos( int nXPos, int nYPos )
{
	m_ptBenchmark.SetPoint( nXPos,nYPos );
}

//////////////////////////////////////////////////////////////////////////
