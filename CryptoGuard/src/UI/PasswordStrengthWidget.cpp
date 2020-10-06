#include "UI/PasswordStrengthWidget.h"

#include "Utils.h"

PasswordStrengthWidget::PasswordStrengthWidget(QWidget* parent) :
	QWidget(parent)
{
	m_ui.setupUi(this);
}

PasswordStrengthWidget::~PasswordStrengthWidget()
{
}

void PasswordStrengthWidget::updatePasswordStrength(const QString& password)
{
	float score = Utils::calcPasswordStrength(password.toStdString());
	m_ui.scoreProgressBar->setValue(score * 100);

	QPalette palette;
	palette.setColor(QPalette::Highlight, QColor((1.f - score) * 255, score * 255, 0));
	m_ui.scoreProgressBar->setPalette(palette);
}