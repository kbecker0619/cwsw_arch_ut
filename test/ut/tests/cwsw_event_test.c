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


void testCwsw_Evt__Init()
{
    CU_ASSERT_EQUAL(Cwsw_Evt__Init(), 0);
    CU_ASSERT_EQUAL(Cwsw_Evt__Get_Initialized(), true);
}

void testCwsw_EvT__Deinit()
{
    Cwsw_Evt__Deinit();
    CU_ASSERT_EQUAL(Cwsw_Evt__Get_Initialized(), false);
}
