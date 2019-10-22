#include <string.h>
#include <stdbool.h>

/// \returns true if c is a character in the string delimiters
bool is_delimiter(int c, char *delimiters)
{
  return strchr(delimiters, c) != NULL;
}

/// TODO: Change original back to a single string using replacements
/// \param original a string chopped into multiple substrings by ioopm_strtok
/// \param an array of integers where every EVEN index holds a character and every ODD index holds the place in original where the preceding EVEN character should be placed. The end is marked by an EVEN index holding 0.
/// \returns number of replacements (same as number of pairs) in replacements
int ioopm_undo_strtok(char *original, int *replacements)
{
  int nr_of_replacements = 0;

  for(int even = 0, odd = 1; replacements[even] != 0; )
  {
    int index_to_replace = replacements[odd];

    original[index_to_replace] = replacements[even];
    
    even += 2;
    odd += 2;
    nr_of_replacements++;
  }
  
  return nr_of_replacements; 
}


/// TODO: Implement in accordance with the specification 
/// \param src a null-terminated string or NULL if we want to continue tokenisation of the current string
/// \param delimiters the delimiters used to tokenise src
/// \param a pointer to replacements (see documentation in ioopm_undo_strtok) -- you can assume it has enough space
/// \returns the next token in the string 
char *ioopm_strtok(char *src, char *delimiters, int *replacements)
{
  /// Du får ändra på och kasta bort all nedanstående kod om du vill.
  /// OBS! Dessa variabler behåller sitt värde mellan funktionsanrop!
  static char *stored_src;       /// Används när src == NULL
  //static char *stored_start;     /// Värdet på src första gånger
  static char *end_of_string;
  static int replacement_index; /// Kan användas för att indexera replacements
  
  if(src)
  {
    /// Spara strängen
    char *first_token = NULL;
    stored_src = NULL;
    //stored_start = src;
    replacement_index = 0;

    char *cursor = src;
    int src_index = 0;

    //Iterate through the entire string
    while(*cursor != '\0')
    {
      //If we bump into a delimiter
      if(is_delimiter(*cursor, delimiters))
      {
	//If we don't have a first token by now, set one!
	if(first_token == NULL) first_token = src;
	
	//add to replacements here
	replacements[replacement_index] = *cursor;
	replacements[replacement_index+1] = src_index;
	replacement_index += 2;
	*cursor = '\0';
	cursor++;
	src_index++;

	//Find start of next token, skipping delimiters
	while(is_delimiter(*cursor, delimiters))
	{
	  cursor++;
	  src_index++;

	  if(*cursor == '\0') //end of string
	  {
	    return NULL;
	  }
	}
	if(stored_src == NULL) stored_src = cursor;
      }
      cursor++;
      src_index++;
    }
    end_of_string = cursor;

    //We have a finished string
    return first_token;
  }
  else
  {
    /// Om src == NULL, använd den sparade strängen 
    src = stored_src;

    if(!src)
      return NULL;

    //----------------------
    //Find the next token

    //Move forward until we find a delimiter or a null terminator
    while(*stored_src != '\0')
    {
      stored_src++;
    }

    if(stored_src == end_of_string)
      stored_src = NULL;
    else
      stored_src++;
  }

  /// Tips: du kan använda två loopar -- en för att skippa onödiga tecken i starten och en för att hitta slutet på tokenen 
  
  return src;
}
