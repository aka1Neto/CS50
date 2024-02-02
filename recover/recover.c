#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
   BYTE buffer[512];
   FILE *temp = NULL;
   int jpeg = 0;
   char jpg[8] = {0};
   if(argc != 2){
      printf("Usage: ./recover IMAGE\n");
      return 1;
   }
   FILE *file = fopen(argv[1], "r");
   if(file == NULL) return 1;
   while(fread(buffer, sizeof(BYTE)*512, 1, file)==1){
      if(buffer[0]==0xFF&&buffer[1]==0xD8&&buffer[2]==0xFF&&(buffer[3]&0xF0)==0xE0){
         if(temp != NULL) fclose(temp);
         sprintf(jpg, "%03d.jpg", jpeg++);
         temp = fopen(jpg, "w");
      }
      if(temp != NULL) fwrite(buffer, sizeof(BYTE)*512, 1, temp);
   }

   if (temp != NULL) fclose(temp);

   fclose(file);
   return 0;
}