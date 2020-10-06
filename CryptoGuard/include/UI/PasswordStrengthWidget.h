#pragma once

#include <QWidget>

#include "ui_PasswordStrengthWidget.h"

class PasswordStrengthWidget : public QWidget
{
	Q_OBJECT
public:
	PasswordStrengthWidget(QWidget* parent = nullptr);
	~PasswordStrengthWidget();

	void updatePasswordStrength(const QString& password);

private:
	Ui::PasswordStrengthWidget m_ui;
};