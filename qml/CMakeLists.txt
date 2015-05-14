#
# QML Plugin
#
set(qml_plugin_SRCS
    qmlplugins.cpp
    flightreservation.cpp
)

add_library(kapaqmlplugin SHARED ${qml_plugin_SRCS})
target_link_libraries(kapaqmlplugin
    Qt5::Qml
    KDocumentStore
)

install (TARGETS kapaqmlplugin DESTINATION ${QML_INSTALL_DIR}/org/kde/kapa)
install (FILES qmldir DESTINATION ${QML_INSTALL_DIR}/org/kde/kapa)
install (FILES FlightInformation.qml
               airplane49.png
         DESTINATION ${QML_INSTALL_DIR}/org/kde/kapa)
