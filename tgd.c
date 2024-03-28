// Faruk Siner 210229012

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>


// kelime say�s�n� bulan fonksiyon
int fWordCounter(char *str)
{
int length = strlen(str);
int count = 0;
char notword[]= " .,:;!?\n\t";

for (int i = 0; i < length; i++)
  {
    while ( i < length)
    {
        if ( strchr(notword , str[i] ) != NULL )
        { break;}
        i++;        
    }  
    
    count++;

    while (i < length)
    {
        if ( strchr(notword , str[i] ) == NULL ) 
        { break;}
        i++;      
    }   
  }

return count;
}

// c�mle say�s�n� bulan fonksiyon
int fSentenceCounter(char *str)
{
int length = strlen(str);
int count = 0;
char sentenceEnder[] = ".:;!?";

for (int i = 0; i < length; i++)
{
  while (i < length)
  {
    // 3 noktan�n �zel durumu oldu�u i�in �zellik ekledim
    if ( (strchr(sentenceEnder , str[i] ) != NULL) && (strchr(sentenceEnder , *(str+i+1) ) != NULL) ) 
    {
      {
      i+=3;
      break;
      }
    }
    
    else if ( strchr(sentenceEnder , str[i] ) != NULL )
    {break;}
   i++;  
  }
  
  count++; 
}
return count;
}

// harf say�s�n� bulan fonksiyon
int fLetterCounter(char *str)
{
int length = strlen(str);
int count = 0;

for (int i = 0; i < length; i++)
{
  if (isalpha(str[i]) != 0 )
  {
    count++;
  }
}
return count;
}


// �o�ul kelimeleri bulup yazd�ran fonksiyon
void fPluralFinder(char *str)
{
int count=0;
char *str2;
str2 = strdup(str);
char *words = strtok(str2," .,:;");
char wordarray[fWordCounter(str)][80];
// stringi kelimelere b�l�p o kelimeleri bir dizide depolad�m
for (int i = 0; i <fWordCounter(str) ; i++)
{
strcpy(wordarray[i],words);
words = strtok(NULL," .,:;");
}

// ilk �nce ka� tane olduklar�n� say�yor
for (int i = 0; i < fWordCounter(str); i++)
{
  if (strstr(wordarray[i],"lar")!=NULL || strstr(wordarray[i],"ler")!=NULL)
  {
   count++;
  }
}

printf("%d plural words found: ",count);

// daha sonra kelimeleri yazd�r�yor
for (int i = 0; i < fWordCounter(str); i++)
{
  if (strstr(wordarray[i],"lar")!=NULL || strstr(wordarray[i],"ler")!=NULL)
{
  printf("%s , ",wordarray[i]);
}
}
printf("\n");
}

// ulamalar� bulup yazd�ran fonksiyon
void fUlamaFinder(char *str)
{
int length = strlen(str) , count = 0;
char *str2;
str2 = strdup(str);  
char vowels[] = "aeıioöuü";
char consonants[] = "bcçdfgğhjklmnpqrsştvwxyz";
char *words = strtok(str2," .,:;");
char wordarray[fWordCounter(str)][80];
// stringi kelimelere b�l�p o kelimeleri bir dizide depolad�m
for (int i = 0; i <fWordCounter(str) ; i++)
{
strcpy(wordarray[i],words);
words = strtok(NULL," .,:;");
}

// ilk kelimenin son harfine ve ikinci kelimenin ilk harfine bak�yor
// e�er �art� sa�larsa sayac� art�r�yor
for (int i = 0; i <fWordCounter(str)-1; i++)
{
  if (strchr(consonants,wordarray[i][strlen(wordarray[i])-1]) != NULL && strchr(vowels,wordarray[i+1][0]) != NULL )
  {
    count++;
  }
}

printf("%d ulama bulundu: ",count);

// ka� tane oldu�unu bulduk �imdi kelimeleri yazd�r�yoruz
for (int i = 0; i <fWordCounter(str)-1; i++)
{
  if (strchr(consonants,wordarray[i][strlen(wordarray[i])-1]) != NULL && strchr(vowels,wordarray[i+1][0]) != NULL )
  {
    printf("%s %s ,",wordarray[i],wordarray[i+1]);
  }
}
printf("\n");
}

// b�y�k �nl� uyumuna uymayan kelimeleri bulup yazd�ran fonksiyon
void fBuyukUnluUymayan(char *str)
{

int length = strlen(str) , count = 0 ,sfinder=0, yfinder=0;
char *str2;
str2 = strdup(str);
char sertunlu[]="aeouAIOU"; // sert �nl�leri depolayan string
char yumusakunlu[]="eiöüEİÖÜ"; // yumu�ak �nl�leri depolayan string
char *words = strtok(str2," .,:;");
char wordarray[fWordCounter(str)][80];
// stringi kelimelere b�l�p o kelimeleri bir dizide depolad�m
for (int i = 0; i <fWordCounter(str) ; i++)
{
strcpy(wordarray[i],words);
words = strtok(NULL," .,:;");
}

// sert �nl� g�rd���nde sfinder art�yor , yumu�ak �nl� g�rd���nde yfinder art�yor
for (int i = 0; i < fWordCounter(str); i++)
{
  for (int j = 0; j < strlen(wordarray[i]) ; j++)
  {
    if (strchr(sertunlu,wordarray[i][j]) != NULL)
    {
      sfinder++;
    }
    
    if (strchr(yumusakunlu,wordarray[i][j]) != NULL)
    {
      yfinder++;
    } 
  }
  // bir kelimede hem sert hem de yumu�ak �nl� oldu�unda uyum bozuldu�u i�in her ikisinden de bulmas� gerek
  // yani ikisinin de s�f�rdan b�y�k olmas� gerek
  // ilk �nce say�s�n� buluyorum
  if (sfinder>0 && yfinder>0)
 {
   count++;
 }

sfinder=0;
yfinder=0;
}

printf("%d buyuk unlu uyumuna uymayan kelime bulundu: ",count);

// say�s�n� bulduktan sonra kelimeleri yazd�r�yorum
for (int i = 0; i < fWordCounter(str); i++)
{
  for (int j = 0; j < strlen(wordarray[i]) ; j++)
  {
    if (strchr(sertunlu,wordarray[i][j]) != NULL)
    {
      sfinder++;
    }
    
    if (strchr(yumusakunlu,wordarray[i][j]) != NULL)
    {
      yfinder++;
    } 
  }
  
  if (sfinder>0 && yfinder>0)
 {
   printf("%s , ",wordarray[i]);
 }

sfinder=0;
yfinder=0;
}
printf("\n");
}

