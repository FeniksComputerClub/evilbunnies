include $(srcdir)/cwm4/root_makefile_top.am

SUBDIRS = @CW_SUBDIRS@

bin_PROGRAMS = cairotest helloworld myarea

cairotest_SOURCES = \
	cairotest.cxx

cairotest_CXXFLAGS = -std=c++11 @CAIROMM_CFLAGS@ @LIBCWD_R_FLAGS@
cairotest_LDADD = @CAIROMM_LIBS@ @LIBCWD_R_LIBS@

helloworld_SOURCES = \
	hello_world.cxx \
	HelloWorld.cxx \
	HelloWorld.h

helloworld_CXXFLAGS = -std=c++11 @GTKMM_CFLAGS@ @LIBCWD_R_FLAGS@
helloworld_LDADD = @GTKMM_LIBS@ @LIBCWD_R_LIBS@


myarea_SOURCES = \
	my_area.cxx \
	MyArea.cxx \
	MyArea.h

myarea_CXXFLAGS = -std=c++11 @GTKMM_CFLAGS@ @LIBCWD_R_FLAGS@
myarea_LDADD = @GTKMM_LIBS@ @LIBCWD_R_LIBS@

include $(srcdir)/cwm4/root_makefile_bottom.am
