
# How to use this makefile:
#
#  > make prepare  # copy all source files to a working directory (src)
#  > make          # build the default target (USBdemo.bin)
#  > make debug    # run the GDB debugger
#  > make clean    # remove all temporary files in the working directories (src, obj, dep)

#  +++ CHECK ALL THE SETTINGS BELOW AND ADAPT THEM IF NEEDED +++

# default target and name of the image and executable files to generate
TARGET     = progetto

# path to the root folder of the STM32Cube platform
STM_DIR   = /C/Users/lucav/Documents/Uni/SistemiEmbedded/STM32Cube_FW_F3_V1.11.0

# Board and MCU  names as used in the linker script path and file name, e.g. "$(STM_DIR)/Demonstrations/SW4STM32/STM32F4-DISCO/STM32F407VGTx_FLASH.ld"
BOARD_UC   = STM32F3-Discovery
MCU_UC     = STM32F303VC

# board name as used in the STM32cube Drivers/BSP folder, e.g. "$(STM_DIR)/Drivers/BSP/STM32F4-Discovery"
BSP_BOARD   = STM32F3-Discovery

# MCU name as used in the .s source file name, e.g. "startup_stm32f407xx.s"
MCU_LC     = stm32f303xc

# pre-processor symbol to be defined for the compilation (will be used in a -Dxxx flag in gcc)
MCU_MC     = STM32F303xC


###############################################################################
# Directories

BSP_DIR    = $(STM_DIR)/Drivers/BSP
HAL_DIR    = $(STM_DIR)/Drivers/STM32F3xx_HAL_Driver
CMSIS_DIR  = $(STM_DIR)/Drivers/CMSIS
DEV_DIR    = $(CMSIS_DIR)/Device/ST/STM32F3xx
STEMWIN_DIR    = $(STM_DIR)/Middlewares/ST/STemWin
DEM_DIR    = $(STM_DIR)/Projects/$(BSP_BOARD)/p1Gruppo13



###############################################################################
# Source files

SRCS = \
$(HAL_DIR)/Src/stm32f3xx_hal.c \
$(HAL_DIR)/Src/stm32f3xx_hal_cortex.c \
$(HAL_DIR)/Src/stm32f3xx_hal_dma.c \
$(HAL_DIR)/Src/stm32f3xx_hal_gpio.c \
$(HAL_DIR)/Src/stm32f3xx_hal_rcc.c \
$(HAL_DIR)/Src/stm32f3xx_hal_spi.c \
$(HAL_DIR)/Src/stm32f3xx_hal_spi_ex.c \
$(HAL_DIR)/Src/stm32f3xx_hal_tim.c \
$(HAL_DIR)/Src/stm32f3xx_hal_tim_ex.c \
$(BSP_DIR)/$(BSP_BOARD)/stm32f3_discovery.c \
$(DEM_DIR)/dev/main.c \
$(DEM_DIR)/dev/stm32f3xx_hal_msp.c \
$(DEM_DIR)/dev/stm32f3xx_it.c \
$(DEM_DIR)/dev/system_stm32f3xx.c \
$(DEM_DIR)/dev/LCDConf.c \
$(DEM_DIR)/dev/GUIConf.c \
$(DEM_DIR)/dev/eslogo.c \
$(DEM_DIR)/dev/stm32logo.c \
$(STEMWIN_DIR)/os/GUI_X.c

	
# remove paths from the file names
SRCS_FN = $(notdir $(SRCS))

LDFILE     = $(DEM_DIR)/dev/$(MCU_UC)Tx_FLASH.ld


###############################################################################
# Tools

PREFIX     = arm-none-eabi
CC         = $(PREFIX)-gcc
AR         = $(PREFIX)-ar
OBJCOPY    = $(PREFIX)-objcopy
OBJDUMP    = $(PREFIX)-objdump
SIZE       = $(PREFIX)-size
GDB        = $(PREFIX)-gdb
OCD        = openocd

###############################################################################
# Options

# Defines (-D flags)
DEFS       = -D$(MCU_MC) -DUSE_HAL_DRIVER
DEFS       += -DUSE_DBPRINTF

