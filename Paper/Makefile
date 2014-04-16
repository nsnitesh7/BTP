source =MPBind

all:
	rm $(source).aux
	latex $(source).tex
	bibtex $(source) 
	latex $(source).tex
	dvips $(source).dvi -o $(source).ps
	ps2pdf $(source).ps $(source).pdf
	#dvipdf  $(source).dvi $(source).pdf 
	#ps2pdf14 -dPDFSETTINGS=/prepress -dOptimize=true -dEmbedAllFonts=true $(source).ps
clean :
	rm -rf *.log *.dvi *.aux *~ core.* *.ps *.pdf *.bbl *.blg; 
