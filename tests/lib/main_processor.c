#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include <ldc/types.h>
#include <ldc/info.h>
#include <ldc/errors.h>
#include <ldc/terminal.h>
#include <ldc/string.h>

#include <processor/processor.h>
#include <processor/cpu_core.h>
#include <processor/cache.h>
#include <processor/cpuinfo.h>


#define UNKNOWN "Unknown"

void test_function(struct info_tuple *function_get_information(int), int function_cal_count, char *expected_key);

/************************************************ <PROCESSOR TESTS> ***************************************************************/
START_TEST(test_set_processor_device)
{
        struct device* processor = new_device("Processors");
        set_processor_device(processor);
        fail_if(processor == NULL,"get_processor_device() returned NULL");
}
END_TEST

START_TEST (test_get_processor_family)
{
	test_function(&get_processor_family, get_processors_count(),"Family");
}
END_TEST

START_TEST (test_get_processor_version)
{
	test_function(&get_processor_version, get_processors_count(), "Version");
}
END_TEST

START_TEST (test_get_processor_socket_designation)
{
	test_function(&get_processor_socket_designation, get_processors_count(), "Socket Designation");	
}
END_TEST

START_TEST (test_get_processor_manufacturer)
{
	test_function(&get_processor_manufacturer, get_processors_count(), "Vendor");
}
END_TEST

START_TEST (test_get_processor_id)
{
	test_function(&get_processor_id, get_processors_count(), "ID");
}
END_TEST

START_TEST (test_get_processor_voltage)
{
	test_function(&get_processor_voltage, get_processors_count(), "Voltage");
}
END_TEST

START_TEST (test_get_processor_external_clock)
{
	test_function(&get_processor_external_clock, get_processors_count(), "External Clock");
}
END_TEST

START_TEST (test_get_processor_l1_cache_handle)
{
	int processors_count = get_processors_count();
	int i;
	for (i = -2; i < processors_count; i++) {
		char *handle = get_processor_l1_cache_handle(i);
		int is_valid = (handle != NULL &&
				(strcmp(handle,UNDEFINED_INFO) == 0 || 
				strcmp(handle, UNEXISTENT_DEPENDENCE) == 0 ||
				strcmp(handle,"Not Provided") == 0 ||
				strncmp(handle,"0x0XXX", 3) == 0));		
		fail_unless(is_valid, "get_processor_l1_cache_handle(%d) returned a invalid value (%s)", i, handle);
		delete(&handle);
	}
}
END_TEST

START_TEST (test_get_processor_l2_cache_handle)
{
	int processors_count = get_processors_count();
	int i;
	for (i = -2; i < processors_count; i++) {
		char *handle = get_processor_l2_cache_handle(i);
		int is_valid = (handle != NULL &&
				(strcmp(handle,UNDEFINED_INFO) == 0 || 
				strcmp(handle, UNEXISTENT_DEPENDENCE) == 0 || 
				strcmp(handle,"Not Provided") == 0 ||
				strncmp(handle,"0x0XXX", 3) == 0));		
		fail_unless(is_valid, "get_processor_l1_cache_handle(%d) returned a invalid value (%s)", i, handle);
		delete(&handle);	
	}
}
END_TEST

START_TEST (test_get_processor_l3_cache_handle)
{
	int processors_count = get_processors_count();
	int i;
	for (i = -2; i < processors_count; i++) {
		char *handle = get_processor_l3_cache_handle(i);
		int is_valid = (handle != NULL &&
				(strcmp(handle,UNDEFINED_INFO) == 0 || 
				strcmp(handle, UNEXISTENT_DEPENDENCE) == 0 || 
				strcmp(handle,"Not Provided") == 0 ||
				strncmp(handle,"0x0XXX", 3) == 0));		
		fail_unless(is_valid, "get_processor_l3_cache_handle(%d) returned a invalid value (%s)", i, handle);
		delete(&handle);	
	}
}
END_TEST

/************************************************ </PROCESSOR TESTS> ***************************************************************/


/************************************************ <CACHE TESTS> ***************************************************************/

START_TEST (test_get_cache)
{
	int caches_count = get_caches_count();
	int i;
	for (i = 0; i < caches_count; i++) {
		struct device *cache = get_cache(i);
		fail_unless(cache != NULL, "get_cache(%d) returned NULL", i);
		
		char expected_name[10];
		sprintf(expected_name, "Cache %d", i);
		fail_unless(strcmp(cache->name, expected_name) == 0, "get_cache(%d) returned a device with unexpected name (%s)", i, cache->name);
		free_device(&cache);	
	}
	struct device *null = get_cache(-1);
	fail_unless(null == NULL, "get_cache(-1) returned a device not NULL");
}
END_TEST

