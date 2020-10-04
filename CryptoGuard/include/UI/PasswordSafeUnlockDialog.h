#pragma once

#include <QDialog>
#include "PasswordSafe.h"

#include "ui_PasswordSafeUnlockDialog.h"

class PasswordSafeUnlockDialog : public QDialog
{
	Q_OBJECT
public:
	PasswordSafeUnlockDialog(PasswordSafe* passwordSafe, QWidget* parent = nullptr, Qt::WindowFlags flags = { 0 });
	~PasswordSafeUnlockDialog();

	QString getMasterPassword() const;

public slots:
	void onUnlockButtonClicked();
	void onCancelButtonClicked();

private:
	void connectUiEvents();

	Ui::PasswordSafeUnlockDialog m_ui;
	PasswordSafe* m_passwordSafe;
};