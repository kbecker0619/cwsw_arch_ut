/*
 * File:   cwsw_evqueue_ex_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:22:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "cwsw_evqueue_ex.h"

/*
 * CUnit Test Suite
 */

tErrorCodes_EvQ Cwsw_EvQX__InitEvQ(ptEvQ_QueueCtrlEx pEvQX, ptEvQ_EvTable ptblEv, ptEvQ_Event pEvBuff, size_t szEvBuf, ptEvQ_EvHndlrAssocTable ptblEvH, ptEvQ_EvHandlerAssoc pAssocArr, size_t szAssocArr);

void testCwsw_EvQX__InitEvQ()
{
    ptEvQ_QueueCtrlEx pEvQX;
    ptEvQ_EvTable ptblEv;
    ptEvQ_Event pEvBuff;
    size_t szEvBuf;
    ptEvQ_EvHndlrAssocTable ptblEvH;
    ptEvQ_EvHandlerAssoc pAssocArr;
    size_t szAssocArr;
    tErrorCodes_EvQ result = Cwsw_EvQX__InitEvQ(pEvQX, ptblEv, pEvBuff, szEvBuf, ptblEvH, pAssocArr, szAssocArr);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQX__FlushEvents(ptEvQ_QueueCtrlEx pEvQX);

void testCwsw_EvQX__FlushEvents()
{
    ptEvQ_QueueCtrlEx pEvQX;
    tErrorCodes_EvQ result = Cwsw_EvQX__FlushEvents(pEvQX);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQX__GetEvent(ptEvQ_QueueCtrlEx pEvQX, ptEvQ_Event pEv);

void testCwsw_EvQX__GetEvent()
{
    ptEvQ_QueueCtrlEx pEvQX;
    ptEvQ_Event pEv;
    tErrorCodes_EvQ result = Cwsw_EvQX__GetEvent(pEvQX, pEv);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQX__PostEvent(ptEvQ_QueueCtrlEx pEvQX, tEvQ_Event ev);

void testCwsw_EvQX__PostEvent()
{
    ptEvQ_QueueCtrlEx pEvQX;
    tEvQ_Event ev;
    tErrorCodes_EvQ result = Cwsw_EvQX__PostEvent(pEvQX, ev);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQX__SetEvHandler(ptEvQ_QueueCtrlEx pEvQX, tEvQ_EventID evId, pEvQ_EvHandlerFunc pHndlrFunc);

void testCwsw_EvQX__SetEvHandler()
{
    ptEvQ_QueueCtrlEx pEvQX;
    tEvQ_EventID evId;
    pEvQ_EvHandlerFunc pHndlrFunc;
    tErrorCodes_EvQ result = Cwsw_EvQX__SetEvHandler(pEvQX, evId, pHndlrFunc);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

pEvQ_EvHandlerFunc Cwsw_EvQX__GetEvHandler(ptEvQ_QueueCtrlEx pEvQX, tEvQ_EventID evId);

void testCwsw_EvQX__GetEvHandler()
{
    ptEvQ_QueueCtrlEx pEvQX;
    tEvQ_EventID evId;
    pEvQ_EvHandlerFunc result = Cwsw_EvQX__GetEvHandler(pEvQX, evId);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

tErrorCodes_EvQ Cwsw_EvQX__HandleNextEvent(ptEvQ_QueueCtrlEx pEvQX, uint32_t ExtraData);

void testCwsw_EvQX__HandleNextEvent()
{
    ptEvQ_QueueCtrlEx pEvQX;
    uint32_t ExtraData;
    tErrorCodes_EvQ result = Cwsw_EvQX__HandleNextEvent(pEvQX, ExtraData);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}
