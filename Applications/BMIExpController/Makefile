prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: TrialHandler/TrialHandler ExpEnviHandler/ExpEnviHandler MovObjHandler/MovObjHandler FirstBMICageInterfacer/FirstBMICageInterfacer

############## TRIAL_HANDLER ############## 

TrialHandler/TrialHandler: TrialHandler/TrialHandler.c TrialHandler/Gui.o TrialHandler/GuiTrialHandler.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2TrialHand.o ../../Library/TrialsData/TrialTypes.o  ../../Library/Combos/TrialTypesCombo.o TrialHandler/TrialHandlerRtTask.o TrialHandler/TrialDurationHandlerRtTask.o ../../Library/TrialsData/TrialStats.o ../../Library/TrialsData/TrialData.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o TrialHandler/HandleGui2TrialHandMsgs.o ../../Library/Status/TrialStatus.o ../../Library/Messages/TrialDurHand2TrialHand.o ../../Library/Messages/TrialHand2TrialDurHand.o TrialHandler/HandleTrialDurHand2TrialHandMsgs.o TrialHandler/HandleTrialHand2TrialDurHandMsgs.o TrialHandler/HandleExpEnviHand2TrialHandMsgs.o TrialHandler/HandleMovObjHand2TrialHandMsgs.o ../../Library/Messages/ExpEnviHand2TrialHand.o ../../Library/Messages/MovObjHand2TrialHand.o ../../Library/Messages/TrialHand2MovObjHand.o ../../Library/Messages/TrialHand2ExpEnviHand.o 
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< TrialHandler/Gui.o TrialHandler/GuiTrialHandler.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2TrialHand.o ../../Library/TrialsData/TrialTypes.o ../../Library/Combos/TrialTypesCombo.o TrialHandler/TrialHandlerRtTask.o TrialHandler/TrialDurationHandlerRtTask.o ../../Library/TrialsData/TrialStats.o ../../Library/TrialsData/TrialData.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o TrialHandler/HandleGui2TrialHandMsgs.o ../../Library/Status/TrialStatus.o ../../Library/Messages/TrialDurHand2TrialHand.o ../../Library/Messages/TrialHand2TrialDurHand.o TrialHandler/HandleTrialDurHand2TrialHandMsgs.o TrialHandler/HandleTrialHand2TrialDurHandMsgs.o TrialHandler/HandleExpEnviHand2TrialHandMsgs.o TrialHandler/HandleMovObjHand2TrialHandMsgs.o ../../Library/Messages/ExpEnviHand2TrialHand.o ../../Library/Messages/MovObjHand2TrialHand.o ../../Library/Messages/TrialHand2MovObjHand.o ../../Library/Messages/TrialHand2ExpEnviHand.o ### TrialHandler

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

TrialHandler/HandleTrialHand2TrialDurHandMsgs.o: TrialHandler/HandleTrialHand2TrialDurHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleTrialHand2TrialDurHandMsgs

TrialHandler/HandleExpEnviHand2TrialHandMsgs.o: TrialHandler/HandleExpEnviHand2TrialHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleExpEnviHand2TrialHandMsgs

TrialHandler/HandleMovObjHand2TrialHandMsgs.o: TrialHandler/HandleMovObjHand2TrialHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandler/HandleMovObjHand2TrialHandMsgs

../../../BlueSpike/Library/Misc/Misc.o: ../../../BlueSpike/Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/Misc/Misc

../../Library/Messages/Gui2TrialHand.o: ../../Library/Messages/Gui2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2TrialHand

../../Library/Messages/TrialDurHand2TrialHand.o: ../../Library/Messages/TrialDurHand2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialDurHand2TrialHand

../../Library/Messages/ExpEnviHand2TrialHand.o: ../../Library/Messages/ExpEnviHand2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/ExpEnviHand2TrialHand

../../Library/Messages/MovObjHand2TrialHand.o: ../../Library/Messages/MovObjHand2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/MovObjHand2TrialHand

../../Library/Messages/TrialHand2TrialDurHand.o: ../../Library/Messages/TrialHand2TrialDurHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2TrialDurHand

../../Library/TrialsData/TrialTypes.o: ../../Library/TrialsData/TrialTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/TrialsData/TrialTypes.o

../../Library/TrialsData/TrialStats.o: ../../Library/TrialsData/TrialStats.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/TrialsData/TrialStats.o

../../Library/TrialsData/TrialData.o: ../../Library/TrialsData/TrialData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/TrialsData/TrialData.o

../../Library/Status/TrialStatus.o: ../../Library/Status/TrialStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Status/TrialStatus.o

../../Library/Combos/TrialTypesCombo.o: ../../Library/Combos/TrialTypesCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Combos/TrialTypesCombo.o

../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o: ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o

############## EXP_ENVI_HANDLER ############## 

