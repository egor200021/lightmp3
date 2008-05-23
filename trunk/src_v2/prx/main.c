//    LightMP3
//    Copyright (C) 2007 Sakya
//    sakya_tg@yahoo.it
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdisplay_kernel.h>
#include <pspimpose_driver.h>
#include <pspsysreg.h>
#include <pspctrl.h>
#include <pspsysmem_kernel.h>

PSP_MODULE_INFO("supportlib", 0x1006, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Prototypes
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sceDisplayEnable(void);
int sceDisplayDisable(void);
int sceDisplayEnable371(void);
int sceDisplayDisable371(void);
void sceDisplaySetBrightness371(int level,int unk1);
void sceDisplayGetBrightness371(int *level,int *unk1);
int sceCtrlSetSamplingCycle371(int cycle);
int sceCtrlSetSamplingMode371(int mode);
int sceCtrlReadBufferPositive371(SceCtrlData *pad_data, int count);
int sceSysregMeBusClockDisable371(void);
int sceSysregMeBusClockEnable371(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Globals
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
u32 k1;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//getBrightness
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getBrightness(){
    k1 = pspSdkSetK1(0);
    int currentBrightness = 0;
	if (sceKernelDevkitVersion() < 0x03070110)
        sceDisplayGetBrightness(&currentBrightness, 0);
    else
        sceDisplayGetBrightness371(&currentBrightness, 0);
    pspSdkSetK1(k1);
    return currentBrightness;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//setBrightness
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setBrightness(int brightness){
    k1 = pspSdkSetK1(0);
    if (sceKernelDevkitVersion() < 0x03070110)
        sceDisplaySetBrightness(brightness, 0);
    else
        sceDisplaySetBrightness371(brightness, 0);
    pspSdkSetK1(k1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeGetBrightness
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeGetBrightness(){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeGetParam(PSP_IMPOSE_BACKLIGHT_BRIGHTNESS);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeSetBrightness
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeSetBrightness(int value){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeSetParam(PSP_IMPOSE_BACKLIGHT_BRIGHTNESS, value);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeGetVolume
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeGetVolume(){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeGetParam(PSP_IMPOSE_MAIN_VOLUME);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeSetVolume
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeSetVolume(int value){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeSetParam(PSP_IMPOSE_MAIN_VOLUME, value);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeGetMute
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeGetMute(){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeGetParam(PSP_IMPOSE_MUTE);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeSetMute
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeSetMute(int value){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeSetParam(PSP_IMPOSE_MUTE, value);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeGetEqualizer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeGetEqualizer(){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeGetParam(PSP_IMPOSE_EQUALIZER_MODE);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeSetEqualizer
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeSetEqualizer(int value){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeSetParam(PSP_IMPOSE_EQUALIZER_MODE, value);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//displayEnable
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int displayEnable(void){
    k1 = pspSdkSetK1(0);
    int ret;
    if (sceKernelDevkitVersion() < 0x03070110)
        ret = sceDisplayEnable();
    else
        ret = sceDisplayEnable371();
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//displayDisable
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int displayDisable(void){
    k1 = pspSdkSetK1(0);
	int ret;
    if (sceKernelDevkitVersion() < 0x03070110)
        ret = sceDisplayDisable();
    else
        ret = sceDisplayDisable371();
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MEEnable
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MEEnable(void){
    k1 = pspSdkSetK1(0);
    if (sceKernelDevkitVersion() < 0x03070110)
        sceSysregMeBusClockEnable();
    else
        sceSysregMeBusClockEnable371();
    pspSdkSetK1(k1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MEDisable
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MEDisable(void){
    k1 = pspSdkSetK1(0);
    if (sceKernelDevkitVersion() < 0x03070110)
        sceSysregMeBusClockDisable();
    else
        sceSysregMeBusClockDisable371();
    pspSdkSetK1(k1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Read PSP Buttons
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initController(){
    k1 = pspSdkSetK1(0);
    if (sceKernelDevkitVersion() < 0x03070110){
	    sceCtrlSetSamplingCycle(0);
        sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    }else{
       sceCtrlSetSamplingCycle371(0);
       sceCtrlSetSamplingMode371(PSP_CTRL_MODE_ANALOG);
    }
    pspSdkSetK1(k1);
}

int readButtons(SceCtrlData *pad_data, int count){
    k1 = pspSdkSetK1(0);
	int ret;
    if (sceKernelDevkitVersion() < 0x03070110)
       ret = sceCtrlReadBufferPositive(pad_data, count);
    else
       ret = sceCtrlReadBufferPositive371(pad_data, count);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//imposeSetHomePopup
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int imposeSetHomePopup(int value){
    k1 = pspSdkSetK1(0);
    int ret = sceImposeSetHomePopup(value);
    pspSdkSetK1(k1);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get loaded modules IDs:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getModuleListID(SceUID modid[100], int *modcount){
    k1 = pspSdkSetK1(0);
    sceKernelGetModuleIdList(modid, 100, modcount);
    pspSdkSetK1(k1);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Stop and unload a running module:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int stopUnloadModule(SceUID modID){
    k1 = pspSdkSetK1(0);
    int status;
    sceKernelStopModule(modID, 0, NULL, &status, NULL);
    sceKernelUnloadModule(modID);
    pspSdkSetK1(k1);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get psp model with sceKernelGetModel:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getModelKernel(){
    k1 = pspSdkSetK1(0);
    int retVal = sceKernelGetModel();
    pspSdkSetK1(k1);
    return retVal;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//module_start
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int module_start(SceSize args, void *argp){
    initController();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//module_stop
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int module_stop(){
	return 0;
}
