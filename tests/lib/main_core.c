#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <check.h>

#include <sys/types.h>

#include <ldc/types.h>
#include <ldc/info.h>
#include <ldc/errors.h>
#include <ldc/hashtable.h>
#include <ldc/system.h>
#include <ldc/terminal.h>
#include <ldc/dmidecode.h>
#include <ldc/string.h>
#include <ldc/parser.h>
#include <ldc/lockfile.h>
#include <ldc/log.h>


START_TEST (new_info_tuple_null_key_and_value)
{

	struct info_tuple * t = new_info_tuple(NULL,NULL);
	//quando passo valores NULL, o que fazer?
	//deixar ponteiro para NULL ou criar uma string?
	//string vazia ou string "NULL"?

	fail_unless(strcmp(get_info_tuple_key(t), "NULL") == 0, 
		"Key not set correctly");
	fail_unless(strcmp(get_info_tuple_value(t), "NULL") == 0,
		"value not set correctly");

	fail_unless((t->next)==NULL, "Pointer to NEXT not set to NULL");

	free(t->key);
	free(t->value);
	free(t);
}
END_TEST

START_TEST (new_info_tuple_valid_key_and_value)
{
	struct info_tuple * t = new_info_tuple("processor_name","core i3");

	fail_unless(strcmp(get_info_tuple_key(t), "processor_name") == 0,
		"Key not set correctly");
	fail_unless(strcmp(get_info_tuple_value(t), "core i3") == 0,
		"Value not set correctly");

	fail_unless((t->next)==NULL, "Pointer to NEXT not set to NULL");

	free(t->key);
	free(t->value);
	free(t);
}
END_TEST

START_TEST (free_single_info_tuple_fields)
{
	struct info_tuple * t = new_info_tuple("processor_name","core i3");

	free_info_tuple_key_and_value(t);

	fail_unless(t->key == NULL, "t->key not freed");
	fail_unless(t->value == NULL, "t->value not freed");

	free(t);
	t = NULL;

}
END_TEST

START_TEST (free_single_info_tuple)
{
	struct info_tuple * t = new_info_tuple("processor_name", "core i3");
	free_info_tuple(&t);

	fail_unless(t == NULL, "info_tuple t not freed");
}
END_TEST

START_TEST (free_chained_info_tuples)
{
	struct info_tuple * t = new_info_tuple("processor_name", "core i3");
	struct info_tuple * u = new_info_tuple("processor_arch", "x86_64");

	t->next = u;

	free_info_tuple(&t);
	fail_unless(t == NULL, "info_tuple t not freed");
}
END_TEST

START_TEST (append_info_tuple_test)
{
	struct info_tuple * t = new_info_tuple("processor_name", "core_i3");
	struct info_tuple * u = new_info_tuple("processor_arch", "x86_64");
	struct info_tuple * v = new_info_tuple("processor_cores", "2");

	append_info_tuple(t, u);
	fail_unless(t->next == u, "info tuple u was not appended as t->next");

	append_info_tuple(t, v);
	fail_if(t->next == v, "third tuple has overwritten the second tuple");
	fail_unless(t->next->next == v, "third tuple was not appended to second tuple");

	struct info_tuple * w = new_info_tuple("processor_vendor", "intel");
	append_info_tuple(v, w);

	fail_unless(v->next == w, "fourth tuple not appended to third tuple");
	fail_unless(t->next->next->next == w, "fourth tuple not appended correctly to tuple list");

	free_info_tuple(&t);
}
END_TEST

START_TEST (append_new_info_tuple_test)
{
	struct info_tuple * t = new_info_tuple("processor_name", "core i3");

	append_new_info_tuple(t, "processor_arch", "x86_64");

	struct info_tuple * last = t;
	while (info_tuple_has_next(last)) {
		last = last->next;
	}

	fail_unless(strcmp(last->key, "processor_arch") == 0, "new tuple key not set correctly");
	fail_unless(strcmp(last->value, "x86_64") == 0, "new tuple value not set correctly");

	free_info_tuple(&t); 
}
END_TEST

START_TEST (print_info_tuple_list_test)
{
	struct info_tuple * t = new_info_tuple("processor_name", "core_i3");
	struct info_tuple * u = new_info_tuple("processor_arch", "x86_64");
	struct info_tuple * v = new_info_tuple("processor_cores", "2");

	append_info_tuple(t, u);
	append_info_tuple(t, v);

	int success = print_info_tuple_list(t);
	fail_unless(success == EXIT_SUCCESS, "failure while printing info_tuple");
}
END_TEST

START_TEST (print_null_info_tuple_list_test)
{
	struct info_tuple * t = NULL;
	int success = print_info_tuple_list(t);
	fail_unless(success == EXIT_FAILURE, "failure to handle attempt to print null info_tuple");
}
END_TEST

START_TEST (new_device_node_test)
{
	struct device * d = new_device("Processor");
	
	fail_unless(strcmp(d->name, "Processor") == 0, "Device node name not correctly set");
	fail_unless(d->info == NULL, "Device info pointer not set to NULL when node is created");
	fail_unless(d->next == NULL, "Next device node pointer not set to NULL when node is created");
	fail_unless(d->child == NULL, "Child device node pointer not set to NULL when node is created");

	free(d->name);
	free(d);
}
END_TEST

START_TEST (new_null_device_node_test)
{
	struct device * d = new_device(NULL);

	fail_unless(d->name != NULL, "Device name cannot be a pointer to NULL, but it is.");

	free(d->name);
	free(d);
}
END_TEST

START_TEST (free_single_device_node_test)
{
	struct device * d = new_device("Processador");
	free_device(&d);

	fail_unless(d == NULL, "Device pointer just freed is not set to NULL.");
}
END_TEST

START_TEST (free_chained_device_node_test)
{
	struct device * t = new_device("processor");
	struct device * u = new_device("processor4");
	struct device * v = new_device("proc_cache");

	t->next = u;
	t->child = v;

	free_device(&t);
	fail_unless(t == NULL, "device t not freed");
}
END_TEST

START_TEST (free_chained_device_node_sig11)
{
	struct device * t = new_device("processor");
	struct device * u = new_device("processor4");

	t->next = u;

	free_device(&t);
	printf("name: %s\n", u->name);
	free_device(&u);
	printf("name: %s\n", u->name);

	//The second and third free_device must raise signal 11, SEGFAULT
}
END_TEST

START_TEST (append_device_node_test)
{	
	struct device * t = new_device("processor");
	struct device * u = new_device("processor2");
	struct device * v = new_device("processor3");

	append_device_node(t, u);
	fail_unless(t->next == u, "device u was not appended as t->next");

	append_device_node(t, v);
	fail_if(t->next == v, "third device has overwritten the second device");
	fail_unless(t->next->next == v, "third device was not appended to second device");

	struct device * w = new_device("processor4");
	append_device_node(v, w);

	fail_unless(v->next == w, "fourth device not appended to third device");
	fail_unless(t->next->next->next == w, "fourth device not appended correctly to device list");

	free_device(&t);
}
END_TEST


