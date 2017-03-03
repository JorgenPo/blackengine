# Code style rules

## Classes

 - Class names must be UpperCamelCased
 - Class names must be as short as possible
 - Class names must be informative

 - Classes should be in different h, cpp files

 - All classes must be in ::black namespace

 - All methods must be lowerCamelCased
 - All methods must be as short as possible
 - All methods must be extreemely informative
 - All methods must be grouped by semantic in class
 - All getters and setters that are short must be defined in a class
 - Access specifiers must be declared in a following order: public, protected, private

 - All fields must be declared in the bottom of a class
 - All field names must be typed in lowerCase style
 - All field names must be informative
 - All field names must be as short as possible
 - All fields that are basic or simple types must be initialized their defaults directly in class definition
 - All fields must have their own access specifiers in well-known order (see above)

## Global rules

 - Reference (&) sign must be used in that way:

   int& name(float &param);
   int& variable;

 - Dereference sign must be used in that way:

   int* name(float *param);
   int* variable;

 - All case operator's must followed by that rule:

   if ( hereIsRule ) {
     // case
   } else {
     // else
   }
