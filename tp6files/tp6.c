#include <stdio.h>
#include <string.h>

int main() {
	char name[80];
    while(printf("enter file name\n"), gets(name)!=0) {
		char str[80];
		FILE *f = fopen(name, "r");
		if (f != NULL) {
			while(!feof(f)) {
				if (fscanf(f, "%s", &str) > 0) {

					//printf("stroka: %s\n", str);
					if (strlen(str) % 2 == 0) {
						printf("chetnoe: %s\n", str);
					}
				}
			}
			fclose(f);
		}
		else {
			printf("file not found\n");
		}
	}
}
