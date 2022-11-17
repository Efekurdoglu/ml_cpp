cmake_minimum_required(VERSION 3.0.0)
project(ML_CPP VERSION 1.0.0)
project(ML_CPP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME "Tech Engineering")
set(EMAIL "efekurdoglu@outlook.com")
message("This project has been created by ${NAME}.")
message("Email: ${EMAIL}")
message("Copyright © 2022 Efe Kurdoglu. All rights reserved.")

add_library(libraries
            src/data.cpp
            src/data_handler.cpp
            src/coheir.cpp)

add_subdirectory(knn)
add_subdirectory(kmeans)

add_executable(main
            src/main.cpp) 

# add_executable(main
#             knn/src/main.cpp) 

# add_executable(main
#             kmeans/src/main.cpp) 
            
target_include_directories(libraries PUBLIC include knn/include kmeans/include)
target_link_libraries(main PUBLIC libraries library library2)


