#include <stdio.h>

int main()
{
	FILE *pF = fopen("test.txt","w");

	fprint(pF, "Spongebob");

	fclose(pF);

return 0;

}
