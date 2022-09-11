PDFNAME=CP Sapienza Booklet.pdf

default: all
.PHONY: clean

all:
	pdflatex --shell-escape main
	pdflatex --shell-escape main
	mv main.pdf "$(PDFNAME)"

clean:
	-rm main.aux main.log main.out main.toc

distclean: clean
	-rm "$(PDFNAME)"

print-todos:
	grep --color '\\todo{' main.tex content/*
