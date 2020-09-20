#pragma once

#include <string>
#include <vector>

class PasswordEntry
{
public:
	PasswordEntry(const std::string& label, const std::string& userName, const std::string& email,
				  const std::string& password, const std::string& masterPassword, bool isLocked);
	PasswordEntry(const std::string& encryptedLabel, const std::string& encryptedUserName, const std::string& encryptedEmail,
				  const std::string& encryptedPassword, const std::string& initializationVector);
	~PasswordEntry();

	bool lock(const std::string& masterPassword);
	bool unlock(const std::string& masterPassword);

	void setPassword(const std::string& password, const std::string& masterPassword);

	std::string getPassword(const std::string& masterPassword) const;
	std::string getEncryptedPassword() const;
	std::string getInitializationVector() const;
	std::string getLabel() const;
	std::string getUserName() const;
	std::string getEmail() const;
	bool isLocked() const;

private:
	std::string m_label;
	std::string m_userName;
	std::string m_email;
	std::string m_url;
	std::string m_encryptedPassword;
	std::string m_initializationVector;
	bool m_isLocked;
};
