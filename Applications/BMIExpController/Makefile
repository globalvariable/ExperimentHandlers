prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: TrialHandler/TrialHandler ExpEnviHandler/ExpEnviHandler MovObjHandler/MovObjHandler 
############## TRIAL_HANDLER ############## 

TrialHandler/TrialHandler: TrialHandler/TrialHandler.c TrialHandler/Gui.o TrialHandler/GuiTrialHandler.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2TrialHand.o TrialHandler/TrialHandlerRtTask.o TrialHandler/TrialDurationHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o TrialHandler/HandleGui2TrialHandMsgs.o ../../Library/Status/TrialStatus.o ../../Library/Messages/TrialDurHand2TrialHand.o ../../Library/Messages/TrialHand2TrialDurHand.o TrialHandler/HandleTrialDurHand2TrialHandMsgs.o TrialHandler/HandleTrialHand2TrialDurHandMsgs.o TrialHandler/HandleExpEnviHand2TrialHandMsgs.o TrialHandler/HandleMovObjHand2TrialHandMsgs.o ../../Library/Messages/ExpEnviHand2TrialHand.o ../../Library/Messages/MovObjHand2TrialHand.o ../../Library/Messages/TrialHand2MovObjHand.o ../../Library/Messages/TrialHand2ExpEnviHand.o ../../Library/Status/TrialDurStatus.o ../../../BlueSpike/Library/Misc/Randn.o TrialHandler/HandleTrialHandDur.o ../../Library/Messages/TrialHand2NeuralNet.o ../../Library/Messages/NeuralNet2TrialHand.o ../../Library/Messages/TrialHand2SpikeGen.o ../../Library/Messages/SpikeGen2TrialHand.o ../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.o TrialHandler/DataHandling/DataHandling.o TrialHandler/DataHandling/v0/DataFormat_v0.o ../../Library/Messages/TrialHand2Gui.o 
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< TrialHandler/Gui.o TrialHandler/GuiTrialHandler.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2TrialHand.o TrialHandler/TrialHandlerRtTask.o TrialHandler/TrialDurationHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o TrialHandler/HandleGui2TrialHandMsgs.o ../../Library/Status/TrialStatus.o ../../Library/Messages/TrialDurHand2TrialHand.o ../../Library/Messages/TrialHand2TrialDurHand.o TrialHandler/HandleTrialDurHand2TrialHandMsgs.o TrialHandler/HandleTrialHand2TrialDurHandMsgs.o TrialHandler/HandleExpEnviHand2TrialHandMsgs.o TrialHandler/HandleMovObjHand2TrialHandMsgs.o ../../Library/Messages/ExpEnviHand2TrialHand.o ../../Library/Messages/MovObjHand2TrialHand.o ../../Library/Messages/TrialHand2MovObjHand.o ../../Library/Messages/TrialHand2ExpEnviHand.o ../../Library/Status/TrialDurStatus.o ../../../BlueSpike/Library/Misc/Randn.o TrialHandler/HandleTrialHandDur.o ../../Library/Messages/TrialHand2NeuralNet.o ../../Library/Messages/NeuralNet2TrialHand.o ../../Library/Messages/TrialHand2SpikeGen.o ../../Library/Messages/SpikeGen2TrialHand.o ../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.o TrialHandler/DataHandling/DataHandling.o TrialHandler/DataHandling/v0/DataFormat_v0.o ../../Library/Messages/TrialHand2Gui.o ### TrialHandler

TrialHandler/Gui.o: TrialHandler/Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/Gui

TrialHandler/GuiTrialHandler.o: TrialHandler/GuiTrialHandler.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/GuiTrialHandler

TrialHandler/TrialHandlerRtTask.o: TrialHandler/TrialHandlerRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandlerRtTask

TrialHandler/TrialDurationHandlerRtTask.o: TrialHandler/TrialDurationHandlerRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/TrialDurationHandlerRtTask

TrialHandler/HandleGui2TrialHandMsgs.o: TrialHandler/HandleGui2TrialHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleGui2TrialHandMsgs