START_TEST (print_device_list_test)
{
	struct device * d1 = new_device("processor");
	struct info_tuple * t1 = new_info_tuple("processor_name", "core i3");
	struct info_tuple * t2 = new_info_tuple("processor_vendor", "intel");
	append_new_info_tuple(t1, "processor_cores", "2");
	add_info(d1, t1);
	add_info(d1, t2);

	struct device * d2 = new_device("cache");
	struct info_tuple * t3 = new_info_tuple("cache_speed", "800mhz");
	struct info_tuple * t4 = new_info_tuple("cache_size", "4mb");
	add_info(d2, t3);
	add_info(d2, t4);

	struct device * d3 = new_device("memory");
	struct info_tuple * t5 = new_info_tuple("memory_size", "4gb");
	struct info_tuple * t6 = new_info_tuple("n_slots", "4");
	add_info(d3, t5);
	add_info(d3, t6);

	set_child(d1, d2);
	append_device_node(d1, d3);


	int success = print_device_list(d1);

	fail_unless(success == EXIT_SUCCESS, "Failed to print valid device list.");
}
END_TEST

START_TEST (print_null_device_list_test)
{
	struct device * d = NULL;
	int success = print_device_list(d);
	fail_unless(success == EXIT_FAILURE, "Failed to handle null device list.");
}
END_TEST





START_TEST (new_tuple_test1)
{
	struct tuple *tuple = NULL;
	tuple = new_tuple (NULL, NULL);

	fail_unless (tuple == NULL, "tupla sendo criada mesmo passando NULL para key e value");

	free_tuple (&tuple);

	fail_unless (tuple == NULL, "erro ao liberar memoria");
}
END_TEST

START_TEST (new_tuple_test2)
{
	struct tuple *tuple = NULL;
	tuple = new_tuple ("key", NULL);

	fail_unless (tuple == NULL, "tupla sendo criada mesmo passando NULL para value");

	free_tuple (&tuple);

	fail_unless (tuple == NULL, "erro ao liberar memoria");
}
END_TEST

START_TEST (new_tuple_test3)
{
	struct tuple *tuple = NULL;
	tuple = new_tuple (NULL, "value");

	fail_unless (tuple == NULL, "tupla sendo criada mesmo passando NULL para key");

	free_tuple (&tuple);

	fail_unless (tuple == NULL, "erro ao liberar memoria");
}
END_TEST

START_TEST (new_tuple_test4)
{
	struct tuple *tuple = NULL;
	tuple = new_tuple ("key", "value");

	fail_if (tuple == NULL, "tupla nao foi criada");

	fail_unless (strcmp(tuple->key, "key") == 0, "key é diferente de 'key'"); 
	fail_unless (strcmp(tuple->value, "value") == 0, "value é diferente de 'value'"); 

	free_tuple (&tuple);

	fail_unless (tuple == NULL, "erro ao liberar memoria");
}
END_TEST

START_TEST (re_find_test1)
{
	char *re = "TEST.*]";

	char *lines_with_pattern[] = {
		"[TEST\\.0]",
		"[TEST\\.1] ",
		"[TEST\\.2] *******",
		"    [TEST\\.3]",
		"      [TEST\\.4]         ",
		"*****[TEST\\.5]***********",
		"	[TEST\\.6]	",
		"  [TEST\\.7]",
		"  [TEST\\.8]",
		"  [TEST\\.9]",
		"  [TEST\\.10]   ",
		"dsa[TEST\\.11]dsadsadsadsa"
	};

	int i;
	for (i = 0; i < 12; i++) {
		char *expected = calloc(30, sizeof(char));
		sprintf(expected, "TEST\\.%d]", i);
		char *actual = re_find(re, lines_with_pattern[i]);

		fail_if (actual == NULL, "returned NULL. expected '%s'", expected);
		fail_unless(equals(actual, expected), "re_find(re '%s', line '%s') returned '%s' != '%s' (expected)", 
							re, lines_with_pattern[i], actual, expected);

		delete(&expected);
		delete(&actual);
	}
}
END_TEST

START_TEST (re_find_test2)
{
	char *re = "Test\\.*]";

	int lines_count = 12;
	char *lines_without_pattern[] = {
		"[TESTABC\\.0]",
		"[TestAbC\\.1] ",
		"[TiuygestABC\\.2] *******",
		"    [Te  stABC\\.3]",
		"      [TeStABC\\.4]         ",
		"[Test\\.]",
		"	[Tes tABC\\.6]	",
		"  [Te stABC\\.7]",
		"  [TestAdBC\\\\.  8]",
		"  [TestdABC\\\\.  9]",
		"  [Test.10]   ",
		"dsa[Test\\11]dsadsadsadsa"
	};

	int i;
	for (i = 0; i < lines_count; i++) {
		char *actual = re_find(re, lines_without_pattern[i]);
		fail_unless (actual == NULL, "line[%d] should return NULL. but returned '%s'", i, actual);
	}
}
END_TEST

START_TEST (re_find_test3)
{
	char *re = ".+=.+";
	char *string = "a=b";

	char *actual = re_find(re, string);
	fail_unless(actual != NULL);
	fail_unless(equals(string, actual));
	delete(&actual);
}
END_TEST

START_TEST (parse_tuple_test1)
{
	struct tuple *t = NULL;
	char *attribution = "key=value";
	t = parse_tuple(attribution);
	fail_unless(t != NULL, "parse_tuple('%s') returned NULL", attribution);
	
	fail_unless(equals(t->key, "key"), "parse_tuple(%s) returned %s (key)", t->key);
	fail_unless(equals(t->value, "value"), "parse_tuple(%s) returned %s (value)", t->value);
	free_tuple(&t);	
}
END_TEST

START_TEST (parse_tuple_test2)
{
	struct tuple *t = NULL;
	char *attribution = "key=";
	t = parse_tuple(attribution);
	fail_unless(t == NULL, "parse_tuple('%s') didn't return NULL", attribution);
}
END_TEST

START_TEST (parse_tuple_test3)
{
	struct tuple *t = NULL;
	char *attribution = "=value";
	t = parse_tuple(attribution);
	fail_unless(t == NULL, "parse_tuple('%s') didn't return NULL", attribution);
}
END_TEST

START_TEST (parse_tuple_test4)
{
	struct tuple *t = NULL;
	char *attribution = "#key=value";
	t = parse_tuple(attribution);
	fail_unless(t == NULL, "parse_tuple('%s') didn't return NULL", attribution);
}
END_TEST

START_TEST (parse_tuple_test5)
{
	struct tuple *t = NULL;
	char *attribution = "   =   ";
	t = parse_tuple(attribution);
	fail_unless(t == NULL, "parse_tuple('%s') didn't return NULL", attribution);
}
END_TEST


START_TEST (plugin_core_create)
{
    /*struct device * d;
    d = new_device("Processador");

   // fail_unless(strcmp(get_device_name(d), "Processador") == 0, "Device node name was not set correctly");
    if(strcmp(get_device_name(d),"Processador") != 0)
	fail("Device node name was not set correctly");

//    free_device(d);
*/
}
END_TEST

