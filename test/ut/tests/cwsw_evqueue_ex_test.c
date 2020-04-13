/*
 * File:   cwsw_evqueue_ex_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:22:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>			/* uint32_t */
#include <CUnit/Basic.h>

#include "cwsw_evqueue_ex.h"
#include "cwsw_evqueue_ex_tests.h"


void testCwsw_EvQX__InitEvQ_badparams(void)
{
	tErrorCodes_EvQ			result;
    tEvQ_QueueCtrlEx		EvQX			= {0};
	tEvQ_EvTable			tblEv			= {0};
    tEvQ_Event				EvBuff[15]		= {0};	// room for 15 events in the queue
    tEvQ_EvHndlrAssocTable	tblEvH			= {0};
	tEvHA_EvHandlerAssoc	AssocArr[10]	= {0};	// room for 10 defined event handlers

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), false);

	// no evqx
    result = Cwsw_EvQX__InitEvQX(NULL,	&tblEv, EvBuff, TABLE_SIZE(EvBuff), &tblEvH,	AssocArr,	TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);

	// no event handler association table
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, EvBuff, TABLE_SIZE(EvBuff),	NULL,		AssocArr,	TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);

	// no event association LUT
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, EvBuff, TABLE_SIZE(EvBuff),	&tblEvH,	NULL,		TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);

	// component not initialized
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, EvBuff, TABLE_SIZE(EvBuff), &tblEvH,	AssocArr,	TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_NotInitialized);
	CU_ASSERT_EQUAL(Cwsw_EvQ__Init(), 0);

	// no event table
    result = Cwsw_EvQX__InitEvQX(&EvQX,	NULL,	EvBuff, TABLE_SIZE(EvBuff),	&tblEvH,	AssocArr,	TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_BadTable);

	// no event buffer
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, NULL,	TABLE_SIZE(EvBuff),	&tblEvH,	AssocArr,	TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_BadEvBuffer);

	// bad event table size
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv,	EvBuff, 0,					&tblEvH,	AssocArr,	TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_BadEvBuffer);	// this is different cuzza onaccounta thefactdat we allow zero-sized tables @ initialization time.
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, EvBuff, -2,					&tblEvH,	AssocArr,	TABLE_SIZE(AssocArr));	CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);

	// bad event-handler association size
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, EvBuff, TABLE_SIZE(EvBuff),	&tblEvH,	AssocArr,	0);						CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, EvBuff, TABLE_SIZE(EvBuff),	&tblEvH,	AssocArr,	-2);					CU_ASSERT_EQUAL(result, kErr_EvQ_BadParm);
}

void testCwsw_EvQX__InitEvQ_goodparams(void)
{
	tErrorCodes_EvQ			result;
	/* pre-initialize structs so we can observe changes resulting from init call */
    tEvQ_QueueCtrlEx		EvQX			= {
		.EvQ_Ctrl = {
			.pEventTable = NULL,
			.Queue_Count = 10,
			.idxWrite = 9,
			.idxRead = 8
		},
		.pEvHndlrs = NULL
	};
	tEvQ_EvTable			tblEv			= {
		.pEvBuffer = NULL,
		.szEvTbl = 99,
		.validity = 0xA5A5
	};
    tEvQ_Event				EvBuff[15]		= {0};	// room for 15 events in the queue
    tEvQ_EvHndlrAssocTable	tblEvH			= {
		.pEvtHndlrLut = NULL,
		.szEvtHandlerTbl = 123,
		.validity = 0x5A5A
	};
	tEvHA_EvHandlerAssoc	AssocArr[10]	= {0};	// room for 10 defined event handlers

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

    result = Cwsw_EvQX__InitEvQX(&EvQX,	&tblEv, EvBuff, TABLE_SIZE(EvBuff), &tblEvH,	AssocArr,	TABLE_SIZE(AssocArr));
    CU_ASSERT_EQUAL(result, kErr_EvQ_NoError);
	CU_ASSERT_PTR_EQUAL(EvQX.EvQ_Ctrl.pEventTable, &tblEv);
	CU_ASSERT_PTR_EQUAL(EvQX.EvQ_Ctrl.pEventTable->pEvBuffer, EvBuff);
	CU_ASSERT_EQUAL(    EvQX.EvQ_Ctrl.pEventTable->szEvTbl, TABLE_SIZE(EvBuff));
	CU_ASSERT_EQUAL(	EvQX.EvQ_Ctrl.pEventTable->validity, kRT_TBL_VALID);
	CU_ASSERT_EQUAL(	EvQX.EvQ_Ctrl.Queue_Count, 0);
	CU_ASSERT_EQUAL(	EvQX.EvQ_Ctrl.idxWrite, 0);
	CU_ASSERT_EQUAL(	EvQX.EvQ_Ctrl.idxRead, 0);

	CU_ASSERT_PTR_EQUAL(EvQX.pEvHndlrs, &tblEvH);
	/* for the next line, i'm getting a segment fault that i cannot trace down. since we've already
	 * confirmed that the correct table of handlers has been attached to our control struct, now
	 * inspect that table directly to confirm that it was initialized correctly.
	 */
	CU_ASSERT_PTR_EQUAL(EvQX.pEvHndlrs->pEvtHndlrLut, AssocArr);
	CU_ASSERT_PTR_EQUAL(tblEvH.pEvtHndlrLut, AssocArr);
	CU_ASSERT_EQUAL(    tblEvH.szEvtHandlerTbl, TABLE_SIZE(AssocArr));
	CU_ASSERT_EQUAL(    tblEvH.validity, kRT_TBL_VALID);
}


