PDFNAME=CP Sapienza Booklet.pdf

default: all
.PHONY: clean

all:
	pdflatex main
	pdflatex main
	mv main.pdf "$(PDFNAME)"

clean:
	-rm main.aux main.log main.out main.toc

distclean: clean
	-rm "$(PDFNAME)"

print-todos:
	grep --color '\\todo' content/*
