CFLAGS := -std=gnu99 \
	-Wall -Wextra -pedantic \
	${CFLAGS}

all: bulkw backlight
bulkw: bulkw.o
backlight: backlight.o

install: all
	install -Dm755 bulkw ${DESTDIR}/usr/bin/bulkw
	install -Dm755 backlight ${DESTDIR}/usr/bin/backlight

clean:
	${RM} bulkw backlight *.o

.PHONY: clean install
