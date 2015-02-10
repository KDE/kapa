#
# KDE Now Daemon
#
add_executable(kdenowd
    main.cpp
    emailfetchjob.cpp
    processor.cpp
    microdataparser.cpp
)
target_link_libraries(kdenowd
    Qt5::Core
    Qt5::Xml
    KF5::Imap
    KF5::CoreAddons
    KDocumentStore
)

install(TARGETS kdenowd ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(autotests)
