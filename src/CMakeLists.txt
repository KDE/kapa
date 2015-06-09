#
# Kapa Daemon
#
add_executable(kapad
    main.cpp
    emailfetchjob.cpp
    processor.cpp
    microdataparser.cpp
)
target_link_libraries(kapad
    Qt5::Core
    Qt5::Xml
    KF5::IMAP
    KF5::CoreAddons
    KDocumentStore
)

install(TARGETS kapad ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(autotests)
