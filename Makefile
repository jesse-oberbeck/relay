.DEFAULT_GOAL := default #found at stackoverflow.com/questions/2057689/how-make-app-knows-default-target-to-build-if-no-target-is-specified

TARGET=decode encode

CPPFLAGS+=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

dispatcher: dispatcher.o
listener: listener.o

CFLAGS+=-std=c11

LDLIBS+=-lm

.PHONY: clean debug profile

default: dispatcher listener

clean:
	rm dispatcher listener
debug:CFLAGS+=-g
debug:$(TARGET)

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg
profile: $(TARGET)
