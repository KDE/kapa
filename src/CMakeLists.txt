add_executable(kdenowd main.cpp emailfetchjob.cpp)
target_link_libraries(kdenowd
    Qt5::Core
    KF5::Imap
    KF5::CoreAddons
)

install(TARGETS kdenowd ${INSTALL_TARGETS_DEFAULT_ARGS})

add_subdirectory(autotests)