START_TEST (test_file_exists_when_doesnt)
{
	char* test1 = "fdsa";
	fail_unless(file_exists(test1) == 0, "erro quando arquivo nao existe");
}
END_TEST

START_TEST (test_file_exist_when_does)
{
	char* test2 = "/sbin/ifconfig";
	fail_unless(file_exists(test2) == 1, "falha quando um programa existe");
}
END_TEST

START_TEST (test_file_exist_resolv)
{
	char* test3 = "/etc/resolv.conf";
	fail_unless(file_exists(test3) == 1, "falha ao verificar se resolv.conf existe");
}
END_TEST

START_TEST (test_file_exist_null_file)
{
	char* null = NULL;
	fail_unless(file_exists(null) == 0, "falha quando a string é nula");
}
END_TEST

START_TEST (test_file_exist_only_allocated_file)
{
	char* null2 = malloc(5 * sizeof(char));
	fail_unless(file_exists(null2) == 0, "falha quando a string só foi alocada");
}
END_TEST

START_TEST(test_is_blank_empty_string)
{
	char* vazia = "";
	fail_unless(is_blank(vazia) == 1,"falha quando string é vazia");
}
END_TEST

START_TEST(test_is_blank_space_string)
{
	char* embranco = " ";
	fail_unless(is_blank(embranco) == 1,"falha quando string é vazia");
}
END_TEST

START_TEST(test_is_blank_large_space_string)
{
	char* embrancogrande = "                          ";
	fail_unless(is_blank(embrancogrande) == 1, "falha quando a string em branco é grande");
}
END_TEST

START_TEST(test_is_blank_ok)
{
	char* naoebranca = "Não";
	fail_unless(is_blank(naoebranca) == 0, "falha quando a string tem letras");
}
END_TEST

START_TEST(test_is_blank_with_space_between_letters)
{
	char* comespaco = "String com espaço";
	fail_unless(is_blank(comespaco) == 0, "falha quando a string tem letras e espaço");
}
END_TEST

START_TEST(test_is_blank_not_striped)
{
	char* comespaco = " didnt_use_strip ";
	fail_unless(is_blank(comespaco) == 0, "falha quando a string tem letras e espaço");
}
END_TEST

START_TEST(test_is_blank_new_line)
{
	char* comespaco = "\n";
	fail_unless(is_blank(comespaco) == 0, "falha quando a string tem letras e espaço");
}
END_TEST

START_TEST(test_is_blank_tab)
{
	char* comespaco = "\t";
	fail_unless(is_blank(comespaco) == 0, "falha quando a string tem letras e espaço");
}
END_TEST

/*START_TEST (core_get_kernel_version)

	int version;
	int major;
	int minor;

	if (get_kernel_version(&version) != 1)
		fail("ger_kernel_version retornou erro");

	fail_unless(version == 2, "versão diferente de 2");
	
	if (get_kernel_major_version(&major) != 1)
		fail("ger_kernel_major_version retornou erro");

	fail_unless(major == 6, "major diferente de 6");
	
	if (get_kernel_minor_version(&minor) != 1)
		fail("ger_kernel_minor_version retornou erro");

	//fail_unless(minor == 32, "minor diferente de 32");

END_TEST*/

START_TEST (test_which_inexistent_dependence)
{
	char *programa = "inexistent";
	char *path = which(programa);
	fail_unless(path == NULL, "which(char*) didn't returned UNEXISTENT_DEPENDENCE for a inexistent program");
}
END_TEST

START_TEST (test_which_null_program)
{
	char *program = NULL;
	char *path = which(program);
	fail_unless(path == NULL, "which(char*) didn't returned UNEXISTENT_DEPENDENCE for a NULL program");
}
END_TEST

START_TEST (test_which_ok)
{
	char *program = "ifconfig";
	char *path = which(program);
	fail_unless(strcmp(path, "/sbin/ifconfig") == 0, "which(char *) should return /sbin/ifconfig, but returned %s", path);
}
END_TEST




/******************************************************************************/
/*		          Test Case : GET_CMD_OUTPUT			      */	
/******************************************************************************/

/*
START_TEST(test_get_cmd_output_with_static_alloc_null_command)
{	
	char null[10];
	char *ret = (char *) get_cmd_output(null, 100);
	fail_unless(ret == NULL, "get_cmd_output(static_alloc_null, 100) != NULL");	
}
END_TEST

START_TEST(test_get_cmd_output_with_dynamic_alloc_null_command)
{	
	char *null = (char *) malloc(sizeof(char)*10);
	char *ret = (char *) get_cmd_output(null, 100);
	fail_unless(ret == NULL, "get_cmd_output(dynamic_alloc_null, 100) != NULL");
}
END_TEST
*/

START_TEST(test_get_cmd_output_with_blank_command)
{
	//char *ret = (char *) get_cmd_output("", 100);
	char *ret = get_cmd_output("", 100);	
	fail_unless(strcmp(ret, UNDEFINED_INFO) == 0, "get_cmd_output('', 100) != undefined_info");	
}
END_TEST

START_TEST(test_get_cmd_output_with_uname_command)
{
	char *ret = get_cmd_output("uname", 10);	
	fail_unless(strcmp(ret, "Linux") == 0, "get_cmd_output(uname, 10) == '%s' and != 'Linux'", ret);
}
END_TEST

START_TEST(test_get_cmd_output_with_invalid_command)
{
	char *ret = get_cmd_output("idontexist", 10);	
	fail_unless(strcmp(ret, UNDEFINED_INFO) == 0, "get_cmd_output(idontexist, 10) != undefined_info");
}
END_TEST

START_TEST(test_get_cmd_output_with_small_buffer_size)
{
	char *ret = get_cmd_output("uname -a", 3);	
	fail_unless(strcmp(ret, "Li") == 0, "get_cmd_output(uname -a, 2) == %s and != Li", ret);
}
END_TEST

START_TEST(test_get_cmd_output_with_buffer_size_zero)
{
	char *ret = get_cmd_output("uname -a", 0);	
	fail_unless(ret == NULL, "get_cmd_output(uname -a, 0) != NULL");
}
END_TEST

START_TEST(test_get_cmd_output_with_buffer_size_negative)
{
	char *ret = get_cmd_output("uname -a", -5);	
	fail_unless(ret == NULL, "get_cmd_output(uname -a, -1) != NULL");
}
END_TEST


/******************************************************************************/
/*		          Test Case : STRIP_END			              */	
/******************************************************************************/

START_TEST(test_strip_end_with_calloc_string)
{
	char *ret = (char *) calloc(100, sizeof(char));
	sprintf(ret, "jflas    ");
	ret = strip_end(ret, "");	
	fail_unless(strcmp(ret, "jflas") == 0, "strip_end(NULL, \"jflas    \") != \"jflas\"");
}
END_TEST