ExpEnviHandler/ExpEnviHandler: ExpEnviHandler/ExpEnviHandler.c ExpEnviHandler/Gui.o ../../Library/Messages/Gui2ExpEnviHand.o ../../../BlueSpike/Library/Misc/Misc.o ExpEnviHandler/ExpEnviHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ExpEnviHandler/GuiExpEnviHandler.o ../../Library/Messages/TrialHand2ExpEnviHand.o
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< ExpEnviHandler/Gui.o ../../Library/Messages/Gui2ExpEnviHand.o ../../../BlueSpike/Library/Misc/Misc.o ExpEnviHandler/ExpEnviHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ExpEnviHandler/GuiExpEnviHandler.o ../../Library/Messages/TrialHand2ExpEnviHand.o ### ExpEnviHandler

ExpEnviHandler/Gui.o: ExpEnviHandler/Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/Gui

ExpEnviHandler/GuiExpEnviHandler.o: ExpEnviHandler/GuiExpEnviHandler.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/GuiExpEnviHandler

ExpEnviHandler/ExpEnviHandlerRtTask.o: ExpEnviHandler/ExpEnviHandlerRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviHandler/ExpEnviHandlerRtTask

../../Library/Messages/Gui2ExpEnviHand.o: ../../Library/Messages/Gui2ExpEnviHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2ExpEnviHand

../../Library/Messages/TrialHand2ExpEnviHand.o: ../../Library/Messages/TrialHand2ExpEnviHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2ExpEnviHand

############## MOV_OBJ_HANDLER ############## 

MovObjHandler/MovObjHandler: MovObjHandler/MovObjHandler.c MovObjHandler/Gui.o ../../Library/Messages/Gui2MovObjHand.o ../../../BlueSpike/Library/Misc/Misc.o MovObjHandler/MovObjHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o MovObjHandler/GuiMovObjHandler.o ../../Library/Messages/TrialHand2MovObjHand.o
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< MovObjHandler/Gui.o ../../Library/Messages/Gui2MovObjHand.o ../../../BlueSpike/Library/Misc/Misc.o MovObjHandler/MovObjHandlerRtTask.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o MovObjHandler/GuiMovObjHandler.o ../../Library/Messages/TrialHand2MovObjHand.o ### MovObjHandler

MovObjHandler/Gui.o: MovObjHandler/Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/Gui

MovObjHandler/MovObjHandlerRtTask.o: MovObjHandler/MovObjHandlerRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/MovObjHandlerRtTask

MovObjHandler/GuiMovObjHandler.o: MovObjHandler/GuiMovObjHandler.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### MovObjHandler/GuiMovObjHandler

../../Library/Messages/Gui2MovObjHand.o: ../../Library/Messages/Gui2MovObjHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2MovObjHand

../../Library/Messages/TrialHand2MovObjHand.o: ../../Library/Messages/TrialHand2MovObjHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/TrialHand2MovObjHand

############## FIRST_BMI_CAGE_INTERFACER ############## 

FirstBMICageInterfacer/FirstBMICageInterfacer: FirstBMICageInterfacer/FirstBMICageInterfacer.c FirstBMICageInterfacer/Gui.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2MovObjInterf.o ../../Library/Messages/Gui2ExpEnviInterf.o FirstBMICageInterfacer/FirstBMICageInterfacerRtTask.o FirstBMICageInterfacer/GuiCageInterfacer.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ../../Library/Messages/ExpEnviHand2ExpEnviInterf.o
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< FirstBMICageInterfacer/Gui.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2MovObjInterf.o ../../Library/Messages/Gui2ExpEnviInterf.o FirstBMICageInterfacer/FirstBMICageInterfacerRtTask.o FirstBMICageInterfacer/GuiCageInterfacer.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ../../Library/Messages/ExpEnviHand2ExpEnviInterf.o ### FirstBMICageInterfacer

FirstBMICageInterfacer/Gui.o: FirstBMICageInterfacer/Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### FirstBMICageInterfacer/Gui

FirstBMICageInterfacer/FirstBMICageInterfacerRtTask.o: FirstBMICageInterfacer/FirstBMICageInterfacerRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### FirstBMICageInterfacer/MovObjHandlerRtTask

FirstBMICageInterfacer/GuiCageInterfacer.o: FirstBMICageInterfacer/GuiCageInterfacer.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### FirstBMICageInterfacer/GuiCageInterfacer

../../Library/Messages/Gui2MovObjInterf.o: ../../Library/Messages/Gui2MovObjInterf.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2MovObjInterf

../../Library/Messages/Gui2ExpEnviInterf.o: ../../Library/Messages/Gui2ExpEnviInterf.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2ExpEnviInterf

../../Library/Messages/ExpEnviHand2ExpEnviInterf.o: ../../Library/Messages/ExpEnviHand2ExpEnviInterf.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/ExpEnviHand2ExpEnviInterf

clean:
	rm -f TrialHandler/TrialHandler TrialHandler/*.o ExpEnviHandler/ExpEnviHandler ExpEnviHandler/*.o MovObjHandler/MovObjHandler MovObjHandler/*.o FirstBMICageInterfacer/FirstBMICageInterfacer FirstBMICageInterfacer/*.o ../../../BlueSpike/Library/Misc/*.o ../../Library/Messages/*.o ../../Library/TrialsData/*.o ../../Library/Combos/*.o ../../../BlueSpike/Library/RtTaskStats/*.o ../../Library/Status/*.o

.PHONY: clean

