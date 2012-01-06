#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <check.h>

#include <ldc/system.h>
#include <ldc/terminal.h>
#include <ldc/string.h>
#include <ldc/types.h>
#include <ldc/errors.h>
#include <harddisk/harddisk.h>
#include <harddisk/hd_string.h>

/* variáveis globais usadas nos testes */
struct device *hd;
struct device *part;

 /**********************************************
  *                                            *
  *    TESTES PARA A FUNÇÃO FORMAT_MEGABYTE    *
  *                                            *
  **********************************************/
START_TEST(format_with_0m)
{
	long long int megabytes = 0;
	char *e = "0MB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lli) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

START_TEST(format_with_1m)
{
	long long int megabytes = 1;
	char *e = "1MB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lli) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

START_TEST(format_with_1024m)
{
	long long int megabytes = 1024;
	char *e = "1024MB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lli) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

START_TEST(format_with_1025m)
{
	long long int megabytes = 1025;
	char *e = "1GB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lli) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

START_TEST(format_with_2047m)
{
	long long int megabytes = 2047;
	char *e = "1GB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lli) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

START_TEST(format_with_2048m)
{
	long long int megabytes = 2048;
	char *e = "2GB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lld) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

START_TEST(format_with_1024g)
{
	long long int megabytes = 1048576;
	char *e = "1024GB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lli) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

START_TEST(format_with_1025g)
{
	long long int megabytes = 1049600;
	char *e = "1TB";
	char *f = format_megabyte(megabytes);
	fail_unless(strcmp(f,e) == 0, "format_megabyte(%lli) returned \"%s\"; expected \"%s\"", megabytes, f, e);
}
END_TEST

 /******************************
  *                            *
  *    TESTES PARA GET_INFO    *
  *                            *
  ******************************/
START_TEST(get_info_ok)
{
	struct device *dev = new_device("get_info_hard_disks");
	int o = get_info(dev);
	fail_unless(dev != NULL && o == SUCCESS, "get_info(device(\"get_info_hard_disks\")) failed");
}
END_TEST

START_TEST(get_info_with_null_device)
{
	struct device *dev = NULL;
	int o = get_info(dev);
	fail_unless(dev == NULL && o != SUCCESS, "get_info(NULL) failed");
}
END_TEST

 /******************************************
  *                                        *
  *    TESTES PARA ADD_DEVICE_MAIN_INFO    *
  *                                        *
  ******************************************/
START_TEST(add_device_main_info_ok)
{
	struct device *dev = hd;
	int o = add_device_main_info(dev);
	fail_unless(o == SUCCESS && dev != NULL, "add_device_main_info returned a failure value");
}
END_TEST

START_TEST(add_device_main_info_with_null_device)
{
	struct device *dev = NULL;
	int o = add_device_main_info(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_device_main_info with null device returned %d; expected %d", o, ERROR);
}
END_TEST

 /******************************************
  *                                        *
  *    TESTES PARA ADD_DEVICE_SIZE_INFO    *
  *                                        *
  ******************************************/
START_TEST(add_device_size_info_ok)
{
	struct device *dev = hd;
	int o = add_device_size_info(dev);
	fail_unless(o == SUCCESS && dev != NULL, "add_device_size_info returned a failure value");
}
END_TEST

START_TEST(add_device_size_info_with_null_device)
{
	struct device *dev = NULL;
	int o = add_device_size_info(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_device_size_info with null device returned %d; expected %d", o, ERROR);
}
END_TEST

 /***********************************
  *                                 *
  *    TESTES PARA ADD_PART_INFO    *
  *                                 *
  ***********************************/
START_TEST(add_part_info_ok)
{
	struct device *dev = hd;
	int o = add_part_info(dev);
	fail_unless(o == SUCCESS && dev != NULL, "add_part_info returned a failure value");
}
END_TEST

START_TEST(add_part_info_with_null_device)
{
	struct device *dev = NULL;
	int o = add_part_info(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_part_info with null device returned %d; expected %d", o, ERROR);
}
END_TEST

 /************************************
  *                                  *
  *    TESTES PARA ADD_PART_FLAGS    *
  *                                  *
  ************************************/
START_TEST(add_part_flags_ok)
{
	struct device *dev = part;
	int o = add_part_flags(dev);
	fail_unless(o == SUCCESS && dev != NULL, "add_part_flags returned a failure value");
}
END_TEST

START_TEST(add_part_flags_with_null_device)
{
	struct device *dev = NULL;
	int o = add_part_flags(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_part_flags with null device returned %d; expected %d", o, ERROR);
}
END_TEST

 /***********************************
  *                                 *
  *    TESTES PARA ADD_GEOM_INFO    *
  *                                 *
  ***********************************/
START_TEST(add_geom_info_ok)
{
	struct device *dev = part;
	int o = add_geom_info(dev);
	fail_unless(o == SUCCESS && dev != NULL, "add_geom_info returned a failure value");
}
END_TEST

START_TEST(add_geom_info_with_null_device)
{
	struct device *dev = NULL;
	int o = add_geom_info(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_geom_info with null device returned %d; expected %d", o, ERROR);
}
END_TEST

 /**********************************
  *                                *
  *    TESTES PARA ADD_DF_INFO    *
  *                                *
  **********************************/
START_TEST(add_df_info_ok)
{
	struct device *dev = part;
	int o = add_df_info(dev);
	fail_unless(o == SUCCESS && dev != NULL, "add_df_info returned a failure value");
}
END_TEST

START_TEST(add_df_info_with_null_device)
{
	struct device *dev = NULL;
	int o = add_df_info(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_df_info with null device returned %d; expected %d", o, ERROR);
}
END_TEST

 /******************************************
  *                                        *
  *    TESTES PARA ADD_FILE_SYSTEM_INFO    *
  *                                        *
  ******************************************/
START_TEST(add_file_system_info_ok)
{
	struct device *dev = part;
	int o = add_file_system_info(dev);
	fail_unless(o == SUCCESS && dev != NULL, "add_file_system_info returned a failure value");
}
END_TEST

START_TEST(add_file_system_info_with_null_device)
{
	struct device *dev = NULL;
	int o = add_file_system_info(dev);
	fail_unless(o != SUCCESS && dev == NULL, "add_file_system_info with null device returned %d; expected %d", o, ERROR);
}
END_TEST

/* cria suite de testes */
Suite * hd_suite(void)
{
	Suite *s = suite_create("LDC_HD");

	/* testes para a format_megabyte */
	TCase *tc_hd_format = tcase_create("HD_format");
	tcase_add_test(tc_hd_format, format_with_0m);
	tcase_add_test(tc_hd_format, format_with_1m);
	tcase_add_test(tc_hd_format, format_with_1024m);
	tcase_add_test(tc_hd_format, format_with_1025m);
	tcase_add_test(tc_hd_format, format_with_2047m);
	tcase_add_test(tc_hd_format, format_with_2048m);
	tcase_add_test(tc_hd_format, format_with_1024g);
	tcase_add_test(tc_hd_format, format_with_1025g);

	/* testes para a função get_info */
	TCase *tc_hd_get_info = tcase_create("HD_get_info");
	tcase_add_test(tc_hd_get_info, get_info_ok);
	tcase_add_test(tc_hd_get_info, get_info_with_null_device);


	/* testes para a função add_device_main_info */
	TCase *tc_hd_add_device_main_info = tcase_create("HD_add_device_main_info");
	tcase_add_test(tc_hd_add_device_main_info, add_device_main_info_ok);
	tcase_add_test(tc_hd_add_device_main_info, add_device_main_info_with_null_device);


	/* testes para a função add_device_size_info */
	TCase *tc_hd_add_device_size_info = tcase_create("HD_add_device_size_info");
	tcase_add_test(tc_hd_add_device_size_info, add_device_size_info_ok);
	tcase_add_test(tc_hd_add_device_size_info, add_device_size_info_with_null_device);


	/* testes para a função add_part_info */
	TCase *tc_hd_add_part_info = tcase_create("HD_add_part_info");
	tcase_add_test(tc_hd_add_part_info, add_part_info_ok);
	tcase_add_test(tc_hd_add_part_info, add_part_info_with_null_device);


	/* testes para a função add_part_flags */
	TCase *tc_hd_add_part_flags = tcase_create("HD_add_part_flags");
	tcase_add_test(tc_hd_add_part_flags, add_part_flags_ok);
	tcase_add_test(tc_hd_add_part_flags, add_part_flags_with_null_device);


	/* testes para a função add_geom_info */
	TCase *tc_hd_add_geom_info = tcase_create("HD_add_geom_info");
	tcase_add_test(tc_hd_add_geom_info, add_geom_info_ok);
	tcase_add_test(tc_hd_add_geom_info, add_geom_info_with_null_device);


	/* testes para a função add_df_info */
	TCase *tc_hd_add_df_info = tcase_create("HD_add_df_info");
	tcase_add_test(tc_hd_add_df_info, add_df_info_ok);
	tcase_add_test(tc_hd_add_df_info, add_df_info_with_null_device);


	/* testes para a função add_file_system_info */
	TCase *tc_hd_add_file_system_info = tcase_create("HD_add_file_system_info");
	tcase_add_test(tc_hd_add_file_system_info, add_file_system_info_ok);
	tcase_add_test(tc_hd_add_file_system_info, add_file_system_info_with_null_device);


	suite_add_tcase(s, tc_hd_format);
	suite_add_tcase(s, tc_hd_get_info);
	suite_add_tcase(s, tc_hd_add_device_main_info);
	suite_add_tcase(s, tc_hd_add_device_size_info);
	suite_add_tcase(s, tc_hd_add_part_info);
	suite_add_tcase(s, tc_hd_add_part_flags);
	suite_add_tcase(s, tc_hd_add_geom_info);
	suite_add_tcase(s, tc_hd_add_df_info);
	suite_add_tcase(s, tc_hd_add_file_system_info);

	return s;
}

int main(void)
{
	if (!is_root()) {
		printf("Root privileges needed to get the hard disk info.\n");
		return EXIT_SUCCESS;
	}

	char *df = which("df");
	char *fdisk = which("fdisk");
	char *cmd = NULL;
	char *path = NULL;

	cmd = calloc(55, sizeof(char));
	sprintf(cmd, "%s -l | grep /dev/ | awk '{print $%d}'", fdisk, 2);
	path = get_cmd_output(cmd, 12);
	path = strip_end(path, ":");
	hd = new_device(path);
	delete(&cmd);
	delete(&path);

	cmd = calloc(45, sizeof(char));
	sprintf(cmd, "%s -P | awk '{print $%d}' | grep %s", df, 1, hd->name);
	path = get_cmd_output(cmd, 13);
	part = new_device(path);
	delete(&cmd);
	delete(&path);

	int fails = 0;
	Suite *s = hd_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	fails = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (fails == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

