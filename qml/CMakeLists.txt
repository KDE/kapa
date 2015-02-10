#
# QML Plugin
#
set(qml_plugin_SRCS
    qmlplugins.cpp
    flightreservation.cpp
)

add_library(kdenowqmlplugin SHARED ${qml_plugin_SRCS})
target_link_libraries(kdenowqmlplugin
    Qt5::Qml
    KDocumentStore
)

install (TARGETS kdenowqmlplugin DESTINATION ${QML_INSTALL_DIR}/org/kde/now)
install (FILES qmldir DESTINATION ${QML_INSTALL_DIR}/org/kde/now)
install (FILES FlightInformation.qml
               airplane49.png
         DESTINATION ${QML_INSTALL_DIR}/org/kde/now)
