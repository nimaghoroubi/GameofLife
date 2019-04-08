#####  usage guidelines #########################################################################################
														#
#################################################################################################################
in terminal just write make and you will get the last version, OMP compiled for you. 

syntax is dynamic, you can use as commandline argument the common ones:

1. h w graphics
example : ./gameoflife 1000 1000 1

2. h w graphics time filename thread_numbers
example: ./gameoflife 1000 1000 0 1000 1test.gal 8


##################################################################################################################
if you need to check other versions, just copy them in current directory and use "make V0" and so on. 
##################################################################################################################

1test.gal and 4test.gal are sample universes premade for correct comparison in tests. you can create or see all 
universes in god_mod (main.c). simply use ./god_mod h w filename.gal and then you are prompted to choose if you want to create or see a currently available universe

##################################################################################################################


p.s. for a fun experience use

./gameoflife 200 200 1


enjoy!

/////////////////////////////////////////////////////////
for testing go to compare_files, (compare.c)
y0ur test subject should be named final.gal
syntax is h w source file.

./a.out 4000 4000 4ksrc.gal


4ksrc.gal is a source file for checking results of 4kx4k 1000 iterations made by serial code
do not change it or you have to make another one (or email me to get a new one nima.ghoroubi@gmail.com)
//////////////////////////////////////////////////////////

V0 to V6 are different versions of the code, from serial to parallel code and with ILP and uArchitecture edits per version to improve pipeline efficiency. 
///////////////////////////////////////////////////////// 

