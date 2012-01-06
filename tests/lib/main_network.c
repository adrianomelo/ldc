#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include <ldc/errors.h>
#include <ldc/types.h>
#include <ldc/info.h>
#include <ldc/terminal.h>
#include <network/network.h>



/******************************************************************************/
/*		            Test Case : GET_INFO			              */	
/******************************************************************************/

START_TEST(test_get_info_with_null)
{
	struct device *dev = NULL;
	fail_unless(get_info(dev) == ERROR, "get_info(NULL) != ERROR");
}
END_TEST



/******************************************************************************/
/*		            Test Case : GET_IP			              */	
/******************************************************************************/

START_TEST(test_get_ip_with_null_device)
{
	struct device *dev = NULL;
	char *ret = get_ip(dev);	
	fail_unless(ret == NULL, "get_ip(NULL) != NULL");	
}
END_TEST




/******************************************************************************/
/*		            Test Case : GET_MAC			              */	
/******************************************************************************/

START_TEST(test_get_mac_with_null_device)
{
	struct device *dev = NULL;
	char *ret = get_mac(dev);	
	fail_unless(ret == NULL, "get_mac(NULL) != NULL");	
}
END_TEST





/******************************************************************************/
/*		            Test Case : GET_GATEWAY  		              */	
/******************************************************************************/

START_TEST(test_get_gateway_with_null_device)
{
	struct device *dev = NULL;
	char *ret = get_gateway(dev);	
	fail_unless(ret == NULL, "get_gateway(NULL) != NULL");	
}
END_TEST



/******************************************************************************/
/*		            Test Case : GET_LINK_DETECTED  		              */	
/******************************************************************************/

START_TEST(test_get_link_detected_with_null_device)
{
	struct device *dev = NULL;
	char *ret = get_link_detected(dev);	
	fail_unless(ret == NULL, "get_link_detected(NULL) != NULL");	
}
END_TEST




/******************************************************************************/
/*		            Test Case : GET_LINK_UP  		              */	
/******************************************************************************/

START_TEST(test_get_link_up_with_null_device)
{
	struct device *dev = NULL;
	char *ret = get_link_up(dev);	
	fail_unless(ret == NULL, "get_link_up(NULL) != NULL");	
}
END_TEST




/******************************************************************************/
/*		          Test Case : ADD_NIC_INFO			      */	
/******************************************************************************/

START_TEST(test_add_nic_info_with_null_device)
{
	struct device *dev = NULL;		
	fail_unless(add_nic_info(dev) == ERROR, "add_nic_info(NULL) != ERROR");	
}
END_TEST




/*################################## CHECK ###################################*/

Suite *network_suite(void)
{
	Suite *s = suite_create("LDC_Network");

	TCase *tc_get_info = tcase_create("test_get_info");
	tcase_add_test(tc_get_info, test_get_info_with_null);

	TCase *tc_get_ip = tcase_create("test_get_ip");
	tcase_add_test(tc_get_ip, test_get_ip_with_null_device);

	TCase *tc_get_mac = tcase_create("test_get_mac");
	tcase_add_test(tc_get_mac, test_get_mac_with_null_device);
	
	TCase *tc_get_gw = tcase_create("test_get_gateway");
	tcase_add_test(tc_get_gw, test_get_gateway_with_null_device);

	TCase *tc_add_nic_info = tcase_create("test_add_nic_info");
	tcase_add_test(tc_add_nic_info, test_add_nic_info_with_null_device);

	TCase *tc_get_link_detected = tcase_create("test_get_link_detected");
	tcase_add_test(tc_get_link_detected, test_get_link_detected_with_null_device);

	TCase *tc_get_link_up = tcase_create("test_get_link_up");
	tcase_add_test(tc_get_link_up, test_get_link_up_with_null_device);
	
	
	suite_add_tcase(s, tc_get_info);
	suite_add_tcase(s, tc_get_ip);
	suite_add_tcase(s, tc_get_mac);
	suite_add_tcase(s, tc_get_gw);
	suite_add_tcase(s, tc_get_link_detected);	
	suite_add_tcase(s, tc_get_link_up);	
	suite_add_tcase(s, tc_add_nic_info);
	return s;
}

int main(void)
{
	int number_failed;
	Suite *s = network_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
