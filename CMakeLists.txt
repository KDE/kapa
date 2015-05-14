project(kapa)
cmake_minimum_required(VERSION 2.8.12)

find_package(ECM 0.0.9 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${ECM_MODULE_PATH})

find_package(Qt5 REQUIRED NO_MODULE COMPONENTS Qml Quick Test)
find_package(KF5 5.5 REQUIRED COMPONENTS Plasma I18n Declarative Config)
find_package(KF5 REQUIRED COMPONENTS Imap Mime)
find_package(KDocumentStore REQUIRED)

include(FeatureSummary)
include(ECMAddTests)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(GenerateExportHeader)
include(ECMInstallIcons)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/src
)

add_subdirectory(src)
add_subdirectory(qml)
add_subdirectory(plasmoids)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
