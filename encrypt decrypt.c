#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void encrypt();
void decrypt();

void main()
{
    while(1){
        int c;
        printf("\n1. Encrypt \n 2.Decrypt \n");
        printf("Enter:");
        scanf("%d",&c);
        switch(c){
            case 1:
                encrypt();
                break;

            case 2:
                decrypt();
                break;

            case 3:
                exit(0);
                break;

            default:
                printf("enter a valid option..");
                break;
        }
    }

}

void encrypt()
{
    char pt[100],ct[100];
    int i,key;

    printf("Enter the string: ");
    scanf("%s",&pt);
    printf("Enter the key value: ");
    scanf("%d",&key);

    for(i=0;i<strlen(pt);i++)
    {
        if(pt[i]>=65 && pt[i]<=91){
            ct[i]=((pt[i]+key-65)%26)+65;
        }
        else if(pt[i]>=97 && pt[i]<=123){
            ct[i]=((pt[i]+key-97)%26)+97;
        }
    }
    ct[i]='\0';
    printf("Encrypted text:");
    printf("%s",&ct);
}

void decrypt()
{
    char pt[100],ct[100];
    int i,key;

    printf("Enter the string: ");
    scanf("%s",&pt);
    printf("Enter the key value: ");
    scanf("%d",&key);

    for(i=0;i<strlen(pt);i++)
    {
        if(pt[i]>=65 && pt[i]<=91){
            ct[i]=((pt[i]-key-65)%26)+65;
        }
        else if(pt[i]>=97 && pt[i]<=123){
            ct[i]=((pt[i]-key-97)%26)+97;
        }
    }
    ct[i]='\0';
    printf("Encrypted text:");
    printf("%s",&ct);
}
