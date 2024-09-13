while (True):
   try:
      height = int(input("Height: "));
      if height >=1 and height <= 8:
         break;
   except:
      print('', end='');

for i in range(1, height + 1):
   for j in range(1, height + 1):
      if i+j<=height:
         print(" ", end='');
      else:
         print("#", end='');

   print("  ", end='');

   for j in range(1, height + 1):
      if(j<=i):
         print("#", end='');

   print();