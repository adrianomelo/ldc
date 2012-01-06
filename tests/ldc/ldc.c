#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <ldc/types.h>
#include <ldc/info.h>
#include <ldc/errors.h>
#include <ldc/terminal.h>
#include <ldc/string.h>
#include <ldc/system.h>
#include <ldc/parser.h>
#include <ldc/hashtable.h>

#include <ldc/lockfile.h>

#include <ldc/config.h>
#include <filelist.h>
#include <libraries.h> 
#include <device2xml.h>
#include <translator.h>


/*****************************************
 ************** filelist.c ***************
 ****************************************/

START_TEST (ldc_new_file_list)
{
	struct file_list *fl;
	fl = new_file_list ();

	fail_if (fl == NULL, "new_file_list não está alocando memoria");

	//fail_if ((*fl).filename == NULL, "new_file_list não está alocando memoria para o nome");
}
END_TEST

START_TEST (ldc_set_name_null)
{
	struct file_list *list = new_file_list();
	int st = set_file_list_name(list, NULL);
	fail_if (st == 0, "deixou setar para NULL");
}
END_TEST

START_TEST (ldc_set_name_list_null)
{
	struct file_list *list = NULL;
	int st = set_file_list_name(list, NULL);
	fail_if (st == 0, "deixou quando list era NULL");
}
END_TEST

START_TEST (ldc_set_name)
{
	struct file_list *list = new_file_list();
	char* nome = "libstdio.so.7.1";

	int st = set_file_list_name(list, nome);

	fail_unless (st == 0, "nao conseguiu setar o nome");

	char *get_nome = get_file_list_name(list);

	fail_unless (strcmp(get_nome, nome) == 0, "set depois get name com erro");
}
END_TEST

START_TEST (ldc_append_file_list)
{
	struct file_list *root = NULL;
	struct file_list *fl_1;
	struct file_list *fl_2;
	struct file_list *fl_3;
	struct file_list *fl_4;
		
	fl_1 = new_file_list();
	fl_2 = new_file_list();
	fl_3 = new_file_list();
	fl_4 = new_file_list();
		
	fail_if (fl_1 == NULL, "fl_1 esta como NULL");
	fail_if (fl_2 == NULL, "fl_2 esta como NULL");
	fail_if (fl_3 == NULL, "fl_3 esta como NULL");
	fail_if (fl_4 == NULL, "fl_4 esta como NULL");

	int st_0 = append_file_list (&root, fl_1);
	int st_1 = append_file_list (&fl_1, fl_2);
	int st_2 = append_file_list (&fl_1, fl_3);
	int st_3 = append_file_list (&root, fl_4);

	fail_unless (st_0 == 0, "append de fl_1 em root falhou");
	fail_unless (st_1 == 0, "append de fl_2 em fl_1 falhou");
	fail_unless (st_2 == 0, "append de fl_3 em fl_1 falhou");
	fail_unless (st_3 == 0, "append de fl_4 em root falhou");

	fail_unless(set_file_list_name(fl_1, "file name 1") == SUCCESS);
	fail_unless(set_file_list_name(fl_2, "file name 2") == SUCCESS);
	fail_unless(set_file_list_name(fl_3, "file name 3") == SUCCESS);
	fail_unless(set_file_list_name(fl_4, "file name 4") == SUCCESS);

	fail_unless (strcmp(root->filename, "file name 1") == 0, 
		"fl_1 nao esta com o nome certo (%s)", fl_1->filename);

	fail_unless (strcmp(root->next->filename, "file name 2") == 0, 
		"fl_2 nao esta com o nome certo");

	fail_unless (strcmp(root->next->next->filename, "file name 3") == 0,
		"fl_3 nao esta com o nome certo");

	fail_unless (strcmp(fl_1->next->next->next->filename, "file name 4") == 0, 
		"fl_4 nao esta com o nome certo");
}
END_TEST

START_TEST (ldc_free_file_list_test1)
{
	struct file_list *fl;
	fl = new_file_list ();
	free_file_list(&fl);

	fail_if(fl != NULL, "free_file_list não está liberando memoria");
}
END_TEST

