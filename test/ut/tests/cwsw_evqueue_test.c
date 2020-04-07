/*
 * File:   cwsw_evqueue_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:11:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>			/* memset() */
#include <CUnit/Basic.h>

#include "cwsw_evqueue.h"
#include "cwsw_evqueue_test.h"


void testCwsw_EvQ__Init(void)
{
	CU_ASSERT_EQUAL(Cwsw_EvQ__Get_Initialized(), false);
	CU_ASSERT_EQUAL(Cwsw_EvQ__Init(), 0);
	CU_ASSERT_EQUAL(Cwsw_EvQ__Get_Initialized(), true);
	CU_ASSERT_EQUAL(Get(Cwsw_Evt, Initialized), true);
	CU_ASSERT_EQUAL(Cwsw_EvQ__Init(), 0);
	Cwsw_EvQ__Deinit();
}

void testCwsw_EvQ__InitEvQ_badparams(void)
{
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	/* compile-time configuration of the event table.
	 * note a successful call to InitEvQ that specifies this same event queue will overwrite this configuration.
	 */
	tEvQ_EvTable evTbl = {0};	// {tblEventBuff, TABLE_SIZE(tblEventBuff), kCT_TBL_VALID};
	tEvQ_QueueCtrl evq = {0};

	// event component not initialized
	Cwsw_EvQ__Deinit();		// ensure startup condition is as expected
	result = Cwsw_EvQ__InitEvQ(NULL, &evTbl, tblEventBuff, TABLE_SIZE(tblEventBuff));
	CU_ASSERT_EQUAL(result, kErr_EvQ_NotInitialized);

	// no event queue
	CU_ASSERT_EQUAL(Cwsw_EvQ__Init(), 0);	// formally tested in the init test above; this assert is only to ensure it "works" b/c the rest of this test case relies on the initialization.
	result = Cwsw_EvQ__InitEvQ(NULL, &evTbl, tblEventBuff, TABLE_SIZE(tblEventBuff));
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadEvQ);

	// no event table
	result = Cwsw_EvQ__InitEvQ(&evq, NULL, tblEventBuff, TABLE_SIZE(tblEventBuff));
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadTable);

	// no event buffer
	result = Cwsw_EvQ__InitEvQ(&evq, &evTbl, NULL, TABLE_SIZE(tblEventBuff));
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadEvBuffer);

	// bad event table size
	result = Cwsw_EvQ__InitEvQ(&evq, &evTbl, tblEventBuff, 0);
	CU_ASSERT_EQUAL(result, kErr_EvQ_BadEvBuffer);
}

void testCwsw_EvQ__InitEvQ_goodparams(void)
{
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {tblEventBuff, TABLE_SIZE(tblEventBuff), kCT_TBL_VALID};
	tEvQ_QueueCtrl evq = {0};

	result = Cwsw_EvQ__InitEvQ(&evq, &evTbl, tblEventBuff, TABLE_SIZE(tblEventBuff));
	CU_ASSERT_EQUAL(result, kErr_EvQ_NoError);
	CU_ASSERT_PTR_EQUAL(evq.pEventTable, &evTbl);
	CU_ASSERT_EQUAL(evq.pEventTable->validity, kRT_TBL_VALID);	// confirm run-time initialization has superseded compile-time init
}


void testCwsw_EvQ__FlushEvents_badparams(void)
{
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_QueueCtrl evq = {0};
	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// no event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__FlushEvents(NULL)), kErr_EvQ_BadEvQ);

	// uninitialized event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__FlushEvents(&evq)), kErr_EvQ_BadTable);

	// uninitialized event table
	evq.pEventTable = &evTbl;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__FlushEvents(&evq)), kErr_EvQ_BadEvBuffer);

	// zero-size event table
	evTbl.pEvBuffer = tblEventBuff;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__FlushEvents(&evq)), kErr_EvQ_BadEvBuffer);

	// invalid event table (is this important for the action? probably more checks are better than fewer)
	evTbl.szEvTbl = TABLE_SIZE(tblEventBuff);
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__FlushEvents(&evq)), kErr_EvQ_BadTable);
}

void testCwsw_EvQ__FlushEvents_goodparams(void)
{
	tEvQ_Event tblEventBuff[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {tblEventBuff, TABLE_SIZE(tblEventBuff), kCT_TBL_VALID};
    tEvQ_QueueCtrl evq = {
		.pEventTable = &evTbl,
		.Queue_Count = 10,
		.idxRead = 5,	// arbitrary value set up so we can observe the behavior of the flush action
		.idxWrite = 6	// arbitrary value set up so we can observe the behavior of the flush action
	};

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);
	CU_ASSERT_EQUAL(Cwsw_EvQ__FlushEvents(&evq), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evq.Queue_Count, 0);
	CU_ASSERT_EQUAL(evq.idxRead, 0);
	CU_ASSERT_EQUAL(evq.idxWrite, 0);
}


