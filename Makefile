compile: 
	qmake -o QMakefile PacMan.pro
	make -f QMakefile

run: compile
	./PacMan

doxygen:
	doxygen doc/Doxyfile
	
clean:
	make clean -f QMakefile
	rm PacMan QMakefile 

pack:
	zip -r xkubic45_xmacek27.zip src/ log/ examples/ doc/ images/ maps/ PacMan.pro Makefile README.txt