START_TEST (ldc_free_file_list_test2)
{
	struct file_list *fl;
	fl = new_file_list();
	set_file_list_name(fl, "primeiro");

	free_file_list(&fl);

	fail_if(fl != NULL, "free_file_list não está liberando memoria");
}
END_TEST

START_TEST (ldc_free_file_list_test3)
{
	struct file_list *fl;
	fl = new_file_list();
	set_file_list_name(fl, "primeiro");

	struct file_list *fl2;
	fl2 = new_file_list();
	set_file_list_name(fl2, "segundo");

	append_file_list(&fl, fl2);

	free_file_list(&fl);

	fail_unless(fl == NULL, "free_file_list não está liberando memoria");
}
END_TEST

START_TEST (ldc_free_file_list_test4)
{
	struct file_list *fl;
	fl = new_file_list();
	set_file_list_name(fl, "primeiro");

	struct file_list *fl2;
	fl2 = new_file_list();
	set_file_list_name(fl2, "segundo");

	append_file_list(&fl, fl2);
	free_file_list(&fl2);

	fail_if(fl == NULL || fl2 != NULL, "free_file_list não está liberando memoria");
}
END_TEST


/*****************************************
 ************** libraries.c **************
 ****************************************/

START_TEST (libraries_test1)
{
	char test[] = "/bin/libldccore.so.1.2";
	
	char *name = get_plugin_name (test);
	
	fail_unless (strcmp(name, "core") == 0, "não achou o nome em /bin/libcore.so.1.2");
}
END_TEST

START_TEST (libraries_test2)
{
	char *test = "/bin/libldccore.so";
	
	char *name = get_plugin_name (test);

	fail_unless (strcmp(name, "core") == 0, "não achou o nome em /bin/libcore.so");
}
END_TEST

START_TEST (libraries_test3)
{
	char test[] = "/usr/bin/libldcnetwork.so.1.2";
	
	char *name = get_plugin_name (test);

	fail_unless (strcmp(name, "network") == 0, "não achou o nome em /bin/libnetwork.so.1.2");
}
END_TEST

START_TEST (libraries_test4)
{
	char test[] = "/home/user/work space/com acentuação/libldcmultiserial.so   ";
	
	char *name = get_plugin_name (test);

	fail_unless (strcmp(name, "multiserial") == 0, "não achou o nome quando tem espaco e acentos");
}
END_TEST

START_TEST (libraries_test5)
{
	char *test = NULL;
	
	char *name = get_plugin_name (test);

	fail_unless (name == NULL, "falha quando o nome é null");
}
END_TEST

START_TEST (libraries_test6)
{
	char *test = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	
	char *name = get_plugin_name (test);

	fail_unless (name == NULL, "falha quando o nome é muito grande");
}
END_TEST

START_TEST (libraries_test7)
{
	char *test = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA/libldcteste.soAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	
	char *name = get_plugin_name (test);

	fail_unless (strcmp(name, "teste") == 0, "falha quando o nome é muito grande e deseja-se pegar o nome");
}
END_TEST

START_TEST (libraries_list_plugins_test1)
{
	char folder[] = "/";
	struct file_list *files = NULL;

	int r = list_plugins(folder, &files);

	fail_unless (r == SUCCESS, "list_plugins nao retornou NULL ao nao achar um .so");
	fail_unless (files == NULL, "achou uma biblioteca em /");
}
END_TEST

/*******************************************
*************** device2xml.c ***************
*******************************************/
START_TEST (append_xml_info_tuple_test1)
{
	struct info_tuple *info = NULL;
	char *actual = append_xml_info_tuple(info);
	fail_unless(actual == NULL, "append_xml_info_tuple(NULL) returned %s",actual);
}
END_TEST

