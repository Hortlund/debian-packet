prefix = /usr

all: src/electrotest-standalone

src/electrotest-standalone: src/main.c
	@echo "CFLAGS=$(CFLAGS)" | \
                fold -s -w 70 | \
                sed -e 's/^/# /'
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDCFLAGS) -o $@ $^

install: src/electrotest-standalone
	install -D src/electrotest-standalone \
                $(DESTDIR)$(prefix)/bin/electrotest-standalone
	install -D src/electrotest-standalone.1.gz \
				$(DESTDIR)$(prefix)/share/man/man1/electrotest-standalone.1.gz
clean:
	-rm -f src/electrotest-standalone

distclean: clean

uninstall:
	-rm -f $(DESTDIR)$(prefix)/bin/electrotest-standalone
	-rm -f $(DESTDIR)$(prefix)/share/man/man1/electrotest-standalone.1.gz

.PHONY: all install clean distclean uninstall