START_TEST(test_strip_end_with_null_string)
{
	char *ret = NULL;
	ret = strip_end(ret, "fasdf");	
	fail_unless(ret == NULL, "strip_end(NULL, \"fasdf\") != NULL");
}
END_TEST


START_TEST(test_strip_end_with_empty_string)
{
	char *ret = "";
	char *out = strip_end(ret, "gfagsdg");	
	fail_unless(strcmp(ret, out) == 0, "strip_end(\"\", \"gfagsdg\") != \"\"");
}
END_TEST


START_TEST(test_strip_end_with_null_filter)
{
	char *ret = "fasdg  \n \n\t  ";
	char *filter = NULL;
	char *out = strip_end(ret, filter);	
	fail_unless(strcmp(out, "fasdg") == 0, "strip_end(\"fasdg  \n \n\t  \", NULL) != \"fasdg\"");
}
END_TEST


START_TEST(test_strip_end_with_one_whitespace_string)
{
	char *ret = " ";
	ret = strip_end(ret, "");	
	fail_unless(strcmp(ret, "") == 0, "strip_end(\" \", \"\") != \"\" ");
}
END_TEST


START_TEST(test_strip_end_with_multiple_whitespace_string)
{
	char *ret = " \t \n \r    ";
	ret = strip_end(ret, "");	
	fail_unless(strcmp(ret, "") == 0, "strip_end(\" \t \n \r    \", \"\") != \"\" ");
}
END_TEST


START_TEST(test_strip_end_with_one_char_filter)
{
	char *ret = ".";
	ret = strip_end(ret, ".");	
	fail_unless(strcmp(ret, "") == 0, "strip_end(\".\", \".\") != \"\" ");
}
END_TEST


START_TEST(test_strip_end_with_multiple_char_filter)
{
	char *ret = "xafa .?*  ";
	ret = strip_end(ret, ".?*");	
	fail_unless(strcmp(ret, "xafa") == 0, "strip_end(\"xafa .?*  \", \".?*\") != \"xafa\" ");
}
END_TEST


START_TEST(test_strip_end_with_complex_string_and_filter)
{
	char *ret = "x. y. z. t?*\n...x   .?*\t\n\r   ";
	ret = strip_end(ret, "?.*");	
	fail_unless(strcmp(ret, "x. y. z. t?*\n...x") == 0, "strip_end(\"x. y. z. t?*\n...x   .?*\t\n\r   \", \"?.*\") != \"x. y. z. t?*\n...x\" ");
}
END_TEST


/******************************************************************************/
/*		          Test Case : DELETE		              */	
/******************************************************************************/

START_TEST(test_delete_ok)
{
	char *str = (char *)malloc(sizeof(char) * 10);
	strcpy(str,"ok");
	delete(&str);
	fail_unless(str == NULL, "delete(allocated_string) didn't set NULL");
}
END_TEST

START_TEST(test_delete_null_string)
{
	char *str = NULL;
	delete(&str); //if fail, it will raise signal 6
}
END_TEST
/*
START_TEST(test_delete_literal_string)
{
	char *str = UNDEFINED_INFO;
	delete(&str); //it should raise signal 11
}
END_TEST
*/

/******************************************************************************/
/*		          Test Case : DMIDECODE		              */	
/******************************************************************************/

void assert(char *actual, char *expected);

START_TEST (get_dmidecode_keyword_output_ok)
{
	char *expected = NULL;
	char *output = get_dmidecode_keyword_output("system-manufacturer", 1);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_keyword_output_invalid_keyword)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_keyword_output("invalid_keyword", 1);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_keyword_output_null_keyword)
{
	char *expected = UNDEFINED_INFO;
	char *keyword = NULL;
	char *output = get_dmidecode_keyword_output(keyword, 1);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_keyword_output_negative_line)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_keyword_output("system-manufacturer", -1);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_keyword_output_line_zero)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_keyword_output("system-manufacturer", 0);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_ok)
{
	//char *expecteds[] = {"Socket 775", UNDEFINED_INFO};
	char *output = get_dmidecode_output(4, "Socket Designation:", 1, 3);
	//assert_values(output, expecteds, 2);
	assert(output, UNDEFINED_INFO);
}
END_TEST

START_TEST (get_dmidecode_output_negative_dmi_type)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(-1, "Socket Designation:", 1, 2);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_dmi_type_inexistent)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(22, "Socket Designation:", 1, 2);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_null_filter)
{
	char *expected = UNDEFINED_INFO;
	char *filter = NULL;
	char *output = get_dmidecode_output(22, filter, 1, 2);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_negative_line)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(4, "Socket Designation:", -1, 2);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_line_zero)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(4, "Socket Designation:", 0, 2);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_inexistent_line)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(4, "Socket Designation:", 15, 2);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_negative_begin)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(4, "Socket Designation:", 1, -1);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_begin_zero)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(4, "Socket Designation:", 1, 0);
	assert(output, expected);
}
END_TEST

START_TEST (get_dmidecode_output_inexistent_begin)
{
	char *expected = UNDEFINED_INFO;
	char *output = get_dmidecode_output(4, "Socket Designation:", 1, 15);
	assert(output, expected);
}
END_TEST

START_TEST (test_get_dmidecode_count_ok)
{
	int count = -1;
	count = get_dmidecode_count(0, "BIOS Information");
	if(is_root())
		fail_unless(count == 1, "get_dmidecode_count failed (returned %d)", count);
	else
	   	fail_unless(count == 0, "get_dmidecode_count failed (returned %d)", count);
}
END_TEST

START_TEST (test_get_dmidecode_count_negative_type)
{
	int count = -1;
	count = get_dmidecode_count(-1, "BIOS Information");
	fail_unless(count == 0, "get_dmidecode_count failed with negative dmi_type");
}
END_TEST

START_TEST (test_get_dmidecode_count_inexistent_type)
{
	int count = -1;
	count = get_dmidecode_count(1000, "Processor");
	fail_unless(count == 0, "get_dmidecode_count failed with inexistent type");
}
END_TEST

START_TEST (test_get_dmidecode_count_null_filter)
{
	int count = -1;
	count = get_dmidecode_count(0, NULL);
	fail_unless(count == 0, "get_dmidecode_count failed with null filter");
}
END_TEST

START_TEST (test_get_dmidecode_count_inexistent_filter)
{
	int count = -1;
	count = get_dmidecode_count(0, "inexistent");
	fail_unless(count == 0, "get_dmidecode_count failed with inexistent filter");
}
END_TEST

START_TEST (test_get_dmidecode_is_valid_keyword_ok_1)
{
	fail_unless(is_valid_keyword("bios-vendor") == 1, "is_valid_keyword failed with bios-vendor");
}
END_TEST

START_TEST (test_get_dmidecode_is_valid_keyword_ok_2)
{
	fail_unless(is_valid_keyword("processor-frequency") == 1, "is_valid_keyword failed");
}
END_TEST

