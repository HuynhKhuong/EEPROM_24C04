project(PDUConfiguration)

add_library(PDUConfigurationLibrary STATIC "./${VARIABLE_DIR_POSTFIX}/MessageListDefine.cpp")

target_include_directories(PDUConfigurationLibrary INTERFACE "./common" )  #This needs improvement
target_include_directories(PDUConfigurationLibrary INTERFACE "./${VARIABLE_DIR_POSTFIX}") #This needs improvement

target_link_libraries(PDUConfigurationLibrary PRIVATE E2EProtectLibrary) #Cyclic Dependent on E2EProtectLibrary
