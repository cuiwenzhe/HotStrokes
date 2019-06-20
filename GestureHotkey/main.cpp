#include "QTWindows.h"
#include "InitGesture.h"
#include "ExternContainer.h"
#include <QPalette>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{


	//Make sure at most one instance of the tool is running
	std::wstring mutex = L"Mutex-Gesture-9527";
	LPCWSTR  gesture_mutex = mutex.c_str();
	HANDLE hMutexOneInstance(::CreateMutex(NULL, TRUE, gesture_mutex));
	bool bAlreadyRunning((::GetLastError() == ERROR_ALREADY_EXISTS));
	if (hMutexOneInstance == NULL || bAlreadyRunning)
	{
		if (hMutexOneInstance)
		{
			::ReleaseMutex(hMutexOneInstance);
			::CloseHandle(hMutexOneInstance);
		}
		MessageBox(NULL, TEXT("HotStrokes Demo is running"), TEXT("Info"), MB_OK);
		throw std::exception("The application is already running");
	}

	QApplication a(argc, argv);

	SettingWindow w;
	WordWindow pw;
	interface_handler.setSettingWindow(&w);
	interface_handler.setPopWindow(&pw);
	
	interface_handler.initDict();
	pw.hide();
	
	w.setWindowFlags(Qt::FramelessWindowHint);
	w.setAttribute(Qt::WA_TranslucentBackground, true);
	w.setWindowOpacity(TRANSPARENCY);
	InitGesture(argc, argv);
	
	return a.exec();
}
