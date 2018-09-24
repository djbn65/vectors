#include "BigInteger.h"

BigInteger::BigInteger()
{
  digit_vector.clear();
  isNegative = false;
}

BigInteger::BigInteger(std::string really_big_number)
{
  std::string tmp ="";
  bool isValid = true, allZeros = false;
  int counter = 0;
  isNegative = false;
  for (int i = 0; i < really_big_number.length(); i++)
  {
    try
    {
      if (i == 0)
      {
	      if (!(really_big_number[0] == '-' || (really_big_number[0] >= 48 && really_big_number[0] <= 57))) //check to see if first digit is a - or a number
        {
          throw BigIntException();
	      }
      }
      else
      {
        if (really_big_number[i] < 48 || really_big_number[i] > 57) //check to see if the rest of the digits are numbers
        {
          throw BigIntException();
        }
      }
    }
    catch (BigIntException &e)
    {
      cout << "Error occurred: " << e.what() << endl;
      i = really_big_number.length();
      isValid = false;

    }
  }
  if (really_big_number[0] != '-') //if number isn't negative, remove leading zeros
  {
    while (counter < really_big_number.length()-1 && really_big_number[counter] == '0')
      counter++;

    for (int i = counter; i < really_big_number.length(); i++)
      tmp+=really_big_number[i];

    if (counter != 0)
      really_big_number = tmp;

    if (tmp=="" && counter == really_big_number.length()-1)
      really_big_number = "0";
  }
  else //if number is negative, remove leading zeros
  {
    really_big_number = really_big_number.substr(1);

    while (counter < really_big_number.length()-1 && really_big_number[counter] == '0')
      counter++;

    tmp+='-';
    for (int i = counter; i < really_big_number.length(); i++)
      tmp+=really_big_number[i];

    if (tmp!="-")
      really_big_number = tmp;

    if (tmp=="-" && counter == really_big_number.length()-1)
      really_big_number = "0";
  }

  if (really_big_number == "-0")
    really_big_number = "0";

  if (!isValid)
    really_big_number = "";

  if (really_big_number[0] == '-')
    isNegative = true;
  if (isValid && isNegative)
    for (int i = 0; i < really_big_number.length(); i++) //this block fills the digit vector with the string that was inputted
      digit_vector.insert(i, really_big_number[i+1]);
  else if (isValid)
    for (int i = 0; i < really_big_number.length(); i++)
      digit_vector.insert(i, really_big_number[i]);
}

std::string BigInteger::to_string()
{
  std::string tmp="";

  if(isNegative) //appends a negative if the number is supposed to be negative
    tmp+='-';

  for (int i = 0; i < digit_vector.size(); i++) //shoves the digit vector into a string to return
    tmp += digit_vector[i];

  return tmp;
}

BigInteger operator+(BigInteger &bi1, BigInteger &bi2)
{
  bool negAdd = false;
  std::string string1 = bi1.to_string();
  std::string string2 = bi2.to_string();
  std::string revAnswer = "";
  std::string answer="";
  int iCounter1, iCounter2;
  int rmd=0;

  if ((string1[0] == '-') == (string2[0] == '-'))
  {
    if (string1[0] == '-') //strips strings of negative sign if they are both negative to make addition easier
    {
      string1 = string1.substr(1);
      string2 = string2.substr(1);
      negAdd = true;
    }

    if (string1.length() < string2.length()) //swaps the two strings if the 2nd's length is larger than the first
    {
      std::string tmp = string1;
      string1 = string2;
      string2 = tmp;
    }

    if (negAdd)
    {
      iCounter1 = string1.length()-2; //get counter that keep track of where addition is happening in each string
      iCounter2 = string2.length()-2;
    }
    else
    {
      iCounter1 = string1.length()-1;
      iCounter2 = string2.length()-1;
    }

    while (iCounter1 >= 0 && iCounter2 >= 0) //add places that line up until one of the strings reach their front
    {
      int tmp = (string1[iCounter1] - '0') + (string2[iCounter2] - '0') + rmd;
      rmd = 0;
      if (tmp > 9)
      {
      	rmd = 1;
      	tmp-=10;
      }

      revAnswer+=(tmp+'0');
      iCounter1--;
      iCounter2--;
    }

    while (iCounter1 >= 0) //add the rest of the longer string to the result
    {
      int tmp = (string1[iCounter1] - '0') + rmd;
      rmd = 0;
      if (tmp > 9)
      {
      	rmd = 1;
      	tmp-=10;
      }

      revAnswer+=(tmp+'0');
      iCounter1--;
    }

    if(rmd)
      revAnswer+="1"; //if a remainder remains after the loop add one to the answer

    if (negAdd)
      revAnswer+='-'; //if answer should be negative, append the negative

    for (int i = revAnswer.length()-1; i >=0; i--) //reverse the answer to get the real result
      answer+=revAnswer[i];

    BigInteger result(answer); //make a new BigInteger to return

    return result;
  }
  else if ((string1[0] == '-') != (string2[0] == '-')) //if one of them is negative, send the probelm to operator-
  {
    BigInteger result;
    if (string1[0] == '-')
    {
      BigInteger bi3(string1.substr(1,string1.length()-2));
      result = bi2 - bi3;
    }
    else
    {
      BigInteger bi3(string2.substr(1,string2.length()-2));
      result = bi1 - bi3;
    }
    return result;
  }
}