void testCwsw_EvQX__FlushEvents_badparams(void)
{
	/* this test case replicates almost exactly, the foundational test case against the same method
	 * in a "standard" event queue.
	 */
	tErrorCodes_EvQ			result;
	tEvQ_Event			tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 },
		{ 9, 415 }, { 0, 100 },
		{ 7, 207 }, { 8, 414 },
		{ 3, 103 }, { 4, 204 },
		{ 1, 101 }, { 2, 102 },
	};
	tEvQ_EvTable			evTbl	= {0};
    tEvQ_QueueCtrlEx		evqx	= {0};

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// no event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__FlushEvents(NULL)), kErr_EvQ_BadEvQ);

	// uninitialized event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__FlushEvents(&evqx)), kErr_EvQ_BadTable);

	// uninitialized event table
	evqx.EvQ_Ctrl.pEventTable = &evTbl;
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__FlushEvents(&evqx)), kErr_EvQ_BadEvBuffer);

	// zero-size event table
	evTbl.pEvBuffer = tblEventBuff;
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__FlushEvents(&evqx)), kErr_EvQ_BadEvBuffer);

	evTbl.szEvTbl = TABLE_SIZE(tblEventBuff);
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__FlushEvents(&evqx)), kErr_EvQ_BadTable);
}

void testCwsw_EvQX__FlushEvents_goodparams(void)
{
	tEvQ_Event tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 },
		{ 9, 415 }, { 0, 100 },
		{ 7, 207 }, { 8, 414 },
		{ 3, 103 }, { 4, 204 },
		{ 1, 101 }, { 2, 102 },
	};
	tEvQ_EvTable evTbl = {tblEventBuff, TABLE_SIZE(tblEventBuff), kCT_TBL_VALID};
    tEvQ_EvHndlrAssocTable	tblEvH = {
		.pEvtHndlrLut = NULL,
		.szEvtHandlerTbl = 123,
		.validity = 0x5A5A
	};
    tEvQ_QueueCtrlEx evqx = {
		.EvQ_Ctrl = {
			.pEventTable = &evTbl,
			.Queue_Count = 10,
			.idxRead = 5,	// arbitrary value set up so we can observe the behavior of the flush action
			.idxWrite = 6	// arbitrary value set up so we can observe the behavior of the flush action
		},
		.pEvHndlrs = &tblEvH
	};

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);
	CU_ASSERT_EQUAL(Cwsw_EvQX__FlushEvents(&evqx), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evqx.EvQ_Ctrl.Queue_Count, 0);
	CU_ASSERT_EQUAL(evqx.EvQ_Ctrl.idxRead, 0);
	CU_ASSERT_EQUAL(evqx.EvQ_Ctrl.idxWrite, 0);
}


void testCwsw_EvQX__PostEvent_badparams(void)
{
	/* this test case replicates almost exactly, the foundational test case against the same method
	 * in a "standard" event queue.
	 */
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
	};
	tEvQ_EvTable		evTbl = {0};
    tEvQ_QueueCtrlEx	evqx = {0};
	tEvQ_Event			ev = {0};

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// no event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(NULL, ev)), kErr_EvQ_BadEvQ);

	// uninitialized event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_BadTable);

	// uninitialized event table
	evqx.EvQ_Ctrl.pEventTable = &evTbl;
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_BadEvBuffer);

	// zero-size event table
	evTbl.pEvBuffer = tblEventBuff;
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_BadEvBuffer);

	// invalid event table
	evTbl.szEvTbl = TABLE_SIZE(tblEventBuff);
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_BadTable);

	// full event buffer
	evTbl.validity = kRT_TBL_VALID;		// correct condition that led to the previous "failure"
	evqx.EvQ_Ctrl.Queue_Count = 11;		// bad number but >= table size. correction will be done upon retrieving an event.
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_QueueFull);

	// null event
	evqx.EvQ_Ctrl.Queue_Count = TABLE_SIZE(tblEventBuff) - 1;
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_BadEvent);
}

