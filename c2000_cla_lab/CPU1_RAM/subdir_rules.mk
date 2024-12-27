################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/device" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/device/include" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib/" --include_path="/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/include" --define=CPU1 --define=DEBUG --define=_LAUNCHXL_F28379D --define=_DUAL_CORE_ --define=F2837XD_DEVICE --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_background_task=off --cla_signed_compare_workaround=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-418108593: ../lab_f2837xd_launchpad.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/Applications/ti/ccs2000/ccs/utils/sysconfig_1.22.0/sysconfig_cli.sh" --script "/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/lab_f2837xd_launchpad.syscfg" -o "syscfg" -s "/Applications/ti/c2000/C2000Ware_5_04_00_00/.metadata/sdk.json" -b "/boards/LAUNCHXL_F28379D" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-418108593 ../lab_f2837xd_launchpad.syscfg
syscfg/board.h: build-418108593
syscfg/board.cmd.genlibs: build-418108593
syscfg/board.opt: build-418108593
syscfg/board.json: build-418108593
syscfg/pinmux.csv: build-418108593
syscfg/epwm.dot: build-418108593
syscfg/adc.dot: build-418108593
syscfg/c2000ware_libraries.cmd.genlibs: build-418108593
syscfg/c2000ware_libraries.opt: build-418108593
syscfg/c2000ware_libraries.c: build-418108593
syscfg/c2000ware_libraries.h: build-418108593
syscfg/clocktree.h: build-418108593
syscfg: build-418108593

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/device" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/device/include" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib/" --include_path="/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/include" --define=CPU1 --define=DEBUG --define=_LAUNCHXL_F28379D --define=_DUAL_CORE_ --define=F2837XD_DEVICE --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_background_task=off --cla_signed_compare_workaround=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -Ooff --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/device" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/device/include" --include_path="/Applications/ti/c2000/C2000Ware_5_04_00_00/driverlib/f2837xd/driverlib/" --include_path="/Applications/ti/ccs2000/ccs/tools/compiler/ti-cgt-c2000_22.6.1A23259/include" --define=CPU1 --define=DEBUG --define=_LAUNCHXL_F28379D --define=_DUAL_CORE_ --define=F2837XD_DEVICE --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --cla_background_task=off --cla_signed_compare_workaround=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/Users/lucasmatamoros/Desktop/Practica CTE/Workspace/c2000_cla_lab/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


