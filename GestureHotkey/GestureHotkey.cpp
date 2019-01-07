#include "GestureHotkey.h"
#include "windows.h"
#include "ExternContainer.h"

WordWindow::WordWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui2.setupUi(this);
}
GestureHotkey::GestureHotkey(QWidget *parent)
	: QMainWindow(parent)
{
	ui1.setupUi(this);
	scene.setSceneRect(0, 0, 5000, 4000);
	freeze_timer = new QTimer(this);
	connect(freeze_timer, SIGNAL(timeout()), this, SLOT(freeze_timer_update()));
	freeze_timer->start(3);
}
void GestureHotkey::setWindowToCursor() {
	QPoint p = QCursor::pos();
	int x_off = p.x() - (this->width())/2;
	int y_off = p.y() - (this->height())/2;
	
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

void GestureHotkey::draw_point(QColor color, Point<long> p, bool isTouching)
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

void GestureHotkey::freeze_timer_update()
{
	if (is_showing) {
		hide_count++;
		this->setWindowOpacity(TRANSPARENCY -(hide_count/80.0));
		if (hide_count == TRANSPARENCY*80) {
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

void GestureHotkey::showText(std::string str, std::string hk)
{
	ui1.textLabel->setText(QString::fromStdString(str));
	//ui1.textLabel->show();
	ui1.hotkeyLabel->setText(QString::fromStdString(hk));
	//ui1.hotkeyLabel->show();
	freeze_timer->start(12);
	is_showing = true;
	hide_count++;
}
void GestureHotkey::hideText()
{
	ui1.textLabel->setText(" ");
	ui1.hotkeyLabel->setText(" ");
}

void GestureHotkey::clear_canvas()
{
	scene.clear();
	ui1.graphicsView->setScene(&scene);
	ui1.graphicsView->fitInView(scene.sceneRect());
	prev_point.x = -1;
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
