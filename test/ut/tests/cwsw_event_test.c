/*
 * File:   cwsw_event_test.c
 * Author: kevin
 *
 * Created on Apr 4, 2020, 6:05:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "cwsw_event.h"


/*
 * CUnit Test Suite
 */
uint16_t Cwsw_Evt__Init();

void testCwsw_Evt__Init()
{
    uint16_t result = Cwsw_Evt__Init();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

void Cwsw_EvT__Deinit();

void testCwsw_EvT__Deinit()
{
    Cwsw_EvT__Deinit();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}

_Bool Cwsw_EvT__Get_Initialized();

void testCwsw_EvT__Get_Initialized()
{
    _Bool result = Cwsw_EvT__Get_Initialized();
    if (1 /*check result*/)
    {
        CU_ASSERT(0);
    }
}
