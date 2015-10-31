add_library(math_functions mysqrt.cpp)

install (TARGETS math_functions DESTINATION bin)
install (FILES mysqrt.h DESTINATION include)