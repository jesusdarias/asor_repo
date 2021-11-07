#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char ** argv)
{

	if(argc!=2)
	{
 		printf("Usage: ./ejercicio_17 <filename>\n");
		return -1;
	}

	DIR *dir = opendir(argv[1]);

	if(dir == NULL)
	{
		perror("Error al leer el directorio");
		return -1;
	}
	
	struct dirent *entries = readdir(dir);
	int bytes = 0;

	while(entries!=NULL)
	{
		if(entries->d_type == DT_REG)
		{
		
			printf("%s", entries->d_name);
			
			struct stat buf;
			stat(entries->d_name, &buf);
			bytes += buf.st_size;
			if((buf.st_mode & S_IXUSR) == S_IXUSR)
				printf("*");
			printf("\n");
		
		}
		else if(entries->d_type == DT_DIR)
		{
			printf("%s/\n", entries->d_name);
		}
		else if(entries->d_type == DT_LNK)
		{
			printf("%s->", entries->d_name);
			char nombre[255];
			int lastchar=readlink(entries->d_name, nombre, 255);
			nombre[lastchar]='\0';
			printf("%s\n", nombre);
			struct stat buf;
			stat(entries->d_name, &buf);
			bytes += buf.st_size;
		}
		else
		{	
			struct stat buf;
			stat(entries->d_name, &buf);
			bytes += buf.st_size;
		}

		entries = readdir(dir);
			
	}
	closedir(dir);
	int kilobytes = bytes/1000;
	printf("Total kB: %d\n", kilobytes);

	
	return 0;
}



