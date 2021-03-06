/** @file
 *	@brief	Event Queue component definitions and methods.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Mar 1, 2018
 *	@author Kevin L. Becker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdbool.h>
#include <stddef.h>		/* ssize_t */

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_evqueue.h"


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

static bool initialized = false;


// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** Initialize the Event Queue component.
 *
 *	This function is intended to be called during the application-initialization
 *	phase, and is only the 1st initialization function that needs to be called.
 *
 *	Because this component is a superclass of an Event Table, we'll ensure that subcomponent is
 *	also initialized.
 *
 *	@returns	Error code, where 0 is no error.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
uint16_t
Cwsw_EvQ__Init(void)
{
	uint16_t ret = kErr_EvQ_NoError;
	if( (XPRJ_Win_MinGW_Debug) || (XPRJ_Lin_GCC_Debug) || (XPRJ_Win_MSVC_Debug) )
	{
		SUPPRESS_EXTRAISO_IDENT;	/* suppress warning for function name */

		dbg_printf(
				"\tModule ID %i\t%s\t\n"
				"\tEntering %s()\n\n",
				Cwsw_EvQ, __FILE__,
				__FUNCTION__);

		RESTORE_WARNING_CONTEXT;
	}
	else
	{
	}

	if(!Get(Cwsw_Evt, Initialized))
	{
		ret = Init(Cwsw_Evt);
	}

	if(!ret)
	{
		initialized = true;
	}
	return ret;
}

/** Deinitialize this component.
 *	Contrary to the Init function, which ensures that dependencies are initialized, this de-init
 *	function controls only this component.
 *
 *	Even though this specific instantiation doesn't really do anything, it is a standard member of
 *	most CWSW components and may do something in other components. We want the API to be consistent
 *	across components.
 */
void
Cwsw_EvQ__Deinit(void)
{
	initialized = false;
}

/**	Target for Get(Cwsw_EvQ, Initialized) API.
 *
 *	@returns	true if component is initialized.
 *	@returns	false if the component is not initialized.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
bool
Cwsw_EvQ__Get_Initialized(void)
{
	return initialized;
}


/** Initialize an Event Queue (meaning specifically, the control structure for an event queue).
 *
 *	Each queue in your system needs initialization: The management functions
 *	need to know the size of this event buffer, and where the buffer is located.
 *
 * 	@param[out]	pEvQ		Reference to the Event Queue.
 *	@param[in]	pEvTable	Pointer to the event table object.
 *							This is an independent object, not embedded into the EvQ control structure.
 *	@param[in]	pEvBuff		Event table buffer.
 *	@param[in]	szEvBuf		Size of Event Table buffer.
 *
 *	@returns			Error code, where 0 (#kErr_EvQ_NoError) is no error. In the event of an
 *						error return, no writes to any output parameter are performed.
 *
 *	It is the responsibility of the caller to ensure the validity of the buffer
 *	and control struct.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__InitEvQ(
		ptEvQ_QueueCtrl	pEvQ,		//!< Event Queue member of the EvQX object.
		ptEvQ_EvTable	pEvTable,	//!< Event Table member of the EvQ object.
		ptEvQ_Event		pEvBuff,	//!< Event Table buffer; actual storage for queued events.
		size_t			szEvBuf		//!< Size of Event Table buffer, in number of elements.
	)
{
	tErrorCodes_EvQ rc = kErr_EvQ_NotInitialized;

	// check preconditions, in order of priority
	if(!initialized)	return kErr_EvQ_NotInitialized; 	// has component init happened?
	if(!pEvQ)			return kErr_EvQ_BadEvQ; 			// is evq control structure valid?
	if(!pEvTable)		return kErr_EvQ_BadTable; 			// is event table valid?
	if(!pEvBuff)		return kErr_EvQ_BadEvBuffer; 		// is event buffer valid?
	if(!szEvBuf)		return kErr_EvQ_BadEvBuffer; 		// is event buffer valid? (while the event component itself allows zero-size tables, we don't)

	rc = Cwsw_Evt__InitEventTable(pEvTable, pEvBuff, szEvBuf);
	if(rc)				return rc;

	pEvQ->pEventTable	= pEvTable;
	pEvQ->Queue_Count	= 0;
	pEvQ->idxRead		= 0;
	pEvQ->idxWrite		= 0;
	return kErr_EvQ_NoError;
}


/**	Clear (empty) the event queue.
 *
 *  While there might be a number of reasons why the developer may want to
 *  empty the current queue of all pending events, one important opportunity is
 *  at module initialization.
 *
 *  @param[in,out]	pEvQ	Event Queue object.
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__FlushEvents(ptEvQ_QueueCtrl pEvQ)
{
	// check preconditions, in order of priority
	if(!initialized)					{ return kErr_EvQ_NotInitialized; }
	if(!pEvQ) 							{ return kErr_EvQ_BadEvQ; }
	if(!pEvQ->pEventTable)				{ return kErr_EvQ_BadTable; }
	if(!pEvQ->pEventTable->pEvBuffer)	{ return kErr_EvQ_BadEvBuffer; }
	if(!pEvQ->pEventTable->szEvTbl)		{ return kErr_EvQ_BadEvBuffer; }
	if( (kCT_TBL_VALID == pEvQ->pEventTable->validity) || (kRT_TBL_VALID == pEvQ->pEventTable->validity) )
	{
		pEvQ->idxRead = 0;
		pEvQ->idxWrite = 0;
		pEvQ->Queue_Count = 0;
		return kErr_EvQ_NoError;
	}
	return kErr_EvQ_BadTable;
}


/**	Posts an event into the queue.
 *
 *	@param[in,out]	pEvQ	Pointer to the current control structure.
 *	@param[in]		ev		Event to add to the queue. Note that an ID of 0 is disallowed (reserved event).
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__PostEvent(ptEvQ_QueueCtrl pEvQ, tEvQ_Event ev)
{
	tErrorCodes_EvQ rc = kErr_EvQ_NoError;
	bool isthereroom;

	// check preconditions, in order of priority
	if(!initialized)					{ return kErr_EvQ_NotInitialized; }
	if(!pEvQ)							{ return kErr_EvQ_BadEvQ; }
	if(!pEvQ->pEventTable)				{ return kErr_EvQ_BadTable; }
	if(!pEvQ->pEventTable->pEvBuffer)	{ return kErr_EvQ_BadEvBuffer; }
	if(!pEvQ->pEventTable->szEvTbl)		{ return kErr_EvQ_BadEvBuffer; }
	if(!( (kCT_TBL_VALID == pEvQ->pEventTable->validity) || (kRT_TBL_VALID == pEvQ->pEventTable->validity) ))	{ return kErr_EvQ_BadTable; }

	isthereroom = (pEvQ->Queue_Count < pEvQ->pEventTable->szEvTbl);
	if(!isthereroom)					{ return kErr_EvQ_QueueFull; }

	if(!ev.evId)						{ return kErr_EvQ_BadEvent; }

	do {
		tEvQ_EvtHandle idx = 0;
		int crit = Cwsw_Critical_Protect(0);

		/* validate the current write index. recall that the evq is owned by the caller, and since
		 * we have no control over it, we need to ensure that the main operating parameters are
		 * correct.
		 */
		if( (pEvQ->idxWrite < 0) || (pEvQ->idxWrite >= pEvQ->pEventTable->szEvTbl) )	{ pEvQ->idxWrite = 0; }

		// get the index of the current event to write, increment to point to the next write
		//	we don't ever expect to have an index > INT_MAX
		idx = pEvQ->idxWrite++;

		// account for buffer  wrap-around
		if( pEvQ->idxWrite >= pEvQ->pEventTable->szEvTbl)	{ pEvQ->idxWrite = 0; }

		// add the item to the queue
		rc = Cwsw_Evt__PutEvent(pEvQ->pEventTable, idx, &ev);

		// adjust the count
		++pEvQ->Queue_Count;

		crit = Cwsw_Critical_Release(crit);
	} while(0);

	return rc;
}


