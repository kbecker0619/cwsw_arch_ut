#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/bc57e8e8/cwsw_event.o \
	${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable.o \
	${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue.o \
	${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler.o \
	${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex.o \
	${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc.o \
	${OBJECTDIR}/_ext/511dfd52/CritSect.o \
	${OBJECTDIR}/_ext/511dfd52/main.o \
	${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f5

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/_ext/a7dd4220/EvQ_CUnit_Main.o \
	${TESTDIR}/_ext/a7dd4220/cwsw_event_test.o \
	${TESTDIR}/_ext/a7dd4220/cwsw_eventtable_test.o \
	${TESTDIR}/_ext/a7dd4220/cwsw_evhandler_test.o \
	${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_ex_test.o \
	${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_test.o \
	${TESTDIR}/_ext/a7dd4220/cwsw_evthndlrassoc_test.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproject.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproject.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nbproject ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/bc57e8e8/cwsw_event.o: ../../cwsw_event/src/cwsw_event.c
	${MKDIR} -p ${OBJECTDIR}/_ext/bc57e8e8
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bc57e8e8/cwsw_event.o ../../cwsw_event/src/cwsw_event.c

${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable.o: ../../cwsw_event/src/cwsw_eventtable.c
	${MKDIR} -p ${OBJECTDIR}/_ext/bc57e8e8
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable.o ../../cwsw_event/src/cwsw_eventtable.c

${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue.o: ../../cwsw_evqueue/src/cwsw_evqueue.c
	${MKDIR} -p ${OBJECTDIR}/_ext/2d710c0e
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue.o ../../cwsw_evqueue/src/cwsw_evqueue.c

${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler.o: ../../cwsw_evqueue_ex/src/cwsw_evhandler.c
	${MKDIR} -p ${OBJECTDIR}/_ext/e9efbc4e
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler.o ../../cwsw_evqueue_ex/src/cwsw_evhandler.c

${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex.o: ../../cwsw_evqueue_ex/src/cwsw_evqueue_ex.c
	${MKDIR} -p ${OBJECTDIR}/_ext/e9efbc4e
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex.o ../../cwsw_evqueue_ex/src/cwsw_evqueue_ex.c

${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc.o: ../../cwsw_evqueue_ex/src/cwsw_evthndlrassoc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/e9efbc4e
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc.o ../../cwsw_evqueue_ex/src/cwsw_evthndlrassoc.c

${OBJECTDIR}/_ext/511dfd52/CritSect.o: ../app/CritSect.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/CritSect.o ../app/CritSect.c

${OBJECTDIR}/_ext/511dfd52/main.o: ../app/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/main.o ../app/main.c

${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o: ../libs/cwsw_lib/src/cwsw_lib.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccfc345
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o ../libs/cwsw_lib/src/cwsw_lib.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f5: ${TESTDIR}/_ext/a7dd4220/EvQ_CUnit_Main.o ${TESTDIR}/_ext/a7dd4220/cwsw_event_test.o ${TESTDIR}/_ext/a7dd4220/cwsw_eventtable_test.o ${TESTDIR}/_ext/a7dd4220/cwsw_evhandler_test.o ${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_ex_test.o ${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_test.o ${TESTDIR}/_ext/a7dd4220/cwsw_evthndlrassoc_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS}   -lcunit 


${TESTDIR}/_ext/a7dd4220/EvQ_CUnit_Main.o: ../ut/tests/EvQ_CUnit_Main.c 
	${MKDIR} -p ${TESTDIR}/_ext/a7dd4220
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a7dd4220/EvQ_CUnit_Main.o ../ut/tests/EvQ_CUnit_Main.c


${TESTDIR}/_ext/a7dd4220/cwsw_event_test.o: ../ut/tests/cwsw_event_test.c 
	${MKDIR} -p ${TESTDIR}/_ext/a7dd4220
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a7dd4220/cwsw_event_test.o ../ut/tests/cwsw_event_test.c


${TESTDIR}/_ext/a7dd4220/cwsw_eventtable_test.o: ../ut/tests/cwsw_eventtable_test.c 
	${MKDIR} -p ${TESTDIR}/_ext/a7dd4220
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a7dd4220/cwsw_eventtable_test.o ../ut/tests/cwsw_eventtable_test.c


${TESTDIR}/_ext/a7dd4220/cwsw_evhandler_test.o: ../ut/tests/cwsw_evhandler_test.c 
	${MKDIR} -p ${TESTDIR}/_ext/a7dd4220
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a7dd4220/cwsw_evhandler_test.o ../ut/tests/cwsw_evhandler_test.c


${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_ex_test.o: ../ut/tests/cwsw_evqueue_ex_test.c 
	${MKDIR} -p ${TESTDIR}/_ext/a7dd4220
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_ex_test.o ../ut/tests/cwsw_evqueue_ex_test.c


${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_test.o: ../ut/tests/cwsw_evqueue_test.c 
	${MKDIR} -p ${TESTDIR}/_ext/a7dd4220
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a7dd4220/cwsw_evqueue_test.o ../ut/tests/cwsw_evqueue_test.c


${TESTDIR}/_ext/a7dd4220/cwsw_evthndlrassoc_test.o: ../ut/tests/cwsw_evthndlrassoc_test.c 
	${MKDIR} -p ${TESTDIR}/_ext/a7dd4220
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a7dd4220/cwsw_evthndlrassoc_test.o ../ut/tests/cwsw_evthndlrassoc_test.c


${OBJECTDIR}/_ext/bc57e8e8/cwsw_event_nomain.o: ${OBJECTDIR}/_ext/bc57e8e8/cwsw_event.o ../../cwsw_event/src/cwsw_event.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/bc57e8e8
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/bc57e8e8/cwsw_event.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bc57e8e8/cwsw_event_nomain.o ../../cwsw_event/src/cwsw_event.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/bc57e8e8/cwsw_event.o ${OBJECTDIR}/_ext/bc57e8e8/cwsw_event_nomain.o;\
	fi

${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable_nomain.o: ${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable.o ../../cwsw_event/src/cwsw_eventtable.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/bc57e8e8
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable_nomain.o ../../cwsw_event/src/cwsw_eventtable.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable.o ${OBJECTDIR}/_ext/bc57e8e8/cwsw_eventtable_nomain.o;\
	fi

${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue_nomain.o: ${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue.o ../../cwsw_evqueue/src/cwsw_evqueue.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2d710c0e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue_nomain.o ../../cwsw_evqueue/src/cwsw_evqueue.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue.o ${OBJECTDIR}/_ext/2d710c0e/cwsw_evqueue_nomain.o;\
	fi

${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler_nomain.o: ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler.o ../../cwsw_evqueue_ex/src/cwsw_evhandler.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/e9efbc4e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler_nomain.o ../../cwsw_evqueue_ex/src/cwsw_evhandler.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler.o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evhandler_nomain.o;\
	fi

${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex_nomain.o: ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex.o ../../cwsw_evqueue_ex/src/cwsw_evqueue_ex.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/e9efbc4e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex_nomain.o ../../cwsw_evqueue_ex/src/cwsw_evqueue_ex.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex.o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evqueue_ex_nomain.o;\
	fi

${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc_nomain.o: ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc.o ../../cwsw_evqueue_ex/src/cwsw_evthndlrassoc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/e9efbc4e
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc_nomain.o ../../cwsw_evqueue_ex/src/cwsw_evthndlrassoc.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc.o ${OBJECTDIR}/_ext/e9efbc4e/cwsw_evthndlrassoc_nomain.o;\
	fi

${OBJECTDIR}/_ext/511dfd52/CritSect_nomain.o: ${OBJECTDIR}/_ext/511dfd52/CritSect.o ../app/CritSect.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/511dfd52/CritSect.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/CritSect_nomain.o ../app/CritSect.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/511dfd52/CritSect.o ${OBJECTDIR}/_ext/511dfd52/CritSect_nomain.o;\
	fi

${OBJECTDIR}/_ext/511dfd52/main_nomain.o: ${OBJECTDIR}/_ext/511dfd52/main.o ../app/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/511dfd52
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/511dfd52/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511dfd52/main_nomain.o ../app/main.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/511dfd52/main.o ${OBJECTDIR}/_ext/511dfd52/main_nomain.o;\
	fi

${OBJECTDIR}/_ext/4ccfc345/cwsw_lib_nomain.o: ${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o ../libs/cwsw_lib/src/cwsw_lib.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccfc345
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -Wall -DXPRJ_NB_${CND_CONF}=1 -I../cfg -I../../cwsw_event/inc -I../../cwsw_evqueue/inc -I../../cwsw_evqueue_ex/inc -I../libs/cwsw_lib/inc -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccfc345/cwsw_lib_nomain.o ../libs/cwsw_lib/src/cwsw_lib.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/4ccfc345/cwsw_lib.o ${OBJECTDIR}/_ext/4ccfc345/cwsw_lib_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f5 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
