#include <cstdio>

#define common_testing_lib_def_default_printf "\x1B[0m"
#define common_testing_lib_def_red_printf "\x1B[31m"
#define common_testing_lib_def_green_printf "\x1B[32m"

#define TEST_ASSERT( condition, test_description )		\
	printf("%s: ", test_description);					\
	if ( (condition) )									\
	{													\
		printf("%sPASS%s\n",							\
			   common_testing_lib_def_green_printf,		\
			   common_testing_lib_def_default_printf);	\
	}													\
	else												\
	{													\
		printf("%sFAIL%s\n",							\
			   common_testing_lib_def_red_printf,		\
			   common_testing_lib_def_default_printf);	\
	}