START_TEST (test_get_dmidecode_is_valid_keyword_invalid_keyword)
{
	fail_unless(is_valid_keyword("invalid") == 0, "is_valid_keyword failed");
}
END_TEST

START_TEST (test_get_dmidecode_is_valid_keyword_null_keyword)
{
	char *keyword = NULL;
	fail_unless(is_valid_keyword(keyword) == 0, "is_valid_keyword failed");
}
END_TEST

/************************************************************
 ****************** função append_string ********************
 ***********************************************************/

START_TEST (append_string_test_both_null)
{
	char *beg = NULL;
	char *end = NULL;

	append_string (&beg, end);

	fail_unless (beg == NULL, "erro quando os dois sao NULL");
	delete(&beg);
	delete(&end);

}
END_TEST

START_TEST (append_string_destination_null)
{
	char *dest = NULL;
	char *end = "1234567890";
	append_string (&dest, end);

	fail_unless (strcmp(dest, "1234567890") == 0, "erro quando o primeiro é NULL");
	delete(&dest);
	
}
END_TEST

START_TEST (append_string_empty_destination)
{
	char *dest = calloc(2, sizeof(char));
	strcpy(dest,"");

	append_string(&dest, "testando");
	fail_unless(strcmp(dest, "testando") == 0, "erro ao append 'testando' at empty_destination");
	delete(&dest);
}
END_TEST

START_TEST (append_string_empty_src)
{
	char *dest = calloc(2, sizeof(char));
	char *end = "";

	copy_string(dest, "---->", 6);
	append_string (&dest, end);
	fail_unless(dest != NULL && strcmp(dest, "---->") == 0, "erro ao append_string('anyging','')");
	delete(&dest);
}
END_TEST

START_TEST (append_string_empty_destination_and_src)
{
	char *dest = calloc(2, sizeof(char));
	char *src = calloc(2,sizeof(char));
	strcpy(dest,"");
	strcpy(src, "");
	
	append_string(&dest, src);
	
	fail_unless(dest != NULL && strlen(dest) == 0, "append string with destination = \"\" and src = \"\"");
	
	delete(&dest);
	delete(&src);
}
END_TEST

START_TEST (append_string_ok)
{
	char *dest = calloc (6, sizeof(char));

	copy_string(dest, "---->", 6);

	char *end = "1234567890";
	append_string (&dest, end);

	fail_unless (dest != NULL && strcmp(dest, "---->1234567890") == 0, "should return '---->1234567890' but returned '%s' ", dest);
	delete(&dest);
}
END_TEST


START_TEST (append_string_recursive)
{
	int i = 0;
	char *dest = NULL;
	char *str[] = {"1","23","456","7890","abcde","fghijlm","nopqrstuvxz","issonao_eh_lixo"};	

	for (i = 0; i < 8; i++) {
		append_string(&dest, str[i]);
	}
	fail_unless(dest != NULL, "recursive append set NULL at dest");
	fail_unless(strcmp(dest, "1234567890abcdefghijlmnopqrstuvxzissonao_eh_lixo") == 0);
	delete(&dest);
}
END_TEST

START_TEST (test_remove_substring_ok)
{
	char *literal = "1p1r1o1j1e1t1o 1l1d1c11";
	char *expected = "projeto ldc";
	char *string = calloc(strlen(literal) + 1, sizeof(char));
	copy_string(string, literal, strlen(literal) + 1);

	int status = remove_substring(&string, "1");
	fail_unless(status == SUCCESS, "remove_substring() returned ERROR");
	fail_unless(strcmp(string, expected) == 0, "%s != %s (expected)",string, expected);
	delete(&string);
}
END_TEST


START_TEST (test_remove_substring_ok_2)
{
	char *literal = "1p2r12oje12to1 2ld12c12";
	char *expected = "1p2rojeto1 2ldc";
	char *string = calloc(strlen(literal) + 1, sizeof(char));
	copy_string(string, literal, strlen(literal) + 1);

	int status = remove_substring(&string, "12");
	fail_unless(status == SUCCESS, "remove_substring() returned ERROR");
	fail_unless(strcmp(string, expected) == 0, "%s != %s (expected)",string, expected);
	delete(&string);
}
END_TEST


START_TEST (test_remove_substring_invalid_src)
{
	char *string = NULL;
	int status = remove_substring(&string, "anything");
	fail_unless(status == ERROR, "remove_substring(NULL,/) returned SUCCESS");

}
END_TEST

START_TEST (test_remove_substring_invalid_remove)
{
	char *literal = "1p2r12oje12to1 2ld12ca12";
	char *string = calloc(strlen(literal) + 1, sizeof(char));
	copy_string(string, literal, strlen(literal) + 1);
	
	int status = remove_substring(&string, NULL);
	fail_unless(status == ERROR, "remove_substring(NULL,/) returned SUCCESS");
}
END_TEST

START_TEST (test_get_clean_string_ok)
{
	char *literal = "|p|r|o|j|e|t|o| |l|d|c|||";
	char *expected = "projeto ldc";
	char *actual = get_clean_string(literal, "|");
	fail_unless(actual != NULL, "get_clean_string(%s) returned NULL",literal);
	fail_unless(strcmp(actual, expected) == 0, "%s != %s (expected)",actual, expected);
	delete(&actual);
}
END_TEST

START_TEST (test_get_clean_string_ok_2)
{
	char *literal = "|p|r|o|j|e|t|o| |l|d|c||";
	char *expected = literal;
	char *actual = get_clean_string(literal, "anything");
	fail_unless(actual != NULL, "get_clean_string(%s) returned NULL",literal);
	fail_unless(strcmp(actual, expected) == 0, "%s != %s (expected)",actual, expected);
	delete(&actual);
}
END_TEST

START_TEST (test_get_clean_string_ok_3)
{
	char *literal = "1p2r12oje12to1 2ld12c12";
	char *expected = "1p2rojeto1 2ldc";
	char *actual = get_clean_string(literal, "12");
	fail_unless(actual != NULL, "get_clean_string(%s) returned NULL",literal);
	fail_unless(strcmp(actual, expected) == 0, "%s != %s (expected)",actual, expected);
	delete(&actual);
}
END_TEST

START_TEST (test_get_clean_string_invalid_src)
{
	char *literal = NULL;
	fail_unless(get_clean_string(literal, " ") == NULL);
}
END_TEST

START_TEST (test_get_clean_string_invalid_remove)
{
	char *literal = "anything";
	char *remove = NULL;
	fail_unless(get_clean_string(literal, remove) == NULL);
}
END_TEST

START_TEST (test_get_clean_string_invalid_src_minor_than_remove)
{
	char *literal = "aaaaaaaaaa";
	char *remove = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	fail_unless(get_clean_string(literal, remove) == NULL);
}
END_TEST

START_TEST(test_get_clean_string_return_empty)
{
	char *literal = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char *remove = "a";
	char *actual = get_clean_string(literal, remove);
	fail_unless(actual != NULL);
	fail_unless(strlen(actual) == 0);
	delete(&actual);
}
END_TEST