void testCwsw_EvQx__PostEvent_goodparams(void)
{
	/* this test case replicates almost exactly, the foundational test case against the same method
	 * in a "standard" event queue.
	 */
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
	};
	tEvQ_EvTable evTbl = {tblEventBuff, TABLE_SIZE(tblEventBuff), kCT_TBL_VALID};
    tEvQ_QueueCtrlEx evqx = {
		.EvQ_Ctrl = {
			.pEventTable = &evTbl,
			.Queue_Count = TABLE_SIZE(tblEventBuff) - 1,	// room for one more event
			.idxRead = 0,
			.idxWrite = -2	// intentionally bad value to observe self-correcting behavior.
		},
	};
	tEvQ_Event		ev = { __LINE__, __LINE__ };

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// bad write index (negative), expect to self-correct
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evqx.EvQ_Ctrl.Queue_Count, 10);
	CU_ASSERT_EQUAL(evqx.EvQ_Ctrl.idxWrite, 1);
	CU_ASSERT_EQUAL(tblEventBuff[0].evId, ev.evId);
	CU_ASSERT_EQUAL(tblEventBuff[0].evData, ev.evData);

	// bad write index (too large), expect to self-correct
	evqx.EvQ_Ctrl.idxWrite = 10;
	--evqx.EvQ_Ctrl.Queue_Count;	// still room for one event
	memset(&tblEventBuff[0], 0xFF, sizeof(tEvQ_Event));
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__PostEvent(&evqx, ev)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evqx.EvQ_Ctrl.Queue_Count, 10);
	CU_ASSERT_EQUAL(evqx.EvQ_Ctrl.idxWrite, 1);
	CU_ASSERT_EQUAL(tblEventBuff[0].evId, ev.evId);
	CU_ASSERT_EQUAL(tblEventBuff[0].evData, ev.evData);
}


static tEvQ_Event gev = {0};
static uint32_t evextra = 0;
static void EvHandlerFunc(tEvQ_Event ev, uint32_t extra)
{
	gev.evId = ev.evId;
	gev.evData = ev.evData;
	evextra = extra;
}
void testCwsw_EvQX__SetEvHandler(void)
{
	/* this test case replicates almost exactly, the foundational test case against the same method
	 * in the event-handler subcomponent.
	 */
    tErrorCodes_EvQ result;

	// event-handler association LUT; equiv. to "event buffer" in an event table.
	tEvHA_EvHandlerAssoc HndlrArray[10] = {0};
	// event handler association table
    tEvQ_EvHndlrAssocTable EvtHndlrTbl = {HndlrArray, TABLE_SIZE(HndlrArray), kCT_TBL_VALID + 1};	// <-- intentionally bad validation signature

	// extended event queue
    tEvQ_QueueCtrlEx evqx = {
		.EvQ_Ctrl = {0},
		.pEvHndlrs = &EvtHndlrTbl
	};

	// there's no component init for this component (yet). don't need to assert its initialization status.

	// no handler association table
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__SetEvHandler(NULL, 1, EvHandlerFunc)), kErr_EvQ_BadParm);

	// invalid table
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__SetEvHandler(&evqx, 1, EvHandlerFunc)), kErr_EvQ_BadParm);

	// invalid event id
	EvtHndlrTbl.validity = kRT_TBL_VALID;
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__SetEvHandler(&evqx, 0, EvHandlerFunc)), kErr_EvQ_BadParm);
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__SetEvHandler(&evqx, -1, EvHandlerFunc)), kErr_EvQ_BadParm);

	// nonexistent event id
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__SetEvHandler(&evqx, 13, EvHandlerFunc)), kErr_EvQ_BadParm);

	// successful association
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__SetEvHandler(&evqx, 1, EvHandlerFunc)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(HndlrArray[1].evId, 1);
	CU_ASSERT_PTR_EQUAL(HndlrArray[1].pEvHandler, EvHandlerFunc);

	// erase handler association
	CU_ASSERT_EQUAL((result = Cwsw_EvQX__SetEvHandler(&evqx, 1, NULL)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(HndlrArray[1].evId, 1);
	CU_ASSERT_PTR_EQUAL(HndlrArray[1].pEvHandler, NULL);
}


void testCwsw_EvQX__GetEvHandler(void)
{
	/* this test case replicates almost exactly, the foundational test case against the same method
	 * in the event-handler subcomponent.
	 */
    pEvQ_EvHandlerFunc result;
	// association array; equiv. to "event buffer" in an event table.
	tEvHA_EvHandlerAssoc HndlrArray[10] = {0};

	// event handler association table
    tEvQ_EvHndlrAssocTable EvtHndlrTbl = {HndlrArray, TABLE_SIZE(HndlrArray), kCT_TBL_VALID + 1};	// <-- intentionally bad validation signature

	// extended event queue
    tEvQ_QueueCtrlEx evqx = {
		.EvQ_Ctrl = {0},
		.pEvHndlrs = &EvtHndlrTbl
	};

	// there's no component init for this component (yet). don't need to assert its initialization status.

	// no handler association table
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvQX__GetEvHandler(NULL, 1)), NULL);

	// invalid table
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvQX__GetEvHandler(&evqx, 1)), NULL);

	// invalid event id
	EvtHndlrTbl.validity = kRT_TBL_VALID;
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvQX__GetEvHandler(&evqx, 0)), NULL);
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvQX__GetEvHandler(&evqx, -1)), NULL);

	// nonexistent event id
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvQX__GetEvHandler(&evqx, 13)), NULL);

	// successful association
	HndlrArray[1].pEvHandler = EvHandlerFunc;
	CU_ASSERT_PTR_EQUAL((result = Cwsw_EvQX__GetEvHandler(&evqx, 1)), EvHandlerFunc);
}

