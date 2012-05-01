prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: TrialHandler

TrialHandler: TrialHandler.c Gui.o GuiTrialHandler.o ../../../../BlueSpike/Library/Misc/Misc.o ../../../Library/Messages/Gui2TrialHand.o ../../../Library/TrialsData/TrialTypes.o  ../../../Library/Combos/TrialTypesCombo.o TrialHandlerRtTask.o TrialDurationHandlerRtTask.o ../../../Library/TrialsData/TrialStats.o ../../../Library/TrialsData/TrialData.o ../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o HandleGui2TrialHandMsgs.o ../../../Library/Status/TrialStatus.o
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< Gui.o GuiTrialHandler.o ../../../../BlueSpike/Library/Misc/Misc.o ../../../Library/Messages/Gui2TrialHand.o ../../../Library/TrialsData/TrialTypes.o ../../../Library/Combos/TrialTypesCombo.o TrialHandlerRtTask.o TrialDurationHandlerRtTask.o ../../../Library/TrialsData/TrialStats.o ../../../Library/TrialsData/TrialData.o ../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o HandleGui2TrialHandMsgs.o ../../../Library/Status/TrialStatus.o ### TrialHandler

Gui.o: Gui.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### Gui

GuiTrialHandler.o: GuiTrialHandler.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### GuiTrialHandler

TrialHandlerRtTask.o: TrialHandlerRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialHandlerRtTask

TrialDurationHandlerRtTask.o: TrialDurationHandlerRtTask.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### TrialDurationHandlerRtTask

HandleGui2TrialHandMsgs.o: HandleGui2TrialHandMsgs.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### HandleGui2TrialHandMsgs

../../../../BlueSpike/Library/Misc/Misc.o: ../../../../BlueSpike/Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/Misc/Misc

../../../Library/Messages/Gui2TrialHand.o: ../../../Library/Messages/Gui2TrialHand.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Messages/Gui2TrialHand

../../../Library/TrialsData/TrialTypes.o: ../../../Library/TrialsData/TrialTypes.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/TrialsData/TrialTypes.o

../../../Library/TrialsData/TrialStats.o: ../../../Library/TrialsData/TrialStats.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/TrialsData/TrialStats.o

../../../Library/TrialsData/TrialData.o: ../../../Library/TrialsData/TrialData.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/TrialsData/TrialData.o

../../../Library/Status/TrialStatus.o: ../../../Library/Status/TrialStatus.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../Library/Status/TrialStatus.o

../../../Library/Combos/TrialTypesCombo.o: ../../../Library/Combos/TrialTypesCombo.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/Combos/TrialTypesCombo.o

../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o: ../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o

clean:
	rm -f BMIExpController *.o ../../../../BlueSpike/Library/Misc/*.o ../../../Library/Messages/*.o ../../../Library/TrialsData/*.o ../../../Library/Combos/*.o ../../../../BlueSpike/Library/RtTaskStats/*.o ../../../Library/Status/*.o

.PHONY: clean