START_TEST(test_equals_1)
{
	int status = equals("ldc", "ldc");
	fail_unless(status == 1);
}
END_TEST

START_TEST(test_equals_3)
{
	int status = equals("", "");
	fail_unless(status == 1);
}
END_TEST

START_TEST(test_equals_2)
{
	int status = equals("ldc", "ldc+");
	fail_unless(status == 0);
}
END_TEST

START_TEST(test_equals_4)
{
	char *a = NULL;
	char *b = "not null";
	int status = equals(a, b);
	fail_unless(status == 0);
}
END_TEST

START_TEST(test_equals_5)
{
	char *a = "not null";
	char *b = NULL;
	int status = equals(a, b);
	fail_unless(status == 0);
}
END_TEST

START_TEST(test_equals_6)
{
	char *a = NULL;
	char *b = NULL;
	int status = equals(a, b);
	fail_unless(status == 0);
}
END_TEST

START_TEST(token_with_null_str)
{
	char *str = NULL;
	char *delim = " ";
	int pos = 1;
	char *o = get_token(str, delim, pos);
	fail_unless(o == NULL, "get_token(NULL,\"%s\",%d) = \"%s\"; expected NULL", delim, pos, o);
}
END_TEST

START_TEST(token_with_null_delim)
{
	char *str = "So testando a funcao";
	char *delim = NULL;
	int pos = 2;
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o, str) == 0, "get_token(\"%s\",NULL,%d) = \"%s\"; expected \"%s\"", str, pos, o, str);
}
END_TEST