void testCwsw_EvQX__HandleNextEvent(void)
{
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {	/* pre-load event buffer w/ events */
		{ 5, 205 }, { 6, 206 },
		{ 9, 415 }, { 0, 100 },		/* remember, event ID 0 is reserved for the null event */
		{ 7, 207 }, { 8, 414 },
		{ 3, 103 }, { 4, 204 },
		{ 1, 101 }, { 2, 102 },
		{10, 101 }, {13, 102 },
		{11, 101 }, {14, 102 },
		{12, 101 }, {15, 102 }
	};
	tEvQ_EvTable evTbl = {
		.pEvBuffer = tblEventBuff,
		.szEvTbl = TABLE_SIZE(tblEventBuff),
		.validity = kCT_TBL_VALID
	};

	tEvHA_EvHandlerAssoc AssocArr[] = {	/* pre-load 10 event handlers, leaving more events than event handler associations allowed. this should simply mean that the excess events aren't handler-able */
		{ 0, EvHandlerFunc},	/* remember, event ID 0 is reserved (null event), and we're using event ID as an index into the event handler table */
		{ 1, EvHandlerFunc},
		{ 2, EvHandlerFunc},
		{ 3, EvHandlerFunc},
		{ 4, EvHandlerFunc},
		{ 5, EvHandlerFunc},
		{ 6, EvHandlerFunc},
		{ 7, EvHandlerFunc},
		{ 8, EvHandlerFunc},
		{ 9, EvHandlerFunc},
		{10, EvHandlerFunc}
	};
	tEvQ_EvHndlrAssocTable	tblEvH = {
		.pEvtHndlrLut = AssocArr,
		.szEvtHandlerTbl = TABLE_SIZE(AssocArr),
		.validity = kCT_TBL_VALID
	};

	tEvQ_QueueCtrlEx evqx = {
		.EvQ_Ctrl = {
			.pEventTable = &evTbl,
			.Queue_Count = TABLE_SIZE(tblEventBuff),
			.idxWrite = TABLE_SIZE(tblEventBuff),
			.idxRead = TABLE_SIZE(tblEventBuff)
		},
		.pEvHndlrs = &tblEvH
	};

	tEvQ_Event			ev = {0};
	pEvQ_EvHandlerFunc	pf;
	uint32_t			extra = __LINE__;

	int idx = 0;
	while(evqx.EvQ_Ctrl.Queue_Count)
	{
		// reminder: this implementation uses the event ID as an index into the table of event
		//	handlers; should this change, the method used here to determine if this is an associable
		//	event or not will need also to change.
		if(	(tblEventBuff[idx].evId) && (tblEventBuff[idx].evId < TABLE_SIZE(AssocArr)))	// if our event is the null event, or is larger than the number of associations, use alternate path
		{
			CU_ASSERT_EQUAL((result =	Cwsw_EvQX__HandleNextEvent(&evqx, extra + idx)), kErr_EvQ_NoError);
			CU_ASSERT_EQUAL(gev.evId,	tblEventBuff[idx].evId);
			CU_ASSERT_EQUAL(gev.evData,	tblEventBuff[idx].evData);
			CU_ASSERT_EQUAL(evextra,	extra + idx);
		}
		else
		{
			CU_ASSERT_EQUAL((result = Cwsw_EvQX__HandleNextEvent(&evqx, extra + idx)), kErr_EvQ_NoAssociation);
		}
		++idx;
	}
	CU_ASSERT_EQUAL(idx, evTbl.szEvTbl);
}
