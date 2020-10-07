#include "UI/PasswordSafeCreationDialog.h"

#include "Utils.h"
#include <QFileDialog>

PasswordSafeCreationDialog::PasswordSafeCreationDialog(QWidget* parent, Qt::WindowFlags flags) :
	QDialog(parent, flags)
{
	m_ui.setupUi(this);
	connectUiEvents();
}

PasswordSafeCreationDialog::~PasswordSafeCreationDialog()
{

}

QString PasswordSafeCreationDialog::getFilePath() const
{
	return m_ui.filePathLineEdit->text() + "/" + m_ui.nameLineEdit->text() + ".pws";
}

QString PasswordSafeCreationDialog::getLabel() const
{
	return m_ui.nameLineEdit->text();
}

QString PasswordSafeCreationDialog::getMasterPassword() const
{
	return m_ui.masterPasswordLineEdit->text();
}

void PasswordSafeCreationDialog::onCreateButtonClicked()
{
	if (m_ui.filePathLineEdit->text().isEmpty())
		return;

	if (m_ui.nameLineEdit->text().isEmpty())
		return;

	if (m_ui.masterPasswordLineEdit->text().isEmpty() || m_ui.masterPasswordLineEdit->text() != m_ui.repeatPasswordLineEdit->text())
		return;

	accept();
}

void PasswordSafeCreationDialog::onCancelButtonClicked()
{
	reject();
}

void PasswordSafeCreationDialog::onSelectFilePathButtonClicked()
{
	const QString& filePath = QFileDialog::getExistingDirectory(this, "Select File Path", m_ui.filePathLineEdit->text());
	if (filePath != QString::null)
		m_ui.filePathLineEdit->setText(filePath);
}

void PasswordSafeCreationDialog::onGeneratePasswordButtonClicked()
{
	std::string password = Utils::generatePassword(12);
	m_ui.masterPasswordLineEdit->setText(QString::fromStdString(password));
	m_ui.repeatPasswordLineEdit->setText(QString::fromStdString(password));
}

void PasswordSafeCreationDialog::onMasterPasswordShowHideButtonToggled(bool checked)
{
	if (checked)
	{
		m_ui.masterPasswordShowHideButton->setText("hide");
		m_ui.masterPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
	}
	else
	{
		m_ui.masterPasswordShowHideButton->setText("show");
		m_ui.masterPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
	}
}

void PasswordSafeCreationDialog::onRepeatMasterPasswordShowHideButtonToggled(bool checked)
{
	if (checked)
	{
		m_ui.repeatPasswordShowHideButton->setText("hide");
		m_ui.repeatPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
	}
	else
	{
		m_ui.repeatPasswordShowHideButton->setText("show");
		m_ui.repeatPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
	}
}

void PasswordSafeCreationDialog::onMasterPasswordChanged(const QString& password)
{
	m_ui.passwordStrengthWidget->updatePasswordStrength(password);
}

void PasswordSafeCreationDialog::connectUiEvents()
{
	connect(m_ui.createButton, &QPushButton::clicked, this, &PasswordSafeCreationDialog::onCreateButtonClicked);
	connect(m_ui.cancelButton, &QPushButton::clicked, this, &PasswordSafeCreationDialog::onCancelButtonClicked);
	connect(m_ui.selectFilePathButton, &QToolButton::clicked, this, &PasswordSafeCreationDialog::onSelectFilePathButtonClicked);
	connect(m_ui.generatePasswordButton, &QToolButton::clicked, this, &PasswordSafeCreationDialog::onGeneratePasswordButtonClicked);
	connect(m_ui.masterPasswordShowHideButton, &QToolButton::toggled, this, &PasswordSafeCreationDialog::onMasterPasswordShowHideButtonToggled);
	connect(m_ui.repeatPasswordShowHideButton, &QToolButton::toggled, this, &PasswordSafeCreationDialog::onRepeatMasterPasswordShowHideButtonToggled);
	connect(m_ui.masterPasswordLineEdit, &QLineEdit::textChanged, this, &PasswordSafeCreationDialog::onMasterPasswordChanged);
}
