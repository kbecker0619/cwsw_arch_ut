/*
 * File:   cwsw_evhandler_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:18:09 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "cwsw_event.h"     /* tErrorCodes_EvQ */
#include "cwsw_evthndlrassoc.h" /* ptEvQ_EvHndlrAssocTable */

/*
 * CUnit Test Suite
 */

tErrorCodes_EvQ Cwsw_EvQ__RegisterHandler(ptEvQ_EvHandlerAssoc pEvHndlrTbl, size_t evtblsz, tEvQ_EventID ev, pEvQ_EvHandlerFunc pf);

void testCwsw_EvQ__RegisterHandler()
{
    ptEvQ_EvHandlerAssoc pEvHndlrTbl;
    size_t evtblsz;
    tEvQ_EventID ev;
    pEvQ_EvHandlerFunc pf;
    tErrorCodes_EvQ result = Cwsw_EvQ__RegisterHandler(pEvHndlrTbl, evtblsz, ev, pf);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

pEvQ_EvHandlerFunc Cwsw_EvQ__GetHandler(ptEvQ_EvHandlerAssoc pEvHndlr, size_t evtblsz, tEvQ_EventID ev);

void testCwsw_EvQ__GetHandler()
{
    ptEvQ_EvHandlerAssoc pEvHndlr;
    size_t evtblsz;
    tEvQ_EventID ev;
    pEvQ_EvHandlerFunc result = Cwsw_EvQ__GetHandler(pEvHndlr, evtblsz, ev);
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}