# Include search paths (-I flags)
INCS       = -Isrc
INCS      += -I$(STM_DIR)/Drivers/CMSIS/Include
INCS      += -I$(STM_DIR)/Drivers/CMSIS/Device/ST/STM32F3xx/Include
INCS      += -I$(STM_DIR)/Drivers/STM32F3xx_HAL_Driver/Inc
INCS      += -I$(STM_DIR)/Drivers/BSP/STM32F3-Discovery
INCS      += -I$(DEM_DIR)/Inc
INCS      += -I$(STEMWIN_DIR)/inc

# Library search paths (-L flags)
LIBS       = -L$(DEM_DIR)/lib
LIB = emWin_nosnts_cm4f_gcc
# Compiler flags
CFLAGS     = -Wall -g -std=c99 -Os
CFLAGS    += -mlittle-endian -mcpu=cortex-m4 -march=armv7e-m -mthumb
CFLAGS    += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS    += -ffunction-sections -fdata-sections
CFLAGS    += $(INCS) $(DEFS)

# Linker flags
LDFLAGS    = -Wl,--gc-sections -Wl,-Map=$(TARGET).map $(LIBS) -Tsrc/linkerScript.ld

# Enable Semihosting
LDFLAGS   += --specs=rdimon.specs -lc -lrdimon
#LDFLAGS   += --specs=nosys.specs --specs=nano.specs --specs=rdimon.specs -lc -lrdimon

# Source search paths
VPATH      = ./src
VPATH     += $(BSP_DIR)
VPATH     += $(HAL_DIR)/Src
VPATH     += $(DEV_DIR)/Source/

# Debugger flags
GDBFLAGS   =

# generate OBJS and DEPS target lists by prepending obj/ and dep prefixes
OBJS       = $(addprefix obj/,$(SRCS_FN:.c=.o))
DEPS       = $(addprefix dep/,$(SRCS_FN:.c=.d))


###################################################

.PHONY: all dirs debug prepare clean
	
all: $(TARGET).bin

-include $(DEPS)

dirs: dep obj

dep obj src:
	@echo "[MKDIR]   $@"
	mkdir -p $@

obj/%.o : %.c | dirs
	@echo "generating \"$@\" from \"$<\""
	$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF dep/$(*F).d

$(TARGET).elf: $(OBJS)
	@echo "[LD]      $(TARGET).elf"
	$(CC) $(CFLAGS) $(LDFLAGS) src/startup_$(MCU_LC).s $^ -l$(LIB) -o $@
	@echo "[OBJDUMP] $(TARGET).lst"
	$(OBJDUMP) -St $(TARGET).elf >$(TARGET).lst
	@echo "[SIZE]    $(TARGET).elf"
	$(SIZE) $(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	@echo "[OBJCOPY] $(TARGET).bin"
	$(OBJCOPY) -O binary $< $@

debug:
	@if ! nc -z localhost 3333; then \
		@echo "\n\t[Error] OpenOCD is not running!\n"; exit 1; \
	else \
	$(GDB)  -ex "target extended localhost:3333" \
			-ex "monitor arm semihosting enable" \
			-ex "monitor reset halt" \
			-ex "load" \
			-ex "monitor reset init" \
			$(GDBFLAGS) $(TARGET).elf; \
	fi

prepare: src
	cp $(SRCS) src/
	cp $(DEM_DIR)/dev/startup_$(MCU_LC).s src/
	cp $(LDFILE) src/linkerScript.ld

clean:
	@echo "[RM]      $(TARGET).bin"; rm -f $(TARGET).bin
	@echo "[RM]      $(TARGET).elf"; rm -f $(TARGET).elf
	@echo "[RM]      $(TARGET).map"; rm -f $(TARGET).map
	@echo "[RM]      $(TARGET).lst"; rm -f $(TARGET).lst
	@echo "[RM]      src files"; rm -f src/*
	@echo "[RM]      ld script"; rm -f src/linkerScript.ld
	@echo "[RMDIR]   dep"          ; rm -fr dep
	@echo "[RMDIR]   obj"          ; rm -fr obj
	@echo "[RMDIR]   obj"          ; rm -fr src
load:
	openocd -f "C:\Users\lucav\Documents\Uni\SistemiEmbedded\Strumenti\xpack-openocd-0.11.0-1\scripts\board\stm32f3discovery.cfg"
