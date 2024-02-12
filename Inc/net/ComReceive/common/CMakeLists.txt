project(ComReceiveKernel)

add_library(ComReceiveKernelLibrary STATIC ComReceive.cpp)

target_include_directories(ComReceiveKernelLibrary PUBLIC "./")

target_link_libraries(ComReceiveKernelLibrary PUBLIC ContainerListLibrary)  # Cyclic dependency on ContainerListLibrary  
target_link_libraries(ComReceiveKernelLibrary PRIVATE PDUConfigurationLibrary) #
target_link_libraries(ComReceiveKernelLibrary PRIVATE E2EProtectLibrary) # Cyclic dependency on E2EProtectLibrary