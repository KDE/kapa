configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h @ONLY)

ecm_add_test(microdataparsertest.cpp ../microdataparser.cpp
    TEST_NAME "microdataparsertest"
    LINK_LIBRARIES Qt5::Test Qt5::Xml
)
