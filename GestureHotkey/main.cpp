#include "GestureHotkey.h"
#include "InitGesture.h"
#include "ExternContainer.h"
#include <QPalette>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	GestureHotkey w;
	WordWindow mw;
	WordWindow pw;
	interface_handler.setTestWindow(&w);
	interface_handler.setWordWindow(&mw);
	interface_handler.setPopWindow(&pw);
	interface_handler.initDict();
	//std::string ss = interface_handler.GetActiveWindowTitle();
	pw.hide();
	
	w.setWindowFlags(Qt::FramelessWindowHint);
	w.setAttribute(Qt::WA_TranslucentBackground, true);
	w.setWindowOpacity(TRANSPARENCY);
	InitGesture(argc, argv);
	
	/*mw.setWindowFlags(Qt::FramelessWindowHint);
	mw.setAttribute(Qt::WA_TranslucentBackground, true);
	mw.setAttribute(Qt::WA_ShowWithoutActivating);

	mw.show();
	mw.showText("");
	mw.hide();*/
	

	
	return a.exec();
}
