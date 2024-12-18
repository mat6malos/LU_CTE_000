################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
device/%.obj: ../device/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/driverlib_lp_f2837xd" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/driverlib_lp_f2837xd/device" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib" --include_path="/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/include" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/device_support/f2837xd/common/include" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/device_support/f2837xd/headers/include" --define=DEBUG --define=CPU1 --define=_LAUNCHXL_F28379D --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/driverlib_lp_f2837xd/CPU1_RAM/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

device/%.obj: ../device/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/driverlib_lp_f2837xd" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/driverlib_lp_f2837xd/device" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib" --include_path="/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/include" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/device_support/f2837xd/common/include" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/device_support/f2837xd/headers/include" --define=DEBUG --define=CPU1 --define=_LAUNCHXL_F28379D --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="device/$(basename $(<F)).d_raw" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/driverlib_lp_f2837xd/CPU1_RAM/syscfg" --obj_directory="device" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


