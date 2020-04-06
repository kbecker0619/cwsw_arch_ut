/*
 * File:   newcunittest.c
 * Author: kevin
 *
 * Created on Apr 5, 2020, 8:04:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include <stdbool.h>    /* type bool, w/ false, true */
#include "cwsw_event.h" /* deinit */
/*
 * CUnit Test Suite
 */

/* Within **this** file, we are doing a very basic check of the project-specific enter-exit-
 * critical-section implementation. As part of that, the `init` an `clean` suite actions will set up
 * the vars used by that module.
 */
extern bool crit_section_seen;
extern int crit_sec_prot_lvl;
extern char const *crit_sect_file;
extern int crit_section_line;

extern void cb_event_demo_cs_enter(int protlvl, const char* const filename, const int lineno);
extern void cb_event_demo_cs_leave(int protlvl, const char* const filename, const int lineno);

/* CUnit function prototypes */
extern void testCwsw_Evt__Init();
extern void testCwsw_EvT__Deinit();



int init_suite(void)
{
    /* critical section initialization */
	crit_section_seen = false;

    /* event initialization */
    Cwsw_EvT__Deinit();
    return 0;
}

int clean_suite(void)
{
    /* critical section initialization */
	crit_section_seen = false;

    /* event initialization */
    Cwsw_EvT__Deinit();
    return 0;
}


void testCb_event_demo_cs_enter()
{
    const int lineno = __LINE__;
    cb_event_demo_cs_enter(1, "Enter", lineno);

    CU_ASSERT_EQUAL(crit_section_seen, true);
    CU_ASSERT_EQUAL(crit_sec_prot_lvl, 1);
    CU_ASSERT_STRING_EQUAL(crit_sect_file, "Enter");
    CU_ASSERT_EQUAL(crit_section_line, lineno);

    /* this next line probably violates CUnit methods, but i don't know the API well enough to do it via any API*/
    crit_section_seen = false;
}

void testCb_event_demo_cs_leave()
{
    const int lineno = __LINE__;
    cb_event_demo_cs_leave(2, "Leave", lineno);

    CU_ASSERT_EQUAL(crit_section_seen, true);
    CU_ASSERT_EQUAL(crit_sec_prot_lvl, -2);
    CU_ASSERT_STRING_EQUAL(crit_sect_file, "Leave");
    CU_ASSERT_EQUAL(crit_section_line, lineno);

    /* this next line probably violates CUnit methods, but i don't know the API well enough to do it via any API*/
    crit_section_seen = false;
}


int main()
{
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("EvQ CUnit Test Suite", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if( (NULL == CU_add_test(pSuite, "testCb_event_demo_cs_enter", testCb_event_demo_cs_enter)) ||
        (NULL == CU_add_test(pSuite, "testCb_event_demo_cs_leave", testCb_event_demo_cs_leave)) ||
        /* add Event component unit tests */
        (NULL == CU_add_test(pSuite, "testCwsw_Evt__Init",      testCwsw_Evt__Init)) ||
        (NULL == CU_add_test(pSuite, "testCwsw_EvT__Deinit",    testCwsw_EvT__Deinit))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
