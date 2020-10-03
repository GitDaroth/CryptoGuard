#pragma once

#include <QWidget>
#include "PasswordSafe.h"

#include "ui_PasswordSafeWidget.h"

class PasswordSafeWidget : public QWidget
{
	Q_OBJECT
public:
	PasswordSafeWidget(PasswordSafe* passwordSafe, QWidget* parent = nullptr);
	~PasswordSafeWidget();

	PasswordSafe* getPasswordSafe();

private:
	Ui::PasswordSafeWidget m_ui;
	PasswordSafe* m_passwordSafe;
};