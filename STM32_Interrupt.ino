bool flag=0;
void *handler;
void setup() 
{
  Serial.begin(115200);
  RCC_BASE->APB2ENR |= 1|(1<<2); // Enable clock to Port A
  //PA0,PA1 input pullup
  GPIOA_BASE->CRL |= ((1<<3)|(1<<7)); 
  GPIOA_BASE->CRL &= ~(1|(1<<1)|(1<<2)|(1<<4)|(1<<5)|(1<<6));
  GPIOA_BASE->ODR |= 1|(1<<1); 
  //attachInterrupt(PA0,EXTI0_IRQHandler,FALLING);
   
  // Interrupt Pin Selection (PA0)
  AFIO_BASE->EXTICR1 = 0;
  EXTI_BASE->IMR = 0xFFFFF;
  EXTI_BASE->EMR = 0xFFFFF;
  //EXTI_BASE->RTSR |= 1;
  EXTI_BASE->FTSR |= 1; 
  //handler = &EXTI0_IRQHandler;
  //exti_channels[EXTI0].handler = handler;
  nvic_irq_enable(NVIC_EXTI0);
  nvic_globalirq_enable();
  nvic_irq_set_priority(NVIC_EXTI0,0);
  pinMode(PC13,OUTPUT);
}

void loop() 
{
  /*
  if (EXTI_BASE->PR &1 >0)
  {
    digitalWrite(PC13,HIGH);
    //Serial.println("Interrupt");
    delay(1000);
    EXTI_BASE->PR =1;
  }
  
  else if (EXTI_BASE->PR &1 ==0)
    digitalWrite(PC13,LOW);
   */ 
  if (flag==1)
   digitalWrite(PC13,HIGH);
  if (flag==0)
   digitalWrite(PC13,LOW);  
    
  // Serial.println(EXTI_BASE->PR);  
    
}

void EXTI0_IRQHandler(void)
{
  //if (EXTI_BASE->PR & (1<<0))
  //{
   //EXTI_BASE->PR |= (1<<0); 
    //Serial.println("Entering");
    flag = !flag; 
  //}   
}

__weak void __irq_exti0(void)
{
 // dispatch_single_exti(EXTI0);
  //Serial.println("Entering");
    flag = !flag; 
}

