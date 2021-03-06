#pragma once

#include <QWidget>
#include <unordered_map>
#include "PasswordSafe.h"

#include "ui_PasswordSafeSelectionWidget.h"

class PasswordSafeSelectionWidget : public QWidget
{
	Q_OBJECT
public:
	PasswordSafeSelectionWidget(QWidget* parent = nullptr);
	~PasswordSafeSelectionWidget();

public slots:
	void onPasswordSafeEdited(PasswordSafe* passwordSafe);
	void onRemovePasswordSafeTriggered(PasswordSafe* passwordSafe);

private slots:
	void onOpenButtonClicked();
	void onCreateButtonClicked();

private:
	void connectUiEvents();
	void readPasswordSafeFile(const QString& filePath);
	void savePasswordSafeFilePaths();
	void openKnownPasswordSafeFiles();
	void updatePasswordSafeListWidget();

	Ui::PasswordSafeSelectionWidget m_ui;
	std::unordered_map<std::string, PasswordSafe*> m_passwordSafeMap;
};