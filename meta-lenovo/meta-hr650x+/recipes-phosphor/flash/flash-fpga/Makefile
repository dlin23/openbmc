#"Copyright ? 2019-present Lenovo
#Licensed under BSD-3, see COPYING.BSD file for details."

EXE     = flash-fpga 
OBJS    = main.o fpga.o
DEPPKGS = gio-unix-2.0 glib-2.0
CC      ?=  $(CROSS_COMPILE)gcc
#CC      ?= gcc
INCLUDES += $(shell pkg-config --cflags $(DEPPKGS))
LIBS += $(shell pkg-config --libs $(DEPPKGS))
CFLAGS = -Isub -Iadd -O2
$(EXE):$(OBJS)
	$(CC) $(LDFLAGS)  $(LDFLAGS) -o $(EXE) $(OBJS) $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXE) *.o *.d
distclean: clean
	rm -f *.c~ *.h~ *.sh~ Makefile~ config.mk~
