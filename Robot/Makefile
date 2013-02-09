#UCPP makefile

# Default target
all: force
	cd PPC603gnu && exec $(MAKE) -f Makefile_linux

# Don't do anything for the "Makefile" target
Makefile: ;

# Recursively run all other targets
%: force
	cd PPC603gnu && exec $(MAKE) -f Makefile_linux "$*"

force: ;

CPP = $(TOOL_PATH)ccppc.exe
NM = $(TOOL_PATH)nmppc.exe
C_FLAGS = -g3 -O2 -fstrength-reduce -fno-builtin -ansi -Wall -MD -MP -fno-feature-proxy
INCLUDES = -I$(HOME)/.ucpp/gccdist/WindRiver/vxworks-6.3/target/h \
	-I$(HOME)/.ucpp/gccdist/WindRiver/vxworks-6.3/target/h/WPILib \
	-I$(HOME)/.ucpp/gccdist/WindRiver/vxworks-6.3/target/h/wrn/coreip 
ARCH = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
WPI_LIB = $(HOME)/.ucpp/gccdist/WindRiver/vxworks-6.3/target/lib/WPILib.a
TOOL_PATH = wine $(HOME)/.ucpp/gccdist/WindRiver/gnu/3.4.4-vxworks-6.3/x86-win32/bin/
DEFINES = -DCPU=PPC603 -D_WRS_KERNEL -DTOOL_FAMILY=gnu -DTOOL=gnu
SRCS = Accumulator.cpp AutonomousController.cpp DriveTrain.cpp Fafnir.cpp HumanController.cpp LinearVictor.cpp Robot.cpp Shooter.cpp
OBJS = $(SRCS:.cpp=.o)
PROG = FRC_Program.out
PROG_DEST = Program
PROG_PARTIAL = FRC_Program_partialImage.o
PROG_PARTIAL_DEST = Program_partialImage
ROBOT_ADDR = 10.0.8.2

export WIND_HOME=$(HOME)/.ucpp/gccdist/WindRiver
export WIND_BASE=$(HOME)/.ucpp/gccdist/WindRiver/vxworks-6.3
export WIND_LIC_PROXY=$(HOME)/.ucpp/gccdist/WindRiver/setup/x86-win32/bin/
export LM_LICENSE_FILE=$(HOME)/.ucpp/gccdist/WindRiver/license/zwrsLicense.lic
export WINEDEBUG=fixme-all

all: $(SRCS) $(PROG_PARTIAL) $(PROG)

.cpp.o:	
	$(CPP) $(C_FLAGS) $(INCLUDES) $(ARCH) $(DEFINES) -o "$@" -c "$<"

$(PROG_PARTIAL): $(OBJS)
	if [ ! -d "$(PROG_PARTIAL_DEST)" ] ; then mkdir -p $(PROG_PARTIAL_DEST); fi
	$(TOOL_PATH)ccppc.exe -r -nostdlib -Wl,-X -o $(PROG_PARTIAL_DEST)/"$@" $(OBJS) 

$(PROG):
	if [ ! -d "$(PROG_DEST)" ] ; then mkdir -p $(PROG_DEST); fi	
	$(NM) $(PROG_PARTIAL_DEST)/$(PROG_PARTIAL) $(WPI_LIB) | tclsh $(HOME)/.ucpp/gccdist/WindRiver/vxworks-6.3/host/resource/hutils/tcl/munch.tcl -c ppc > $(PROG_DEST)/ctdt.c ; \
	$(CPP) -g3 $(ARCH) -fdollars-in-identifiers -Wall $(DEFINES) -o $(PROG_DEST)/ctdt.o -c $(PROG_DEST)/ctdt.c ; \
	$(CPP) -r -nostdlib -Wl,-X -T $(HOME)/.ucpp/gccdist/WindRiver/vxworks-6.3/target/h/tool/gnu/ldscripts/link.OUT -o $(PROG_DEST)/"$@" $(PROG_DEST)/ctdt.o $(PROG_PARTIAL_DEST)/$(PROG_PARTIAL) $(WPI_LIB) -fno-feature-proxy

deploy: $(SRCS) $(PROG_PARTIAL) $(PROG)
	wput -u $(PROG_DEST)/$(PROG) ftp://anonymous@$(ROBOT_ADDR)/ni-rt/system/FRC_UserProgram.out

clean:
	rm *.o ; \
	rm *.d ; \
	cd $(PROG_DEST) && rm $(PROG) ctdt.* ; \
	cd $(PROG_PARTIAL_DEST) && rm $(PROG_PARTIAL)
