/*
 * File:   newcunittest.c
 * Author: kevin
 *
 * Created on Apr 5, 2020, 8:04:38 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include <stdbool.h>		/* type bool, w/ false, true */
#include "cwsw_evqueue.h"	/* deinit */

#include "cwsw_evqueue_test.h"
#include "cwsw_evqueue_ex_tests.h"


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


int init_suite(void)
{
    /* critical section initialization */
	crit_section_seen = false;

    /* event initialization */
    Cwsw_Evt__Deinit();
	Cwsw_EvQ__Deinit();

    return 0;
}

int clean_suite(void)
{
    /* critical section initialization */
	crit_section_seen = false;

    /* event initialization */
    Cwsw_Evt__Deinit();
	Cwsw_EvQ__Deinit();

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
	enum {
		kEventPkgTests,
		kEventQueuePkgTests,
		kEventQueueExPkgTests,
		kNumCUnitTestingSuites
	};

	int suiteidx;
	bool problem = false;

    CU_pSuite pSuite[kNumCUnitTestingSuites] = {0};

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())	{ return CU_get_error(); }

	for(suiteidx = 0; suiteidx < kNumCUnitTestingSuites; suiteidx ++)
	{
		/* Add suite to the registry */
		pSuite[suiteidx] = CU_add_suite("EvQ CUnit Test Suite", init_suite, clean_suite);
		if (NULL == pSuite[suiteidx])
		{
			CU_cleanup_registry();
			return CU_get_error();
		}

	    /* Add the tests to the suite */
		problem = false;
		switch(suiteidx)
		{
		case kEventPkgTests:	{
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCb_event_demo_cs_enter", testCb_event_demo_cs_enter));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCb_event_demo_cs_leave",	testCb_event_demo_cs_leave));

			/* add Event component unit tests */
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__Init",      testCwsw_Evt__Init));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvT__Deinit",    testCwsw_EvT__Deinit));

			/* Event Table unit tests */
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__InitEventTable_badparams",		testCwsw_Evt__InitEventTable_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__InitEventTable_goodparams",	testCwsw_Evt__InitEventTable_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__GetEventPtr_badparams",		testCwsw_Evt__GetEventPtr_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__GetEventPtr_goodparams",		testCwsw_Evt__GetEventPtr_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__GetEvent_badparams",			testCwsw_Evt__GetEvent_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__GetEvent_goodparams",			testCwsw_Evt__GetEvent_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__PutEvent_badparams",			testCwsw_Evt__PutEvent_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_Evt__PutEvent_goodparams",			testCwsw_Evt__PutEvent_goodparams));
			}
			break;

		case kEventQueuePkgTests:	{
			/* Event Queue unit tests*/
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__Init",						testCwsw_EvQ__Init));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__InitEvQ",					testCwsw_EvQ__InitEvQ_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__InitEvQ_goodparams",		testCwsw_EvQ__InitEvQ_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__FlushEvents_badparams",	testCwsw_EvQ__FlushEvents_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__FlushEvents_goodparams",	testCwsw_EvQ__FlushEvents_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__PostEvent_badparams",		testCwsw_EvQ__PostEvent_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__PostEvent_goodparams",		testCwsw_EvQ__PostEvent_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__GetEvent_badparams",		testCwsw_EvQ__GetEvent_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__GetEvent_goodparams",		testCwsw_EvQ__GetEvent_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__PostEvent",				testCwsw_EvQX__PostEvent_badparams));
			}
			break;

		case kEventQueueExPkgTests:	{
			/* event handler association table tests */
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvHA__InitEventHandlerTable",	testCwsw_EvHA__InitEventHandlerTable));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvHA__SetEvHandler",			testCwsw_EvHA__SetEvHandler));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvHA__GetEvHandler",			testCwsw_EvHA__GetEvHandler));

			/* event handler tests */
			/* not actually sure this module is useful. it seems to be an independent subset of the previous.
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQ__RegisterHandler",			testCwsw_EvQ__RegisterHandler));
			 */

			/* extended event handler tests */
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__InitEvQ_badparams",		testCwsw_EvQX__InitEvQ_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__InitEvQ_goodparams",		testCwsw_EvQX__InitEvQ_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__FlushEvents_badparams",	testCwsw_EvQX__FlushEvents_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__FlushEvents_goodparams",	testCwsw_EvQX__FlushEvents_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__PostEvent_badparams",		testCwsw_EvQX__PostEvent_badparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQx__PostEvent_goodparams",	testCwsw_EvQx__PostEvent_goodparams));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__SetEvHandler",			testCwsw_EvQX__SetEvHandler));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__GetEvHandler",			testCwsw_EvQX__GetEvHandler));
			problem |= (NULL == CU_add_test(pSuite[suiteidx], "testCwsw_EvQX__HandleNextEvent",			testCwsw_EvQX__HandleNextEvent));
			}
			break;

		default:
			break;
		}

		if(problem)
		{
			CU_cleanup_registry();
			return CU_get_error();
		}
	}

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
