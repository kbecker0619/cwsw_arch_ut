/*
 * File:   cwsw_evqueue_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:11:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "cwsw_evqueue.h"


/*
 * CUnit Test Suite
 */

uint16_t Cwsw_EvQ__Init();

void testCwsw_EvQ__Init()
{
    uint16_t result = Cwsw_EvQ__Init();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

_Bool Cwsw_EvQ__Get_Initialized();

void testCwsw_EvQ__Get_Initialized()
{
    _Bool result = Cwsw_EvQ__Get_Initialized();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQ__InitEvQ(ptEvQ_QueueCtrl pEvQ, ptEvQ_EvTable pEvTable, ptEvQ_Event pEvBuff, size_t szEvBuf);

void testCwsw_EvQ__InitEvQ()
{
    ptEvQ_QueueCtrl pEvQ;
    ptEvQ_EvTable pEvTable;
    ptEvQ_Event pEvBuff;
    size_t szEvBuf;
    tErrorCodes_EvQ result = Cwsw_EvQ__InitEvQ(pEvQ, pEvTable, pEvBuff, szEvBuf);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQ__FlushEvents(ptEvQ_QueueCtrl pEvQueueCtrl);

void testCwsw_EvQ__FlushEvents()
{
    ptEvQ_QueueCtrl pEvQueueCtrl;
    tErrorCodes_EvQ result = Cwsw_EvQ__FlushEvents(pEvQueueCtrl);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQ__PostEvent(ptEvQ_QueueCtrl pEvQueueCtrl, tEvQ_Event ev);

void testCwsw_EvQ__PostEvent()
{
    ptEvQ_QueueCtrl pEvQueueCtrl;
    tEvQ_Event ev;
    tErrorCodes_EvQ result = Cwsw_EvQ__PostEvent(pEvQueueCtrl, ev);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQ__GetEvent(ptEvQ_QueueCtrl pEvQ, ptEvQ_Event pEv);

void testCwsw_EvQ__GetEvent()
{
    ptEvQ_QueueCtrl pEvQ;
    ptEvQ_Event pEv;
    tErrorCodes_EvQ result = Cwsw_EvQ__GetEvent(pEvQ, pEv);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}
