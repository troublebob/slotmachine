# Description : Terminal slot machine game

Notes on naming convention:
Subroutine specific variables are prefixed with their type. Parameters passed
where possible have the same name without the prefix as the passed in variable.
Global variables start with a capital letter and are not prefixed with type.

Notes on program structure:
The actual work is done in the playing_the_game() function. A random int 0/1/2
is assigned to a fruit structure which is added to the slot structure. 
The money handling and bet results are done in seperate functions.

Heirarchy:
Main--PrintMenu
|-GetOption
|-ProcessOption--PlayTheGame--CollectBet
|-NameOfFruit
|-BetResult  --CheckCredit