BigInteger operator-(BigInteger &bi1, BigInteger &bi2)
{
  std::string string1 = bi1.to_string();
  std::string string2 = bi2.to_string();
  std::string revAnswer="", answer="", temp = "";
  bool negSub = false, lenSwap = false, str1IsLarger = true,       //variables to hold many different quantities
       str2IsLarger = false, removeZeros = true, isNegative=false, //regarding negatives, which is larger, etc.
       digit2IsLonger = false;

  int iCounter1, iCounter2, borrow=0, len1, len2, leadZeroCount = 0;

  if ((string1[0] == '-') == (string2[0] == '-')) //check to see if both numbers are negative or both are positive
  {
    if (string1.length() == 3 && string2.length() == 3 && //check to see if strings are single digits and if they are negative
	     string1[0] == '-' && string2[0] == '-' &&
	     (string1[1]-'0') < (string2[1]-'0'))
    {
      digit2IsLonger = true;
    }

    if (string1[0] == '-') //take off the negative sign for easier substration
    {
      string1 = string1.substr(1);
      string2 = string2.substr(1);
      negSub = true;
    }

    if (string1.length() < string2.length()) //swap the two strings if the first is shorter
    {
      std::string tmp = string1;
      string1 = string2;
      string2 = tmp;
      str2IsLarger = true;
      if (!negSub)
        lenSwap = true;
    }

    if (negSub)
    {
      iCounter1 = len1 = string1.length()-2; //counters to keep track of the position in the string
      iCounter2 = len2 = string2.length()-2;
    }
    else
    {
      iCounter1 = len1 = string1.length()-1;
      iCounter2 = len2 = string2.length()-1;
    }

    if (len1 == len2)
      for (int i = 0; i < len1; i++)
	{
	  if ((string1[i]-'0') > (string2[i]-'0')) //this block goes through same length string to see which is larger
	  {
	    i=len1;
	  }
	  else if ((string1[i]-'0') < (string2[i]-'0'))
	  {
	    std::string tmp = string1;
	    string1 = string2;
	    string2 = tmp;
	    i = len1;
	    lenSwap = true;
	    str2IsLarger = true;
	  }
	}



	if (len1 == 0 && len2 == 0 && (string1[0]-'0') < (string2[0]-'0'))
	  negSub = true;

	while (iCounter1 >= 0 && iCounter2 >= 0) //subtract parts of string that line up with each other
	{
	  int tmp = (string1[iCounter1]-'0') - (string2[iCounter2]-'0') - borrow;
	  borrow = 0;
	  if (tmp < 0 && ((len1 != 0) || (len2 != 0)))
	  {
	    borrow = 1;
	    tmp+=10;
	  }
	  else if (tmp < 0)
	  {
	    str1IsLarger = false;
	    tmp*=(-1);
	  }
	  revAnswer+=(tmp+'0');
	  iCounter1--;
	  iCounter2--;
	}

	while (iCounter1 >= 0) //append the rest of the longer string to the answer string
	{
	  int tmp = (string1[iCounter1]-'0') - borrow;
	  borrow = 0;
	  if (tmp < 0)
	  {
	    borrow = 1;
	    tmp+=10;
	  }
	  revAnswer+=(tmp+'0');
	  iCounter1--;
	}

  //this block resolves any issues with negative signs that arise
	if ((negSub && ((len1 == 0) && (len2 == 0)) && str1IsLarger) || lenSwap ||
	    (negSub && ((len1 != 0) && (len2 != 0))) || ((len1 == 0) && (len2 == 0) && !str1IsLarger))
	{
	  revAnswer+='-';
	  isNegative = true;
	}

	if (negSub && str2IsLarger && isNegative) //remove negative sign if it was added based on conditions shown
	{
	  revAnswer = revAnswer.substr(0,revAnswer.length()-1);
	  isNegative = false;
	}

  for (int i = revAnswer.length()-1; i>=0; i--) //reverse the answer to the right order
	  answer+=revAnswer[i];

	if (len1 == len2)
	  for (int i = 0; i <= len1; i++) //check if zeros need to be removed
	  {
	    if ((string1[i]-'0') == (string2[i]-'0'))
	    {
	      removeZeros = false;
	    }
	    else
	    {
	      removeZeros = true;
	      i = len1;
	    }
	  }

	if (!removeZeros) //if this is true answer was all zeros, so set answer to one zero
	  answer = '0';

	if ((len1 != 0 || len2 != 0) && removeZeros) //remove zeros depending on whether or not the number is negative
  {
	  if (!isNegative)
	  {
      	    while (answer[leadZeroCount] == '0')
	      leadZeroCount++;

	    for (int i = leadZeroCount; i < answer.length(); i++)
	      temp+=answer[i];

	    answer = temp;
	  }
	  else
	  {
	    while (answer[leadZeroCount+1] == '0')
	      leadZeroCount++;

	    temp+='-';
	    for (int i = leadZeroCount+1; i < answer.length(); i++)
	      temp+=answer[i];

	    answer = temp;
	  }
	}

	if (negSub && !str2IsLarger && answer[0] != '-')
	{
	  temp="-";
	  for (int i = 0; i < answer.length(); i++)
	    temp+=answer[i];
	  answer = temp;
	}

	if (answer == "-0")
	  answer = '0';

        if (negSub && len1 == 0 && len2 == 0 && answer[0] == '-' && digit2IsLonger)
       	  answer = answer.substr(1,answer.length()-1);

	BigInteger result(answer);

	return result;
}
else //string2 is negative and string1 is positive and this is sent to operator+ which handles it
{
  	std::string tmp="";
  	if (string1[0] == '-')
  	{
  	  BigInteger bi4, bi3(string1.substr(1,string1.length()-2));
  	  bi4 = bi2 + bi3;
  	  tmp = '-' + bi4.to_string();
  	  BigInteger result(tmp);

  	  return result;
  	}
  	else
  	{
  	  BigInteger bi3(string2.substr(1,string2.length()-2)), result;
  	  result = bi1 + bi3;
  	  return result;
  	}
  }
}
