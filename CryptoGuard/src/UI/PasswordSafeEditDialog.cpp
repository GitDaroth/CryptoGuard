#include "UI/PasswordSafeEditDialog.h"

#include <QFileDialog>

PasswordSafeEditDialog::PasswordSafeEditDialog(PasswordSafe* passwordSafe, QWidget* parent, Qt::WindowFlags flags) :
	QDialog(parent, flags),
	m_passwordSafe(passwordSafe)
{
	m_ui.setupUi(this);
	connectUiEvents();

	m_ui.nameLineEdit->setText(QString::fromStdString(m_passwordSafe->getLabel()));
}

PasswordSafeEditDialog::~PasswordSafeEditDialog()
{

}

QString PasswordSafeEditDialog::getLabel() const
{
	return m_ui.nameLineEdit->text();
}

QString PasswordSafeEditDialog::getOldMasterPassword() const
{
	return m_ui.oldMasterPasswordLineEdit->text();
}

QString PasswordSafeEditDialog::getNewMasterPassword() const
{
	return m_ui.newMasterPasswordLineEdit->text();
}

void PasswordSafeEditDialog::onEditButtonClicked()
{
	if (m_ui.nameLineEdit->text().isEmpty())
		return;

	if (!m_passwordSafe->isMasterPasswordCorrect(m_ui.oldMasterPasswordLineEdit->text().toStdString()))
		return;

	if (m_ui.newMasterPasswordLineEdit->text().isEmpty() || m_ui.newMasterPasswordLineEdit->text() != m_ui.repeatNewPasswordLineEdit->text())
		return;

	accept();
}

void PasswordSafeEditDialog::onCancelButtonClicked()
{
	reject();
}

void PasswordSafeEditDialog::onGeneratePasswordButtonClicked()
{
}

void PasswordSafeEditDialog::connectUiEvents()
{
	connect(m_ui.editButton, &QPushButton::clicked, this, &PasswordSafeEditDialog::onEditButtonClicked);
	connect(m_ui.cancelButton, &QPushButton::clicked, this, &PasswordSafeEditDialog::onCancelButtonClicked);
	connect(m_ui.generatePasswordButton, &QToolButton::clicked, this, &PasswordSafeEditDialog::onGeneratePasswordButtonClicked);
}
