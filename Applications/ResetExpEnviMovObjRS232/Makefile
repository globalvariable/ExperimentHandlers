prefix := $(shell rtai-config --prefix)

ifeq ($(prefix),)
$(error Please add <rtai-install>/bin to your PATH variable)
endif

CC = $(shell rtai-config --cc)
LXRT_CFLAGS = $(shell rtai-config --lxrt-cflags)
LXRT_LDFLAGS = $(shell rtai-config --lxrt-ldflags)
MATH_FLAGS = -lm
GTK_FLAGS = $(shell pkg-config --cflags --libs gtk+-2.0 gtkdatabox)

all: ResetExpEnviMovObjRS232

ResetExpEnviMovObjRS232: ResetExpEnviMovObjRS232.c ../../../BlueSpike/Library/Misc/Misc.o ../../Library/RS232/RS232Handler.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o 
	$(CC) $(LXRT_CFLAGS) $(LXRT_LDFLAGS) $(MATH_FLAGS) $(GTK_FLAGS) -o $@ $< ../../../BlueSpike/Library/Misc/Misc.o ../../Library/RS232/RS232Handler.o ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o ### ResetRS232

../../../BlueSpike/Library/Misc/Misc.o: ../../../BlueSpike/Library/Misc/Misc.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/Misc/Misc

../../Library/RS232/RS232Handler.o: ../../Library/RS232/RS232Handler.c
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../Library/RS232/RS232Handler

../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o: ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.c	
	$(CC) $(LXRT_CFLAGS) -c -o $@ $< $(LXRT_LDFLAGS) $(GTK_FLAGS)			### ../../../BlueSpike/Library/RtTaskStats/RtTaskStats.o

clean:
	rm -f ResetExpEnviMovObjRS232 *.o ../../../BlueSpike/Library/Misc/*.o ../../Library/RS232/RS232*.o ../../../BlueSpike/Library/RtTaskStats/*.o 

.PHONY: clean
