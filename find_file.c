/*
Implementing linux command `find` including following flags:
-maxdepth x
-mindepth x
-size +x
-size -x
-size x
-name filename
-iname filename
-perm permissions
-empty
-type filetype
*/
#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<bsd/unistd.h>//strmode()
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>//exit()
#include<ctype.h>//isdigit()
#include<sys/types.h>
#include<time.h>

int file_access_details(time_t file_time,int hours,char *argv)
{
	int temp;
	if(strcmp(argv,"-atime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}
	
	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) == (temp * hours))	
		return 1;
	else
		return -1;
}

int file_access_details_less(time_t file_time,int hours, char *argv)
{
	int temp;
	if(strcmp(argv,"-atime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}

	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) < (temp * hours))	
		return 1;
	else
		return -1;
}

int file_access_details_more(time_t file_time,int hours,char *argv)
{
	int temp;
	if(strcmp(argv,"-atime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}
	
	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) > (temp * hours))	
		return 1;
	else
		return -1;
}

int file_change_details(time_t file_time,int hours,char *argv)
{
	int temp;
	if(strcmp(argv,"-ctime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}
	
	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) == (temp * hours))	
		return 1;
	else
		return -1;
}


int file_change_details_less(time_t file_time,int hours, char *argv)
{
	int temp;
	if(strcmp(argv,"-ctime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}

	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) < (temp * hours))	
		return 1;
	else
		return -1;
}

int file_change_details_more(time_t file_time,int hours,char *argv)
{
	int temp;
	if(strcmp(argv,"-ctime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}

	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) > (temp * hours))	
		return 1;
	else
		return -1;
}


int file_modification_details(time_t file_time,int hours,char *argv)
{
	int temp;
	if(strcmp(argv,"-mtime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}
	
	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) == (temp * hours))	
		return 1;
	else
		return -1;
}


int file_modification_details_less(time_t file_time,int hours, char *argv)
{
	int temp;
	if(strcmp(argv,"-mtime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}

	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) < (temp * hours))	
		return 1;
	else
		return -1;
}

int file_modification_details_more(time_t file_time,int hours,char *argv)
{
	int temp;
	if(strcmp(argv,"-mtime") == 0)
	{
		temp = 3600*24;
	}
	else
	{
		temp = 60*24;
	}

	time_t curtime;
	
	time(&curtime);

	if((curtime - file_time) > (temp * hours))	
		return 1;
	else
		return -1;
}


int check_permissions(char *perm, char *argv)//check files with given permissions
{
	int i = 0;
	int j = 1;

	for(i = 0, j = 1; perm[j] != '\0' || argv[i] == '\0'; i++,j += 3)
	{

		if(i == 0)// user permissions
		{
			if(argv[i] == 55)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == 'w' && perm[j+2] == 'x'))
					return -1;

			}
			else
			if(argv[i] == 54)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == 'w' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 53)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == '-' && perm[j+2] == 'x'))
					return -1;
			}
			else
			if(argv[i] == 52)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == '-' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 51)
			{	
				if(!(perm[j] == '-' && perm[j+1] == 'w' && perm[j+2] == 'x'))
					return -1;
			}
			else
			if(argv[i] == 50)
			{	
				if(!(perm[j] == '-' && perm[j+1] == 'w' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 49)
			{	
				if(!(perm[j] == '-' && perm[j+1] == '-' && perm[j+2] == 'x'))
					return -1;
			}
			else
			{	
				printf("Error: -perm expects argument of type mode_t\n");
				exit(1);
			}
		}
	
		if(i == 1)//group permissions
		{
			if(argv[i] == 55)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == 'w' && perm[j+2] == 'x'))
					return -1;

			}
			else
			if(argv[i] == 54)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == 'w' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 53)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == '-' && perm[j+2] == 'x'))
					return -1;
			}
			else
			if(argv[i] == 52)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == '-' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 51)
			{	
				if(!(perm[j] == '-' && perm[j+1] == 'w' && perm[j+2] == 'x'))
					return -1;
			}
			else
			if(argv[i] == 50)
			{	
				if(!(perm[j] == '-' && perm[j+1] == 'w' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 49)
			{	
				if(!(perm[j] == '-' && perm[j+1] == '-' && perm[j+2] == 'x'))
					return -1;
			}
			else
			{	
				printf("Error: -perm expects argument of type mode_t\n");
				exit(1);
			}
	
		}
		
		if(i == 2)//other permissions
		{
			if(argv[i] == 55)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == 'w' && perm[j+2] == 'x'))
					return -1;

			}
			else
			if(argv[i] == 54)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == 'w' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 53)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == '-' && perm[j+2] == 'x'))
					return -1;
			}
			else
			if(argv[i] == 52)
			{	
				if(!(perm[j] == 'r' && perm[j+1] == '-' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 51)
			{	
				if(!(perm[j] == '-' && perm[j+1] == 'w' && perm[j+2] == 'x'))
					return -1;
			}
			else
			if(argv[i] == 50)
			{	
				if(!(perm[j] == '-' && perm[j+1] == 'w' && perm[j+2] == '-'))
					return -1;
			}
			else
			if(argv[i] == 49)
			{	
				if(!(perm[j] == '-' && perm[j+1] == '-' && perm[j+2] == 'x'))
					return -1;
			}
			else
			{	
				printf("Error: -perm expects argument of type mode_t\n");
				exit(1);
			}
	
		}
	}

		return 1;
}


