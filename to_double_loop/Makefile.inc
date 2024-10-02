mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_CXXOBJS += \
	HackSPiUnit2.o \
	ScenarioTracerWithStarter.o \
	ScenarioTracer.o \
	DeviceManage.o \
	Scenario.o \
	Scene.o \
	Run.o \
	LineSearchRun.o \
	LineTraceRun.o \
	RotateRun.o \
	StraRun.o \
	RotateAngleJudge.o \
	RunDistJudge.o \
	ColorJudge.o \
	GyroStopP.o \
	GyroStraPD.o \
	LineTracePID.o \
	RunDistDetect.o \
	ColorDetect.o \
	AngleMonitor.o \
	HSVMonitor.o \
	CountMonitor.o \

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile

endif

APPL_DIRS += $(mkfile_path)ScenarioTracer $(mkfile_path)Run $(mkfile_path)Judge $(mkfile_path)Control $(mkfile_path)Detect $(mkfile_path)Monitor

INCLUDES += \
	-I$(mkfile_path)ScenarioTracer \
	-I$(mkfile_path)Run \
	-I$(mkfile_path)Judge \
	-I$(mkfile_path)Control \
	-I$(mkfile_path)Detect \
	-I$(mkfile_path)Monitor \
