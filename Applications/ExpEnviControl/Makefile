prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: ExpEnviControl

ExpEnviControl: ExpEnviControl.c ExpEnviControlRtTask.o Gui.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/RS232/RS232Handler.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o 
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< ExpEnviControlRtTask.o Gui.o ../../../BlueSpike/Library/Misc/Misc.o ../../Library/RS232/RS232Handler.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ### ExpEnviControl

ExpEnviControlRtTask.o: ExpEnviControlRtTask.c 
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ExpEnviControlRtTask

Gui.o: Gui.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### Gui

../../../BlueSpike/Library/Misc/Misc.o: ../../../BlueSpike/Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/Misc/Misc

../../Library/RS232/RS232Handler.o: ../../Library/RS232/RS232Handler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/RS232/RS232Handler

../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o: ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o

clean:
	rm -f ExpEnviControl *.o ../../../BlueSpike/Library/Misc/*.o ../../Library/RS232/RS232*.o ../../../BlueSpike/Library/RtTaskStats/*.o 

.PHONY: clean

