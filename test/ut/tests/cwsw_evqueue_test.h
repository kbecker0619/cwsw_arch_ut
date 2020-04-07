/* File:   cwsw_evqueue_test.h
 * Author: kevin
 *
 * Created on April 9, 2020, 8:29 AM
 */

#ifndef CWSW_EVQUEUE_TEST__H
#define CWSW_EVQUEUE_TEST__H

#ifdef __cplusplus
extern "C"
{
#endif

/* CUnit function prototypes */
extern void testCwsw_Evt__Init(void);
extern void testCwsw_EvT__Deinit(void);
extern void testCwsw_Evt__InitEventTable_badparams(void);
extern void testCwsw_Evt__InitEventTable_goodparams(void);
extern void testCwsw_Evt__GetEventPtr_badparams(void);
extern void testCwsw_Evt__GetEventPtr_goodparams(void);
extern void testCwsw_Evt__GetEvent_badparams(void);
extern void testCwsw_Evt__GetEvent_goodparams(void);
extern void testCwsw_Evt__PutEvent_badparams(void);
extern void testCwsw_Evt__PutEvent_goodparams(void);
extern void testCwsw_EvQ__Init(void);
extern void testCwsw_EvQ__InitEvQ_badparams(void);
extern void testCwsw_EvQ__InitEvQ_goodparams(void);
extern void testCwsw_EvQ__FlushEvents_badparams(void);
extern void testCwsw_EvQ__FlushEvents_goodparams(void);
extern void testCwsw_EvQ__PostEvent_badparams(void);
extern void testCwsw_EvQ__PostEvent_goodparams(void);
extern void testCwsw_EvQ__GetEvent_badparams();
extern void testCwsw_EvQ__GetEvent_goodparams();


#ifdef __cplusplus
}
#endif

#endif /* CWSW_EVQUEUE_TEST__H */