START_TEST (test_get_cache_handle)
{
	test_function(&get_cache_handle, get_caches_count(), "Handle");
}
END_TEST

START_TEST(test_get_cache_socket_designation)
{
	test_function(&get_cache_socket_designation, get_caches_count(), "Socket Designation");//External Cache
}
END_TEST

START_TEST(test_get_cache_configuration)
{
	test_function(&get_cache_configuration, get_caches_count(), "Configuration");//Enabled, Not Socketed, Level 1
}
END_TEST

START_TEST(test_get_cache_operational_mode)
{
	test_function(&get_cache_operational_mode, get_caches_count(), "Operational Mode");
}
END_TEST

START_TEST(test_get_cache_location)
{
	test_function(&get_cache_location, get_caches_count(), "Location");
}
END_TEST

START_TEST(test_get_cache_installed_size)
{
	test_function(&get_cache_installed_size, get_caches_count(), "Installed Size"); //Maximum Size: 64 KB
}
END_TEST

START_TEST(test_get_cache_maximum_size)
{
	test_function(&get_cache_maximum_size, get_caches_count(), "Maximum Size"); //Maximum Size: 64 KB
}
END_TEST

/*
START_TEST(test_get_cache_supported_sram_types)
{
	char *expected_values[] = {"Synchronous", "Synchronous"};
	//generic_test_iteractive_information(&get_cache_supported_sram_types, get_total_caches(), expected_values, "Supported SRAM Types");
}
END_TEST
*/

START_TEST(test_get_cache_installed_sram_type)
{
	test_function(&get_cache_installed_sram_type, get_caches_count(), "Installed SRAM Type");
}
END_TEST

START_TEST(test_get_cache_speed)
{
	test_function(&get_cache_speed, get_caches_count(), "Speed");
}
END_TEST

START_TEST(test_get_cache_error_correction_type)
{
	test_function(&get_cache_error_correction_type, get_caches_count(), "Error Correction Type");
}
END_TEST

START_TEST(test_get_cache_system_type)
{
	test_function(&get_cache_system_type, get_caches_count(), "System Type");
}
END_TEST

START_TEST(test_get_cache_associativity)
{
	test_function(&get_cache_associativity, get_caches_count(), "Associativity");
}
END_TEST


START_TEST (test_get_cache_handle_value)
{
	int caches_count = get_caches_count();
	int i;
	for (i = -2; i < caches_count; i++) {
		char *handle = get_cache_handle_value(i);
		int is_valid = (handle != NULL &&
				(strcmp(handle,UNDEFINED_INFO) == 0 || 
				strcmp(handle, UNEXISTENT_DEPENDENCE) == 0 || 
				strcmp(handle,"Not Provided") == 0 ||
				strncmp(handle,"0x0XXX", 3) == 0));		
		fail_unless(is_valid, "get_processor_l3_cache_handle(%d) returned a invalid value (%s)", i, handle);
		delete(&handle);
	}
}
END_TEST

START_TEST (has_cache_handle_true)
{
	struct device *cache = new_device("cache test");
	struct info_tuple *info1 = new_info_tuple("dsa", "not");
	struct info_tuple *info2 = new_info_tuple("Handle", "ACHOU");
	add_info(cache, info1);
	add_info(cache, info2);
	fail_unless(has_cache_handle("ACHOU", cache) == 1, "didn't find, but should.");
}
END_TEST

START_TEST (has_cache_handle_false)
{
	struct device *cache = new_device("cache test");
	struct info_tuple *info1 = new_info_tuple("dsa", "ACHOU");
	struct info_tuple *info2 = new_info_tuple("Handle", "123");
	add_info(cache, info1);
	add_info(cache, info2);
	fail_unless(has_cache_handle("ACHOU", cache) == 0, "did find, but shouldn't.");
}
END_TEST

START_TEST (has_cache_handle_false2)
{
	struct device *cache = new_device("cache test");
	struct info_tuple *info = new_info_tuple("dsa", "ACHOU");
	add_info(cache, info);
	fail_unless(has_cache_handle("ACHOU", cache) == 0, "did find, but shouldn't.");
}
END_TEST

