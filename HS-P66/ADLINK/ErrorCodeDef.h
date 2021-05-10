#ifndef _ADLINK_ERROR_CODE_DEF_H
#define _ADLINK_ERROR_CODE_DEF_H

#define ERR_NoError						(0)		//No Error	

// System Error ( -1 ~ -1000 )
#define ERR_OSVersion					(-1)	// Operation System type mismatched
#define ERR_OpenDriverFailed			(-2)	// Open device driver failed - Create driver interface failed
#define ERR_InsufficientMemory			(-3)	// System memory insufficiently
#define ERR_DeviceNotInitial			(-4)	// Cards not be initialized
#define ERR_NoDeviceFound				(-5)	// Cards not found(No card in your system)
#define ERR_CardIdDuplicate				(-6)	// Cards' ID is duplicated. 
#define ERR_DeviceAlreadyInitialed		(-7)	// Cards have been initialed 
#define ERR_InterruptNotEnable			(-8)	// Cards' interrupt events not enable or not be initialized
#define ERR_TimeOut						(-9)	// Function time out
#define ERR_ParametersInvalid			(-10)	// Function input parameters are invalid
#define ERR_SetEEPROM					(-11)	// Set data to EEPROM (or nonvolatile memory) failed
#define ERR_GetEEPROM					(-12)	// Get data from EEPROM (or nonvolatile memory) failed
#define ERR_FunctionNotAvailable		(-13)	// Function is not available in this step, The device is not support this function or Internal process failed
#define ERR_FirmwareError				(-14)   // Firmware error, please reboot the system
#define ERR_CommandInProcess			(-15)	// Previous command is in process
#define ERR_AxisIdDuplicate				(-16)	// Axes' ID is duplicated.
#define ERR_ModuleNotFound				(-17)   // Slave module not found.
#define ERR_InsufficientModuleNo		(-18)	// System ModuleNo insufficiently
#define ERR_HandShakeFailed				(-19)   // HandSake with the DSP out of time.
#define ERR_FILE_FORMAT					(-20)	// Config file format error.(cannot be parsed)
#define ERR_ParametersReadOnly			(-21)	// Function parameters read only.
#define ERR_DistantNotEnough			(-22)	// Distant is not enough for motion.
#define ERR_FunctionNotEnable			(-23)	// Function is not enabled.
#define ERR_ServerAlreadyClose		    (-24)	// Server already closed.
#define ERR_DllNotFound					(-25)	// Related dll is not found, not in correct path.
//Following are added for AI16AO2 calibration
#define ERR_TrimDAC_Channel				(-26)
#define ERR_Satellite_Type				(-27)
#define	ERR_Over_Voltage_Spec			(-28)
#define ERR_Over_Current_Spec			(-29)
#define ERR_SlaveIsNotAI				(-30)
#define ERR_Over_AO_Channel_Scope		(-31)
#define ERR_DllFuncFailed				(-32)	// Failed to invoke dll function. Extension Dll version is wrong.
#define ERR_FeederAbnormalStop		    (-33)	//Feeder abnormal stop, External stop or feeding stop
#define ERR_AlreadyClose				(-34)	// Already closed by others
#define ERR_NullObject					(-35)	// Null object is detected
#define ERR_PreMoveErr					(-36)	// last move is on error stop
#define ERR_PreMoveNotDone			    (-37)	// last move not be done
#define ERR_MismatchState				(-38)	// there is a mismatch state
#define ERR_Read_ModuleType_Dismatch	(-39)
#define ERR_DoubleOverflow			    (-40)	// Double format parameter is overflow
#define ERR_SlaveNumberErr			    (-41)
#define ERR_SlaveStatusErr			    (-42)
#define ERR_MapPDOOffset_TimeOut        (-43)
#define ERR_Fifo_Access_Fail            (-44)
#define ERR_KernelVerifyError			(-45)   // Kernel verify error, please download kernel again
#define ERR_LatchFlowErr				(-46)	
#define ERR_NoSystemAuthority			(-47)
#define ERR_InServoOnState				(-48)	// Now only use it in 8154/58 APS_spiral_ce_xxx this API, to judge 4th axis is servo on
#define ERR_InterpolationParameterInvalid (-49) // For 8144C, some interpolation  axis Vmax out of range.
#define ERR_KernelUpdateError	        (-50)   // For Kernel update
#define ERR_KernelGeneralFunc	        (-51)   // For general functions
#define ERR_NO_POINT_EXIST              (-52)   // There is no point exist in point table when point table move start.

