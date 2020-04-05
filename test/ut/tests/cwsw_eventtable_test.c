/*
 * File:   cwsw_eventtable_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:07:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "cwsw_eventtable.h"


/*
 * CUnit Test Suite
 */

tErrorCodes_EvQ Cwsw_Evt__InitEventTable(ptEvQ_EvTable pEvQTable, ptEvQ_Event pTable, size_t TableSize);

void testCwsw_Evt__InitEventTable()
{
    ptEvQ_EvTable pEvQTable;
    ptEvQ_Event pTable;
    size_t TableSize;
    tErrorCodes_EvQ result = Cwsw_Evt__InitEventTable(pEvQTable, pTable, TableSize);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

ptEvQ_Event Cwsw_Evt__GetEventPtr(ptEvQ_EvTable pEvTbl, tEvQ_EvtHandle hnd);

void testCwsw_Evt__GetEventPtr()
{
    ptEvQ_EvTable pEvTbl;
    tEvQ_EvtHandle hnd;
    ptEvQ_Event result = Cwsw_Evt__GetEventPtr(pEvTbl, hnd);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_Evt__GetEvent(ptEvQ_Event pEv, ptEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd);

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
