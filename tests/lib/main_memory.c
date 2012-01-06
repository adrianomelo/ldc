#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include <ldc/types.h>
#include <ldc/info.h>
#include <ldc/errors.h>
#include <ldc/terminal.h>
#include <ldc/system.h>

#include <memory/memory.h>

#define UNKNOWN "Unknown"


void generic_test_size(struct info_tuple * temp, char *key);
void generic_test_information(struct info_tuple *function_get_information(void), int expected_values_count, char *expected_value[], char *expected_key);
void test_function(struct info_tuple *function_get_information(int), int function_call_count, char *expected_values[], int expected_values_count, char *expected_key);

START_TEST(test_set_memory_device_ok)
{
        struct device* memory = new_device("Memory");
        set_memory(memory);
        fail_if(memory == NULL,"set_memory_device() returned NULL");
//	print_device(memory); DOESNT EXIST ANYMORE

}
END_TEST

START_TEST(test_set_memory_null_device)
{
	struct device *null_device = NULL;
	set_memory(null_device);
	fail_if(null_device != NULL, "set_memory_device(NULL) did something, but shouldn't");
}
END_TEST

START_TEST(test_get_maximum_memory_module_size)
{
	char *expected_values[] = {"1024 MB"," 2048 MB"};
	generic_test_information(&get_maximum_memory_module_size, 2, expected_values, "Maximum Module Size");
}
END_TEST

START_TEST(test_get_maximum_memory_total_size)
{
	char *expected_values[] = {"4096 MB", "8192 MB"};
	generic_test_information(&get_maximum_memory_total_size, 2, expected_values, "Maximum Total Size");
}
END_TEST

START_TEST(test_get_memory_module_voltage)
{
	char *expected_values[] = {"5.0 V"};
	generic_test_information(&get_memory_module_voltage, 1, expected_values, "Voltage");
}
END_TEST

START_TEST(test_get_associated_memory_slots_number)
{
	char *expected_values[] = {"4"};
	generic_test_information(&get_associated_memory_slots_number, 1, expected_values, "Slots");
}
END_TEST


//TODO ADICIONAR O TESTE ABAIXO E RESOLVER O BUG
START_TEST(test_get_memory_device_manufacturer)
{
	char *expected_values[] = {UNDEFINED_INFO, "Intel", "Intel(R) Corporation", "Samsung"};
	test_function(&get_memory_device_manufacturer, get_total_memory_physical_devices(), expected_values, 4, "Vendor");
}
END_TEST

START_TEST(test_get_memory_device_factor)
{
	char *expected_values[] = {"DIMM"};
	test_function(&get_memory_device_factor, get_total_memory_physical_devices(), expected_values, 1, "Factor");
}
END_TEST

START_TEST(test_get_memory_device_type)
{
	char *expected_values[] = {"Unknown"};
	test_function(&get_memory_device_type, get_total_memory_physical_devices(),expected_values, 1, "Type");
}
END_TEST

START_TEST(test_get_memory_device_type_detail)
{
	char *expected_values[] = {"Synchronous"};
	test_function(&get_memory_device_type_detail, get_total_memory_physical_devices(), expected_values, 1, "Type Detail");
}
END_TEST

START_TEST(test_get_memory_device_size)
{
	char *expected_values[] = {"2048 MB", "No Module Installed"};
	test_function(&get_memory_device_size, get_total_memory_physical_devices(), expected_values, 2, "Size");
}
END_TEST

START_TEST(test_get_memory_device_serial)
{
	char *expected_values[] = {"can't know for sure"};
	test_function(&get_memory_device_serial, get_total_memory_physical_devices(), expected_values, 1, "Serial Number");
}
END_TEST

START_TEST(test_get_memory_device_speed)
{
	char *expected_values[] = {"800 MHz (1.2 ns)", "Unknown"};
	test_function(&get_memory_device_speed, get_total_memory_physical_devices(), expected_values, 2, "Speed");
}
END_TEST

START_TEST(test_get_total_memory_physical_devices)
{
	int modules = get_total_memory_physical_devices();
	fail_unless((is_root() && has_dependence("dmidecode") ? modules >= 0 : modules == 0), "get_total_memory_modules() returned a invalid number: %d",modules);
}
END_TEST

