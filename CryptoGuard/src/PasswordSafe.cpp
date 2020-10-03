#include "PasswordSafe.h"

#include "Hashing/Scrypt.h"
#include "Utils.h"
#include <QRandomGenerator>
#include <iostream>
#include <fstream>

PasswordSafe::PasswordSafe(const std::string& label, const std::string& masterPassword)
{
	m_isValid = true;
	m_isLocked = true;
	m_label = label;

	// Generate Salt for MasterPassword 64 Bytes
	m_masterPasswordSalt = "";
	for(int i = 0; i < 16; i++)
		m_masterPasswordSalt += Utils::ulongToString(QRandomGenerator::system()->generate());

	m_hashedMasterPassword = Scrypt::hash(masterPassword, m_masterPasswordSalt);
}

PasswordSafe::PasswordSafe(const std::string& filePath)
{
	m_isLocked = true;
	readFromFile(filePath);
}

PasswordSafe::~PasswordSafe()
{
}

bool PasswordSafe::addPasswordEntry(PasswordEntry* passwordEntry)
{
	if(m_isLocked || passwordEntry->isLocked())
		return false;

	m_passwordEntries.push_back(passwordEntry);

	return true;
}

bool PasswordSafe::removePasswordEntry(PasswordEntry* passwordEntry)
{
	if(m_isLocked)
		return false;

	return m_passwordEntries.removeOne(passwordEntry);
}

bool PasswordSafe::removePasswordEntry(int index)
{
	if(m_isLocked)
		return false;

	if(m_passwordEntries.size() <= index || index < 0)
		return false;

	m_passwordEntries.removeAt(index);
	return true;
}

bool PasswordSafe::switchPasswordEntries(PasswordEntry* passwordEntryA, PasswordEntry* passwordEntryB)
{
	if(m_isLocked)
		return false;

	if(!m_passwordEntries.contains(passwordEntryA) || !m_passwordEntries.contains(passwordEntryB))
		return false;

	int indexA = m_passwordEntries.indexOf(passwordEntryA);
	int indexB = m_passwordEntries.indexOf(passwordEntryB);
	return switchPasswordEntries(indexA, indexB);
}

bool PasswordSafe::switchPasswordEntries(int indexA, int indexB)
{
	if(m_isLocked)
		return false;

	if(m_passwordEntries.size() <= indexA || indexA < 0 ||
	   m_passwordEntries.size() <= indexB || indexB < 0)
		return false;

	PasswordEntry* temp = m_passwordEntries[indexA];
	m_passwordEntries[indexA] = m_passwordEntries[indexB];
	m_passwordEntries[indexB] = temp;

	return true;
}

bool PasswordSafe::lock(const std::string& masterPassword)
{
	if(m_isLocked)
		return false;

	std::string hashedMasterPassword = Scrypt::hash(masterPassword, m_masterPasswordSalt);
	if(m_hashedMasterPassword != hashedMasterPassword)
		return false;

	for(PasswordEntry* entry : m_passwordEntries)
		entry->lock(masterPassword);

	m_isLocked = true;
	return true;
}

bool PasswordSafe::unlock(const std::string& masterPassword)
{
	if(!m_isLocked)
		return false;

	std::string hashedMasterPassword = Scrypt::hash(masterPassword, m_masterPasswordSalt);
	if(m_hashedMasterPassword != hashedMasterPassword)
		return false;

	for(PasswordEntry* entry : m_passwordEntries)
		entry->unlock(masterPassword);

	m_isLocked = false;
	return true;
}

bool PasswordSafe::changeMasterPassword(const std::string& oldMasterPassword, const std::string& newMasterPassword)
{
	std::string hashedMasterPassword = Scrypt::hash(oldMasterPassword, m_masterPasswordSalt);
	if(m_hashedMasterPassword != hashedMasterPassword)
		return false;

	// Generate new Salt for MasterPassword 64 Bytes
	m_masterPasswordSalt = "";
	for(int i = 0; i < 16; i++)
		m_masterPasswordSalt += Utils::ulongToString(QRandomGenerator::system()->generate());

	m_hashedMasterPassword = Scrypt::hash(newMasterPassword, m_masterPasswordSalt);

	for(PasswordEntry* entry : m_passwordEntries)
	{
		std::string password = entry->getPassword(oldMasterPassword);
		if(entry->isLocked())
		{
			entry->unlock(oldMasterPassword);
			entry->lock(newMasterPassword);
		}
		entry->setPassword(password, newMasterPassword);
		password = "";
	}

	return true;
}

