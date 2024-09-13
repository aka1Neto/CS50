import sys;

def main():
    card = input("Number: ");
    numbers = len(card);
    check_numbers(numbers);
    aux = int(card);
    digits = [];
    for _ in range(numbers):
        digits.insert(0, aux%10);
        aux = aux // 10;
    check_luhn(numbers,digits);
    check_brand(numbers,digits);

def invalid():
    print("INVALID\n");
    sys.exit(0);

def check_numbers(numbers):
    if(numbers < 13 or numbers > 16):
      invalid();
    elif(numbers == 14):
      invalid();

def check_luhn(numbers, digits):
   mul=0;
   t1=0;
   t2=0;
   total=0;
   if(numbers==16):
      for i in range(numbers):
         if((i+1) % 2 != 0):
            mul = digits[i]*2;
            if(mul>=10):
               t1 = t1 + ((mul//10) + (mul%10));
            else:
               t1 = t1 + mul;

         else:
            t2 = t2 + digits[i];

      total = t1 + t2;
      if(total%10!=0):
         invalid();

   else:
      for i in range(numbers):
         if((i+1) % 2 == 0):
            mul = digits[i]*2;
            if(mul>=10):
               t1 = t1 + ((mul//10) + (mul%10));
            else:
               t1 = t1 + mul;

         else:
            t2 = t2 + digits[i];

      total = t1 + t2;
      if(total%10!=0):
         invalid();

def check_brand(numbers, digits):
   if(numbers==15 and digits[0]==3):
      if(digits[1]==4 or digits[1]==7):
         print("AMEX");
      else:
         invalid();

   elif(numbers==13 or numbers==16):
      if(digits[0]==4):
         print("VISA");
      elif(digits[0]==5):
         if(digits[1]<6 and digits[1]!=0):
            print("MASTERCARD");
         else:
            invalid();

      else:
         invalid();

   else:
      invalid();

main();