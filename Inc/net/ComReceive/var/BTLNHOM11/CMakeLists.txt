project(ContainerList)

add_library(ContainerListLibrary ContainerList.cpp)

target_include_directories(ContainerListLibrary PUBLIC "./")

target_link_libraries(ContainerListLibrary PRIVATE ComReceiveKernelLibrary) #Cyclic Dependency on ComReceiveKernelLibrary
target_link_libraries(ContainerListLibrary PRIVATE PDUConfigurationLibrary)