#include "PasswordEntry.h"

#include "Encryption/AES.h"
#include "Utils.h"
#include <QRandomGenerator>

PasswordEntry::PasswordEntry(const std::string& label, const std::string& userName, const std::string& email,
							 const std::string& password, const std::string& masterPassword, bool isLocked)
{
	m_isLocked = false;
	m_label = label;
	m_userName = userName;
	m_email = email;
	setPassword(password, masterPassword);

	if(isLocked)
		lock(masterPassword);
}

PasswordEntry::PasswordEntry(const std::string& encryptedLabel, const std::string& encryptedUserName, const std::string& encryptedEmail,
							 const std::string& encryptedPassword, const std::string& initializationVector)
{
	m_isLocked = true;
	m_label = encryptedLabel;
	m_userName = encryptedUserName;
	m_email = encryptedEmail;
	m_encryptedPassword = encryptedPassword;
	m_initializationVector = initializationVector;
}

PasswordEntry::~PasswordEntry()
{
}

bool PasswordEntry::lock(const std::string& masterPassword)
{
	if(m_isLocked)
		return false;

	m_label = AES::encrypt(m_label, masterPassword, m_initializationVector);
	m_userName = AES::encrypt(m_userName, masterPassword, m_initializationVector);
	m_email = AES::encrypt(m_email, masterPassword, m_initializationVector);
	m_isLocked = true;

	return true;
}

bool PasswordEntry::unlock(const std::string& masterPassword)
{
	if(!m_isLocked)
		return false;

	m_label = AES::decrypt(m_label, masterPassword, m_initializationVector);
	m_userName = AES::decrypt(m_userName, masterPassword, m_initializationVector);
	m_email = AES::decrypt(m_email, masterPassword, m_initializationVector);
	m_isLocked = false;

	return true;
}

void PasswordEntry::setPassword(const std::string& password, const std::string& masterPassword)
{
	bool wasLocked = m_isLocked;
	if(wasLocked)
		unlock(masterPassword);

	// Generate InitializationVector for Encryption 16 Bytes
	m_initializationVector = "";
	for(int i = 0; i < 4; i++)
		m_initializationVector += Utils::ulongToString(QRandomGenerator::system()->generate());

	m_encryptedPassword = AES::encrypt(password, masterPassword, m_initializationVector);

	if(wasLocked)
		lock(masterPassword);
}

std::string PasswordEntry::getPassword(const std::string& masterPassword) const
{
	return AES::decrypt(m_encryptedPassword, masterPassword, m_initializationVector);
}

std::string PasswordEntry::getEncryptedPassword() const
{
	return m_encryptedPassword;
}

std::string PasswordEntry::getInitializationVector() const
{
	return m_initializationVector;
}

std::string PasswordEntry::getLabel() const
{
	return m_label;
}

std::string PasswordEntry::getUserName() const
{
	return m_userName;
}

std::string PasswordEntry::getEmail() const
{
	return m_email;
}

bool PasswordEntry::isLocked() const
{
	return m_isLocked;
}