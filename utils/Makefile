CFLAGS := -std=gnu99 \
	-Wall -Wextra -pedantic \
	${CFLAGS}

all: backlight
backlight: backlight.o

install: all
	install -Dm5755 backlight ${DESTDIR}/usr/bin/backlight

clean:
	${RM} backlight *.o

.PHONY: clean install
