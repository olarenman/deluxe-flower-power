/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "adc.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char MESSAGE[17];
char hard_MESSAGE[17];
const int PULSE=512;
const int DELAYMULTIPLIER = 7;
const int DELAYOFFSET = 400;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
/* **************************************************
Delayfunktion för att få mikrosekunder som behövs för sändning.
Kalibreras nedan i while-loopen.
*/
void US_Delay(int u){
  u=(u*DELAYMULTIPLIER)+DELAYOFFSET;
  for(;u>=0;u--){ 
  }
}
/* **************************************************
Metod för att skicka nollor.
*/
void sendZero(){
  HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_SET); // TX Set High
  US_Delay(PULSE);
  HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_RESET); // TX Set Low
  US_Delay(PULSE * 2);
  HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_SET); // TX Set High
  US_Delay(PULSE);

}
/* **************************************************
Metod för att skicka ettor.
*/
void sendOne(){
  HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_RESET); // TX Set Low
  US_Delay(PULSE);
  HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_SET); // TX Set High
  US_Delay(PULSE * 2);
  HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_RESET); // TX Set Low
  US_Delay(PULSE);

}
/* **************************************************
Skickar preamble dvs 16st 1:or 
*/
void Preamble(){
  for(int i = 0; i < 16; i++){
    sendOne();
  }
}


/* **************************************************
Skickar postamble, dvs 8st 0:or
*/
void Postamble(){
  for(int i = 0; i < 8; i++){
    sendZero();
  }
}
/* **************************************************
Sendningsfunktion som skickar nibs, dvs 4-bitar
*/
void sendNib(char n){
  if((n & 0x1) > 0) sendOne(); else sendZero();
  if((n & 0x2) > 0) sendOne(); else sendZero();
  if((n & 0x4) > 0) sendOne(); else sendZero();
  if((n & 0x8) > 0) sendOne(); else sendZero();
//  US_Delay(2000); debug
}

/* **************************************************
Skickar en syncnib
*/
void Sync(){
  sendNib(0xA);

}
/* **************************************************
Räknar ut checksumman för meddelandes som ska skickas.
*/
void CheckSum(){
  char check=0;
  char MSB=0;
  char LSB=0;
  
  for(int i = 0; i<15; i++){
    check +=MESSAGE[i];   
    //printf("MESSAGE[%d] = %x", i,MESSAGE[i]);
  }
 // printf("Checkpre = %x\n", check);
  MSB = (check & 0xF0) >> 4;
  LSB = check & 0xF;
  
  
  //printf("Checkpost = %x\n", check);
  //printf("MSB = %x\n", MSB);
  //printf("LSB = %x\n", LSB);
  //HAL_Delay(500);
  MESSAGE[16] = MSB;
  MESSAGE[15] = LSB;

  /*
  HAL_Delay(1000);
  printf("Checksum = %x\n", check);
  HAL_Delay(1000);
  printf("CheckMSB = %x\n", MSB);
  HAL_Delay(1000);
  printf("CheckLSB = %x\n\n", LSB);
  */
 
}
/* **************************************************
Huvudfunktion för att skicka det som ligger i MESSAGE()
*/
void Send(){
  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET); // Led 
  Preamble();
  
  Sync();
  
  for(int i = 0 ; i < 17; i++){
    sendNib(MESSAGE[i]);
  }
  
  Postamble();
  HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_RESET); // Led 
}

/* **************************************************
Tar in sensorvärdet och omvandlar till procent.
Sedan lagras värdet på rätt plats i MESSAGE().
*/
void moisture(int m){
  char moist=0; 
  char MSB=0;
  char LSB=0;
  
  moist = m/32;
  
  MSB = moist / 10;
  LSB = moist % 10;
  
  MESSAGE[13] = MSB;
  MESSAGE[12] = LSB;
  /*
  HAL_Delay(1000);
  printf("Moist = %d\n", moist);
  HAL_Delay(1000);
  printf("Moist_MSB = %d\n", MSB);
  HAL_Delay(1000);
  printf("Moist_LSB = %d\n\n", LSB);
  */
}
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();

  /* USER CODE BEGIN 2 */
  double read[20];
