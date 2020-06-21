/** @file
 *	@brief	One-sentence short description of file.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 9, 2020
 *	Author: Kevin
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <limits.h>		/* INT_MAX */

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_evthndlrassoc.h"


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

/**	Return a handle to a specified event in the event-handler association table.
 *	- This instantiation uses the event ID as an index into the association table;
 *	therefore, it is important that all event IDs be contiguous and non-negative.
 *	- Since in this system, event ID zero is reserved, this means index 0 of this
 *	association array will not be used.
 *
 *	@ingroup tEvQ_EvHndlrAssocTable
 */
static tEvQ_EvtHandle
GetTableHandle(ptEvQ_EvHndlrAssocTable pHndlrTbl, tEvQ_EventID evId)
{
	// for this implementation, the event is used as an index into the LUT
	if(!pHndlrTbl)								{ return -1; }
	if( (pHndlrTbl->validity == kCT_TBL_VALID) ||
		(pHndlrTbl->validity == kRT_TBL_VALID) )
	{
		if(evId >= pHndlrTbl->szEvtHandlerTbl)	{ return -1; }
		if(evId < 1)							{ return -1; }
		return (tEvQ_EvtHandle)evId;
	}

	return -1;
}


// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** "Constructor" for an Event Handler association.
 * 	This connects an event ID with its handler.
 *	This function works at the level of the Event Handler Association object.
 *
 *	@param[out]	pEvtHndlrTbl	Event Handler Association table to be initialized.
 *	@param[in]	pHndlrArray		Reference to the buffer that holds the actual event associations.
 *	@param[in]	szHndlrArray	Size of the handler array in number of elements.
 *
 *	@returns	Error code, where `0` (#kErr_EvQ_NoError) is no error.
 *				In the event of an error return, no writes to any output parameter are performed.
 *
 *	@ingroup tEvQ_EvHndlrAssocTable
 */
tErrorCodes_EvQ
Cwsw_EvHA__InitEventHandlerTable(
	ptEvQ_EvHndlrAssocTable pEvtHndlrTbl,
	ptEvHA_EvHandlerAssoc pHndlrArray,
	size_t szHndlrArray)
{
	if(!pEvtHndlrTbl)			return kErr_EvQ_BadParm;		// no handler association table
	if(!pHndlrArray)			return kErr_EvQ_BadParm;		// no association array
	if(szHndlrArray > INT_MAX)	return kErr_EvQ_BadParm;		// bad table size
	if(szHndlrArray < 1)		return kErr_EvQ_BadParm;		// bad table size

	pEvtHndlrTbl->pEvtHndlrLut		= pHndlrArray;
	pEvtHndlrTbl->szEvtHandlerTbl	= (int32_t)szHndlrArray;
	pEvtHndlrTbl->validity			= kRT_TBL_VALID;			// indicate initialization by init function (as opposed to compile-time initialization)

	return kErr_EvQ_NoError;
}


/** Set the association between an Event ID and a handler for that event.
 *
 *	@param[in,out]	pHndlrTbl	Event Handler Association object.
 *	@param[in]		evId		Event ID to which to "attach" the handler.
 *	@param[in]		pHndlrFunc	Event handler.
 *
 *	@returns Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	@note	This works at the level of the Event Handler Association table, not at the EvQX level.
 *	@note	In this design, we're using a value derived from the Event ID as an index into a table.
 *			Because of this, we expect that all defined IDs are contiguous, and are all positive.
 *
 *	@ingroup tEvQ_EvHndlrAssocTable
 */
tErrorCodes_EvQ
Cwsw_EvHA__SetEvHandler(
	ptEvQ_EvHndlrAssocTable pHndlrTbl,
	tEvQ_EventID evId,
	ptEvQ_EvHandlerFunc pHndlrFunc)
{
	tEvQ_EvtHandle hnd = GetTableHandle(pHndlrTbl, evId);
	if(hnd < 1)	{ return kErr_EvQ_BadParm; }				// not completely accurate return code, but MVP for now. could return more precise error codes if we did our own examination of the parameters.

	// set event
	pHndlrTbl->pEvtHndlrLut[hnd].evId = evId;
	// set handler
	pHndlrTbl->pEvtHndlrLut[hnd].pEvHandler = pHndlrFunc;

	return kErr_EvQ_NoError;
}


/** Get the address of the registered event handler for event ID \<n\>.
 *
 *	@param[in]	pHndlrTbl	Event Handler array.
 *	@param[in]	evId		Event ID to which to "attach" the handler.
 *
 *	@return Address of the handler function, or NULL for failure.
 *
 *	@note This works at the level of the Event Handler Association table, not at the EvQX level.
 *	@ingroup tEvQ_EvHndlrAssocTable
 */
ptEvQ_EvHandlerFunc
Cwsw_EvHA__GetEvHandler(ptEvQ_EvHndlrAssocTable pHndlrTbl,	tEvQ_EventID evId)
{
	tEvQ_EvtHandle hnd = GetTableHandle(pHndlrTbl, evId);	// validates both association table as well as event id
	if(hnd < 1)	{ return NULL; }

	// at this time, no confirmation of event ID (it could be thought of that this confirmation was done in the GetTableHandle() call above)
	return pHndlrTbl->pEvtHndlrLut[hnd].pEvHandler;
}
