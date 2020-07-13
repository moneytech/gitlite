PROG=	gitlite

WARNS=	2
MK_MAN=	no
MK_DEBUG_FILES=no

SRC=	gitlite.c

CFLAGS=	-I/usr/local/include -L/usr/local/lib -g
LDFLAGS=-lgit2 -Wl

.include <bsd.prog.mk>
