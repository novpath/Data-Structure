#include <stdio.h>

bool IsLegalSequence(char a[])
{
    int num_I = 0, num_O = 0;
    int i = 0, flag = 1;
    while (a[i] != '\0') {
        if (a[i] == 'I')
            num_I++;
        else if (a[i] == 'O') {
            num_O++;
            if (num_O > num_I) {
                flag = 0;
                break;
            }
        }
        i++;
    }
    if (num_I != num_O)
        flag = 0;
    
    return flag;
}

int main()
{
	printf("%d\n", IsLegalSequence("IOIIOIOO"));
	printf("%d\n", IsLegalSequence("IOOIOIIO"));
	printf("%d\n", IsLegalSequence("IIIOIOIO"));
	printf("%d\n", IsLegalSequence("IIIOOIOO"));
    printf("%d\n", IsLegalSequence("IIIOOIOOIO"));
    printf("%d\n", IsLegalSequence("IIIOOIOOI"));
    printf("%d\n", IsLegalSequence("IIIIIIIIIIOIIOOOOOOOOOOO"));
    printf("%d\n", IsLegalSequence("IIIOOIOOO"));

    return 0;
}

