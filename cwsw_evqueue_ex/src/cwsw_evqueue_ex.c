/** @file
 *	@brief	Methods for the Event Queue Extended component.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 15, 2020
 *	Author: kevin
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_evqueue_ex.h"


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

// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** Initialize an Event Queue (Extended) object from scratch.
 *
 *	@param[out]	pEvQX		EvQX object being ultimately initialized.
 *	@param[out]	ptblEv		Event Table member of the EvQ object.
 *	@param[in]	pEvBuff		Event Table buffer; actual storage for queued events.
 *	@param[in]	szEvBuf		Size of Event Table buffer, in number of elements.
 *	@param[out]	ptblEvH		Event Handler Association table member of the EvQX object.
 *	@param[in]	pAssocArr	Event Handler association array.
 *	@param[in]	szAssocArr	Size of Event Handler association array, in number of elements.
 *
 *	@return		Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@note Does not clear (or otherwise initialize) the table of queued events,
 *	or the Event Handler Association lookup table.
 *
 *	@ingroup tEvQ_QueueCtrlEx
 */
tErrorCodes_EvQ
Cwsw_EvQX__InitEvQX(
	// Event Queue Extended component.
	ptEvQ_QueueCtrlEx 		pEvQX,
		// Event Queue component and its members.
		ptEvQ_EvTable ptblEv, ptEvQ_Event pEvBuff, const size_t szEvBuf,
		// Event Handler Association elements.
		ptEvQ_EvHndlrAssocTable ptblEvH, ptEvHA_EvHandlerAssoc pAssocArr, size_t szAssocArr
) {
	tErrorCodes_EvQ rc = kErr_EvQ_NotInitialized;
	if(!pEvQX)		{ return kErr_EvQ_BadParm; }	// no event queue
	if(!ptblEvH)	{ return kErr_EvQ_BadParm; }	// no event handler association table
	if(!pAssocArr)	{ return kErr_EvQ_BadParm; }	// no event handler storage array

	// initialize member EvQ (embedded struct)
	rc = Cwsw_EvQ__InitEvQ(&pEvQX->EvQ_Ctrl, ptblEv, pEvBuff, szEvBuf);
	if(rc)			{ return rc; }

	// initialize member Ev Handler Association table (pointer), then the struct pointed to
	pEvQX->pEvHndlrs = ptblEvH;
	return Cwsw_EvHA__InitEventHandlerTable(ptblEvH, pAssocArr, szAssocArr);
}


/**	Clear (empty) the event queue (EvQX version).
 *
 *  @param[in,out]	pEvQX	Event Queue Extended object.
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@ingroup tEvQ_QueueCtrlEx
 */
tErrorCodes_EvQ
Cwsw_EvQX__FlushEvents(ptEvQ_QueueCtrlEx pEvQX)
{
	// check preconditions, in order of priority
	if(!pEvQX) { return kErr_EvQ_BadEvQ; }
	return Cwsw_EvQ__FlushEvents(&pEvQX->EvQ_Ctrl);
}


/** Get an event from the Event Queue (EvQX version).
 * 	Destructive read from the event buffer.
 *	Always writes to the event parameter, except if queue is presently empty.
 *
 *	@param[in,out]	pEvQX	Extended Event Queue. Control metadata is updated during this method's operation.
 *	@param[out]		pEv		Event retrieved. Cleared if event buffer is empty.
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@ingroup tEvQ_QueueCtrlEx
 */
tErrorCodes_EvQ
Cwsw_EvQX__GetEvent(ptEvQ_QueueCtrlEx pEvQX, ptEvQ_Event pEv)
{
	if(!pEvQX) { return kErr_EvQ_BadEvQ; }
	return Cwsw_EvQ__GetEvent(&pEvQX->EvQ_Ctrl, pEv);
}


/** Post an event ID.
 * 	This is a "convenience" wrapper so that the client doesn't have to allocate & manage an event
 * 	object, but can simply post the event ID itself.
 *
 *	@param [inout]	pEvQX	Extended event queue into which to post event.
 *	@param [in]		evId	Event ID to post.
 *	@returns	Error code from the "real" PostEvent function.
 */
tErrorCodes_EvQ
Cwsw_EvQX__PostEventId(ptEvQ_QueueCtrlEx pEvQX, tEvQ_EventID evId)
{
	tEvQ_Event ev;
	ev.evId = evId;
	ev.evData = 0;
	return Cwsw_EvQX__PostEvent(pEvQX, ev);
}


/**	Posts an event into the queue.
 *
 *	@param[in,out]	pEvQX	Extended Event Queue object to which to add the event.
 *	@param[in]		ev		Event to add to the queue.
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@ingroup tEvQ_QueueCtrlEx
 */
tErrorCodes_EvQ
Cwsw_EvQX__PostEvent(ptEvQ_QueueCtrlEx pEvQX, tEvQ_Event ev)
{
	if(!pEvQX) { return kErr_EvQ_BadEvQ; }
	return Cwsw_EvQ__PostEvent(&pEvQX->EvQ_Ctrl, ev);
}


/** Set the association between an Event ID and a handler for that event.
 *
 *	@param[in,out]	pEvQX		Event Handler Association object.
 *	@param[in]		evId		Event ID to which to "attach" the handler.
 *	@param[in]		pHndlrFunc	Event handler.
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@note This works at the level of the Event Handler Association table, not at the EvQX level.
 *	@ingroup tEvQ_QueueCtrlEx
 */
tErrorCodes_EvQ
Cwsw_EvQX__SetEvHandler(ptEvQ_QueueCtrlEx pEvQX, tEvQ_EventID evId, ptEvQ_EvHandlerFunc pHndlrFunc)
{
	if(!pEvQX) { return kErr_EvQ_BadParm; }
	return Cwsw_EvHA__SetEvHandler(pEvQX->pEvHndlrs, evId, pHndlrFunc);
}


/** Get the address of the registered event handler for event ID \<n\>.
 *
 *	@param[in,out]	pEvQX		Event Handler Association object.
 *	@param[in]		evId		Event ID to which to "attach" the handler.
 *
 *	@return Address of the handler function, or NULL for failure.
 *
 *	@note This works at the level of the Event Handler Association table, not at the EvQX level.
 *	@ingroup tEvQ_QueueCtrlEx
 */
ptEvQ_EvHandlerFunc
Cwsw_EvQX__GetEvHandler(ptEvQ_QueueCtrlEx pEvQX, tEvQ_EventID evId)
{
	if(!pEvQX) { return NULL; }
	return Cwsw_EvHA__GetEvHandler(pEvQX->pEvHndlrs, evId);
}


/** Execute the handler for the next event in the queue.
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *	@note	A success return code only means that there was an handler associated with the next
 *			event in the queue, and it was called and returned.
 *	@ingroup tEvQ_QueueCtrlEx
 */
tErrorCodes_EvQ
Cwsw_EvQX__HandleNextEvent(ptEvQ_QueueCtrlEx pEvQX, uint32_t ExtraData)
{
	tErrorCodes_EvQ rc;
	tEvQ_Event ev = {0};
	ptEvQ_EvHandlerFunc pf;

	if(!pEvQX)						{ return kErr_EvQ_BadParm; }
	rc = Cwsw_EvQX__GetEvent(pEvQX, &ev);
	if(kErr_EvQ_NoError != rc)		{ return rc; }

	pf = Cwsw_EvHA__GetEvHandler(pEvQX->pEvHndlrs, ev.evId);
	if(pf)
	{
		pf(ev, ExtraData);
		return kErr_EvQ_NoError;
	}

	return kErr_EvQ_NoAssociation;
}
