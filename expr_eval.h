//#define RIDE_C

#ifdef RIDE_C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef unsigned char	Xuint8;		/**< unsigned 8-bit */
typedef unsigned short	Xuint16;	/**< unsigned 16-bit */
typedef unsigned long	Xuint32;	/**< unsigned 32-bit */
typedef Xuint32         u32;
typedef Xuint16         u16;
typedef Xuint8          u8;

unsigned char EXPRESSION_LIST_LENGTH=0;
char EXPRESSION_TEMP1[25][15];
char EXPRESSION_TEMP2[25];
char EXPRESSION_STRING[255];

void MOVE_STRING(char *DEST, char *SOURCE){
	u16 INDEX=0;
    while ((SOURCE[INDEX]!='\n')&&(SOURCE[INDEX] != '\0'))
    {
    	DEST[INDEX]=SOURCE[INDEX];
    	INDEX++;
    }
    DEST[INDEX]='\0';
}

// Function to remove all spaces from a given string
void removeSpaces(char *str)
{
    // To keep track of non-space character count
    int count = 0;

    // Traverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; // here count is
                                   // incremented
    str[count] = '\0';
}

#define CONFIG_VALUE_CHAR_COUNT 	14
#define VALUE_STRING_START          71
#define VALUE_STRING_END            VALUE_STRING_START + CONFIG_VALUE_CHAR_COUNT - 1

