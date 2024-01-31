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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"

//#include "GameObject.cpp"
//#include "Dino.cpp"
#include "Obstacle.cpp"
#include "Score.cpp"
#include "Dino.cpp"

#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
char dinosaur_1[] = {
	0b01011,
	0b00111,
	0b00110,
	0b01110,
	0b11110,
	0b11110,
	0b01010,
	0b01010
};

char dinosaur_2[] = {
	0b00000,
	0b01011,
	0b00111,
	0b00110,
	0b01110,
	0b11110,
	0b11110,
	0b10001
};

//char dinosaur_textures[2][8] = {dinosaur_1, dinosaur_2};

char dinosaur_textures[2][8] = {
    {
        0b01011,
        0b00111,
        0b00110,
        0b01110,
        0b11110,
        0b11110,
        0b01010,
        0b01010
    },
    {
        0b00000,
        0b01011,
        0b00111,
        0b00110,
        0b01110,
        0b11110,
        0b11110,
        0b10001
    }
};

char cactus_1[] = {
	0b00110,
	0b00110,
	0b10111,
	0b11111,
	0b01110,
	0b00110,
	0b00110,
	0b00110,
};

char cactus_2[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00001,
	0b01101,
	0b01111,
	0b01110,
	0b01100
};

char filledSquare[]{
   0b11111,
   0b11111,
   0b11111,
   0b11111,
   0b11111,
   0b11111,
   0b11111,
   0b11111,
};

char notFilledSquare[]{
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void loadCustomChar(uint8_t charNum, const char *pattern) {
	lcd_cmd(0x40 | (charNum << 3)); // Set CGRAM address
	for (int i = 0; i < 8; ++i)
	{
		lcd_char_cp(pattern[i]);
	}
}

void load_custom_chars(){
     loadCustomChar(0, dinosaur_1);
     loadCustomChar(1, dinosaur_2);
     loadCustomChar(2, cactus_1);
     loadCustomChar(3, cactus_2);
     loadCustomChar(4, filledSquare);
     loadCustomChar(5, notFilledSquare);
}

void lcd_transition(){
  int mid = 7;

  for (int i=0; i <= mid; i++) {
    lcd_print(1, mid+i, filledSquare);
    lcd_print(1, mid-i+1, filledSquare);
    lcd_print(2, mid+i, filledSquare);
    lcd_print(2, mid-i+1, filledSquare);
  }

  for (int i=0; i <= mid; i++) {
      lcd_print(1, mid+i, notFilledSquare);
      lcd_print(1, mid-i+1, notFilledSquare);
      lcd_print(2, mid+i, notFilledSquare);
      lcd_print(2, mid-i+1, notFilledSquare);
  }

  lcd_clear();

}

void manage_obstacles(std::vector<Obstacle>& vec) {
    // проверка не пустой ли массив
    if(!vec.empty()){
        if(vec[0].getX() < 0){
            vec.erase(vec.begin());
        }
    }

    // int prevX = 0 так как obst.getX() - prevX <= 2
    int prevX = -Dino::FLY_TIME;
    int group_counter = 1;
    for (Obstacle& obst : vec) {
        if(obst.getX() - prevX <= 2){
            group_counter++;
        } else {
            group_counter = 1;
        }
        prevX = obst.getX();
    }

    std::srand(static_cast<unsigned>(std::time(0)));
    int chanseToCreateObstacle = std::rand() % 10 + 1;

    if(group_counter < Dino::FLY_TIME){  // add new obstacles
        if(chanseToCreateObstacle <= 1){
            vec.emplace_back(Obstacle(cactus_2));
        }else if(chanseToCreateObstacle <= 4){
            vec.emplace_back(Obstacle(cactus_1));
        }
    }
}


void end_game(Score* score){
  lcd_transition();
  score->calculateMaxScore();

  char max_score[3];
  std::sprintf(max_score, "%d", score->MAX_SCORE);

  lcd_print(1, 1, "MAX_SCORE:");
  lcd_print(1, 14, max_score);
  lcd_print(2, 1, "CURRENT_SCORE:");
  lcd_print(2, 14, score->getTexture());

  // Catch algorithm in the loop which breaks after the USER_BTN is pressed
  while (HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, USER_BTN_Pin) == GPIO_PIN_SET) {}
}

void game(Score* score) {
	Dino dino(dinosaur_textures, 3, 2);
	std::vector<Obstacle> obstacles;
//	Score score();
	score->reset();

	int delay = 600;
	int gameOver = false;	// default: 0

	while (!gameOver) {
		// Check if Dino is currently in the air
		if (dino.getY() == 1) dino.fall();
		// If Dino is on the ground and the USER_BTN is pressed – jump
		else if (HAL_GPIO_ReadPin(USER_BTN_GPIO_Port, USER_BTN_Pin) == GPIO_PIN_RESET) {
			dino.jump();
		}

		// Iterate through the obstacles
		for (Obstacle& obst : obstacles) {
			obst.move();						// Move the current obstacle
			gameOver = obst.collides(dino);	// Check if dino collides the obstacle
			obst.draw();						// Draw the obstacle
		}

		// Rise Player's score
		score->up();
		// If score has reached it's max.value – game ends
		if (score->get() >= score->SCORE_LIMIT) gameOver = true;

		manage_obstacles(obstacles);

		// Clear the LCD screen before drawing objects
		lcd_clear();
		// Draw player charachter and score
		dino.draw();
		score->draw();
		// Draw all the obstacles
		for (Obstacle& obst : obstacles) {
			obst.draw();
		}

		// Delays before the next frame
		delay -= 5;
		HAL_Delay(delay);
	}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	lcd_init(8, 1, 2);
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
  /* USER CODE BEGIN 2 */
  load_custom_chars();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Create score display at the (x:14, y:1)
	  Score score(14, 1);
	  // Make smooth transition to the game start
	  lcd_transition();
	  // Starts the game
	  game(&score);
	  // Shows endgame screen with the Top Score and the Current Score
	  end_game(&score);
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

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_D7_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D6_Pin LCD_D5_Pin LCD_D4_Pin */
  GPIO_InitStruct.Pin = LCD_D6_Pin|LCD_D5_Pin|LCD_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_EN_Pin */
  GPIO_InitStruct.Pin = LCD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D7_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_D7_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
