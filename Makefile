#---------------------------------------------------------------------------------------------------------------------
# TARGET is the name of the output (ROM file name without extension).
# BUILD is the directory where object files & intermediate files will be placed.
# LIBBUTANO is the main directory of butano library (https://github.com/GValiente/butano).
# PYTHON is the path to the Python interpreter.
# SOURCES is a list of directories containing source code.
# INCLUDES is a list of directories containing extra header files.
# DATA is a list of directories containing binary data.
# GRAPHICS is a list of files and directories containing files to be processed by grit.
# AUDIO is a list of files and directories containing files to be processed by mmutil.
# DMGAUDIO is a list of files and directories containing files to be processed by mod2gbt and s3m2gbt.
# ROMTITLE is an uppercase ASCII, max 12 characters text string containing the output ROM title.
# ROMCODE is an uppercase ASCII, max 4 characters text string containing the output ROM code.
# USERFLAGS is a list of additional compiler flags.
#---------------------------------------------------------------------------------------------------------------------

# Update the project name here
TARGET      	:=  Pong
BUILD       	:=  build
LIBBUTANO   	:=  ../../butano
PYTHON      	:=  python3

# Add your source directories here
SOURCES     	:=  src ../../common/src

# Add include directories here
INCLUDES    	:=  include ../../common/include

# Leave DATA blank unless you use binary data
DATA        	:=

# Update GRAPHICS to include your graphics folder and shared assets (if any)
GRAPHICS    	:=  graphics ../../common/graphics

# Update AUDIO if you have audio files to process
AUDIO       	:=  audio ../../common/audio

# DMGAUDIO for Game Boy-compatible audio files (if any)
DMGAUDIO    	:=  dmg_audio ../../common/dmg_audio

# Set the ROM title (12 characters max) and code (4 characters max)
ROMTITLE    	:=  PONG WAR
ROMCODE     	:=  PWAR

# Custom compiler and linker flags
USERFLAGS   	:=
USERCXXFLAGS	:=
USERASFLAGS 	:=
USERLDFLAGS 	:=
USERLIBDIRS 	:=
USERLIBS    	:=
DEFAULTLIBS 	:=
STACKTRACE		:=

# Leave empty unless you want custom build tools
USERBUILD   	:=
EXTTOOL     	:=

#---------------------------------------------------------------------------------------------------------------------
# Export absolute butano path:
#---------------------------------------------------------------------------------------------------------------------
ifndef LIBBUTANOABS
	export LIBBUTANOABS	:=	$(realpath $(LIBBUTANO))
endif

#---------------------------------------------------------------------------------------------------------------------
# Include main makefile:
#---------------------------------------------------------------------------------------------------------------------
include $(LIBBUTANOABS)/butano.mak
