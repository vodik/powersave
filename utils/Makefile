CFLAGS := -std=gnu99 \
	-Wall -Wextra -pedantic \
	${CFLAGS}

all: bulkw
bulkw: bulkw.o

install: all
	install -Dm755 bulkw ${DESTDIR}/usr/bin/bulkw

clean:
	${RM} bulkw *.o

.PHONY: clean install