//for EMX-100
#define ERR_Emx_Offset					(-899)
#define ERR_Smp_App_Existed				(-900)
#define ERR_Init_Error					(-901)
#define ERR_No_Init						(-902)
#define ERR_No_Setup					(-903)
#define ERR_Input_Error					(-904)
#define ERR_Status_Not_Ready			(-905)
#define ERR_Axis_Busy					(-906)
#define ERR_Network_Error				(-907)
#define ERR_Network_Time_Out			(-908)
#define ERR_Crc_Fail					(-909)
#define ERR_Param_Invalid 				(-910)
#define ERR_No_Servo_On					(-911)
#define ERR_Api_Timeout					(-912)
#define ERR_Load_Xml_Mismatch 			(-915)




#define ERR_Fifo_Access_Success         (1)

//For EtherCAT, PCIe-833x ( -1001 ~ -1999 )
#define ERR_NoENIFile						(-1001)
#define ERR_TimeOut_SetVoltageEnable		(-1002)
#define ERR_TimeOut_SetReadyToSwitch		(-1003)
#define ERR_TimeOut_SetShutdown				(-1004)
#define ERR_TimeOut_SetSwitchOn				(-1005)
#define ERR_TimeOut_SetOperationEnable		(-1006)
#define ERR_RegistryPath					(-1007)
#define ERR_MasterNotOPState				(-1008)
#define ERR_SlaveNotOPState					(-1009)
#define ERR_SlaveTotalAxisNumber			(-1010) // The scanned number of EtherCAT slaves' axes exceeds the number of max.
#define ERR_MissESIFileOrMissENIPath		(-1011) // No ESI file or ESI file path miss result .
#define ERR_MissConfig_1_Xml				(-1012) // No config_1 xml.
#define ERR_CopyConfig_1_Xml_fail			(-1013) // No config_1 xml.
#define ERR_MissConfig_2_Xml				(-1014) // No config_2 xml.
#define ERR_CopyConfig_2_Xml_fail			(-1015) // No config_2 xml.
#define ERR_InvalidSlaveLocalAxis           (-1016) // 20190813; Invalid slave local axis (for GPM4XMO, local axis should be 0~3)
#define ERR_InvalidECATHomeMode				(-1017) // 20200309; Invalid home mode
#define ERR_FoEFileNameOverLimit			(-1018)	// 20200520
#define ERR_FoEFileVerifyError				(-1019)	// 20200520
#define ERR_FoEConflictAutoRecovery			(-1020) // 20200520
#define ERR_FoEFileSizeOverLimit			(-1021)	// 20200603

#define	EC_NO_ERROR                         (0)
#define	EC_INIT_MASTER_ERR                  (-4001)
#define	EC_GET_SLV_NUM_ERR                  (-4011)
#define EC_CONFIG_MASTER_ERR                (-4012)
#define	EC_BUSCONFIG_MISMATCH               (-4013)
#define EC_CONFIGDATA_READ_ERR              (-4014)
#define	EC_ENI_NO_SAFEOP_OP_SUPPORT         (-4015)
#define	EC_CONFIG_DC_ERR                    (-4021)
#define	EC_DCM_MODE_NO_SUPPORT              (-4022)
#define	EC_CONFIG_DCM_FEATURE_DISABLED      (-4023)            
#define	EC_CONFIG_DCM_ERR                   (-4024)
#define	EC_REG_CLIENT_ERR                   (-4031)
#define	EC_SET_INIT_STATE_ERR               (-4041)        
#define	EC_SET_PREOP_STATE_ERR              (-4042)
#define	EC_SET_SAFEOP_STATE_ERR             (-4043)
#define	EC_SET_OP_STATE_ERR                 (-4044)
#define	EC_DE_INIT_MASTER_ERR               (-4051)
#define	EC_ENI_FOPEN_ERR                    (-4061)
#define	EC_ENI_FREAD_ERR                    (-4062)
#define	EC_GEN_EBI_BUSSCAN_ERR              (-4063)
#define	EC_GEN_EBI_FOPEN_ERR                (-4064)     
#define	EC_GET_EBI_FOPEN_ERR                (-4065)
#define	EC_GET_EBI_FREAD_ERR                (-4066)
#define	EC_WRITE_DO_OUT_ERR                 (-4071)
#define	EC_READ_DI_INP_ERR                  (-4072)
#define	EC_CONNECT_SLAVES_ERR               (-4073)
#define	EC_WRONG_PORT_NO                    (-4081)
#define	EC_GET_SLAVE_INFO_ERR               (-4091)
#define	EC_COE_SDO_UPLOAD_ERR               (-4101)

