# CryptoGuard

CryptoGuard is a password management application. I do not recommend to use CryptoGuard for your password management because I cannot quarantee total security. The purpose of this project is to teach myself the basics of cryptography (encryption, hashing, ...).

**Features:**
- AES256 encryption and decryption
- Scrypt hashing for master password
- encrypted passwords are saved in file PasswordSafe (.pws)

**Upcoming Features:**
- copy passwords to clipboard
- password generator
- password strength validator
- search function

## Build Instructions
CryptoGuard only supports Windows at the moment!

For Visual Studio 2019:
```
git clone https://github.com/GitDaroth/CryptoGuard
cd CryptoGuard
cmake_generate_VS2019.bat
```
Make sure to set the Qt5 path for cmake!

Open the generated Visual Studio solution in the "build" folder and build the "CryptoGuard" target.

## Dependencies
- [Qt5](https://www.qt.io)
- [Catch2](https://github.com/catchorg/Catch2)