cmake_minimum_required(VERSION 3.16)

add_library(bsa_packer SHARED)
mo2_configure_plugin(bsa_packer WARNINGS OFF
	PUBLIC_DEPENDS libbsarch
	PRIVATE_DEPENDS boost Qt::Concurrent DirectXTex)

target_include_directories(bsa_packer
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${BOOST_DI_ROOT}/include)
target_compile_definitions(bsa_packer PRIVATE BSAPACKER_LIBRARY)

mo2_install_target(bsa_packer)
