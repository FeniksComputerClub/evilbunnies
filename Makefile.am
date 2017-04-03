include $(srcdir)/cwm4/root_makefile_top.am

SUBDIRS = @CW_SUBDIRS@

bin_PROGRAMS = cairotest

cairotest_SOURCES = \
	cairotest.cxx

cairotest_CXXFLAGS = -std=c++11 @CAIRO_CFLAGS@ @LIBCWD_R_FLAGS@
cairotest_LDADD = @CAIRO_LIBS@ @LIBCWD_R_LIBS@

include $(srcdir)/cwm4/root_makefile_bottom.am
