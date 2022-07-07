
// Cursova2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Cursova2.h"
#include "Cursova2Dlg.h"
#include "afxdialogex.h"
#include <list>
#include <string>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CCursova2Dlg



CCursova2Dlg::CCursova2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CURSOVA2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCursova2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCursova2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CCursova2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CCursova2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCursova2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCursova2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений CCursova2Dlg

BOOL CCursova2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CCursova2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCursova2Dlg::OnPaint()
{
	CPaintDC dc(this); // контекст устройства для рисования
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/*string name;
		int x, y, line, ValueOfAngles = 0;
		ifstream ifs;
		ifs.open("filePoint.txt");
		if (!ifs.is_open()){}
		else
		{
			while (!ifs.eof())
			{
				ifs >> name;
				ifs >> x;
				ifs >> y;
				ValueOfAngles++;
			}
		}
		ifs.close();
		Point* PointArray = new Point[ValueOfAngles];
		ifs.open("filePoint.txt");
		if(!ifs.is_open()){}
		else 
		{
			for (int i = 0; i < ValueOfAngles; i++)
			{
				ifs >> name;
				ifs >> x;
				ifs >> y;
				PointArray[i] = Point(x, y);
			}
		}
		ifs.close();
		ifs.open("Line.txt");
		if(!ifs.is_open()){}
		else
		{
			ifs >> name;
			ifs >> line;
		}
		ifs.close();
		
		PolyGon FirstPolygon(PointArray, ValueOfAngles, line);
		FirstPolygon.DrawingPolygon(dc);
		FirstPolygon.SearchRadius();
		FirstPolygon.DrawCircle(dc);
		CDialogEx::OnPaint();*/
		Program.Draw(dc);
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCursova2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCursova2Dlg::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnCancel();
}


void CCursova2Dlg::OnBnClickedButton1()
{
	Program.Run();
	Invalidate();
}


void CCursova2Dlg::OnBnClickedButton2()
{
	
	int res = _spawnl(_P_WAIT, "C:\\Windows\\notepad.exe","notepad.exe", "filePoint.txt", NULL);
	int res1 = _spawnl(_P_WAIT, "C:\\Windows\\notepad.exe", "notepad.exe", "Line.txt", NULL);
	Program.Init();
	Invalidate();
}


void CCursova2Dlg::OnBnClickedButton3()
{
	
}
