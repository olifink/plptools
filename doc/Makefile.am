EXTRA_DIST = ncpd.man.in plpfuse.man.in plpftp.man.in sisinstall.man.in \
	plpprintd.man.in

man_MANS = ncpd.8 plpftp.1 sisinstall.1 plpprintd.8
if BUILD_PLPFUSE
man_MANS += plpfuse.8
endif

edit = sed \
	-e 's|@MANDATE@|'`git log --pretty=format:"%ad" --date=short -1 $<.in`'|g' \
	-e 's|@pkgdatadir[@]|$(pkgdatadir)|g'

%.1: %.man Makefile
	rm -f $@ $@.tmp
	$(edit) $< >$@.tmp
	mv $@.tmp $@

%.8: %.man Makefile
	rm -f $@ $@.tmp
	$(edit) $< >$@.tmp
	mv $@.tmp $@

distclean-local:
	rm -f *.1 *.8
