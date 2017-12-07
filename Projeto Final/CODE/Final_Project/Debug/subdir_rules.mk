################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DHT11_LIB.obj: ../DHT11_LIB.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs720/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccs720/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/ArturArthur/workspace_v7/Final_Project" --include_path="C:/ti/ccs720/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="DHT11_LIB.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs720/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccs720/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/ArturArthur/workspace_v7/Final_Project" --include_path="C:/ti/ccs720/ccsv7/tools/compiler/ti-cgt-msp430_17.9.0.STS/include" --advice:power=all --define=__MSP430G2553__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