TrialHandler/HandleTrialDurHand2TrialHandMsgs.o: TrialHandler/HandleTrialDurHand2TrialHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleTrialDurHand2TrialHandMsgs

TrialHandler/HandleTrialHandDur.o: TrialHandler/HandleTrialHandDur.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleTrialHandDur

TrialHandler/HandleTrialHand2TrialDurHandMsgs.o: TrialHandler/HandleTrialHand2TrialDurHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleTrialHand2TrialDurHandMsgs

TrialHandler/HandleExpEnviHand2TrialHandMsgs.o: TrialHandler/HandleExpEnviHand2TrialHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleExpEnviHand2TrialHandMsgs

TrialHandler/HandleMovObjHand2TrialHandMsgs.o: TrialHandler/HandleMovObjHand2TrialHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleMovObjHand2TrialHandMsgs

../../../BlueSpike/Library/Misc/Misc.o: ../../../BlueSpike/Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/Misc/Misc

../../../BlueSpike/Library/Misc/Randn.o: ../../../BlueSpike/Library/Misc/Randn.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/Misc/Randn

../../Library/Messages/Gui2TrialHand.o: ../../Library/Messages/Gui2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2TrialHand

../../Library/Messages/TrialHand2Gui.o: ../../Library/Messages/TrialHand2Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2Gui

../../Library/Messages/TrialDurHand2TrialHand.o: ../../Library/Messages/TrialDurHand2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialDurHand2TrialHand

../../Library/Messages/ExpEnviHand2TrialHand.o: ../../Library/Messages/ExpEnviHand2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/ExpEnviHand2TrialHand

../../Library/Messages/MovObjHand2TrialHand.o: ../../Library/Messages/MovObjHand2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/MovObjHand2TrialHand

../../Library/Messages/TrialHand2TrialDurHand.o: ../../Library/Messages/TrialHand2TrialDurHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2TrialDurHand

../../Library/Messages/TrialHand2NeuralNet.o: ../../Library/Messages/TrialHand2NeuralNet.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2NeuralNet

../../Library/Messages/NeuralNet2TrialHand.o: ../../Library/Messages/NeuralNet2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/NeuralNet2TrialHand

../../Library/Messages/TrialHand2SpikeGen.o: ../../Library/Messages/TrialHand2SpikeGen.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2SpikeGen

../../Library/Messages/SpikeGen2TrialHand.o: ../../Library/Messages/SpikeGen2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/SpikeGen2TrialHand

../../Library/Status/TrialStatus.o: ../../Library/Status/TrialStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/TrialStatus.o

../../Library/Status/TrialDurStatus.o: ../../Library/Status/TrialDurStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/TrialDurStatus.o

../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o: ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o

../../Library/ExpParadigm/ParadigmRobotReach/TrialHandParadigm.o: ../../Library/ExpParadigm/ParadigmRobotReach/TrialHandParadigm.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/ExpParadigm/ParadigmRobotReach/TrialHandParadigm

../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.o: ../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/ExpParadigm/ParadigmRobotReach/TrialHistory

TrialHandler/DataHandling/DataHandling.o: TrialHandler/DataHandling/DataHandling.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/DataHandling/DataHandling

TrialHandler/DataHandling/v0/DataFormat_v0.o: TrialHandler/DataHandling/v0/DataFormat_v0.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/DataHandling/v0/DataFormat_v0

############## EXP_ENVI_HANDLER ############## 