// k���k �nl� uyumuna uymayan kelimeleri bulup yazd�ran fonksiyon
// �stteki ile hemen hemen ayn� o y�zden yorum atmadan ge�iyorum
void fKucukUnluUymayan(char *str)
{
int length = strlen(str) , count = 0 ,dfinder=0, yfinder=0;
char *str2;
str2 = strdup(str);
char duzunlu[]="aıeiAIEİ";
char yuvarlakunlu[]="oöuüOÖUÜ";
char *words = strtok(str2," .,:;");
char wordarray[fWordCounter(str)][80];

for (int i = 0; i <fWordCounter(str) ; i++)
{
strcpy(wordarray[i],words);
words = strtok(NULL," .,:;");
}

for (int i = 0; i < fWordCounter(str); i++)
{
  for (int j = 0; j < strlen(wordarray[i]) ; j++)
  {
    if (strchr(duzunlu,wordarray[i][j]) != NULL)
    {
      dfinder++;
    }
    
    if (strchr(yuvarlakunlu,wordarray[i][j]) != NULL)
    {
      yfinder++;
    } 
  }
  
  if (dfinder>0 && yfinder>0)
 {
   count++;
 }

dfinder=0;
yfinder=0;
}
printf("%d kucuk unlu uyumuna uymayan kelime bulundu: ",count);

for (int i = 0; i < fWordCounter(str); i++)
{
  for (int j = 0; j < strlen(wordarray[i]) ; j++)
  {
    if (strchr(duzunlu,wordarray[i][j]) != NULL)
    {
      dfinder++;
    }
    
    if (strchr(yuvarlakunlu,wordarray[i][j]) != NULL)
    {
      yfinder++;
    } 
  }
  
  if (dfinder>0 && yfinder>0)
 {
   printf("%s , ",wordarray[i]);
 }

dfinder=0;
yfinder=0;
}
printf("\n");
}

// sert ve yumu�ak �nl� harflerin say�s�n� buluyor
// bu da di�er ikisine benzer
void fVowelCounter(char *str)
{
 int length = strlen(str) ,sfinder=0, yfinder=0;
char *str2;
str2 = strdup(str);
char sertunlu[]="aıouAIOU"; // sert �nl�leri depolad���m string
char yumusakunlu[]="eiöüEİÖÜ";  // yumu�ak �nl�leri depolad���m string

for (int i = 0; i < length; i++)
{
  if (strchr(sertunlu,str2[i]) != NULL)
  {
    sfinder++;
  }
  
  if (strchr(yumusakunlu,str2[i]) != NULL)
  {
    yfinder++;
  }
}

printf("%d sert unlu bulundu.\n",sfinder);
printf("%d yumusak unlu bulundu.\n",yfinder);
}

// program� kullanabilmek i�in gereken men� fonksiyonu
int fMenu(char *text)
{
int menu=0;
int choice=0;
printf("/==================================================================================================/\n");
printf("THIS PROGRAM CHECKS FOR: ulama , great vowel harmony , little vowel harmony , strong-soft vowels,\n");
printf("plural words, number of words, number of sentences, number of letters\n");
printf("Is there a rule you want checked? You can enter these numbers to check them or enter 0 for exit.\n");
printf("/==================================================================================================/\n");
printf("1.ulama\n2.buyuk unlu uyumu\n3.kucuk unlu uyumu\n4.sert yumusak unluler\n5.cogul kelimeler\n6.kelime sayisi\n7.cumle sayisi\n8.harf sayisi\n");
scanf("%d",&menu);

if (menu==1)
{
  fUlamaFinder(text);

// yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==2)
{
  fBuyukUnluUymayan(text);
  
  // yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==3)
{
  fKucukUnluUymayan(text);
  
  // yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==4)
{
  fVowelCounter(text);
  
  // yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==5)
{
  fPluralFinder(text);
  
  // yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==6)
{
  printf("%d words found.\n",fWordCounter(text));
  
  // yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==7)
{
  
  printf("%d sentences found.\n",fSentenceCounter(text));
  
  // yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==8)
{
  
  printf("%d letters found.\n",fLetterCounter(text));
  
  // yeniden kullan�labilirli�i sa�lamas� i�in
  printf("Enter 1 for main menu, Enter 2 for exit.\n");
  scanf("%d",&choice);
  if (choice==1)
  {fMenu(text);}

  else if (choice==2)
  {return 0;}
}

else if (menu==0)
  {
    return 0;
  }
}


int main() {
// T�rk�e karakterleri kullanabilmek i�in gereken kodlar
setlocale(LC_ALL, "Turkish_turkish.1254");
SetConsoleOutputCP(1254);
SetConsoleCP(1254);

// Program�n i�leyece�i metnin girildi�i yer
char text[999];
printf("Please input your text.\n");
fgets(text,999,stdin);

fMenu(text);

return 0;
}

