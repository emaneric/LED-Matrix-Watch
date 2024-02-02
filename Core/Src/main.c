/* USER CODE BEGIN Header */
/**
RGB color order is BGR
Piskel generated BGR colors automatically
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MONTH (\
  __DATE__ [2] == 'n' ? (__DATE__ [1] == 'a' ? 1 : 6) \
: __DATE__ [2] == 'b' ? 2 \
: __DATE__ [2] == 'r' ? (__DATE__ [0] == 'M' ? 3 : 4) \
: __DATE__ [2] == 'y' ? 5 \
: __DATE__ [2] == 'l' ? 7 \
: __DATE__ [2] == 'g' ? 8 \
: __DATE__ [2] == 'p' ? 9 \
: __DATE__ [2] == 't' ? 10 \
: __DATE__ [2] == 'v' ? 11 \
: 12)

#define RED 0xFF0000
#define ORANGE 0xFF8400
#define GREEN 0x00FF00
#define BLUE 0x0000FF

#define NONE 0x000000

#define displaySizeX 12
#define displaySizeY 7
#define displayTotalPix 84

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
//const uint8_t numLED = 84;
const uint8_t empty_frame = 0;

static uint32_t test_image[1][84] = {
{
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200,
0xff0000ff, 0xff0000ff, 0xff0000ff, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xff00ff53, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200, 0xffff6200
}
};

static uint32_t one[1][35] = {	//5x7
{
0xff000000, 0xff000000, 0xffffffff, 0xff000000, 0xff000000,
0xff000000, 0xffffffff, 0xffffffff, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xffffffff, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xffffffff, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xffffffff, 0xff000000, 0xff000000,
0xff000000, 0xff000000, 0xffffffff, 0xff000000, 0xff000000,
0xff000000, 0xffffffff, 0xffffffff, 0xffffffff, 0xff000000
}
};

uint32_t frame_buffer[84] = {
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};

static const uint32_t test_sprite[1][16] = {
{
0xff0000ff, 0xff00fffb, 0xff00fffb, 0xff0000ff,
0xffff00d9, 0xff0000ff, 0xff0000ff, 0xff36b800,
0xffff00d9, 0xff0000ff, 0xff0000ff, 0xff36b800,
0xff0000ff, 0xffff000f, 0xffff000f, 0xff0000ff
}
};

static const uint32_t test_sprite2[1][8] = {
{
0xff0000ff, 0xff00ff00,
0xff0000ff, 0xff00ff00,

}
};

static const uint32_t star_animation[6][25] = {
{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000,
0x00000000, 0xffffffff, 0xffffffff, 0xffffffff, 0x00000000,
0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000,
0x00000000, 0xffffffff, 0x00000000, 0xffffffff, 0x00000000,
0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
},
{
0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000,
0x00000000, 0xffffffff, 0x00000000, 0xffffffff, 0x00000000,
0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff,
0x00000000, 0xffffffff, 0x00000000, 0xffffffff, 0x00000000,
0x00000000, 0x00000000, 0xffffffff, 0x00000000, 0x00000000
},
{
0x00000000, 0xffffffff, 0x00000000, 0xffffffff, 0x00000000,
0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff,
0x00000000, 0xffffffff, 0x00000000, 0xffffffff, 0x00000000
},
{
0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0xffffffff, 0x00000000, 0x00000000, 0x00000000, 0xffffffff
}
};

static const uint32_t heart[1][42] = {
{
0x00000000, 0xffd600ff, 0xffd600ff, 0x00000000, 0xffd600ff, 0xffd600ff, 0x00000000,
0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff,
0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff,
0x00000000, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0x00000000,
0x00000000, 0x00000000, 0xffd600ff, 0xffd600ff, 0xffd600ff, 0x00000000, 0x00000000,
0x00000000, 0x00000000, 0x00000000, 0xffd600ff, 0x00000000, 0x00000000, 0x00000000
}
};

float global_brightness = 0.1;	//0.05 to 1

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
//void set_time_auto(void);
void initDisplay(void);
void fillDisplay(uint32_t color);
//void drawSprite(uint8_t x, uint8_t y, uint8_t sprite_width, uint8_t sprite_height, uint32_t sprite_array[][sprite_width*sprite_height], uint32_t color);
void drawSprite(int8_t x, int8_t y, uint8_t sprite_width, uint8_t sprite_height, uint32_t sprite_array[sprite_width*sprite_height], uint32_t color);
void clearDisplay(void);
void tx_start_frame(void);
void tx_end_frame(void);
void updateDisplay(void);
uint32_t RGB_to_BGR(uint32_t RGB);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//RTC_TimeTypeDef sTime1;
	//RTC_DateTypeDef sDate1;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  //uint8_t frame = 0;
  //uint8_t frame_total = sizeof(new_piskel_data)/sizeof(new_piskel_data[0]);


  //It is important not to exceed battery current limit, nominally 150mA
  //normal range for global brightness should be 0.05 to 0.3
  //When when all pixels are on, brightness need to be lowered to stay within 150mA current draw

  //power on and clear LEDs
  initDisplay();
  /* USER CODE END 2 */

  uint8_t sprite_x_pos = 0;
  int8_t mode = 1;

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  //memcpy(frame_buffer, test_image, displayTotalPix*4);
	  //updateDisplay();
	  //HAL_Delay(1000);
	  //clearDisplay();
	  //updateDisplay();
	  //HAL_Delay(1000);



	  //drawSprite(0,0,12,7,test_image,0);
	  //drawSprite(0,0,12,7,test_image[0],0);
	  //drawSprite(3,1,2,2,test_sprite2[0],0);

	  //drawSprite(3,1,2,2,test_sprite2[0],0);
	  //updateDisplay();	//send the frame buffer to the display
	  //HAL_Delay(500);
	  //clearDisplay();


	  drawSprite(sprite_x_pos,0,5,7,one[0],ORANGE);

	  drawSprite(0,0,7,6,heart[0],NONE);

	  updateDisplay();
	  HAL_Delay(100);
	  clearDisplay();

	  sprite_x_pos = sprite_x_pos + mode;

	  if (sprite_x_pos > 7)
	  {
		  mode = -1;
	  }

	  if (sprite_x_pos < 1)
	  {
		  mode = 1;
	  }


