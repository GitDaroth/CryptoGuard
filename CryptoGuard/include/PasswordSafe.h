#pragma once

#include "PasswordEntry.h"
#include <QVector>

class PasswordSafe
{
public:
	PasswordSafe(const std::string& label, const std::string& masterPassword);
	PasswordSafe(const std::string& filePath);
	~PasswordSafe();

	bool addPasswordEntry(PasswordEntry* passwordEntry);
	bool removePasswordEntry(PasswordEntry* passwordEntry);
	bool removePasswordEntry(int index);
	bool switchPasswordEntries(PasswordEntry* passwordEntryA, PasswordEntry* passwordEntryB);
	bool switchPasswordEntries(int indexA, int indexB);

	bool lock(const std::string& masterPassword);
	bool unlock(const std::string& masterPassword);

	bool changeMasterPassword(const std::string& oldMasterPassword, const std::string& newMasterPassword);
	void setLabel(const std::string& label);

	bool isMasterPasswordCorrect(const std::string& masterPassword) const;
	bool isValid() const;
	bool isLocked() const;
	const std::string& getLabel() const;
	int getPasswordEntryCount() const;
	QVector<PasswordEntry*> getPasswordEntries();

	void readFromFile(const std::string& filePath);
	void writeToFile(const std::string& filePath);

private:
	bool m_isValid;
	std::string m_label;
	std::string m_masterPasswordSalt;
	std::string m_hashedMasterPassword;
	QVector<PasswordEntry*> m_passwordEntries;
	bool m_isLocked;
};