START_TEST (append_xml_info_tuple_test2)
{
	struct info_tuple *info = new_info_tuple("KEY","VALUE");
	char *actual = append_xml_info_tuple(info);
	char *expected = "<info key=\"KEY\" value=\"VALUE\" />\n";
	
	fail_unless(actual != NULL, "append_xml_info_tuple(info) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_info_tuple returned '%s' != '%s' (expected)", actual, expected);
	free_info_tuple(&info);
	delete(&actual);
}
END_TEST

START_TEST (append_xml_info_tuple_test3)
{
	struct info_tuple *info = new_info_tuple("KEY","VALUE");
	info->next = new_info_tuple("KEY_NEXT", "VALUE_NEXT");
	
	char *actual = append_xml_info_tuple(info);
	char *expected = "<info key=\"KEY\" value=\"VALUE\" />\n<info key=\"KEY_NEXT\" value=\"VALUE_NEXT\" />\n";
	
	fail_unless(actual != NULL, "append_xml_info_tuple(info) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_info_tuple returned '%s' != '%s' (expected)", actual, expected);
	free_info_tuple(&info);
	delete(&actual);
}
END_TEST

START_TEST (append_xml_info_tuple_test4)
{
	struct info_tuple *info = new_info_tuple("KEY_1","VALUE_1");
	info->next = new_info_tuple("KEY_2", "VALUE_2");
	info->next->key = NULL;
	info->next->next = new_info_tuple("KEY_3", "VALUE_3");
	
	char *actual = append_xml_info_tuple(info);
	char *expected = "<info key=\"KEY_1\" value=\"VALUE_1\" />\n<info key=\"KEY_3\" value=\"VALUE_3\" />\n";
	
	fail_unless(actual != NULL, "append_xml_info_tuple(info1, info2->key = NULL, info3) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_info_tuple with inconsistent info_tuple in the middle of the list, returned '%s' != '%s' (expected)", actual, expected);

	free_info_tuple(&info);
	delete(&actual);
	
}
END_TEST

START_TEST (append_xml_device_test1)
{
	struct device *dev = NULL;
	char *actual = append_xml_device(dev);
	fail_unless(actual == NULL, "append_xml_device(NULL) didn't return NULL");
}
END_TEST

START_TEST (append_xml_device_test2)
{
	struct device *dev = new_device("DEV_1");
	char *actual = append_xml_device(dev);
	char *expected = "<device name=\"DEV_1\">\n</device>\n";
	fail_unless(strcmp(actual, expected) == 0, "append_xml_device(info) returned %s != %d (expected",actual, expected);
	
	free_device(&dev);
	delete(&actual);
}
END_TEST

START_TEST (append_xml_device_test3)
{
	
	struct device *dev = new_device("DEV_1");	
	struct info_tuple *info = new_info_tuple("KEY_1","VALUE_1");
	info->next = new_info_tuple("KEY_2", "VALUE_2");
	info->next->next = new_info_tuple("KEY_3", "VALUE_3");
	add_info(dev, info);

	char *expected = "<device name=\"DEV_1\">\n<info key=\"KEY_1\" value=\"VALUE_1\" />\n<info key=\"KEY_2\" value=\"VALUE_2\" />\n<info key=\"KEY_3\" value=\"VALUE_3\" />\n</device>\n";
	
	char *actual = append_xml_device(dev);

	fail_unless(actual != NULL, "append_xml_device(dev) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_device(dev) returned %s != %s (expected)", actual, expected);

	free_device(&dev);
	delete(&actual);

}
END_TEST


