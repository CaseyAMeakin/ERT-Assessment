# DEFINITIONS

FC=f77
FFLAGS=


# IRI source files

iri_src_dir=./src/iri_2020/src
iri_for_src=  irisub.for irifun.for iritec.for iridreg.for igrf.for \
	cira.for iriflip.for rocdrift.for iritest_sub.for
iri_for=$(patsubst %.for,${iri_src_dir}/%.for,$(iri_for_src))
iri_obj=$(patsubst %.for,%.o,$(iri_for))
iri_stdout=$(patsubst %.o.stdout,%.o,$(iri_for))
iri_stderr=$(patsubst %.o.stdout,%.o,$(iri_for))

# my c driver

my_c_driver_obj=./src/my_c_driver/iri_driver.o

# my plotter (gnu libplot based)

my_plotter_src_dir=./src/my_plotter
INC_PLPLOT=-I ./src/plotutils-2.6/include -I ${my_plotter_src_dir}
LIB_PLPLOT=-L ./src/plotutils-2.6/libplot/.libs \
	-lplot -lXaw -lXmu -lXt -lSM -lICE -lXext -lX11 -lpng -lz -lm

my_plotter_lib_src=${my_plotter_src_dir}/my_plotter_lib.c \
	${my_plotter_src_dir}/my_plotter_lib.h

# IMPLICIT COMPILATION RULES

%.o:	%.for
	${FC} ${FFLAGS} -c $< -o $@ > $@.stdout 2> $@.stderr

%.o:	%.c
	gcc -c $< -o $@ ${INC_PLPLOT} > $@.stdout 2> $@.stderr


# MAIN TARGETS

clean:
	-rm ${iri_obj} > /dev/null 2> /dev/null
	-rm iri_c.x
	-rm my_plotter.x

iri_c.x: ${iri_obj} ${my_c_driver_obj}
	@f77 -o iri_c.x \
			${my_c_driver_obj} \
			${iri_obj} \
			${my_plotter_src_dir}/my_plotter_lib.c \
			${INC_PLPLOT} \
			${LIB_PLPLOT}

