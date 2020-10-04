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

signals:
	void passwordSafeEdited(PasswordSafe* passwordSafe);
	void removePasswordSafeTriggered(PasswordSafe* passwordSafe);

private slots:
	void onLockUnlockButtonToggled(bool checked);
	void onEditButtonClicked();
	void onRemoveButtonClicked();

private:
	void connectUiEvents();

	Ui::PasswordSafeWidget m_ui;
	PasswordSafe* m_passwordSafe;
	std::string m_masterPassword;
};