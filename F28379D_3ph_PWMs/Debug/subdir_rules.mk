################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O1 --opt_for_speed=4 --fp_mode=relaxed --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/F28379D_3ph_PWMs" --include_path="/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/ti/c2000/C2000Ware_4_01_00_00/device_support/f2837xd/headers/include" --include_path="D:/ti/c2000/C2000Ware_4_01_00_00/device_support/f2837xd/common/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -O1 --opt_for_speed=4 --fp_mode=relaxed --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/F28379D_3ph_PWMs" --include_path="/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/ti/c2000/C2000Ware_4_01_00_00/device_support/f2837xd/headers/include" --include_path="D:/ti/c2000/C2000Ware_4_01_00_00/device_support/f2837xd/common/include" --define=CPU1 --define=_LAUNCHXL_F28379D -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


