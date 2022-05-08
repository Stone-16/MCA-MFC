#pragma once
#include "afxwin.h"



// CControlView ������ͼ

class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

protected:
	CControlView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CControlView();

public:
	enum { IDD = IDD_DIALOG_CONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditPeriod;
	double m_nPeriod;
	CEdit m_EditHight;
	double m_nHight;
	CButton m_ButtonPaint;
	CButton m_ButtonClear;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonPaint();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnMenuPaint();
	afx_msg void OnMenuClear();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	BOOL m_bCheckAuto;
	BOOL m_bCheckAuto;
	afx_msg void OnBnClickedCheckTimer();
};


