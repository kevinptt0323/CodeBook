all:
	xelatex -interaction=nonstopmode --shell-escape codebook.tex

clean:
	rm codebook.aux codebook.log codebook.out codebook.toc
