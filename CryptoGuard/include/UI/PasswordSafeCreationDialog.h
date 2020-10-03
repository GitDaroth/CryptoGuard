#pragma once

#include <QDialog>

#include "ui_PasswordSafeCreationDialog.h"

class PasswordSafeCreationDialog : public QDialog
{
	Q_OBJECT
public:
	PasswordSafeCreationDialog(QWidget* parent = nullptr, Qt::WindowFlags flags = {0});
	~PasswordSafeCreationDialog();

	QString getFilePath() const;
	QString getLabel() const;
	QString getMasterPassword() const;

public slots:
	void onCreateButtonClicked();
	void onCancelButtonClicked();
	void onSelectFilePathButtonClicked();
	void onGeneratePasswordButtonClicked();

private:
	void connectUiEvents();

	Ui::PasswordSafeCreationDialog m_ui;
};