void PasswordSafe::setLabel(const std::string& label)
{
	m_label = label;
}

bool PasswordSafe::isValid() const
{
	return m_isValid;
}

const std::string& PasswordSafe::getLabel() const
{
	return m_label;
}

int PasswordSafe::getPasswordEntryCount() const
{
	return m_passwordEntries.size();
}

QVector<PasswordEntry*> PasswordSafe::getPasswordEntries()
{
	return m_passwordEntries;
}

void PasswordSafe::readFromFile(const std::string& filePath)
{
	m_isValid = false;
	std::ifstream file;
	file.open(filePath, std::ios::binary | std::ios::in);

	if(!file.is_open())
		return;

	uint16_t labelLength;
	file.read((char*)&labelLength, 4);
	m_label.resize(labelLength);
	file.read(&m_label[0], labelLength);

	uint16_t passwordEntryCount;
	file.read((char*)&passwordEntryCount, 4);

	m_hashedMasterPassword.resize(64);
	file.read(&m_hashedMasterPassword[0], 64);

	m_masterPasswordSalt.resize(64);
	file.read(&m_masterPasswordSalt[0], 64);

	m_passwordEntries.clear();
	for(int i = 0; i < passwordEntryCount; i++)
	{
		uint16_t entryLabelLength;
		file.read((char*)&entryLabelLength, 4);
		std::string entryLabel;
		entryLabel.resize(entryLabelLength);
		file.read(&entryLabel[0], entryLabelLength);

		uint16_t userNameLength;
		file.read((char*)&userNameLength, 4);
		std::string userName;
		userName.resize(userNameLength);
		file.read(&userName[0], userNameLength);

		uint16_t emailLength;
		file.read((char*)&emailLength, 4);
		std::string email;
		email.resize(emailLength);
		file.read(&email[0], emailLength);

		uint16_t encryptedPasswordLength;
		file.read((char*)&encryptedPasswordLength, 4);
		std::string encryptedPassword;
		encryptedPassword.resize(encryptedPasswordLength);
		file.read(&encryptedPassword[0], encryptedPasswordLength);

		std::string initializationVector;
		initializationVector.resize(16);
		file.read(&initializationVector[0], 16);

		PasswordEntry* passwordEntry = new PasswordEntry(entryLabel, userName, email, encryptedPassword, initializationVector);
		m_passwordEntries.push_back(passwordEntry);
	}

	file.close();
	m_isValid = true;
}

void PasswordSafe::writeToFile(const std::string& filePath)
{
	std::ofstream file;
	file.open(filePath, std::ios::binary | std::ios::out);

	if(!file.is_open())
		return;

	uint16_t labelLength = m_label.size();
	file.write((char*)&labelLength, 4);
	file.write(&m_label[0], labelLength);

	uint16_t passwordEntryCount = m_passwordEntries.size();
	file.write((char*)&passwordEntryCount, 4);

	file.write(&m_hashedMasterPassword[0], 64);
	file.write(&m_masterPasswordSalt[0],64);

	for(PasswordEntry* entry : m_passwordEntries)
	{
		uint16_t entryLabelLength = entry->getLabel().size();
		file.write((char*)&entryLabelLength, 4);
		file.write(&entry->getLabel()[0], entryLabelLength);

		uint16_t userNameLength = entry->getUserName().size();
		file.write((char*)&userNameLength, 4);
		file.write(&entry->getUserName()[0], userNameLength);

		uint16_t emailLength = entry->getEmail().size();
		file.write((char*)&emailLength, 4);
		file.write(&entry->getEmail()[0], emailLength);

		uint16_t encryptedPasswordLength = entry->getEncryptedPassword().size();
		file.write((char*)&encryptedPasswordLength, 4);
		file.write(&entry->getEncryptedPassword()[0], encryptedPasswordLength);

		file.write(&entry->getInitializationVector()[0], 16);
	}

	file.close();
}