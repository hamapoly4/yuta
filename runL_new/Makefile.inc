mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	ScenarioTracer.o \
	Scenario.o \
	Scene.o \
	LineTraceRun.o \
	PIDcon.o \
	RunDistJudgeMent.o \
	ColorJudgeMent.o \
	RunDistDetect.o \
	ColorDetect.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += $(mkfile_path)Scenario $(mkfile_path)SpikeCon $(mkfile_path)JudgeMent $(mkfile_path)Detect

INCLUDES += \
	-I$(mkfile_path)Scenario \
	-I$(mkfile_path)SpikeCon \
	-I$(mkfile_path)JudgeMent \
	-I$(mkfile_path)Detect \
