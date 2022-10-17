set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME "Tech Engineering")
message("This project has been created by ${NAME}.")

add_library(library
            src/knn.cpp)
     
target_include_directories(library PUBLIC include)
