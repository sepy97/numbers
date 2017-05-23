#include "scanner.h"
#include "tree.h"
#include "parser.h"
#include "code.h"

int main(int argc, char **argv)
{
	int	fd;
	if (argc >= 2)
	{
		close(0);
		fd = open(argv[1],0);
		if (fd != 0) 
		{
			fprintf(stderr, "Cannot open file '%s' for reading\n", argv[1]);
			exit(1);
		}
	}
    	yyparse();
}

