bin_PROGRAMS = gplacian placian

gplacian_SOURCES = gplacian.cpp gplacian-test.cpp gplacian.h
gplacian_CXXFLAGS = \
	$(GTK_CFLAGS)	\
	$(CAIRO_CFLAGS)
gplacian_LDADD = \
	$(GTK_LIBS)	\
	$(CAIRO_LIBS)

placian_SOURCES = main.cpp placian.h placian.cpp gplacian.cpp gplacian.h
placian_CXXFLAGS = \
	$(GTK_CFLAGS)	\
	$(CAIRO_CFLAGS)
placian_LDADD = \
	$(GTK_LIBS)	\
	$(CAIRO_LIBS)