void testCwsw_EvQ__PostEvent_badparams(void)
{
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
	};
	tEvQ_EvTable	evTbl = {0};
    tEvQ_QueueCtrl	evq = {0};
	tEvQ_Event		ev = {0};

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// no event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(NULL, ev)), kErr_EvQ_BadEvQ);

	// uninitialized event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_BadTable);

	// uninitialized event table
	evq.pEventTable = &evTbl;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_BadEvBuffer);

	// zero-size event table
	evTbl.pEvBuffer = tblEventBuff;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_BadEvBuffer);

	// invalid event table
	evTbl.szEvTbl = TABLE_SIZE(tblEventBuff);
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_BadTable);

	// full event buffer
	evTbl.validity = kRT_TBL_VALID;	// correct condition that led to the previous "failure"
	evq.Queue_Count = 11;			// bad number but >= table size. correction will be done upon retrieving an event.
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_QueueFull);

	// null event
	evq.Queue_Count = TABLE_SIZE(tblEventBuff) - 1;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_BadEvent);
}

void testCwsw_EvQ__PostEvent_goodparams(void)
{
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
	};
	tEvQ_EvTable evTbl = {tblEventBuff, TABLE_SIZE(tblEventBuff), kCT_TBL_VALID};
    tEvQ_QueueCtrl evq = {
		.pEventTable = &evTbl,
		.Queue_Count = TABLE_SIZE(tblEventBuff) - 1,	// room for one more event
		.idxRead = 0,
		.idxWrite = -2	// intentionally bad value to observe self-correcting behavior.
	};
	tEvQ_Event		ev = { __LINE__, __LINE__ };

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// bad write index (negative), expect to self-correct
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evq.Queue_Count, 10);
	CU_ASSERT_EQUAL(evq.idxWrite, 1);
	CU_ASSERT_EQUAL(tblEventBuff[0].evId, ev.evId);
	CU_ASSERT_EQUAL(tblEventBuff[0].evData, ev.evData);

	// bad write index (too large), expect to self-correct
	evq.idxWrite = 10;
	evq.Queue_Count--;	// still room for one event
	memset(&tblEventBuff[0], 0xFF, sizeof(tEvQ_Event));
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__PostEvent(&evq, ev)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evq.Queue_Count, 10);
	CU_ASSERT_EQUAL(evq.idxWrite, 1);
	CU_ASSERT_EQUAL(tblEventBuff[0].evId, ev.evId);
	CU_ASSERT_EQUAL(tblEventBuff[0].evData, ev.evData);
}


void testCwsw_EvQ__GetEvent_badparams()
{
    tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
	};
	tEvQ_EvTable evTbl = {0};
    tEvQ_QueueCtrl evq = {0};
	tEvQ_Event		ev = {0};

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// no event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(NULL, &ev)), kErr_EvQ_BadEvQ);

	// uninitialized event queue
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_BadTable);

	// uninitialized event table
	evq.pEventTable = &evTbl;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_BadEvBuffer);

	// zero-size event table (initialize table size, leaving the validity field uninitialized)
	evTbl.pEvBuffer = tblEventBuff;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_BadEvBuffer);

	// null event
	evTbl.szEvTbl =	TABLE_SIZE(tblEventBuff);
	evq.Queue_Count = TABLE_SIZE(tblEventBuff);
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, NULL)), kErr_EvQ_BadParm);

	// invalid event table (still not initialized)
	evTbl.szEvTbl = TABLE_SIZE(tblEventBuff);
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_BadTable);

	// empty event buffer
	evTbl.validity = kRT_TBL_VALID;	// correct condition that led to the previous "failure"
	evq.Queue_Count = -1;
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_QueueEmpty);
}

// bad read pointer
void testCwsw_EvQ__GetEvent_goodparams()
{
	tErrorCodes_EvQ result;
	tEvQ_Event tblEventBuff[] = {
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
	};
	tEvQ_EvTable evTbl = {tblEventBuff, TABLE_SIZE(tblEventBuff), kCT_TBL_VALID};
    tEvQ_QueueCtrl evq = {
		.pEventTable = &evTbl,
		.Queue_Count = TABLE_SIZE(tblEventBuff),
		.idxRead = -2,	// intentionally bad value to observe self-correcting behavior.
		.idxWrite = 0
	};
	tEvQ_Event		ev = { __LINE__, __LINE__ };

	CU_ASSERT_EQUAL(Get(Cwsw_EvQ, Initialized), true);

	// read with an invalid (low) read index
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evq.Queue_Count, 9);
	CU_ASSERT_EQUAL(evq.idxRead, 1);
	CU_ASSERT_EQUAL(ev.evId, tblEventBuff[0].evId);
	CU_ASSERT_EQUAL(ev.evData, tblEventBuff[0].evData);

	// read with an invalid (high) read index
	evq.Queue_Count = TABLE_SIZE(tblEventBuff);
	evq.idxRead = TABLE_SIZE(tblEventBuff);
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_NoError);
	CU_ASSERT_EQUAL(evq.Queue_Count, 9);
	CU_ASSERT_EQUAL(evq.idxRead, 1);
	CU_ASSERT_EQUAL(ev.evId, tblEventBuff[0].evId);
	CU_ASSERT_EQUAL(ev.evData, tblEventBuff[0].evData);

	// deplete the remainder of the events from the queue.
	int idx = 1;
	while(evq.Queue_Count)
	{
		CU_ASSERT_EQUAL((result = Cwsw_EvQ__GetEvent(&evq, &ev)), kErr_EvQ_NoError);
		CU_ASSERT_EQUAL(ev.evId, tblEventBuff[idx].evId);
		CU_ASSERT_EQUAL(ev.evData, tblEventBuff[idx].evData);
		++idx;
	}
	CU_ASSERT_EQUAL(idx, 10);
}
