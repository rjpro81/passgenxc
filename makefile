passgenx: accountmanager.c passwordgenerator.c sessionmanager.c passwordgeneratormain.c 
	gcc -o passgenx accountmanager.c passwordgenerator.c sessionmanager.c passwordgeneratormain.c

clean:
	rm passgenx
