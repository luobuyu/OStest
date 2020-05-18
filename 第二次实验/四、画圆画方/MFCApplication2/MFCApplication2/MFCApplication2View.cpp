
// MFCApplication2View.cpp: CMFCApplication2View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMFCApplication2View::Ondraw)
END_MESSAGE_MAP()

// CMFCApplication2View 构造/析构

CMFCApplication2View::CMFCApplication2View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View 绘图

void CMFCApplication2View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication2View 打印

BOOL CMFCApplication2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication2View 诊断

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG

UINT DrawCircle(LPVOID lp)
{
	CMFCApplication2View* pDlg = (CMFCApplication2View*)lp;
	CDC* pDC = pDlg->GetDC();

	CPoint CirclePoint(200, 200);
	COLORREF crColor = RGB(255, 0, 0);
	CPen pen(PS_SOLID, 5, crColor);
	pDC->SelectObject(&pen);
	int r = 150;
	const double degree_half = 0.008726; //每半度 2×3.1415 / 720 

	for (int i = 0; i < 720; i++)
	{
		pDC->SetPixelV(
			CirclePoint.x + r * sin(degree_half * i),
			CirclePoint.y + r * cos(degree_half * i),
			crColor);
		Sleep(10);
	}
	return 0;
}

// CMFCApplication2View 消息处理程序
UINT DrawRectgle(LPVOID lp)
{
	CMFCApplication2View* pDlg = (CMFCApplication2View*)lp;
	CDC* pDC = pDlg->GetDC();

	CPoint LeftRight(400, 50);
	COLORREF crColor = RGB(255, 0, 0);
	CPen pen(PS_SOLID, 5, crColor);
	pDC->SelectObject(&pen);
	const int width = 2;
	for (int i = 0; i < 180; i++)
	{
		pDC->SetPixelV(
			LeftRight.x + width * i,
			LeftRight.y,
			crColor);
		Sleep(10);
	}

	for (int i = 0; i < 180; i++)
	{
		pDC->SetPixelV(
			LeftRight.x + width * 180,
			LeftRight.y + width * i,
			crColor);
		Sleep(10);
	}

	for (int i = 0; i < 180; i++)
	{
		pDC->SetPixelV(
			LeftRight.x - width * i + width * 180,
			LeftRight.y + width * 180,
			crColor);
		Sleep(10);
	}

	for (int i = 0; i < 180; i++)
	{
		pDC->SetPixelV(
			LeftRight.x,
			LeftRight.y + width * 180 - width * i,
			crColor);
		Sleep(10);
	}

	return 0;
}

void CMFCApplication2View::Ondraw()
{
	// TODO: 在此添加命令处理程序代码
	this->UpdateWindow();
	pThread_Circle = AfxBeginThread(DrawCircle, this);
	pThread_Circle = AfxBeginThread(DrawRectgle, this);

}