/** Get an event from the Event Queue.
 * 	Destructive read from the event buffer.
 *	Always writes to the event parameter, except if queue is presently empty.
 *
 *	@param[in,out]	pEvQ	Event Queue. Control metadata is updated during this method's operation.
 *	@param[out]		pEv		Event retrieved. Cleared if event buffer is empty.
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__GetEvent(ptEvQ_QueueCtrl pEvQ, ptEvQ_Event pEv)
{
	tErrorCodes_EvQ rc = kErr_EvQ_NoError;
	tEvQ_EvtHandle idx = 0;
	int crit = 0;

	// check preconditions, in order of priority
	if(!initialized)					{ return kErr_EvQ_NotInitialized; }
	if(!pEvQ)							{ return kErr_EvQ_BadEvQ; }			// no event queue
	if(!pEvQ->pEventTable)				{ return kErr_EvQ_BadTable; }		// no event table
	if(!pEvQ->pEventTable->pEvBuffer)	{ return kErr_EvQ_BadEvBuffer;}		// uninitialized event table
	if(pEvQ->pEventTable->szEvTbl < 1)	{ return kErr_EvQ_BadEvBuffer; }	// event table of no size
	if(!pEv)							{ return kErr_EvQ_BadParm; }		// null event
	if(pEvQ->Queue_Count < 1)			{ return kErr_EvQ_QueueEmpty; }		// empty queue, nothing to get
	if(!( (kCT_TBL_VALID == pEvQ->pEventTable->validity) || (kRT_TBL_VALID == pEvQ->pEventTable->validity) ))	{ return kErr_EvQ_BadTable; }	// invalid event table

	Cwsw_EvT__InitEvent(pEv);

	crit = Cwsw_Critical_Protect(0);	// protect the evq control structure.

	/* validate the current write index. recall that the evq is owned by the caller, and since
	 * we have no control over it, we need to ensure that the main operating parameters are
	 * correct.
	 */
	if( (pEvQ->idxRead < 0) || (pEvQ->idxRead >= pEvQ->pEventTable->szEvTbl) )	{ pEvQ->idxRead = 0; }

	// get the index of the current event to read, increment to point to the next read
	//	we don't ever expect to have an index > INT_MAX
	idx = pEvQ->idxRead++;

	// still updating for the next read, correct for buffer wrap-around
	if(pEvQ->idxRead > pEvQ->pEventTable->szEvTbl)	{ pEvQ->idxRead = 0; }

	// retrieve the event
	rc = Cwsw_Evt__GetEvent(pEv, pEvQ->pEventTable, idx);

	// decrement the count
	--pEvQ->Queue_Count;
	crit = Cwsw_Critical_Release(crit);

	// return the event
	return rc;
}

