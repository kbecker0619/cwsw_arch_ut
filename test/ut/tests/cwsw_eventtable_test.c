/*
 * File:   cwsw_eventtable_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:07:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <CUnit/Basic.h>

#include "cwsw_eventtable.h"


void testCwsw_Evt__InitEventTable_badparams()
{
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tErrorCodes_EvQ result;

    result = Cwsw_Evt__InitEventTable(NULL, my_table_of_events, TABLE_SIZE(my_table_of_events));
    CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
    result = Cwsw_Evt__InitEventTable(&evTbl, NULL, TABLE_SIZE(my_table_of_events));
    CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
    result = Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, INT_MAX + 1);
    CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
}

void testCwsw_Evt__InitEventTable_goodparams()
{
    /* because they're function-local, these data disappear once this function ends */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tErrorCodes_EvQ result;

    result = Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events));
    CU_ASSERT_EQUAL(result, kErr_EvQ_NoError);
    CU_ASSERT_PTR_EQUAL(evTbl.pEvBuffer, my_table_of_events);
    CU_ASSERT_EQUAL(evTbl.szEvTbl, 10);
	CU_ASSERT_EQUAL(evTbl.validity, kRT_TBL_VALID);
}

void testCwsw_Evt__GetEventPtr_badparams()
{
    /* because they're function-local, these data disappear once this function ends */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_EvtHandle hnd = 1;
    ptEvQ_Event pEv;	/* note this data type is "pointer-to-event" */

	/* 1. null event table */
    pEv = Cwsw_Evt__GetEventPtr(NULL, hnd);
	CU_ASSERT_PTR_EQUAL(pEv, NULL);

    /* 2. uninitialized event table.
	 * note this relies on the initializer specified for the table.
	 */
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, hnd);
	CU_ASSERT_PTR_EQUAL(pEv, NULL);

	/* 3. badly initialized event table (no size).
	 * Using intimate knowledge of internal operations, supply an arbitrary address to the event
	 * buffer field (we know the UUT will not dereference it before this check is done.)
	 */
	evTbl.pEvBuffer = my_table_of_events;
	evTbl.szEvTbl = 0;
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, hnd);
	CU_ASSERT_PTR_EQUAL(pEv, NULL);
}

void testCwsw_Evt__GetEventPtr_goodparams()
{
    /* because they're function-local, these data disappear once this function ends */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_EvtHandle hnd = 1;
    ptEvQ_Event pEv;	/* note this data type is "pointer-to-event" */

    CU_ASSERT_EQUAL(Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)), kErr_EvQ_NoError);

	/* 3. badly initialized event table (no size).
	 * Using intimate knowledge of internal operations, supply an arbitrary address to the event
	 * buffer field (we know the UUT will not dereference it before this check is done.)
	 */
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, hnd);
	CU_ASSERT_PTR_EQUAL(pEv, &my_table_of_events[1]);
}

void testCwsw_Evt__GetEvent()
{
    ptEvQ_Event pEv;
    ptEvQ_EvTable pEvTb;
    tEvQ_EvtHandle hnd;
    tErrorCodes_EvQ result = Cwsw_Evt__GetEvent(pEv, pEvTb, hnd);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_Evt__PutEvent(ptEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd, ptEvQ_Event pEv);

void testCwsw_Evt__PutEvent()
{
    ptEvQ_EvTable pEvTb;
    tEvQ_EvtHandle hnd;
    ptEvQ_Event pEv;
    tErrorCodes_EvQ result = Cwsw_Evt__PutEvent(pEvTb, hnd, pEv);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}