int check_mode(char *str)// check if mode is permissible value
{
	int i = 0;
	
	if(strlen(str) != 3)
		return -1;

	for( i = 0; str[i] != '\0';i++)
	{
		if(0 >= str[i] - '0' && 8 <= str[i] - '0')
			return -1;
	}
	
	return 1;
}

int check_int(char *str)// check if given argument is integer or not
{
	int i = 0;
	
	for(i = 0; str[i] != '\0';i++)
	{
		if(!isdigit(str[i]))
			return -1;
	}

	return 1;
}


void directory_recursive(char *argv[],char *from_dir,int argc,int maxdepth, int mindepth)// Recursively traverse files in directory
{
	int ret = 0;
	int size;
	int n = 0;
	int file_found = 0;
	int file_notfound = 0;

	char read_dir[4096];
	char *perm = (char *)malloc(1024);

        DIR *fd_dir = opendir(from_dir);
	
        struct dirent *entry;
	struct stat buff;

        while((entry = readdir(fd_dir)) != NULL)
        {
		bzero(read_dir,4096);
		file_found = 0;
		file_notfound = 0;
		
		if(entry->d_name[0] == '.' || strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
			continue;

		strcpy(read_dir,from_dir);

		if(read_dir[strlen(read_dir) - 1] !='/')
			strcat(read_dir,"/");

		strcat(read_dir,entry->d_name);
		stat(read_dir,&buff);
		
		if((S_IFDIR ^(S_IFMT & buff.st_mode)) == 0)
                {	
			if(maxdepth > 0)
                		directory_recursive(argv,read_dir,argc,maxdepth - 1,mindepth - 1);
		}
		
		if( mindepth <= 0)
		{
			n = 1;
			while(n < argc)
			{
				if(strcmp(argv[n],"-size") == 0)
				{
					if(n == argc -1)
					{
						printf("Error: -size expects argument\n");
						closedir(fd_dir);
						exit(1);
					}
				
					if(argv[n+1][0] == '-' || argv[n+1][0] == '+')
					{
						ret = check_int(&argv[n+1][1]);
			
						if(ret == -1)
						{
							printf("Error: -size expects integer value\n");
							closedir(fd_dir);
							exit(1);
						}
						else
						{
							size = atoi(&argv[n+1][1]);
							if(argv[n+1][0] == '-')
							{
								if(buff.st_size > size)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}
							}
							else if(argv[n+1][0] == '+')
							{
								if(buff.st_size < size)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}
							}
						}
					}
					else
					{
						ret = check_int(argv[n+1]);
					
						if(ret == -1)
						{
							printf("Error: -size expects integer value\n");
							closedir(fd_dir);
							exit(1);
						}
						else
						{
							size = atoi(argv[n+1]);
			
							if(size != buff.st_size)
							{
								file_notfound = 1;
								break;
							}
							else
							{
								file_found = 1;
							}
						}
					}	
				}

				if(strcmp(argv[n],"-name") == 0)
				{
					if(strcmp(argv[n-1],"-not") != 0)
					{

						if(strcmp(entry->d_name,argv[n+1]) != 0)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}
					}
					else
					{
						if(strcmp(entry->d_name,argv[n+1]) != 0)
						{
							file_found = 1;
						}
						else
						{
							file_notfound = 1;
							break;
						}

					}
				}
				
				if(strcmp(argv[n],"-iname") == 0)
				{
					if(strcmp(argv[n-1],"-not") != 0)
					{
						if(strcasecmp(entry->d_name,argv[n+1]) != 0)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}
					}
					else
					{
						if(strcmp(entry->d_name,argv[n+1]) != 0)
						{
							file_found = 1;
						}
						else
						{
							file_notfound = 1;
							break;
						}
					}
				}

				if(strcmp(argv[n],"-type") == 0)
				{
					if(strcmp(argv[n+1],"s") == 0)
					{
						if((S_IFSOCK ^(S_IFMT & buff.st_mode)) != 0)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}
					}
					
					if(strcmp(argv[n+1],"l") == 0)
					{
						if((S_IFLNK ^(S_IFMT & buff.st_mode)) != 0)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}
					}
					
					if(strcmp(argv[n+1],"f") == 0)
					{
						if((S_IFREG ^(S_IFREG & buff.st_mode)) != 0)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}
					}
					
					if(strcmp(argv[n+1],"d") == 0)
					{
						if((S_IFDIR ^(S_IFDIR & buff.st_mode)) != 0)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}
					}
				}

				if(strcmp(argv[n],"-empty") == 0)
				{
					if(buff.st_size != 0)
					{
						file_notfound = 1;
						break;
					}
					else
					{
						file_found = 1;
					}				

				}
		
				if(strcmp(argv[n],"-perm") == 0)
				{
					ret = check_mode(argv[n+1]);		

					if(ret == -1)
					{
						printf("Error: -perm expects argument of type mode_t\n");
						exit(1);
					}
						
					strmode(buff.st_mode,perm); // Get file permissions in string
					ret = check_permissions(perm,argv[n+1]);	
	
					if(ret == -1)
					{
						file_notfound = 1;
						break;
					}
					else
					{
						file_found = 1;
					}				
					
				}
				
				if(strcmp(argv[n],"-mtime") == 0 || strcmp(argv[n],"-mmin") == 0)
				{
					int ret2;
					int ret1;

					ret = check_int(argv[n+1]);
					if( ret == -1)
					{
						ret1 = check_int(&argv[n+1][1]);
						if(ret1 == -1)
						{
							printf("Error: -mtime expects integer argument\n");
							exit(1);
						}
						else
						{
							if(argv[n+1][0] == '+')
							{
								ret2 = file_modification_details_more(buff.st_mtime,atoi(&argv[n+1][1]),argv[n]);
								if(ret2 == -1)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}				

							}
							else if(argv[n+1][0] == '-')
							{
								ret2 = file_modification_details_less(buff.st_mtime,atoi(&argv[n+1][1]),argv[n]);
								if(ret2 == -1)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}				

							}
						

						}
					}
					else
					{
						ret1 = file_modification_details(buff.st_mtime,atoi(argv[n+1]),argv[n]);
						if(ret1 == -1)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}				
			
					}	
				}

				if(strcmp(argv[n],"-ctime") == 0 || strcmp(argv[n],"-cmin") == 0)
				{
					int ret2;
					int ret1;

					ret = check_int(argv[n+1]);
					if( ret == -1)
					{
						ret1 = check_int(&argv[n+1][1]);
						if(ret1 == -1)
						{
							printf("Error: -ctime expects integer argument\n");
							exit(1);
						}
						else
						{
							if(argv[n+1][0] == '+')
							{
								ret2 = file_change_details_more(buff.st_ctime,atoi(&argv[n+1][1]),argv[n]);
								if(ret2 == -1)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}				

							}
							else if(argv[n+1][0] == '-')
							{
								ret2 = file_change_details_less(buff.st_ctime,atoi(&argv[n+1][1]),argv[n]);
								if(ret2 == -1)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}				

							}
						

						}
					}
					else
					{
						ret1 = file_change_details(buff.st_ctime,atoi(argv[n+1]),argv[n]);
						if(ret1 == -1)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}				
			
					}	
				}
				
				if(strcmp(argv[n],"-atime") == 0 || strcmp(argv[n],"-amin") == 0)
				{
					int ret2;
					int ret1;

					ret = check_int(argv[n+1]);
					if( ret == -1)
					{
						ret1 = check_int(&argv[n+1][1]);
						if(ret1 == -1)
						{
							printf("Error: -atime expects integer argument\n");
							exit(1);
						}
						else
						{
							if(argv[n+1][0] == '+')
							{
								ret2 = file_access_details_more(buff.st_atime,atoi(&argv[n+1][1]),argv[n]);
								if(ret2 == -1)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}				

							}
							else if(argv[n+1][0] == '-')
							{
								ret2 = file_access_details_less(buff.st_atime,atoi(&argv[n+1][1]),argv[n]);
								if(ret2 == -1)
								{
									file_notfound = 1;
									break;
								}
								else
								{
									file_found = 1;
								}				

							}
						

						}
					}
					else
					{
						ret1 = file_access_details(buff.st_atime,atoi(argv[n+1]),argv[n]);
						if(ret1 == -1)
						{
							file_notfound = 1;
							break;
						}
						else
						{
							file_found = 1;
						}				
			
					}	
				}
				n++;
				
			}
		if(file_found == 1 && file_notfound == 0)
			printf("%s\n",read_dir);		

		}
			
        }
	closedir(fd_dir);
}

int main(int argc, char *argv[])
{
	char dir[4096];
	int maxdepth = -1;
	int mindepth = -1;
	int ret = 0;
	int i = 0;

	if(argv[1][0] == '-')
		strcpy(dir,".");
	else
		strcpy(dir,argv[1]);
 
	for( i = 1 ; i < argc; i++)
	{
		if(strcmp(argv[i],"-maxdepth") == 0)
		{
			ret = check_int(argv[i+1]);
			
			if(ret == -1)
			{
				printf("Error : Integer value expected for MAXDEPTH\n");
				exit(1);
			}
			else
			{
				maxdepth = atoi(argv[i+1]);
			}
		}
		
		if(strcmp(argv[i],"-mindepth") == 0)
		{
			ret = check_int(argv[i+1]);
			
			if(ret == -1)
			{
				printf("Error : Integer value expected for MINDEPTH\n");
				exit(1);
			}
			else
			{
				mindepth = atoi(argv[i+1]);
			}
		}
		
	}

	directory_recursive(argv,dir,argc,maxdepth - 1,mindepth - 1);	
	return 0;
}