/*	  drawSprite(1,1,5,5,star_animation[0],0);
	  updateDisplay();	//send the frame buffer to the display


	  drawSprite(6,1,5,5,star_animation[5],0);
	  updateDisplay();	//send the frame buffer to the display
	  HAL_Delay(70);


	  drawSprite(1,1,5,5,star_animation[1],0);
	  updateDisplay();	//send the frame buffer to the display



	  drawSprite(6,1,5,5,star_animation[0],0);
	  updateDisplay();	//send the frame buffer to the display
	  HAL_Delay(200);


	  drawSprite(1,1,5,5,star_animation[2],0);
	  updateDisplay();	//send the frame buffer to the display



	  drawSprite(6,1,5,5,star_animation[1],0);
	  updateDisplay();	//send the frame buffer to the display
	  HAL_Delay(200);


	  drawSprite(1,1,5,5,star_animation[3],0);
	  updateDisplay();	//send the frame buffer to the display


	  drawSprite(6,1,5,5,star_animation[2],0);
	  updateDisplay();	//send the frame buffer to the display
	  HAL_Delay(200);


	  drawSprite(1,1,5,5,star_animation[4],0);
	  updateDisplay();	//send the frame buffer to the display


	  drawSprite(6,1,5,5,star_animation[3],0);
	  updateDisplay();	//send the frame buffer to the display
	  HAL_Delay(200);


	  drawSprite(1,1,5,5,star_animation[5],0);
	  updateDisplay();	//send the frame buffer to the display


	  drawSprite(6,1,5,5,star_animation[4],0);
	  updateDisplay();	//send the frame buffer to the display
	  HAL_Delay(200);


	  clearDisplay();*/




