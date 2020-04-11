/* File:   cwsw_evqueue_ex_tests.h
 * Author: kevin
 *
 * Created on April 9, 2020, 8:29 PM
 */

#ifndef CWSW_EVQUEUE_EX_TESTS_H
#define CWSW_EVQUEUE_EX_TESTS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* CUnit function prototypes */
extern void testCwsw_EvHA__InitEventHandlerTable(void);
extern void testCwsw_EvHA__SetEvHandler(void);
extern void testCwsw_EvHA__GetEvHandler(void);

extern void testCwsw_EvQ__RegisterHandler(void);

extern void testCwsw_EvQX__InitEvQ_badparams(void);
extern void testCwsw_EvQX__InitEvQ_goodparams(void);
extern void testCwsw_EvQX__FlushEvents_badparams(void);
extern void testCwsw_EvQX__FlushEvents_goodparams(void);
extern void testCwsw_EvQX__PostEvent_badparams(void);
extern void testCwsw_EvQx__PostEvent_goodparams(void);
extern void testCwsw_EvQX__SetEvHandler(void);
extern void testCwsw_EvQX__GetEvHandler(void);
extern void testCwsw_EvQX__HandleNextEvent(void);


#ifdef __cplusplus
}
#endif

#endif /* CWSW_EVQUEUE_EX_TESTS_H */