START_TEST (append_xml_device_test4)
{
	
	struct device *dev = new_device("DEV_1");
	add_info(dev, new_info_tuple("KEY_1", "VALUE_1"));
	add_info(dev, new_info_tuple("KEY_2", "VALUE_2"));
	add_info(dev, new_info_tuple("KEY_3", "VALUE_3"));

	struct device *dev_child = new_device("DEV_2");
	add_info(dev_child, new_info_tuple("KEY_4", "VALUE_4"));
	add_info(dev_child, new_info_tuple("KEY_5", "VALUE_5"));

	struct device *dev_next = new_device("DEV_3");
	add_info(dev_next, new_info_tuple("KEY_6", "VALUE_6"));

	dev->child = dev_child;
	dev->next = dev_next;

	char *expected = "<device name=\"DEV_1\">\n<info key=\"KEY_1\" value=\"VALUE_1\" />\n<info key=\"KEY_2\" value=\"VALUE_2\" />\n<info key=\"KEY_3\" value=\"VALUE_3\" />\n<device name=\"DEV_2\">\n<info key=\"KEY_4\" value=\"VALUE_4\" />\n<info key=\"KEY_5\" value=\"VALUE_5\" />\n</device>\n</device>\n<device name=\"DEV_3\">\n<info key=\"KEY_6\" value=\"VALUE_6\" />\n</device>\n";

	
	char *actual = append_xml_device(dev);

	fail_unless(actual != NULL, "append_xml_device(dev) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_device(dev) returned %s != %s (expected)", actual, expected);

	free_device(&dev);
	delete(&actual);

}
END_TEST

START_TEST (append_xml_device_test5)
{
	
	struct device *dev = new_device("DEV_0");
	struct device *temp = dev;	

	char expected[400] = "<device name=\"DEV_0\">\n</device>\n";

	int i;
	for (i = 1; i < 10; i++) {
		char template[40];
		char device_name[10];

		sprintf(device_name, "DEV_%d", i);
		temp->next = new_device(device_name);
		temp = temp->next;

		
 		sprintf(template, "<device name=\"%s\">\n</device>\n", device_name);
		strcat(expected, template);	
	}

	char *actual = append_xml_device(dev);

	fail_unless(actual != NULL, "append_xml_device(dev) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_device(dev) with 9 brothers, returned %s != %s (expected)", actual, expected);

	free_device(&dev);
	delete(&actual);

}
END_TEST


START_TEST (append_xml_device_test6)
{
	struct device *dev = new_device("DEV_0");
	struct device *temp = dev;
	
	char expected[400] = "<device name=\"DEV_0\">\n";
	
	int i;
	for (i = 1; i < 10; i++) {
		
		char template[40];
		char device_name[10];

		sprintf(device_name, "DEV_%d", i);
		temp->child = new_device(device_name);
		temp = temp->child;
		
 		sprintf(template, "<device name=\"%s\">\n", device_name);
		strcat(expected, template);
	}

	for (i = 0; i < 10; i++) {
		strcat(expected,"</device>\n");
	}

	char *actual = append_xml_device(dev);

	fail_unless(actual != NULL, "append_xml_device(dev) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_device(dev) with 9 childs, returned %s != %s (expected)", actual, expected);

	free_device(&dev);
	delete(&actual);
}
END_TEST



START_TEST (append_xml_device_test7)
{
	/*
	Este teste verifica o comportamento da função append_xml_device
	quando se passa como argumento um device mal formando (device->name == NULL)
	*/

	struct device *dev = new_device("TESTE");
	dev->name = NULL;
	char *actual = append_xml_device(dev);
	fail_unless(actual == NULL, "append_xml_device(device without name) didn't returned NULL, but should");
	delete(&actual);
}
END_TEST

START_TEST (append_xml_meta_test1)
{
	struct device *dev = NULL;
	char *actual = append_xml_meta(dev);
	char *expected = "<?xml version=\"1.0\" encoding=\"ISO-8859-2\"?>\n<device></device>\n";
	fail_unless(strcmp(actual, expected) == 0, "append_xml_meta(NULL) returned %s != %s (expected)", actual, expected);
	delete(&actual);
}
END_TEST

