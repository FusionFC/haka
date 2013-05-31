
#include <stdio.h>
#include <check.h>
#include <wchar.h>
#include <haka/ipv4.h>
#include <haka/ipv4-address.h>
#include <haka/ipv4-network.h>

START_TEST(ipv4_addr_check_from_string)
{
	ck_assert_int_eq(ipv4_addr_from_string("192.12.1.9"), -1072955127);
}
END_TEST

START_TEST(ipv4_addr_check_from_bytes)
{
	ck_assert_int_eq(ipv4_addr_from_bytes(192, 12, 1, 9), -1072955127);
}
END_TEST

START_TEST(ipv4_addr_check_to_string)
{
	char str[IPV4_ADDR_STRING_MAXLEN+1];
	ipv4_addr_to_string(-1072955127, str, IPV4_ADDR_STRING_MAXLEN+1);
	ck_assert_str_eq(str, "192.12.1.9");
}
END_TEST

START_TEST(ipv4_network_check)
{
	char str[32];
	ipv4network network;
	network = ipv4_network_from_string("192.168.1.0/24");
	wprintf(L"--------- : %d\n", network.net);
	ck_assert_int_eq(network.net, -1062731520);
	ck_assert_int_eq(network.mask, 24);
	network.net = -1408237568;
	network.mask = 16;
	ipv4_network_to_string(network, str, 32);
	ck_assert_str_eq(str, "172.16.0.0/16");
}
END_TEST

Suite* ipv4_suite(void)
{
	Suite *suite = suite_create("ipv4_suite");

	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, ipv4_addr_check_from_string);
	tcase_add_test(tcase, ipv4_addr_check_from_bytes);
	tcase_add_test(tcase, ipv4_addr_check_to_string);
	tcase_add_test(tcase, ipv4_network_check);
	suite_add_tcase(suite, tcase);
	return suite;
}

int main (int argc, char *argv[])
{
	int number_failed;
	Suite *suite = ipv4_suite();
	SRunner *runner = srunner_create(suite);
	srunner_run_all(runner, CK_NORMAL);
	number_failed = srunner_ntests_failed(runner);
	srunner_free(runner);
	return number_failed;
}
