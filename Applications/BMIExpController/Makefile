prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: TrialHandler/TrialHandler

TrialHandler/TrialHandler: TrialHandler/TrialHandler.c TrialHandler/Gui.o TrialHandler/GuiTrialHandler.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2TrialHand.o ../../Library/TrialsData/TrialTypes.o  ../../Library/Combos/TrialTypesCombo.o TrialHandler/TrialHandlerRtTask.o TrialHandler/TrialDurationHandlerRtTask.o ../../Library/TrialsData/TrialStats.o ../../Library/TrialsData/TrialData.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o TrialHandler/HandleGui2TrialHandMsgs.o ../../Library/Status/TrialStatus.o ../../Library/Messages/TrialDurHand2TrialHand.o ../../Library/Messages/TrialHand2TrialDurHand.o TrialHandler/HandleTrialDurHand2TrialHandMsgs.o TrialHandler/HandleTrialHand2TrialDurHandMsgs.o TrialHandler/HandleExpEnviHand2TrialHandMsgs.o TrialHandler/HandleMovObjHand2TrialHandMsgs.o
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< TrialHandler/Gui.o TrialHandler/GuiTrialHandler.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/Messages/Gui2TrialHand.o ../../Library/TrialsData/TrialTypes.o ../../Library/Combos/TrialTypesCombo.o TrialHandler/TrialHandlerRtTask.o TrialHandler/TrialDurationHandlerRtTask.o ../../Library/TrialsData/TrialStats.o ../../Library/TrialsData/TrialData.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o TrialHandler/HandleGui2TrialHandMsgs.o ../../Library/Status/TrialStatus.o ../../Library/Messages/TrialDurHand2TrialHand.o ../../Library/Messages/TrialHand2TrialDurHand.o TrialHandler/HandleTrialDurHand2TrialHandMsgs.o TrialHandler/HandleTrialHand2TrialDurHandMsgs.o TrialHandler/HandleExpEnviHand2TrialHandMsgs.o TrialHandler/HandleMovObjHand2TrialHandMsgs.o ### TrialHandler

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

clean:
	rm -f TrialHandler/TrialHandler TrialHandler/*.o ../../../BlueSpike/Library/Misc/*.o ../../Library/Messages/*.o ../../Library/TrialsData/*.o ../../Library/Combos/*.o ../../../BlueSpike/Library/RtTaskStats/*.o ../../Library/Status/*.o

.PHONY: clean