/*	  uint8_t sprite_size = sizeof(one)/sizeof(one[0][0]);

	  for (uint8_t i = 0; i <= sprite_size; i++)
	  {
			  //if x is larger than x size of the chacater to draw, skip forward in the  array
			  if (x == 5){	//5 -1 = 4
				  x = x + 7;	//12-5 = 7

				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }

			  else if (x == 17){
				  x = x + 7;
				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }
			  else if (x == 29){
				  x = x + 7;
				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }
			  else if (x == 41){
				  x = x + 7;
				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }
			  else if (x == 53){
				  x = x + 7;
				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }
			  else if (x == 65){
				  x = x + 7;
				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }
			  else if (x == 77){
				  x = x + 7;
				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }

			  else
			  {
				  if (((one[0][i]) & 0x00FFFFFF) != 0) frame_buffer[x] = one[0][i];
				  x++;
			  }


	  }*/

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_EN_Pin */
  GPIO_InitStruct.Pin = LED_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_EN_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void initDisplay(void)
{
	//HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 0);
	//HAL_Delay(1000);
	HAL_GPIO_WritePin(LED_EN_GPIO_Port, LED_EN_Pin, 1);
	HAL_Delay(10);
	clearDisplay();
	//__NOP();
}

void clearDisplay(void)
{
	uint8_t clear_frames[] = {0b11100000, 0, 0, 0};

	tx_start_frame();
	for (uint8_t i = 0; i <= displayTotalPix; i++) HAL_SPI_Transmit(&hspi1, clear_frames, 4, 100);
	tx_end_frame();

	memset(frame_buffer, 0, displayTotalPix*4);
}

void fillDisplay(uint32_t color)
{
	for (uint8_t i = 0; i <= displayTotalPix; i++)
	{
		frame_buffer[i] = color;
	}
}


//void drawSprite(uint8_t x, uint8_t y, uint8_t sprite_width, uint8_t sprite_height, uint32_t sprite_array[][sprite_width*sprite_height], uint32_t color)
void drawSprite(int8_t x, int8_t y, uint8_t sprite_width, uint8_t sprite_height, uint32_t sprite_array[sprite_width*sprite_height], uint32_t color)
{

	//x = 0, y = 0, one, 5 x 7, 0

	//uint8_t sprite_size = sizeof(one)/sizeof(one[0][0]);
	//uint8_t sprite_size = sizeof(sprite_array)/sizeof(sprite_array[0]);
	uint8_t sprite_size = sprite_width * sprite_height;
	uint8_t display_i = 0;
	uint8_t sprite_i = 0;
	uint8_t line_count = 1;
	uint8_t line_start = 0;
	uint8_t found_endLine = 0;

	//stores the numbers for when to skip lines in the display_i index given the dimmensions of the sprite
	uint8_t sprite_endlines[sprite_height];
	sprite_endlines[0] =  sprite_width - 1;

	for (uint8_t i = 1; i <= sprite_height; i++)
	{
		sprite_endlines[i] = sprite_endlines[i-1] + sprite_width;
	}



	display_i = (displaySizeX * y) + x;	//start off from the correct index
	while (sprite_i <= (sprite_size - 1))
	{

		//frame_buffer[display_i] = sprite_array[sprite_i];	//working well!
		if(((sprite_array[sprite_i] & 0x00FFFFFF) != 0) && color != 0)	//testing if color works
		{
			frame_buffer[display_i] = color;
		}
		else
		{
			frame_buffer[display_i] = sprite_array[sprite_i];	//working well!
		}

		//search if sprite_i is in the list of endlines
		//for(uint8_t i = 0; i < (sizeof(sprite_endlines)/sizeof(sprite_endlines[0])); i++)
		for (uint8_t i = 0; i <= sprite_height; i++)
		{
		    if (sprite_i == sprite_endlines[i])
		    {
		    	display_i = display_i + (displaySizeX - sprite_width + 1);
		    	found_endLine = 1;
		        break;
		    }
		}
		//if for loop didn't find anything, do not go to the next line
		if (found_endLine == 0)
		{
			display_i++;
		}
		//reset the found endline flag
		else
		{
			found_endLine = 0;
		}



/*		if (sprite_i == 4)	//need to find how to programatically find these numbers
		//if (sprite_i == sprite_width - 1)
		{
			display_i = display_i + (displaySizeX - sprite_width + 1);
		}

		else if (sprite_i == 9)
		{
			display_i = display_i + (displaySizeX - sprite_width + 1);
		}

		else if (sprite_i == 14)
		{
			display_i = display_i + (displaySizeX - sprite_width + 1);
		}


		else
		{
			display_i++;
		}*/

		//frame_buffer[display_i] = sprite_array[sprite_i];

		sprite_i++;
	}
/*	while (sprite_i <= (sprite_size - 1)){

		if (line_start == 0)
		{
			display_i = (displaySizeX * y) + x + sprite_i + 1; //not sure about the extra one added
		}

		frame_buffer[display_i] = sprite_array[sprite_i];
		sprite_i++;
		__NOP();

		if (sprite_i == (sprite_width) * line_count){
			display_i = display_i + displaySizeX;
			line_count++;
			line_start = 1;
		}

		else
		{
			line_start = 0;
		}


	}*/
























/*	  for (uint8_t sprite_i = 0; sprite_i <= sprite_size; sprite_i++)
	  {
			  //if x is larger than x size of the chacater to draw, skip forward in the  array
			  if (frameBuffer_i == 5){	//5 -1 = 4
				  frameBuffer_i = frameBuffer_i + 7;	//12-5 = 7
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }

			  else if (frameBuffer_i == 17){
				  frameBuffer_i = frameBuffer_i + 7;
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }
			  else if (frameBuffer_i == 29){
				  frameBuffer_i = frameBuffer_i + 7;
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }
			  else if (frameBuffer_i == 41){
				  frameBuffer_i = frameBuffer_i + 7;
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }
			  else if (frameBuffer_i == 53){
				  frameBuffer_i = frameBuffer_i + 7;
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }
			  else if (frameBuffer_i == 65){
				  frameBuffer_i = frameBuffer_i + 7;
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }
			  else if (frameBuffer_i == 77){
				  frameBuffer_i = frameBuffer_i + 7;
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }

			  else
			  {
				  if (((one[0][sprite_i]) & 0x00FFFFFF) != 0) frame_buffer[frameBuffer_i] = one[0][sprite_i];
				  frameBuffer_i++;
			  }
	  }*/


}









