set(miscFiles
        include/catch.hpp
        src/main.cpp
        ../CryptoGuard/include/Utils.h)

set(encryptionFiles
        src/AESTest.cpp
	../CryptoGuard/include/Encryption/AES.h        
	../CryptoGuard/src/Encryption/AES.cpp)

set(hashingFiles
        src/SHA256Test.cpp
        ../CryptoGuard/include/Hashing/SHA256.h
	../CryptoGuard/src/Hashing/SHA256.cpp
        src/Salsa20Test.cpp
        ../CryptoGuard/include/Hashing/Salsa20.h
	../CryptoGuard/src/Hashing/Salsa20.cpp
        src/HMACTest.cpp
        ../CryptoGuard/include/Hashing/HMAC.h
	../CryptoGuard/src/Hashing/HMAC.cpp
        src/PBKDF2Test.cpp
        ../CryptoGuard/include/Hashing/PBKDF2.h
	../CryptoGuard/src/Hashing/PBKDF2.cpp
        src/ScryptTest.cpp
        ../CryptoGuard/include/Hashing/Scrypt.h
	../CryptoGuard/src/Hashing/Scrypt.cpp)

add_executable(Test
	${miscFiles}
	${encryptionFiles} 
	${hashingFiles})

source_group("" FILES ${miscFiles})
source_group("\\Encryption" FILES ${encryptionFiles})
source_group("\\Hashing" FILES ${hashingFiles})

target_include_directories(Test PRIVATE "include" "../CryptoGuard/include")