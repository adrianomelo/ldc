#include <string.h>

#include <check.h>

#include <ldc/types.h>
#include <ldc/errors.h>
#include <ldc/string.h>
#include <software/software.h>


 /***************************************
  *                                     *
  *    TESTES PARA A FUNÇÃO GET_INFO    *
  *                                     *
  ***************************************/
START_TEST(get_info_ok)
{
	struct device *dev = new_device("teste");
	int o = get_info(dev);
	fail_unless(o == SUCCESS && dev != NULL,"get_info retornou erro");
}
END_TEST

START_TEST(get_info_with_null_device)
{
	struct device *dev = NULL;
	int o = get_info(dev);
	fail_unless(o != SUCCESS && dev == NULL, "get_info com device NULL nao retorna erro");
}
END_TEST

 /********************************************
  *                                          *
  *    TESTES PARA A FUNÇÃO GET_PROG_INFO    *
  *                                          *
  ********************************************/
START_TEST(get_prog_info_ok)
{
	char *prog = "gcc";
	char *param = "--version | grep gcc";
	char *inf = NULL;
	int tamBuf = 150;
	int expected = SUCCESS;
	int status = get_prog_info(prog, param, &inf, tamBuf);
	fail_unless(status == expected && !is_blank(inf),"get_prog_info retornou erro");
}
END_TEST

START_TEST(get_prog_info_with_null_prog)
{
	char *prog = NULL;
	char *param = "--version | grep gcc";
	char *inf = NULL;
	int tamBuf = 50;
	int status = get_prog_info(prog, param, &inf, tamBuf);
	fail_unless(status != SUCCESS && is_blank(inf),"get_prog_info com prog NULL nao retornou erro");
}
END_TEST

START_TEST(get_prog_info_with_null_param)
{
	char *prog = "gcc";
	char *param = NULL;
	char *inf = NULL;
	int tamBuf = 50;
	int status = get_prog_info(prog, param, &inf, tamBuf);
	fail_unless(status != SUCCESS && is_blank(inf),"get_prog_info com param NULL nao retornou erro");
}
END_TEST

START_TEST(get_prog_info_with_invalid_tambuf)
{
	char *prog = "gcc";
	char *param = "--version | grep gcc";
	char *inf = NULL;
	int tamBuf = 0;
	int status = get_prog_info(prog, param, &inf, tamBuf);
	fail_unless(status != SUCCESS && is_blank(inf),"get_prog_info com tamBuf invalido nao retornou erro");
}
END_TEST

START_TEST(get_prog_info_with_invalid_prog)
{
	char *prog = "programa inexistente";//"eu_S2_LDC";
	char *param = "--version | grep gcc";
	char *inf = NULL;
	int tamBuf = 150;
	int status = get_prog_info(prog, param, &inf, tamBuf);
	fail_unless(status != SUCCESS && strcmp(inf, UNDEFINED_INFO) == 0,"get_prog_info com prog invalido nao retornou erro");
}
END_TEST

START_TEST(get_prog_info_with_invalid_param)
{
	char *prog = "gcc";
	char *param = "--parametro-invalido";//"--eu-S2-LDC";
	char *inf = NULL;
	int tamBuf = 50;
	int status = get_prog_info(prog, param, &inf, tamBuf);
	fail_unless(status != SUCCESS && strcmp(inf, UNDEFINED_INFO) == 0,"get_prog_info com param invalido nao retornou erro");
}
END_TEST

 /*****************************************
  *                                       *
  *    TESTES PARA A FUNÇÃO ADD_VENDOR    *
  *                                       *
  *****************************************/
START_TEST(add_vendor_ok)
{
	struct device *dev = new_device("teste");
	int o = add_vendor(dev);
	fail_unless(o == SUCCESS && dev != NULL && dev->info != NULL, "add_vendor apresenta comportamento errado");
}
END_TEST