void tx_start_frame(void)
{
	HAL_SPI_Transmit(&hspi1, (uint8_t *)&empty_frame, 1, 100);
}

void tx_end_frame(void)
{
	for (uint8_t i = 0; i <= 6; i++) HAL_SPI_Transmit(&hspi1, (uint8_t *)&empty_frame, 1, 100);
}

void updateDisplay(void)
{
	tx_start_frame();

	for (uint8_t i = 0; i <= displayTotalPix; i++) {

		  //get the color values from the frame array
		  //uint8_t red = (frame_buffer[i] & 0xFF0000) >> 16;
		  //uint8_t green = (frame_buffer[i] & 0xFF00) >> 8;
		  //uint8_t blue = (frame_buffer[i] & 0xFF);
		  uint8_t blue = (frame_buffer[i] & 0xFF0000) >> 16;
		  uint8_t green = (frame_buffer[i] & 0xFF00) >> 8;
		  uint8_t red = (frame_buffer[i] & 0xFF);

		  //scale the color values with global brightness
		  red = red * global_brightness;
		  green = green * global_brightness;
		  blue = blue * global_brightness;

		  //set the local brightness for a given pixel based on global brightness
		  uint8_t pixel_brightness = 31 * global_brightness;
		  uint8_t pixel_start = 0b11100000 | pixel_brightness;

		  //uint8_t tx_buffer[] = {pixel_start, red, green, blue};
		  uint8_t tx_buffer[] = {pixel_start, blue, green, red};

		  HAL_SPI_Transmit(&hspi1, tx_buffer, 4, 100);
	  }

	  tx_end_frame();
}

uint32_t RGB_to_BGR(uint32_t RGB)
{
	uint32_t red = (RGB  & 0xFF0000) >> 16;
	uint32_t green = (RGB  & 0x00FF00);
	uint32_t blue = (RGB  & 0x0000FF) << 16;
	uint32_t BGR = 0xFF000000 | red | green | blue;	//combine and add the alpha channel
	return(BGR);
}
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
