add_subdirectory(3rdParty/zxcvbn)
set_target_properties(zxcvbn PROPERTIES FOLDER 3rdParty)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

set(miscFiles
	src/main.cpp
	include/Utils.h
    include/PasswordSafe.h
	src/PasswordSafe.cpp
    include/PasswordEntry.h
	src/PasswordEntry.cpp)

set(encryptionFiles
	include/Encryption/AES.h        
	src/Encryption/AES.cpp)

set(hashingFiles
    include/Hashing/SHA256.h
	src/Hashing/SHA256.cpp
    include/Hashing/Salsa20.h
	src/Hashing/Salsa20.cpp
    include/Hashing/HMAC.h
	src/Hashing/HMAC.cpp
    include/Hashing/PBKDF2.h
	src/Hashing/PBKDF2.cpp
    include/Hashing/Scrypt.h
	src/Hashing/Scrypt.cpp)

set(uiFiles
	include/UI/MainWindow.ui
	include/UI/MainWindow.h
	src/UI/MainWindow.cpp
	include/UI/PasswordSafeSelectionWidget.ui
	include/UI/PasswordSafeSelectionWidget.h
	src/UI/PasswordSafeSelectionWidget.cpp
	include/UI/PasswordSafeWidget.ui
	include/UI/PasswordSafeWidget.h
	src/UI/PasswordSafeWidget.cpp
	include/UI/PasswordSafeCreationDialog.ui
	include/UI/PasswordSafeCreationDialog.h
	src/UI/PasswordSafeCreationDialog.cpp
	include/UI/PasswordSafeUnlockDialog.ui
	include/UI/PasswordSafeUnlockDialog.h
	src/UI/PasswordSafeUnlockDialog.cpp
	include/UI/PasswordSafeEditDialog.ui
	include/UI/PasswordSafeEditDialog.h
	src/UI/PasswordSafeEditDialog.cpp
	include/UI/PasswordStrengthWidget.ui
	include/UI/PasswordStrengthWidget.h
	src/UI/PasswordStrengthWidget.cpp)

add_executable(CryptoGuard 
	${miscFiles}
	${encryptionFiles}
	${hashingFiles}
	${uiFiles})

source_group("" FILES ${miscFiles})
source_group("\\Encryption" FILES ${encryptionFiles})
source_group("\\Hashing" FILES ${hashingFiles})
source_group("\\UI" FILES ${uiFiles})

target_link_libraries(CryptoGuard PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui zxcvbn)
target_include_directories(CryptoGuard PUBLIC "include")