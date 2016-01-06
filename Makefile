#
# OMNeT++/OMNEST Makefile for bici_simu
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I../inet/src/util -I../inet/src/networklayer/common -I../inet/src/linklayer/contract -I../inet/src/base -I../inet/src/mobility -I../inet/src/networklayer/contract -I../MiXiM/src/base/utils -I../inet/src/mobility/models -I../MiXiM/src/base/modules -I../MiXiM/src -I../MiXiM/src/base -I../MiXiM/src/base/phyLayer -I../MiXiM/src/base/connectionManager -I../MiXiM/src/base/messages -L../inet/out/$$\(CONFIGNAME\)/src -L../MiXiM/out/$$\(CONFIGNAME\)/src -linet -lmixim -DINET_IMPORT -KINET_PROJ=../inet -KMIXIM_PROJ=../MiXiM
#

# Name of target to be created (-o option)
TARGET = bici_simu$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../inet/src/util \
    -I../inet/src/networklayer/common \
    -I../inet/src/linklayer/contract \
    -I../inet/src/base \
    -I../inet/src/mobility \
    -I../inet/src/networklayer/contract \
    -I../MiXiM/src/base/utils \
    -I../inet/src/mobility/models \
    -I../MiXiM/src/base/modules \
    -I../MiXiM/src \
    -I../MiXiM/src/base \
    -I../MiXiM/src/base/phyLayer \
    -I../MiXiM/src/base/connectionManager \
    -I../MiXiM/src/base/messages \
    -I. \
    -Isrc \
    -Isrc/modules \
    -Isrc/modules/application \
    -Isrc/modules/messages \
    -Isrc/modules/mobility \
    -Isrc/modules/mobility/models \
    -Isrc/modules/nodes \
    -Isrc/networks \
    -Isrc/networks/scenario1 \
    -Isrc/networks/scenario1/results

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../inet/out/$(CONFIGNAME)/src -L../MiXiM/out/$(CONFIGNAME)/src  -linet -lmixim
LIBS += -Wl,-rpath,`abspath ../inet/out/$(CONFIGNAME)/src` -Wl,-rpath,`abspath ../MiXiM/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/src/modules/application/CustomAppLayer.o \
    $O/src/modules/application/NodeInfo.o \
    $O/src/modules/application/MyTestAppLayer.o \
    $O/src/modules/mobility/models/CustomMovingMobilityBase.o \
    $O/src/modules/mobility/models/CustomRectangleMobility.o \
    $O/src/modules/mobility/models/CustomLinearMobility.o \
    $O/src/modules/mobility/models/CustomMobilityAccess.o \
    $O/src/modules/messages/CustomApplPkt_m.o

# Message files
MSGFILES = \
    src/modules/messages/CustomApplPkt.msg

# Other makefile variables (-K)
INET_PROJ=../inet
MIXIM_PROJ=../MiXiM

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f bici_simu bici_simu.exe libbici_simu.so libbici_simu.a libbici_simu.dll libbici_simu.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f src/*_m.cc src/*_m.h
	$(Q)-rm -f src/modules/*_m.cc src/modules/*_m.h
	$(Q)-rm -f src/modules/application/*_m.cc src/modules/application/*_m.h
	$(Q)-rm -f src/modules/messages/*_m.cc src/modules/messages/*_m.h
	$(Q)-rm -f src/modules/mobility/*_m.cc src/modules/mobility/*_m.h
	$(Q)-rm -f src/modules/mobility/models/*_m.cc src/modules/mobility/models/*_m.h
	$(Q)-rm -f src/modules/nodes/*_m.cc src/modules/nodes/*_m.h
	$(Q)-rm -f src/networks/*_m.cc src/networks/*_m.h
	$(Q)-rm -f src/networks/scenario1/*_m.cc src/networks/scenario1/*_m.h
	$(Q)-rm -f src/networks/scenario1/results/*_m.cc src/networks/scenario1/results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc src/*.cc src/modules/*.cc src/modules/application/*.cc src/modules/messages/*.cc src/modules/mobility/*.cc src/modules/mobility/models/*.cc src/modules/nodes/*.cc src/networks/*.cc src/networks/scenario1/*.cc src/networks/scenario1/results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/modules/application/CustomAppLayer.o: src/modules/application/CustomAppLayer.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	src/modules/application/CustomAppLayer.h \
	src/modules/application/MyTestAppLayer.h \
	src/modules/application/NodeInfo.h \
	src/modules/messages/CustomApplPkt_m.h \
	src/modules/mobility/models/CustomLinearMobility.h \
	src/modules/mobility/models/CustomMobilityAccess.h \
	src/modules/mobility/models/CustomMovingMobilityBase.h \
	src/modules/mobility/models/CustomRectangleMobility.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityAccess.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/src/modules/application/MyTestAppLayer.o: src/modules/application/MyTestAppLayer.cc \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/MiximBatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/NetwControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	src/modules/application/MyTestAppLayer.h \
	src/modules/messages/CustomApplPkt_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h
$O/src/modules/application/NodeInfo.o: src/modules/application/NodeInfo.cc \
	src/modules/application/NodeInfo.h
$O/src/modules/messages/CustomApplPkt_m.o: src/modules/messages/CustomApplPkt_m.cc \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	src/modules/messages/CustomApplPkt_m.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/linklayer/contract/MACAddress.h
$O/src/modules/mobility/models/CustomLinearMobility.o: src/modules/mobility/models/CustomLinearMobility.cc \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	src/modules/mobility/models/CustomLinearMobility.h \
	src/modules/mobility/models/CustomMovingMobilityBase.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/src/modules/mobility/models/CustomMobilityAccess.o: src/modules/mobility/models/CustomMobilityAccess.cc \
	src/modules/mobility/models/CustomLinearMobility.h \
	src/modules/mobility/models/CustomMobilityAccess.h \
	src/modules/mobility/models/CustomMovingMobilityBase.h \
	src/modules/mobility/models/CustomRectangleMobility.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/src/modules/mobility/models/CustomMovingMobilityBase.o: src/modules/mobility/models/CustomMovingMobilityBase.cc \
	src/modules/mobility/models/CustomMovingMobilityBase.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/util/FWMath.h
$O/src/modules/mobility/models/CustomRectangleMobility.o: src/modules/mobility/models/CustomRectangleMobility.cc \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	src/modules/mobility/models/CustomMovingMobilityBase.h \
	src/modules/mobility/models/CustomRectangleMobility.h \
	$(INET_PROJ)/src/base/BasicModule.h \
	$(INET_PROJ)/src/base/Coord.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/base/INotifiable.h \
	$(INET_PROJ)/src/base/ModuleAccess.h \
	$(INET_PROJ)/src/base/NotificationBoard.h \
	$(INET_PROJ)/src/base/NotifierConsts.h \
	$(INET_PROJ)/src/mobility/IMobility.h \
	$(INET_PROJ)/src/mobility/models/MobilityBase.h \
	$(INET_PROJ)/src/util/FWMath.h