START_TEST (test_get_caches_count)
	fail_unless(get_caches_count() >= 0, "get_total_caches() returned a invalid value");
END_TEST


/************************************************ <\CACHE TESTS> ***************************************************************/
/************************************************ <CORE TESTS>  ****************************************************************/

START_TEST (test_get_core_vendor_id)
{
	int cores_count = get_cores_count();
	fail_unless(cores_count > 0, "get_cores_count() didn't proveid a number of cores valid for get_core_vendor_id");
	test_function(&get_core_vendor_id, cores_count, "Vendor ID");
}
END_TEST

START_TEST (test_get_core_cpu_mhz)
{
	test_function(&get_core_cpu_mhz, get_cores_count(), "Cpu Mhz");
}
END_TEST

START_TEST (test_get_core_physical_id)
{
	test_function(&get_core_physical_id, get_cores_count(), "Physical ID");
}
END_TEST

START_TEST (test_get_core_id)
{
	int cores_count = get_cores_count();
	fail_unless(cores_count > 0, "get_cores_count() didn't provide a number of cores valid for get_core_id");
	test_function(&get_core_id, cores_count, "Core ID");
}
END_TEST

START_TEST (test_get_cpu_cores_count)
{
	test_function(&get_cpu_cores_count, get_cores_count(), "Cpu Cores");	
}
END_TEST

START_TEST (test_get_core_features)
{
	int total_cores = get_cores_count();
	fail_unless(total_cores != 0, "get_processor_cores_number didn't provide a number of cores valid for features");
	test_function(&get_core_features, total_cores, "Features");
}
END_TEST

START_TEST (test_core_get_physical_id_value)
{
	int i;
	int cores_count = get_cores_count();
	for (i = 0; i < cores_count; i++) {
		char *temp = get_core_physical_id_value(i);
		fail_unless(temp != NULL, "get_core_physical_id_value(%d) returned a NULL value", i);
		delete(&temp);
	}
}
END_TEST

START_TEST (test_get_cores_count)
{
	int cores_count = get_cores_count();
	fail_unless(cores_count > 0, "get_cores_count() returned (%d)", cores_count);
}
END_TEST

START_TEST (test_has_physical_id_true)
{
	struct device *core = new_device("core test");
	struct info_tuple *info1 = new_info_tuple("dsa", "not");
	struct info_tuple *info2 = new_info_tuple("Physical ID", "ACHOU");
	add_info(core, info1);
	add_info(core, info2);
	fail_unless(has_physical_id("ACHOU", core) == 1, "didn't find, but should.");
}
END_TEST

START_TEST (test_has_physical_id_false_1)
{
	struct device *core = new_device("core test");
	struct info_tuple *info1 = new_info_tuple("dsa", "not");
	struct info_tuple *info2 = new_info_tuple("Physical ID", "SIM");
	add_info(core, info1);
	add_info(core, info2);
	fail_unless(has_physical_id("NAO", core) == 0, "found. but shouldn't.");
}
END_TEST

START_TEST (test_has_physical_id_false_2)
{
	struct device *core = new_device("core test");
	struct info_tuple *info1 = new_info_tuple("dsa", "not");
	add_info(core, info1);
	fail_unless(has_physical_id("ANY", core) == 0, "found. but shouldn't.");
}
END_TEST


START_TEST (test_get_physical_id_uniq_count)
{
	int physical_id_uniq_count = get_physical_id_uniq_count();
	fail_unless(physical_id_uniq_count >= 0, "get_physical_id_uniq_count() returend (%d)", physical_id_uniq_count);
}
END_TEST

START_TEST (test_get_physical_id_uniq)
{
	int physical_id_uniq_count = get_physical_id_uniq_count();
	int i;
	for (i = 0; i < physical_id_uniq_count; i++) {
		char *temp = get_physical_id_uniq(i);
		fail_unless(temp != NULL, "get_physical_id_uniq_count(%d) returned a NULL value", i);
		delete(&temp);
	}
}
END_TEST

/**************************************************************** </CORE TESTS> ***************************************************************/
/**************************************************************** <CPU_INFO TESTS> ***************************************************************/

