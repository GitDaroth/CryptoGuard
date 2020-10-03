#include "UI/PasswordSafeSelectionWidget.h"

#include "UI/PasswordSafeWidget.h"
#include "UI/PasswordSafeCreationDialog.h"
#include <QFileDialog>
#include <iostream>
#include <fstream>

PasswordSafeSelectionWidget::PasswordSafeSelectionWidget(QWidget* parent) :
	QWidget(parent)
{
	m_ui.setupUi(this);
	connectUiEvents();
	openKnownPasswordSafeFiles();
}

PasswordSafeSelectionWidget::~PasswordSafeSelectionWidget()
{
	for (auto& passwordSafeMapEntry : m_passwordSafeMap)
		delete passwordSafeMapEntry.second;

	m_passwordSafeMap.clear();
}

void PasswordSafeSelectionWidget::onOpenButtonClicked()
{
	const QString& filePath = QFileDialog::getOpenFileName(this, tr("Open Password Safe"), "", tr("Password Safe Files (*.pws)"));
	if (filePath != QString::null)
	{
		readPasswordSafeFile(filePath);
		updatePasswordSafeListWidget();
	}
}

void PasswordSafeSelectionWidget::onCreateButtonClicked()
{
	PasswordSafeCreationDialog creationDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
	if (creationDialog.exec() == QDialog::Accepted)
	{
		std::string passwordSafeLabel = creationDialog.getLabel().toStdString();
		std::string passwordSafeMasterPassword = creationDialog.getMasterPassword().toStdString();
		std::string passwordSafeFilePath = creationDialog.getFilePath().toStdString();

		PasswordSafe* passwordSafe = new PasswordSafe(passwordSafeLabel, passwordSafeMasterPassword);
		passwordSafe->lock(passwordSafeMasterPassword);
		passwordSafe->writeToFile(passwordSafeFilePath);

		m_passwordSafeMap.emplace(passwordSafeFilePath, passwordSafe);
		updatePasswordSafeListWidget();
	}
}

void PasswordSafeSelectionWidget::connectUiEvents()
{
	connect(m_ui.openButton, &QToolButton::pressed, this, &PasswordSafeSelectionWidget::onOpenButtonClicked);
	connect(m_ui.createButton, &QToolButton::pressed, this, &PasswordSafeSelectionWidget::onCreateButtonClicked);
}

void PasswordSafeSelectionWidget::readPasswordSafeFile(const QString& filePath)
{
	if (m_passwordSafeMap.find(filePath.toStdString()) != m_passwordSafeMap.end())
		return;

	PasswordSafe* passwordSafe = new PasswordSafe(filePath.toStdString());
	if (passwordSafe->isValid())
		m_passwordSafeMap.emplace(filePath.toStdString(), passwordSafe);
	else
		delete passwordSafe;
}

void PasswordSafeSelectionWidget::savePasswordSafeFilePaths()
{
	std::ofstream file;
	file.open("pws_files.txt", std::ios::out);

	if (!file.is_open())
		return;

	for (auto& passwordSafeMapEntry : m_passwordSafeMap)
		file << passwordSafeMapEntry.first << "\n";

	file.close();
}

void PasswordSafeSelectionWidget::openKnownPasswordSafeFiles()
{
	std::ifstream file;
	file.open("pws_files.txt", std::ios::in);

	if (!file.is_open())
		return;

	std::string lineText;
	while (std::getline(file, lineText))
		readPasswordSafeFile(QString::fromStdString(lineText));

	file.close();

	updatePasswordSafeListWidget();
}

void PasswordSafeSelectionWidget::updatePasswordSafeListWidget()
{
	m_ui.passwordSafeList->clear();

	for (auto& passwordSafeMapEntry : m_passwordSafeMap)
	{
		PasswordSafe* passwordSafe = passwordSafeMapEntry.second;
		QListWidgetItem* listItem = new QListWidgetItem();
		PasswordSafeWidget* passwordSafeWidget = new PasswordSafeWidget(passwordSafe);
		m_ui.passwordSafeList->insertItem(m_ui.passwordSafeList->count(), listItem);
		m_ui.passwordSafeList->setItemWidget(listItem, passwordSafeWidget);
		listItem->setText(QString::fromStdString(passwordSafe->getLabel()));
		listItem->setTextColor(QColor(0, 0, 0, 0));
		listItem->setFlags(listItem->flags() & ~Qt::ItemIsSelectable);
		listItem->setSizeHint(passwordSafeWidget->sizeHint());
	}

	m_ui.passwordSafeList->sortItems();

	savePasswordSafeFilePaths();
}