ExpEnviHandler/ExpEnviHandler: ExpEnviHandler/ExpEnviHandler.c ExpEnviHandler/Gui.o ../../Library/Messages/Gui2ExpEnviHand.o ../../../BlueSpike/Library/Misc/Misc.o ExpEnviHandler/ExpEnviHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ExpEnviHandler/GuiExpEnviHandler.o ../../Library/Messages/TrialHand2ExpEnviHand.o ../../Library/Messages/ExpEnviDurHand2ExpEnviHand.o ExpEnviHandler/ExpEnviDurationHandlerRtTask.o ExpEnviHandler/HandleExpEnviHand2ExpEnviDurHandMsgs.o ../../Library/Messages/ExpEnviHand2ExpEnviDurHand.o ../../Library/Messages/ExpEnviHand2TrialHand.o ../../Library/ExpEnviData/ExpEnviComponentTypes.o ../../Library/ExpEnviData/ExpEnviData.o ExpEnviHandler/HandleGui2ExpEnviHandMsgs.o ExpEnviHandler/HandleExpEnviDurHand2ExpEnviHandMsgs.o ExpEnviHandler/HandleTrialHand2ExpEnviHandMsgs.o ExpEnviHandler/HandleExpEnviHandDur.o ../../Library/Status/ExpEnviStatus.o ../../Library/Status/ExpEnviDurStatus.o ../../Library/ExpEnviData/ExpEnviEvaluate.o ../../Library/Status/ExpEnviComponentStatus.o ExpEnviHandler/HandleRS232Buffers.o ../../Library/RS232/RS232Handler.o 
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< ExpEnviHandler/Gui.o ../../Library/Messages/Gui2ExpEnviHand.o ../../../BlueSpike/Library/Misc/Misc.o ExpEnviHandler/ExpEnviHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ExpEnviHandler/GuiExpEnviHandler.o ../../Library/Messages/TrialHand2ExpEnviHand.o ../../Library/Messages/ExpEnviDurHand2ExpEnviHand.o ExpEnviHandler/ExpEnviDurationHandlerRtTask.o ExpEnviHandler/HandleExpEnviHand2ExpEnviDurHandMsgs.o ../../Library/Messages/ExpEnviHand2ExpEnviDurHand.o ../../Library/Messages/ExpEnviHand2TrialHand.o ../../Library/ExpEnviData/ExpEnviComponentTypes.o ../../Library/ExpEnviData/ExpEnviData.o ExpEnviHandler/HandleGui2ExpEnviHandMsgs.o ExpEnviHandler/HandleExpEnviDurHand2ExpEnviHandMsgs.o ExpEnviHandler/HandleTrialHand2ExpEnviHandMsgs.o ExpEnviHandler/HandleExpEnviHandDur.o ../../Library/Status/ExpEnviStatus.o ../../Library/Status/ExpEnviDurStatus.o ../../Library/ExpEnviData/ExpEnviEvaluate.o ../../Library/Status/ExpEnviComponentStatus.o ExpEnviHandler/HandleRS232Buffers.o ../../Library/RS232/RS232Handler.o ### ExpEnviHandler

ExpEnviHandler/Gui.o: ExpEnviHandler/Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/Gui

ExpEnviHandler/GuiExpEnviHandler.o: ExpEnviHandler/GuiExpEnviHandler.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/GuiExpEnviHandler

ExpEnviHandler/ExpEnviHandlerRtTask.o: ExpEnviHandler/ExpEnviHandlerRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/ExpEnviHandlerRtTask

ExpEnviHandler/ExpEnviDurationHandlerRtTask.o: ExpEnviHandler/ExpEnviDurationHandlerRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/ExpEnviDurationHandlerRtTask

ExpEnviHandler/HandleGui2ExpEnviHandMsgs.o: ExpEnviHandler/HandleGui2ExpEnviHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/HandleGui2ExpEnviHandMsgs

ExpEnviHandler/HandleExpEnviDurHand2ExpEnviHandMsgs.o: ExpEnviHandler/HandleExpEnviDurHand2ExpEnviHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/HandleExpEnviDurHand2ExpEnviHandMsgs

ExpEnviHandler/HandleTrialHand2ExpEnviHandMsgs.o: ExpEnviHandler/HandleTrialHand2ExpEnviHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/HandleTrialHand2ExpEnviHandMsgs

ExpEnviHandler/HandleExpEnviHand2ExpEnviDurHandMsgs.o: ExpEnviHandler/HandleExpEnviHand2ExpEnviDurHandMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/HandleExpEnviHand2ExpEnviDurHandMsgs