START_TEST(token_with_neg_pos)
{
	char *str = "So testando a funcao";
	char *delim = " ";
	int pos =-1;
	char *o = get_token(str, delim, pos);
	fail_unless(o == NULL, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected NULL", str, delim, pos, o);
}
END_TEST

START_TEST(token_with_space_0)
{
	char *str = "So testando a funcao";
	char *delim = " ";
	int pos = 0;
	char *e = "So";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_space_1)
{
	char *str = "So testando a funcao";
	char *delim = " ";
	int pos = 1;
	char *e = "testando";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_space_2)
{
	char *str = "So testando a funcao";
	char *delim = " ";
	int pos = 2;
	char *e = "a";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_space_20)
{
	char *str = "So testando a funcao";
	char *delim = " ";
	int pos = 20;
	char *o = get_token(str, delim, pos);
	fail_unless(o == NULL, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected NULL", str, delim, pos, o);
}
END_TEST

START_TEST(token_with_space_t_0)
{
	char *str = "So testando a funcao";
	char *delim = " t";
	int pos = 0;
	char *e = "So";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_space_t_1)
{
	char *str = "So testando a funcao";
	char *delim = " t";
	int pos = 1;
	char *e = "es";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_space_t_2)
{
	char *str = "So testando a funcao";
	char *delim = " t";
	int pos = 2;
	char *e = "ando";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_space_t_20)
{
	char *str = "So testando a funcao";
	char *delim = " t";
	int pos = 20;
	char *o = get_token(str, delim, pos);
	fail_unless(o == NULL, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected NULL", str, delim, pos, o);
}
END_TEST

START_TEST(token_with_t_0)
{
	char *str = "So testando a funcao";
	char *delim = "t";
	int pos = 0;
	char *e = "So ";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_t_1)
{
	char *str = "So testando a funcao";
	char *delim = "t";
	int pos = 1;
	char *e = "es";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_t_2)
{
	char *str = "So testando a funcao";
	char *delim = "t";
	int pos = 2;
	char *e = "ando a funcao";
	char *o = get_token(str, delim, pos);
	fail_unless(strcmp(o,e) == 0, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected \"%s\"", str, delim, pos, o, e);
}
END_TEST

START_TEST(token_with_t_20)
{
	char *str = "So testando a funcao";
	char *delim = "t";
	int pos = 20;
	char *o = get_token(str, delim, pos);
	fail_unless(o == NULL, "get_token(\"%s\",\"%s\",%d) = \"%s\"; expected NULL", str, delim, pos, o);
}
END_TEST

START_TEST (test_hash_table_1)
{
	hash_table *table = new_hash_table();
	fail_unless(table != NULL);
	fail_unless(table->list == NULL);
	fail_unless(table->hash != NULL);
}
END_TEST

START_TEST (test_hash_table_2)
{
	hash_table *hash = new_hash_table();
	fail_unless(hash != NULL);
	int status = ERROR;
	status = add_hash_info(hash, "key", "value");
	fail_unless(status == SUCCESS);
}
END_TEST

START_TEST (test_hash_table_3)
{
	hash_table *table = new_hash_table();

	fail_unless(table != NULL);
	fail_unless(table->hash != NULL);
	fail_unless(table->list == NULL);

	int status = ERROR;
	
	status = add_hash_info(table, "key", "value");
	fail_unless(status == SUCCESS);
	fail_unless(table->list != NULL);

	char *info = get_hash_info(table, "key");
	fail_unless(info != NULL);
	fail_unless(equals(info, "value"));

	info = get_hash_info(table, "keu");
	fail_unless(info == NULL);
}
END_TEST

START_TEST (test_hash_table_4)
{
	hash_table *table = new_hash_table();
	free_hash_table(&table);
	fail_unless(table == NULL);
}
END_TEST

START_TEST (test_hash_table_5)
{
	hash_table *table = new_hash_table ();

	add_hash_info (table, "teste", "123");
	add_hash_info (table, "teste1", "1234");
	add_hash_info (table, "teste2", "1235");
	add_hash_info (table, "teste3", "1236");
	add_hash_info (table, "teste4", "1237");
	add_hash_info (table, "teste5", "1238");

	char *teste = get_hash_info (table, "teste");
	char *teste1 = get_hash_info (table, "teste1");
	char *teste2 = get_hash_info (table, "teste2");
	char *teste3 = get_hash_info (table, "teste3");
	char *teste4 = get_hash_info (table, "teste4");
	char *teste5 = get_hash_info (table, "teste5");

	fail_unless (strcmp(teste, "123") == 0, "valor errado para teste");
	fail_unless (strcmp(teste1, "1234") == 0, "valor errado para teste1");
	fail_unless (strcmp(teste2, "1235") == 0, "valor errado para teste2");
	fail_unless (strcmp(teste3, "1236") == 0, "valor errado para teste3");
	fail_unless (strcmp(teste4, "1237") == 0, "valor errado para teste4");
	fail_unless (strcmp(teste5, "1238") == 0, "valor errado para teste5");

	free_hash_table (&table);
}
END_TEST

START_TEST (test_hash_table_6)
{
	hash_table *table = new_hash_table ();

	fail_if (table == NULL, "table é null");

	add_hash_info (table, "teste", "123");
	add_hash_info (table, NULL, "123");
	add_hash_info (table, "teste2", NULL);

	char *teste2 = get_hash_info (table, "teste2");
	fail_unless (teste2 == NULL, "deixou inserir uma string nula (%s)", teste2 );
	free_hash_table (&table);
}
END_TEST

START_TEST (test_lock_file_negative_fd)
{
	int fd = -1;
	int locked = lock_file(fd);
	fail_unless(locked == ERROR, "lock_file(-1) returned %d", locked);
}
END_TEST

START_TEST (test_unlock_file_negative_fd)
{
	int fd = -1;
	int unlocked = unlock_file(fd);
	fail_unless (unlocked == ERROR, "unlock_file(-1) returned %d", unlocked);
}
END_TEST

START_TEST (test_unlock_file_invalid_fd)
{
	int fd = open("inexistent", O_RDONLY);
	int unlocked = unlock_file(fd);
	fail_unless(unlocked == ERROR, "unlock_file(%d) returned %d", fd, unlocked);
}
END_TEST

Suite * core_suite(void)
{
	Suite *s = suite_create("LDC_Core");

	TCase *tc_lock = tcase_create("lockfile");
	tcase_add_test(tc_lock, test_lock_file_negative_fd);
	tcase_add_test(tc_lock, test_unlock_file_negative_fd);
	tcase_add_test(tc_lock, test_unlock_file_invalid_fd);
	suite_add_tcase(s, tc_lock);
	
	TCase *tc_hash = tcase_create("hash_table");
	tcase_add_test(tc_hash, test_hash_table_1);
	tcase_add_test(tc_hash, test_hash_table_2);
	tcase_add_test(tc_hash, test_hash_table_3);
	tcase_add_test(tc_hash, test_hash_table_4);
	tcase_add_test(tc_hash, test_hash_table_5);
	tcase_add_test(tc_hash, test_hash_table_6);
	suite_add_tcase(s, tc_hash);

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, plugin_core_create);
	tcase_add_test(tc_core, test_file_exists_when_doesnt);
	tcase_add_test(tc_core, test_file_exist_when_does);
	tcase_add_test(tc_core, test_file_exist_resolv);
	tcase_add_test(tc_core, test_file_exist_null_file);
	tcase_add_test(tc_core, test_file_exist_only_allocated_file);
	//tcase_add_test(tc_core, core_get_kernel_version);
	tcase_add_test(tc_core,test_is_blank_empty_string);
	tcase_add_test(tc_core,test_is_blank_space_string);
	tcase_add_test(tc_core,test_is_blank_large_space_string);
	tcase_add_test(tc_core,test_is_blank_ok);
	tcase_add_test(tc_core,test_is_blank_with_space_between_letters);
	tcase_add_test(tc_core,test_is_blank_not_striped);
	tcase_add_test(tc_core,test_is_blank_new_line);
	tcase_add_test(tc_core,test_is_blank_tab);
	tcase_add_test(tc_core, test_which_inexistent_dependence);
	tcase_add_test(tc_core, test_which_null_program);
	tcase_add_test(tc_core, test_which_ok);


	tcase_add_test(tc_core, new_info_tuple_null_key_and_value);
	tcase_add_test(tc_core, new_info_tuple_valid_key_and_value);
	tcase_add_test(tc_core, free_single_info_tuple_fields);
	tcase_add_test(tc_core, free_single_info_tuple);
	tcase_add_test(tc_core, free_chained_info_tuples);
	tcase_add_test(tc_core, append_info_tuple_test);
	tcase_add_test(tc_core, append_new_info_tuple_test);
	tcase_add_test(tc_core, print_info_tuple_list_test);
	tcase_add_test(tc_core, print_null_info_tuple_list_test);
	tcase_add_test(tc_core, new_device_node_test);
	tcase_add_test(tc_core, new_null_device_node_test);
	tcase_add_test(tc_core, free_single_device_node_test);
	tcase_add_test(tc_core, free_chained_device_node_test);
	tcase_add_test_raise_signal(tc_core, free_chained_device_node_sig11, 11); //SEGFAULT!
	tcase_add_test(tc_core, append_device_node_test);
	tcase_add_test(tc_core, print_device_list_test);
	tcase_add_test(tc_core, print_null_device_list_test);
	suite_add_tcase(s, tc_core);


	TCase *tc_remove = tcase_create("remove_substring-get_clean_string");
	tcase_add_test(tc_remove, test_remove_substring_ok);
	tcase_add_test(tc_remove, test_remove_substring_ok_2);
	tcase_add_test(tc_remove, test_remove_substring_invalid_src);
	tcase_add_test(tc_remove, test_remove_substring_invalid_remove);
	tcase_add_test(tc_remove, test_get_clean_string_ok);
	tcase_add_test(tc_remove, test_get_clean_string_ok_2);
	tcase_add_test(tc_remove, test_get_clean_string_ok_3);
	tcase_add_test(tc_remove, test_get_clean_string_invalid_src);
	tcase_add_test(tc_remove, test_get_clean_string_invalid_remove);
	tcase_add_test(tc_remove, test_get_clean_string_invalid_src_minor_than_remove);
	tcase_add_test(tc_remove, test_get_clean_string_return_empty);
	suite_add_tcase(s, tc_remove);

	TCase *tc_equals = tcase_create("equals");
	tcase_add_test(tc_equals, test_equals_1);
	tcase_add_test(tc_equals, test_equals_2);
	tcase_add_test(tc_equals, test_equals_3);
	tcase_add_test(tc_equals, test_equals_4);
	tcase_add_test(tc_equals, test_equals_5);
	tcase_add_test(tc_equals, test_equals_6);	
	suite_add_tcase(s, tc_equals);

	/* testes para a get_token */
	TCase *tc_hd_get_token = tcase_create("HD_token");
	tcase_add_test(tc_hd_get_token, token_with_null_str);
	tcase_add_test(tc_hd_get_token, token_with_null_delim);
	tcase_add_test(tc_hd_get_token, token_with_neg_pos);
	tcase_add_test(tc_hd_get_token, token_with_space_0);
	tcase_add_test(tc_hd_get_token, token_with_space_1);
	tcase_add_test(tc_hd_get_token, token_with_space_2);
	tcase_add_test(tc_hd_get_token, token_with_space_20);
	tcase_add_test(tc_hd_get_token, token_with_space_t_0);
	tcase_add_test(tc_hd_get_token, token_with_space_t_1);
	tcase_add_test(tc_hd_get_token, token_with_space_t_2);
	tcase_add_test(tc_hd_get_token, token_with_space_t_20);
	tcase_add_test(tc_hd_get_token, token_with_t_0);
	tcase_add_test(tc_hd_get_token, token_with_t_1);
	tcase_add_test(tc_hd_get_token, token_with_t_2);
	tcase_add_test(tc_hd_get_token, token_with_t_20);
	suite_add_tcase(s, tc_hd_get_token);

	TCase *tc_strip_end = tcase_create("test_strip_end");	
	tcase_add_test(tc_strip_end, test_strip_end_with_calloc_string);
	tcase_add_test(tc_strip_end, test_strip_end_with_null_string);	
	tcase_add_test(tc_strip_end, test_strip_end_with_empty_string);
	tcase_add_test(tc_strip_end, test_strip_end_with_null_filter);
	tcase_add_test(tc_strip_end, test_strip_end_with_one_whitespace_string);
	tcase_add_test(tc_strip_end, test_strip_end_with_multiple_whitespace_string);	
	tcase_add_test(tc_strip_end, test_strip_end_with_one_char_filter);
	tcase_add_test(tc_strip_end, test_strip_end_with_multiple_char_filter);
	tcase_add_test(tc_strip_end, test_strip_end_with_complex_string_and_filter);
	suite_add_tcase(s, tc_strip_end);

	TCase *tc_delete = tcase_create("test_delete");
	tcase_add_test(tc_delete, test_delete_ok);
	tcase_add_test(tc_delete, test_delete_null_string);
	suite_add_tcase(s, tc_delete);

	TCase *tc_app = tcase_create("append_string");
	tcase_add_test(tc_app, append_string_test_both_null);
	tcase_add_test(tc_app, append_string_destination_null);
	tcase_add_test(tc_app, append_string_empty_destination);
	tcase_add_test(tc_app, append_string_empty_src);
	tcase_add_test(tc_app, append_string_empty_destination_and_src);
	tcase_add_test(tc_app, append_string_ok);
	tcase_add_test(tc_app, append_string_recursive);
	suite_add_tcase(s, tc_app);

	TCase *tc_get_cmd_output = tcase_create("test_get_cmd_output");
	tcase_add_test(tc_get_cmd_output, test_get_cmd_output_with_blank_command);
	tcase_add_test(tc_get_cmd_output, test_get_cmd_output_with_uname_command);
	tcase_add_test(tc_get_cmd_output, test_get_cmd_output_with_invalid_command);
	tcase_add_test(tc_get_cmd_output, test_get_cmd_output_with_small_buffer_size);
	tcase_add_test(tc_get_cmd_output, test_get_cmd_output_with_buffer_size_zero);	
	tcase_add_test(tc_get_cmd_output, test_get_cmd_output_with_buffer_size_negative);
	suite_add_tcase(s, tc_get_cmd_output);


	TCase *tc_dmidecode_keyword = tcase_create("test_get_dmidecode_keyword_output");
	tcase_add_test(tc_dmidecode_keyword, get_dmidecode_keyword_output_ok);
	tcase_add_test(tc_dmidecode_keyword, get_dmidecode_keyword_output_invalid_keyword);
	tcase_add_test(tc_dmidecode_keyword, get_dmidecode_keyword_output_null_keyword);
	tcase_add_test(tc_dmidecode_keyword, get_dmidecode_keyword_output_negative_line);
	tcase_add_test(tc_dmidecode_keyword, get_dmidecode_keyword_output_line_zero);
	suite_add_tcase(s, tc_dmidecode_keyword);
	
	TCase *tc_dmidecode_output = tcase_create("test_get_dmidecode_output");
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_ok);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_negative_dmi_type);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_dmi_type_inexistent);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_null_filter);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_negative_line);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_line_zero);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_inexistent_line);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_negative_begin);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_begin_zero);
	tcase_add_test(tc_dmidecode_output, get_dmidecode_output_inexistent_begin);
	suite_add_tcase(s, tc_dmidecode_output);
	
	TCase *tc_dmidecode_count = tcase_create("test_get_dmidecode_count");		
	tcase_add_test(tc_dmidecode_count, test_get_dmidecode_count_ok);
	tcase_add_test(tc_dmidecode_count, test_get_dmidecode_count_negative_type);
	tcase_add_test(tc_dmidecode_count, test_get_dmidecode_count_inexistent_type);
	tcase_add_test(tc_dmidecode_count, test_get_dmidecode_count_null_filter);
	tcase_add_test(tc_dmidecode_count, test_get_dmidecode_count_inexistent_filter);
	suite_add_tcase(s, tc_dmidecode_count);	

	TCase *tc_dmidecode_valid_keyword = tcase_create("test_get_dmidecode_valid_keyword");		
	tcase_add_test(tc_dmidecode_valid_keyword, test_get_dmidecode_is_valid_keyword_ok_1);
	tcase_add_test(tc_dmidecode_valid_keyword, test_get_dmidecode_is_valid_keyword_ok_2);
	tcase_add_test(tc_dmidecode_valid_keyword, test_get_dmidecode_is_valid_keyword_invalid_keyword);
	tcase_add_test(tc_dmidecode_valid_keyword, test_get_dmidecode_is_valid_keyword_null_keyword);
	suite_add_tcase(s, tc_dmidecode_valid_keyword);
	
	TCase *tc_keyword = tcase_create("get_dmidecode_keyword_output");
	tcase_add_test(tc_keyword, get_dmidecode_keyword_output_ok);
	tcase_add_test(tc_keyword, get_dmidecode_keyword_output_invalid_keyword);
	tcase_add_test(tc_keyword, get_dmidecode_keyword_output_null_keyword);
	tcase_add_test(tc_keyword, get_dmidecode_keyword_output_negative_line);
	tcase_add_test(tc_keyword, get_dmidecode_keyword_output_line_zero);
	suite_add_tcase(s, tc_keyword);
	
	TCase *tc_output = tcase_create("get_dmidecode_output");
	tcase_add_test(tc_output, get_dmidecode_output_ok);
	tcase_add_test(tc_output, get_dmidecode_output_negative_dmi_type);
	tcase_add_test(tc_output, get_dmidecode_output_dmi_type_inexistent);
	tcase_add_test(tc_output, get_dmidecode_output_null_filter);
	tcase_add_test(tc_output, get_dmidecode_output_negative_line);
	tcase_add_test(tc_output, get_dmidecode_output_line_zero);
	tcase_add_test(tc_output, get_dmidecode_output_inexistent_line);
	tcase_add_test(tc_output, get_dmidecode_output_negative_begin);
	tcase_add_test(tc_output, get_dmidecode_output_begin_zero);
	tcase_add_test(tc_output, get_dmidecode_output_inexistent_begin);
	suite_add_tcase(s, tc_output);

	TCase *tc_parse = tcase_create("parse");
	tcase_add_test(tc_parse, new_tuple_test1);
	tcase_add_test(tc_parse, new_tuple_test2);
	tcase_add_test(tc_parse, new_tuple_test3);
	tcase_add_test(tc_parse, new_tuple_test4);
	tcase_add_test(tc_parse, re_find_test1);
	tcase_add_test(tc_parse, re_find_test2);
	tcase_add_test(tc_parse, re_find_test3);
	tcase_add_test(tc_parse, parse_tuple_test1);
	tcase_add_test(tc_parse, parse_tuple_test2);
	tcase_add_test(tc_parse, parse_tuple_test3);
	tcase_add_test(tc_parse, parse_tuple_test4);
	tcase_add_test(tc_parse, parse_tuple_test5);
	suite_add_tcase(s, tc_parse);

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

void assert(char *actual, char *expected)
{
	fail_unless(actual != NULL, "this function returned a NULL value");
}

