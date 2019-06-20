#pragma once
#include "TraceLog.h"
#include "Dictionary.h"
#include "Containers.h"
#include "ui_MainWindow.h"
#include "ui_GestureHotkey.h"
#include "ui_PopWindow.h"
#include "AnimationLine.h"
#include <string.h>
#include <QTimer>
#include <QMessageBox>
#include <QtWidgets/QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>


class WordWindow : public QMainWindow
{
	Q_OBJECT

public:
	WordWindow(QWidget *parent = Q_NULLPTR);
	void showText(std::string str);
	void showTextRed(std::string str);
	std::pair<std::string, std::string> getDefinedCommand();
	void setHotkey(std::string str);
public slots:
	void setCommandInfo();
	void setCommandDefinition();
private:
	Ui::MainWindow ui2;
};
class PWindow : public QMainWindow
{
	Q_OBJECT

public:
	PWindow(QWidget *parent = Q_NULLPTR);
private:
	Ui::PopWindow ui3;
};

class SettingWindow : public QMainWindow
{
	Q_OBJECT

public:
	SettingWindow(QWidget *parent = Q_NULLPTR);
	void clear_canvas();
	void setWindowToCursor();
	//void draw_point(Point<long> p, bool isTouching);
	void draw_point(QColor color, Point<long> p, bool isTouching);
	void showText(std::string str, std::string hk);
	void hideText();
	void createTrayMenus();
	void createTrayIcon();
public slots:
	void freeze_timer_update();
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void terminateProgram();

	void restartProgram();

private:
	QSystemTrayIcon * myTrayIcon;
	QMenu * trayMenu;
	QAction * quitAction;
	QAction * restartAction;

	std::vector<AnimationLine> linelist;
	Ui::GestureHotkeyClass ui1;
	Point<long> prev_point;
	QGraphicsScene scene;
	QTimer *freeze_timer;
	int hide_count = 0;
	bool is_showing = false;
};
