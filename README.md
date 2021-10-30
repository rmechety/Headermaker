# Headermaker


## Install:
### Install processus if you have the sudo power:
 ```
  git clone https://github.com/rmechety42/Headermaker.git
  cd Headermaker
  make install
  cd -
```
### Install processus if you NOT have the sudo power and you have ZSH:

```
  git clone https://github.com/rmechety42/Headermaker.git
  cd Headermaker
  make installinpath 
  cd -
```
## Usage:

  Headermaker src_folder_you_want_to_parse header_name_you_want_to_create [-inc nameoftheheaderyouwanttoinclude ....]</br>
  A good idea can be to add a rule in your makefile like : </br>
  ```

all : header
      dothings
header :
	@Headermaker src inc/prototypes.h -inc structs define

```
Like this you don't have to run the command every time you want to compile your project

## How to change the 42Header:
  go to src/main.cpp and look at the top of the file. change the HEADER define.



Enjoy!

if you have any question or bug ask it on github or contact me at mechety.rayan@gmail.com


https://user-images.githubusercontent.com/51334669/137965520-df155516-be54-40fd-8ada-c373db99e1ae.mp4