START_TEST (append_xml_meta_test2)
{
	struct device *dev = new_device("DEV_1");
	add_info(dev, new_info_tuple("KEY_1", "VALUE_1"));
	add_info(dev, new_info_tuple("KEY_2", "VALUE_2"));
	add_info(dev, new_info_tuple("KEY_3", "VALUE_3"));

	struct device *dev_child = new_device("DEV_2");
	add_info(dev_child, new_info_tuple("KEY_4", "VALUE_4"));
	add_info(dev_child, new_info_tuple("KEY_5", "VALUE_5"));

	struct device *dev_next = new_device("DEV_3");
	add_info(dev_next, new_info_tuple("KEY_6", "VALUE_6"));

	dev->child = dev_child;
	dev->next = dev_next;

	char *expected = "<?xml version=\"1.0\" encoding=\"ISO-8859-2\"?>\n<device name=\"DEV_1\">\n<info key=\"KEY_1\" value=\"VALUE_1\" />\n<info key=\"KEY_2\" value=\"VALUE_2\" />\n<info key=\"KEY_3\" value=\"VALUE_3\" />\n<device name=\"DEV_2\">\n<info key=\"KEY_4\" value=\"VALUE_4\" />\n<info key=\"KEY_5\" value=\"VALUE_5\" />\n</device>\n</device>\n<device name=\"DEV_3\">\n<info key=\"KEY_6\" value=\"VALUE_6\" />\n</device>\n";

	
	char *actual = append_xml_meta(dev);
	
	fail_unless(actual != NULL, "append_xml_device(dev) returned NULL, but shouldn't");
	fail_unless(strcmp(actual, expected) == 0, "append_xml_device(dev) returned %s != %s (expected)", actual, expected);


	free_device(&dev);
	delete(&actual);
}
END_TEST

/*
START_TEST (test_append_xml_meta_null)
{
	struct device *dev = NULL;
	char *expected = "<?xml version=\"1.0\" encoding=\"ISO-8859-2\">\n<device></device>\n";
	char *actual = append_xml_meta(dev);
	fail_unless(strcmp(actual,expected) == 0, "append_xml_meta(NULL) returned %s", actual);	
}
END_TEST
*/


/*
START_TEST (device2xml_test1)
{
	struct device *d = new_device("processor");
	hash_table *config = new_hash_table();
	add_hash_info (config, "xml_output", "/tmp/processor.xml");

	int ret = device2xml (d, config);

	fail_unless (ret == SUCCESS, "funcao device2xml nao foi executada corretamente");
}
END_TEST

START_TEST (device2xml_test2)
{
	struct device *d = NULL;
	
	hash_table *config = new_hash_table();
	add_hash_info (config, "xml_output", "/tmp/processor.xml");

	int ret = device2xml (d, config);

	fail_unless (ret == ERROR, "nao esta retornando erro");
}
END_TEST
*/



/*******************************
********** config.c ************
*******************************/

START_TEST (config_test1)
{
	char *file = "/usr/etc/ldc.conf";
	hash_table *table = new_hash_table();

	int ret = load_config (table, file);

	fail_unless (ret == SUCCESS, "nao conseguiu abrir o arquivo /etc/ldc.conf");

	free_hash_table (&table);
}
END_TEST

START_TEST (config_test2)
{
	char *file = NULL;
	hash_table *table = new_hash_table();

	int ret = load_config (table, file);

	fail_unless (ret == ERROR, "conseguiu abrir o arquivo NULL?");

	free_hash_table (&table);
}
END_TEST

START_TEST (config_test3)
{
	char *file = "/etc/";
	hash_table *table = new_hash_table();

	int ret = load_config (table, file);

	fail_unless (ret == SUCCESS, "conseguiu abrir uma pasta?");

	free_hash_table (&table);
}
END_TEST

START_TEST (config_test5)
{
	char *file = "/etc/ldc.conf.esse.arquivo.nao.existe";
	hash_table *table = new_hash_table();

	int ret = load_config (table, file);

	fail_unless (ret == ERROR, "nao conseguiu abrir o arquivo /etc/ldc.conf.  esse arquivo nao existe");

	free_hash_table (&table);
}
END_TEST


/*****************************************
 ************ translator.c ***************
 ****************************************/

START_TEST (get_translation_with_null_table)
{
	hash_table *trans = NULL;
	char *ret = get_translation(trans, "IP");

	fail_unless (ret == NULL, "não checou corretamente os parametros");
}
END_TEST

