/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "robot_config.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// MOTOR����
int Vertical_out, Velocity_out, Turn_out; // ֱ����&�ٶȻ�&ת�򻷵��������
int Encoder_Left, Encoder_Right, Balance_PWM;
int Moto1, Moto2;
int PWM_out, Turn_Pwm; //�ջ����
int dead_zone =300;// 3000 ;		//L298N�������� 0 - 3000
uint8_t AIN1, AIN2;//���Ƶ������ת
uint8_t BIN1, BIN2;
uint8_t Moto_Flag=0;//������Ʊ�־

// PID����
float Vertical_Kp= 0, Vertical_Kd= 0;	//ֱ����Kp,Kd
float kp=10,ki=0.5;

// MPU6050����
float temp;
float pitch = 0, roll = 0, yaw = 0;   //ŷ����
short gyro[3] = {0};//gyro_x, gyro_y, gyro_z;        // ���ٶ�
short acc[3] = {0};//acc_x, acc_y, acc_z;           // ���ٶ�
float Med_Angle=-0.2;//��е��ֵ����ʹ��С������ƽ��ס�ĽǶ�

// ������������
float temperature = 0;
float humidity = 0;
float distance = 0;

// openmv���ձ���
uint8_t USART1_RXbuff;
extern uint8_t center_x ,center_y ,color_type ;
extern double center_x_cm,center_y_cm;


uint8_t Start_Flag=0;//ϵͳ��ʼ����ɱ�־
uint8_t i = 0;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint16_t tempt;/*������ʱ������Ž��ܵ�����*/
    if(huart->Instance==USART1)
    {
        tempt=USART1_RXbuff;

        openmv_receive_data(tempt);
    }
    HAL_UART_Receive_IT(&huart1,(void *)&USART1_RXbuff,1);/*�ٴο��������ж�*/
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  // openmv���ձ���
    int temp_x = center_x,temp_y = center_y;
    char temp_color = color_type;
    /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
    HAL_UART_Receive_IT(&huart1,(void *)&USART1_RXbuff,1);

  // �����ʼ��
    PCA9685_Init(50,60);   //PCA9685--16·�����ʼ��  Ƶ��50Hz -- 0��
//    DHT11_GPIO_Init();          //DHT11���ų�ʼ��
    Ultrasonic_Init();
//    Buzzer_Init();

//    // MPU6050��ʼ��
//    MPU6050_Init();
//    // DMP��ʼ��
//    while( mpu_dmp_init() )
//    {
//        printf("dmp error\r\n");
//        HAL_Delay(1000);
//    }
//    printf("Initialization Data Succeed \r\n");
//    //SERVO_PWM
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // ������ʱ��1��ͨ��1��PWM���
//    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4); // ������ʱ��1��ͨ��4��PWM���
//    // MOTOR_PWM
//    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
//    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
//
//    //������
//    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1);
//    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_2);
//    HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);
//    HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);

    Start_Flag = 1; //��־ϵͳ��ʼ���ɹ�
    printf(" Start_Flag Succeed \r\n");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      //��ȡŷ����
//      if( mpu_dmp_get_data(&pitch,&roll,&yaw) == 0 )
//      {
//          MPU6050ReadGyro(gyro);  // ��ȡ���ٶ�
//          MPU6050ReadAcc(acc); // ��ȡ���ٶ�
//          temp = MPU6050_GetTemp();
//          printf("pitch:%f,roll:%f,yaw:%f,temp:%f\r\n",pitch,roll,yaw,temp);
//          calculate();
//      }

// openmv_sg90_arm
//      temp_x = center_x,temp_y = center_y,temp_color = color_type;
//      HAL_Delay(200);
//      coordinate_transformation(temp_x,temp_y);
//      if(temp_color == 'B')
//      {
//          blue_task();
//      }
//
////      else if(temp_color == 'Y')
////      {
////          yellow_task();
////      }
//
//      else
//      {
//          servo_reset();
//          continue;
//      }
//      center_x = 0;
//      center_y = 0;
//      temp_color = 'A';
//      HAL_Delay(100);

// �����е��
//    setAngle(0,90);
//    HAL_Delay(20);
//    setAngle(1,85);
//    HAL_Delay(20);
//    setAngle(2,97);
//    HAL_Delay(20);
//    setAngle(3,82);
//    HAL_Delay(20);
//    setAngle(4,85);
//    HAL_Delay(20);
//    setAngle(5,173);
//    HAL_Delay(20);
    setAngle(6,180);
    HAL_Delay(20);
    setAngle(7,110);
//
//    Buzzer_On();
//    HAL_Delay(1000);
//    Buzzer_Off();
//    HAL_Delay(1000);

// ����
//    DHT11_Read_Data();
//    temperature = Get_temperature();
//    humidity = Get_humidity();
    distance = Hcsr04GetLength();
//    AdjustServo();

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
