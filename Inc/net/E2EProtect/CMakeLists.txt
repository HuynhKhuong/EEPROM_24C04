project(E2EProtect)

set(PDUComponent "")

get_filename_component(ReceiveKernelLogic "${GLOBAL_PROJECT_DIR}/ComReceive/common/ComReceive.hpp" DIRECTORY)
get_filename_component(ProjectContainerList "${GLOBAL_PROJECT_DIR}/ComReceive/${VARIABLE_DIR_POSTFIX}/ContainerList.hpp" DIRECTORY)

add_library(E2EProtectLibrary STATIC RxProtect.cpp)

target_include_directories(E2EProtectLibrary PUBLIC "./") # header is in same directory with source file 

target_link_libraries(E2EProtectLibrary PUBLIC PDUConfigurationLibrary) # Dependency on PDUConfigurationLibrary 
target_link_libraries(E2EProtectLibrary PRIVATE ComReceiveKernelLibrary) # Dependency on ComReceiveKernelLibrary 
target_link_libraries(E2EProtectLibrary PRIVATE ContainerListLibrary) # Dependency on ComReceiveKernelLibrary 

