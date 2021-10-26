#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include<sys/types.h>
#include <errno.h>



int main()
{
	struct passwd *info;
	info = getpwuid(getuid());
	if(info ==NULL)
	{
		perror("Error");
		return -1;
	}
	printf("User Name: %s\n", info->pw_name);
	printf("Home Directory: %s\n", info->pw_dir);
	printf("User Information: %s\n", info->pw_gecos); 
	printf("User ID: %d\n",getuid());
	printf("User ID: %d\n",getuid());
        printf("Effective User ID: %d\n",geteuid());
	printf("Group ID: %d\n",getgid());
        printf("Effective Group ID: %d\n",getegid());


	return 0;
}
