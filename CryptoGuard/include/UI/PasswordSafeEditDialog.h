#pragma once

#include <QDialog>
#include "PasswordSafe.h"

#include "ui_PasswordSafeEditDialog.h"

class PasswordSafeEditDialog : public QDialog
{
	Q_OBJECT
public:
	PasswordSafeEditDialog(PasswordSafe* passwordSafe, QWidget* parent = nullptr, Qt::WindowFlags flags = { 0 });
	~PasswordSafeEditDialog();

	QString getLabel() const;
	QString getOldMasterPassword() const;
	QString getNewMasterPassword() const;

public slots:
	void onEditButtonClicked();
	void onCancelButtonClicked();
	void onGeneratePasswordButtonClicked();
	void onMasterPasswordChanged(const QString& password);

private:
	void connectUiEvents();

	Ui::PasswordSafeEditDialog m_ui;
	PasswordSafe* m_passwordSafe;
};