ExpEnviHandler/HandleExpEnviHandDur.o: ExpEnviHandler/HandleExpEnviHandDur.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/HandleExpEnviHandDur

ExpEnviHandler/HandleRS232Buffers.o: ExpEnviHandler/HandleRS232Buffers.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/HandleRS232Buffers

../../Library/Messages/Gui2ExpEnviHand.o: ../../Library/Messages/Gui2ExpEnviHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2ExpEnviHand

../../Library/Messages/TrialHand2ExpEnviHand.o: ../../Library/Messages/TrialHand2ExpEnviHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2ExpEnviHand

../../Library/Messages/ExpEnviDurHand2ExpEnviHand.o: ../../Library/Messages/ExpEnviDurHand2ExpEnviHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/ExpEnviDurHand2ExpEnviHand

../../Library/Messages/ExpEnviHand2ExpEnviDurHand.o: ../../Library/Messages/ExpEnviHand2ExpEnviDurHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/ExpEnviHand2ExpEnviDurHand

../../Library/ExpEnviData/ExpEnviComponentTypes.o: ../../Library/ExpEnviData/ExpEnviComponentTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/ExpEnviData/ExpEnviComponentTypes

../../Library/ExpEnviData/ExpEnviData.o: ../../Library/ExpEnviData/ExpEnviData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/ExpEnviData/ExpEnviData

../../Library/ExpEnviData/ExpEnviEvaluate.o: ../../Library/ExpEnviData/ExpEnviEvaluate.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/ExpEnviData/ExpEnviEvaluate

../../Library/Status/ExpEnviStatus.o: ../../Library/Status/ExpEnviStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/ExpEnviStatus

../../Library/Status/ExpEnviDurStatus.o: ../../Library/Status/ExpEnviDurStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/ExpEnviDurStatus

../../Library/Status/ExpEnviComponentStatus.o: ../../Library/Status/ExpEnviComponentStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/ExpEnviComponentStatus

../../Library/RS232/RS232Handler.o: ../../Library/RS232/RS232Handler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/RS232/RS232Handler

############## MOV_OBJ_HANDLER ############## 