/****** <GENERAL>******
START_TEST(test_get_memory_total)
{
	generic_test_size(get_memory_total(), "Memory Total");
}
END_TEST

START_TEST(test_get_memory_free)
{
	generic_test_size(get_memory_free(), "Memory Free");
}
END_TEST

START_TEST(test_get_memory_buffers)
{
	generic_test_size(get_memory_buffers(), "Memory Buffers");
}
END_TEST

START_TEST(test_get_memory_cached)
{
	generic_test_size(get_memory_cached(), "Memory Cached");
}
END_TEST
****** <GENERAL> *******/

Suite * memory_suite(void)
{
        Suite *s = suite_create("LDC_Memory");
        TCase *tc_core = tcase_create("memory-tcase");

        tcase_add_test(tc_core, test_set_memory_device_ok);
	tcase_add_test(tc_core, test_set_memory_null_device);

        tcase_add_test(tc_core, test_get_maximum_memory_module_size); 
        tcase_add_test(tc_core, test_get_maximum_memory_total_size); 
        tcase_add_test(tc_core, test_get_memory_module_voltage); 
        tcase_add_test(tc_core, test_get_associated_memory_slots_number);

	tcase_add_test(tc_core, test_get_memory_device_manufacturer);
        tcase_add_test(tc_core, test_get_memory_device_factor);
        tcase_add_test(tc_core, test_get_memory_device_type);
	tcase_add_test(tc_core, test_get_memory_device_type_detail);
	tcase_add_test(tc_core, test_get_memory_device_size);
	tcase_add_test(tc_core, test_get_memory_device_serial);
        tcase_add_test(tc_core, test_get_memory_device_speed);
        tcase_add_test(tc_core, test_get_total_memory_physical_devices);
/*
	tcase_add_test(tc_core, test_get_memory_total);
	tcase_add_test(tc_core, test_get_memory_free);
	tcase_add_test(tc_core, test_get_memory_buffers);
	tcase_add_test(tc_core, test_get_memory_cached);
*/
        suite_add_tcase(s, tc_core);
        return s;
}

int main(void)
{
        int number_failed;

        Suite *s = memory_suite();
        SRunner *sr = srunner_create(s);
        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);

        return (number_failed == 0) ?
        EXIT_SUCCESS : EXIT_FAILURE;
}

void generic_test_size(struct info_tuple * temp, char *key) {
	fail_unless(temp != NULL, "function returned a NULL pointer.");
//	fail_unless(strcmp(get_info_tuple_key(temp), key) == 0,"function returned key %s != %s (expected)",get_info_tuple_key(temp), key);
	fail_unless(get_info_tuple_value(temp) != NULL, "function returned a NULL value");
	char *value = get_info_tuple_value(temp);
	int size = strlen(value);
	if((value[size - 1] == 'B' || value[size - 1] == 'b') && (value [size - 2] == 'k' || value [size - 2] == 'K' || value [size - 2] == 'M' || value[size - 2] == 'G')) {
		char num[size - 2];		
		strncpy(num, value, (size - 3));
		num[size - 3] = '\0';
		int val = atoi(num);
		fail_unless(val >= 0, "invalid format");

	} else if(strcmp(value, UNDEFINED_INFO) != 0 && strcmp(value, UNEXISTENT_DEPENDENCE) != 0) {
		fail("invalid format");
	}
}


void generic_test_information(struct info_tuple *function_get_information(void), int expected_values_count, char *expected_values[], char *expected_key) {	
	struct info_tuple *temp = function_get_information();
	fail_unless(temp != NULL, "this function returned a null info_tuple");
	fail_unless(get_info_tuple_value(temp) != NULL, "this function returned a null value");	
//	fail_unless(strcmp(get_info_tuple_key(temp), expected_key) == 0, "Memory Key %s != %s (expected)", get_info_tuple_key(temp), expected_key);        
	free_info_tuple(&temp);
}

void test_function(struct info_tuple *function_get_information(int), int function_call_count, char *expected_values[], int expected_values_count, char *expected_key)
{
	int i = 0;
	while (i < function_call_count) {
		struct info_tuple *temp = function_get_information(i);
		fail_unless(temp != NULL);
		fail_unless(get_info_tuple_value(temp) != NULL);
//		fail_unless(strcmp(get_info_tuple_key(temp), expected_key) == 0);
		free_info_tuple(&temp);
		i++;
	}
}



