build: tema1

tema1: tema1.obj
	link /nologo /out:tema1 compare.lib tema1.obj

tema1.obj: source.c
	cl /c /MD source.c /Fotema1.obj

clean:
	del tema1 *.obj