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
    result = Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, ((size_t)INT_MAX + 1));
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
    ptEvQ_Event pEv;	/* note this data type is "pointer-to-event" */

	/* 1. null event table */
    pEv = Cwsw_Evt__GetEventPtr(NULL, 1);
	CU_ASSERT_PTR_EQUAL(pEv, NULL);

    /* 2. uninitialized event table.
	 * note this relies on the initializer specified for the table.
	 */
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, 1);
	CU_ASSERT_PTR_EQUAL(pEv, NULL);

	/* 3. badly initialized event table (no size).
	 * Using intimate knowledge of internal operations, supply an arbitrary address to the event
	 * buffer field (we know the UUT will not dereference it before this check is done.)
	 */
	evTbl.pEvBuffer = my_table_of_events;
	evTbl.szEvTbl = 0;
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, 1);
	CU_ASSERT_PTR_EQUAL(pEv, NULL);

	// 4. bad handle (negative)
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, -1);
	CU_ASSERT_PTR_EQUAL(pEv, NULL);

	// 5. bad handle (too large). remember, our handle is base-0.
	evTbl.szEvTbl = TABLE_SIZE(my_table_of_events);
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, TABLE_SIZE(my_table_of_events));
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
    ptEvQ_Event pEv;	/* note this data type is "pointer-to-event" */

    CU_ASSERT_EQUAL(Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)), kErr_EvQ_NoError);

	/* 3. badly initialized event table (no size).
	 * Using intimate knowledge of internal operations, supply an arbitrary address to the event
	 * buffer field (we know the UUT will not dereference it before this check is done.)
	 */
	pEv = Cwsw_Evt__GetEventPtr(&evTbl, 1);
	CU_ASSERT_PTR_EQUAL(pEv, &my_table_of_events[1]);
}

void testCwsw_Evt__GetEvent_badparams()
{
    /* because they're function-local, these data disappear once this function ends */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_Event ev = {0};
    tErrorCodes_EvQ result;

	// no event
	result = Cwsw_Evt__GetEvent(NULL, &evTbl, 1);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
	// no event table
    result = Cwsw_Evt__GetEvent(&ev, NULL, 1);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
	// bad event buffer. note we're still not initialized.
	evTbl.szEvTbl = 2;
	result = Cwsw_Evt__GetEvent(&ev, &evTbl, 1);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadEvent);

	// bad handle
	CU_ASSERT_EQUAL(Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)), kErr_EvQ_NoError);
    result = Cwsw_Evt__GetEvent(&ev, &evTbl, TABLE_SIZE(my_table_of_events) + 1);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadTable);
}

void testCwsw_Evt__GetEvent_goodparams()
{
    /* because they're function-local, these data disappear once this function ends */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_Event ev = {0};
    tErrorCodes_EvQ result;

	CU_ASSERT_EQUAL(Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)), kErr_EvQ_NoError);
	/* for totally arbitrary reasons, pick the 7th slot in the table and see what we get back */
    result = Cwsw_Evt__GetEvent(&ev, &evTbl, 7);
	CU_ASSERT_EQUAL(result, kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(ev.evId, 7);
	CU_ASSERT_EQUAL(ev.evData, 207);
}


void testCwsw_Evt__PutEvent_badparams()
{
    /* because they're function-local, these data disappear once this function ends */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_Event ev = {0};
    tErrorCodes_EvQ result;

	// no event table
	result = Cwsw_Evt__PutEvent(NULL, 1, &ev);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
	// no event
    result = Cwsw_Evt__PutEvent(&evTbl, 1, NULL);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
	// bad event buffer. note we're still not initialized.
	evTbl.szEvTbl = 2;
    result = Cwsw_Evt__PutEvent(&evTbl, 1, &ev);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadEvBuffer);

	// bad handle
	CU_ASSERT_EQUAL(Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)), kErr_EvQ_NoError);
    result = Cwsw_Evt__PutEvent(&evTbl, TABLE_SIZE(my_table_of_events) + 1, &ev);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadTable);
}

void testCwsw_Evt__PutEvent_goodparams()
{
    /* because they're function-local, these data disappear once this function ends */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_Event ev = {0};
    tErrorCodes_EvQ result;

	CU_ASSERT_EQUAL(Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)), kErr_EvQ_NoError);
    result = Cwsw_Evt__PutEvent(&evTbl, 1, &ev);
	CU_ASSERT_EQUAL(result, kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(my_table_of_events[1].evId, 0);
	CU_ASSERT_EQUAL(my_table_of_events[1].evData, 0);
}