char UPB_PART_INS[10];
char UPB_FULL_INS[62];
char USER_FULL_INS[60];
u8 UPB_INS_CHANGE=0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
u8 atoh(char *src, u32 *dst){
	u32 temp=0; u8 i=0; u8 val=0;

	while(src[i]){
		val = src[i];
		if((val == ' ')||(val=='0')||(val=='x')||(val=='X'))
			i++;
		else
			break;
	}

	while(src[i]){
		val = tolower(src[i]);
		if( ((val>='0')&&(val<='9')) || ((val>='a')&&(val<='f')) ){
			val -= isdigit(val) ? 0x30 : 0x57;
			temp = (u32)val | (temp << 4);
			i++;
		}
		else{
			return(0);
		}
	}
	*dst = temp;
	return(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CONCATENATE_STRING(char *SRC1_STRING, char *SRC2_STRING, char *DEST_STRING){
	u16 i=0;
	u16 j=0;
    while (SRC1_STRING[i] != '\0') {
    	DEST_STRING[i] = SRC1_STRING[i];
    	++i;
    }
    for(j=0; SRC2_STRING[j]!='\0'; ++j, ++i) {
    	DEST_STRING[i] = SRC2_STRING[j];
    }
    DEST_STRING[i] = '\0';
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
#define INS_HALT       0x00000000
#define INS_FREG       0x00010000
#define INS_JUMP       0x00020000
#define INS_CALL       0x00030000
#define INS_RET        0x00040000
#define INS_REPEAT     0x00050000
#define INS_FADD       0x00060000
#define INS_FSUB       0x00070000
#define INS_FMUL       0x00080000
#define INS_FDIV       0x00090000
#define INS_FDIFF      0x000A0000
#define INS_FABS       0x000B0000
#define INS_FNEG       0x000C0000
#define INS_FMIN       0x000D0000
#define INS_FMAX       0x000E0000
#define INS_FINV       0x000F0000
#define INS_FMOD       0x00100000
#define INS_FDEG       0x00110000
#define INS_FRAD       0x00120000
#define INS_FPW2       0x00130000
#define INS_FPW3       0x00140000
#define INS_FSINCOS    0x00150000
#define INS_FTAN       0x00160000
#define INS_FMAGANG    0x00170000
#define INS_FJL        0x00180000
#define INS_FJLE       0x00190000
#define INS_FJG        0x001A0000
#define INS_FJGE       0x001B0000
#define INS_FJE        0x001C0000
#define INS_FJNE       0x001D0000
#define INS_FJZ        0x001E0000
#define INS_FJNZ       0x001F0000
#define INS_FJLZ       0x00200000
#define INS_FJGZ       0x00210000
#define INS_SELDT      0x00220000
#define INS_WAITSAMPLE 0x00230000
#define INS_WAITST     0x00240000
#define INS_FSQRT      0x00250000
#define INS_FEXP       0x00260000
#define INS_FLN        0x00270000
#define INS_FLOG       0x00280000
#define INS_NOP        0x00290000
#define INS_FSELDT     0x002A0000
#define INS_FSIN       0x002B0000
#define INS_FCOS       0x002C0000
#define INS_RSTMSR     0x002D0000
#define INS_MSR        0x002E0000

#define INS_DIRECT     0x00300000
#define INS_REG        0x00310000
#define INS_UINT8      0x00320000
#define INS_FLOAT      0x00330000
#define INS_INC        0x00340000
#define INS_DEC        0x00350000
#define INS_ADD        0x00360000
#define INS_SUB        0x00370000
#define INS_MUL        0x00380000
#define INS_JL         0x00390000
#define INS_JLE        0x003A0000
#define INS_JG         0x003B0000
#define INS_JGE        0x003C0000
#define INS_JE         0x003D0000
#define INS_JNE        0x003E0000
#define INS_JZ         0x003F0000
#define INS_JNZ        0x00400000
#define INS_PTRRD      0x00410000
#define INS_PTRWR      0x00420000

#define INS_CMPRFL     0x00500000
#define INS_CMPRFLE    0x00510000
#define INS_CMPRFG     0x00520000
#define INS_CMPRFGE    0x00530000
#define INS_CMPRFE     0x00540000
#define INS_CMPRFNE    0x00550000
#define INS_CMPRFZ     0x00560000
#define INS_CMPRFNZ    0x00570000
#define INS_CMPRFLZ    0x00580000
#define INS_CMPRFGZ    0x00590000
#define INS_CMPRFAA    0x005A0000
#define INS_CMPRFRR    0x005B0000
#define INS_FNOT       0x005C0000
#define INS_FXOR       0x005D0000

#define INS_CNT1RESET     0x00600000
#define INS_CNT1POS       0x00610000
#define INS_CNT1NEG       0x00620000
#define INS_CNT1WAIT1     0x00630000
#define INS_CNT1WAIT0     0x00640000
#define INS_CNT1CNFGQ0    0x00650000
#define INS_CNT1CNFGQ1    0x00660000
#define INS_CNT1MODE      0x00670000
#define INS_CNT1GET       0x00680000
#define INS_CNT1GETON     0x00690000
#define INS_CNT1GETONF    0x006A0000
#define INS_CNT1GETDIR    0x006B0000
#define INS_CNT1STRBW     0x006C0000
#define INS_CNT1CLRP      0x006D0000
#define INS_CNT1GETQ0     0x006E0000
#define INS_CNT1GETQ1     0x006F0000

const u8 COUNT_MAX = 10;
const u8 INSTRUCTON_INDEX_MAX = 25;
char INSTRUCTION_STRING_PART1[10];
char INSTRUCTION_STRING_PART2[10];
char INSTRUCTION_STRING_PART3[10];
char INSTRUCTION_STRING_PART4[10];
u8 PART_COUNT=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////

u8 FIND_INSTRUCTION_STRING_PART(char *INSTRUCTION_STRING, char *INSTRUCTION_STRING_PART, u8 INDEX){
	u8 STATE_A=0;
	u8 COUNT=0;
	//xil_printf("\r\n FIND_INSTRUCTION_STRING_PART(");xil_printf(INSTRUCTION_STRING);xil_printf(", INDEX=%d)", INDEX);
	while(1){
		switch(STATE_A){
			case 0:
					if(INDEX==INSTRUCTON_INDEX_MAX){
						STATE_A=2;
					}
					else if( (INSTRUCTION_STRING[INDEX] == ' ') || 
						(INSTRUCTION_STRING[INDEX] == '=') || 
						(INSTRUCTION_STRING[INDEX] == ',') ) {
						INDEX++;
					}
					else if((INSTRUCTION_STRING[INDEX] == '/') ||
							(INSTRUCTION_STRING[INDEX] == '\0') ||
							(INSTRUCTION_STRING[INDEX] == 0) ) {
						//INDEX++;
						STATE_A=2;
					}
					else{
						PART_COUNT++;
						INSTRUCTION_STRING_PART[COUNT++] = INSTRUCTION_STRING[INDEX++];
						STATE_A++;
					}
					break;
			
			case 1: if(INDEX==INSTRUCTON_INDEX_MAX) STATE_A++;
					else if( (INSTRUCTION_STRING[INDEX] == ' ') || 
						(INSTRUCTION_STRING[INDEX] == '=') || 
						(INSTRUCTION_STRING[INDEX] == ',') ) {
						INDEX++;
						STATE_A++;
					}
					else if((INSTRUCTION_STRING[INDEX] == '/') ||
							(INSTRUCTION_STRING[INDEX] == '\0') ||
							(INSTRUCTION_STRING[INDEX] == 0) ){
						//INDEX++;
						STATE_A=2;
					}
					else{
						if(COUNT<COUNT_MAX){
							INSTRUCTION_STRING_PART[COUNT++] = INSTRUCTION_STRING[INDEX++]; 
						}
						else{
							return(INDEX);
						}
					}
					break;
					
			case 2: INSTRUCTION_STRING_PART[COUNT]=0;
			        return(INDEX);
			
			default: break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
#define TYPE_AA 0
#define TYPE_RD_RA_RB 1
#define TYPE_FA_FB 2
#define TYPE_FD 3
#define TYPE_DD 4
#define TYPE_SL 5

u8 CHECK_INS_PART_TYPE(char *INSTRUCTION_STRING_PART, u8 INS_PART_TYPE, u32 *OP32, u8 PLACE){
	u32 OP32_TEMP;

	//xil_printf("\r\n CHECK_INS_PART_TYPE(");xil_printf(INSTRUCTION_STRING_PART);xil_printf(", %d , %08X , %d)", INS_PART_TYPE, *OP32, PLACE);PRINT_EOL();

	switch(INS_PART_TYPE){
		case TYPE_AA: // AA should be within 00 to FE
			if (INSTRUCTION_STRING_PART[0]=='R'){
				//xil_printf("TYPE_RAA \n\r");
				if (!atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)) return(0);
				if(OP32_TEMP>0xCF) return(0);
			}
			else{
				//xil_printf("TYPE_AA \n\r");
				//xil_printf("\r\n else{");
				if (!atoh(INSTRUCTION_STRING_PART, &OP32_TEMP)) return(0);
				if(OP32_TEMP>0xCF) return(0);
			}
			break;

		case TYPE_RD_RA_RB:
			//xil_printf("TYPE_RD_RA_RB \n\r");
			if (INSTRUCTION_STRING_PART[0]!='R') return(0);
			if (!atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)) return(0);
			if(OP32_TEMP>0x7) return(0);
			OP32_TEMP = 0xF8 + OP32_TEMP; // R0 to R7
			break;

		case TYPE_FA_FB:
			//xil_printf("TYPE_FA_FB \n\r");
			if (INSTRUCTION_STRING_PART[0]=='Q') {
				if (!atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)) return(0);
				if (OP32_TEMP>0x7) return(0);
				OP32_TEMP = 0xE8 + OP32_TEMP; // Q0 to Q7
				sprintf(UPB_PART_INS,"Q%01X ",(unsigned int)(OP32_TEMP-0xE8));
			}else if (!strcmp("MM", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF0;
			}else if (!strcmp("NN", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF1;
			}else if (!strcmp("PI", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF2;
			}else if (!strcmp("DT", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF3;
			}else if (!strcmp("FR", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF4;
			}else if (!strcmp("ST", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF5;
			}else if (!strcmp("UN", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF6;
			}else if (!strcmp("ZR", INSTRUCTION_STRING_PART)){
				OP32_TEMP = 0xF7;
			}else if(INSTRUCTION_STRING_PART[0]=='D'){
				if (!atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)) return(0);
				if(OP32_TEMP>0x7) return(0);
				OP32_TEMP = 0xE0 + OP32_TEMP; // D0 to D7
				sprintf(UPB_PART_INS,"D%01X ",(unsigned int)(OP32_TEMP-0xE0));
			}else if(INSTRUCTION_STRING_PART[0]=='X'){
				if (!atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)) return(0);
				if(OP32_TEMP>0x7) return(0);
				OP32_TEMP = 0xE0 + OP32_TEMP; // D0 to D7
				sprintf(UPB_PART_INS,"X%02X ",(unsigned int)(OP32_TEMP-0xE0));
			}else if (INSTRUCTION_STRING_PART[0]=='R'){
				if (atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)){
					if(OP32_TEMP>0xF8) return(0);
					UPB_PART_INS[0]=INSTRUCTION_STRING_PART[0];
					UPB_PART_INS[1]=INSTRUCTION_STRING_PART[1];
					UPB_PART_INS[2]=INSTRUCTION_STRING_PART[2];
					UPB_PART_INS[3]=' ';
					UPB_PART_INS[4]=0;
				}else return(0);
			}else if (atoh(INSTRUCTION_STRING_PART, &OP32_TEMP)){
			    if(OP32_TEMP<=0xF8){
    				UPB_PART_INS[0]='R';
	    			UPB_PART_INS[1]=INSTRUCTION_STRING_PART[0];
		    		UPB_PART_INS[2]=INSTRUCTION_STRING_PART[1];
			    	UPB_PART_INS[3]=' ';
				    UPB_PART_INS[4]=0;
			    }
				if(OP32_TEMP>0xF8) return(0);
			}else return(0);
			break;

		case TYPE_FD:
			//xil_printf("TYPE_FD \n\r");
			if (INSTRUCTION_STRING_PART[0]=='Q'){
				if (!atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)) return(0);
				if (OP32_TEMP>0x7) return(0);
				OP32_TEMP = 0xE8 + OP32_TEMP; // Q0 to Q7
				sprintf(UPB_PART_INS,"Q%01X ",(unsigned int)(OP32_TEMP-0xE8));
			}
			else if (INSTRUCTION_STRING_PART[0]=='Y'){
				if (!atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)) return(0);
				if (OP32_TEMP>0x7) return(0);
				OP32_TEMP = 0xE8 + OP32_TEMP; // Q0 to Q7
				sprintf(UPB_PART_INS,"Y%02X ",(unsigned int)(OP32_TEMP-0xE8));
			}else if (INSTRUCTION_STRING_PART[0]=='R'){
				if (atoh(&INSTRUCTION_STRING_PART[1], &OP32_TEMP)){
					if(OP32_TEMP>0xF8) return(0);
					UPB_PART_INS[0]=INSTRUCTION_STRING_PART[0];
					UPB_PART_INS[1]=INSTRUCTION_STRING_PART[1];
					UPB_PART_INS[2]=INSTRUCTION_STRING_PART[2];
					UPB_PART_INS[3]=' ';
					UPB_PART_INS[4]=0;
				}else return(0);
			}else if (atoh(INSTRUCTION_STRING_PART, &OP32_TEMP)){
			    if(OP32_TEMP<=0xF8){
    				UPB_PART_INS[0]='R';
	    			UPB_PART_INS[1]=INSTRUCTION_STRING_PART[0];
		    		UPB_PART_INS[2]=INSTRUCTION_STRING_PART[1];
			    	UPB_PART_INS[3]=' ';
				    UPB_PART_INS[4]=0;
			    }
				if(OP32_TEMP>0xF8) return(0);
			}else return(0);
			break;

		case TYPE_DD:
			//xil_printf("\r\n TYPE_DD \n\r");
			if (!atoh(INSTRUCTION_STRING_PART, &OP32_TEMP)) return(0);
			break;

		case TYPE_SL:
			//xil_printf("\r\n TYPE_SL \n\r");
			if (!atoh(INSTRUCTION_STRING_PART, &OP32_TEMP)) return(0);
			if (OP32_TEMP>0x7) return(0);
			break;

		default:  return(0);
			break;
	}

	switch(PLACE){
		case 1: OP32_TEMP <<= 24; break;
		case 3: OP32_TEMP <<= 8;  break;
		default : break;
	}

	*OP32 = *OP32 | OP32_TEMP;
	return(1);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void SPACE_UPB_INS(void){
	CONCATENATE_STRING(UPB_FULL_INS," ",UPB_FULL_INS);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void JOIN_UPB_INS(void){
	CONCATENATE_STRING(UPB_FULL_INS,UPB_PART_INS,UPB_FULL_INS);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void SKIP_UPB_INS_1(void){
	CONCATENATE_STRING(UPB_FULL_INS,INSTRUCTION_STRING_PART1,UPB_FULL_INS);SPACE_UPB_INS();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void SKIP_UPB_INS_2(void){
	CONCATENATE_STRING(UPB_FULL_INS,INSTRUCTION_STRING_PART2,UPB_FULL_INS);SPACE_UPB_INS();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void SKIP_UPB_INS_3(void){
	CONCATENATE_STRING(UPB_FULL_INS,INSTRUCTION_STRING_PART2,UPB_FULL_INS);SPACE_UPB_INS();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void SKIP_UPB_INS_4(void){
	CONCATENATE_STRING(UPB_FULL_INS,INSTRUCTION_STRING_PART2,UPB_FULL_INS);SPACE_UPB_INS();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
u8 DECODE_INSTRUCTION_AUX(char *INSTRUCTION_STRING, u32 *OP32){
	u8 INDEX=0;
	PART_COUNT = 0;
	u8 MODEL = 0;
	//if(!STOP_PRINT) { xil_printf("\r\n DECODE_INSTRUCTION(");xil_printf(INSTRUCTION_STRING);xil_printf(")"); }

	INDEX = FIND_INSTRUCTION_STRING_PART(INSTRUCTION_STRING, INSTRUCTION_STRING_PART1, INDEX);
	INDEX = FIND_INSTRUCTION_STRING_PART(INSTRUCTION_STRING, INSTRUCTION_STRING_PART2, INDEX);
	INDEX = FIND_INSTRUCTION_STRING_PART(INSTRUCTION_STRING, INSTRUCTION_STRING_PART3, INDEX);
	INDEX = FIND_INSTRUCTION_STRING_PART(INSTRUCTION_STRING, INSTRUCTION_STRING_PART4, INDEX);
	
	//if(!STOP_PRINT) xil_printf("\r\n PART_COUNT = %d \n\r",PART_COUNT);

	switch(PART_COUNT) {
		case 0: *OP32 = INS_HALT;
				return(0);
				break;
		
		case 1: if (!strcmp("HALT", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_HALT;
				} else if (!strcmp("RSTMSR", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_RSTMSR;
				} else if (!strcmp("MSR", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_MSR;
				} else if (!strcmp("RET", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_RET;
				} else if (!strcmp("REPEAT", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_REPEAT;
				} else if (!strcmp("WAITSAMPLE", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_WAITSAMPLE;
				} else if (!strcmp("NOP", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_NOP;
				} else if (!strcmp("CNT1RESET", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1RESET;
				} else if (!strcmp("CNT1WAIT1", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1WAIT1;
				} else if (!strcmp("CNT1WAIT0", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1WAIT0;
				} else if (!strcmp("CNT1CLRP", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1CLRP;
				} else {
					*OP32 = INS_HALT;
					return(0);
				}
				UPB_INS_CHANGE=0;
				return(1);
				break;
		
		case 2: if (!strcmp("WAITST", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_WAITST;
					MODEL = 0;
				} else if (!strcmp("FSELDT", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_FSELDT;
					MODEL = 0;
				} else if (!strcmp("CNT1POS", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1POS;
					MODEL = 16;
				} else if (!strcmp("CNT1NEG", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1NEG;
					MODEL = 16;
				} else if (!strcmp("CNT1STRBW", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1STRBW;
					MODEL = 16;
				} else if (!strcmp("CNT1CNFGQ0", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1CNFGQ0;
					MODEL = 16;
				} else if (!strcmp("CNT1CNFGQ1", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1CNFGQ1;
					MODEL = 16;
				} else if (!strcmp("CNT1MODE", INSTRUCTION_STRING_PART1)) {
					*OP32 = INS_CNT1MODE;
					MODEL = 16;
				} else if (!strcmp("JUMP", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JUMP;
					MODEL = 1;
				} else if (!strcmp("JMP", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JUMP;
					MODEL = 1;
				} else if (!strcmp("CALL", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CALL;
					MODEL = 1;
				} else if (!strcmp("SELDT", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_SELDT;
					MODEL = 2;
				} else if (!strcmp("CNT1GET", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CNT1GET;
					MODEL = 15;
				} else if (!strcmp("CNT1GETON", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CNT1GETON;
					MODEL = 15;
				} else if (!strcmp("CNT1GETONF", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CNT1GETONF;
					MODEL = 15;
				} else if (!strcmp("CNT1GETDIR", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CNT1GETDIR;
					MODEL = 15;
				} else if (!strcmp("CNT1GETQ0", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CNT1GETQ0;
					MODEL = 15;
				} else if (!strcmp("CNT1GETQ1", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CNT1GETQ1;
					MODEL = 15;
				} else {
					*OP32 = INS_HALT;
					return(0);
				}
				break;
				
		case 3: if (!strcmp("FREG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FREG;
					MODEL = 3;
				} else if (!strcmp("FABS", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FABS;
					MODEL = 3;
				} else if (!strcmp("FSQRT", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FSQRT;
					MODEL = 3;
				} else if (!strcmp("FEXP", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FEXP;
					MODEL = 3;
				} else if (!strcmp("FLN", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FLN;
					MODEL = 3;
				} else if (!strcmp("FLOG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FLOG;
					MODEL = 3;
				} else if (!strcmp("FNEG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FNEG;
					MODEL = 3;
				} else if (!strcmp("FNOT", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FNOT;
					MODEL = 3;
				} else if (!strcmp("FINV", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FINV;
					MODEL = 3;
				} else if (!strcmp("FDEG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FDEG;
					MODEL = 3;
				} else if (!strcmp("FRAD", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FRAD;
					MODEL = 3;
				} else if (!strcmp("FPW2", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FPW2;
					MODEL = 3;
				} else if (!strcmp("FPW3", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FPW3;
					MODEL = 3;
					
				} else if (!strcmp("CMPRFZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFZ;
					MODEL = 3;
				} else if (!strcmp("CMPRFNZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFNZ;
					MODEL = 3;
				} else if (!strcmp("CMPRFLZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFLZ;
					MODEL = 3;
				} else if (!strcmp("CMPRFGZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFGZ;
					MODEL = 3;


				} else if (!strcmp("FJZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJZ;
					MODEL = 4;
				} else if (!strcmp("FJNZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJNZ;
					MODEL = 4;
				} else if (!strcmp("FJLZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJLZ;
					MODEL = 4;
				} else if (!strcmp("FJGZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJGZ;
					MODEL = 4;

				} else if (!strcmp("JZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JZ;
					MODEL = 13;
				} else if (!strcmp("JNZ", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JNZ;
					MODEL = 13;

				} else if (!strcmp("DIRECT", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_DIRECT;
					MODEL = 5;

				} else if (!strcmp("REG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_REG;
					MODEL = 6;
				} else if (!strcmp("INC", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_INC;
					MODEL = 6;
				} else if (!strcmp("DEC", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_DEC;
					MODEL = 6;

				} else if (!strcmp("UINT8", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_UINT8;
					MODEL = 7;

				} else if (!strcmp("FLOAT", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FLOAT;
					MODEL = 8;

				} else {
					*OP32 = INS_HALT;
					return(0);
				}
				break;
				
		case 4: if (!strcmp("FADD", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FADD;
					MODEL = 9;
				} else if (!strcmp("FSUB", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FSUB;
					MODEL = 9;
				} else if (!strcmp("FMUL", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FMUL;
					MODEL = 9;
				} else if (!strcmp("FDIV", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FDIV;
					MODEL = 9;
				} else if (!strcmp("FDIFF", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FDIFF;
					MODEL = 9;
				} else if (!strcmp("FMIN", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FMIN;
					MODEL = 9;
				} else if (!strcmp("FMAX", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FMAX;
					MODEL = 9;
				} else if (!strcmp("FMOD", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FMOD;
					MODEL = 9;
				} else if (!strcmp("FSINCOS", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FSINCOS;
					MODEL = 9;
				} else if (!strcmp("FSIN", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FSIN;
					MODEL = 9;
				} else if (!strcmp("FCOS", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FCOS;
					MODEL = 9;
				} else if (!strcmp("FTAN", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FTAN;
					MODEL = 9;
				} else if (!strcmp("FMAGANG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FMAGANG;
					MODEL = 9;

				} else if (!strcmp("CMPRFL", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFL;
					MODEL = 9;
				} else if (!strcmp("CMPRFLE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFLE;
					MODEL = 9;
				} else if (!strcmp("CMPRFG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFG;
					MODEL = 9;
				} else if (!strcmp("CMPRFGE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFGE;
					MODEL = 9;
				} else if (!strcmp("CMPRFE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFE;
					MODEL = 9;
				} else if (!strcmp("CMPRFNE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_CMPRFNE;
					MODEL = 9;
				} else if (!strcmp("CMPRFAA", INSTRUCTION_STRING_PART2)) { // FAND instruction is also same
					*OP32 = INS_CMPRFAA;
					MODEL = 9;
				} else if (!strcmp("CMPRFRR", INSTRUCTION_STRING_PART2)) { // FORR instruction is also same
					*OP32 = INS_CMPRFRR;
					MODEL = 9;
				} else if (!strcmp("FAND", INSTRUCTION_STRING_PART2)) { // CMPRFAA instruction is also same
					*OP32 = INS_CMPRFAA;
					MODEL = 9;
				} else if (!strcmp("FORR", INSTRUCTION_STRING_PART2)) { // CMPRFRR instruction is also same
					*OP32 = INS_CMPRFRR;
					MODEL = 9;
				} else if (!strcmp("FXOR", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FXOR;
					MODEL = 9;

				} else if (!strcmp("FJL", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJL;
					MODEL = 10;
				} else if (!strcmp("FJLE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJLE;
					MODEL = 10;
				} else if (!strcmp("FJG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJG;
					MODEL = 10;
				} else if (!strcmp("FJGE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJGE;
					MODEL = 10;
				} else if (!strcmp("FJE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJE;
					MODEL = 10;
				} else if (!strcmp("FJNE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_FJNE;
					MODEL = 10;

				} else if (!strcmp("ADD", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_ADD;
					MODEL = 11;
				} else if (!strcmp("SUB", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_SUB;
					MODEL = 11;
				} else if (!strcmp("MUL", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_MUL;
					MODEL = 11;

				} else if (!strcmp("JL", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JL;
					MODEL = 12;
				} else if (!strcmp("JLE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JLE;
					MODEL = 12;
				} else if (!strcmp("JG", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JG;
					MODEL = 12;
				} else if (!strcmp("JGE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JGE;
					MODEL = 12;
				} else if (!strcmp("JE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JE;
					MODEL = 12;
				} else if (!strcmp("JNE", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_JNE;
					MODEL = 12;

				} else if (!strcmp("PTRRD", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_PTRRD;
					MODEL = 14;
				} else if (!strcmp("PTRWR", INSTRUCTION_STRING_PART2)) {
					*OP32 = INS_PTRWR;
					MODEL = 14;

				} else {
					*OP32 = INS_HALT;
					return(0);
				}
				break;

		default: return(0);
				 break;
	}
	
	printf("MODEL=%d \n",MODEL);
	switch(MODEL){
		case 0: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART2,TYPE_DD,OP32,3)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;
		
		case 1: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_AA,OP32,1)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;
			
		case 2: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_SL,OP32,1)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;
		
		case 3: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_FD,OP32,1)) {return(0);} JOIN_UPB_INS();
				SKIP_UPB_INS_2();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_FA_FB,OP32,3)) {return(0);} JOIN_UPB_INS();
				return(1);
				break;
				
		case 4: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_AA,OP32,1)) return(0); SKIP_UPB_INS_1();
				SKIP_UPB_INS_2();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_FA_FB,OP32,3)) {return(0);} JOIN_UPB_INS();
				return(1);
				break;
				
		case 5: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_RD_RA_RB,OP32,1)) return(0);
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_DD,OP32,3)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;
				
		case 6: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_RD_RA_RB,OP32,1)) return(0);
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_RD_RA_RB,OP32,3)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;
				
		case 7: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_RD_RA_RB,OP32,1)) {return(0);} SKIP_UPB_INS_1();
				SKIP_UPB_INS_2();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_FA_FB,OP32,3)) {return(0);} JOIN_UPB_INS();
				return(1);
				break;
				
		case 8: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_FA_FB,OP32,1)) {return(0);} JOIN_UPB_INS();
				SKIP_UPB_INS_2();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_RD_RA_RB,OP32,3)) {return(0);} SKIP_UPB_INS_3();
				return(1);
				break;
				
		case 9: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_FD,OP32,1)) {return(0);} JOIN_UPB_INS();
				SKIP_UPB_INS_2();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_FA_FB,OP32,3)) {return(0);} JOIN_UPB_INS();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART4,TYPE_FA_FB,OP32,4)) {return(0);} JOIN_UPB_INS();
				return(1);
				break;

		case 10: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_AA,OP32,1)) {return(0);} SKIP_UPB_INS_1();
				SKIP_UPB_INS_2();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_FA_FB,OP32,3)) {return(0);} JOIN_UPB_INS();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART4,TYPE_FA_FB,OP32,4)) {return(0);} JOIN_UPB_INS();
				return(1);
				break;

		case 11: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_RD_RA_RB,OP32,1)) return(0);
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_RD_RA_RB,OP32,3)) return(0);
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART4,TYPE_RD_RA_RB,OP32,4)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;

		case 12: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_AA,OP32,1)) return(0);
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_RD_RA_RB,OP32,3)) return(0);
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART4,TYPE_RD_RA_RB,OP32,4)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;

		case 13: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_AA,OP32,1)) return(0);
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_RD_RA_RB,OP32,3)) return(0);
				UPB_INS_CHANGE=0;
				return(1);
				break;

		case 14: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_FA_FB,OP32,1)) {return(0);} JOIN_UPB_INS();
				SKIP_UPB_INS_2();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART3,TYPE_FA_FB,OP32,3)) {return(0);} JOIN_UPB_INS();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART4,TYPE_RD_RA_RB,OP32,4)) {return(0);} SKIP_UPB_INS_4();
				return(1);
				break;

		case 15: if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART1,TYPE_FD,OP32,1)) {return(0);} JOIN_UPB_INS();
				SKIP_UPB_INS_2();
				return(1);
				break;

		case 16: SKIP_UPB_INS_1();
				if(!CHECK_INS_PART_TYPE(INSTRUCTION_STRING_PART2,TYPE_FA_FB,OP32,3)) {return(0);} JOIN_UPB_INS();
				return(1);
				break;

		default: return(0);
				 break;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
u8 DECODE_INSTRUCTION(char *INSTRUCTION_STRING, u32 *OP32){
	UPB_FULL_INS[0]=0;
	UPB_INS_CHANGE=1;
	if(DECODE_INSTRUCTION_AUX(INSTRUCTION_STRING,OP32)) {
		if(!UPB_INS_CHANGE) MOVE_STRING(UPB_FULL_INS, INSTRUCTION_STRING);
		return(1);
	}
	else { *OP32=0; return(0); }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

unsigned char EVAL_INDEX=0;
char OPCODE[250];
char OPMEM[15];
char INSTRUCTION[20];
unsigned char HIT=0;
unsigned char HIT_ATLEAST_ONCE=0;
unsigned char END_LOCATOR[30];
unsigned char END_LOCATOR_TYPE[30];
unsigned char END_LOCATOR_N=1;
char OPCODE_ADDR[3];
unsigned char EVAL_INDEX_BACKUP=0;
unsigned char FIND_LIST_TEMP_ERROR=0;
unsigned char JUMP_REMINDER=0;
unsigned char JUMP_REMINDER_PREV[50];
u8 JUMP_REMINDER_PREV_INDEX=0;
u8 EVAL_ERROR=0;
u8 PARANTHSIS_START=0;
u8 PARANTHSIS_END=0;
unsigned char PROCESS_POINTER=0,PROCESS=0;
unsigned char PARANTHESIS_OR_UNARY_HIT=0;
u8 STOP_PRINT_EVAL=1;
char ASM_OUTPUT_MEM[512][128];
///////////////////////////////////////////////////////////////////////////////////////////////////////
void OPMEM_0p0(void){
	sprintf(OPMEM,"0.0");
}
struct PARAMETER{
    char NAME[54];
    char  VALUES[14];
};
struct PARAMETER PARAMETERS[255];
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void PARAMETER_FILL_ARRAY(void){
	//xil_printf("PARAMETER_FILL_ARRAY() \n\r");
	for(u8 i=0;i<255;i++){
	    #ifndef RIDE_C
		MOVE_STRING(PARAMETERS[i].NAME,TEXTBOX_CONFIG_DETAILS[i].TXT_STRING);
		MOVE_STRING(PARAMETERS[i].VALUES,TEXTBOX_CONFIG_VALUES[i].TXT_STRING);
		//xil_printf("NAME=%s VALUE=%s\n\r",PARAMETERS[i].NAME,PARAMETERS[i].VALUES);
		#endif
		//xil_printf("NAME=%s VALUE=%s\n\r",PARAMETERS[i].NAME,PARAMETERS[i].VALUES);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHANGE_PARAMETER_NAME_TO_VALUES(char *inst){
	//xil_printf("CHANGE_PARAMETER_NAME_TO_VALUES()\n\r");
    for(u8 i=0;i<255;i++){
        if(!strcmp(inst,PARAMETERS[i].NAME)){
        	//xil_printf("\r\n yes true");
        	removeSpaces(PARAMETERS[i].VALUES);
	        MOVE_STRING(inst,PARAMETERS[i].VALUES);
            break;//return(1);
        }
    }
   // return(0);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void PRINT_DEBUG(u16 DEBUG_VAL){
	#ifndef RIDE_C
	if(!STOP_PRINT_EVAL)
		xil_printf("\r\n *** DEBUG - %03d ",DEBUG_VAL);
	#else
//	printf("\r\n ********* DEBUG - %03d ",DEBUG_VAL);
	#endif	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void append_instruction_direct(char *inputstring){
	#ifndef RIDE_C
	unsigned char i;
	if(!STOP_PRINT_EVAL)
		xil_printf("\r\n append_instruction_direct EVAL_INDEX:%02X  INSTRUCTION:%s  0.0", EVAL_INDEX, inputstring);

	unsigned int EVAL_INDEX_NEW=((unsigned int)EVAL_INDEX)+10;

	for(i=0;i<20;i++){
		if(inputstring[i]!=0) { ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=inputstring[i]; }
		else { ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=' '; break; }
	}
	while(i<26){
		ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=' ';
		i++;
	}

	#else
	printf("\r\n append_instruction_direct EVAL_INDEX:%02X  INSTRUCTION:%s 0.0", EVAL_INDEX, inputstring);
	unsigned char i;
	unsigned int EVAL_INDEX_NEW=((unsigned int)EVAL_INDEX)+10;

	for(i=0;i<20;i++){
		if(inputstring[i]!=0) { ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=inputstring[i]; }
		else { ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=' '; break; }
	}
	while(i<26){
		ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=' ';
		i++;
	}
	#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char append_instruction(void){
	#ifndef RIDE_C

	if(!STOP_PRINT_EVAL)
		xil_printf("\r\n append_instruction EVAL_INDEX:%02X  INSTRUCTION:%s %s", EVAL_INDEX, OPCODE, OPMEM);
	unsigned char i;
	unsigned char START;
	u32 TEMPOP32;

	unsigned int EVAL_INDEX_NEW=((unsigned int)EVAL_INDEX)+10;

	if(DECODE_INSTRUCTION(OPCODE,&TEMPOP32)){
		for(i=0;i<20;i++){
			if(OPCODE[i]!=0) ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=OPCODE[i];
			else { OPCODE[i]=' '; break; }
		}
		while(i<26){
			ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=' ';
			i++;
		}

		if(OPMEM[0]!='-') { ASM_OUTPUT_MEM[EVAL_INDEX_NEW][VALUE_STRING_START]=' '; START=VALUE_STRING_START+1; }
		else START=VALUE_STRING_START;
		for(i=0;(START+i)<VALUE_STRING_END;i++){
			if(OPMEM[i]!=0) ASM_OUTPUT_MEM[EVAL_INDEX_NEW][START+i]=OPMEM[i];
			else { OPCODE[i]=' '; break; }
		}
		while((START+i)<VALUE_STRING_END){
			ASM_OUTPUT_MEM[EVAL_INDEX_NEW][START+i]=' ';
			i++;
		}
		return(1);
	}
	else return(0);

	#else
	printf("\r\n append_instruction EVAL_INDEX:%02X  INSTRUCTION:%s %s", EVAL_INDEX, OPCODE, OPMEM);
	unsigned char i;
	unsigned char START;
	u32 TEMPOP32;

	unsigned int EVAL_INDEX_NEW=((unsigned int)EVAL_INDEX)+10;

	if(DECODE_INSTRUCTION(OPCODE,&TEMPOP32)){
		for(i=0;i<20;i++){
			if(OPCODE[i]!=0) ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=OPCODE[i];
			else { OPCODE[i]=' '; break; }
		}
		while(i<26){
			ASM_OUTPUT_MEM[EVAL_INDEX_NEW][14+i]=' ';
			i++;
		}

		if(OPMEM[0]!='-') { ASM_OUTPUT_MEM[EVAL_INDEX_NEW][VALUE_STRING_START]=' '; START=VALUE_STRING_START+1; }
		else START=VALUE_STRING_START;
		for(i=0;(START+i)<VALUE_STRING_END;i++){
			if(OPMEM[i]!=0) ASM_OUTPUT_MEM[EVAL_INDEX_NEW][START+i]=OPMEM[i];
			else { OPCODE[i]=' '; break; }
		}
		while((START+i)<VALUE_STRING_END){
			ASM_OUTPUT_MEM[EVAL_INDEX_NEW][START+i]=' ';
			i++;
		}
		return(1);
	}
	else return(0);
	#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void remaining_halt_instruction_sub(void){
	sprintf(OPCODE,"REPEAT            ");
	OPMEM_0p0();
	append_instruction();
	EVAL_INDEX++;

	while(EVAL_INDEX<=254){
		sprintf(OPCODE,"NOP               ");
		OPMEM_0p0();
		append_instruction();
		EVAL_INDEX++;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void print_expression(void){
	unsigned char i=0;
	#ifndef RIDE_C
	if(!STOP_PRINT_EVAL){
		PRINT_LINE();
		for(i=0;i<=EXPRESSION_LIST_LENGTH;i++){
			xil_printf("%s%c",EXPRESSION_TEMP1[i],EXPRESSION_TEMP2[i]);
		}
		PRINT_LINE();
		xil_printf("\r\n EXPRESSION_LIST_LENGTH = %d",EXPRESSION_LIST_LENGTH);
		for(i=0;i<=EXPRESSION_LIST_LENGTH;i++){
			xil_printf("\r\n %02d: %s %c",i, EXPRESSION_TEMP1[i],EXPRESSION_TEMP2[i]);
		}
		PRINT_LINE();
	}
	#else
	printf("\r\n");
	for(i=0;i<=EXPRESSION_LIST_LENGTH;i++){
		printf("%s%c",EXPRESSION_TEMP1[i],EXPRESSION_TEMP2[i]);
	}
	printf("\r\n EXPRESSION_LIST_LENGTH = %d",EXPRESSION_LIST_LENGTH);
	for(i=0;i<=EXPRESSION_LIST_LENGTH;i++){
		printf("\r\n %02d: %s %c",i, EXPRESSION_TEMP1[i],EXPRESSION_TEMP2[i]);
	}
	printf("\r\n");
	#endif
}
unsigned char FINISH_INSTRUCTION=0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char OPCODE_OPMEM_APPEND(unsigned char i){
  if((EXPRESSION_TEMP2[i-1]=='=')&&(i==1)&&(EXPRESSION_LIST_LENGTH==2)){
	sprintf(OPCODE,"%s %s %s %s",EXPRESSION_TEMP1[i-1], INSTRUCTION, EXPRESSION_TEMP1[i], EXPRESSION_TEMP1[i+1]);
    FINISH_INSTRUCTION=1;
    //xil_printf("\r\n OPCODE_OPMEM_APPEND case-1");
  }
  else if((EXPRESSION_TEMP1[i-1][0]==0) && (EXPRESSION_TEMP2[i-1]=='(')&&(EXPRESSION_TEMP2[i-2]=='=')&&(EXPRESSION_TEMP2[i+1]==')')&&(i==2)&&(EXPRESSION_LIST_LENGTH==4)){
	 sprintf(OPCODE,"%s %s %s %s",EXPRESSION_TEMP1[i-2], INSTRUCTION, EXPRESSION_TEMP1[i], EXPRESSION_TEMP1[i+1]);
     FINISH_INSTRUCTION=1;
     //xil_printf("\r\n OPCODE_OPMEM_APPEND case-2");
  }
  else{
	sprintf(OPCODE,"%02X %s %s %s",EVAL_INDEX, INSTRUCTION, EXPRESSION_TEMP1[i], EXPRESSION_TEMP1[i+1]);
    FINISH_INSTRUCTION=0;
    //xil_printf("\r\n OPCODE_OPMEM_APPEND case-3");
  }  
  OPMEM_0p0();
  HIT=1;HIT_ATLEAST_ONCE=1;
  unsigned char t12=append_instruction();

  //xil_printf("\r\n append_instruction EVAL_INDEX:%02X  INSTRUCTION:%s %s", EVAL_INDEX, OPCODE, OPMEM);

  return(t12);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void MOVE_UP_EXPRESSION_LIST(unsigned char LOCATION, unsigned char OFFSET){
	unsigned char j=0;
	unsigned char k=0;

	sprintf(EXPRESSION_TEMP1[LOCATION],"%02X",EVAL_INDEX);
	EXPRESSION_TEMP2[LOCATION]=EXPRESSION_TEMP2[LOCATION+OFFSET];
	for(j=LOCATION+1;j<=EXPRESSION_LIST_LENGTH;j++){
		for(k=0;k<15;k++) EXPRESSION_TEMP1[j][k]=EXPRESSION_TEMP1[j+OFFSET][k];
		EXPRESSION_TEMP2[j]=EXPRESSION_TEMP2[j+OFFSET];
	}
	EVAL_INDEX++;
	EXPRESSION_LIST_LENGTH=EXPRESSION_LIST_LENGTH-OFFSET;
	PARANTHSIS_END = PARANTHSIS_END-OFFSET;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void FIND_LIST_TEMP(unsigned char i, unsigned char j, char *inputstring, unsigned char *start, unsigned char *end, char val, unsigned char offset){
	unsigned char var1=0;
	unsigned char k=0;
	if(i==0){
		end[0]=0;
		EXPRESSION_TEMP1[j][var1]=0;
		EXPRESSION_TEMP2[j]=val;
		start[0]=i+offset;
		FIND_LIST_TEMP_ERROR=1;
	}
	else{
		end[0]=i-1;
		if(start[0] > end[0])// initially it was >=
			EXPRESSION_TEMP1[j][var1]=0;
		else
			for(k= start[0];k<= end[0];k++) {
				EXPRESSION_TEMP1[j][var1++]=inputstring[k];
				EXPRESSION_TEMP1[j][var1]=0;
			}
		EXPRESSION_TEMP2[j]=val;
		start[0]=i+offset;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void COMMAND_START_INIT(unsigned char print_type, unsigned char END_LOCATOR_TEMP, unsigned char index){
	#ifndef RIDE_C
	unsigned char i;
	for(i=0;i<20;i++) OPCODE[i] = ASM_OUTPUT_MEM[(unsigned int)(END_LOCATOR_TEMP)+10][14+i];
	for(i=19;i>0;i--) { if(OPCODE[i]!=' ') { OPCODE[i+1]=0; break; } }
	#else
	unsigned char i;
	for(i=0;i<20;i++) OPCODE[i] = ASM_OUTPUT_MEM[(unsigned int)(END_LOCATOR_TEMP)+10][14+i];
	for(i=19;i>0;i--) { if(OPCODE[i]!=' ') { OPCODE[i+1]=0; break; } }
	if(print_type==1)sprintf(OPCODE,"?? FJZ ??    ");
	else if(print_type==2)sprintf(OPCODE,"?? JUMP    ");
	else if(print_type==3)sprintf(OPCODE,"?? FJNZ ??    ");
	#endif
	sprintf(OPCODE_ADDR,"%02X",index);
	OPCODE[0]=OPCODE_ADDR[0];
	OPCODE[1]=OPCODE_ADDR[1];
	EVAL_INDEX_BACKUP=EVAL_INDEX;
	EVAL_INDEX = END_LOCATOR_TEMP;
	append_instruction();
	EVAL_INDEX=EVAL_INDEX_BACKUP;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
u8 EVAL_INSTRUCTION(u8 i, char A, char *STR){
  EVAL_ERROR=0;
  if(EXPRESSION_TEMP2[i]==A){
    if( (EXPRESSION_TEMP1[i][0]!=0) && (EXPRESSION_TEMP1[i+1][0]!=0) && (EXPRESSION_TEMP2[i+1]!='(') )   {
      PROCESS=i;
      PROCESS_POINTER=i+1;
      //sprintf(INSTRUCTION,STR);
      MOVE_STRING(INSTRUCTION,STR);
      if(!OPCODE_OPMEM_APPEND(i)) {EVAL_ERROR=1; return(1);}
      if(FINISH_INSTRUCTION==1) MOVE_UP_EXPRESSION_LIST(i,2);
	  else MOVE_UP_EXPRESSION_LIST(i,1);
      return(1);
    }
  }
  return(0);
 }

unsigned char DO_ALL_UNARY_OPERATION(void);
void REMOVE_ALL_PHARANTHESIS(void);
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void REMOVE_ALL_PHARANTHESIS(void){ 
	unsigned char i=0;
	unsigned char j=0;
	unsigned char k=0;

		PROCESS_POINTER=0;
		PROCESS=0;
		HIT=0;
	
		while(PROCESS<EXPRESSION_LIST_LENGTH){
			//PRINT_DEBUG(17);
			for(i=PROCESS_POINTER;i<=EXPRESSION_LIST_LENGTH;i++){
				//PRINT_DEBUG(18);
				if( (EXPRESSION_TEMP2[i]=='(') && (EXPRESSION_TEMP2[i+1]==')') ){
				   if((strcmp(EXPRESSION_TEMP1[i],"SIN") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"COS") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"TAN") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"ATAN") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"ATAN2") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"SQRT") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"EXP") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"LN") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"LOG") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"ABS") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"FDEG") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"FRAD") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"PW2") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"PW3") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"IF") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"ELSIF") != 0)&&
				      (strcmp(EXPRESSION_TEMP1[i],"WHILE") != 0)){
						PROCESS=i;
						PROCESS_POINTER=i+1;

						for(k=0;k<15;k++) EXPRESSION_TEMP1[i][k]=EXPRESSION_TEMP1[i+1][k];
						EXPRESSION_TEMP2[i]=EXPRESSION_TEMP2[i+2];
						for(j=i+1;j<=EXPRESSION_LIST_LENGTH;j++){
							for(k=0;k<15;k++) EXPRESSION_TEMP1[j][k]=EXPRESSION_TEMP1[j+2][k];
							EXPRESSION_TEMP2[j]=EXPRESSION_TEMP2[j+2];
						}
						EXPRESSION_LIST_LENGTH = EXPRESSION_LIST_LENGTH - 2;
						HIT=1;HIT_ATLEAST_ONCE=1;PARANTHESIS_OR_UNARY_HIT=1;
						break;
					}
				}
				PROCESS=i;
			}
		}
		
	if(HIT){ print_expression(); }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char DO_ALL_UNARY_OPERATION(void){ 
	unsigned char i=0;

		PROCESS_POINTER=0;
		PROCESS=0;
		HIT=0;
		while(PROCESS<EXPRESSION_LIST_LENGTH){
			//PRINT_DEBUG(19);
			for(i=PROCESS_POINTER;i<=EXPRESSION_LIST_LENGTH;i++){
				//PRINT_DEBUG(20);
				if((EXPRESSION_TEMP2[i]=='-')||(EXPRESSION_TEMP2[i]=='~')){
					if((i==0) ||
					   ((EXPRESSION_TEMP2[i-1]=='(')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='=')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='>')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='<')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='*')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='/')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='&')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='|')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]=='^')&&(EXPRESSION_TEMP1[i][0]==0)) ||
					   ((EXPRESSION_TEMP2[i-1]==',')&&(EXPRESSION_TEMP1[i][0]==0)) 
					   ) {
						PROCESS=i;
						PROCESS_POINTER=i+1;
						if(EXPRESSION_TEMP1[i+1][0]!=0){
							if(EXPRESSION_TEMP2[i]=='-') sprintf(OPCODE,"%02X FNEG %s  ",EVAL_INDEX,EXPRESSION_TEMP1[i+1]);
							else sprintf(OPCODE,"%02X FNOT %s  ",EVAL_INDEX,EXPRESSION_TEMP1[i+1]);
							OPMEM_0p0();
							if(!append_instruction()) return(111);
						}
						else if(EXPRESSION_TEMP2[i+1]=='('){
							return(0);
						}
						else return(112); // error in instruction
						MOVE_UP_EXPRESSION_LIST(i,1);
						HIT=1;HIT_ATLEAST_ONCE=1;PARANTHESIS_OR_UNARY_HIT=1;
						break;
					}
				}
				PROCESS=i;
			}
		}
		if(HIT){ print_expression(); }
		return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char PARANTHESIS_AND_UNARY_CLEAR(void){
   unsigned char error_code;
   PARANTHESIS_OR_UNARY_HIT=0;
   do{
      error_code=DO_ALL_UNARY_OPERATION();
      if(error_code>0) return(error_code);
      if(HIT) continue;
      REMOVE_ALL_PHARANTHESIS();
   }while(HIT);
   return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void REMOVE_R(unsigned char x){
	if(EXPRESSION_TEMP1[x][0]=='R') {
		EXPRESSION_TEMP1[x][0]=EXPRESSION_TEMP1[x][1];
		EXPRESSION_TEMP1[x][1]=EXPRESSION_TEMP1[x][2];
		EXPRESSION_TEMP1[x][2]=EXPRESSION_TEMP1[x][3];
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
u8 COMP_EXPRESSION_TEMP1_UN_i(unsigned char i, char *TXT, char *TXT1){
	if(strcmp(EXPRESSION_TEMP1[i],TXT) == 0) {
		sprintf(OPCODE,"%02X %s UN %s ",EVAL_INDEX, TXT1, EXPRESSION_TEMP1[i+1]);
		OPMEM_0p0();
		return(1);
	}
	else {
		return(0);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
u8 COMP_EXPRESSION_TEMP1_i(unsigned char i, char *TXT, char *TXT1){
	if(strcmp(EXPRESSION_TEMP1[i],TXT) == 0) {
		sprintf(OPCODE,"%02X %s %s ",EVAL_INDEX, TXT1, EXPRESSION_TEMP1[i+1]);
		OPMEM_0p0();
		return(1);
	}
	else {
		return(0);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
u8 COMP_EXPRESSION_TEMP1_2_i(unsigned char i, char *TXT, char *TXT1){
	if(strcmp(EXPRESSION_TEMP1[i],TXT) == 0) {
		sprintf(OPCODE,"%02X %s %s %s  ",   EVAL_INDEX, TXT1, EXPRESSION_TEMP1[i+1],EXPRESSION_TEMP1[i+2]);
		OPMEM_0p0();
		return(1);
	}
	else {
		return(0);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void PRINT_JUMP_REMINDER_DETAILS(void){
	xil_printf("\r\n   -- JUMP_REMINDER_PREV_INDEX=%d ",JUMP_REMINDER_PREV_INDEX);
	for(u8 ju=0;ju<35;ju++) xil_printf("\r\n    -- JUMP_REMINDER_PREV[%d]=%d ",ju,JUMP_REMINDER_PREV[ju]);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char EVAL_EXPRESSION_SUB(char *inputstring)
{
	unsigned char LENGTH;
	unsigned char i=0;
	unsigned char i_temp=0;
	unsigned char k_init=0;
	unsigned char start=0, end=0;
	unsigned char EXPRESSION_ERROR=0;
	unsigned char j=0;
	unsigned char k=0;
	unsigned char NUMBER=0;
	unsigned char DIGIT=0,DOT=0,EXPONENT=0;
	unsigned char LOOP_BREAK;
	unsigned char FUNCT_ID;
	unsigned char ITERATION=1;
	unsigned char valid_list=0;
	unsigned char IF_BREAK=0;
    unsigned char error_code=0;
    unsigned char TEMP_MINUS=0;
	
	//PRINT_DEBUG(1);
	
   FINISH_INSTRUCTION=0;
   
	// STEP-2-A   Initialize a constant 1.0 for sincos amplitude default
	/*
    if(EVAL_INDEX==0){
		PRINT_DEBUG(7);
		sprintf(OPCODE,"NOP");
		sprintf(OPMEM,"1.0");
		append_instruction(); EVAL_INDEX++;
		PRINT_DEBUG(8);
	}
	*/
   
	#ifndef RIDE_C
	u32 TEMPOP32;
	if(DECODE_INSTRUCTION(inputstring,&TEMPOP32)){
		append_instruction_direct(inputstring);
		EVAL_INDEX++;
		return(0);
	}
	#else
	u32 TEMPOP32;
	if(DECODE_INSTRUCTION(inputstring,&TEMPOP32)){
		append_instruction_direct(inputstring);
		EVAL_INDEX++;
		return(0);
	}
	#endif

	removeSpaces(inputstring);

	LENGTH = strlen(inputstring);
	FIND_LIST_TEMP_ERROR=0;

	//PRINT_DEBUG(2);

	for(i=0;i<LENGTH+1;i++){
		valid_list=0;
		//	<   1
		//	<=  2
		//	>   3
		//	>=  4
		//	==  5
		//	/=  6
		//	&&  7
		//	||  8
		if(inputstring[i]=='<'){
			if(inputstring[i+1]=='='){
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '2', 2);i++; // '2' for  <=
				valid_list=1;
			}
			else{
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '1', 1);
				valid_list=1;
			}
		}
		else if(inputstring[i]=='>'){
			if(inputstring[i+1]=='='){
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '4', 2);i++; // '4' for  >=
				valid_list=1;
			}
			else{
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '3', 1);
				valid_list=1;
			}
		}
		else if(inputstring[i]=='='){
			if(inputstring[i+1]=='='){
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '5', 2);i++; // '5' for  ==
				valid_list=1;
			}
			else{
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, inputstring[i], 1);
				valid_list=1;
			}
		}
		else if(inputstring[i]=='/'){
			if(inputstring[i+1]=='='){
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '6', 2);i++; // '6' for  /=
				valid_list=1;
			}
			else{
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, inputstring[i], 1);
				valid_list=1;
			}
		}
		else if(inputstring[i]=='&'){
			if(inputstring[i+1]=='&'){
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '7', 2);i++; // '7' for  &&
				valid_list=1;
			}
			else{
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, inputstring[i], 1);
				valid_list=1;
			}
		}
		else if(inputstring[i]=='|'){
			if(inputstring[i+1]=='|'){
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, '8', 2);i++; // '8' for  ||
				valid_list=1;
			}
			else{
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, inputstring[i], 1);
				valid_list=1;
			}
		}
		else if((inputstring[i]=='*') || (inputstring[i]=='+') || (inputstring[i]=='-') || (inputstring[i]=='(') || (inputstring[i]==',') ||
		(inputstring[i]==')') || (inputstring[i]=='^') || (inputstring[i]=='~') || (inputstring[i]=='%') || (inputstring[i]==0) ){
			if((inputstring[i]=='-')&&((inputstring[i-1]=='E')||(inputstring[i-1]=='e'))&&((inputstring[i-2]>='0')&&(inputstring[i-2]<='9')) && (inputstring[i-3]!='R')){}
			else if((inputstring[i]=='+')&&((inputstring[i-1]=='E')||(inputstring[i-1]=='e'))&&((inputstring[i-2]>='0')&&(inputstring[i-2]<='9')) && (inputstring[i-3]!='R')){}
			else{
				FIND_LIST_TEMP(i, j, inputstring, &start, &end, inputstring[i], 1);
				valid_list=1;
			}
		}

		if(FIND_LIST_TEMP_ERROR==1) return(101);

		if(valid_list){
            CHANGE_PARAMETER_NAME_TO_VALUES(EXPRESSION_TEMP1[j]);
			#ifndef RIDE_C
            //xil_printf("\r\n");
            //xil_printf("%d: ",j);
            //xil_printf("%s",EXPRESSION_TEMP1[j]);
            //xil_printf(" ");
            //xil_printf("%c",EXPRESSION_TEMP2[j]);
            #else
			printf("\r\n");
			printf("%d: ",j);
			printf("%s",EXPRESSION_TEMP1[j]);
			printf(" ");
			printf("%c",EXPRESSION_TEMP2[j]);
            #endif
			j++;
		}
	}

	//PRINT_DEBUG(3);

	EXPRESSION_LIST_LENGTH=j-1;
	#ifndef RIDE_C
	//xil_printf("\r\n");
	#else
	printf("\r\n");
	#endif
	
	print_expression();
	#ifndef RIDE_C
	//xil_printf("\r\n");
	#else
	printf("\r\n");
	#endif
	
	if(strcmp(EXPRESSION_TEMP1[0],"ELSIF") == 0){
		if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==1) ){	// if earlier IF TYPE
			//xil_printf("\r\n HIT ************* ELSIF earlier IF TYPE");
			sprintf(OPCODE,"%02X JUMP   ",EVAL_INDEX);
			//xil_printf("\r\n %02X JUMP",EVAL_INDEX);
			OPMEM_0p0();
			JUMP_REMINDER=EVAL_INDEX;
			append_instruction();EVAL_INDEX++;
			END_LOCATOR_N--;
			COMMAND_START_INIT(1,END_LOCATOR[END_LOCATOR_N],EVAL_INDEX);
			JUMP_REMINDER_PREV[JUMP_REMINDER_PREV_INDEX++]=JUMP_REMINDER; // to store jump location
			//PRINT_JUMP_REMINDER_DETAILS();
		}
		else if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==6) ){	// if earlier ELSIF TYPE
			//xil_printf("\r\n HIT ************* ELSIF earlier ELSIF TYPE");
			//xil_printf("\r\n   JUMP_REMINDER_PREV_INDEX=%d ",JUMP_REMINDER_PREV_INDEX);
			sprintf(OPCODE,"%02X JUMP   ",EVAL_INDEX);
			//xil_printf("\r\n %02X JUMP",EVAL_INDEX);
			OPMEM_0p0();
			JUMP_REMINDER=EVAL_INDEX;
			append_instruction();EVAL_INDEX++;
			COMMAND_START_INIT(2,JUMP_REMINDER_PREV[JUMP_REMINDER_PREV_INDEX-1],EVAL_INDEX-1);
			END_LOCATOR_N--;
			COMMAND_START_INIT(1,END_LOCATOR[END_LOCATOR_N],EVAL_INDEX);
			JUMP_REMINDER_PREV[JUMP_REMINDER_PREV_INDEX-1]=JUMP_REMINDER; // to store jump location
			//PRINT_JUMP_REMINDER_DETAILS();
		}
		else{
		 	return(102);
		}
	}
	else if(strcmp(EXPRESSION_TEMP1[0],"ELSE") == 0){
		if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==1) ) { 	// if earlier IF TYPE		    
			//xil_printf("\r\n HIT ************* ELSE earlier IF TYPE");
			//xil_printf("\r\n %02X JUMP",EVAL_INDEX);
			sprintf(OPCODE,"%02X JUMP   ",EVAL_INDEX);
			OPMEM_0p0();
			JUMP_REMINDER=EVAL_INDEX; // to store jump location
			append_instruction();EVAL_INDEX++;
			END_LOCATOR_N--;
			COMMAND_START_INIT(1,END_LOCATOR[END_LOCATOR_N],EVAL_INDEX);
			JUMP_REMINDER_PREV[JUMP_REMINDER_PREV_INDEX++]=JUMP_REMINDER; // to store jump location
			//PRINT_JUMP_REMINDER_DETAILS();
		}
		else if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==6) ){	// if earlier ELSIF TYPE
			//xil_printf("\r\n HIT ************* ELSE earlier ELSIF TYPE");
			//xil_printf("\r\n   JUMP_REMINDER_PREV_INDEX=%d ",JUMP_REMINDER_PREV_INDEX);
			sprintf(OPCODE,"%02X JUMP   ",EVAL_INDEX);
			//xil_printf("\r\n %02X JUMP",EVAL_INDEX);
			OPMEM_0p0();
			JUMP_REMINDER=EVAL_INDEX;
			append_instruction();EVAL_INDEX++;
			COMMAND_START_INIT(2,JUMP_REMINDER_PREV[JUMP_REMINDER_PREV_INDEX-1],EVAL_INDEX-1);
			END_LOCATOR_N--;
			COMMAND_START_INIT(1,END_LOCATOR[END_LOCATOR_N],EVAL_INDEX);
			JUMP_REMINDER_PREV[JUMP_REMINDER_PREV_INDEX-1]=JUMP_REMINDER; // to store jump location
			//PRINT_JUMP_REMINDER_DETAILS();
		}
		else{
			//PRINT_DEBUG(6);
		 	return(103);
		}
	}
	else if(strcmp(EXPRESSION_TEMP1[0],"DO") == 0){ // while needs two storage for two jumping operations
		END_LOCATOR[END_LOCATOR_N]=EVAL_INDEX;
		if(END_LOCATOR_N < 29){
			END_LOCATOR_TYPE[END_LOCATOR_N++]=4; // DO WHILE TYPE (DO statement)
		}
	}
	else if( (strcmp(EXPRESSION_TEMP1[0],"WHILE") == 0)&&(END_LOCATOR_TYPE[END_LOCATOR_N-1]!=4)){ // while needs two storage for two jumping operations
		END_LOCATOR[END_LOCATOR_N]=EVAL_INDEX;
		if(END_LOCATOR_N < 29){
			END_LOCATOR_TYPE[END_LOCATOR_N++]=3; // WHILE TYPE
		}
	}
	else if(strcmp(EXPRESSION_TEMP1[0],"END") == 0){
		//xil_printf("\r\n END CHECK OPENING ---- EVAL_INDEX=%d, END_LOCATOR_N=%d, END_LOCATOR_TYPE[END_LOCATOR_N-1]=%d ",EVAL_INDEX,END_LOCATOR_N,END_LOCATOR_TYPE[END_LOCATOR_N-1]);
		//PRINT_JUMP_REMINDER_DETAILS();

		if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==1) ){	// if earlier IF TYPE
			END_LOCATOR_N--;
			COMMAND_START_INIT(1,END_LOCATOR[END_LOCATOR_N],EVAL_INDEX);
			//xil_printf("\r\n END CHECK (EARLIER - 'IF') ");
			//xil_printf("\r\n   -- EVAL_INDEX=%d, END_LOCATOR_N=%d, END_LOCATOR[END_LOCATOR_N]=%d ",EVAL_INDEX,END_LOCATOR_N,END_LOCATOR[END_LOCATOR_N]);
			//PRINT_JUMP_REMINDER_DETAILS();
		}
		else if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==6) ){	// if earlier ELSIF TYPE
			//xil_printf("\r\n END CHECK (EARLIER - 'ELSIF') ");
			//xil_printf("\r\n   JUMP_REMINDER_PREV_INDEX=%d ",JUMP_REMINDER_PREV_INDEX);
			COMMAND_START_INIT(2,JUMP_REMINDER_PREV[--JUMP_REMINDER_PREV_INDEX],EVAL_INDEX);
			//xil_printf("\r\n   FIRST COMMAND_START_INIT");
			//xil_printf("\r\n     -- EVAL_INDEX=%d, END_LOCATOR_N=%d, END_LOCATOR[END_LOCATOR_N]=%d ",EVAL_INDEX,END_LOCATOR_N,END_LOCATOR[END_LOCATOR_N]);
			//PRINT_JUMP_REMINDER_DETAILS();
			END_LOCATOR_N--;
			COMMAND_START_INIT(1,END_LOCATOR[END_LOCATOR_N],EVAL_INDEX);
			//xil_printf("\r\n   SECOND COMMAND_START_INIT");
			//xil_printf("\r\n     -- EVAL_INDEX=%d, END_LOCATOR_N=%d, END_LOCATOR[END_LOCATOR_N]=%d ",EVAL_INDEX,END_LOCATOR_N,END_LOCATOR[END_LOCATOR_N]);
			//PRINT_JUMP_REMINDER_DETAILS();
		}
		else if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==2) ){	// if earlier ELSE TYPE
			END_LOCATOR_N--;
			COMMAND_START_INIT(2,END_LOCATOR[END_LOCATOR_N],EVAL_INDEX);
			//xil_printf("\r\n END CHECK (EARLIER - 'ELSE') ");
			//xil_printf("\r\n   -- EVAL_INDEX=%d, END_LOCATOR_N=%d, END_LOCATOR[END_LOCATOR_N]=%d ",EVAL_INDEX,END_LOCATOR_N,END_LOCATOR[END_LOCATOR_N]);
			//PRINT_JUMP_REMINDER_DETAILS();
			JUMP_REMINDER_PREV_INDEX--;
		}
		else if( (END_LOCATOR_N > 1) && (END_LOCATOR_TYPE[END_LOCATOR_N-1]==3) ){	// if earlier WHILE TYPE
			sprintf(OPCODE,"%02X JUMP   ",END_LOCATOR[END_LOCATOR_N-2]);
			OPMEM_0p0();
			append_instruction();EVAL_INDEX++;
			COMMAND_START_INIT(3,END_LOCATOR[END_LOCATOR_N-1],EVAL_INDEX);
			END_LOCATOR_N = END_LOCATOR_N-2;
		}
		else{
		 	return(104);
		}
	}
	else if(strcmp(EXPRESSION_TEMP1[0],"PEND") == 0){
		return(255); // END OF PROGRAM
	}

	// STEP-2-B   find all the numbers, and assign it to memory as variable,  start from address 00
	if(EXPRESSION_LIST_LENGTH>0){
		//PRINT_DEBUG(9);
		for(i=0;i<=EXPRESSION_LIST_LENGTH;i++){
			//PRINT_DEBUG(10);
			NUMBER=0;
			DIGIT=0;
			DOT=0;
			EXPONENT=0;
			for(j=0;j<25;j++) {
				if(EXPRESSION_TEMP1[i][j]==0) break;
				else if((EXPRESSION_TEMP1[i][j]>='0')&&(EXPRESSION_TEMP1[i][j]<='9'))DIGIT++;
				else if(EXPRESSION_TEMP1[i][j]=='.') DOT++;
				else if((EXPRESSION_TEMP1[i][j]=='E')||(EXPRESSION_TEMP1[i][j]=='e')) {
					if((EXPRESSION_TEMP1[i][j-1]=='.')||(EXPRESSION_TEMP1[i][j+1]=='.')) return(105);
					else if(EXPRESSION_TEMP1[i][j+1]=='-') { if((EXPRESSION_TEMP1[i][j+2]>='0')&&(EXPRESSION_TEMP1[i][j+2]<='9')) { EXPONENT++; j++; } else return(205);}
					else if(EXPRESSION_TEMP1[i][j+1]=='+') { if((EXPRESSION_TEMP1[i][j+2]>='0')&&(EXPRESSION_TEMP1[i][j+2]<='9')) { EXPONENT++; j++; } else return(206);}
					else if( (EXPRESSION_TEMP1[i][j+1]>='0')&&(EXPRESSION_TEMP1[i][j+1]<='9') && (EXPRESSION_TEMP1[i][j-1]>='0') && (EXPRESSION_TEMP1[i][j-1]<='9') )
						     EXPONENT++;
				}
				else{
					//xil_printf("\r\n NUMBER=0 ");
					NUMBER=0;
					break;
				}
				if((DIGIT==0)&&(DOT==0)&&(EXPONENT==0)) { NUMBER=0; break; }
				if((DOT>1)||(EXPONENT>1)) return(106);
				if((DOT==1)&&(DIGIT==0)) return(107);
				else {
					//xil_printf("\r\n NUMBER=1 ");
					NUMBER=1;
				}
			}
			if(NUMBER){
				//PRINT_DEBUG(501);
		        //xil_printf("\r\n EXPRESSION_LIST_LENGTH = %d EXPRESSION_TEMP2[i-1]=%c i=%d",EXPRESSION_LIST_LENGTH,EXPRESSION_TEMP2[i-1],i);
        		  
		        //printf("EXPRESSION_LIST_LENGTH = %d ,EXPRESSION_TEMP2[i-1]=%c , i=%d ",EXPRESSION_LIST_LENGTH, EXPRESSION_TEMP2[i-1], i);
        		  
		        if( ((EXPRESSION_LIST_LENGTH==1)&&(EXPRESSION_TEMP2[i-1]=='=')&&(i==1)) ||
		            ((EXPRESSION_LIST_LENGTH==2)&&(EXPRESSION_TEMP2[i-1]=='-')&&(EXPRESSION_TEMP1[i-1][0]==0)&&(EXPRESSION_TEMP2[i-2]=='=')&&(i==2)) )
		        {
						/*
						if(i==1){
			    			REMOVE_R(i-1);
			            sprintf(OPCODE,"%s FREG %02X   ",EXPRESSION_TEMP1[i-1],EVAL_INDEX);
		            	for(k=0;k<15;k++) OPMEM[k]=EXPRESSION_TEMP1[i][k];
		            }
		            else {
			    			REMOVE_R(i-2);
			            sprintf(OPCODE,"%s FREG %02X   ",EXPRESSION_TEMP1[i-2],EVAL_INDEX);
		            	OPMEM[0]='-';
							for(k=1;k<15;k++) OPMEM[k]=EXPRESSION_TEMP1[i][k-1];
						}
						*/
					//PRINT_DEBUG(502);
		            if(i==1) {
						//PRINT_DEBUG(503);
		            	i_temp = i-1;
		            	k_init=0;
		            }
		            else {
						//PRINT_DEBUG(504);
		            	i_temp = i-2;
		            	k_init=1;
		            	OPMEM[0]='-';
		            }
		    		REMOVE_R(i_temp);
		            sprintf(OPCODE,"%s FREG %02X   ",EXPRESSION_TEMP1[i_temp],EVAL_INDEX);
		            for(k=k_init;k<15;k++) {
		            	OPMEM[k]=EXPRESSION_TEMP1[i][k-k_init];
		            }
		            append_instruction();
		            FINISH_INSTRUCTION=1;
		            EVAL_INDEX++;
		            break;
		        }
		        else{
					//PRINT_DEBUG(505);
					sprintf(OPCODE,"NOP        ");
					if(EXPRESSION_TEMP2[i-1]=='-'){
						//PRINT_DEBUG(506);
						if(((EXPRESSION_TEMP2[i-2]=='(')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]=='=')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]=='>')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]=='<')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]=='*')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
					   	   ((EXPRESSION_TEMP2[i-2]=='/')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]=='&')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]=='|')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]=='^')&&(EXPRESSION_TEMP1[i-1][0]==0)) ||
						   ((EXPRESSION_TEMP2[i-2]==',')&&(EXPRESSION_TEMP1[i-1][0]==0)) 
						   ) {
							OPMEM[0]='-';
							for(k=1;k<15;k++) OPMEM[k]=EXPRESSION_TEMP1[i][k-1];
						
							sprintf(EXPRESSION_TEMP1[i-1],"%02X",EVAL_INDEX);
							EXPRESSION_TEMP2[i-1]=EXPRESSION_TEMP2[i];
							for(j=i+1;j<=EXPRESSION_LIST_LENGTH;j++){
								for(k=0;k<15;k++) EXPRESSION_TEMP1[j-1][k]=EXPRESSION_TEMP1[j][k];
									EXPRESSION_TEMP2[j-1]=EXPRESSION_TEMP2[j];
							}
							EXPRESSION_LIST_LENGTH=EXPRESSION_LIST_LENGTH-1;
  					  	   print_expression();
  						   append_instruction();
  						   EVAL_INDEX++;
  						   TEMP_MINUS=1;
  						   i--;
			         }
			     }
			     if(!TEMP_MINUS){
					//PRINT_DEBUG(507);
			     	for(k=0;k<15;k++) OPMEM[k]=EXPRESSION_TEMP1[i][k];
			     	append_instruction();
			     	sprintf(EXPRESSION_TEMP1[i],"%02X",EVAL_INDEX++);
			     }
			     TEMP_MINUS=0;
				}
			}
		}
	}
	print_expression();

	//PRINT_DEBUG(12);

	// Remove all 'R' from Rxx register definition
	for(i=0;i<=EXPRESSION_LIST_LENGTH;i++){
		REMOVE_R(i);
	}
	print_expression();

	//PRINT_DEBUG(121);
	//#ifndef RIDE_C
	//if(!STOP_PRINT) xil_printf("\r\n EXPRESSION_LIST_LENGTH=%d, ITERATION=%d, IF_BREAK=%d, FINISH_INSTRUCTION=%d",EXPRESSION_LIST_LENGTH,ITERATION,IF_BREAK,FINISH_INSTRUCTION);
	//#else
	//printf("\r\n EXPRESSION_LIST_LENGTH=%d, ITERATION=%d, IF_BREAK=%d, FINISH_INSTRUCTION=%d",EXPRESSION_LIST_LENGTH,ITERATION,IF_BREAK,FINISH_INSTRUCTION);
	//#endif

    while((EXPRESSION_LIST_LENGTH>1)&&(ITERATION<50)&&(IF_BREAK==0)&&(FINISH_INSTRUCTION==0)){
    	//PRINT_DEBUG(122);
    	HIT_ATLEAST_ONCE=0;
		error_code=PARANTHESIS_AND_UNARY_CLEAR();
    	//PRINT_DEBUG(123);
		if(error_code>0) return(error_code);
    	//PRINT_DEBUG(124);
		if(PARANTHESIS_OR_UNARY_HIT) continue;
    	//PRINT_DEBUG(125);
		
		// STEP-1 check innermost paranthesis starting, ending
		PARANTHSIS_START=0;
		PARANTHSIS_END=EXPRESSION_LIST_LENGTH;
		for(i=0;i<=EXPRESSION_LIST_LENGTH;i++){
			if(EXPRESSION_TEMP2[i]=='(')
				PARANTHSIS_START=i;
			if(EXPRESSION_TEMP2[i]==')'){
				PARANTHSIS_END=i;
				break;
			}
		}
		
		//PRINT_DEBUG(13);
		#ifndef RIDE_C
		if(!STOP_PRINT_EVAL)xil_printf("\r\n SOLVER ITERATION = %d",ITERATION);
		#else
		printf("\r\n SOLVER ITERATION = %d",ITERATION);
		#endif
		ITERATION++;
		
		// STEP-3   Remove all scientific functions
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while((PROCESS<PARANTHSIS_END)&&(IF_BREAK==0)){
			//PRINT_DEBUG(14);
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				//PRINT_DEBUG(15);
				LOOP_BREAK=0;
				if( (EXPRESSION_TEMP2[i]=='(') && (EXPRESSION_TEMP2[i+1]==')') ){
					FUNCT_ID=0; // SIN-1 COS-2 TAN-3 SQRT-4 EXP-5 LN-6 LOG-7
					if(COMP_EXPRESSION_TEMP1_UN_i(i,"SIN", "FSIN")) {FUNCT_ID=1;}
					else if(COMP_EXPRESSION_TEMP1_UN_i(i,"COS", "FCOS")) {FUNCT_ID=2;}
					else if(COMP_EXPRESSION_TEMP1_UN_i(i,"ATAN", "FMAGANG")) {FUNCT_ID=2;
						if(!append_instruction()) return(108);
						EVAL_INDEX++;
						sprintf(OPCODE,"%02X FREG MM   ",EVAL_INDEX);
						OPMEM_0p0();
					}
					/*
					else if(COMP_EXPRESSION_TEMP1_UN_i(i,"COS", "FSINCOS")||COMP_EXPRESSION_TEMP1_UN_i(i,"ATAN", "FMAGANG")) {FUNCT_ID=2;
						if(!append_instruction()) return(108);
						EVAL_INDEX++;
						sprintf(OPCODE,"%02X FREG MM   ",EVAL_INDEX);
						OPMEM_0p0();
					}*/
					else if(COMP_EXPRESSION_TEMP1_UN_i(i,"TAN", "FTAN")) {FUNCT_ID=3;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"SQRT", "FSQRT" )) {FUNCT_ID=4;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"EXP" , "FEXP"  )) {FUNCT_ID=5;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"LN"  , "FLN"   )) {FUNCT_ID=6;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"LOG" , "FLOG"  )) {FUNCT_ID=7;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"ABS" , "FABS"  )) {FUNCT_ID=8;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"FDEG" , "FDEG"  )) {FUNCT_ID=9;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"FRAD" , "FRAD"  )) {FUNCT_ID=10;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"PW2" , "FPW2"  )) {FUNCT_ID=11;}
					else if(COMP_EXPRESSION_TEMP1_i(i,"PW3" , "FPW3"  )) {FUNCT_ID=12;}
					else if(EXPRESSION_TEMP1[i][0] == 0) FUNCT_ID=25;
					switch(FUNCT_ID){
						case 0: 	if(strcmp(EXPRESSION_TEMP1[i],"IF") == 0) { IF_BREAK=1; LOOP_BREAK=1; break;}
									if(strcmp(EXPRESSION_TEMP1[i],"ELSIF") == 0) { IF_BREAK=1; LOOP_BREAK=1; break;}
									if(strcmp(EXPRESSION_TEMP1[i],"WHILE") == 0) { IF_BREAK=1; LOOP_BREAK=1; break;}
									//if(strcmp(EXPRESSION_TEMP1[i],"ELSE") == 0) { IF_BREAK=1; LOOP_BREAK=1; break;} // since EXPRESSION_LIST_LENGTH=0, it wont be required
									//if(strcmp(EXPRESSION_TEMP1[i],"END") == 0) { IF_BREAK=1; LOOP_BREAK=1; break;}  // since EXPRESSION_LIST_LENGTH=0, it wont be required
									EXPRESSION_ERROR=1; break; // other fault instruction
						case 1: 	// SIN
						case 2: 	// COS or ATAN
						case 3: 	// TAN
						case 4: 	// SQRT
						case 5: 	// EXP
						case 6: 	// LN
						case 7: 	// LOG
						case 8: 	// ABS
						case 9: 	// DEG
						case 10: 	// RAD
						case 11: 	// PW2
						case 12: 	// PW3
									if(!append_instruction()) return(109);
									PROCESS=i;
									PROCESS_POINTER=i+1;
									MOVE_UP_EXPRESSION_LIST(i,2);
									LOOP_BREAK=1;
									HIT=1;HIT_ATLEAST_ONCE=1;
									break;

						case 25: 	break; // If NULL
						default:	break;
					}
					if(EXPRESSION_ERROR) return(110);
					if(LOOP_BREAK==1)break;
				}
				else if( (EXPRESSION_TEMP2[i]=='(') && (EXPRESSION_TEMP2[i+1]==',') && (EXPRESSION_TEMP2[i+2]==')') ){
					FUNCT_ID=0; // SIN-1 COS-2 TAN-3 SQRT-4 EXP-5 LN-6 LOG-7
					if(COMP_EXPRESSION_TEMP1_2_i(i,"MIN","FMIN")){FUNCT_ID=20;}
					else if(COMP_EXPRESSION_TEMP1_2_i(i,"MAX","FMAX"    )){FUNCT_ID=21;}
					else if(COMP_EXPRESSION_TEMP1_2_i(i,"DIF","FDIFF"   )){FUNCT_ID=22;}
					else if(COMP_EXPRESSION_TEMP1_2_i(i,"MOD","FMOD"    )){FUNCT_ID=23;}
					else if(COMP_EXPRESSION_TEMP1_2_i(i,"MAG","FMAGANG" )){FUNCT_ID=24;}
					else if(COMP_EXPRESSION_TEMP1_2_i(i,"ANG","FMAGANG" )||COMP_EXPRESSION_TEMP1_2_i(i,"ATAN2","FMAGANG" )){FUNCT_ID=25;
						if(!append_instruction()) return(108);
						EVAL_INDEX++;
						sprintf(OPCODE,"%02X FREG MM   ",EVAL_INDEX);
						OPMEM_0p0();
					}
					else if(EXPRESSION_TEMP1[i][0] == 0) FUNCT_ID=50;
					switch(FUNCT_ID){
						case 20: 	// MIN
						case 21: 	// MAX
						case 22: 	// DIF
						case 23: 	// MOD
						case 24: 	// MAG
						case 25: 	// ANG
									if(!append_instruction()) return(109);
									PROCESS=i;
									PROCESS_POINTER=i+1;
									MOVE_UP_EXPRESSION_LIST(i,3);
									LOOP_BREAK=1;
									HIT=1;HIT_ATLEAST_ONCE=1;
									break;
						case 50: 	break; // If NULL
						default:	break;
					}
					if(EXPRESSION_ERROR) return(120);
					if(LOOP_BREAK==1)break;
				}				
				PROCESS=i;
			}
		}
		if(IF_BREAK) break;
		if(HIT) { print_expression(); continue; }

		//PRINT_DEBUG(16);

		// STEP-6   Do all multiplications, divisions and modulo between values or variables, wont consider after or before paranthesis
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			//PRINT_DEBUG(21);
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				//PRINT_DEBUG(22);
				if(EVAL_INSTRUCTION(i, '*', "FMUL")) {if(EVAL_ERROR) return(113); else break;}
				else if(EVAL_INSTRUCTION(i, '/', "FDIV")) {if(EVAL_ERROR) return(113); else break;}
				else if(EVAL_INSTRUCTION(i, '%', "FMOD")) {if(EVAL_ERROR) return(113); else break;}
				PROCESS=i;
				if(HIT) break;
			}
			if(HIT) break;
		}
		if(HIT) { print_expression(); continue; }
	
		// STEP-7   Do all additions and subtractions between values or variables, wont consider after or before paranthesis
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				if(EVAL_INSTRUCTION(i, '+', "FADD")) {if(EVAL_ERROR) return(114); else break;}
				else if(EVAL_INSTRUCTION(i, '-', "FSUB")) {if(EVAL_ERROR) return(114); else break;}
				PROCESS=i;
				if(HIT) break;
			}
			if(HIT) break;
		}
		if(HIT) { print_expression(); continue; }

		// STEP-8   Do comparision operations like < <= > >=
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				if(EVAL_INSTRUCTION(i, '1', "CMPRFL")) {if(EVAL_ERROR) return(115); else break;}        // <   1
				else if(EVAL_INSTRUCTION(i, '2', "CMPRFLE")) {if(EVAL_ERROR) return(115); else break;}  // <=  2
				else if(EVAL_INSTRUCTION(i, '3', "CMPRFG")) {if(EVAL_ERROR) return(115); else break;}   // >   3
				else if(EVAL_INSTRUCTION(i, '4', "CMPRFGE")) {if(EVAL_ERROR) return(115); else break;}  // >=  4
				PROCESS=i;
			}
		}
		if(HIT) { print_expression(); continue; }

		// STEP-9   Do comparision operations like == /=
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				if(EVAL_INSTRUCTION(i, '5', "CMPRFE")) {if(EVAL_ERROR) return(116); else break;}        //  == 5
				else if(EVAL_INSTRUCTION(i, '6', "CMPRFNE")) {if(EVAL_ERROR) return(116); else break;}  //  /= 6
				PROCESS=i;
			}
		}
		if(HIT) { print_expression(); continue; }

		// STEP-10   Bitwise AND
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				if(EVAL_INSTRUCTION(i, '&', "FAND")) {if(EVAL_ERROR) return(117); else break;}
				PROCESS=i;
			}
		}
		if(HIT) { print_expression(); continue; }

		// STEP-11   Bitwise XOR
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				if(EVAL_INSTRUCTION(i, '^', "FXOR")) {if(EVAL_ERROR) return(118); else break;}
				PROCESS=i;
			}
		}
		if(HIT) { print_expression(); continue; }

		// STEP-12   Bitwise OR
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				if(EVAL_INSTRUCTION(i, '|', "FORR")) {if(EVAL_ERROR) return(119); else break;}
				PROCESS=i;
			}
		}
		if(HIT) { print_expression(); continue; }

		// STEP-13   Do comparison operations like && ||  (Logical AND and Logical OR operations)
		PROCESS_POINTER=PARANTHSIS_START;
		PROCESS=0;
		HIT=0;
		while(PROCESS<PARANTHSIS_END){
			for(i=PROCESS_POINTER;i<=PARANTHSIS_END;i++){
				//	&&  7
				//	||  8
				if( (EXPRESSION_TEMP2[i]=='7') || (EXPRESSION_TEMP2[i]=='8') ){
					if( (EXPRESSION_TEMP1[i][0]!=0) && (EXPRESSION_TEMP1[i+1][0]!=0) && (EXPRESSION_TEMP2[i+1]!='(') )   {
						PROCESS=i;
						PROCESS_POINTER=i+1;

						if(EXPRESSION_TEMP2[i]=='7') sprintf(INSTRUCTION,"CMPRFAA");
						else sprintf(INSTRUCTION,"CMPRFRR");
						if(!OPCODE_OPMEM_APPEND(i)) return(120);
						MOVE_UP_EXPRESSION_LIST(i,1);
						break;
					}
				}
				PROCESS=i;
			}
		}
		if(HIT) { print_expression(); continue; }

		if(HIT_ATLEAST_ONCE==0) break;
	}

	if(FINISH_INSTRUCTION==1){
		#ifndef RIDE_C
		//xil_printf("\r\n Instruction Shortened");
		#else
		//printf("\r\n Instruction Shortened");
		#endif
	}
	else if((EXPRESSION_TEMP2[0]=='=')&&(EXPRESSION_LIST_LENGTH==1))  {
		//PRINT_DEBUG(23);
		sprintf(OPCODE,"%s FREG %s",EXPRESSION_TEMP1[0],EXPRESSION_TEMP1[1]);
		OPMEM_0p0();
		if(!append_instruction()) return(121);
		EVAL_INDEX++;
  	}
  	else if( (strcmp(EXPRESSION_TEMP1[0],"IF") == 0) && (EXPRESSION_TEMP2[0]=='(') && (EXPRESSION_TEMP2[1]==')') && (EXPRESSION_LIST_LENGTH==2) ){
		//PRINT_DEBUG(24);
		sprintf(OPCODE,"%02X FJZ %s",EVAL_INDEX,EXPRESSION_TEMP1[1]);
		OPMEM_0p0();
		if(!append_instruction()) return(122);
		MOVE_UP_EXPRESSION_LIST(i,2);
		print_expression();
		END_LOCATOR[END_LOCATOR_N]=EVAL_INDEX-1; // ELSE_LOCATOR[--ELSE_LOCATOR_EVAL_INDEX]
		if(END_LOCATOR_N < 29){
			END_LOCATOR_TYPE[END_LOCATOR_N++]=1; // IF TYPE
		}
		else return(123);
  	}
  	else if( (strcmp(EXPRESSION_TEMP1[0],"ELSIF") == 0) && (EXPRESSION_TEMP2[0]=='(') && (EXPRESSION_TEMP2[1]==')') && (EXPRESSION_LIST_LENGTH==2) ){
		//PRINT_DEBUG(25);
  		sprintf(OPCODE,"%02X FJZ %s",EVAL_INDEX,EXPRESSION_TEMP1[1]);
  		OPMEM_0p0();
		if(!append_instruction()) return(125);
		MOVE_UP_EXPRESSION_LIST(i,2);
		print_expression();
		END_LOCATOR[END_LOCATOR_N]=EVAL_INDEX-1; // ELSE_LOCATOR[--ELSE_LOCATOR_EVAL_INDEX]
		if(END_LOCATOR_N < 29){
			END_LOCATOR_TYPE[END_LOCATOR_N++]=6; // ELSIF TYPE
		}
		else return(126);
  	}
  	else if( (strcmp(EXPRESSION_TEMP1[0],"WHILE") == 0) && (EXPRESSION_TEMP2[0]=='(') && (EXPRESSION_TEMP2[1]==')') && (EXPRESSION_LIST_LENGTH==2) ){
		//PRINT_DEBUG(26);
  		if(END_LOCATOR_TYPE[END_LOCATOR_N-1]==4){ //DO WHILE TYPE ENDS
			#ifndef RIDE_C
			//xil_printf("\r\n DO WHILE TYPE ENDS");
			#else
			printf("\r\n DO WHILE TYPE ENDS");
			#endif
			sprintf(OPCODE,"%02X FJZ %s",END_LOCATOR[END_LOCATOR_N],EXPRESSION_TEMP1[1]);
			OPMEM_0p0();
			if(!append_instruction()) return(127);
			MOVE_UP_EXPRESSION_LIST(i,2);
			print_expression();
			if(END_LOCATOR_N > 1) END_LOCATOR_N--;
			else return(128);
		}
		else{
			sprintf(OPCODE,"%02X FJZ %s",EVAL_INDEX,EXPRESSION_TEMP1[1]);
			OPMEM_0p0();
			if(!append_instruction()) return(129);
			MOVE_UP_EXPRESSION_LIST(i,2);
			print_expression();
			END_LOCATOR[END_LOCATOR_N]=EVAL_INDEX-1; // ELSE_LOCATOR[--ELSE_LOCATOR_EVAL_INDEX]
			if(END_LOCATOR_N < 29){
				END_LOCATOR_TYPE[END_LOCATOR_N++]=3; // WHILE TYPE
			}
			else return(130);
		}
  	}
  	else if(strcmp(EXPRESSION_TEMP1[0],"ELSE") == 0){
		//PRINT_DEBUG(27);
		END_LOCATOR[END_LOCATOR_N]=EVAL_INDEX-1;
		if(END_LOCATOR_N < 29){
			END_LOCATOR_TYPE[END_LOCATOR_N++]=2; // ELSE TYPE
		}
		else return(131);
  	}
  	else if(strcmp(EXPRESSION_TEMP1[0],"END") == 0){
		//PRINT_DEBUG(28);

  		if(END_LOCATOR_TYPE[END_LOCATOR_N]==1){
			#ifndef RIDE_C
			//xil_printf("\r\n IF TYPE ENDS");
			#else
			//printf("\r\n IF TYPE ENDS");
			#endif
			//PRINT_DEBUG(29);
		}
  		else if(END_LOCATOR_TYPE[END_LOCATOR_N]==6){
			#ifndef RIDE_C
			//xil_printf("\r\n ELSIF TYPE ENDS");
			#else
			//printf("\r\n ELSIF TYPE ENDS");
			#endif
		}
  		else if(END_LOCATOR_TYPE[END_LOCATOR_N]==2){
			#ifndef RIDE_C
			//printf("\r\n ELSE TYPE ENDS");
			#else
			//printf("\r\n ELSE TYPE ENDS");
			#endif
			//PRINT_DEBUG(30);
		}
  		else if(END_LOCATOR_TYPE[END_LOCATOR_N]==3){
			#ifndef RIDE_C
			//xil_printf("\r\n WHILE TYPE ENDS");
			#else
			//printf("\r\n WHILE TYPE ENDS");
			#endif
  		}
  	}
  	else if(strcmp(EXPRESSION_TEMP1[0],"DO") == 0){
		#ifndef RIDE_C
		//xil_printf("\r\n DO TYPE STARTED");
		#else
		//printf("\r\n DO TYPE STARTED");
		#endif
  	}
  	else{
      return(135);// ERROR IN EXPRESSION
  	}

	//PRINT_DEBUG(31);

	#ifndef RIDE_C
	if(!STOP_PRINT_EVAL) xil_printf("\r\n EVALUATE EXPRESSION FUNCTON ENDS  ******* ");
	#else
	printf("\r\n EVAL EXPRESSION FUNCTON ENDS  *** ");
	#endif

	return(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned char EVAL_EXPRESSION(char OUTPUT_ASM[][128], char *inputstring)
{
	u16 m,n;
	unsigned char TEMP1;
	for(m=0; m<512; m++) for(n=0; n<128; n++)   ASM_OUTPUT_MEM[m][n] = OUTPUT_ASM[m][n];
	TEMP1 = EVAL_EXPRESSION_SUB(inputstring);
	for(m=0; m<512; m++) for(n=0; n<128; n++)   OUTPUT_ASM[m][n] = ASM_OUTPUT_MEM[m][n];
	return(TEMP1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void remaining_halt_instruction(char OUTPUT_ASM[][128]){
	u16 m,n;
	remaining_halt_instruction_sub();
	for(m=0; m<512; m++) for(n=0; n<128; n++)   OUTPUT_ASM[m][n] = ASM_OUTPUT_MEM[m][n];
}

#ifdef RIDE_C
char OUTPUT_ASM[512][128];
char inputstring[100]="Q0 = D0*SIN(D0) + 500 + Ls1 + AS";
int main()
{
    printf("Hello World");
    unsigned char EXPR_ERROR_CODE;

    EXPR_ERROR_CODE = EVAL_EXPRESSION(OUTPUT_ASM, inputstring);

    return 0;
}
#endif