START_TEST (get_translation_with_null_label)
{
	hash_table *trans = new_hash_table();
	char *tag = NULL;
	char *ret = get_translation(trans, tag);

	fail_unless (ret == NULL, "não checou corretamente os parametros");
}
END_TEST

START_TEST (get_translation_with_valid_args)
{
	char *file = "/etc/ldc.conf";
	hash_table *table = new_hash_table();

	load_config(table, file);
	
	hash_table *trans = load_translation(table);

	char *ret = get_translation(trans, "IP");

	if (ret != NULL)
		fail_unless (strcmp(ret, "Endereço IP") == 0, "não traduziu corretamente a tag IP");
}
END_TEST

Suite * core_suite(void)
{
	Suite *s = suite_create("Linux Diagnostic Center");

	TCase *tc_core = tcase_create("funcoes do filelist.c");
	tcase_add_test(tc_core, ldc_new_file_list);
	tcase_add_test(tc_core, ldc_append_file_list);
	tcase_add_test(tc_core, ldc_set_name_null);
	tcase_add_test(tc_core, ldc_set_name);
	tcase_add_test(tc_core, ldc_set_name_list_null);
	tcase_add_test(tc_core, ldc_free_file_list_test1);
	tcase_add_test(tc_core, ldc_free_file_list_test2);
	tcase_add_test(tc_core, ldc_free_file_list_test3);
	tcase_add_test(tc_core, ldc_free_file_list_test4);
	suite_add_tcase(s, tc_core);

	TCase *tc_core2 = tcase_create("funcoes do libraries.c, get_plugin_name");
	tcase_add_test(tc_core2, libraries_test1);
	tcase_add_test(tc_core2, libraries_test2);
	tcase_add_test(tc_core2, libraries_test3);
	tcase_add_test(tc_core2, libraries_test4);
	tcase_add_test(tc_core2, libraries_test5);
	tcase_add_test(tc_core2, libraries_test6);
	tcase_add_test(tc_core2, libraries_test7);
	suite_add_tcase(s, tc_core2);

	TCase *tc_core3 = tcase_create("funcoes do libraries.c, list_plugins");
	tcase_add_test(tc_core3, libraries_list_plugins_test1);
	suite_add_tcase(s, tc_core3);

	TCase *tc_core4 = tcase_create("device2xml.c");
	//tcase_add_test(tc_core4, device2xml_test1);
	//tcase_add_test(tc_core4, device2xml_test2);
	tcase_add_test(tc_core4, append_xml_info_tuple_test1);
	tcase_add_test(tc_core4, append_xml_info_tuple_test2);
	tcase_add_test(tc_core4, append_xml_info_tuple_test3);
	tcase_add_test(tc_core4, append_xml_info_tuple_test4);
	tcase_add_test(tc_core4, append_xml_device_test1);
	tcase_add_test(tc_core4, append_xml_device_test2);
	tcase_add_test(tc_core4, append_xml_device_test3);
	tcase_add_test(tc_core4, append_xml_device_test4);
	tcase_add_test(tc_core4, append_xml_device_test5);
	tcase_add_test(tc_core4, append_xml_device_test6);
	tcase_add_test(tc_core4, append_xml_device_test7);
	tcase_add_test(tc_core4, append_xml_meta_test1);	
	tcase_add_test(tc_core4, append_xml_meta_test2);
	suite_add_tcase(s, tc_core4);

	TCase *tc_core6 = tcase_create("config.c");
	tcase_add_test(tc_core6, config_test1);
	tcase_add_test(tc_core6, config_test2);
	tcase_add_test(tc_core6, config_test3);
	tcase_add_test(tc_core6, config_test5);
	suite_add_tcase(s, tc_core6);

	TCase *tc_core10 = tcase_create("translator.c");
	tcase_add_test(tc_core10, get_translation_with_null_table);
	tcase_add_test(tc_core10, get_translation_with_null_label);
	tcase_add_test(tc_core10, get_translation_with_valid_args);
	suite_add_tcase(s, tc_core10);

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

