#include "UI/PasswordSafeWidget.h"

#include "UI/PasswordSafeUnlockDialog.h"
#include "UI/PasswordSafeEditDialog.h"

PasswordSafeWidget::PasswordSafeWidget(PasswordSafe* passwordSafe, QWidget* parent) :
	QWidget(parent),
	m_passwordSafe(passwordSafe)
{
	m_ui.setupUi(this);
	connectUiEvents();

	m_ui.label->setText(QString::fromStdString(m_passwordSafe->getLabel()));
}

PasswordSafeWidget::~PasswordSafeWidget()
{
}

PasswordSafe* PasswordSafeWidget::getPasswordSafe()
{
	return m_passwordSafe;
}

void PasswordSafeWidget::onLockUnlockButtonToggled(bool checked)
{
	if (checked)
	{
		Qt::WindowFlags flags = Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint;
		PasswordSafeUnlockDialog unlockDialog(m_passwordSafe, this, flags);
		if (unlockDialog.exec() == QDialog::Accepted)
		{
			m_masterPassword = unlockDialog.getMasterPassword().toStdString();
			m_passwordSafe->unlock(m_masterPassword);
			m_ui.lockUnlockButton->setText("L");
		}
		else
			m_ui.lockUnlockButton->setChecked(false);
	}
	else
	{
		m_passwordSafe->lock(m_masterPassword);
		m_masterPassword = "****************************************************************";
		m_ui.lockUnlockButton->setText("U");
	}
}

void PasswordSafeWidget::onEditButtonClicked()
{
	Qt::WindowFlags flags = Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint;
	PasswordSafeEditDialog editDialog(m_passwordSafe, this, flags);
	if (editDialog.exec() == QDialog::Accepted)
	{
		std::string oldMasterPassword = editDialog.getOldMasterPassword().toStdString();
		std::string newMasterPassword = editDialog.getNewMasterPassword().toStdString();
		std::string oldLabel = m_passwordSafe->getLabel();
		std::string newLabel = editDialog.getLabel().toStdString();
		m_passwordSafe->setLabel(newLabel);
		m_passwordSafe->changeMasterPassword(oldMasterPassword, newMasterPassword);

		if (!m_passwordSafe->isLocked())
		{
			m_passwordSafe->lock(newMasterPassword);
			m_masterPassword = "****************************************************************";
			m_ui.lockUnlockButton->setText("U");
		}

		emit passwordSafeEdited(m_passwordSafe);
	}
}

void PasswordSafeWidget::onRemoveButtonClicked()
{
	emit removePasswordSafeTriggered(m_passwordSafe);
}

void PasswordSafeWidget::connectUiEvents()
{
	connect(m_ui.lockUnlockButton, &QToolButton::toggled, this, &PasswordSafeWidget::onLockUnlockButtonToggled);
	connect(m_ui.editButton, &QToolButton::clicked, this, &PasswordSafeWidget::onEditButtonClicked);
	connect(m_ui.removeButton, &QToolButton::clicked, this, &PasswordSafeWidget::onRemoveButtonClicked);
}