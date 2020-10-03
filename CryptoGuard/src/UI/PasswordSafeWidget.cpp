#include "UI/PasswordSafeWidget.h"

PasswordSafeWidget::PasswordSafeWidget(PasswordSafe* passwordSafe, QWidget* parent) :
	QWidget(parent),
	m_passwordSafe(passwordSafe)
{
	m_ui.setupUi(this);
	m_ui.label->setText(QString::fromStdString(m_passwordSafe->getLabel()));
}

PasswordSafeWidget::~PasswordSafeWidget()
{
}

PasswordSafe* PasswordSafeWidget::getPasswordSafe()
{
	return m_passwordSafe;
}
