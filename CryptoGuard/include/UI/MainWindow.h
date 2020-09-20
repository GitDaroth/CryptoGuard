#pragma once

#include <QWidget>

#include "ui_MainWindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow m_ui;
};