START_TEST (test_get_cpu_info_output_ok)
{
	char *output = get_cpu_info_output("processor", 1, 3);
	fail_unless(output != NULL, "get_cpu_info_output() returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_null_filter)
{
	char *filter = NULL;
	char *output = get_cpu_info_output(filter, 1, 3);
	fail_unless(output != NULL, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_inexistent_filter)
{
	char *output= get_cpu_info_output("inexistent", 1, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output() with and inexistent filter returned a invalid value");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_negative_line)
{
	char *filter = "processor";
	char *output = get_cpu_info_output(filter, -1, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a (%s) value, but shouldn't.", output);
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_line_zero)
{
	char *filter = "processor";
	char *output = get_cpu_info_output(filter, 0, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_inexistent_line)
{
	char *filter = "processor";
	char *output = get_cpu_info_output(filter, 100, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_negative_begin)
{
	char *filter = "processor";
	char *output = get_cpu_info_output(filter, 1, -3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_begin_zero)
{
	char *filter = "processor";
	char *output = get_cpu_info_output(filter, 1, 0);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_inexistent_begin)
{
	char *filter = "processor";
	char *output = get_cpu_info_output(filter, 1, 100);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output() returned (%s) value, but shouldn't.", output);
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_ok)
{
	char *output = get_cpu_info_output_uniq("processor", 1, 3);
	fail_unless(output != NULL, "get_cpu_info_output() returned a NULL value, but shouldn't.");
	delete(&output);
	
	output = get_cpu_info_output_uniq("processor", get_cores_count() + 1, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output() returned %s value, but shouldn't.", output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_null_filter)
{
	char *filter = NULL;
	char *output = get_cpu_info_output_uniq(filter, 1, 3);
	fail_unless(output != NULL, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_inexistent_filter)
{
	char *output= get_cpu_info_output_uniq("inexistent", 1, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output() with and inexistent filter returned a invalid value");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_negative_line)
{
	char *filter = "processor";
	char *output = get_cpu_info_output_uniq(filter, -1, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_line_zero)
{
	char *filter = "processor";
	char *output = get_cpu_info_output_uniq(filter, 0, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_inexistent_line)
{
	char *filter = "processor";
	char *output = get_cpu_info_output_uniq(filter, 100, 3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_negative_begin)
{
	char *filter = "processor";
	char *output = get_cpu_info_output_uniq(filter, 1, -3);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_begin_zero)
{
	char *filter = "processor";
	char *output = get_cpu_info_output_uniq(filter, 1, 0);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output(NULL ...) returned a NULL value, but shouldn't.");
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_inexistent_begin)
{
	char *filter = "processor";
	char *output = get_cpu_info_output_uniq(filter, 1, 100);
	fail_unless(output != NULL && strcmp(output, UNDEFINED_INFO) == 0, "get_cpu_info_output() returned a (%s) value, but shouldn't.",output);
	delete(&output);
}
END_TEST

START_TEST (test_get_cpu_info_output_count_ok)
{
	int cores_count = get_cpu_info_output_count("processor");
	fail_unless(cores_count > 0, "get_cpu_info_output(\"processor\") returned (%d)", cores_count);
}
END_TEST

START_TEST (test_get_cpu_info_output_count_null_filter)
{
	char *filter = NULL;
	int out = get_cpu_info_output_count(filter);
	fail_unless(out == 0, "get_cpu_info_output(NULL) returned (%d)", out);
}
END_TEST

START_TEST (test_get_cpu_info_output_count_inexistent_filter)
{
	char *filter = "inexistent";
	int out = get_cpu_info_output_count(filter);
	fail_unless(out == 0, "get_cpu_info_output(inexistent) returned (%d)", out);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_count_ok)
{
	int cores_count = get_cpu_info_output_uniq_count("processor");
	fail_unless(cores_count > 0, "get_cpu_info_output(\"processor\") returned (%d)", cores_count);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_count_null_filter)
{
	char *filter = NULL;
	int out = get_cpu_info_output_uniq_count(filter);
	fail_unless(out == 0, "get_cpu_info_output(NULL) returned (%d)", out);
}
END_TEST

START_TEST (test_get_cpu_info_output_uniq_count_inexistent_filter)
{
	char *filter = "inexistent";
	int out = get_cpu_info_output_uniq_count(filter);
	fail_unless(out == 0, "get_cpu_info_output(inexistent) returned (%d)", out);
}
END_TEST

/**************************************************************** </CPU_INFO TESTS> ***************************************************************/


Suite * processor_suite(void)
{
        Suite *s = suite_create("LDC_Processor");
        
	TCase *tc_proc = tcase_create("processor information");
  	TCase *tc_cache = tcase_create("cache information");
	TCase *tc_core = tcase_create("core information");
	TCase *tc_cpuinfo = tcase_create("cpuinfo information");

	tcase_add_test(tc_proc, test_set_processor_device);
	tcase_add_test(tc_proc, test_get_processor_family);
	tcase_add_test(tc_proc, test_get_processor_version);
	tcase_add_test(tc_proc, test_get_processor_socket_designation);
	tcase_add_test(tc_proc, test_get_processor_manufacturer);
	tcase_add_test(tc_proc, test_get_processor_id);
	tcase_add_test(tc_proc, test_get_processor_voltage);
	tcase_add_test(tc_proc, test_get_processor_external_clock);
	tcase_add_test(tc_proc, test_get_processor_l1_cache_handle);
	tcase_add_test(tc_proc, test_get_processor_l2_cache_handle);
	tcase_add_test(tc_proc, test_get_processor_l3_cache_handle);

	tcase_add_test(tc_cache, test_get_cache);
	tcase_add_test(tc_cache, test_get_cache_handle);
	tcase_add_test(tc_cache, test_get_cache_socket_designation);
	tcase_add_test(tc_cache, test_get_cache_configuration);
	tcase_add_test(tc_cache, test_get_cache_operational_mode);
	tcase_add_test(tc_cache, test_get_cache_location);
	tcase_add_test(tc_cache, test_get_cache_installed_size);
	tcase_add_test(tc_cache, test_get_cache_maximum_size);
	tcase_add_test(tc_cache, test_get_cache_installed_sram_type);
	tcase_add_test(tc_cache, test_get_cache_speed);
	tcase_add_test(tc_cache, test_get_cache_error_correction_type);
	tcase_add_test(tc_cache, test_get_cache_system_type);
	tcase_add_test(tc_cache, test_get_cache_associativity);
	tcase_add_test(tc_cache, test_get_cache_handle_value);
	tcase_add_test(tc_cache, has_cache_handle_true);
	tcase_add_test(tc_cache, has_cache_handle_false);
	tcase_add_test(tc_cache, has_cache_handle_false2);
	tcase_add_test(tc_cache, test_get_caches_count);

	tcase_add_test(tc_core, test_get_core_vendor_id);
	tcase_add_test(tc_core, test_get_core_cpu_mhz);
	tcase_add_test(tc_core, test_get_core_physical_id);
	tcase_add_test(tc_core, test_get_core_id);
	tcase_add_test(tc_core, test_get_cpu_cores_count);
	tcase_add_test(tc_core, test_get_core_features);
	tcase_add_test(tc_core, test_core_get_physical_id_value);
	tcase_add_test(tc_core, test_get_cores_count);
	tcase_add_test(tc_core, test_has_physical_id_true);
	tcase_add_test(tc_core, test_has_physical_id_false_1);
	tcase_add_test(tc_core, test_has_physical_id_false_2);
	tcase_add_test(tc_core, test_get_physical_id_uniq_count);
	tcase_add_test(tc_core, test_get_physical_id_uniq);

	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_ok);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_null_filter);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_inexistent_filter);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_negative_line);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_line_zero);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_inexistent_line);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_negative_begin);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_begin_zero);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_inexistent_begin);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_ok);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_null_filter);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_inexistent_filter);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_negative_line);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_line_zero);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_inexistent_line);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_negative_begin);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_begin_zero);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_inexistent_begin);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_count_ok);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_count_null_filter);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_count_inexistent_filter);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_count_ok);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_count_null_filter);
	tcase_add_test(tc_cpuinfo, test_get_cpu_info_output_uniq_count_inexistent_filter);

        suite_add_tcase(s, tc_proc);
	suite_add_tcase(s, tc_cache);        
	suite_add_tcase(s, tc_core);
	suite_add_tcase(s, tc_cpuinfo);

        return s;
}

int main(void)
{
        int number_failed;
	Suite *s = processor_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);

        return (number_failed == 0) ?
        EXIT_SUCCESS : EXIT_FAILURE;
}

/****************************************************** < FUNÇÕES AUXILIARES> ****************************************************/


void test_function(struct info_tuple *function_get_information(int), int function_call_count, char *expected_key)
{
	int i = 0;
	while (i < function_call_count) {
		struct info_tuple *temp = function_get_information(i);
		fail_unless(temp != NULL);
		fail_unless(get_info_tuple_value(temp) != NULL);
		//fail_unless(strcmp(get_info_tuple_key(temp), expected_key) == 0, "%s != %s", get_info_tuple_key(temp), expected_key);
		free_info_tuple(&temp);
		i++;
	}
}

