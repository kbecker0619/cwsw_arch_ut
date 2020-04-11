/*
 * File:   cwsw_evhandler_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:18:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "cwsw_evhandler.h"
#include "cwsw_evqueue_ex_tests.h"


static tEvQ_Event gev = {0};
static uint32_t evextra = 0;
static void EvHandlerFunc(tEvQ_Event ev, uint32_t extra)
{
	gev.evId = ev.evId;
	gev.evData = ev.evData;
	evextra = extra;
}


void testCwsw_EvQ__RegisterHandler(void)
{
    tErrorCodes_EvQ result;
	// association array; equiv. to "event buffer" in an event table.
	tEvHA_EvHandlerAssoc HndlrArray[10] = {0};
	// event handler association table
//	tEvQ_EvHndlrAssocTable EvtHndlrTbl = {HndlrArray, TABLE_SIZE(HndlrArray), kCT_TBL_VALID + 1};	// <-- intentionally bad validation signature

    pEvQ_EvHandlerFunc pf = NULL;

	// no handler association table
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__RegisterHandler(NULL, TABLE_SIZE(HndlrArray), 1, pf)), kErr_EvQ_BadParm);
	// invalid table
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__RegisterHandler(HndlrArray, TABLE_SIZE(HndlrArray), 1, pf)), kErr_EvQ_NoError);
	// invalid event id
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__RegisterHandler(HndlrArray, TABLE_SIZE(HndlrArray), 0, pf)), kErr_EvQ_BadParm);
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__RegisterHandler(HndlrArray, TABLE_SIZE(HndlrArray), -2, pf)), kErr_EvQ_BadParm);
	// nonexistent event id
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__RegisterHandler(HndlrArray, TABLE_SIZE(HndlrArray), 13, pf)), kErr_EvQ_BadParm);

	// successful registration (in our usage, basically a synonym for successful association of handler to event id)
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__RegisterHandler(HndlrArray, TABLE_SIZE(HndlrArray), 1, EvHandlerFunc)), kErr_EvQ_BadParm);
	// erase handler association
	CU_ASSERT_EQUAL((result = Cwsw_EvQ__RegisterHandler(HndlrArray, TABLE_SIZE(HndlrArray), 1, pf)), kErr_EvQ_BadParm);
}

pEvQ_EvHandlerFunc Cwsw_EvQ__GetHandler(ptEvHA_EvHandlerAssoc pEvHndlr, size_t evtblsz, tEvQ_EventID ev);

void testCwsw_EvQ__GetHandler()
{
    ptEvHA_EvHandlerAssoc pEvHndlr = NULL;
    size_t evtblsz = 0UL;
    tEvQ_EventID ev = 0;
    pEvQ_EvHandlerFunc result = Cwsw_EvQ__GetHandler(pEvHndlr, evtblsz, ev);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}
