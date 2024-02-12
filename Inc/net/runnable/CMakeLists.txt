project(NetRunnable)

add_library(NetRunnableLibrary NetRunnable.cpp)

target_include_directories(NetRunnableLibrary PUBLIC "./")

target_link_libraries(NetRunnableLibrary PRIVATE PDUConfigurationLibrary)
target_link_libraries(NetRunnableLibrary PRIVATE ComReceiveKernelLibrary)