//  double voltage;
  double mean = 0;
  double meanval[10];
  double exactval = 0;
  int readnr = 0;
  
  hard_MESSAGE[0] = 0x1;             // 1 ID
  hard_MESSAGE[1] = 0xD;             // D ID
  hard_MESSAGE[2] = 0x2;             // 2 ID
  hard_MESSAGE[3] = 0x0;             // 0 ID
  hard_MESSAGE[4] = 0x4;             // 4 Channel
  hard_MESSAGE[5] = 0xA;             // 8 Rolling
  hard_MESSAGE[6] = 0x5;             // 5 Rolling
  hard_MESSAGE[7] = 0xC;             // C Battery
  hard_MESSAGE[8] = 0x9;             // 4 Temp
  hard_MESSAGE[9] = 0x9;             // 8 Temp
  hard_MESSAGE[10] = 0x9;            // 0 Temp
  hard_MESSAGE[11] = 0x8;            // 8 Temp - = 8,  + = 0
  hard_MESSAGE[12] = 0x0;            // 8 Fukt
  hard_MESSAGE[13] = 0x5;            // 2 Fukt
  hard_MESSAGE[14] = 0x8;            // 8 Unknown
  hard_MESSAGE[15] = 0xf;            // 3 Check
  hard_MESSAGE[16] = 0x4;            // 5 Check

  for(int i = 0; i < sizeof(hard_MESSAGE); i++){
    MESSAGE[i] = hard_MESSAGE[i];
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    
    //Calibration of US_Delay
    /* 
    while(1){
      HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_SET);
      US_Delay(1024);
      HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_RESET);
      US_Delay(1024);
    }
    */
    
    //Läs in 20 AD-värden och ta medelvärdet
    for(int i=0;i<20;i++){
    HAL_ADC_Start(&hadc);
    read[i] = HAL_ADC_GetValue(&hadc);
    HAL_ADC_Stop(&hadc);
    }
    
    for(int i=0;i<20;i++)
      mean += read[i];
    
    
    mean = mean/20;   
    
    if(readnr<=10){
      meanval[readnr] = mean;
    }
    readnr++;
    
    //Spårutskrifter
      /*
    printf("Read number: = %d\n",readnr);
    printf("ADC_Val0 = %.2f\n",read[0]);
    printf("ADC_Mean = %.2f\n",mean);
    voltage = (read[0]/4096) * 3.3;
    printf("Voltage_Val = %.2f\n",voltage);
    voltage = (mean/4096) * 3.3;
    printf("Voltage_Mean = %.2f\n\n",voltage);
    */
    
    
    mean = 0;
    

    
    if(readnr == 10){         // Skickar och nollar
      for(int i = 0; i < 10; i++)
        exactval += meanval[i];
      exactval = exactval/10;
      
      moisture(exactval); //add monew moisture
      
      CheckSum(); //Calc checksum     
      
      //Start TX
      HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
      HAL_Delay(500);
      Send();
      HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_RESET); // TX Set Low
      US_Delay(PULSE*2);
      Send();
      HAL_GPIO_WritePin(GPIOA, TX_Pin, GPIO_PIN_RESET); // TX Set Low
      HAL_Delay(500);
      HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_RESET);
      
      //Indicate TX Done
      HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
      HAL_Delay(71);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
      HAL_Delay(71);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
      HAL_Delay(71);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
      HAL_Delay(71);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);   
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
      HAL_Delay(71);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
      HAL_Delay(71);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
      HAL_Delay(71);
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
      
 //     printf("Exactvalue = %.2f\n\n",exactval);
      exactval=0;
      readnr=0;
    }
    
   HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_SET);
   HAL_Delay(50);
   HAL_GPIO_WritePin(GPIOA, LED3_Pin, GPIO_PIN_RESET);
   HAL_Delay(4950);


  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
