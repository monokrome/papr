cc=clang++
cflags=-Wall -Wextra -Werror -Wno-long-long -Wno-variadic-macros -fexceptions -DNDEBUG -std=c++11 -x c++ -I ./include

core_objects=papr.o
core_binary=bin/papr

lib_dir=lib/
bin_dir=bin/

mkdir=mkdir -p

all: ${core_binary}

${core_binary}: ${core_objects}
	@${mkdir} ${bin_dir}
	${cc} ${patsubst %, lib/%, ${core_objects}} -o $@

%.o: src/%.cpp
	@${mkdir} ${lib_dir}
	${cc} ${cflags} -c $< -o ${lib_dir}$@

clean:
	rm -rf ${lib_dir} ${bin_dir}

.PHONY: all clean

