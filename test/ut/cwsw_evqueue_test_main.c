/*
 * File:   cwsw_event_test_main.c
 * Author: kevin
 *
 * Created on Mar 23, 2020, 8:32:20 PM
 *
 * This is the main driver for the Unit Tests of the Event Queue set of components.
 * Each component has its own CUnit suite, and its own set of UT files.
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

/* CUnit Test Suite
 */

/* Initialize all test suites
 */
int init_suite(void)
{
    return 0;
}

/* Clean all test suites
 */
int clean_suite(void)
{
    return 0;
}

uint16_t Cwsw_Evt__Init();

void testCwsw_Evt__Init()
{
    uint16_t result = Cwsw_Evt__Init();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void Cwsw_EvT__Deinit();

void testCwsw_EvT__Deinit()
{
    Cwsw_EvT__Deinit();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

_Bool Cwsw_EvT__Get_Initialized();

void testCwsw_EvT__Get_Initialized()
{
    _Bool result = Cwsw_EvT__Get_Initialized();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

int main(void)
{
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("cwsw_event_test", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testCwsw_Evt__Init", testCwsw_Evt__Init)) ||
        (NULL == CU_add_test(pSuite, "testCwsw_EvT__Deinit", testCwsw_EvT__Deinit)) ||
        (NULL == CU_add_test(pSuite, "testCwsw_EvT__Get_Initialized", testCwsw_EvT__Get_Initialized)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
