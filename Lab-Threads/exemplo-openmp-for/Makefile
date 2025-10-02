CC=gcc
CXX=g++

all: main

main: parallel-region png pdf
	@echo "Ver os arquivos .omplower e .ompexp"

parallel-region:
	${CC} -fopenmp -fdump-tree-ompexp example-for-directive.c -o example-for-directive.exe
	${CC} -fopenmp -fdump-tree-ompexp-graph example-for-directive.c
	
	# -fno-asynchronous-unwind-tables retira Call Frame Information .cfi_startproc, .cfi_endproc
	${CC} -fopenmp example-for-directive.c -fno-asynchronous-unwind-tables -S -o example-for-directive.s	

clean:
	find . -type f \( ! \( -iname "*.c" -or -iname "Makefile" -or -iname "*.ompexp" -or -iname "dump2dot" -or -iname "*.sh" \) \) -delete

png:
	../scripts/gen-png.sh

pdf:
	../scripts/gen-pdf.sh
