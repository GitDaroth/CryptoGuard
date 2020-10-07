#include "UI/PasswordSafeEditDialog.h"

#include "Utils.h"
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
	std::string password = Utils::generatePassword(12);
	m_ui.newMasterPasswordLineEdit->setText(QString::fromStdString(password));
	m_ui.repeatNewPasswordLineEdit->setText(QString::fromStdString(password));
}

void PasswordSafeEditDialog::onOldMasterPasswordShowHideButtonToggled(bool checked)
{
	if (checked)
	{
		m_ui.oldMasterPasswordShowHideButton->setText("hide");
		m_ui.oldMasterPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
	}
	else
	{
		m_ui.oldMasterPasswordShowHideButton->setText("show");
		m_ui.oldMasterPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
	}
}

void PasswordSafeEditDialog::onNewMasterPasswordShowHideButtonToggled(bool checked)
{
	if (checked)
	{
		m_ui.newMasterPasswordShowHideButton->setText("hide");
		m_ui.newMasterPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
	}
	else
	{
		m_ui.newMasterPasswordShowHideButton->setText("show");
		m_ui.newMasterPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
	}
}

void PasswordSafeEditDialog::onRepeatNewMasterPasswordShowHideButtonToggled(bool checked)
{
	if (checked)
	{
		m_ui.repeatNewPasswordShowHideButton->setText("hide");
		m_ui.repeatNewPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
	}
	else
	{
		m_ui.repeatNewPasswordShowHideButton->setText("show");
		m_ui.repeatNewPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
	}
}

void PasswordSafeEditDialog::onMasterPasswordChanged(const QString& password)
{
	m_ui.passwordStrengthWidget->updatePasswordStrength(password);
}

void PasswordSafeEditDialog::connectUiEvents()
{
	connect(m_ui.editButton, &QPushButton::clicked, this, &PasswordSafeEditDialog::onEditButtonClicked);
	connect(m_ui.cancelButton, &QPushButton::clicked, this, &PasswordSafeEditDialog::onCancelButtonClicked);
	connect(m_ui.generatePasswordButton, &QToolButton::clicked, this, &PasswordSafeEditDialog::onGeneratePasswordButtonClicked);
	connect(m_ui.oldMasterPasswordShowHideButton, &QToolButton::toggled, this, &PasswordSafeEditDialog::onOldMasterPasswordShowHideButtonToggled);
	connect(m_ui.newMasterPasswordShowHideButton, &QToolButton::toggled, this, &PasswordSafeEditDialog::onNewMasterPasswordShowHideButtonToggled);
	connect(m_ui.repeatNewPasswordShowHideButton, &QToolButton::toggled, this, &PasswordSafeEditDialog::onRepeatNewMasterPasswordShowHideButtonToggled);
	connect(m_ui.newMasterPasswordLineEdit, &QLineEdit::textChanged, this, &PasswordSafeEditDialog::onMasterPasswordChanged);
}
