
//W25Q64 
#define W25QXX_BASE_ADDR			  0x10000								//Bin文件存储的基地址 block1 
#define NEED_UPGRADE_ADDR1			0x1F0000              //需要升级的标志位基地址      


//升级文件信息结构体
typedef struct{
	unsigned char NeedUpgrade[12];          //是否升级标志
	unsigned char BinVersion[3];            //Bin文件版本 
	unsigned char BinVersionDate[10];				//Bin文件版本时间
	unsigned short TotalBinSize;						//Bin文件总大小
	unsigned short TotalSector;							//总的扇区占用
	unsigned short LastWriteDataLen;				//最后一次写入的数据长度
	unsigned char MD5[16];                   //Bin文件MD5值
}BinDataInfoDef; 


//要读出的bin信息
BinDataInfoDef r_BinInfo;
void NetUpGrade(void)
{
	
	MD5Init(&context_bin);  
	
	unsigned char W25Q64_BinDataBuf[2048];     //2K的缓冲
//  BinDataInfoDef r_BinInfo;
	unsigned int i;
	
	//读取W25Q64的Flash中的 标志位	
	sf_ReadBuffer(r_BinInfo.NeedUpgrade,NEED_UPGRADE_ADDR1,sizeof(r_BinInfo));         //读取FLASH 标志
	
	if(strstr((char*)r_BinInfo.NeedUpgrade,"NeedUpGrade") !=NULL)        //判断是否需要升级
	{
		//读取存储信息 多少个扇区 最后一个扇区有多少数据等
		 printf("Read out %s\r\n",r_BinInfo.NeedUpgrade);
		 printf("Read out Total Bin size %d\r\n",r_BinInfo.TotalBinSize); //数据大小
		 printf("Read out total sector %d\r\n",r_BinInfo.TotalSector);    //总的扇区占用
		 printf("Read out LastWriteDataLen %d\r\n",r_BinInfo.LastWriteDataLen); //最后一次写入的数据长度		 	
		for(i = 0; i < r_BinInfo.TotalSector*2 ; i++)
		{
			if(i == r_BinInfo.TotalSector*2-1)  //最后一次的单独处理
			{
				sf_ReadBuffer(W25Q64_BinDataBuf,W25QXX_BASE_ADDR+ReadFlashOffset,r_BinInfo.LastWriteDataLen);
				ReadFlashOffset += r_BinInfo.LastWriteDataLen;
				HAL_Delay(1);
				//将读取的数据写入STM32的运行区
				bsp_WriteCpuFlash(AppAddr+WriteFlashAddrCur,W25Q64_BinDataBuf,r_BinInfo.LastWriteDataLen);
				WriteFlashAddrCur += r_BinInfo.LastWriteDataLen;                     //flash address offset 2K 
			}
			else                                //前面每次读取2K 
			{
				//循环 从W25Q64中读取bin文件 每次读取2K到缓存		
				sf_ReadBuffer(W25Q64_BinDataBuf,W25QXX_BASE_ADDR+ReadFlashOffset,2048);
				ReadFlashOffset += 2048;
				HAL_Delay(1);
				//将读取的数据写入STM32的运行区
				bsp_WriteCpuFlash(AppAddr+WriteFlashAddrCur,W25Q64_BinDataBuf,2048);
				WriteFlashAddrCur += 2048;                     //flash address offset 2K   
			}														
		}
		
		printf("\r\n ****UP Done**** \r\n");
		memset(NeedUpGrade,0,12);                             //擦除清除是否需要升级标志
	  memcpy(r_BinInfo.NeedUpgrade,NeedUpGrade,12);
		sf_WriteBuffer((unsigned char *)&r_BinInfo,NEED_UPGRADE_ADDR1, sizeof(r_BinInfo));; 

		//写完后重启中控
		__disable_irq();
		HAL_NVIC_SystemReset();                //设备重启	
		
	}
}

