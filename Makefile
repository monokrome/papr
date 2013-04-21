cc=clang++

cflags=-Wall -Wextra -Werror -Wno-long-long -Wno-variadic-macros -fexceptions -DNDEBUG -std=c++11 -x c++ -I ./include

lib_dir=lib/
bin_dir=bin/

libpapr_objects=buffer.o
libpapr_binary_filename=libpapr.so
libpapr_binary=${lib_dir}${libpapr_binary_filename}

papr_libs=${libpapr_binary_filename}
papr_objects=papr.o
papr_binary=${bin_dir}papr

build_dir=build/
cache_dir=${build_dir}cache/
objects_cache_dir=${cache_dir}objects/

mkdir=mkdir -p

all: ${libpapr_binary} ${papr_binary}

${papr_binary}: ${papr_objects}
	@${mkdir} ${bin_dir}
	${cc} -L${lib_dir} ${libpapr_binary} ${patsubst %, ${objects_cache_dir}%, ${papr_objects}} -o $@

${libpapr_binary}: ${libpapr_objects}
	@${mkdir} ${lib_dir}
	${cc} -shared ${patsubst %, ${objects_cache_dir}%, ${libpapr_objects}} -o $@

%.o: src/%.cpp
	@${mkdir} ${objects_cache_dir}
	${cc} ${cflags} -c $< -o ${objects_cache_dir}$@

clean:
	rm -rf ${lib_dir} ${bin_dir} ${build_dir}

.PHONY: all clean

