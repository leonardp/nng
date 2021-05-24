# SPDX-License-Identifier: Apache-2.0

if(CONFIG_NNG)

	set(CMAKE_SYSTEM_NAME "Zephyr")
	set(NNG_DIR ${ZEPHYR_CURRENT_MODULE_DIR})

	add_subdirectory(${NNG_DIR} ${NNG_DIR}/bin)

endif()