START_TEST(add_vendor_with_null_device)
{
	struct device *dev = NULL;
	int o = add_vendor(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_vendor com device NULL nao retorna erro");
	
}
END_TEST

 /*************************************************
  *                                               *
  *    TESTES PARA A FUNÇÃO ADD_KERNEL_VERSION    *
  *                                               *
  *************************************************/
START_TEST(add_kernel_version_ok)
{
	struct device *dev = new_device("teste");
	int o = add_kernel_version(dev);
	fail_unless(o == SUCCESS && dev != NULL && dev->info != NULL, "add_kernel_version apresenta comportamento errado");
}
END_TEST

START_TEST(add_kernel_version_with_null_device)
{
	struct device *dev = NULL;
	int o = add_kernel_version(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_kernel_version com device NULL nao retorna erro");
	
}
END_TEST

 /***********************************************
  *                                             *
  *    TESTES PARA A FUNÇÃO ADD_ARCHITECTURE    *
  *                                             *
  ***********************************************/
START_TEST(add_architecture_ok)
{
	struct device *dev = new_device("teste");
	int o = add_architecture(dev);
	fail_unless(o == SUCCESS && dev != NULL && dev->info != NULL, "add_architecture apresenta comportamento errado");
}
END_TEST

START_TEST(add_architecture_with_null_device)
{
	struct device *dev = NULL;
	int o = add_architecture(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_architecture com device NULL nao retorna erro");
	
}
END_TEST

 /*****************************************
  *                                       *
  *    TESTES PARA A FUNÇÃO ADD_DISTRO    *
  *                                       *
  *****************************************/
START_TEST(add_distro_ok)
{
	struct device *dev = new_device("teste");
	int o = add_distro(dev);
	fail_unless(o == SUCCESS && dev != NULL && dev->info != NULL, "add_distro apresenta comportamento errado");
}
END_TEST

START_TEST(add_distro_with_null_device)
{
	struct device *dev = NULL;
	int o = add_distro(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_distro com device NULL nao retorna erro");
	
}
END_TEST

 /*************************************************
  *                                               *
  *    TESTES PARA A FUNÇÃO ADD_NODE_NAME    *
  *                                               *
  *************************************************/
START_TEST(add_node_name_ok)
{
	struct device *dev = new_device("teste");
	int o = add_node_name(dev);
	fail_unless(o == SUCCESS && dev != NULL && dev->info != NULL, "add_node_name apresenta comportamento errado");
}
END_TEST

START_TEST(add_node_name_with_null_device)
{
	struct device *dev = NULL;
	int o = add_node_name(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_node_name com device NULL nao retorna erro");
	
}
END_TEST

 /**********************************************
  *                                            *
  *    TESTES PARA A FUNÇÃO ADD_GCC_VERSION    *
  *                                            *
  **********************************************/
START_TEST(add_gcc_version_ok)
{
	struct device *dev = new_device("teste");
	int o = add_gcc_version(dev);
	fail_unless(o == SUCCESS && dev != NULL && dev->info != NULL, "add_gcc_version apresenta comportamento errado");
}
END_TEST

START_TEST(add_gcc_version_with_null_device)
{
	struct device *dev = NULL;
	int o = add_gcc_version(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_gcc_version com device NULL nao retorna erro");
	
}
END_TEST

/*
 * Cria suite de testes
 */
Suite * kernel_suite(void)
{
	Suite *s = suite_create("LDC-Software");

	/* testes para a função get_info */
	TCase *tc_software_get_info = tcase_create("Software_get_info");
	tcase_add_test(tc_software_get_info, get_info_ok);
	tcase_add_test(tc_software_get_info, get_info_with_null_device);

	/* testes para a função get_prog_info */
	TCase *tc_software_get_prog_info = tcase_create("Software_get_prog_info");
	tcase_add_test(tc_software_get_prog_info, get_prog_info_ok);
	tcase_add_test(tc_software_get_prog_info, get_prog_info_with_null_prog);
	tcase_add_test(tc_software_get_prog_info, get_prog_info_with_null_param);
	tcase_add_test(tc_software_get_prog_info, get_prog_info_with_invalid_tambuf);
	tcase_add_test(tc_software_get_prog_info, get_prog_info_with_invalid_prog);
	tcase_add_test(tc_software_get_prog_info, get_prog_info_with_invalid_param);

	/* testes para a função add_vendor */
	TCase *tc_software_add_vendor = tcase_create("Software_add_vendor");
	tcase_add_test(tc_software_add_vendor, add_vendor_ok);
	tcase_add_test(tc_software_add_vendor, add_vendor_with_null_device);

	/* testes para a função add_kernel_version */
	TCase *tc_software_add_kernel_version = tcase_create("Software_add_kernel_version");
	tcase_add_test(tc_software_add_kernel_version, add_kernel_version_ok);
	tcase_add_test(tc_software_add_kernel_version, add_kernel_version_with_null_device);

	/* testes para a função add_architecture */
	TCase *tc_software_add_architecture = tcase_create("Software_add_architecture");
	tcase_add_test(tc_software_add_architecture, add_architecture_ok);
	tcase_add_test(tc_software_add_architecture, add_architecture_with_null_device);

	/* testes para a função add_distro */
	TCase *tc_software_add_distro = tcase_create("Software_add_distro");
	tcase_add_test(tc_software_add_distro, add_distro_ok);
	tcase_add_test(tc_software_add_distro, add_distro_with_null_device);

	/* testes para a função add_node_name */
	TCase *tc_software_add_node_name = tcase_create("Software_add_node_name");
	tcase_add_test(tc_software_add_node_name, add_node_name_ok);
	tcase_add_test(tc_software_add_node_name, add_node_name_with_null_device);

	/* testes para a função add_gcc_version */
	TCase *tc_software_add_gcc_version = tcase_create("Software_add_gcc_version");
	tcase_add_test(tc_software_add_gcc_version, add_gcc_version_ok);
	tcase_add_test(tc_software_add_gcc_version, add_gcc_version_with_null_device);

	suite_add_tcase(s, tc_software_get_info);
	suite_add_tcase(s, tc_software_get_prog_info);
	suite_add_tcase(s, tc_software_add_vendor);
	suite_add_tcase(s, tc_software_add_kernel_version);
	suite_add_tcase(s, tc_software_add_architecture);
	suite_add_tcase(s, tc_software_add_distro);
	suite_add_tcase(s, tc_software_add_node_name);
	suite_add_tcase(s, tc_software_add_gcc_version);

	return s;
}

int main(void)
{
	int fails = 0;
	Suite *s = kernel_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	fails = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (fails == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
