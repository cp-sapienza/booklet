PDFNAME=CP Sapienza Booklet.pdf

default: all
.PHONY: clean

all:
	pdflatex --shell-escape main
	pdflatex --shell-escape main
	mv main.pdf "$(PDFNAME)"

clean:
	-rm -r main.aux main.log main.out main.toc build

distclean: clean
	-rm "$(PDFNAME)"

print-todos:
	grep --color '\\todo{' main.tex content/*

test:
	mkdir -p build
	cd build && cmake .. && make -j8 && ./tests/tests