#define	EC_COE_SDO_HOME_MODE_ERR            (-4102)
#define	EC_COE_SDO_HOME_ACCDEC_ERR          (-4103)
#define	EC_COE_SDO_HOME_VM_SWITCH_ERR       (-4104)
#define	EC_COE_SDO_HOME_VM_ZERO_ERR         (-4105)
#define	EC_COE_SDO_HOME_OFFSET_ERR          (-4106)
#define EC_CONTROL_WORD_HOME_ERR			(-4107)
#define EC_COE_SDO_STOP_ERR					(-4108)
#define EC_CONTROL_WORD_STOP_ERR			(-4109)
#define EC_SET_OP_MODE_HOME_ERR				(-4110)
//#define EC_SET_OP_MODE_STOP_ERR				(-4111)
//#define EC_SET_OP_MODE_EMG_STOP_ERR			(-4112)

#define	EC_WRONG_SLAVE_NO                   (-4201)
#define	EC_WRONG_MODULE_NO                  (-4202)
#define	EC_WRONG_AI_CHANNEL_NO              (-4203)
#define	EC_WRONG_AO_CHANNEL_NO              (-4204)
#define	EC_COE_SDO_DOWNLOAD_ERR             (-4205)
#define	EC_COE_OD_INIT_ERR                  (-4301)
#define	EC_COE_GET_OD_NUM_ERR               (-4302)
#define	EC_COE_GET_OD_NUM_LAST              (-4303)
#define	EC_COE_GET_OD_DESC_ERR              (-4304)
#define	EC_COE_GET_OD_DESC_ENTRY_ERR        (-4305)
#define	EC_COE_GET_OD_STATUS_PEND           (-4306)
#define EC_GET_SLAVE_PRESENT_ERR			(-4401)
#define EC_GET_SLAVE_STATE_ERR		 		(-4402)
#define EC_SET_SLAVE_STATE_ERR		 		(-4403)
#define EC_Get_CONNETED_SLAVE_NUM_ERR		(-4404)
#define EC_PDO_ACCESS_OFFSET_ERR			(-4405)
#define EC_GET_SLAVE_ID_ERR		 	        (-4501)
#define EC_SET_SLAVE_ID_ERR		 		    (-4502)
#define	EC_DUPLICATE_SLAVE_ID_ERR           (-4503)
#define	EC_GET_SLAVE_REGISTER_ERR		    (-4504)
#define	EC_SET_SLAVE_REGISTER_ERR		    (-4505)

#define EC_FOE_FILE_NAME_NULL				(-4600)
#define EC_FOE_FILE_OPEN_FAIL				(-4601)
#define EC_FOE_FILE_MEMORY_ALLOCATE_FAIL	(-4602)
#define EC_FOE_FILE_COPY_DATA_FAIL			(-4603)
#define EC_FOE_NO_MBX_SUPPORT				(-4604)
#define EC_FOE_FILE_DELETE_FAIL				(-4605)
#define EC_FOE_DOWNLOAD_TIME_OUT			(-4606)
#define EC_FOE_DOWNLOAD_FILE_NOT_VALID		(-4607)
#define EC_FOE_DOWNLOAD_PWD_NOT_VALID		(-4608)

#define ERR_Win32Error					(-1000) // No such INT number, or WIN32_API error, contact with ADLINK's FAE staff.

// DSP Error ( -2001 ~ -3000 ) //Defined in manual
#define ERR_DspStart					(-2000) // The base for DSP error

#endif  //_ADLINK_ERROR_CODE_DEF_H
