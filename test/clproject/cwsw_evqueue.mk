##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=cwsw_evqueue
ConfigurationName      :=Debug
WorkspacePath          :=C:/_Projects/cwsw_eventqueue/test/clproject
ProjectPath            :=C:/_Projects/cwsw_eventqueue/test/clproject
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=kevin
Date                   :=01/04/2020
CodeLitePath           :=D:/_Programs/CodeLite
LinkerName             :=//TSCLIENT/C/MinGW/bin/g++.exe
SharedObjectLinkerName :=//TSCLIENT/C/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="cwsw_evqueue.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=//TSCLIENT/C/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := //TSCLIENT/C/MinGW/bin/ar.exe rcu
CXX      := //TSCLIENT/C/MinGW/bin/g++.exe
CC       := //TSCLIENT/C/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := //TSCLIENT/C/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=D:\_Programs\CodeLite
Srcs=../../cwsw_evqueue_ex/src/cwsw_evqueue_ex.c ../../cwsw_event/src/cwsw_eventtable.c ../../cwsw_event/src/cwsw_event.c ../libs/cwsw_lib/src/cwsw_lib.c ../app/main.c ../../cwsw_evqueue_ex/src/cwsw_evhandler.c ../../cwsw_evqueue_ex/src/cwsw_evthndlrassoc.c ../../cwsw_evqueue/src/cwsw_evqueue.c ../app/CritSect.c 

Objects0=$(IntermediateDirectory)/up_up_cwsw_evqueue_ex_src_cwsw_evqueue_ex.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_cwsw_event_src_cwsw_eventtable.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_cwsw_event_src_cwsw_event.c$(ObjectSuffix) $(IntermediateDirectory)/up_libs_cwsw_lib_src_cwsw_lib.c$(ObjectSuffix) $(IntermediateDirectory)/up_app_main.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_cwsw_evqueue_ex_src_cwsw_evhandler.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_cwsw_evqueue_ex_src_cwsw_evthndlrassoc.c$(ObjectSuffix) $(IntermediateDirectory)/up_up_cwsw_evqueue_src_cwsw_evqueue.c$(ObjectSuffix) $(IntermediateDirectory)/up_app_CritSect.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(ConfigurationName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(ConfigurationName)"

PreBuild:
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


