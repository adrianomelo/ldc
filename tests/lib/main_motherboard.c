#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include <ldc/types.h>
#include <ldc/info.h>

#include <motherboard/motherboard.h>

START_TEST (motherboard_informacoes)
{
	struct device* plugin = new_device("motherboard");
	get_info(plugin);

	fail_unless(1, "Erro na estrutura de dados");

	free_device (&plugin);
}
END_TEST

Suite * core_suite(void)
{
    Suite *s = suite_create("LDC_motherboard");

    TCase *tc_core = tcase_create("Motherboard");
    tcase_add_test(tc_core, motherboard_informacoes);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = core_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ?
        EXIT_SUCCESS : EXIT_FAILURE;
}

