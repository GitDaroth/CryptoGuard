set(files
	zxcvbn.h
	zxcvbn.cpp)

add_library(zxcvbn STATIC ${files})
target_include_directories(zxcvbn PUBLIC "")