MovObjHandler/MovObjHandler: MovObjHandler/MovObjHandler.c MovObjHandler/Gui.o ../../Library/Messages/Gui2MovObjHand.o ../../../BlueSpike/Library/Misc/Misc.o MovObjHandler/MovObjHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o MovObjHandler/GuiMovObjHandler.o ../../Library/Messages/TrialHand2MovObjHand.o ../../Library/Messages/MovObjDurHand2MovObjHand.o ../../Library/Messages/MovObjHand2MovObjDurHand.o MovObjHandler/HandleMovObjHand2MovObjDurHandMsgs.o ../../Library/Messages/MovObjHand2TrialHand.o MovObjHandler/HandleMovObjDurHand2MovObjHandMsgs.o MovObjHandler/HandleTrialHand2MovObjHandMsgs.o MovObjHandler/HandleGui2MovObjHandMsgs.o ../../Library/MovObjData/MovObjComponentTypes.o ../../Library/MovObjData/MovObjData.o ../../Library/Status/MovObjStatus.o ../../Library/Status/MovObjDurStatus.o ../../Library/Messages/MovObjHand2NeuralNet.o ../../Library/Messages/NeuralNet2MovObjHand.o MovObjHandler/HandleNeuralNet2MovObjHandMsgs.o ../../../IzNeuronSimulators/Library/SpikeData/SpikeData.o MovObjHandler/HandleSpikeDataBuff.o ../../Library/Graphs/LocationGraph.o ../../Library/Messages/MovObjHand2Gui.o ../../Library/Servo/Servo.o ../../Library/Robot/ThreeDofRobot.o ../../Library/RS232/RS232Handler.o ../../../BlueSpike/Library/LogBuffer/MessageLogBuffer.o MovObjHandler/HandleRS232Buffers.o MovObjHandler/HandleRobotPosition.o ../../../BlueSpike/Library/Thresholding/Thresholding.o ../../Library/ExpParadigm/ParadigmRobotReach/MovObjHandParadigm.o ../../Library/Coordinate/Cartesian.o 
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< MovObjHandler/Gui.o ../../Library/Messages/Gui2MovObjHand.o ../../../BlueSpike/Library/Misc/Misc.o MovObjHandler/MovObjHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o MovObjHandler/GuiMovObjHandler.o ../../Library/Messages/TrialHand2MovObjHand.o ../../Library/Messages/MovObjDurHand2MovObjHand.o ../../Library/Messages/MovObjHand2MovObjDurHand.o MovObjHandler/HandleMovObjHand2MovObjDurHandMsgs.o ../../Library/Messages/MovObjHand2TrialHand.o MovObjHandler/HandleMovObjDurHand2MovObjHandMsgs.o MovObjHandler/HandleTrialHand2MovObjHandMsgs.o MovObjHandler/HandleGui2MovObjHandMsgs.o ../../Library/MovObjData/MovObjComponentTypes.o ../../Library/MovObjData/MovObjData.o ../../Library/Status/MovObjStatus.o ../../Library/Status/MovObjDurStatus.o ../../Library/Messages/MovObjHand2NeuralNet.o ../../Library/Messages/NeuralNet2MovObjHand.o MovObjHandler/HandleNeuralNet2MovObjHandMsgs.o ../../../IzNeuronSimulators/Library/SpikeData/SpikeData.o MovObjHandler/HandleSpikeDataBuff.o ../../Library/Graphs/LocationGraph.o ../../Library/Messages/MovObjHand2Gui.o ../../Library/Servo/Servo.o ../../Library/Robot/ThreeDofRobot.o ../../Library/RS232/RS232Handler.o ../../../BlueSpike/Library/LogBuffer/MessageLogBuffer.o MovObjHandler/HandleRS232Buffers.o MovObjHandler/HandleRobotPosition.o ../../../BlueSpike/Library/Thresholding/Thresholding.o ../../Library/ExpParadigm/ParadigmRobotReach/MovObjHandParadigm.o ../../Library/Coordinate/Cartesian.o ### MovObjHandler

MovObjHandler/Gui.o: MovObjHandler/Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/Gui

MovObjHandler/MovObjHandlerRtTask.o: MovObjHandler/MovObjHandlerRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/MovObjHandlerRtTask

MovObjHandler/GuiMovObjHandler.o: MovObjHandler/GuiMovObjHandler.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/GuiMovObjHandler

MovObjHandler/HandleMovObjHand2MovObjDurHandMsgs.o: MovObjHandler/HandleMovObjHand2MovObjDurHandMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleMovObjHand2MovObjDurHandMsgs

MovObjHandler/HandleMovObjDurHand2MovObjHandMsgs.o: MovObjHandler/HandleMovObjDurHand2MovObjHandMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleMovObjDurHand2MovObjHandMsgs

MovObjHandler/HandleTrialHand2MovObjHandMsgs.o: MovObjHandler/HandleTrialHand2MovObjHandMsgs.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleTrialHand2MovObjHandMsgs

MovObjHandler/HandleGui2MovObjHandMsgs.o: MovObjHandler/HandleGui2MovObjHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleGui2MovObjHandMsgs

MovObjHandler/HandleNeuralNet2MovObjHandMsgs.o: MovObjHandler/HandleNeuralNet2MovObjHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleNeuralNet2MovObjHandMsgs.o

MovObjHandler/HandleSpikeDataBuff.o: MovObjHandler/HandleSpikeDataBuff.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleSpikeDataBuff.o

MovObjHandler/HandleRS232Buffers.o: MovObjHandler/HandleRS232Buffers.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleRS232Buffers

MovObjHandler/HandleRobotPosition.o: MovObjHandler/HandleRobotPosition.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/HandleRobotPosition

../../Library/Messages/Gui2MovObjHand.o: ../../Library/Messages/Gui2MovObjHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2MovObjHand

../../Library/Messages/MovObjHand2Gui.o: ../../Library/Messages/MovObjHand2Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/MovObjHand2Gui

