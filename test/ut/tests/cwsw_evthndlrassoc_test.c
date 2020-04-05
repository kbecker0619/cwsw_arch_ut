/*
 * File:   cwsw_evthndlrassoc_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 7:00:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "cwsw_evthndlrassoc.h"


/*
 * CUnit Test Suite
 */

tErrorCodes_EvQ Cwsw_EvHA__InitEventHandlerTable(ptEvQ_EvHndlrAssocTable EvtHndlrTbl, ptEvQ_EvHandlerAssoc HndlrArray, size_t szHndlrArray);

void testCwsw_EvHA__InitEventHandlerTable()
{
    ptEvQ_EvHndlrAssocTable EvtHndlrTbl;
    ptEvQ_EvHandlerAssoc HndlrArray;
    size_t szHndlrArray;
    tErrorCodes_EvQ result = Cwsw_EvHA__InitEventHandlerTable(EvtHndlrTbl, HndlrArray, szHndlrArray);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvHA__SetEvHandler(ptEvQ_EvHndlrAssocTable pHndlrTbl, tEvQ_EventID evId, pEvQ_EvHandlerFunc pHndlrFunc);

void testCwsw_EvHA__SetEvHandler()
{
    ptEvQ_EvHndlrAssocTable pHndlrTbl;
    tEvQ_EventID evId;
    pEvQ_EvHandlerFunc pHndlrFunc;
    tErrorCodes_EvQ result = Cwsw_EvHA__SetEvHandler(pHndlrTbl, evId, pHndlrFunc);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

pEvQ_EvHandlerFunc Cwsw_EvHA__GetEvHandler(ptEvQ_EvHndlrAssocTable pHndlrTbl, tEvQ_EventID evId);

void testCwsw_EvHA__GetEvHandler()
{
    ptEvQ_EvHndlrAssocTable pHndlrTbl;
    tEvQ_EventID evId;
    pEvQ_EvHandlerFunc result = Cwsw_EvHA__GetEvHandler(pHndlrTbl, evId);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}
