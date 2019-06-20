#include "QTWindows.h"
#include "windows.h"
#include "ExternContainer.h"

WordWindow::WordWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui2.setupUi(this);
}

void WordWindow::showText(std::string str)
{
	/*this->show();
	ui2.infoLabel->setText(QString::fromStdString(str));
	this->hide();*/
}
void WordWindow::showTextRed(std::string str)
{
	this->show();
	ui2.infoLabel->setText(QString::fromStdString(str));
}
std::pair<std::string,std::string> WordWindow::getDefinedCommand() {
	std::string command = ui2.infoLabel->text().toStdString();
	std::string hotkey = ui2.hotkey->text().toStdString();
	pair<std::string, std::string> mPair(command,hotkey);
	return mPair;
}

void WordWindow::setCommandInfo() {
	ui2.infoLabel->setText(ui2.commandEditor->toPlainText());
}

void WordWindow::setHotkey(std::string str) {
	ui2.hotkey->setText(QString::fromStdString(str));
}

void WordWindow::setCommandDefinition()
{
	QString cmd = ui2.commandEditor->toPlainText();
	QString hotkey = ui2.hotkey->text();
	QMessageBox msgBox;
	if (hotkey == "Hotkey") {
		msgBox.setText("You need to define hotkey");
		msgBox.exec();
		return;
	}
	int status = interface_handler.createComandHotkey(cmd.toStdString(),hotkey.toStdString());
	if (status == CMD_OCCUPIED) {
		msgBox.setText(cmd + " is occupied");
		msgBox.exec();
		return;
	}
	else if (status == HOTKEY_OCCUPIED) {
		msgBox.setText(hotkey + " is occupied");
		msgBox.exec();
		return;
	}
	this->close();
}

/*********************************
*		Setting Window
**********************************/
SettingWindow::SettingWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui1.setupUi(this);
	scene.setSceneRect(0, 0, 5000, 4000);
	freeze_timer = new QTimer(this);
	connect(freeze_timer, SIGNAL(timeout()), this, SLOT(freeze_timer_update()));
	freeze_timer->start(3);
	createTrayIcon();
}
void SettingWindow::setWindowToCursor() {
	QPoint p = QCursor::pos();
	int x_off = p.x() - (this->width()) / 2;
	int y_off = p.y() - (this->height()) / 2;

	p.setX(x_off);
	p.setY(y_off);
	this->move(p);
}
/*
void GestureHotkey::draw_point(Point<long> p, bool isTouching)
{
double rad = 1;
double gap = 30.0;
QPen pen(QColor(67, 133, 245), 180, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
if (isTouching) {
if (prev_point.x != -1) {
if (prev_point.y == -1) {
prev_point = p;
}
int distance = std::hypot(p.x - prev_point.x, p.y - prev_point.y);
if (distance > 3 && distance <= gap) {
linelist.push_back(AnimationLine(this, &scene, pen, prev_point, p));
}
else if (distance > gap) {//insert point to make line smooth
int count = (int)(distance / gap);
double inc_x, inc_y;
inc_x = ((p.x - prev_point.x) * gap / (double)distance);
inc_y = ((p.y - prev_point.y) * gap / (double)distance);
Point<long> p_point = prev_point;
Point<long> n_point = prev_point;
for (count; count > 0; count--) {
n_point.x = p_point.x + inc_x;
n_point.y = p_point.y + inc_y;
linelist.push_back(AnimationLine(this, &scene, pen, p_point, n_point));
p_point = n_point;
}
linelist.push_back(AnimationLine(this, &scene, pen, n_point, p));
}
//scene.addLine(prev_point.x, prev_point.y, p.x, p.y, pen);
}
}
else {
linelist.clear();
clear_canvas();
p.y = -1;
}
prev_point = p;
}*/

void SettingWindow::draw_point(QColor color, Point<long> p, bool isTouching)
{
	double rad = 1;
	//QPen pen(QColor(82, 187, 173), 140, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QPen pen(color, 140, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	QBrush brush(QColor(82, 187, 173), Qt::SolidPattern);
	if (isTouching) {
		if (prev_point.x != -1) {
			scene.addLine(prev_point.x, prev_point.y, p.x, p.y, pen);
		}
	}
	prev_point = p;
	//scene.addEllipse(p.x, p.y, rad * 60, rad * 60,
	//	pen, brush);

	ui1.graphicsView->setScene(&scene);
	ui1.graphicsView->fitInView(scene.sceneRect());
}

void SettingWindow::freeze_timer_update()
{
	if (is_showing) {
		hide_count++;
		this->setWindowOpacity(TRANSPARENCY - (hide_count / 80.0));
		if (hide_count == TRANSPARENCY * 80) {
			hide_count = 0;
			hideText();
			is_showing = false;
			//this->setWindowOpacity(0);
			this->clear_canvas();
			this->destroy();
			interface_handler.triggerCurrentHotkey();

		}
	}
}

void SettingWindow::showText(std::string str, std::string hk)
{
	ui1.textLabel->setText(QString::fromStdString(str));
	//ui1.textLabel->show();
	ui1.hotkeyLabel->setText(QString::fromStdString(hk));
	//ui1.hotkeyLabel->show();
	freeze_timer->start(12);
	is_showing = true;
	hide_count++;
}
void SettingWindow::hideText()
{
	ui1.textLabel->setText(" ");
	ui1.hotkeyLabel->setText(" ");
}

void SettingWindow::createTrayMenus()
{
	quitAction = new QAction("Quit", this);
	restartAction = new QAction("Restart", this);

	this->connect(quitAction, SIGNAL(triggered()), this, SLOT(terminateProgram()));
	this->connect(restartAction, SIGNAL(triggered()), this, SLOT(restartProgram()));

	trayMenu = new QMenu((QWidget*)QApplication::desktop());
	trayMenu->addAction(quitAction);
	trayMenu->addAction(restartAction);
}

void SettingWindow::createTrayIcon()
{
	createTrayMenus();
	myTrayIcon = new QSystemTrayIcon(this);
	myTrayIcon->setIcon(QIcon(":GestureHotkey/Resources/Gesture.png"));

	myTrayIcon->setToolTip("HotStroke Demo");
	myTrayIcon->setContextMenu(trayMenu);
	myTrayIcon->show();
	myTrayIcon->showMessage("HotStrokes", "The demo is running", 
		QSystemTrayIcon::Information, 3000);
	this->connect(myTrayIcon,
		SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void SettingWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
		break;
	case QSystemTrayIcon::DoubleClick:
		break;
	case QSystemTrayIcon::MiddleClick:
		break;
	default:
		break;
	}
}

void SettingWindow::terminateProgram()
{
	myTrayIcon->showMessage("HotStrokes", "The demo Terminated",
		QSystemTrayIcon::Information, 3000);
	myTrayIcon->hide();
	exit(1);
}

void SettingWindow::restartProgram()
{
	myTrayIcon->showMessage("HotStrokes", "The demo Restart",
		QSystemTrayIcon::Information, 3000);
	interface_handler.reInitialTouchpad();
}

void SettingWindow::clear_canvas()
{
	scene.clear();
	ui1.graphicsView->setScene(&scene);
	ui1.graphicsView->fitInView(scene.sceneRect());
	prev_point.x = -1;
}