../../Library/Messages/TrialHand2MovObjHand.o: ../../Library/Messages/TrialHand2MovObjHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2MovObjHand

../../Library/Messages/MovObjDurHand2MovObjHand.o: ../../Library/Messages/MovObjDurHand2MovObjHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/MovObjDurHand2MovObjHand

../../Library/Messages/MovObjHand2MovObjDurHand.o: ../../Library/Messages/MovObjHand2MovObjDurHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/MovObjHand2MovObjDurHand

../../Library/Messages/MovObjHand2NeuralNet.o: ../../Library/Messages/MovObjHand2NeuralNet.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/MovObjHand2NeuralNet

../../Library/Messages/NeuralNet2MovObjHand.o: ../../Library/Messages/NeuralNet2MovObjHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/NeuralNet2MovObjHand

../../Library/MovObjData/MovObjComponentTypes.o: ../../Library/MovObjData/MovObjComponentTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/MovObjData/MovObjComponentTypes

../../Library/MovObjData/MovObjData.o: ../../Library/MovObjData/MovObjData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/MovObjData/MovObjData

../../Library/MovObjData/MovObjDirectionTypes.o: ../../Library/MovObjData/MovObjDirectionTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/MovObjData/MovObjDirectionTypes

../../Library/Status/MovObjStatus.o: ../../Library/Status/MovObjStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/MovObjStatus

../../Library/Status/MovObjDurStatus.o: ../../Library/Status/MovObjDurStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/MovObjDurStatus

../../../IzNeuronSimulators/Library/SpikeData/SpikeData.o: ../../../IzNeuronSimulators/Library/SpikeData/SpikeData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../IzNeuronSimulators/Library/SpikeData/SpikeData

../../Library/Graphs/LocationGraph.o: ../../Library/Graphs/LocationGraph.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Graphs/LocationGraph

../../Library/Servo/Servo.o: ../../Library/Servo/Servo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Servo/Servo

../../Library/Robot/ThreeDofRobot.o: ../../Library/Robot/ThreeDofRobot.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Robot/ThreeDofRobot

../../Library/Coordinate/Cartesian.o: ../../Library/Coordinate/Cartesian.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Coordinate/Cartesian

../../../BlueSpike/Library/LogBuffer/MessageLogBuffer.o: ../../../BlueSpike/Library/LogBuffer/MessageLogBuffer.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/LogBuffer/MessageLogBuffer

../../../BlueSpike/Library/Thresholding/Thresholding.o: ../../../BlueSpike/Library/Thresholding/Thresholding.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/Thresholding/Thresholding

../../Library/ExpParadigm/ParadigmRobotReach/MovObjHandParadigm.o: ../../Library/ExpParadigm/ParadigmRobotReach/MovObjHandParadigm.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/ExpParadigm/ParadigmRobotReach/MovObjHandParadigm

clean:
	rm -f TrialHandler/TrialHandler TrialHandler/*.o ExpEnviHandler/ExpEnviHandler ExpEnviHandler/*.o MovObjHandler/MovObjHandler MovObjHandler/*.o ../../../BlueSpike/Library/Misc/*.o ../../Library/Messages/*.o ../../Library/TrialsData/*.o ../../Library/Combos/*.o ../../../BlueSpike/Library/RtTaskStats/*.o ../../Library/Status/*.o ../../Library/RS232/*.o ../../Library/ExpEnviData/*.o ../../Library/MovObjData/*.o ../../../IzNeuronSimulators/Library/SpikeData/*.o ../../Library/Graphs/*.o ../../Library/Servo/*.o ../../Library/Robot/*.o ../../../BlueSpike/Library/Thresholding/*.o ../../Library/RS232/*.o ../../../BlueSpike/Library/LogBuffer/*.o ../../Library/ExpParadigm/ParadigmRobotReach/*.o ../../Library/Coordinate/*.o TrialHandler/DataHandling/*.o TrialHandler/DataHandling/v0/*.o

.PHONY: clean

