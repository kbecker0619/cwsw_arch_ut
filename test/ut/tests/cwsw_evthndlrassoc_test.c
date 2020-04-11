/*
 * File:   cwsw_evthndlrassoc_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 7:00:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <CUnit/Basic.h>

#include "cwsw_evthndlrassoc.h"
#include "cwsw_evqueue_ex_tests.h"


/* Test Init Event Handler Table.
 * writing this UT case after just having spent a lot of time in the EVQ case; this leads me to look
 * at the complexity of this API and decide (for now) to execute both happy-path and briar-patch
 * path in this one case.
 */
void testCwsw_EvHA__InitEventHandlerTable(void)
{
	tEvHA_EvHandlerAssoc HndlrArray[10] = {0};	// association array; equiv. to "event buffer" in an event table.
    tEvQ_EvHndlrAssocTable EvtHndlrTbl = {0};	// event handler association table
    tErrorCodes_EvQ result;

	// no handler association table
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__InitEventHandlerTable(NULL, HndlrArray, TABLE_SIZE(HndlrArray))), kErr_EvQ_BadParm);

	// no association array
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__InitEventHandlerTable(&EvtHndlrTbl, NULL, TABLE_SIZE(HndlrArray))), kErr_EvQ_BadParm);

	// bad size
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__InitEventHandlerTable(&EvtHndlrTbl, HndlrArray, (size_t)INT_MAX + 1UL)), kErr_EvQ_BadParm);
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__InitEventHandlerTable(&EvtHndlrTbl, HndlrArray, 0UL)), kErr_EvQ_BadParm);

	// successful
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__InitEventHandlerTable(&EvtHndlrTbl, HndlrArray, TABLE_SIZE(HndlrArray))), kErr_EvQ_NoError);
	CU_ASSERT_PTR_EQUAL(EvtHndlrTbl.pEvtHndlrLut, HndlrArray);
	CU_ASSERT_EQUAL(EvtHndlrTbl.szEvtHandlerTbl, TABLE_SIZE(HndlrArray));
	CU_ASSERT_EQUAL(EvtHndlrTbl.validity, kRT_TBL_VALID);
}


static tEvQ_Event gev = {0};
static uint32_t evextra = 0;
static void EvHandlerFunc(tEvQ_Event ev, uint32_t extra)
{
	gev.evId = ev.evId;
	gev.evData = ev.evData;
	evextra = extra;
}

void testCwsw_EvHA__SetEvHandler(void)
{
    tErrorCodes_EvQ result;
	// association array; equiv. to "event buffer" in an event table.
	tEvHA_EvHandlerAssoc HndlrArray[10] = {0};
	// event handler association table
    tEvQ_EvHndlrAssocTable EvtHndlrTbl = {HndlrArray, TABLE_SIZE(HndlrArray), kCT_TBL_VALID + 1};	// <-- intentionally bad validation signature

	// there's no component init for this component (yet). don't need to assert its initialization status.

	// no handler association table
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__SetEvHandler(NULL, 1, EvHandlerFunc)), kErr_EvQ_BadParm);
	// invalid table
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__SetEvHandler(&EvtHndlrTbl, 1, EvHandlerFunc)), kErr_EvQ_BadParm);
	// invalid event id
	EvtHndlrTbl.validity = kRT_TBL_VALID;
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__SetEvHandler(&EvtHndlrTbl, 0, EvHandlerFunc)), kErr_EvQ_BadParm);
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__SetEvHandler(&EvtHndlrTbl, -1, EvHandlerFunc)), kErr_EvQ_BadParm);
	// nonexistent event id
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__SetEvHandler(&EvtHndlrTbl, 13, EvHandlerFunc)), kErr_EvQ_BadParm);

	// successful association
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__SetEvHandler(&EvtHndlrTbl, 1, EvHandlerFunc)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(HndlrArray[1].evId, 1);
	CU_ASSERT_PTR_EQUAL(HndlrArray[1].pEvHandler, EvHandlerFunc);

	// erase handler association
	CU_ASSERT_EQUAL((result = Cwsw_EvHA__SetEvHandler(&EvtHndlrTbl, 1, NULL)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(HndlrArray[1].evId, 1);
	CU_ASSERT_PTR_EQUAL(HndlrArray[1].pEvHandler, NULL);
}


void testCwsw_EvHA__GetEvHandler(void)
{
    pEvQ_EvHandlerFunc result;
	// association array; equiv. to "event buffer" in an event table.
	tEvHA_EvHandlerAssoc HndlrArray[10] = {0};
	// event handler association table
    tEvQ_EvHndlrAssocTable EvtHndlrTbl = {HndlrArray, TABLE_SIZE(HndlrArray), kCT_TBL_VALID + 1};	// <-- intentionally bad validation signature

	// there's no component init for this component (yet). don't need to assert its initialization status.

	// no handler association table
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvHA__GetEvHandler(NULL, 1)), NULL);
	// invalid table
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvHA__GetEvHandler(&EvtHndlrTbl, 1)), NULL);
	// invalid event id
	EvtHndlrTbl.validity = kRT_TBL_VALID;
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvHA__GetEvHandler(&EvtHndlrTbl, 0)), NULL);
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvHA__GetEvHandler(&EvtHndlrTbl, -1)), NULL);
	// nonexistent event id
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvHA__GetEvHandler(&EvtHndlrTbl, 13)), NULL);

	// successful association
	HndlrArray[1].pEvHandler = EvHandlerFunc;
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvHA__GetEvHandler(&EvtHndlrTbl, 1)), EvHandlerFunc);
}
